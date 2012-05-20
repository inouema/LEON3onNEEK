/*
 * depmod
 *
 * Create dependency file for modprobe, the kernel loadable modules loader.
 *
 * Copyright 1994, 1995, 1996, 1997 Jacques Gelinas <jack@solucorp.qc.ca>
 * Additional modifications: Björn Ekwall <bj0rn@blox.se> February, March 1999
 *
 * This file is part of the Linux modutils.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <ctype.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <syslog.h>
#include <limits.h>
#include <elf.h>
#include ELF_MACHINE_H

#include "module.h"
#include "version.h"
#include "util.h"
#include "obj.h"
#include "config.h"
#include "modstat.h"

#define ALLOC_MODULE	5000	/* Number of modules we can handle... */
#define ALLOC_SYM	10000	/* Number of symbols allocated per chunk */
#define MAX_MAP_SYM	100000	/* Maximum number of symbols in map */

#ifndef __u32
#define __u32 u_int32_t
#endif
#ifndef __u16
#define __u16 u_int16_t
#endif
#ifndef __u8
#define __u8 u_int8_t
#endif

typedef struct SYMBOL{
	struct SYMBOL *next;	/* List connected via hashing */
	struct MODULE *module;	/* Module declaring this symbol */
	const char *name;
	unsigned short hashval;
	unsigned short hashval_nosuffix;
	unsigned short length_nosuffix;
	char status;
} SYMBOL;

/* Extracted from 2.4.0-test6-pre6/include/linux/pci.h */

unsigned int pci_device_id_ver;

struct pci_device_id {
	unsigned int vendor, device;		/* Vendor and device ID or PCI_ANY_ID */
	unsigned int subvendor, subdevice;	/* Subsystem ID's or PCI_ANY_ID */
	unsigned int class, class_mask;		/* (class,subclass,prog-if) triplet */
	unsigned tgt_long driver_data;		/* Data private to the driver */
};

/* Extracted from 2.4.0-test10-pre1 /include/linux/isapnp.h */

unsigned int isapnp_device_id_ver;

struct isapnp_device_id {
	unsigned short card_vendor, card_device;
	unsigned short vendor, function;
	unsigned tgt_long driver_data;		/* data private to the driver */
};

/* Extracted from 2.4.0-test10-pre1 /include/linux/isapnp.h */
#define ISAPNP_CARD_DEVS	8
struct isapnp_card_id {
	unsigned tgt_long driver_data;	/* data private to the driver */
	unsigned short card_vendor, card_device;
	struct {
		unsigned short vendor, function;
	} devs[ISAPNP_CARD_DEVS];	/* logical devices */
};

/* Version 1 table extracted from 2.4.0-test10-pre3 + David Brownell
 * usb-device_id patch 2.
 * Version 2 table extracted from 2.4.0 + Keith Owens 2.4.0-depmod patch.
 * Update 23/01/2001.  Drop version 2 and old version 1.  New version 1
 * is now from kernel 2.4.0.
 */

/*
 * Device table entry for "new style" table-driven USB drivers.
 * User mode code can read these tables to choose which modules to load.
 * Declare the table as __devinitdata, and as a MODULE_DEVICE_TABLE.
 *
 * With a device table provide bind() instead of probe().  Then the
 * third bind() parameter will point to a matching entry from this
 * table.  (Null value reserved.)
 *
 * Terminate the driver's table with an all-zeroes entry.
 * Init the fields you care about; zeroes are not used in comparisons.
 *
 * match_flags was added in kernel 2.4.0 but it was incorrectly put at the start
 * of the structure.  KAO moved it to before driver_info and defined that format
 * as a version 2 table for kernel 2.4.1 and modutils 2.4.1.  USB modules will
 * not be supported in standard kernel 2.4.0, with any version of modutils.
 *
 * Update 23/01/2001.  USB maintainers will not support anybody using the USB
 * table format in 2.4.0-prerelease or earlier.  Without their support, Linus
 * will not apply my patch to add version numbers to kernel tables.  Without the
 * version number, depmod cannot distinguish between 2.4.0-prelease or earlier
 * formats and 2.4.0.  So it has to assume 2.4.0 format for everybody.  This
 * will break USB for anybody using modutils >= 2.4.2 on kernels before 2.4.0.
 */

unsigned int usb_device_id_ver;

struct usb_device_id {
	/* This bitmask is used to determine which of the following fields
	 * are to be used for matching.
	 */
	__u16		match_flags;

	/*
	 * vendor/product codes are checked, if vendor is nonzero
	 * Range is for device revision (bcdDevice), inclusive;
	 * zero values here mean range isn't considered
	 */
	__u16		idVendor;
	__u16		idProduct;
	__u16		bcdDevice_lo, bcdDevice_hi;

	/*
	 * if device class != 0, these can be match criteria;
	 * but only if this bDeviceClass value is nonzero
	 */
	__u8		bDeviceClass;
	__u8		bDeviceSubClass;
	__u8		bDeviceProtocol;

	/*
	 * if interface class != 0, these can be match criteria;
	 * but only if this bInterfaceClass value is nonzero
	 */
	__u8		bInterfaceClass;
	__u8		bInterfaceSubClass;
	__u8		bInterfaceProtocol;

	/*
	 * for driver's use; not involved in driver matching.
	 */
	unsigned tgt_long	driver_info;
};

/* Supplied by Adam J. Richter, approx 2.4.0-test13, modified by KAO.
 * Although the kernel defines pattern as char *, define it as ElfW(Addr)
 * to make combined 32/64 code work.
 */

unsigned int parport_device_id_ver;

struct parport_device_id {
	ElfW(Addr) pattern;
};

/* Device tables for ieee1394 devices.
 * Added sep. 15, 2001, Kristian Hogsberg <hogsberg@users.sf.net>.
 * See linux/drivers/ieee1394/ieee1394_hotplug.h
 * Although the kernel defines driver_data as void *, define it as ElfW(Addr)
 * to make combined 32/64 code work.
 */

unsigned int ieee1394_device_id_ver;

struct ieee1394_device_id {
	__u32 match_flags;
	__u32 vendor_id;
	__u32 model_id;
	__u32 specifier_id;
	__u32 version;
	ElfW(Addr) driver_data;
};

/*
 * Device tables for pnpbios devices.
 * Added Nov. 1, 2001, Andrey Panin <pazke@orbita1.ru>.
 * See /include/linux/pnp_bios.h
 */

unsigned int pnpbios_device_id_ver;

struct pnpbios_device_id {
	char id[8];
	ElfW(Addr) driver_data;
};

typedef struct MODULE {
	char *name;
	int resolved;
	struct {	/* Defined + required symbols for this module */
		SYMBOL **symtab;
		int n_syms;
	} defsym, undefs;
	char **generic_string;
	int n_generic_string;
	struct pci_device_id *pci_device;
	int n_pci_device;
	struct isapnp_device_id *isapnp_device;
	int n_isapnp_device;
	struct isapnp_card_id *isapnp_card;
	int n_isapnp_card;
	struct usb_device_id *usb_device;
	int n_usb_device;
	struct parport_device_id *parport_device;
	int n_parport_device;
	struct ieee1394_device_id *ieee1394_device;
	int n_ieee1394_device;
	struct pnpbios_device_id *pnpbios_device;
	int n_pnpbios_device;
} MODULE;

typedef enum SYM_STATUS {
	SYM_UNDEF,	/* Required by another module */
	SYM_DEFINED,	/* We have found a module that knows about it */
	SYM_RESOLVED
} SYM_STATUS;

typedef struct LIST_SYMBOL {
	struct LIST_SYMBOL *next;
	SYMBOL alloc[ALLOC_SYM];
} LIST_SYMBOL;

/*==================================================*/

static MODULE modules[ALLOC_MODULE];
static int n_modules;
static SYMBOL *symhash[2048];
static SYMBOL *symavail;
static SYMBOL *maxsyms;
static LIST_SYMBOL *chunk;

extern int flag_unresolved_error;

static int quiet;	/* Don't print errors */
static int showerror;	/* Shows undefined symbols */
#if !defined(COMMON_3264) || defined(ONLY_64)
int flag_verbose = 0;
int flag_unresolved_error = 0;
#endif

extern int depmod_main(int argc, char **argv);
extern int depmod_main_32(int argc, char **argv);
extern int depmod_main_64(int argc, char **argv);

extern int quick;	/* Option -A */


/*
 *	Create a symbol definition.
 *	Add defined symbol to the head of the list of defined symbols.
 *	Return the new symbol.
 */
static SYMBOL *addsym(const char *name, MODULE *module, SYM_STATUS status,
		      int ignore_suffix)
{
	SYMBOL added;
	SYMBOL *me;
	unsigned short hashval = 0;
	const char *pt = name, *pt_R;
	char *p;
	int l;

	for (pt = name; *pt; ++pt)
		hashval = (hashval << 1) ^ *pt;
	hashval %= 2048;

	memset(&added, 0, sizeof(SYMBOL));
	added.module = module;
	added.name = xstrdup(name);
	added.hashval = hashval;
	added.status = status;

	/* Compute the hash without the trailing genksym suffix if required */
	if (ignore_suffix && (pt_R = strstr(name, "_R"))) {
		while ((p = strstr(pt_R+2, "_R"))) pt_R = p;
		l = strlen(pt_R);
		if (l >= 10) {	/* May be _R.*xxxxxxxx */
			(void)strtoul(pt_R+l-8, &p, 16);
			if (!*p) { /* It is _R.*xxxxxxxx */
				added.length_nosuffix = pt_R - name;
				hashval = 0;
				for (pt = name; pt < pt_R; ++pt)
					hashval = (hashval << 1) ^ *pt;
				hashval %= 2048;
				added.hashval_nosuffix = hashval;
			}
		}
	}
	else {
		added.hashval_nosuffix = 0;
		added.length_nosuffix = 0;
	}

	if (status == SYM_DEFINED) {
		if (symavail == NULL ||
		    symavail == maxsyms) {
			/*
			 * Allocate a new buffer for the collection of symbols
			 */
			LIST_SYMBOL *list = (LIST_SYMBOL *)xmalloc(sizeof(LIST_SYMBOL));
			list->next = chunk;
			chunk = list;
			symavail = list->alloc;
			maxsyms = list->alloc + ALLOC_SYM;
		}
		me = symavail++;
		*me = added;
		me->next = symhash[added.hashval];
		symhash[added.hashval] = me;
	} else {
		me = (SYMBOL *)xmalloc(sizeof(SYMBOL));
		*me = added;
	}

	return me;
}

/************************************************************
 * Module.c
 */

static void resolve(void)
{
	MODULE *mod;
	SYMBOL **sym;
	int i;
	int n;
	int resolved;

	/*
	 * Resolve, starting with the most recently added
	 * module symbol definitions.
	 */
	if (n_modules <= 0)
		return;
	/* else */
	for (i = n_modules - 1, mod = modules + i; i >= 0; --i, --mod) {
		if (mod->resolved)
			continue;

		for (resolved = 1, n = 0, sym = mod->undefs.symtab;
		     n < mod->undefs.n_syms; ++sym, ++n) {
			SYMBOL *psym = *sym, *find;
			const char *name;
			unsigned short hashval;
			unsigned short hashval_nosuffix;
			unsigned short length_nosuffix;

			if (psym->status != SYM_UNDEF)
				continue;

			/* This is an undefined symbol.   Find first
			   definition.  Symbol hash linked list has
			   newest first, so we want the last match in
			   the chain.  In particular, this prefers
			   kernel symbols to that of any module.

			   If we are ignoring the genksyms suffix in this
			   comparision then there are two hashes to try.
			 */

			name = psym->name;
			hashval = psym->hashval;
			hashval_nosuffix = psym->hashval_nosuffix;
			length_nosuffix = psym->length_nosuffix;
#ifdef	ARCH_ppc64
		look_again:
#endif
			find = symhash[hashval];
			while (find) {
				if (strcmp(find->name, name) == 0) {
					psym->status = SYM_RESOLVED;
					psym->module = find->module;
				}
				find = find->next;
			}
			if (psym->status == SYM_UNDEF && length_nosuffix) {
				/* Try again ignoring the suffix */
				find = symhash[hashval_nosuffix];
				while (find) {
					if (strncmp(find->name, name,
					    length_nosuffix) == 0 &&
					    !find->name[length_nosuffix]) {
						psym->status = SYM_RESOLVED;
						psym->module = find->module;
					}
					find = find->next;
				}
			}
			if (psym->status == SYM_UNDEF) {
#ifdef	ARCH_ppc64
				/* ppc64 is one of those architectures with
				   function descriptors.  A function is
				   exported and accessed across object
				   boundaries via its function descriptor.
				   The function code symbol happens to be the
				   function name, prefixed with '.', and a
				   function call is a branch to the code
				   symbol.  The linker recognises when a call
				   crosses object boundaries, and inserts a
				   stub to call via the function descriptor.
				   obj_ppc64.c of course does the same thing,
				   so here we recognise that an undefined code
				   symbol can be satisfied by the
				   corresponding function descriptor symbol.
				*/
				if (name == psym->name && name[0] == '.') {
					const char *pt;

					name++;
					if (length_nosuffix != 0)
						length_nosuffix--;
					hashval = 0;
					for (pt = name; *pt; ++pt) {
						if (pt == name + length_nosuffix)
							hashval_nosuffix = hashval;
						hashval = (hashval << 1) ^ *pt;
					}
					hashval %= 2048;
					hashval_nosuffix %= 2048;
					goto look_again;
				}
#endif	/* ARCH_ppc64 */
				resolved = 0;
			}
		}
		mod->resolved = resolved;
	}
}

/*
 *	Verify that an "address" falls within the module image.
 *	Note: assumes same machine and arch for depmod and module.
 */
static int in_range(const struct obj_file *f, unsigned long m_size,
		    ElfW(Addr) start, unsigned int length)
{
	return(start >= f->baseaddr && (start + length - 1 - f->baseaddr) <= m_size);
}

static const char has_kernel_changed[] =
	"\n\tIt is likely that the kernel structure has changed, if so then"
	"\n\tyou probably need a new version of modutils to handle this kernel."
	"\n\tCheck linux/Documentation/Changes.";

/*
 *	Extract any generic string from the given symbol.
 *	Note: assumes same machine and arch for depmod and module.
 */
static void extract_generic_string(struct obj_file *f, MODULE *mod)
{
	struct obj_section *sec;
	char *p, *ep, *s, **latest;

	sec = obj_find_section(f, ".modstring");
	if (sec == NULL)
		return;
	p = sec->contents;
	ep = p + sec->header.sh_size;
	while (p < ep) {
		s = p;
		while (*p != '\0' && p < ep)
			p++;
		if (p >= ep) {
			error("unterminated generic string '%*s'", (int)(p - s), s);
			break;
		}
		if (p++ == s)		/* empty string? */
			continue;
		mod->generic_string = xrealloc(mod->generic_string, ++(mod->n_generic_string)*sizeof(*(mod->generic_string)));
		latest = mod->generic_string + mod->n_generic_string-1;
		*latest = xstrdup(s);
	}
}

/*
 *	Extract the table version, if any, from the module.  Only call
 *	this routine when you know that the module contains a table.
 *	Note: assumes same machine and arch for depmod and module.
 */
static void extract_version(struct obj_file *f, void *image, unsigned long m_size,
			    const char *table, unsigned int *version,
			    int min_version, int max_version)
{
	ElfW(Addr) ref_ver;
	unsigned tgt_long ver;
	char name[2000];	/* grossly oversized */
	strcpy(name, "__module_");
	strcat(name, table);
	strcat(name, "_ver");
	ref_ver = obj_symbol_final_value(f, obj_find_symbol(f, name));
	/* Kernels before 2.4.1 do not have __module_<table>_ver, default to min_version */
	if (ref_ver) {
		if (!in_range(f, m_size, ref_ver, sizeof(ver)))
			return;
		memcpy(&ver, (char *)image + ref_ver - f->baseaddr, sizeof(ver));
	}
	else
		ver = min_version;
	if (*version && *version != ver) {
		error("Modules have a mixture of version %d and version %" tgt_long_fmt "d %s tables",
			*version, ver, table);
		return;
	}
	if (ver < min_version || ver > max_version) {
		error("Module %s has an unknown version (%" tgt_long_fmt "d) %s table%s",
			f->filename, ver, table, has_kernel_changed);
		return;
	}
	*version = ver;
}

/*
 *	Extract any pci_device_table from the module.
 *	Note: assumes same machine and arch for depmod and module.
 */
static void extract_pci_device_id(struct obj_file *f, void *image, unsigned long m_size, MODULE *mod)
{
	struct pci_device_id pci_device, *latest;
	ElfW(Addr) ref_pci;
	ElfW(Addr) ref_ref_pci;
	unsigned tgt_long pci_device_size;
	ref_pci = obj_symbol_final_value(f, obj_find_symbol(f, "__module_pci_device_size"));
	/* Kernels before 2.4.0-test10-pre1 do not have __module_pci_device_size */
	if (ref_pci) {
		if (!in_range(f, m_size, ref_pci, sizeof(pci_device_size)))
			return;
		memcpy(&pci_device_size, (char *)image + ref_pci - f->baseaddr, sizeof(pci_device_size));
	}
	else
		pci_device_size = sizeof(pci_device);
	ref_ref_pci = obj_symbol_final_value(f, obj_find_symbol(f, "__module_pci_device_table"));
	if (!in_range(f, m_size, ref_ref_pci, sizeof(ref_pci)))
		return;
	memcpy(&ref_pci, (char *)image + ref_ref_pci - f->baseaddr, sizeof(ref_pci));
	extract_version(f, image, m_size, "pci_device", &pci_device_id_ver, 1, 1);
	if (pci_device_size != sizeof(pci_device)) {
		error("Unexpected value (%" tgt_long_fmt "d) in '%s' for pci_device_size%s",
			pci_device_size, f->filename, has_kernel_changed);
		return;
	}
	while (in_range(f, m_size, ref_pci, pci_device_size)) {
		memset(&pci_device, 0, sizeof(pci_device));
		memcpy(&pci_device, (char *)image + ref_pci - f->baseaddr, pci_device_size);
		ref_pci += pci_device_size;
		if (!pci_device.vendor)
			break;
		mod->pci_device = xrealloc(mod->pci_device, ++(mod->n_pci_device)*sizeof(*(mod->pci_device)));
		latest = mod->pci_device + mod->n_pci_device-1;
		*latest = pci_device;
	}
}

/*
 *	Extract any isapnp_device_table from the module.
 *	Note: assumes same machine and arch for depmod and module.
 */
static void extract_isapnp_device_id(struct obj_file *f, void *image, unsigned long m_size, MODULE *mod)
{
	struct isapnp_device_id isapnp_device, *latest;
	ElfW(Addr) ref_isapnp, ref_ref_isapnp;
	unsigned tgt_long isapnp_device_size;
	ref_isapnp = obj_symbol_final_value(f, obj_find_symbol(f, "__module_isapnp_device_size"));
	if (!in_range(f, m_size, ref_isapnp, sizeof(isapnp_device_size)))
		return;
	memcpy(&isapnp_device_size, (char *)image + ref_isapnp - f->baseaddr, sizeof(isapnp_device_size));
	ref_ref_isapnp = obj_symbol_final_value(f, obj_find_symbol(f, "__module_isapnp_device_table"));
	if (!in_range(f, m_size, ref_ref_isapnp, sizeof(ref_isapnp)))
		return;
	memcpy(&ref_isapnp, (char *)image + ref_ref_isapnp - f->baseaddr, sizeof(ref_isapnp));
	extract_version(f, image, m_size, "isapnp_device", &isapnp_device_id_ver, 1, 1);
	if (isapnp_device_size != sizeof(isapnp_device)) {
		error("Unexpected value (%" tgt_long_fmt "d) in '%s' for isapnp_device_size%s",
			isapnp_device_size, f->filename, has_kernel_changed);
		return;
	}
	while (in_range(f, m_size, ref_isapnp, isapnp_device_size)) {
		memset(&isapnp_device, 0, sizeof(isapnp_device));
		memcpy(&isapnp_device, (char *)image + ref_isapnp - f->baseaddr, isapnp_device_size);
		ref_isapnp += isapnp_device_size;
		if (!isapnp_device.card_vendor)
			break;
		mod->isapnp_device = xrealloc(mod->isapnp_device, ++(mod->n_isapnp_device)*sizeof(*(mod->isapnp_device)));
		latest = mod->isapnp_device + mod->n_isapnp_device-1;
		*latest = isapnp_device;
	}
}

/*
 *	Extract any isapnp_card_table from the module.
 *	Note: assumes same machine and arch for depmod and module.
 */
static void extract_isapnp_card_id(struct obj_file *f, void *image, unsigned long m_size, MODULE *mod)
{
	struct isapnp_card_id isapnp_card, *latest;
	ElfW(Addr) ref_isapnp, ref_ref_isapnp;
	unsigned tgt_long isapnp_card_size;
	ref_isapnp = obj_symbol_final_value(f, obj_find_symbol(f, "__module_isapnp_card_size"));
	if (!in_range(f, m_size, ref_isapnp, sizeof(isapnp_card_size)))
		return;
	memcpy(&isapnp_card_size, (char *)image + ref_isapnp - f->baseaddr, sizeof(isapnp_card_size));
	ref_ref_isapnp = obj_symbol_final_value(f, obj_find_symbol(f, "__module_isapnp_card_table"));
	if (!in_range(f, m_size, ref_ref_isapnp, sizeof(ref_isapnp)))
		return;
	memcpy(&ref_isapnp, (char *)image + ref_ref_isapnp - f->baseaddr, sizeof(ref_isapnp));
	if (isapnp_card_size != sizeof(isapnp_card)) {
		error("Unexpected value (%" tgt_long_fmt "d) in '%s' for isapnp_card_size%s",
			isapnp_card_size, f->filename, has_kernel_changed);
		return;
	}
	while (in_range(f, m_size, ref_isapnp, isapnp_card_size)) {
		memset(&isapnp_card, 0, sizeof(isapnp_card));
		memcpy(&isapnp_card, (char *)image + ref_isapnp - f->baseaddr, isapnp_card_size);
		ref_isapnp += isapnp_card_size;
		if (!isapnp_card.card_vendor)
			break;
		mod->isapnp_card = xrealloc(mod->isapnp_card, ++(mod->n_isapnp_card)*sizeof(*(mod->isapnp_card)));
		latest = mod->isapnp_card + mod->n_isapnp_card-1;
		*latest = isapnp_card;
	}
}

/*
 *	Extract any usb_device_table from the module.
 *	Note: assumes same machine and arch for depmod and module.
 */
static void extract_usb_device_id(struct obj_file *f, void *image, unsigned long m_size, MODULE *mod)
{
	struct usb_device_id usb_device, *latest;
	ElfW(Addr) ref_usb, ref_ref_usb;
	unsigned tgt_long usb_device_size;
	ref_usb = obj_symbol_final_value(f, obj_find_symbol(f, "__module_usb_device_size"));
	if (!in_range(f, m_size, ref_usb, sizeof(usb_device_size)))
		return;
	memcpy(&usb_device_size, (char *)image + ref_usb - f->baseaddr, sizeof(usb_device_size));
	ref_ref_usb = obj_symbol_final_value(f, obj_find_symbol(f, "__module_usb_device_table"));
	if (!in_range(f, m_size, ref_ref_usb, sizeof(ref_usb)))
		return;
	memcpy(&ref_usb, (char *)image + ref_ref_usb - f->baseaddr, sizeof(ref_usb));
	extract_version(f, image, m_size, "usb_device", &usb_device_id_ver, 1, 1);
	if (usb_device_size != sizeof(usb_device)) {
		error("Unexpected value (%" tgt_long_fmt "d) in '%s' for usb_device_size%s",
		usb_device_size, f->filename, has_kernel_changed);
		return;
	}
	while (in_range(f, m_size, ref_usb, usb_device_size)) {
		memset(&usb_device, 0, sizeof(usb_device));
		memcpy(&usb_device, (char *)image + ref_usb - f->baseaddr, usb_device_size);
		ref_usb += usb_device_size;
		if (!usb_device.idVendor && !usb_device.bDeviceClass &&
		    !usb_device.bInterfaceClass && !usb_device.driver_info)
		break;
		mod->usb_device = xrealloc(mod->usb_device, ++(mod->n_usb_device)*sizeof(*(mod->usb_device)));
		latest = mod->usb_device + mod->n_usb_device-1;
		*latest = usb_device;
	}
}

/*
 *	Extract any parport_device_table from the module.
 *	Note: assumes same machine and arch for depmod and module.
 */
static void extract_parport_device_id(struct obj_file *f, void *image, unsigned long m_size, MODULE *mod)
{
	struct parport_device_id parport_device, *latest;
	ElfW(Addr) ref_parport, ref_ref_parport;
	unsigned tgt_long parport_device_size;
	ref_parport = obj_symbol_final_value(f, obj_find_symbol(f, "__module_parport_device_size"));
	if (!in_range(f, m_size, ref_parport, sizeof(parport_device_size)))
		return;
	memcpy(&parport_device_size, (char *)image + ref_parport - f->baseaddr, sizeof(parport_device_size));
	ref_ref_parport = obj_symbol_final_value(f, obj_find_symbol(f, "__module_parport_device_table"));
	if (!in_range(f, m_size, ref_ref_parport, sizeof(ref_parport)))
		return;
	memcpy(&ref_parport, (char *)image + ref_ref_parport - f->baseaddr, sizeof(ref_parport));
	extract_version(f, image, m_size, "parport_device", &parport_device_id_ver, 1, 1);
	if (parport_device_size != sizeof(parport_device)) {
		error("Unexpected value (%" tgt_long_fmt "d) in '%s' for parport_device_size%s",
			parport_device_size, f->filename, has_kernel_changed);
		return;
	}
	while (in_range(f, m_size, ref_parport, parport_device_size)) {
		memset(&parport_device, 0, sizeof(parport_device));
		memcpy(&parport_device, (char *)image + ref_parport - f->baseaddr, parport_device_size);
		ref_parport += parport_device_size;
		if (!parport_device.pattern)
			break;
		mod->parport_device = xrealloc(mod->parport_device, ++(mod->n_parport_device)*sizeof(*(mod->parport_device)));
		latest = mod->parport_device+mod->n_parport_device-1;
		*latest = parport_device;
		if (!in_range(f, m_size, parport_device.pattern, 1))
			latest->pattern = obj_native_ptr_to_addr(
				xstrdup("Start address of out range"));
		else
			latest->pattern = obj_native_ptr_to_addr(
				xstrdup((char*)image + parport_device.pattern - f->baseaddr));
	}
}

static void extract_pnpbios_device_id(struct obj_file *f, void *image, unsigned long m_size, MODULE *mod)
{
	struct pnpbios_device_id pnpbios_device, *latest;
	ElfW(Addr) ref_pnpbios, ref_ref_pnpbios;
	unsigned tgt_long pnpbios_device_size;

	ref_pnpbios = obj_symbol_final_value(f, obj_find_symbol(f, "__module_pnpbios_device_size"));
	if (!in_range(f, m_size, ref_pnpbios, sizeof(pnpbios_device_size)))
		return;
	memcpy(&pnpbios_device_size, (char *)image + ref_pnpbios - f->baseaddr, sizeof(pnpbios_device_size));
	ref_ref_pnpbios = obj_symbol_final_value(f, obj_find_symbol(f, "__module_pnpbios_device_table"));
	if (!in_range(f, m_size, ref_ref_pnpbios, sizeof(ref_pnpbios)))
		return;
	memcpy(&ref_pnpbios, (char *)image + ref_ref_pnpbios - f->baseaddr, sizeof(ref_pnpbios));
	extract_version(f, image, m_size, "pnpbios_device", &pnpbios_device_id_ver, 1, 1);
	if (pnpbios_device_size != sizeof(pnpbios_device)) {
		error("Unexpected value (%" tgt_long_fmt "d) in '%s' for pnpbios_device_size%s",
			pnpbios_device_size, f->filename, has_kernel_changed);
		return;
	}
	while (in_range(f, m_size, ref_pnpbios, pnpbios_device_size)) {
		memset(&pnpbios_device, 0, sizeof(pnpbios_device));
		memcpy(&pnpbios_device, (char *)image + ref_pnpbios - f->baseaddr, pnpbios_device_size);
		ref_pnpbios += pnpbios_device_size;
		if (!pnpbios_device.id[0])
			break;
		mod->pnpbios_device = xrealloc(mod->pnpbios_device, ++(mod->n_pnpbios_device)*sizeof(*(mod->pnpbios_device)));
		latest = mod->pnpbios_device + mod->n_pnpbios_device-1;
		*latest = pnpbios_device;
	}
}

/*
 *	Extract any ieee1394_device_table from the module.
 *	Note: assumes same machine and arch for depmod and module.
 */
static void extract_ieee1394_device_id(struct obj_file *f, void *image, unsigned long m_size, MODULE *mod)
{
	struct ieee1394_device_id ieee1394_device, *latest;
	ElfW(Addr) ref_ieee1394, ref_ref_ieee1394;
	unsigned tgt_long ieee1394_device_size;
	ref_ieee1394 = obj_symbol_final_value(f, obj_find_symbol(f, "__module_ieee1394_device_size"));
	if (!in_range(f, m_size, ref_ieee1394, sizeof(ieee1394_device_size)))
		return;
	memcpy(&ieee1394_device_size, (char *)image + ref_ieee1394 - f->baseaddr, sizeof(ieee1394_device_size));
	ref_ref_ieee1394 = obj_symbol_final_value(f, obj_find_symbol(f, "__module_ieee1394_device_table"));
	if (!in_range(f, m_size, ref_ref_ieee1394, sizeof(ref_ieee1394)))
		return;
	memcpy(&ref_ieee1394, (char *)image + ref_ref_ieee1394 - f->baseaddr, sizeof(ref_ieee1394));
	extract_version(f, image, m_size, "ieee1394_device", &ieee1394_device_id_ver, 1, 1);
	if (ieee1394_device_size != sizeof(ieee1394_device)) {
		error("Unexpected value (%" tgt_long_fmt "d) in '%s' for ieee1394_device_size%s",
		ieee1394_device_size, f->filename, has_kernel_changed);
		return;
	}
	while (in_range(f, m_size, ref_ieee1394, ieee1394_device_size)) {
		memset(&ieee1394_device, 0, sizeof(ieee1394_device));
		memcpy(&ieee1394_device, (char *)image + ref_ieee1394 - f->baseaddr, ieee1394_device_size);
		ref_ieee1394 += ieee1394_device_size;
		if (ieee1394_device.match_flags == 0)
			break;
		mod->ieee1394_device = xrealloc(mod->ieee1394_device, ++(mod->n_ieee1394_device)*sizeof(*(mod->ieee1394_device)));
		latest = mod->ieee1394_device + mod->n_ieee1394_device-1;
		*latest = ieee1394_device;
	}
}

/*
 *	Read the symbols in an object and register them in the symbol table.
 *	Return -1 if there is an error.
 */
static int loadobj(const char *objname, int ignore_suffix)
{
	static char *currdir;
	static int currdir_len;
	int fp;
	MODULE *mod;
	SYMBOL *undefs[5000];
	SYMBOL *defsym[5000];
	struct obj_file *f;
	struct obj_section *sect;
	struct obj_symbol *objsym;
	int i;
	int is_2_2;
	int ksymtab;
	int len;
	int n_undefs = 0;
	int n_defsym = 0;
	char *p;
	void *image;
	unsigned long m_size;

	p = strrchr(objname, '/');
	len = 1 + (int)(p - objname);

	if ((fp = gzf_open(objname, O_RDONLY)) < 0)
		return 1;

	if (!(f = obj_load(fp, ET_REL, objname))) {
		gzf_close(fp);
		return -1;
	}
	gzf_close(fp);

	/*
	 * Allow arch code to define _GLOBAL_OFFSET_TABLE_
	 */
	arch_create_got(f);

	/*
	 * If we have changed base directory
	 * then use the defined symbols from modules
	 * in the _same_ directory to resolve whatever
	 * undefined symbols there are.
	 *
	 * This strategy ensures that we will have
	 * as correct dependencies as possible,
	 * even if the same symbol is defined by
	 * other modules in other directories.
	 */
	if (currdir_len != len || currdir == NULL ||
	    strncmp(currdir, objname, len) != 0) {
		if (currdir)
			resolve();
		currdir = xstrdup(objname);
		currdir_len = len;
	}

	mod = modules + n_modules++;
	mod->name = xstrdup(objname);

	if ((sect = obj_find_section(f, "__ksymtab")) != NULL)
		ksymtab = sect->idx; /* Only in 2.2 (or at least not 2.0) */
	else
		ksymtab = -1;

	if (sect ||
	    obj_find_section(f, ".modinfo") ||
	    obj_find_symbol(f, "__this_module"))
		is_2_2 = 1;
	else
		is_2_2 = 0;

	for (i = 0; i < HASH_BUCKETS; ++i) {
		for (objsym = f->symtab[i]; objsym; objsym = objsym->next) {
			if (objsym->secidx == SHN_UNDEF) {
				if (ELFW(ST_BIND)(objsym->info) != STB_WEAK &&
				    objsym->r_type /* assumes that R_arch_NONE is always 0 on all arch */) {
					undefs[n_undefs++] = addsym(objsym->name,
								    mod,
								    SYM_UNDEF,
								    ignore_suffix);
				}
				continue;
			}
			/* else */

			if (is_2_2 && ksymtab != -1) {
				/* A 2.2 module using EXPORT_SYMBOL */
				if (objsym->secidx == ksymtab &&
				    ELFW(ST_BIND)(objsym->info) == STB_GLOBAL) {
					/* Ignore leading "__ksymtab_" */
					defsym[n_defsym++] = addsym(objsym->name + 10,
								    mod,
								    SYM_DEFINED,
								    ignore_suffix);
				}
				continue;
			}
			/* else */

			if (is_2_2) {
				/*
				 * A 2.2 module _not_ using EXPORT_SYMBOL
				 * It might still want to export symbols,
				 * although strictly speaking it shouldn't...
				 * (Seen in pcmcia)
				 * Architectures with function descriptors must
				 * not do this, it is unsafe.
				 */
#ifndef HAS_FUNCTION_DESCRIPTORS
				if (ELFW(ST_BIND)(objsym->info) == STB_GLOBAL) {
					defsym[n_defsym++] = addsym(objsym->name,
								    mod,
								    SYM_DEFINED,
								    ignore_suffix);
				}
#endif
				continue;
			}
			/* else */

			/* Not undefined or 2.2 ksymtab entry */
			if (objsym->secidx < SHN_LORESERVE
			/*
			 * The test below is removed for 2.0 compatibility
			 * since some 2.0-modules (correctly) hide the
			 * symbols it exports via register_symtab()
			 */
			/* && ELFW(ST_BIND)(objsym->info) == STB_GLOBAL */
			     ) {
				defsym[n_defsym++] = addsym(objsym->name,
							    mod,
							    SYM_DEFINED,
							    ignore_suffix);
			}
		}
	}

	/*
	 *	Finalize the information about a module.
	 */
	mod->defsym.n_syms = n_defsym;
	if (n_defsym > 0) {
		int size = n_defsym * sizeof(SYMBOL *);

		mod->defsym.symtab = (SYMBOL **)xmalloc(size);
		memcpy(mod->defsym.symtab, defsym, size);
	} else
		mod->defsym.symtab = NULL;

	mod->undefs.n_syms = n_undefs;
	if (n_undefs > 0) {
		int size = n_undefs * sizeof(SYMBOL *);

		mod->undefs.symtab = (SYMBOL **) xmalloc(size);
		memcpy(mod->undefs.symtab, undefs, size);
		mod->resolved = 0;
	} else {
		mod->undefs.symtab = NULL;
		mod->resolved = 1;
	}

#ifdef	ARCH_ppc64
	if (!ppc64_process_syms (f)) {
		error("ppc64_process_syms failed\n");
		return(-1);
	}
#endif	/* ARCH_ppc64 */

	/* Do a pseudo relocation to base address 0x1000 (arbitrary).
	 * All undefined symbols are treated as absolute 0.  This builds
	 * enough of a module to allow extraction of internal data such
	 * as device tables.
	 */
	obj_clear_undefineds(f);
	obj_allocate_commons(f);
	m_size = obj_load_size(f);
	if (!obj_relocate(f, 0x1000)) {
		error("depmod obj_relocate failed\n");
		return(-1);
	}
	extract_generic_string(f, mod);
	image = xmalloc(m_size);
	obj_create_image(f, image);
	extract_pci_device_id(f, image, m_size, mod);
	extract_isapnp_device_id(f, image, m_size, mod);
	extract_isapnp_card_id(f, image, m_size, mod);
	extract_usb_device_id(f, image, m_size, mod);
	extract_parport_device_id(f, image, m_size, mod);
	extract_ieee1394_device_id(f, image, m_size, mod);
	extract_pnpbios_device_id(f, image, m_size, mod);
	free(image);

	obj_free(f);
	return 0;
}

/*
 * Add the symbol defined in the kernel, simulating a pseudo module.
 * Create a dummy module entry in the list of modules.
 * This module is used to handle the exported kernel symbols.
 *
 * Load from the currently running kernel
 * OR
 * from a file containing kernel symbols from a different kernel.
 * The file can be either a "System.map" file or a copy of "/proc/ksyms".
 *
 * Return -1 if any error.
 */
static int addksyms(char *file_syms)
{
	FILE *fp;
	MODULE *mod = modules + n_modules++;
	SYMBOL *symtab[MAX_MAP_SYM];
	struct module_symbol *ksym;
	unsigned int so_far = 0;
	int is_mapfile = 0;
	int n_syms = 0;
	int size;
	char line[PATH_MAX];
	char *p;

	mod->name = "-";
	mod->defsym.n_syms = 0;
	mod->defsym.symtab = NULL;
	mod->undefs.n_syms = 0;
	mod->undefs.symtab = NULL;

	/* Fake the _mod_use_count_ symbol provided by insmod */
	/* Dummy */
	symtab[n_syms++] = addsym("mod_use_count_", mod, SYM_DEFINED, 0);
	symtab[n_syms++] = addsym("__this_module", mod, SYM_DEFINED, 0);

	/*
	 * Specification: depmod / kernel syms only
	 * When initialising its symbol table from the kernel
	 * depmod silently discards all symbol from loaded modules.
	 *
	 * This means that depmod may be used at any time to compute
	 * the dependancy table, even if there are modules already
	 * loaded.
	 *
	 * depmod use the kernel system call to obtain the
	 * symbol table, not /proc/ksyms.
	 */

	if (file_syms) {
		if ((fp = fopen(file_syms, "r")) == NULL) {
			error("Can't read %s", file_syms);
			return -1;
		}
		if (!fgets(line, sizeof(line), fp)) {
			fclose(fp);
			error("premature EOF on %s", file_syms);
			return -1;
		}

		p = strtok(line, " \t\n");
		if (!p) {
			fclose(fp);
			error("Illegal format of %s", file_syms);
			return -1;
		}
		if (!isspace(*line))	/* Adressless symbol? */
			p = strtok(NULL, " \t\n");
		/* The second word is either the symbol name or a type */
		if (p && p[0] && !p[1]) { /* System.map */
			is_mapfile = 1;
			p = strtok(NULL, " \t\n");
		} else { /* /proc/ksyms copy */
			if (p && strtok(NULL, " \t\n"))
				p = NULL;
		}

		if (p && strncmp(p, "GPLONLY_", 8) == 0)
			p += 8;
		if (p)
			symtab[n_syms++] = addsym(p, mod, SYM_DEFINED, 0);

		while (fgets(line, sizeof(line), fp)) {
			if (!is_mapfile && strchr(line, '['))
				continue;
			p = strtok(line, " \t\n"); /* Skip first word */
			if (!isspace(*line))	/* Adressless symbol? */
				p = strtok(NULL, " \t\n");
			if (is_mapfile) {
				if (!p || !p[0] || p[1])
					continue;
				p = strtok(NULL, " \t\n");
				/* Sparc has symbols like '.div' that need to be
				 * exported.  They strip the '.' and prefix the
				 * symbol with '__sparc_dot_'.  There is no need
				 * for 'sparc' in the name, other systems with
				 * the same problem should use just '__dot_'.
				 * Support both prefixes, ready for other
				 * systems.
				 * */
				if (!strncmp(p, "__kstrtab___dot_", 15)) {
					p += 15;
					*p = '.';
				}
				else if (!strncmp(p, "__kstrtab___sparc_dot_", 21)) {
					p += 21;
					*p = '.';
				}
				else if (!strncmp(p, "__kstrtab_", 10))
					p += 10;
				else if (!strncmp(p, "__export_priv_", 14)) {
					/* Sparc has some weird exported symbols marked
					 * __export_priv_ instead of the normal __kstrtab_.
					 * Replace the 'v' with '_' and point at the start of
					 * the '__' before the name.  I see no good reason
					 * to use __export_priv_, but for compatibility with
					 * old sparc kernels, it is supported.  Try to remove
					 * __export_priv_ from sparc and remove this code
					 * four releases after the last kernel that uses
					 * __export_priv_.
					 */
					p += 12;
					*p = '_';
				} else
					continue;
			}
			if (strncmp(p, "GPLONLY_", 8) == 0)
				p += 8;
			assert(n_syms < MAX_MAP_SYM);
			symtab[n_syms++] = addsym(p, mod, SYM_DEFINED, 0);
		}
		fclose(fp);
	} else { /* Use the exported symbols from currently running kernel */
		if (!get_kernel_info(K_SYMBOLS))
			return -1;

		for (ksym = ksyms; so_far < nksyms; ++so_far, ksym++) {
			if (strncmp((char *)ksym->name, "GPLONLY_", 8) == 0)
				((char *)ksym->name) += 8;
			assert(n_syms < MAX_MAP_SYM);
			symtab[n_syms++] = addsym((char *)ksym->name, mod, SYM_DEFINED, 0);
		}
	}

	size = n_syms * sizeof(SYMBOL *);
	mod->defsym.symtab = (SYMBOL **)xmalloc(size);
	mod->defsym.n_syms = n_syms;
	memcpy(mod->defsym.symtab, symtab, size);

	return 0;
}

/* Open a generated file for output */
static FILE *gen_file_open(const struct gen_files *gf)
{
	FILE *f = fopen(gf->name, "w");
	if (!f) {
		error("Can't open %s for writing", gf->name);
		exit(-1);
	}
	return(f);
}

static
char *shortname(const char *name)
{
	char *name2 = xstrdup(name);
	char *s = strrchr(name2, '/');
	int l;
	if (s) {
		++s;
		l = strlen(s);
		if (l > 3 && strcmp(s+l-3, ".gz") == 0) {
			*(s+l-3) = '\0';
			l -= 3;
		}
		if (l > 2 && strcmp(s+l-2, ".o") == 0) {
			*(s+l-2) = '\0';
			l -= 2;
		} else if (l > 4 && strcmp(s+l-4, ".mod") == 0) {
			*(s+l-4) = '\0';
			l -= 4;
		}
	}
	else
		s = name2;	/* No '/' in name, strange */
	return(s);
}

/*
 *	Format the dependancy list of a module into a simple makefile.
 *	Print the dependancies in the depfile (or stdout if nflag is true).
 *	Print the pcimap in the pcimapfile (or stdout if nflag is true).
 *	Print the isapnpmap in the isapnpmapfile (or stdout if nflag is true).
 *	Print the usbmap in the usbmapfile (or stdout if nflag is true).
 *
 *	Documented limits which utilities can rely on.
 *	  No field name on a header line will be longer than 20 characters.  The
 *	  data in a field can be longer than 20 characters but the name will not.
 *	  No single line in a generated file will be longer than PATH_MAX-1
 *	  characters.
 */

static int prtdepend(char *base_dir, int nflag)
{
	FILE *dep = stdout;
	FILE *generic_string = stdout;
	FILE *pcimap = stdout;
	FILE *isapnpmap = stdout;
	FILE *usbmap = stdout;
	FILE *parportmap = stdout;
	FILE *ieee1394map = stdout;
	FILE *pnpbiosmap = stdout;
	MODULE **tbdep;
	MODULE *ptmod;
	int i;
	int ret = 0;
	int skipchars;	/* For depmod -a in image of a tree */

	if (!nflag) {
		dep = gen_file_open(gen_file+GEN_DEPFILE);
		generic_string = gen_file_open(gen_file+GEN_GENERIC_STRINGFILE);
		pcimap = gen_file_open(gen_file+GEN_PCIMAPFILE);
		isapnpmap = gen_file_open(gen_file+GEN_ISAPNPMAPFILE);
		usbmap = gen_file_open(gen_file+GEN_USBMAPFILE);
		parportmap = gen_file_open(gen_file+GEN_PARPORTMAPFILE);
		ieee1394map = gen_file_open(gen_file+GEN_IEEE1394MAPFILE);
		pnpbiosmap = gen_file_open(gen_file+GEN_PNPBIOSMAPFILE);
	}

	skipchars = strlen(base_dir);
	tbdep = (MODULE **)alloca(sizeof(MODULE) * n_modules);

	ptmod = modules;
	for (i = 0; i < n_modules; i++, ptmod++) {
		SYMBOL **undefs = ptmod->undefs.symtab;
		int n_undefs = ptmod->undefs.n_syms;
		int nbdepmod = 0;
		int nberr = 0;
		int e;
		int m;

		/* Don't print a dependency list for the _kernel_ ... */
		if (strcmp(ptmod->name, "-") == 0)
			continue;

		/* Look for unresolved symbols in this module */
		for (e = 0; e < n_undefs; e++, undefs++) {
			MODULE *mod = (*undefs)->module;

			if ((*undefs)->status == SYM_RESOLVED) {
				/* Resolved by self or exported kernel symbol */
				if (strcmp(mod->name, ptmod->name) == 0 ||
				    strcmp(mod->name, "-") == 0)
					continue;

				/* No duplicate dependencies, please */
				for (m = 0; m < nbdepmod; m++) {
					if (tbdep[m] == mod)
						break;
				}
				if (m == nbdepmod)
					tbdep[nbdepmod++] = mod;
			} else {
				/* Kludge to preserve old depmod behaviour without -u.
				 * 2.4.13 change to keep going had the unwanted side
				 * effect of always treating unresolved symbols as an
				 * error.  Use the error() routine but do not count
				 * any errors.  Remove in 2.5.
				 */
				int save_errors = errors;
				if (!quiet && nberr == 0)
					error("*** Unresolved symbols in %s",
					      ptmod->name);
				if (!quiet && showerror)
						error("\t%s", (*undefs)->name);
				nberr++;
				if (flag_unresolved_error)
					ret = 1;
				errors = save_errors;
			}
		}
		verbose("%s\n", ptmod->name + skipchars);

		fprintf(dep, "%s:", ptmod->name + skipchars);
		for (m = 0; m < nbdepmod; m++) {
			if (m != 0 /*&& (m & 3) == 0*/)
				fprintf(dep, " \\\n");
			fprintf(dep, "\t%s", tbdep[m]->name + skipchars);
		}
		fprintf(dep, "\n\n");
	}

	ptmod = modules;
	fprintf(generic_string, "# module             id=string\n");
	for (i = 0; i < n_modules; i++, ptmod++) {
		int j;
		char **pstr = ptmod->generic_string;
		if (!ptmod->n_generic_string)
			continue;
		for (j = 0; j < ptmod->n_generic_string; j++, ++pstr) {
			int l, l1;
			fprintf(generic_string, "%-20s ", shortname(ptmod->name));
			l = PATH_MAX-1;
			l1 = strlen(shortname(ptmod->name));
			if (l1 < 20)
				l1 = 20;
			l -= (l1+1);
			fprintf(generic_string, "%.*s\n", l, *pstr);
		}
	}

	ptmod = modules;
	fprintf(pcimap, "# pci module         vendor     device     subvendor  subdevice  class      class_mask driver_data\n");
	for (i = 0; i < n_modules; i++, ptmod++) {
		int j;
		struct pci_device_id *pci_device = ptmod->pci_device;
		if (!ptmod->n_pci_device)
			continue;
		for (j = 0; j < ptmod->n_pci_device; j++, pci_device++) {
			fprintf(pcimap, "%-20s 0x%0*x 0x%0*x 0x%0*x 0x%0*x 0x%0*x 0x%0*x 0x%0*" tgt_long_fmt "x\n",
				shortname(ptmod->name),
				(int)(2*sizeof(pci_device->vendor)), pci_device->vendor,
				(int)(2*sizeof(pci_device->device)), pci_device->device,
				(int)(2*sizeof(pci_device->subvendor)), pci_device->subvendor,
				(int)(2*sizeof(pci_device->subdevice)), pci_device->subdevice,
				(int)(2*sizeof(pci_device->class)), pci_device->class,
				(int)(2*sizeof(pci_device->class_mask)), pci_device->class_mask,
				(int)(2*sizeof(pci_device->driver_data)), pci_device->driver_data);
		}
	}

	ptmod = modules;
	fprintf(isapnpmap, "# isapnp module      cardvendor carddevice driver_data vendor     function   ...\n");
	for (i = 0; i < n_modules; i++, ptmod++) {
		int j, l;
		struct isapnp_device_id *isapnp_device = ptmod->isapnp_device;
		struct isapnp_card_id *isapnp_card = ptmod->isapnp_card;
		if (!ptmod->n_isapnp_device && !ptmod->n_isapnp_card)
			continue;
		for (j = 0; j < ptmod->n_isapnp_device; j++, isapnp_device++) {
			fprintf(isapnpmap, "%-20s 0x%0*x     0x%0*x     0x%0*" tgt_long_fmt "x  0x%0*x     0x%0*x\n",
				shortname(ptmod->name),
				(int)(2*sizeof(isapnp_device->card_vendor)), isapnp_device->card_vendor,
				(int)(2*sizeof(isapnp_device->card_device)), isapnp_device->card_device,
				(int)(2*sizeof(isapnp_device->driver_data)), isapnp_device->driver_data,
				(int)(2*sizeof(isapnp_device->vendor)), isapnp_device->vendor,
				(int)(2*sizeof(isapnp_device->function)), isapnp_device->function);
		}
		for (j = 0; j < ptmod->n_isapnp_card; j++, isapnp_card++) {
			fprintf(isapnpmap, "%-20s 0x%0*x     0x%0*x     0x%0*" tgt_long_fmt "x ",
				shortname(ptmod->name),
				(int)(2*sizeof(isapnp_card->card_vendor)), isapnp_card->card_vendor,
				(int)(2*sizeof(isapnp_card->card_device)), isapnp_card->card_device,
				(int)(2*sizeof(isapnp_card->driver_data)), isapnp_card->driver_data);
			for (l = 0; l < ISAPNP_CARD_DEVS; ++l) {
				if (isapnp_card->devs[l].vendor) {
					fprintf(isapnpmap, " 0x%0*x     0x%0*x    ",
						(int)(2*sizeof(isapnp_card->devs[l].vendor)), isapnp_card->devs[l].vendor,
						(int)(2*sizeof(isapnp_card->devs[l].function)), isapnp_card->devs[l].function);
				}
			}
			fprintf(isapnpmap, "\n");
		}
	}

	ptmod = modules;
	fprintf(usbmap, "# usb module         ");
	/* Requires all users to be on kernel 2.4.0 or later */
	fprintf(usbmap, "match_flags ");
	fprintf(usbmap, "idVendor idProduct bcdDevice_lo bcdDevice_hi"
		" bDeviceClass bDeviceSubClass bDeviceProtocol bInterfaceClass bInterfaceSubClass"
		" bInterfaceProtocol driver_info\n");
	for (i = 0; i < n_modules; i++, ptmod++) {
		int j;
		struct usb_device_id *usb_device = ptmod->usb_device;
		if (!ptmod->n_usb_device)
			continue;
		for (j = 0; j < ptmod->n_usb_device; j++, usb_device++) {
			fprintf(usbmap, "%-20s ", shortname(ptmod->name));
			/* Requires all users to be on kernel 2.4.0 or later */
			fprintf(usbmap, "0x%0*x      ",
				(int)(2*sizeof(usb_device->match_flags)), usb_device->match_flags);
			fprintf(usbmap, "0x%0*x   0x%0*x    0x%0*x       0x%0*x       "
				"0x%0*x         0x%0*x            0x%0*x            0x%0*x            0x%0*x               "
				"0x%0*x               0x%0*" tgt_long_fmt "x\n",
				(int)(2*sizeof(usb_device->idVendor)), usb_device->idVendor,
				(int)(2*sizeof(usb_device->idProduct)), usb_device->idProduct,
				(int)(2*sizeof(usb_device->bcdDevice_lo)), usb_device->bcdDevice_lo,
				(int)(2*sizeof(usb_device->bcdDevice_hi)), usb_device->bcdDevice_hi,
				(int)(2*sizeof(usb_device->bDeviceClass)), usb_device->bDeviceClass,
				(int)(2*sizeof(usb_device->bDeviceSubClass)), usb_device->bDeviceSubClass,
				(int)(2*sizeof(usb_device->bDeviceProtocol)), usb_device->bDeviceProtocol,
				(int)(2*sizeof(usb_device->bInterfaceClass)), usb_device->bInterfaceClass,
				(int)(2*sizeof(usb_device->bInterfaceSubClass)), usb_device->bInterfaceSubClass,
				(int)(2*sizeof(usb_device->bInterfaceProtocol)), usb_device->bInterfaceProtocol,
				(int)(2*sizeof(usb_device->driver_info)), usb_device->driver_info);
		}
	}

	ptmod = modules;
	fprintf(parportmap, "# module             pattern\n");
	for (i = 0; i < n_modules; i++, ptmod++) {
		int j;
		struct parport_device_id *parport_device = ptmod->parport_device;
		if (!ptmod->n_parport_device)
			continue;
		for (j = 0; j < ptmod->n_parport_device; j++, parport_device++) {
			fprintf(parportmap, "%-20s %s\n",
				shortname(ptmod->name),
				(char *)obj_addr_to_native_ptr(ptmod->parport_device[j].pattern));
		}
	}

	ptmod = modules;
	fprintf(ieee1394map, "# ieee1394 module    match_flags vendor_id model_id specifier_id version\n");
	for (i = 0; i < n_modules; i++, ptmod++) {
		int j;
		struct ieee1394_device_id *ieee1394_device = ptmod->ieee1394_device;
		if (!ptmod->n_ieee1394_device)
			continue;
		for (j = 0; j < ptmod->n_ieee1394_device; j++, ieee1394_device++) {
			fprintf(ieee1394map, "%-20s 0x%08x  0x%06x  0x%06x 0x%06x     0x%06x\n",
				shortname(ptmod->name),
				ieee1394_device->match_flags,
				ieee1394_device->vendor_id,
				ieee1394_device->model_id,
				ieee1394_device->specifier_id,
				ieee1394_device->version);
		}
	}

	ptmod = modules;
	fprintf(pnpbiosmap, "# module             id\n");
	for (i = 0; i < n_modules; i++, ptmod++) {
		int j;
		struct pnpbios_device_id *pnpbios_device = ptmod->pnpbios_device;
		if (!ptmod->n_pnpbios_device)
			continue;
		for (j = 0; j < ptmod->n_pnpbios_device; j++, pnpbios_device++) {
			fprintf(pnpbiosmap, "%-20s %s\n",
				shortname(ptmod->name),
				(char *)pnpbios_device->id);
		}
	}

	if (generic_string != stdout)
		fclose(generic_string);
	if (pcimap != stdout)
		fclose(pcimap);
	if (isapnpmap != stdout)
		fclose(isapnpmap);
	if (usbmap != stdout)
		fclose(usbmap);
	if (parportmap != stdout)
		fclose(parportmap);
	if (ieee1394map != stdout)
		fclose(ieee1394map);
	if (pnpbiosmap != stdout)
		fclose(pnpbiosmap);
	/* Close depfile last, it's timestamp is critical */
	if (dep != stdout)
		fclose(dep);
	return ret;
}

/* For common 3264, only compile the usage message once, in the 64 bit version */
#if defined(COMMON_3264) && defined(ONLY_32)
extern void depmod_usage(void);         /* Use the copy in the 64 bit version */
#else   /* Common 64 bit version or any non common code - compile usage routine */
void depmod_usage(void)
{
	fprintf(stderr,
	"depmod " MODUTILS_VERSION "\n"
	"depmod -[aA] [-n -e -v -q -V -r -u]\n"
	"      [-C configfile] [-F kernelsyms] [-b basedirectory] [forced_version]\n"
	"depmod [-n -e -v -q -r -u] [-F kernelsyms] module1.o module2.o ...\n"
	"If no arguments (except options) are given, \"depmod -a\" is assumed\n"
	"\n"
	"depmod will output a dependancy list suitable for the modprobe utility.\n"
	"depmod -a will find the list of modules to probe from the file\n"
	ETC_MODULES_CONF ". It will output the result into the depfile specified\n"
	"in this configuration file\n"
	"\n"
	"depmod -A is the same as depmod -a, but will first compare the timestamps\n"
	"of the files involved to see if the depfile needs updating.\n"
	"\n"
	"Normally depmod operates silently, reporting only the list of modules that\n"
	"won't load properly (missing symbols).\n"
	"\n"
	"Options:\n"
	"\t-a, --all            Probe modules listed in " ETC_MODULES_CONF "\n"
	"\t-A                   Like -a, compares timestamps first\n"
	"\t-q, --quiet          Don't report missing symbols\n"
	"\t-e, --errsyms        List unresolved symbols for the given module\n"
	"\t-s, --syslog         Report errors using syslog\n"
	"\t-v, --verbose        Print all visited modules\n"
	"\t-n, --show           Write the dependency file on stdout only\n"
	"\t-r, --root           Allow root to allow modules not owned by root\n"
	"\t-V, --version        Print the release version\n"
	"\t-u, --unresolved-error Set an error return code for unresolved symbols\n"
	"\t-h, --help           Print this usage message\n"
	"\n"
	"The following options are useful for people managing distributions:\n"
	"\t-b basedirectory\n"
	"\t    --basedir basedirectory    Use an image of a module tree.\n"
	"\t-C configfile\n"
	"\t    --config configfile        Use the file instead of\n"
	"\t                               " ETC_MODULES_CONF ".\n"
	"\t-F kernelsyms\n"
	"\t    --filesyms kernelsyms      Use the file instead of the\n"
	"\t                               current kernel symbols.\n"
	);
}
#endif  /* defined(COMMON_3264) && defined(ONLY_32) */

#if defined(COMMON_3264) && defined(ONLY_32)
#define DEPMOD_MAIN depmod_main_32	/* 32 bit version */
#elif defined(COMMON_3264) && defined(ONLY_64)
#define DEPMOD_MAIN depmod_main_64	/* 64 bit version */
#else
#define DEPMOD_MAIN depmod_main		/* Not common 3264 code */
#endif

/* For common 3264 code, add an overall depmod_main, in the 64 bit version. */
#if defined(COMMON_3264) && defined(ONLY_64)
int depmod_main(int argc, char **argv)
{
	if (arch64())
		return depmod_main_64(argc, argv);
	else
		return depmod_main_32(argc, argv);
}
#endif  /* defined(COMMON_3264) && defined(ONLY_64) */

int DEPMOD_MAIN(int argc, char **argv)
{
	int ret = -1;
	int stdmode = 0;
	int err = 0;
	int nflag = 0;
	int o;
	char *conf_file = NULL;
	char *file_syms = NULL;
	char *base_dir = "";
	int ignore_suffix = 0;	/* Ignore genksyms suffix on resolve? */

	struct option long_opts[] = {
		{"all", 0, 0, 'a'},
		{"basedir", 1, 0, 'b'},
		{"config", 1, 0, 'C'},
		{"errsyms", 0, 0, 'e'},
		{"filesyms", 1, 0, 'F'},
		{"help", 0, 0, 'h'},
		{"show", 0, 0, 'n'},
		{"quick", 0, 0, 'A'},
		{"quiet", 0, 0, 'q'},
		{"syslog", 0, 0, 's'},
		{"verbose", 0, 0, 'v'},
		{"version", 0, 0, 'V'},
		{"root", 0, 0, 'r'},
		{"unresolved-error", 0, 0, 'u'},
		{0, 0, 0, 0 }
	};

	error_file = "depmod";

	while ((o = getopt_long(argc, argv, "aAb:C:eF:hnqsvVru",
				&long_opts[0], NULL)) != EOF) {
		switch (o) {
		case 'A':
		case 'a':
			quick = o == 'A';
			stdmode = 1;	/* Probe standard directory */
			break;		/* using the config file */

		case 'e':
			showerror = 1;
			break;

		case 'b':
			base_dir = optarg;
			break;

		case '?':
		case 'h':
			depmod_usage();
			return 0;
			break;

		case 'C':
			conf_file = optarg;
			break;

		case 'F':
			file_syms = optarg;
			break;

		case 'n':
			nflag = 1;
			break;

		case 'q':
			quiet = 1;
			break;

		case 's':
			setsyslog("depmod");
			break;

		case 'v':
			flag_verbose = 1;
			break;

		case 'V':
			printf("depmod version %s\n", MODUTILS_VERSION);
			break;

		case 'r':
			root_check_off = 1;
			break;

		case 'u':
			flag_unresolved_error = 1;
			break;

		default:
			err = 1;
			break;
		}
	}

	if (err) {
		error("Aborting");
		return -1;
	}
	/* else */
	argc -= optind;
	argv += optind;

	ignore_suffix = file_syms != NULL;

	if (stdmode || argc == 0) {
		/* option -a is the default without arguments */
		if (argc > 0) {
			if (config_read(0, *argv, base_dir, conf_file) == -1) {
				error("%s does not exist", gen_file[GEN_DEPFILE].name);
				return -1;
			}
		} else if (config_read(0, NULL, base_dir, conf_file) == -1) {
			return -1;
		}

		if ((ret = addksyms(file_syms)) != -1) {
			int i;
			GLOB_LIST *g = config_lstmod(NULL, NULL, 0);
			for (i = 0; g && i < g->pathc; i++)
				loadobj(g->pathv[i], ignore_suffix);
			resolve();
			ret = prtdepend(base_dir, nflag) || ret;
		}
	} else {
		/* not stdmode */
		if ((ret = addksyms(file_syms)) != -1) {
			for (; argc > 0 && ret != -1; ++argv, --argc)
				loadobj(*argv, ignore_suffix);
			resolve();
			ret = prtdepend(base_dir, 1) || ret;
		}
	}

	return ret;
}

/* For common 3264 code, only compile main in the 64 bit version. */
#if defined(COMMON_3264) && defined(ONLY_32)
/* Use the main in the 64 bit version */
#else
int main(int argc, char **argv)
{
	return depmod_main(argc, argv) || errors;
}
#endif	/* defined(COMMON_3264) && defined(ONLY_32) */
