#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "depmod.h"
#include "tables.h"

/* Turn /lib/modules/2.5.49/kernel/foo.ko(.gz) => foo */
static void make_shortname(char *dest, const char *src)
{
	char *ext;
	const char *slash;

	slash = strrchr(src, '/') ?: src-1;
	strcpy(dest, slash + 1);
	ext = strchr(dest, '.');
	if (ext)
		*ext = '\0';
}

/* We set driver_data to zero */
static void output_pci_entry(struct pci_device_id *pci, char *name, FILE *out)
{
	fprintf(out,
		"%-20s 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x0\n",
		name,
		pci->vendor,
		pci->device,
		pci->subvendor,
		pci->subdevice,
		pci->class,
		pci->class_mask);
}

void output_pci_table(struct module *modules, FILE *out)
{
	struct module *i;

	fprintf(out, "# pci module         vendor     device     subvendor"
		"  subdevice  class      class_mask driver_data\n");

	for (i = modules; i; i = i->next) {
		struct pci_device_id *e;
		char shortname[strlen(i->pathname) + 1];

		if (!i->pci_table)
			continue;

		make_shortname(shortname, i->pathname);
		for (e = i->pci_table; e->vendor; e = (void *)e + i->pci_size)
			output_pci_entry(e, shortname, out);
	}
}

/* We set driver_info to zero */
static void output_usb_entry(struct usb_device_id *usb, char *name, FILE *out)
{
	fprintf(out, "%-20s 0x%04x      0x%04x   0x%04x    0x%04x"
		"       0x%04x       0x%02x         0x%02x"
		"            0x%02x            0x%02x"
		"            0x%02x               0x%02x"
		"               0x0\n",
		name,
		usb->match_flags,
		usb->idVendor,
		usb->idProduct,
		usb->bcdDevice_lo,
		usb->bcdDevice_hi,
		usb->bDeviceClass,
		usb->bDeviceSubClass,
		usb->bDeviceProtocol,
		usb->bInterfaceClass,
		usb->bInterfaceSubClass,
		usb->bInterfaceProtocol);
}

void output_usb_table(struct module *modules, FILE *out)
{
	struct module *i;

	fprintf(out, "# usb module         ");
	/* Requires all users to be on kernel 2.4.0 or later */
	fprintf(out, "match_flags ");
	fprintf(out, "idVendor idProduct bcdDevice_lo bcdDevice_hi"
		" bDeviceClass bDeviceSubClass bDeviceProtocol"
		" bInterfaceClass bInterfaceSubClass"
		" bInterfaceProtocol driver_info\n");

	for (i = modules; i; i = i->next) {
		struct usb_device_id *e;
		char shortname[strlen(i->pathname) + 1];

		if (!i->usb_table)
			continue;

		make_shortname(shortname, i->pathname);
		for (e = i->usb_table; 
		     e->idVendor || e->bDeviceClass || e->bInterfaceClass;
		     e = (void *)e + i->usb_size)
			output_usb_entry(e, shortname, out);
	}
}

static void output_ieee1394_entry(struct ieee1394_device_id *fw, char *name, FILE *out)
{
	fprintf(out, "%-20s 0x%08x  0x%06x  0x%06x 0x%06x     0x%06x\n",
		name, fw->match_flags, fw->vendor_id, fw->model_id,
		fw->specifier_id, fw->version);
}

void output_ieee1394_table(struct module *modules, FILE *out)
{
	struct module *i;

	fprintf(out, "# ieee1394 module    ");
	fprintf(out, "match_flags vendor_id model_id specifier_id version\n");

	for (i = modules; i; i = i->next) {
		struct ieee1394_device_id *fw;
		char shortname[strlen(i->pathname) + 1];

		if (!i->ieee1394_table)
			continue;

		make_shortname(shortname, i->pathname);
		for (fw = i->ieee1394_table; fw->match_flags;
		     fw = (void *) fw + i->ieee1394_size)
			output_ieee1394_entry(fw, shortname, out);
	}
}


/* We set driver_data to zero */
static void output_ccw_entry(struct ccw_device_id *ccw, char *name, FILE *out)
{
	fprintf(out, "%-20s 0x%04x      0x%04x  0x%02x      0x%04x  0x%02x\n",
		name, ccw->match_flags,
		ccw->cu_type,  ccw->cu_model,
		ccw->dev_type, ccw->dev_model);
}

void output_ccw_table(struct module *modules, FILE *out)
{
	struct module *i;

	fprintf(out, "# ccw module         ");
	fprintf(out, "match_flags cu_type cu_model dev_type dev_model\n");

	for (i = modules; i; i = i->next) {
		struct ccw_device_id *e;
		char shortname[strlen(i->pathname) + 1];

		if (!i->ccw_table)
			continue;

		make_shortname(shortname, i->pathname);
		for (e = i->ccw_table;
		     e->cu_type || e->cu_model || e->dev_type || e->dev_model;
		     e = (void *) e + i->ccw_size)
			output_ccw_entry(e, shortname, out);
	}
}

#define ISAPNP_VENDOR(a,b,c)	(((((a)-'A'+1)&0x3f)<<2)|\
				((((b)-'A'+1)&0x18)>>3)|((((b)-'A'+1)&7)<<13)|\
				((((c)-'A'+1)&0x1f)<<8))
#define ISAPNP_DEVICE(x)	((((x)&0xf000)>>8)|\
				 (((x)&0x0f00)>>8)|\
				 (((x)&0x00f0)<<8)|\
				 (((x)&0x000f)<<8))

static void put_isapnp_id(FILE *out, const char *id)
{
	unsigned short vendor, device;

	vendor = ISAPNP_VENDOR(id[0], id[1], id[2]);
	device = (unsigned short)strtol(&id[3], NULL, 16);
	device = ISAPNP_DEVICE(device);
	fprintf(out, " 0x%04x     0x%04x    ", vendor, device);
}

void output_isapnp_table(struct module *modules, FILE *out)
{
	struct module *i;

	fprintf(out, "# isapnp module      ");
	fprintf(out, "cardvendor carddevice driver_data vendor     function   ...\n");

	for (i = modules; i; i = i->next) {
		char shortname[strlen(i->pathname) + 1];

		if (i->pnp_table) {
			struct pnp_device_id *id;
			make_shortname(shortname, i->pathname);
			for (id = i->pnp_table;
			     id->id[0];
			     id = (void *)id + i->pnp_size) {
				fprintf(out, "%-20s", shortname);
				fprintf(out, " 0xffff     0xffff    ");
				fprintf(out, " 0x00000000 "); /* driver_data */
				put_isapnp_id(out, id->id);
				fprintf(out, "\n");
			}
		}
		if (i->pnp_card_table) {
			void *id;
			make_shortname(shortname, i->pathname);
			for (id = i->pnp_card_table;
			     ((char *)id)[0];
			     id += i->pnp_card_size) {
				int idx;
				struct pnp_card_devid *devid
					= id + i->pnp_card_offset;

				fprintf(out, "%-20s", shortname);
				put_isapnp_id(out, id);
				fprintf(out, " 0x00000000 "); /* driver_data */
				for (idx = 0; idx < 8; idx++) {
					if (!devid->devid[idx][0])
						break;
					put_isapnp_id(out, devid->devid[idx]);
				}
				fprintf(out, "\n");
			}
		}
	}
}

#define MATCH_bustype   1
#define MATCH_vendor    2
#define MATCH_product   4
#define MATCH_version   8

#define MATCH_evbit     0x010
#define MATCH_keybit    0x020
#define MATCH_relbit    0x040
#define MATCH_absbit    0x080
#define MATCH_mscbit    0x100
#define MATCH_ledbit    0x200
#define MATCH_sndbit    0x400
#define MATCH_ffbit     0x800

#define MATCH(x) (input->match_flags & MATCH_ ## x)
#define PRINT_SCALAR(n) fprintf(out, "  0x%lx", MATCH(n) ? input->n : 0l)
#define PRINT_ARRAY(n) do {						    \
	fprintf(out, "  ");						    \
	if (MATCH(n))							    \
		output_input_bits(out, (long *)input->n, sizeof(input->n)); \
	else								    \
		fprintf(out, "%d", 0);					    \
	} while (0)

static void output_input_bits(FILE *out, long *bits, int size)
{
	int i, j;

	size /= sizeof(long);
	for (i = size - 1; i >= 0; i--)
		 if (bits[i])
			 break;
	if (i < 0)
		i = 0;
	fprintf(out, "%lx", bits[i]);
	for (j = i - 1; j >= 0; j--)
		fprintf(out, ":%lx", bits[j]);
}

/* Formats are too different to */
static void output_input_entry_32(struct input_device_id_32 *input,
				  char *name, FILE *out)
{
	fprintf(out, "%-20s0x%x", name, input->match_flags);

	PRINT_SCALAR(bustype);
	PRINT_SCALAR(vendor);
	PRINT_SCALAR(product);
	PRINT_SCALAR(version);

	PRINT_ARRAY(evbit);
	PRINT_ARRAY(keybit);
	PRINT_ARRAY(relbit);
	PRINT_ARRAY(absbit);
	PRINT_ARRAY(mscbit);
	PRINT_ARRAY(ledbit);
	PRINT_ARRAY(sndbit);
	PRINT_ARRAY(ffbit);

	fprintf(out, "  0x%x\n", input->driver_info);
}

static void output_input_entry_64(struct input_device_id_64 *input,
				  char *name, FILE *out)
{
	fprintf(out, "%-20s0x%llx", name, input->match_flags);

	PRINT_SCALAR(bustype);
	PRINT_SCALAR(vendor);
	PRINT_SCALAR(product);
	PRINT_SCALAR(version);

	PRINT_ARRAY(evbit);
	PRINT_ARRAY(keybit);
	PRINT_ARRAY(relbit);
	PRINT_ARRAY(absbit);
	PRINT_ARRAY(mscbit);
	PRINT_ARRAY(ledbit);
	PRINT_ARRAY(sndbit);
	PRINT_ARRAY(ffbit);

	fprintf(out, "  0x%llx\n", input->driver_info);
}

void output_input_table(struct module *modules, FILE *out)
{
	struct module *i;

	fprintf(out, "# module         matchBits");
	fprintf(out, " bustype vendor product version evBits keyBits relBits");
	fprintf(out, " absBits mscBits ledBits sndBits ffBits driver_info\n");

	for (i = modules; i; i = i->next) {
		struct input_device_id_32 *i32;
		struct input_device_id_64 *i64;

		char shortname[strlen(i->pathname) + 1];

		if (!i->input_table)
			continue;

		make_shortname(shortname, i->pathname);
		if (i->input_size == sizeof(*i32)) {
			for (i32 = i->input_table; 
			     i32->match_flags || i32->driver_info;
			     i32++)
				output_input_entry_32(i32, shortname, out);
		} else {
			for (i64 = i->input_table; 
			     i64->match_flags || i64->driver_info;
			     i64++)
				output_input_entry_64(i64, shortname, out);
		}
	}
}
