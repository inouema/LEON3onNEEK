/* Generate kernel symbol version hashes.
   Copyright 1996, 1997 Linux International.

   New implementation contributed by Richard Henderson <rth@tamu.edu>
   Based on original work by Bjorn Ekwall <bj0rn@blox.se>

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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <stdarg.h>
#include <getopt.h>

#include "genksyms.h"
#include "util.h"
#include "version.h"

/*----------------------------------------------------------------------*/

#define HASH_BUCKETS  4099

static struct symbol *symtab[HASH_BUCKETS];
FILE *outfile, *debugfile;

int cur_line = 1;
char *cur_filename, *output_directory;

int flag_debug, flag_dump_defs, flag_warnings;
int checksum_version = 1, kernel_version = version(2,0,0);

static int errors;
static int nsyms;

static struct symbol *expansion_trail;
static const char *crc_prefix = "";

static const char * const symbol_type_name[] = {
  "normal", "typedef", "enum", "struct", "union"
};

/*----------------------------------------------------------------------*/

static const unsigned int crctab32[] =
{
#include "crc32.tab"
};

static inline unsigned long
partial_crc32_one(unsigned char c, unsigned long crc)
{
  return crctab32[(crc ^ c) & 0xff] ^ (crc >> 8);
}

static inline unsigned long
partial_crc32(const char *s, unsigned long crc)
{
  while (*s)
    crc = partial_crc32_one(*s++, crc);
  return crc;
}

static inline unsigned long
crc32(const char *s)
{
  return partial_crc32(s, 0xffffffff) ^ 0xffffffff;
}


/*----------------------------------------------------------------------*/

static inline enum symbol_type
map_to_ns(enum symbol_type t)
{
  if (t == SYM_TYPEDEF)
    t = SYM_NORMAL;
  else if (t == SYM_UNION)
    t = SYM_STRUCT;
  return t;
}

struct symbol *
find_symbol(const char *name, enum symbol_type ns)
{
  unsigned long h = crc32(name) % HASH_BUCKETS;
  struct symbol *sym;

  for (sym = symtab[h]; sym ; sym = sym->hash_next)
    if (map_to_ns(sym->type) == map_to_ns(ns) && strcmp(name, sym->name) == 0)
      break;

  return sym;
}

struct symbol *
add_symbol(const char *name, enum symbol_type type, struct string_list *defn, int is_extern)
{
  unsigned long h = crc32(name) % HASH_BUCKETS;
  struct symbol *sym;

  for (sym = symtab[h]; sym ; sym = sym->hash_next)
    if (map_to_ns(sym->type) == map_to_ns(type)
	&& strcmp(name, sym->name) == 0)
      {
	if (!equal_list(sym->defn, defn))
	  error_with_pos("redefinition of %s", name);
	return sym;
      }

  sym = xmalloc(sizeof(*sym));
  sym->name = name;
  sym->type = type;
  sym->defn = defn;
  sym->expansion_trail = NULL;
  sym->is_extern = is_extern;

  sym->hash_next = symtab[h];
  symtab[h] = sym;

  if (flag_debug)
    {
      fprintf(debugfile, "Defn for %s %s == <", symbol_type_name[type],  name);
      if (is_extern)
        fputs("extern ", debugfile);
      print_list(debugfile, defn);
      fputs(">\n", debugfile);
    }

  ++nsyms;
  return sym;
}


/*----------------------------------------------------------------------*/

inline void
free_node(struct string_list *node)
{
  free(node->string);
  free(node);
}

void
free_list(struct string_list *s, struct string_list *e)
{
  while (s != e)
    {
      struct string_list *next = s->next;
      free_node(s);
      s = next;
    }
}

inline struct string_list *
copy_node(struct string_list *node)
{
  struct string_list *newnode;

  newnode = xmalloc(sizeof(*newnode));
  newnode->string = xstrdup(node->string);
  newnode->tag = node->tag;

  return newnode;
}

struct string_list *
copy_list(struct string_list *s, struct string_list *e)
{
  struct string_list *h, *p;

  if (s == e)
    return NULL;

  p = h = copy_node(s);
  while ((s = s->next) != e)
    p = p->next = copy_node(s);
  p->next = NULL;

  return h;
}

int
equal_list(struct string_list *a, struct string_list *b)
{
  while (a && b)
    {
      if (a->tag != b->tag || strcmp(a->string, b->string))
	return 0;
      a = a->next;
      b = b->next;
    }

  return !a && !b;
}

static inline void
print_node(FILE *f, struct string_list *list)
{
  switch (list->tag)
    {
    case SYM_STRUCT:
      putc('s', f);
      goto printit;
    case SYM_UNION:
      putc('u', f);
      goto printit;
    case SYM_ENUM:
      putc('e', f);
      goto printit;
    case SYM_TYPEDEF:
      putc('t', f);
      goto printit;

    printit:
      putc('#', f);
    case SYM_NORMAL:
      fputs(list->string, f);
      break;
    }
}

void
print_list(FILE *f, struct string_list *list)
{
  struct string_list **e, **b;
  struct string_list *tmp, **tmp2;
  int elem = 1;

  if (list == NULL)
    {
      fputs("(nil)", f);
      return;
    }

  tmp = list;
  while((tmp = tmp->next) != NULL)
	  elem++;

  b = alloca(elem * sizeof(*e));
  e = b + elem;
  tmp2 = e - 1;

  (*tmp2--) = list;
  while((list = list->next) != NULL)
	  *(tmp2--) = list;

  while (b != e)
    {
      print_node(f, *b++);
      putc(' ', f);
    }
}

static unsigned long
expand_and_crc_list(struct string_list *list, unsigned long crc)
{
  struct string_list **e, **b;
  struct string_list *tmp, **tmp2;
  int elem = 1;

  if (!list)
    return crc;

  tmp = list;
  while((tmp = tmp->next) != NULL)
	  elem++;

  b = alloca(elem * sizeof(*e));
  e = b + elem;
  tmp2 = e - 1;

  *(tmp2--) = list;
  while ((list = list->next) != NULL)
    *(tmp2--) = list;

  while (b != e)
    {
      struct string_list *cur;
      struct symbol *subsym;

      cur = *(b++);
      switch (cur->tag)
	{
	case SYM_NORMAL:
	  if (flag_dump_defs)
	    fprintf(debugfile, "%s ", cur->string);
	  crc = partial_crc32(cur->string, crc);
	  crc = partial_crc32_one(' ', crc);
	  break;

	case SYM_TYPEDEF:
	  subsym = find_symbol(cur->string, cur->tag);
	  if (checksum_version == 1)
	    crc = expand_and_crc_list(subsym->defn, crc);
	  else if (subsym->expansion_trail)
	    {
	      if (flag_dump_defs)
		fprintf(debugfile, "%s ", cur->string);
	      crc = partial_crc32(cur->string, crc);
	      crc = partial_crc32_one(' ', crc);
	    }
	  else
	    {
	      subsym->expansion_trail = expansion_trail;
	      expansion_trail = subsym;
	      crc = expand_and_crc_list(subsym->defn, crc);
	    }
	  break;

	case SYM_STRUCT:
	case SYM_UNION:
	case SYM_ENUM:
	  subsym = find_symbol(cur->string, cur->tag);
	  if (!subsym)
	    {
	      struct string_list *n, *t = NULL;

	      error_with_pos("expand undefined %s %s",
			     symbol_type_name[cur->tag], cur->string);

	      n = xmalloc(sizeof(*n));
	      n->string = xstrdup(symbol_type_name[cur->tag]);
	      n->tag = SYM_NORMAL;
	      n->next = t;
	      t = n;

	      n = xmalloc(sizeof(*n));
	      n->string = xstrdup(cur->string);
	      n->tag = SYM_NORMAL;
	      n->next = t;
	      t = n;

	      n = xmalloc(sizeof(*n));
	      n->string = xstrdup("{ UNKNOWN }");
	      n->tag = SYM_NORMAL;
	      n->next = t;

	      subsym = add_symbol(cur->string, cur->tag, n, 0);
	    }
	  if (subsym->expansion_trail)
	    {
	      if (flag_dump_defs)
		{
		  fprintf(debugfile, "%s %s ", symbol_type_name[cur->tag],
			  cur->string);
		}

	      crc = partial_crc32(symbol_type_name[cur->tag], crc);
	      crc = partial_crc32_one(' ', crc);
	      crc = partial_crc32(cur->string, crc);
	      crc = partial_crc32_one(' ', crc);
	    }
	  else
	    {
	      subsym->expansion_trail = expansion_trail;
	      expansion_trail = subsym;
	      crc = expand_and_crc_list(subsym->defn, crc);
	    }
	  break;
	}
    }

  return crc;
}

void
export_symbol(const char *name)
{
  struct symbol *sym;

  sym = find_symbol(name, SYM_NORMAL);
  if (!sym)
    error_with_pos("export undefined symbol %s", name);
  else
    {
      unsigned long crc;

      if (flag_dump_defs)
	fprintf(debugfile, "Export %s == <", name);

      expansion_trail = (struct symbol *)-1L;

      crc = expand_and_crc_list(sym->defn, 0xffffffff) ^ 0xffffffff;

      sym = expansion_trail;
      while (sym != (struct symbol *)-1L)
	{
	  struct symbol *n = sym->expansion_trail;
	  sym->expansion_trail = 0;
	  sym = n;
	}

      if (flag_dump_defs)
	fputs(">\n", debugfile);

      if (checksum_version > 1)
	{
	  fprintf(outfile, "#define __ver_%s\t%s%08lx\n", name,
		  crc_prefix, crc);
	  fprintf(outfile, "#define %s\t_set_ver(%s)\n", name, name);
	}
      else
	{
	  fprintf(outfile, "#define %s\t_set_ver(%s, %s%08lx)\n", name, name,
		  crc_prefix, crc);
	}
    }
}


/*----------------------------------------------------------------------*/

static int
parse_kernel_version(char * p)
{
  int a, b, c;

  a = strtoul(p, &p, 10);
  if (*p != '.')
    return -1;
  b = strtoul(p+1, &p, 10);
  if (*p != '.')
    return -1;
  c = strtoul(p+1, &p, 10);
  if (*p != '\0')
    return -1;

  kernel_version = a << 16 | b << 8 | c;

  return 0;
}

void
error(const char *fmt, ...)
{
  va_list args;

  if (flag_warnings)
    {
      va_start(args, fmt);
      vfprintf(stderr, fmt, args);
      va_end(args);
      putc('\n', stderr);

      errors++;
    }
}

void
error_with_pos(const char *fmt, ...)
{
  va_list args;

  if (flag_warnings)
    {
      fprintf(stderr, "%s:%d: ", cur_filename ? : "<stdin>", cur_line);

      va_start(args, fmt);
      vfprintf(stderr, fmt, args);
      va_end(args);
      putc('\n', stderr);

      errors++;
    }
}


void genksyms_usage(void)
{
	fputs("Usage:\n"
	      "genksyms [-dDwqhV] [-k kernel_version] [-p prefix] > .../linux/module/*.ver\n"
	      "\n"
	      "  -d, --debug           Increment the debug level (repeatable)\n"
	      "  -D, --dump            Dump expanded symbol defs (for debugging only)\n"
	      "  -w, --warnings        Enable warnings\n"
	      "  -q, --quiet           Disable warnings (default)\n"
	      "  -h, --help            Print this message\n"
	      "  -V, --version         Print the release version\n"
	      "  -k ver\n"
	      "       --kernel ver     Set the kernel version for which we are compiling\n"
	      "  -p string\n"
	      "       --prefix string  Set a mangling prefix for all symbols\n"
	      , stderr);
}

int
main(int argc, char **argv)
{
  int o;

  struct option long_opts[] = {
    {"debug", 0, 0, 'd'},
    {"warnings", 0, 0, 'w'},
    {"quiet", 0, 0, 'q'},
    {"dump", 0, 0, 'D'},
    {"kernel", 1, 0, 'k'},
    {"prefix", 1, 0, 'p'},
    {"version", 0, 0, 'V'},
    {"help", 0, 0, 'h'},
    {0, 0, 0, 0}
  };

  while ((o = getopt_long(argc, argv, "dwqVDk:p:",
			  &long_opts[0], NULL)) != EOF)
    switch (o)
      {
      case 'd':
	flag_debug++;
	break;
      case 'w':
	flag_warnings = 1;
	break;
      case 'q':
	flag_warnings = 0;
	break;
      case 'V':
	fputs("genksyms version " MODUTILS_VERSION "\n", stderr);
	break;
      case 'D':
	flag_dump_defs = 1;
	break;
      case 'k':
	if (parse_kernel_version(optarg)) {
	    fprintf( stderr, "unrecognised kernel version : %s\n", optarg);
	    return -1;
	}
	break;
      case 'p':
	crc_prefix = optarg;
	break;
      case 'h':
	genksyms_usage();
	return 0;
      default:
	genksyms_usage();
	return 1;
      }

  if (kernel_version >= version(2,1,18))
    {
      if (optind != argc) {
	  genksyms_usage();
	  return 1;
      }

      /* For newer kernels, eliminate some irrelevant constructs.  */
      checksum_version = 2;

      outfile = stdout;
    }
  else
    {
      if (optind+1 != argc) {
	  genksyms_usage();
	  return 1;
      }
      output_directory = argv[optind];
    }

    {
      extern int yydebug;
      extern int yy_flex_debug;

      yydebug = (flag_debug > 1);
      yy_flex_debug = (flag_debug > 2);

      debugfile = stderr;
      /* setlinebuf(debugfile); */
    }

  yyparse();

  if (checksum_version == 1)
    {
      fputs("#endif\n#endif\n", outfile);
    }

  if (flag_debug)
    {
      fprintf(debugfile, "Hash table occupancy %d/%d = %g\n",
	      nsyms, HASH_BUCKETS, (double)nsyms / (double)HASH_BUCKETS);
    }

  return errors != 0;
}
