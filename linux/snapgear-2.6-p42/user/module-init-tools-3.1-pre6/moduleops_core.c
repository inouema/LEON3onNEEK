/* Load the given section: NULL on error. */
static void *PERBIT(load_section)(ElfPERBIT(Ehdr) *hdr,
			    const char *secname,
			    unsigned long *size)
{
	ElfPERBIT(Shdr) *sechdrs;
	unsigned int i;
	char *secnames;

	/* Grab section headers and strings so we can tell who is who */
	sechdrs = (void *)hdr + hdr->e_shoff;
	secnames = (void *)hdr + sechdrs[hdr->e_shstrndx].sh_offset;

	/* Find the section they want */
	for (i = 1; i < hdr->e_shnum; i++) {
		if (strcmp(secnames+sechdrs[i].sh_name, secname) == 0) {
			*size = sechdrs[i].sh_size;
			return (void *)hdr + sechdrs[i].sh_offset;
		}
	}
	*size = 0;
	return NULL;
}

static void PERBIT(load_symbols)(struct module *module)
{
	struct PERBIT(kernel_symbol) *ksyms;
	char *ksymstrings;
	unsigned long i, size;

	/* New-style: strings are in this section. */
	ksymstrings = PERBIT(load_section)(module->data, "__ksymtab_strings",
					   &size);
	if (ksymstrings) {
		unsigned int i = 0;
		for (;;) {
			/* Skip any zero padding. */
			while (!ksymstrings[i])
				if (++i >= size)
					return;
			add_symbol(ksymstrings+i, module);
			i += strlen(ksymstrings+i);
		}
		/* GPL symbols too */
		ksymstrings = PERBIT(load_section)(module->data,
						   "__ksymtab_strings_gpl",
						   &size);
		for (;;) {
			/* Skip any zero padding. */
			while (!ksymstrings[i])
				if (++i >= size)
					return;
			add_symbol(ksymstrings+i, module);
			i += strlen(ksymstrings+i);
		}
		return;
	}

	/* Old-style. */
	ksyms = PERBIT(load_section)(module->data, "__ksymtab", &size);
	for (i = 0; i < size / sizeof(struct PERBIT(kernel_symbol)); i++)
		add_symbol(ksyms[i].name, module);
	ksyms = PERBIT(load_section)(module->data, "__gpl_ksymtab", &size);
	for (i = 0; i < size / sizeof(struct PERBIT(kernel_symbol)); i++)
		add_symbol(ksyms[i].name, module);
}

static char *PERBIT(get_aliases)(struct module *module, unsigned long *size)
{
	return PERBIT(load_section)(module->data, ".modalias", size);
}

static char *PERBIT(get_modinfo)(struct module *module, unsigned long *size)
{
	return PERBIT(load_section)(module->data, ".modinfo", size);
}

#ifndef STT_REGISTER
#define STT_REGISTER    13              /* Global register reserved to app. */
#endif

/* Calculate the dependencies for this module */
static void PERBIT(calculate_deps)(struct module *module, int verbose)
{
	unsigned int i;
	unsigned long size;
	char *strings;
	ElfPERBIT(Sym) *syms;
	ElfPERBIT(Ehdr) *hdr;
	int handle_register_symbols;

	strings = PERBIT(load_section)(module->data, ".strtab", &size);
	syms = PERBIT(load_section)(module->data, ".symtab", &size);

	if (!strings || !syms) {
		warn("Couldn't find symtab and strtab in module %s\n",
		     module->pathname);
		return;
	}

	hdr = module->data;
	handle_register_symbols = 0;
	if (hdr->e_machine == EM_SPARC ||
	    hdr->e_machine == EM_SPARCV9)
		handle_register_symbols = 1;

	module->num_deps = 0;
	module->deps = NULL;
	for (i = 1; i < size / sizeof(syms[0]); i++) {
		if (syms[i].st_shndx == SHN_UNDEF) {
			/* Look for symbol */
			const char *name = strings + syms[i].st_name;
			struct module *owner;
			int weak;

			/* Not really undefined: sparc gcc 3.3 creates
                           U references when you have global asm
                           variables, to avoid anyone else misusing
                           them. */
			if (handle_register_symbols
			    && (ELFPERBIT(ST_TYPE)(syms[i].st_info)
				== STT_REGISTER))
				continue;

			weak = ELFPERBIT(ST_BIND)(syms[i].st_info) == STB_WEAK;
			owner = find_symbol(name, module->pathname, weak);
			if (owner) {
				if (verbose)
					printf("%s needs \"%s\": %s\n",
					       module->pathname, name,
					       owner->pathname);
				add_dep(module, owner);
			}
		}
	}
}

static void *PERBIT(deref_sym)(ElfPERBIT(Ehdr) *hdr, const char *name)
{
	unsigned int i;
	unsigned long size;
	char *strings;
	ElfPERBIT(Sym) *syms;
	ElfPERBIT(Shdr) *sechdrs;

	sechdrs = (void *)hdr + hdr->e_shoff;
	strings = PERBIT(load_section)(hdr, ".strtab", &size);
	syms = PERBIT(load_section)(hdr, ".symtab", &size);

	/* Don't warn again: we already have above */
	if (!strings || !syms)
		return NULL;

	for (i = 0; i < size / sizeof(syms[0]); i++) {
		if (strcmp(strings + syms[i].st_name, name) == 0) {
			/* In BSS?  Happens for empty device tables on
			 * recent GCC versions. */
			if (sechdrs[syms[i].st_shndx].sh_type == SHT_NOBITS)
				return NULL;
			return (void *)hdr
				+ sechdrs[syms[i].st_shndx].sh_offset
				+ syms[i].st_value;
		}
	}
	return NULL;
}

/* FIXME: Check size, unless we end up using aliases anyway --RR */
static void PERBIT(fetch_tables)(struct module *module)
{
	module->pci_size = PERBIT(PCI_DEVICE_SIZE);
	module->pci_table = PERBIT(deref_sym)(module->data,
					"__mod_pci_device_table");

	module->usb_size = PERBIT(USB_DEVICE_SIZE);
	module->usb_table = PERBIT(deref_sym)(module->data,
					"__mod_usb_device_table");

	module->ccw_size = PERBIT(CCW_DEVICE_SIZE);
	module->ccw_table = PERBIT(deref_sym)(module->data,
					"__mod_ccw_device_table");

	module->ieee1394_size = PERBIT(IEEE1394_DEVICE_SIZE);
	module->ieee1394_table = PERBIT(deref_sym)(module->data,
					"__mod_ieee1394_device_table");

	module->pnp_size = PERBIT(PNP_DEVICE_SIZE);
	module->pnp_table = PERBIT(deref_sym)(module->data,
					"__mod_pnp_device_table");

	module->pnp_card_size = PERBIT(PNP_CARD_DEVICE_SIZE);
	module->pnp_card_table = PERBIT(deref_sym)(module->data,
					"__mod_pnp_card_device_table");
	module->pnp_card_offset = PERBIT(PNP_CARD_DEVICE_OFFSET);

	module->input_size = PERBIT(INPUT_DEVICE_SIZE);
	module->input_table = PERBIT(deref_sym)(module->data,
					"__mod_input_device_table");
}

struct module_ops PERBIT(mod_ops) = {
	.load_symbols	= PERBIT(load_symbols),
	.calculate_deps	= PERBIT(calculate_deps),
	.fetch_tables	= PERBIT(fetch_tables),
	.get_aliases	= PERBIT(get_aliases),
	.get_modinfo	= PERBIT(get_modinfo),
};
