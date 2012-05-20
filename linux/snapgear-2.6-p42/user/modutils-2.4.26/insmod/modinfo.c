/* Display information gleaned from a module's .modinfo section.
   Copyright 1996, 1997 Linux International.

   Contributed by Tom Dyas <tdyas@eden.rutgers.edu>

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
 * Fixes:
 *
 * optind++ in show_module_info, Salvador Ortiz Garcia <sog@msg.com.mx>
 * unified module path handling: Bjorn Ekwall <bj0rn@blox.se> February 1999
 * Rationalize common code for 32/64 bit architectures.
 *   Keith Owens <kaos@ocs.com.au> December 1999.
 * Add arch64().
 *   Keith Owens <kaos@ocs.com.au> December 1999.
 * Print " persistent" for persistent parameters.
 *   Keith Owens <kaos@ocs.com.au> November 2000.
 * License support.
 *   Keith Owens <kaos@ocs.com.au> September 2001.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>
#include <unistd.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "module.h"
#include "obj.h"
#include "util.h"
#include "version.h"
#include "config.h"

extern int show_module_info(const char *filename, const char *fmtstr);
extern int show_module_info_32(const char *filename, const char *fmtstr);
extern int show_module_info_64(const char *filename, const char *fmtstr);

#if defined(COMMON_3264) && defined(ONLY_32)
#define SHOW_MODULE_INFO show_module_info_32		/* 32 bit version */
#elif defined(COMMON_3264) && defined(ONLY_64)
#define SHOW_MODULE_INFO show_module_info_64		/* 64 bit version */
#else
#define SHOW_MODULE_INFO show_module_info		/* Not common 3264 code */
#endif


static int convert_escape (int c)
{
  switch (c)
    {
    case 'a':  /* WARNING: the meaning of \a is changed is -traditional is used */
      c = '\a';
      break;
    case 'v':
      c = '\v';
      break;
    case 'b':
      c = '\b';
      break;
    case 'e': /* ESC -- non-ANSI */
    case 'E':
      c = '\033';
      break;
    case 'f':
      c = '\f';
      break;
    case 'n':
      c = '\n';
      break;
    case 'r':
      c = '\r';
      break;
    case 't':
      c = '\t';
      break;
    }

  return(c);
}


static const char *get_modinfo_value(struct obj_file *f, const char *key)
{
	struct obj_section *sec;
	char *p, *v, *n, *ep;
	size_t klen = strlen(key);

	if (strcmp(key, "filename") == 0) {
		return(f->filename);
	}

	sec = obj_find_section(f, ".modinfo");
	if (sec == NULL)
		return NULL;

	p = sec->contents;
	ep = p + sec->header.sh_size;
	while (p < ep) {
		v = strchr(p, '=');
		n = strchr(p, '\0');
		if (v) {
			if (v - p == klen && strncmp(p, key, klen) == 0)
				return v + 1;
		} else {
			if (n - p == klen && strcmp(p, key) == 0)
				return n;
		}
		p = n + 1;
	}

	return NULL;
}

/* Most fields are fixed format which makes it relatively easy for programs to
 * parse the output from modinfo.  But description and author fields can be
 * multi line and can contain any characters.  To make it possible to parse the
 * modinfo output, fields that might be multi line are printed enclosed in '"'
 * for human readability and embedded newlines are printed as "\n  " so the
 * second and subsequent lines are always indented.
 */

static void append_modinfo_tag(struct obj_file *f, char *tag, char *def,
			      int multi_line)
{
	const char *p, *p1;
	int l;

	p = get_modinfo_value(f, tag);
	if (!p && !def)
		return;

	if (!p) {
		p = def;
		multi_line = 0;
	}

	if (!multi_line)
		fputs (p, stdout);
	else {
		putchar ('"');
		p1 = p;
		while (*p1) {
			p1 = strchr(p, '\n');
			if (p1)
				++p1;
			else
				p1 = p + strlen(p);
			l = p1 - p;
			fwrite (p, 1, l, stdout);
			if (*(p1-1) == '\n')
				fputs ("  ", stdout);
			p = p1;
		}
		putchar ('"');
	}
}

static void show_parameter(struct obj_file *f, char *key, char *value,
			   const char *desc)
{
	struct obj_symbol *sym;
	int min, max;
	char *p = value;

	sym = obj_find_symbol(f, key);
	if (sym == NULL)
		printf("warning: symbol for parameter %s not found\n", key);

	if (isdigit(*p)) {
		min = strtoul(p, &p, 10);
		if (*p == '-')
			max = strtoul(p + 1, &p, 10);
		else
			max = min;
	} else
		min = max = 1;

	if (max < min)
		printf("warning: parameter %s has max < min!\n", key);

	printf("%s ", key);

	switch (*p) {
	case 'c':
		printf("char");
		if (!isdigit(p[1]))
			printf(" *** missing string size ***");
		else while (isdigit(p[1]))
			++p;	/* swallow c array size */
		break;
	case 'b':
		printf("byte");
		break;
	case 'h':
		printf("short");
		break;
	case 'i':
		printf("int");
		break;
	case 'l':
		printf("long");
		break;
	case 's':
		printf("string");
		break;
	case '\0':
		printf("no format character!\n");
		return;
	default:
		printf("unknown format character '%c'", *p);
		return;
	}
	switch (*++p) {
	case 'p':
		printf(" persistent");
		if (*(p-1) == 's')
			printf(" (invalid)");
		break;
	case '\0':
		break;
	default:
		printf(" unknown format modifier '%c'", *p);
		break;
	}

	if (min > 1 || max > 1)
		printf(" array (min = %d, max = %d)", min, max);

	if (desc && *desc) {
		const char *p = desc, *p1;
		printf(", description \"");
		p1 = p;
		while (*p1) {
			p1 = strchr(p, '\n');
			if (p1)
				++p1;
			else
				p1 = p + strlen(p);
			printf("%.*s", (int)(p1 - p), p);
			if (*(p1-1) == '\n')
				printf("  ");
			p = p1;
		}
		printf("\"");
	}
}

#define MAX_TAG_LEN 128

/* Check the "format" string. */
static int format_check_string(const char *format)
{
	const char *in_str = format;

	while (*in_str) {
		/* Just skip normal characters. */
		if (*in_str != '%')
		  {
		    if (*in_str == '\\')
		      convert_escape(*++in_str);
		    ++in_str;
		    continue;
		  }
		/* Ensure that the replacement is there. */
		if (*++in_str == '\0') {
			error("missing replacement");
			return -1;
		}
		/* Process the replacement as required. */
		switch (*in_str++) {

		case '%':
		case 'a':
		case 'd':
		case 'n':
		case 'l':
		case 'p':
			break;

		case '{':{
				char *end = strchr(in_str, '}');

				/* Make sure the %{...} is formatted correctly. */
				if (!end) {
					error("unterminated %%{...} construct");
					return -1;
				}
				if (end - in_str > MAX_TAG_LEN - 1) {
					error("%%{...} construct is too large");
					return -1;
				}
				/* Advance past the end of the replacement. */
				in_str = end + 1;
				break;
			}

		default:
			error("%c: unknown replacement", in_str[-1]);
			return -1;
		}		/* switch */
	}			/* while */
	return 0;
}

/* Format one line of the "format" string based on the module contents. */
static void format_query_line(struct obj_file *f, const char *format,
			      char *key, char *value, const char *desc)
{
	int c;
	const char *in_str = format;

	while (*in_str) {
		/* Just copy normal characters into the output. */
		if (*in_str != '%')
		  {
		    if (*in_str == '\\')
		      c = convert_escape(*++in_str);
		    else
		      c = *in_str;

		    ++in_str;

		    putchar (c);
		    if (c == '\n')
			    break;
		    continue;
		  }
		++in_str;
		/* Process the replacement as required. */
		switch (*in_str++) {

		case '%':
			putchar ('%');
			break;

		case 'a':
			append_modinfo_tag(f, "author", "<none>", 1);
			break;

		case 'd':
			append_modinfo_tag(f, "description", "<none>", 1);
			break;

		case 'n':
			append_modinfo_tag(f, "filename", "<none>", 0);
			break;

		case 'l':
			append_modinfo_tag(f, "license", "<none>", 1);
			break;

		case 'p':
			show_parameter(f, key, value, desc);
			break;

		case '{':{
				char tag[MAX_TAG_LEN];
				char *end = strchr(in_str, '}');
				int multi_line;

				/* Copy out the tag name. */
				memset(tag, 0, sizeof(tag));
				strncpy(tag, in_str, end - in_str);
				tag[end - in_str] = '\0';
				multi_line = strcmp(tag, "author") == 0 ||
					     strcmp(tag, "description") == 0 ||
					     strcmp(tag, "license") == 0;

				if (strcmp (tag, "parm") != 0)
				        /* Append the tag's value if it exists. */
					append_modinfo_tag(f, tag, "<none>", multi_line);
				else
					show_parameter(f, key, value, desc);

				/* Advance past the end of the replacement. */
				in_str = end + 1;
				break;
			}
		}		/* switch */
	}			/* while */
}

static void show_module_parameters(struct obj_file *f, const char *format)
{
	struct obj_section *sec;
	char *ptr, *value, *n, *endptr;
	int namelen;

	sec = obj_find_section(f, ".modinfo");
	if (sec == NULL) {
		error("module does not support typed parameters");
		return;
	}
	ptr = sec->contents;
	endptr = ptr + sec->header.sh_size;
	while (ptr < endptr) {
		value = strchr(ptr, '=');
		n = strchr(ptr, '\0');
		if (value) {
			namelen = value - ptr;
			if (namelen >= 5 && strncmp(ptr, "parm_", 5) == 0
			    && !(namelen > 10 && strncmp(ptr, "parm_desc_", 10) == 0)) {
				char *pname = xmalloc(namelen + 1);
				char *desckey = xmalloc(namelen + 5 + 1);

				strncpy(pname, ptr + 5, namelen - 5);
				pname[namelen - 5] = '\0';

				strcpy(desckey, "parm_desc_");	/* safe, xmalloc */
				strncat(desckey, ptr + 5, namelen - 5);
				desckey[namelen + 5] = '\0';

				format_query_line(f, format, pname, value + 1, get_modinfo_value(f, desckey));

				free(pname);
				free(desckey);
			}
		} else {
			if (n - ptr >= 5 && strncmp(ptr, "parm_", 5) == 0) {
				error("parameter %s found with no value", ptr);
			}
		}
		ptr = n + 1;
	}
}

/* Format the "format" string based on the module contents. */
static void format_query_string(struct obj_file *f, const char *format)
{
	while (*format != 0) {
		const char *p;
		int parm;

		parm = 0;
		for (p = format; *p != 0; p++) {
			if (p > format && p[-1] == '%' && *p == 'p')
				parm = 1;
			if (p >= format + 6 && memcmp (p - 6, "%{parm}", 7) == 0)
				parm = 1;
			if (p > format && p[-1] == '\n')
				break;
			if (p > format + 1 && p[-2] == '\\' && p[-1] == 'n')
				break;
		}
		if (parm == 0)
			format_query_line(f, format, NULL, NULL, NULL);
		else
		  show_module_parameters(f, format);
		format = p;
	}
}

int SHOW_MODULE_INFO(const char *filename, const char *fmtstr)
{
	int fp;
	struct obj_file *f;

	/* Locate the file to be loaded.  */
	if (!strchr(filename, '/') && !strchr(filename, '.')) {
		char *tmp = search_module_path(filename);
		if (tmp == NULL) {
			error("%s: no module by that name found", filename);
			return 1;
		}
		filename = tmp;
	}
	error_file = filename;

	/* Attempt to open and parse the module file. */
	if ((fp = gzf_open(filename, O_RDONLY)) < 0) {
		error("%s: %m", filename);
		return -1;
	} else if ((f = obj_load(fp, ET_REL, filename)) == NULL)
		return -1;
	gzf_close(fp);

	format_query_string(f, fmtstr);
	return 0;
}

/* For common 3264 code, add an overall show_module_info, in the 64 bit version. */
#if defined(COMMON_3264) && defined(ONLY_64)
int show_module_info(const char *filename, const char *fmtstr)
{
	if (arch64())
		return show_module_info_64(filename, fmtstr);
	else
		return show_module_info_32(filename, fmtstr);
}
#endif  /* defined(COMMON_3264) && defined(ONLY_64) */

/* For common 3264 code, only compile the usage message once, in the 64 bit version */
#if defined(COMMON_3264) && defined(ONLY_32)
extern void modinfo_usage(void);	/* Use the copy in the 64 bit version */
#else	/* Common 64 bit version or any non common code - compile usage routine */
void modinfo_usage(void)
{
	printf("usage: modinfo <options> <module>\n");
	printf("  -a, --author            display module author\n");
	printf("  -d, --description       display module description\n");
	printf("  -l, --license           display module license\n");
	printf("  -n, --filename          display module filename\n");
	printf("  -f <str>\n");
	printf("      --format <str>      print the <query-string>\n");
	printf("  -p, --parameters        display module parameters\n");
	printf("  -V, --version           show version\n");
	printf("  -h, --help              this usage screen\n");
}
#endif  /* defined(COMMON_3264) && defined(ONLY_32) */


/* For common 3264 code, only compile main in the 64 bit version. */
#if defined(COMMON_3264) && defined(ONLY_32)
/* Use the main in the 64 bit version */
#else
int main(int argc, char *argv[])
{
	static struct option long_opts[] =
	{
		{"author", 0, 0, 'a'},
		{"description", 0, 0, 'd'},
		{"license", 0, 0, 'l'},
		{"filename", 0, 0, 'n'},
		{"format", required_argument, 0, 'f'},
		{"parameters", 0, 0, 'p'},
		{"version", 0, 0, 'V'},
		{"help", 0, 0, 'h'},
		{0, 0, 0, 0}
	};
	int opt;
	char *fmtstr = "filename:    %n\ndescription: %d\nauthor:      %a\nlicense:     %l\nparm:        %p\n";

	while ((opt = getopt_long(argc, argv, "adlnq:pf:Vh", long_opts, NULL)) != EOF)
		switch (opt) {
		case 'a':
			fmtstr = "%a\n";
			break;
		case 'd':
			fmtstr = "%d\n";
			break;
		case 'l':
			fmtstr = "%l\n";
			break;
		case 'n':
			fmtstr = "%n\n";
			break;
		case 'f':
			fmtstr = optarg;
			break;
		case 'p':
			fmtstr = "%p\n";
			break;
		case 'V':
			fputs("modinfo (Linux modutils) " MODUTILS_VERSION "\n", stdout);
			exit(0);
		case 'h':

		default:
			modinfo_usage();
			exit(opt == 'h' ? 0 : 1);
		}

	if (optind >= argc) {
		modinfo_usage();
		exit(1);
	}
	error_file = "modinfo";
	if (format_check_string (fmtstr) != 0)
	  exit (1);
	while (optind < argc)
		show_module_info(argv[optind++], fmtstr);

	return 0;
}
#endif  /* defined(COMMON_3264) && defined(ONLY_32) */
