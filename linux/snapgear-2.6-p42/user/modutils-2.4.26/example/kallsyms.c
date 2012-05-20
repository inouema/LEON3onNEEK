/* An example of using kallsyms data in a kernel debugger.

   Copyright 2000 Keith Owens <kaos@ocs.com.au> April 2000

   This file is part of the Linux modutils.

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 2 of the License, or (at your
   option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
  */

/*
   This code uses the list of all kernel and module symbols to :-

   * Find any non-stack symbol in a kernel or module.  Symbols do
     not have to be exported for debugging.

   * Convert an address to the module (or kernel) that owns it, the
     section it is in and the nearest symbol.  This finds all non-stack
     symbols, not just exported ones.

   You need modutils >= 2.3.11 and a kernel with the kallsyms patch
   which was compiled with CONFIG_KALLSYMS.
 */

#include <linux/elf.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/kallsyms.h>

/* These external symbols are only available on kernels compiled with
 * CONFIG_KALLSYMS.
 */

extern const char __start___kallsyms[];
extern const char __stop___kallsyms[];

static struct module *local_module_list;

static void get_module_list(void)
{
	const struct kallsyms_header	*ka_hdr;
	const struct kallsyms_section	*ka_sec;
	const struct kallsyms_symbol	*ka_sym;
	const char			*ka_str;
	int i;
	const char *p;

	if (__start___kallsyms >= __stop___kallsyms)
		return;
	ka_hdr = (struct kallsyms_header *)__start___kallsyms;
	ka_sec = (struct kallsyms_section *)
		((char *)(ka_hdr) + ka_hdr->section_off);
	ka_sym = (struct kallsyms_symbol *)
		((char *)(ka_hdr) + ka_hdr->symbol_off);
	ka_str =
		((char *)(ka_hdr) + ka_hdr->string_off);

	for (i = 0; i < ka_hdr->symbols; kallsyms_next_sym(ka_hdr, ka_sym), ++i) {
		p = ka_str + ka_sym->name_off;
		if (strcmp(p, "module_list") == 0) {
			if (ka_sym->symbol_addr)
				local_module_list = *((struct module **)(ka_sym->symbol_addr));
			break;
		}
	}
}

static void __inline__ do_first_time(void)
{
	static int first_time = 1;
	if (first_time)
		get_module_list();
	first_time = 0;
}

/* A symbol can appear in more than one module.  A token is used to
 * restart the scan at the next module, set the token to 0 for the
 * first scan of each symbol.
 */

int kallsyms_symbol_to_address(
	const char	 *name,		/* Name to lookup */
	unsigned long 	 *token,	/* Which module to start at */
	const char	**mod_name,	/* Set to module name */
	unsigned long 	 *mod_start,	/* Set to start address of module */
	unsigned long 	 *mod_end,	/* Set to end address of module */
	const char	**sec_name,	/* Set to section name */
	unsigned long 	 *sec_start,	/* Set to start address of section */
	unsigned long 	 *sec_end,	/* Set to end address of section */
	const char	**sym_name,	/* Set to full symbol name */
	unsigned long 	 *sym_start,	/* Set to start address of symbol */
	unsigned long 	 *sym_end	/* Set to end address of symbol */
	)
{
	const struct kallsyms_header	*ka_hdr = NULL;	/* stupid gcc */
	const struct kallsyms_section	*ka_sec;
	const struct kallsyms_symbol	*ka_sym = NULL;
	const char			*ka_str = NULL;
	const struct module *m;
	int i = 0, l;
	const char *p, *pt_R;
	char *p2;

	do_first_time();

	/* Restart? */
	m = local_module_list;
	if (token && *token) {
		for (; m; m = m->next)
			if ((unsigned long)m == *token)
				break;
		if (m)
			m = m->next;
	}

	for (; m; m = m->next) {
		if (!mod_member_present(m, kallsyms_start) ||
		    !mod_member_present(m, kallsyms_end) ||
		    m->kallsyms_start >= m->kallsyms_end)
			continue;
		ka_hdr = (struct kallsyms_header *)m->kallsyms_start;
		ka_sym = (struct kallsyms_symbol *)
			((char *)(ka_hdr) + ka_hdr->symbol_off);
		ka_str =
			((char *)(ka_hdr) + ka_hdr->string_off);
		for (i = 0; i < ka_hdr->symbols; ++i, kallsyms_next_sym(ka_hdr, ka_sym)) {
			p = ka_str + ka_sym->name_off;
			if (strcmp(p, name) == 0)
				break;
			/* Unversioned requests match versioned names */
			if (!(pt_R = strstr(p, "_R")))
				continue;
			l = strlen(pt_R);
			if (l < 10)
				continue;	/* Not _R.*xxxxxxxx */
			(void)simple_strtoul(pt_R+l-8, &p2, 16);
			if (*p2)
				continue;	/* Not _R.*xxxxxxxx */
			if (strncmp(p, name, pt_R-p) == 0)
				break;	/* Match with version */
		}
		if (i < ka_hdr->symbols)
			break;
	}

	if (token)
		*token = (unsigned long)m;
	if (!m)
		return(0);	/* not found */

	ka_sec = (const struct kallsyms_section *)
		((char *)ka_hdr + ka_hdr->section_off + ka_sym->section_off);
	*mod_name = *(m->name) ? m->name : "kernel";
	*mod_start = ka_hdr->start;
	*mod_end = ka_hdr->end;
	*sec_name = ka_sec->name_off + ka_str;
	*sec_start = ka_sec->start;
	*sec_end = ka_sec->start + ka_sec->size;
	*sym_name = ka_sym->name_off + ka_str;
	*sym_start = ka_sym->symbol_addr;
	if (i < ka_hdr->symbols-1) {
		const struct kallsyms_symbol *ka_symn = ka_sym;
		kallsyms_next_sym(ka_hdr, ka_symn);
		*sym_end = ka_symn->symbol_addr;
	}
	else
		*sym_end = *sec_end;
	return(1);
}

int kallsyms_address_to_symbol(
	unsigned long	  address,	/* Address to lookup */
	const char	**mod_name,	/* Set to module name */
	unsigned long 	 *mod_start,	/* Set to start address of module */
	unsigned long 	 *mod_end,	/* Set to end address of module */
	const char	**sec_name,	/* Set to section name */
	unsigned long 	 *sec_start,	/* Set to start address of section */
	unsigned long 	 *sec_end,	/* Set to end address of section */
	const char	**sym_name,	/* Set to full symbol name */
	unsigned long 	 *sym_start,	/* Set to start address of symbol */
	unsigned long 	 *sym_end	/* Set to end address of symbol */
	)
{
	const struct kallsyms_header	*ka_hdr = NULL;	/* stupid gcc */
	const struct kallsyms_section	*ka_sec = NULL;
	const struct kallsyms_symbol	*ka_sym;
	const char			*ka_str;
	const struct module *m;
	int i;
	unsigned long end;

	do_first_time();

	for (m = local_module_list; m; m = m->next) {
		if (!mod_member_present(m, kallsyms_start) ||
		    !mod_member_present(m, kallsyms_end) ||
		    m->kallsyms_start >= m->kallsyms_end)
			continue;
		ka_hdr = (struct kallsyms_header *)m->kallsyms_start;
		ka_sec = (const struct kallsyms_section *)
			((char *)ka_hdr + ka_hdr->section_off);
		/* Is the address in any section in this module? */
		for (i = 0; i < ka_hdr->sections; ++i, kallsyms_next_sec(ka_hdr, ka_sec)) {
			if (ka_sec->start <= address &&
			    (ka_sec->start + ka_sec->size) > address)
				break;
		}
		if (i < ka_hdr->sections)
			break;	/* Found a matching section */
	}

	if (!m)
		return(0);	/* not found */

	ka_sym = (struct kallsyms_symbol *)
		((char *)(ka_hdr) + ka_hdr->symbol_off);
	ka_str =
		((char *)(ka_hdr) + ka_hdr->string_off);
	*mod_name = *(m->name) ? m->name : "kernel";
	*mod_start = ka_hdr->start;
	*mod_end = ka_hdr->end;
	*sec_name = ka_sec->name_off + ka_str;
	*sec_start = ka_sec->start;
	*sec_end = ka_sec->start + ka_sec->size;
	*sym_name = *sec_name;		/* In case we find no matching symbol */
	*sym_start = *sec_start;
	*sym_end = *sec_end;

	for (i = 0; i < ka_hdr->symbols; ++i, kallsyms_next_sym(ka_hdr, ka_sym)) {
		if (ka_sym->symbol_addr > address)
			continue;
		if (i < ka_hdr->symbols-1) {
			const struct kallsyms_symbol *ka_symn = ka_sym;
			kallsyms_next_sym(ka_hdr, ka_symn);
			end = ka_symn->symbol_addr;
		}
		else
			end = *sec_end;
		if (end <= address)
			continue;
		if ((char *)ka_hdr + ka_hdr->section_off + ka_sym->section_off
		    != (char *)ka_sec)
			continue;	/* wrong section */
		*sym_name = ka_str + ka_sym->name_off;
		*sym_start = ka_sym->symbol_addr;
		*sym_end = end;
		break;
	}
	return(1);
}
