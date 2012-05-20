/*
 * Display the symbols exported from the running kernel.
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

#include <unistd.h>
#include <getopt.h>

#include "module.h"
#include "version.h"
#include "util.h"
#include "obj.h"
#include "modstat.h"

#ifdef COMBINE_ksyms
#define main ksyms_main
#endif

void ksyms_usage(void)
{
	fputs("Usage:\n"
	      "ksyms [-ahm?V]\n"
	      "\n"
	      " -a, --all      Display all symbols\n"
	      " -h, --noheader Suppress the column header\n"
	      " -m, --info     Display module information\n"
	      " -H, --help     Print this message\n"
	      " -V, --version  Print the release version\n"
	      ,stderr);
}

/*FIXME: A non-root ksyms: copy the output from /proc/ksyms */
int main(int argc, char **argv)
{
	struct module_stat *m;
	struct module_symbol *s;
	size_t i;
	size_t j;
	int flag_allsyms = 0;
	int flag_mod_info = 0;
	int flag_print_header = 1;

	struct option long_opts[] = {
		{"all", 0, 0, 'a'},
		{"info", 0, 0, 'm'},
		{"noheader", 0, 0, 'h'},
		{"version", 0, 0, 'V'},
		{"help", 0, 0, 'H'},
		{0, 0, 0, 0}
	};

	error_file = "ksyms";

	while ((i = getopt_long(argc, argv, "amhVH",
				&long_opts[0], NULL)) != EOF)
		switch (i) {
		case 'a':
			flag_allsyms = 1;
			break;
		case 'm':
			flag_mod_info = 1;
			break;
		case 'h':
			flag_print_header = 0;
			break;
		case 'V':
			fputs("ksyms version " MODUTILS_VERSION "\n", stderr);
			break;
		case 'H':
			ksyms_usage();
			return 0;
		default:
			ksyms_usage();
			return 1;
		}

	if (!get_kernel_info(K_SYMBOLS | K_INFO))
		return 1;

	if (flag_print_header)
		printf("%-*s  %-32s  Defined by\n", (int) (2 * sizeof(void *)),
		       "Address", "Symbol");

	/*
	 * Iterate over the modules, in order,
	 * and care for their symbols.
	 */
	for (i = 0, m = module_stat; i < n_module_stat; ++i, ++m) {
		if (flag_mod_info) {
			int o;

			o = printf("%0*lx  (%luk)",
				(int) (2 * sizeof(void *)),
				(tgt_long)m->addr,
				(m->size / 1024) + ((m->size % 1024) != 0));
			o = 2 * sizeof(void *) + 2 + 32 + 2 - o;
			printf("%*s[%s]\n", o, "", m->name);
		}

		for (j = 0, s = m->syms; j < m->nsyms; ++j, ++s)
			printf("%0*lx  %-32s  [%s]\n",
				(int) (2 * sizeof(void *)),
				s->value,
				(char *)s->name,
				m->name);
	}

	if (flag_allsyms) {
		/*
		 * Show kernel resident symbols
		 */
		for (i = 0, s = ksyms; i < nksyms; ++i, ++s)
			printf("%0*lx  %-32s\n",
			       (int) (2 * sizeof(void *)),
			       s->value,
			       (char *)s->name);
	}

	return 0;
}
