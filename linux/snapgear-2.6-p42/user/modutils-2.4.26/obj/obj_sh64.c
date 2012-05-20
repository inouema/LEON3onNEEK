/* sh64 specific support for Elf loading and relocation.
   Copyright 1999 Linux International.

   Contributed by Benedict R. Gaster (benedict.gaster@superh.com)
   
   Currently limited to support only 32bit ABI.

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
   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

#include <string.h>
#include <assert.h>

#include <module.h>
#include <obj.h>
#include <util.h>

/*======================================================================*/

/* Standard method of finding relocation symbols, sets isym */
#define obj_find_relsym(isym, f, find, rel, symtab, strtab) \
  { \
    unsigned long symndx = ELFW(R_SYM)((rel)->r_info); \
    ElfW(Sym) *extsym = (symtab)+symndx; \
    if (ELFW(ST_BIND)(extsym->st_info) == STB_LOCAL) { \
      isym = (typeof(isym)) (f)->local_symtab[symndx]; \
    } \
    else { \
      const char *name; \
      if (extsym->st_name) \
        name = (strtab) + extsym->st_name; \
      else \
        name = (f)->sections[extsym->st_shndx]->name; \
      isym = (typeof(isym)) obj_find_symbol((find), name); \
    } \
  }

/*======================================================================*/


struct sh64_got_entry
{
  int offset;
  unsigned offset_done : 1;
  unsigned reloc_done : 1;
};

struct sh64_file
{
  struct obj_file root;
  struct obj_section *got;
};

struct sh64_symbol
{
  struct obj_symbol root;
  struct sh64_got_entry gotent;
};


/*======================================================================*/

struct obj_file *
arch_new_file (void)
{
  struct sh64_file *f;
  f = xmalloc(sizeof(*f));
  f->got = NULL;
  return &f->root;
}

struct obj_section *
arch_new_section (void)
{
  return xmalloc(sizeof(struct obj_section));
}

struct obj_symbol *
arch_new_symbol (void)
{
  struct sh64_symbol *sym;
  sym = xmalloc(sizeof(*sym));
  memset(&sym->gotent, 0, sizeof(sym->gotent));
  return &sym->root;
}

enum obj_reloc
arch_apply_relocation (struct obj_file *f,
		       struct obj_section *targsec,
		       struct obj_section *symsec,
		       struct obj_symbol *sym,
		       Elf32_Rela *rel,
		       Elf32_Addr v)
{
  struct sh64_file *ifile = (struct sh64_file *)f;
  struct sh64_symbol *isym  = (struct sh64_symbol *)sym;

  Elf32_Addr *loc = (Elf32_Addr *)(targsec->contents + rel->r_offset);
  Elf32_Addr dot = targsec->header.sh_addr + rel->r_offset;
  Elf32_Addr got = ifile->got ? ifile->got->header.sh_addr : 0;

  enum obj_reloc ret = obj_reloc_ok;

  switch (ELF32_R_TYPE(rel->r_info))
    {
    case R_SH_NONE:
      break;

    case R_SH_DIR32:
      *loc += v;
      break;

    case R_SH_REL32:
      *loc += v - dot;
      break;

    case R_SH_PLT32:
      *loc = v - dot;
      break;

    case R_SH_GLOB_DAT:
    case R_SH_JMP_SLOT:
      *loc = v;
      break;

    case R_SH_RELATIVE:
      *loc = f->baseaddr + rel->r_addend;
      break;

    case R_SH_GOTPC:
      assert(got != 0);
      *loc = got - dot + rel->r_addend;
      break;

    case R_SH_GOT32:
      assert(isym != NULL);
      if (!isym->gotent.reloc_done)
	{
	  isym->gotent.reloc_done = 1;
	  *(Elf32_Addr *)(ifile->got->contents + isym->gotent.offset) = v;
	}
      *loc = isym->gotent.offset + rel->r_addend;
      break;

    case R_SH_GOTOFF:
      assert(got != 0);
      *loc = v - got;
      break;

    case R_SH_IMM_MEDLOW16:
    case R_SH_IMM_LOW16:
      {
	Elf32_Addr word;

	if (ELF32_R_TYPE(rel->r_info) == R_SH_IMM_MEDLOW16)
	  v >>= 16;

	/*
	 *  movi and shori have the format:
	 *
	 *  |  op  | imm  | reg | reserved |
         *   31..26 25..10 9.. 4 3   ..   0
	 *
	 * so we simply mask and or in imm.
	 */
	word = *loc & ~0x3fffc00;
	word |= (v & 0xffff) << 10;

	*loc = word;
      }
      break;
    case R_SH_IMM_MEDLOW16_PCREL:
    case R_SH_IMM_LOW16_PCREL:
      {
	Elf32_Addr word;
	
	word = *loc & ~0x3fffc00;

        v -= dot;

	if (ELF32_R_TYPE(rel->r_info) == R_SH_IMM_MEDLOW16_PCREL)
	{
	  v >>= 16;
	} 

	word |= (v & 0xffff) << 10;

	*loc = word;
      }
      break;
    default:
      ret = obj_reloc_unhandled;
      break;
    }

  return ret;
}

int
arch_create_got (struct obj_file *f)
{
  struct sh64_file *ifile = (struct sh64_file *)f;
  int i, n, offset = 0, gotneeded = 0;

  n = ifile->root.header.e_shnum;
  for (i = 0; i < n; ++i)
    {
      struct obj_section *relsec, *symsec, *strsec;
      Elf32_Rela *rel, *relend;
      Elf32_Sym *symtab;
      const char *strtab;

      relsec = ifile->root.sections[i];
      if (relsec->header.sh_type != SHT_REL)
	continue;

      symsec = ifile->root.sections[relsec->header.sh_link];
      strsec = ifile->root.sections[symsec->header.sh_link];

      rel = (Elf32_Rela *)relsec->contents;
      relend = rel + (relsec->header.sh_size / sizeof(Elf32_Rela));
      symtab = (Elf32_Sym *)symsec->contents;
      strtab = (const char *)strsec->contents;

      for (; rel < relend; ++rel)
	{
	  struct sh64_symbol *intsym;

	  switch (ELF32_R_TYPE(rel->r_info))
	    {
	    case R_SH_GOTPC:
	    case R_SH_GOTOFF:
	      gotneeded = 1;
	    default:
	      continue;

	    case R_SH_GOT32:
	      break;
	    }

	  obj_find_relsym(intsym, f, &ifile->root, rel, symtab, strtab);

	  if (!intsym->gotent.offset_done)
	    {
	      intsym->gotent.offset_done = 1;
	      intsym->gotent.offset = offset;
	      offset += 4;
	    }
	}
    }

  if (offset > 0 || gotneeded)
    ifile->got = obj_create_alloced_section(&ifile->root, ".got", 4, offset);

  return 1;
}

int
arch_init_module (struct obj_file *f, struct module *mod)
{
  return 1;
}

int
arch_finalize_section_address(struct obj_file *f, Elf32_Addr base)
{
  int  i, n = f->header.e_shnum;

  f->baseaddr = base;
  for (i = 0; i < n; ++i)
    f->sections[i]->header.sh_addr += base;
  return 1;
}

int
arch_load_proc_section(struct obj_section *sec, int fp)
{
    /* Assume it's just a debugging section that we can safely
       ignore ...  */
    sec->contents = NULL;

    return 0;
}

int
arch_archdata (struct obj_file *fin, struct obj_section *sec)
{
  return 0;
}
