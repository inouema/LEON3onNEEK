/* Create a section containing all the symbols for an object.

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
     Fixes:
   */

#include <sys/types.h>
#include <getopt.h>
#include <fcntl.h>
#include <unistd.h>

#include "module.h"
#include "obj.h"
#include "kallsyms.h"
#include "util.h"
#include "version.h"

extern int kallsyms_main_32(int argc, char **argv);
extern int kallsyms_main_64(int argc, char **argv);

/*======================================================================*/

/* For common 3264 code, only compile the usage message once, in the 64 bit version */
#if defined(COMMON_3264) && defined(ONLY_32)
extern void kallsyms_usage(void);		/* Use the copy in the 64 bit version */
#else	/* Common 64 bit version or any non common code - compile usage routine */
void
kallsyms_usage (void)
{
    fputs("Usage:\n"
	  "kallsyms [-Vh] file\n"

	  "\n"
	  "  -V, --version         Show version\n"
	  "  -h, --help            Print this message.\n"
	  "  file                  Filename of a kernel (e.g. vmlinux)\n"
	  ,stderr);
}
#endif	/* defined(COMMON_3264) && defined(ONLY_32) */

#if defined(COMMON_3264) && defined(ONLY_32)
#define KALLSYMS_MAIN kallsyms_main_32	/* 32 bit version */
#elif defined(COMMON_3264) && defined(ONLY_64)
#define KALLSYMS_MAIN kallsyms_main_64	/* 64 bit version */
#else
#define KALLSYMS_MAIN kallsyms_main	/* Not common code */
#endif

int KALLSYMS_MAIN (int argc, char **argv)
{
    struct option long_opts[] = {
	    {"version", 0, 0, 'V'},
	    {"help", 0, 0, 'h'},
	    {0, 0, 0, 0}
    };
    char *filename = NULL;
    int fp;
    struct obj_file *fin, *fout;
    int i, c;

    error_file = "kallsyms";

    /* To handle repeated calls from combined modprobe */
    errors = optind = 0;

    /* Process the command line.  */
    while ((c = getopt_long(argc, argv, "Vh",
			    &long_opts[0], NULL)) != EOF)
	switch (c) {
	case 'V':
	    fputs("kallsyms version " MODUTILS_VERSION "\n", stderr);
	    return(0);
	case 'h':       /* Print the usage message. */
	    kallsyms_usage();
	    return(0);
	default:
	    kallsyms_usage();
	    return(1);
	}

    if (optind != argc-1) {
	kallsyms_usage();
	return(1);
    }

    filename = argv[optind++];
    error_file = filename;
    if ((fp = gzf_open(filename, O_RDONLY)) < 0) {
	error("%s: %m", filename);
	return 1;
    }

    if ((fin = obj_load(fp, ET_EXEC, filename)) == NULL) {
	gzf_close(fp);
	return 1;
    }
    gzf_close(fp);

    error_file = "kallsyms";
    if (obj_kallsyms(fin, &fout))
	return 1;

    /* Write the extracted data */
    fwrite(&fout->header, sizeof(fout->header), 1, stdout);
    for (i = 0; i < fout->header.e_shnum; ++i)
	fwrite(&fout->sections[i]->header, fout->header.e_shentsize, 1, stdout);
    for (i = 0; i < fout->header.e_shnum; ++i) {
	if (fout->sections[i]->header.sh_size) {
	    fseek(stdout, fout->sections[i]->header.sh_offset, SEEK_SET);
	    fwrite(fout->sections[i]->contents,
	    	fout->sections[i]->header.sh_size, 1, stdout);
	}
    }

    return 0;
}

/* For common 3264 code, add an overall kallsyms_main, in the 64 bit version. */
#if defined(COMMON_3264) && defined(ONLY_64)
int kallsyms_main (int argc, char **argv)
{
    if (arch64())
	return kallsyms_main_64(argc, argv);
    else
	return kallsyms_main_32(argc, argv);
}
#endif	/* defined(COMMON_3264) && defined(ONLY_64) */


/* For common 3264 code, only compile main in the 64 bit version. */
#if defined(COMMON_3264) && defined(ONLY_32)
/* Use the main in the 64 bit version */
#else
/* Not common 3264 code, only need main if not combined with insmod */
#ifndef COMBINE_kallsyms
int main(int argc, char **argv)
{
    return(kallsyms_main(argc, argv));
}
#endif	/* COMBINE_kallsyms */
#endif	/* defined(COMMON_3264) && defined(ONLY_32) */
