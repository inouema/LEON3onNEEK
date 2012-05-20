/*
 * List the currently loaded modules.
 *
 * New re-implementation by Björn Ekwall <bj0rn@blox.se> February 1999.
 * Inspired by work contributed by Richard Henderson <rth@tamu.edu>
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
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <getopt.h>

#include "module.h"
#include "util.h"
#include "obj.h"
#include "modstat.h"
#include "version.h"

#ifdef COMBINE_lsmod
#define main lsmod_main
#endif

void lsmod_usage(void)
{
	fputs("Usage:\n"
	      "lsmod [-Vh]\n"
	      "\n"
	      " -V, --version    Print the release version\n"
	      " -h, --help       Print this message\n"
	      ,stderr);
}

int main(int argc, char **argv)
{
	struct module_stat *m;
	int i;
	int j;
	int tainted = 0;
	FILE *f;

	struct option long_opts[] = {
	  {"version", 0, 0, 'V'},
	  {"help", 0, 0, 'h'},
	  {0, 0, 0, 0}
	};

	error_file = "lsmod";

	while ((i = getopt_long(argc, argv, "Vh",
				&long_opts[0], NULL)) != EOF)
		switch(i) {
		case 'V':
			fputs("lsmod version " MODUTILS_VERSION "\n",stderr);
			return 0;
		case 'h':
			lsmod_usage();
			return 0;
		default:
			lsmod_usage();
			return 1;
		}

	if ((f = fopen(TAINT_FILENAME, "r"))) {
		fscanf(f, "%d", &tainted);
		fclose(f);
	}

	/* A header.  */
	printf("Module                  Size  Used by    ");
	if (f) {
		if (tainted) {
			printf("Tainted: %c%c%c",
				tainted & TAINT_PROPRIETORY_MODULE	? 'P' : 'G',
				tainted & TAINT_FORCED_MODULE		? 'F' : ' ',
				tainted & TAINT_UNSAFE_SMP		? 'S' : ' ');
		}
		else
			printf("Not tainted");
	}
	printf("\n");

	if (getuid() != 0) {
		int fd;
		char line[100];

		fflush(stdout);

		/*FIXME: non-root format... */
		if ((fd = open("/proc/modules", O_RDONLY)) >= 0 ) {
			while ((i = read(fd, line, 100)) > 0)
				write(1, line, i);
			close(fd);
			return 0;
		}
		perror("/proc/modules");
		return 1;
	}

	if (!get_kernel_info(K_INFO | K_REFS))
		return 1;

	for (i = 0, m = module_stat; i < n_module_stat; ++i, ++m) {
		printf("%-20s%8lu%4ld ", m->name, m->size, m->usecount);

		if (m->flags & NEW_MOD_DELETED)
			fputs(" (deleted)", stdout);
		else if (m->flags & NEW_MOD_INITIALIZING)
			fputs(" (initializing)", stdout);
		else if (!(m->flags & NEW_MOD_RUNNING))
			fputs(" (uninitialized)", stdout);
		else {
			if (m->flags & NEW_MOD_AUTOCLEAN)
				fputs(" (autoclean)", stdout);
			if (!(m->flags & NEW_MOD_USED_ONCE))
				fputs(" (unused)", stdout);
		}

		if (m->nrefs > 0) {
			struct module_stat *mr;

			putchar(' ');
			putchar('[');
			for (j = 0; j < m->nrefs; ++j) {
				mr = m->refs[j];
				fputs(mr->name, stdout);
				if (j != m->nrefs - 1)
					putchar(' ');
			}
			putchar(']');
		}
		putchar('\n');
	}

	return 0;
}
