/*
 * Modprobe
 *
 * Copyright 1994, 1995, 1996, 1997:
 *	Jacques Gelinas <jack@solucorp.qc.ca>
 *	Björn Ekwall <bj0rn@blox.se> February 1999
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
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>
#include <limits.h>
#include <sys/param.h>
#include <sys/stat.h>
#include "module.h"
#include "obj.h"
#include "modstat.h"
#include "util.h"
#include "version.h"
#include "config.h"

#ifdef COMBINE_modprobe
#define main modprobe_main
#endif

#define FIRST 0
#define LAST 1

typedef struct LINK LINK;

typedef struct NODE {
	struct NODE *next;
	struct NODE *dep; /* list of dependencies for this node */
	char *str;
	char *key; /* the "module name" */
} NODE;

#define MODE_NORMAL 0
#define MODE_ABOVE 1
#define MODE_BELOW 2

typedef struct DESC {
	LINK *name;
	const char *kname;
	const char *objkey;
	NODE *nod;
	LINK *options;
	short int mode;
	short int autoclean;
} DESC;
static char *modename[] = { "NORMAL", "ABOVE", "BELOW" };

struct LINK {
	struct LINK *next;
	union {
		void *v;
		const char *s;
		NODE *n;
		DESC *d;
		GLOB_LIST *g;
	} item;
};


static char *conf_file = NULL;
static int runit = 1;
static int quiet = 0;
static int debug = 0;

static NODE *in_kernel;
static NODE *in_depfile;

/*
 *	Strip the path and extension off a file name
 */
static const char *stripo(const char *fname)
{
	const char *pt = fname;
	char *ptv;
	int len;

	if ((pt = strrchr(fname, '/')) != NULL)
		fname = pt + 1;
	len = strlen(fname);
	if (len > 2 && !strcmp(fname + len - 2, ".o"))
		len -= 2;
	else if (len > 4 && !strcmp(fname + len - 4, ".mod"))
		len -= 4;
#ifdef CONFIG_USE_ZLIB
	else if (len > 5 && !strcmp(fname + len - 5, ".o.gz"))
		len -= 5;
#endif
	else return fname;

	ptv = xmalloc(len + 1);

	strncpy(ptv, fname, len);
	ptv[len] = '\0';
	return ptv;	/* memleak */
}

/*
 *	Return the list of modules to probe for this "alias".
 *	Return NULL if there is none.
 */
static GLOB_LIST *any_probe_list(const char *name)
{
	int i;

	for (i = 0; probe_list && probe_list[i].name; ++i) {
		if (strcmp(probe_list[i].name, name) == 0)
			return probe_list[i].opts;
	}
	return NULL;
}

/*
 *	Return the list of modules to probe for this "alias".
 *	Return NULL if there is none.
 */
static GLOB_LIST *any_probeall_list(const char *name)
{
	int i;

	for (i = 0; probeall_list && probeall_list[i].name; ++i) {
		if (strcmp(probeall_list[i].name, name) == 0)
			return probeall_list[i].opts;
	}
	return NULL;
}

/*
 *	Return the options associated with a module.
 *	Return NULL if there is none.
 */
static OPT_LIST *any_options(const char *mod)
{
	const char *modname;
	int i;

	if (*mod == '/')
		modname = mod;
	else
		modname = stripo(mod);

	for (i = 0; opt_list && opt_list[i].name; ++i) {
		if (strcmp(opt_list[i].name, modname) == 0)
			return opt_list+i;
	}
	return NULL;
}

/*
 *	Check if a module name is indeed an alias for another module.
 *	Return the alias, or NULL if not found.  devfs requires that
 *	alias /dev/xyz* /dev/xyz be valid but that can cause a loop.
 *	Detect this special case and return NULL instead of the same name.
 */
static const char *any_alias(const char *mod)
{
	int i;
	const char *newmod;

	/*
	 * Specification: /etc/modules.conf / alias / format
	 * The format of the alias command in /etc/modules.conf is
	 *	alias alias_name module_name
	 */
	/* For devfs */
	if (*mod != '/') {
		const char *modname = stripo(mod);

		for (i = 0; aliases && aliases[i].name; i++) {
			if (strcmp(aliases[i].name, modname) == 0) {
				if (aliases[i].opts && aliases[i].opts->pathc)
					return aliases[i].opts->pathv[0];
				break;
			}
		}
		return NULL;
	}
	/* else maybe devfs, check full name (shell-globbing aliases allowed) */
	for (i = 0; aliases && aliases[i].name; i++) {
		char *p = aliases[i].name;
		const char *q = mod;

		for (; *p && *q; ++p, ++q) {
			if (*p == '*') /* ok break */
				break;
			if (*p != *q && *p != '?') /* failed */
				break;
		}

		if (*p == '*' || (*p == '\0' && *q == '\0')) {
			if (aliases[i].opts && aliases[i].opts->pathc) {
				newmod = aliases[i].opts->pathv[0];
				if (strcmp(mod, newmod))
					return(newmod);
				else
					return(NULL);
			}
			break;
		}
	}
	return NULL;
}

static NODE *lookup(NODE * nod, const char *str)
{
	if (nod)
		do {
			if (strcmp(str, nod->str) == 0)
				break;
		} while ((nod = nod->next) != (NODE *)0);

	return nod;
}

static NODE *lookup_key(NODE * nod, const char *str)
{
	if (nod)
		do {
			if (nod->key && strcmp(str, nod->key) == 0)
				break;
		} while ((nod = nod->next) != (NODE *)0);

	return nod;
}

static GLOB_LIST *extradeps(OPT_LIST *list, const char *mod, const char *path)
{
	OPT_LIST *me;
	const char *name;

	if (list) {
		if (path) {
			name = stripo(path);
			for (me = list; me->name; ++me) {
				if (strcmp(me->name, name) == 0)
					return me->opts;
			}
		}
		/* else */
		name = stripo(mod);
		for (me = list; me->name; ++me) {
			if (strcmp(me->name, name) == 0)
				return me->opts;
		}
	}

	return NULL;
}

static LINK *linkit(int last, void *item, LINK *linkto)
{
	LINK *me = (LINK *)xmalloc(sizeof(LINK));
	me->item.v = item;
	if (last && linkto) {
		LINK *x = linkto;
		while (x->next)
			x = x->next;
		x->next = me;
		me->next = NULL;
		return linkto;
	}
	/* else */
	me->next = linkto;

	return me;
}

/* Forward definition for probe[all] recusrsion.  */
static int modprobe_fromlist(int argc, char *argv[], char *type, int loadall);

static DESC *build_desc(const char *name, const char *objname, int allow_alias)
{
	DESC *desc;
	GLOB_LIST *g;
	OPT_LIST *o;
	NODE *nod = NULL;
	const char *p;
	int aliases = 0, ret = 0;

	if (objname && (nod = lookup(in_depfile, objname)) == NULL)
		return NULL;

	desc = (DESC *)xmalloc(sizeof(DESC));
	desc->name = NULL;
	desc->options = NULL;
	desc->kname = NULL;
	desc->nod = objname ? nod : NULL;
	desc->autoclean = 1;

	for (p = name; p; p = allow_alias ? any_alias(p) : NULL) {
		if (strcmp(p, "off") == 0) {
			desc->objkey = NULL;
			break;
		}
		desc->objkey = p;
		desc->name = linkit(LAST, (void *)p, desc->name);
		if (!(o = any_options(p)))
			continue;

		if (!o->autoclean) desc->autoclean = 0;

		if ((g = o->opts)) {
			desc->options = linkit(FIRST, g, desc->options);
			if (!desc->kname) {
				int i;
				for (i = 0; i < g->pathc; ++i) {
					if (strcmp(g->pathv[i], "-o") == 0) {
						desc->kname = g->pathv[i+1];
						break;
					}
				}
			}
		}
		if (++aliases > 1000) {		/* Arbitrary limit on alias loop */
			allow_alias = 0;
			fprintf(stderr, "modprobe: alias loop detected on %s\n", name);
			break;
		}
	}
	if (!desc->kname)
		desc->kname = desc->objkey;

	if (!desc->nod && desc->objkey)
		desc->nod = lookup_key(in_depfile, desc->objkey);

	/* Iff the result of the above code is not a valid module and is not "off"
	 * and it is mapped to a string which is different than the original name
	 * (aliased) then try probe[all] expansion on the result.  devfs does
	 *   alias           /dev/sg*        /dev/sg
	 *   probeall        /dev/sg         scsi-hosts sg
	 * expecting /dev/sg1 alias -> /dev/sg then probeall on /dev/sg.
	 */
	if (!desc->nod &&			/* no object */
	     desc->objkey &&			/* not "off" */
	     strcmp(name, desc->objkey)) {	/* different name, aliased */
		if ((g = any_probe_list(desc->objkey)))
			ret = modprobe_fromlist(g->pathc, g->pathv, NULL, 0);
		else if ((g = any_probeall_list(desc->objkey)))
			ret = modprobe_fromlist(g->pathc, g->pathv, NULL, 1);
		if (ret)
			desc->objkey = NULL;	/* treat as "off", modprobe_fromlist did the load */
	}

	return desc;
}

/* KG, 2000-11-29: Limit recursion in build_stack() */
#define BSTACKRECMAX 128
static int bstackrecurs;
/*
 * Create a linked list of the stack of modules needed in the kernel
 * in order to satisfy a request for "name"
 * The sort order in the list is "tuned" for insertion or removal.
 * Returns:
 *	OK		0
 *	aliased off	-1
 *	error		-2
 */
static int build_stack(LINK **stack, const char *name, const char *objname,
		       int dir, DESC *rev, int mode, int allow_alias, const char **error_name)
{
	NODE *nod;
	DESC *desc;
	GLOB_LIST *g;
	LINK *lp;
	LINK *prev = NULL;
	int i;
	int r;

	if (error_name)
		*error_name = name;
	if ((desc = build_desc(name, objname, allow_alias)) == NULL)
		return -2;
	if (desc->kname == NULL)
		return -1; /* aliased off */
	if (desc->nod == NULL)
		return -2; /* Not found! */
	desc->mode = mode;

	/* Avoid infinite loops with reverse references ("above") */
	if (rev && strcmp(rev->kname, desc->kname) == 0)
		return 0;

	if (++bstackrecurs > BSTACKRECMAX) {
		fprintf (stderr, "modprobe: Too deep recursion in module dependencies!\n");
		fprintf (stderr, "modprobe: Circular dependency?");
		for (lp = *stack; lp; lp = lp->next)
			fprintf (stderr, " %s", lp->item.d->kname);
		fprintf (stderr, "\n");
		abort ();
	}

	/*
	 * Get the modules that this one should pull in
	 * according to modules.conf ("above")
	 * Handle all levels of aliases (from desc->name)
	 */
	for (lp = desc->name; lp; lp = lp->next) {
		if ((g = extradeps(abovelist, lp->item.s, NULL))) {
			for (i = 0; i < g->pathc; ++i) {
				LINK *up;
				/* Already there? */
				for (up = *stack; up; up = up->next)
					if (strcmp(g->pathv[i], up->item.d->kname) == 0)
						break;
				if (up == NULL) { /* Not already there */
					r = build_stack(stack, g->pathv[i],
							NULL, dir,
							rev ? rev : desc,
							MODE_ABOVE, 1, error_name);
					if (r < 0) {
						bstackrecurs--;
						return r;
					}
				}
			}
		}
	}

	for (lp = *stack; lp; prev = lp, lp = lp->next) {
		if (strcmp(desc->kname, lp->item.d->kname) == 0) {
			/* Avoid infinite loops ("above") */
			if (rev && rev == lp->item.d) {
				bstackrecurs--;
				return 0;
			}
			/* else */
			/* Remove the entry, it is in the wrong place */
			if (prev)
				prev->next = lp->next;
			else
				*stack = lp->next;
			free(lp->item.v);
			free(lp);
			break;
		}
	}

	*stack = linkit(dir, desc, *stack);

	/*
	 * Get the modules that this one depends on
	 * according to modules.conf ("below")
	 * Handle all levels of aliases (from desc->name)
	 */
	for (lp = desc->name; lp; lp = lp->next) {
		if ((g = extradeps(belowlist, lp->item.s, NULL))) {
			for (i = 0; i < g->pathc; ++i) {
				if ((r = build_stack(stack, g->pathv[i],
						NULL,
						dir,
						rev,
						MODE_BELOW, 1, error_name)) < 0) {
					bstackrecurs--;
					return r;
				}
			}
		}
	}

	/*
	 * Get the modules that this one depends on
	 * according to modules.dep.  These are real modules, alias expansion is
	 * not allowed.
	 */
	for (nod = desc->nod->dep; nod; nod = nod->next) {
		if ((r = build_stack(stack, nod->key, nod->str, dir, rev,
			MODE_NORMAL, 0, error_name)) < 0) {
			bstackrecurs--;
			return r;
		}
	}

	bstackrecurs--;
	return 0;
}

/* For debugging */
static void dump_desc(DESC *desc)
{
	GLOB_LIST *g;
	LINK *p = desc->name;
	int i;

	printf("=============================================\n");
	printf("Module %s\n", p->item.s);
	printf("kname %s\n", desc->kname);
	printf("objkey %s\n", desc->objkey);

	printf("names:");
	for (; p; p = p->next)
		printf (" %s", p->item.s);
	printf("\n");

	if (desc->options) {
		LINK *x = desc->options;
		printf("options:");
		for (x = desc->options; x; x = x->next) {
			g = x->item.g;
			for (i = 0; i < g->pathc; ++i)
				printf (" %s", g->pathv[i]);
		}
		printf("\n");
	}
	printf("mode: %s\n", modename[desc->mode]);

	printf("Module matching %s: %s\n", desc->objkey,
		desc->nod ? desc->nod->str : "<none>");
	printf("=============================================\n");

}

static void dump_stack(LINK *stack)
{
	LINK *p;

	for (p = stack; p; p = p->next)
		dump_desc(p->item.d);
}
/* End of debugging support */

/*
 *	Locate all modules matching "match".
 *	Return a GLOB_LIST with found modules.
 *	The caller must free the content of abs_path[].
 */
 /* Restrict search to path[type] or type is NULL (no restriction) */
static GLOB_LIST *config_locate(const char *match, const char *type)
{
	GLOB_LIST *g;
	int i;
	char match_o[PATH_MAX];

	if (!match || !(*match))
		return NULL;

	if (strchr(match, '/') != NULL) {
		char **list = (char **)xmalloc(sizeof(char **));
		g = (GLOB_LIST *)xmalloc(sizeof(GLOB_LIST));
		list[0] = xstrdup(match);
		g->pathv = list;
		g->pathc = 1;
		return g;
	}
	/* else */
	snprintf(match_o, sizeof(match_o), "%s.o", match);
	g = config_lstmod(match_o, type, 0);
	if (g == NULL || g->pathc == 0) {
#ifdef CONFIG_USE_ZLIB
		snprintf(match_o, sizeof(match_o), "%s.o.gz", match);
		g = config_lstmod(match_o, type, 0);
		if (g == NULL || g->pathc == 0)
#endif
		{
			g = config_lstmod((char *)match, type, 0);
			if (g == NULL || g->pathc == 0)
				return NULL;
		}
	}
	/* else */

	/*
	 * The list may contain many duplicates of some module,
	 * for example:
	 * the module slip may be in /lib/modules/default/net
	 * and in /lib/modules/x.y.z/net
	 */
	for (i = 0; i < g->pathc; i++) {
		int j;
		char *check = g->pathv[i];
		char *p;

		if (check == NULL)
			continue;

		if ((p = strrchr(check, '/')) == NULL)
			p = check;
		else
			++p;

		for (j = i + 1; j < g->pathc; j++) {
			if (g->pathv[j]) {
				char *s;

				if ((s = strrchr(g->pathv[j], '/')) == NULL)
					s = g->pathv[j];
				else
					++s;
				if (strcmp(s, p) == 0) {
					free(g->pathv[j]);
					g->pathv[j] = NULL;
				}
			}
		}
	}

	return g;
}

static void show_list( OPT_LIST *list, const char *title, const char *prefix )
{
	GLOB_LIST *g;
	int i;

	if (!list)
		return;

	puts(title);
	for (; list->name; list++) {
		g = list->opts;
		printf("%s %s", prefix, list->name);
		for (i = 0; i < g->pathc; i++)
			printf(" %s", g->pathv[i]);
		printf("\n");
	}
}


/*
 *	Print out the configuration in use
 */
static void config_show()
{
	struct PATH_TYPE *pttb = modpath;
	int i;

	printf("# Generated by modprobe -c (%s)\n", MODUTILS_VERSION);
	for (i = 0; i < nmodpath; i++, pttb++) {
		if (pttb->type != NULL) {
			printf("path[%s]=%s\n", pttb->type, pttb->path);
		} else {
			printf("path=%s\n", pttb->path);
		}
	}

	show_list(prunelist, "# Prune", "prune");
	show_list(abovelist, "# Above", "above");
	show_list(belowlist, "# Below", "below");
	show_list(aliases, "# Aliases", "alias");
	show_list(opt_list, "# Options", "options");
	show_list(probe_list, "# Probes", "probe");
	show_list(probeall_list, "# Probeall", "probeall");

	if (nexecs > 0) {
		puts("# Commands");
		for (i = 0; i < nexecs; i++) {
			switch (execs[i].when) {
			case EXEC_PRE_INSTALL:
				printf("pre-install ");
				break;

			case EXEC_INSTALL:
				printf("install ");
				break;

			case EXEC_POST_INSTALL:
				printf("post-install ");
				break;

			case EXEC_PRE_REMOVE:
				printf("pre-remove ");
				break;

			case EXEC_REMOVE:
				printf("remove ");
				break;

			case EXEC_POST_REMOVE:
				printf("post-remove ");
				break;
			}
			printf("%s %s\n", execs[i].module, execs[i].cmd);
		}
	}

	puts("# Miscellaneous file and directory names");
	for (i = 0; i < gen_file_count; ++i)
		printf("%sfile=%s\n", gen_file[i].base, gen_file[i].name);
	printf("persistdir=%s\n", persistdir);
}

/*
 *	Check if a module needs an external command
 *	while being loaded or unloaded.
 *	Return the command, or NULL if there was no command defined
 */
static const char *exec_cmd(int when, const char *mod)
{
	int i;
	const char *modname = stripo(mod);

	for (i = 0; i < nexecs; i++) {
		if (execs[i].when != when)
			continue;
		if (strcmp(execs[i].module, modname) == 0)
			return execs[i].cmd;
	}
	return NULL;
}

/************************************************/

static NODE *new_NODE(const char *key, const char *_str, NODE ** _head)
{
	NODE *node = (NODE *)xmalloc(sizeof(NODE));

	node->str = xstrdup(_str);
	node->key = xstrdup(key);
	node->next = NULL;
	node->dep = NULL;
	if (*_head) {
		NODE *x = *_head;
		while(x->next)
			x = x->next;
		x->next = node;
	} else
		*_head = node;

	return node;
}

/*
 *	Read the list of modules already loaded in the kernel
 */
static int readcur(void)
{
	int ret = 0;
	struct module_stat *mod;
	int so_far = 0;

	/* delete in_kernel; */
	while (in_kernel) {
		NODE *next = in_kernel->next;
		free(in_kernel);
		in_kernel = next;
	}
	get_kernel_info(0);
	for (mod = module_stat; so_far < n_module_stat; ++so_far, mod++)
		new_NODE(mod->name, mod->name, &in_kernel);

	return ret;
}

/*
 *	Read the dependency file.
 *	The format is like a makefile.
 */
static int read_depfile(void)
{
	FILE *fin;
	struct stat statbuf;
	int ret = 0;
	int line_no;
	int sizebuf;
	char *buf = NULL;
	const char *depfile = gen_file[GEN_DEPFILE].name;

	if ((fin = fopen(depfile, "r")) == NULL) {
		error("Can't open dependencies file %s (%s)",
		      depfile, strerror(errno));
		return -1;
	}

#define EXTREMELY_CAUTIOUS
#ifdef EXTREMELY_CAUTIOUS
	if (fstat(fileno(fin), &statbuf) != 0)
		error("Could not stat %s", depfile);
	else if (config_mtime && config_mtime > statbuf.st_mtime)
		lprintf("Note: %s is more recent than %s",
			config_file, depfile);
#endif

	while (fgets_strip(&buf, &sizebuf, fin, &line_no) != NULL) {
		NODE *nod;
		char line[sizebuf];
		char *pt;
		char *modname;
		int len = strlen(buf);

		pt = line + len-1;

		strcpy(line, buf);	/* safe, same size */
		while (len > 0 && isspace(*pt)) {
			*pt-- = '\0';
			len --;
		}
		if (line[0] == '\0')
			continue;
		pt = line;
		while (isspace(*pt))
			pt++;

		/* Extract the lhs */
		modname = pt;
		while (*pt != ':' && *pt != '\0' && !isspace(*pt))
			pt++;
		if (*pt != ':') {
			error("line %d: Invalid dependency\n\t%s", line_no, line);
			ret = -1;
			break;
		}
		*pt++ = '\0';
		nod = new_NODE(stripo(modname), modname, &in_depfile);

		/* Parse the list of modules */
		while (*pt != '\0') {
			while (isspace(*pt))
				pt++;
			if (*pt > ' ') {
				char *depname = pt;

				while (*pt > ' ')
					pt++;
				if (*pt != '\0')
					*pt++ = '\0';
				new_NODE(stripo(depname), depname, &nod->dep);
			}
		}
	}
	fclose(fin);
	return ret;
}

static int call_rmmod(const char *modname, DESC *desc, int complain)
{
	struct module_stat *m;
	LINK nodesc;
	LINK *head;
	LINK *p;
	int ret = 0;
	int used_ex = 0;
	int i;
	const char *ex;
	const char *kname;

	if (desc == NULL) {
		kname = (char *)stripo(modname);
		nodesc.item.s = kname;
		nodesc.next = NULL;
		head = &nodesc;
	} else {
		kname = desc->kname;
		head = desc->name;
	}

	/*
	 * OK to delete?
	 */
	if (!get_kernel_info(K_INFO | K_REFS))
		return -1;

	for (m = module_stat, i = 0; i < n_module_stat; ++i, ++m) {
		if (strcmp(m->name, kname) == 0) {
			if (m->nrefs != 0 || m->usecount != 0) {
				errno = EBUSY;
				return -1; /* Busy */
			}
			break;
		}
	}
	if (i == n_module_stat)
		return 0; /* It is not even loaded! Easy removal job :-) */

	/* The code below uses system() for commands read from the configuration
	 * file.  It has to use system() because the commands are arbitrary and
	 * may require shell expansion.
	 *
	 * When running as a normal user, you can specify -C config.file and
	 * that file can contain any commands.  The commands are executed with
	 * the normal authority of the user, there is no security exposure.
	 *
	 * When invoked out of kmod, modprobe runs with root authority.  If the
	 * kernel lets user parameters through unchanged then the user could
	 * pass explot strings to modprobe.  The string could start with '-C' to
	 * specify a user config file, modprobe would then issue user commands
	 * as root.  To prevent the use of spurious config files, modprobe run
	 * from kmod runs in safemode and treats the last parameter as a module
	 * name, even if it starts with '-'.  Therefore the user cannot specify
	 * any options to modprobe, only a module name.  When invoked from kmod,
	 * modprobe will only read commands from /etc/modules.conf.  As long as
	 * that file is secure (and we have to assume that it is) then using
	 * system() to invoke commands from the config file is safe.
	 */

	/*
	 * OK to delete!
	 */
	for (p = head; ret == 0 && p; p = p->next) {
		const char *name = p->item.s;
		if ((ex = exec_cmd(EXEC_PRE_REMOVE, name)) != NULL) {
			verbose("# pre-remove %s:\n%s\n", name, ex);
			/* Trusting commands from config file */
			if (runit && system(ex) != 0) {
				if (!quiet && complain)
					error("pre-remove %s failed", name);
				ret = -1;
			}
		}
	}

	for (p = head; ret == 0 && p; p = p->next) {
		const char *name = p->item.s;
		if ((ex = exec_cmd(EXEC_REMOVE, kname)) != NULL) {
			verbose("# remove %s:\n%s\n", name, ex);
			/* Trusting commands from config file */
			if (runit && (ret = system(ex)) != 0) {
				if (!quiet && complain)
					error("remove %s failed", name);
				ret = -1;
			}
			used_ex = 1;
		}
	}

	if (!used_ex && ret == 0) {
		verbose("# delete %s\n", kname);
		if (runit && (ret = delete_module(kname)) < 0)
			if (!quiet && complain)
				perror(kname);
	}

	for (p = head; ret == 0 && p; p = p->next) {
		const char *name = p->item.s;
		if ((ex = exec_cmd(EXEC_POST_REMOVE, name)) != NULL) {
			verbose("# post-remove %s:\n%s\n", name, ex);
			/* Trusting commands from config file */
			if (runit && system(ex) != 0) {
				if (!quiet && complain)
					error("post-remove %s failed", name);
				ret = -1;
			}
		}
	}

	readcur();
	return ret;
}

/*
 * Try to load a module.
 * Return -1 if any error.
 *
 * Parameters:
 *	desc		the module descriptor of the module to be loaded
 *	options		if not NULL, options to the requested module name
 */
static int insmod(DESC *desc, LINK **new_in_kernel, char *options[])
{
	LINK *p;
	int ret = 0;
	int used_ex = 0;
	const char *ex;

	/* Something new for us to do? Or is the module already installed... */
	if (desc == NULL || strcmp(desc->objkey, "null") == 0 ||
	    (runit && lookup_key(in_kernel, desc->kname) != NULL))
		return 0;
	/* else */

	/*
	 * pre-install
	 */
	for (p = desc->name; ret == 0 && p; p = p->next) {
		const char *name = p->item.s;
		if ((ex = exec_cmd(EXEC_PRE_INSTALL, name)) != NULL) {
			verbose("# pre-install %s:\n%s\n", name, ex);
			/* Trusting commands from config file */
			if (runit && (ret = system(ex)) != 0)
				error("pre-install %s failed", name);
		}
	}

	/*
	 * install
	 */
	for (p = desc->name; ret == 0 && p; p = p->next) {
		const char *name = p->item.s;
		if ((ex = exec_cmd(EXEC_INSTALL, name)) != NULL) {
			verbose("# install %s:\n%s\n", name, ex);
			used_ex = 1;
			/* Trusting commands from config file */
			if (runit && (ret = system(ex)) != 0)
				error("install %s failed", name);
		}
	}

	if (ret == 0 && !used_ex) { /* Use the old faithful insmod */
		GLOB_LIST *pg;
		int my_argc = 0;
		int modopts;
		char *my_argv[100]; /* hardcoded, but big enough... */

		/* Locking is _always_ done in insmod now: -L is redundant */
		my_argv[my_argc++] = "/sbin/insmod";
		if (flag_autoclean && desc->autoclean)
			my_argv[my_argc++] = "-k";

		if (quiet)
			my_argv[my_argc++] = "-q";

		if (log)
			my_argv[my_argc++] = "-s";

		if (insmod_opt) {
			char *xopts = xstrdup(insmod_opt); /* leak */
			char *opt = strtok(xopts, " \t");

			while (opt) {
				if (my_argc >= sizeof(my_argv)/sizeof(my_argv[0])) {
					error("Too many arguments for insmod");
					exit(1);
				}
				my_argv[my_argc++] = opt;
				opt = strtok(NULL, " \t");
			}
		}

		if (my_argc >= sizeof(my_argv)/sizeof(my_argv[0])) {
			error("Too many arguments for insmod");
			exit(1);
		}
		my_argv[my_argc++] = desc->nod->str;
		modopts = my_argc; /* index of first module option */
		/*
		 * Handle module parameter options
		 *
		 * Check for aliased module names.
		 * These will override identical options from their
		 * base module option declarations.
		 * Otherwise just add it.
		 */
		for (p = desc->options; p; p = p->next) {
			int n;
			pg = p->item.g;
			for (n = 0; n < pg->pathc; ++n) {
				int j = modopts;
				char *opts = pg->pathv[n];
				char *optend;

				if (strcmp(opts, "-o") == 0) {
					opts = pg->pathv[++n];
					for (; j < my_argc; ++j) {
						if (!strcmp(my_argv[j], "-o")) {
							my_argv[j+1] = opts;
							break;
						}
					}
					if (j != my_argc)
						continue;
					/* else new option */
					if (my_argc >= sizeof(my_argv)/sizeof(my_argv[0])) {
						error("Too many arguments for insmod");
						exit(1);
					}
					my_argv[my_argc++] = "-o";
				} else if ((optend = strchr(opts, '='))) {
					int l = optend - opts + 1;
					char **av = my_argv + modopts;

					for (; j < my_argc; ++j, ++av) {
						if (!strncmp(*av, opts, l)) {
							*av = opts;
							break;
						}
					}
					if (j != my_argc)
						continue;
					/* else new option */
				} else
					break;

				if (my_argc >= sizeof(my_argv)/sizeof(my_argv[0])) {
					error("Too many arguments for insmod");
					exit(1);
				}
				my_argv[my_argc++] = opts;
			}
		}

		/*
		 * Handle command line options: "param=value ..."
		 *
		 * Check if the user wants to override
		 * any of the configuration options.
		 * Otherwise just add it.
		 */
		if (options && strchr(options[0], '=')) {
			int nopt;

			for (nopt = 0; options[nopt]; ++nopt) {
				int j = modopts;
				int l;
				char *optend;
				char **av;

				if (!strchr(options[nopt], '=')) {
					break;
				}
				/* else */
				optend = strchr(options[nopt], '=');
				l = optend - options[nopt] + 1;
				av = my_argv + modopts;

				for (; j < my_argc; ++j, ++av) {
					if (!strncmp(*av, options[nopt], l)) {
						*av = options[nopt];
						break;
					}
				}

				if (j == my_argc) /* new option */ {
					if (my_argc >= sizeof(my_argv)/sizeof(my_argv[0])) {
						error("Too many arguments for insmod");
						exit(1);
					}
					my_argv[my_argc++] = options[nopt];
				}
			}
		}

		if (my_argc >= sizeof(my_argv)/sizeof(my_argv[0])) {
			error("Too many arguments for insmod");
			exit(1);
		}
		my_argv[my_argc] = NULL;	/* for execvp */

		if (verbose) {
			int i;
			char cmd[2000]; /* hardcoded, but big enough... */

			cmd[0] = '\0';
			for (i = 0; i < my_argc; ++i) {
				if ((strlen(cmd) + strlen(my_argv[i]) + 2) >= sizeof(cmd)) {
					if ((strlen(cmd) + 5) >= sizeof(cmd))
						cmd[sizeof(cmd)-5] = '\0';
					xstrcat(cmd, " ...", sizeof(cmd));
					break;
				}
				xstrcat(cmd, my_argv[i], sizeof(cmd));
				if (i != my_argc - 1)
					xstrcat(cmd, " ", sizeof(cmd));
			}
			verbose("%s\n", cmd);
		}

#ifdef COMBINE_modprobe
		if (runit) {
			int insmod_main(int argc, char **argv);
			int flag_autoclean_save = flag_autoclean;

			flag_autoclean = 0;
			ret = insmod_main(my_argc, my_argv);
			flag_autoclean = flag_autoclean_save;
		}
#else
		if (runit)
			ret = xsystem(my_argv[0], my_argv);
#endif /* COMBINE_modprobe */
		if (!quiet && ret != 0)
			error("insmod %s failed", desc->nod->str);
	}

	/*
	 * post-install
	 */
	for (p = desc->name; ret == 0 && p; p = p->next) {
		const char *name = p->item.s;
		if ((ex = exec_cmd(EXEC_POST_INSTALL, name)) != NULL) {
			verbose("# post-install %s:\n%s\n", name, ex);
			/* Trusting commands from config file */
			if (runit && (ret = system(ex)) != 0)
				error("post-install %s failed", name);
		}
	}

	if (ret == 0)
		*new_in_kernel = linkit(FIRST, desc, *new_in_kernel);

	readcur();
	return ret;
}

/*
 *	Unload a module and whatever modules was required by this module.
 *	We blindly remove everything in order, even if a module is needed
 *	by another module. The idea is that this module will refuse to
 *	unload.
 *
 *	Return -1 if the module named on the command line could not be unloaded.
 */
static int unload(const char *name)
{
	GLOB_LIST *g;
	LINK *stack = NULL;
	LINK *p;
	const char *mod;
	int ret = 0;

	if (name == NULL)
		return ret;
	/* else */
	mod = stripo(name);

	if ((g = any_probe_list(mod)) || (g = any_probeall_list(mod))) {
		int i;
		int how;

		for (i = 0; i < g->pathc; ++i)
			if ((how = unload(g->pathv[i])))
				ret = how;

		return ret;
	}
	/* else */

	ret = build_stack(&stack, mod, NULL, 1, NULL, MODE_NORMAL, 1, NULL);

	if (debug)
		dump_stack(stack);

	if (ret == -1)
		return 0; /* aliased off */
	else if (ret < 0) /* Unknown */
		/*
		 * #Specification: modprobe -r / unknown module
		 *	If there is no information about a module in
		 *	the dependancy file, we simply try to remove
		 *	the module without further checking.
		 */
		return call_rmmod(mod, NULL, 1);
	/* else */
	for (p = stack; p; p = p->next) {
		DESC *desc = p->item.d;
		int want_del;

		if (!lookup_key(in_kernel, desc->kname))
			continue; /* Not loaded */
		want_del = (strcmp(mod, desc->kname) == 0);
		if (call_rmmod(desc->kname, desc, want_del) && want_del)
			ret = -1;
	}

	return ret;
}

/*
 * Try to load a stack of modules.
 * If a module can't be loaded then undo everything.
 *
 * Returns:
 *	Install failed:	-3	asked_for points to the requested module node
 *	Unknown module:	-2
 *	Aliased off:	-1
 *	Install OK:	0	asked_for points to the requested module node
 *
 */
static int probe_stack(const char *name, const char *obj, char **options,
		       DESC **asked_for, const char **error_name)
{
	LINK *stack;
	LINK *p;
	LINK *new_in_kernel;
	int status;

	new_in_kernel = stack = NULL;

	if ((status = build_stack(&stack, name, obj, 0, NULL, MODE_NORMAL, 1, error_name)) < 0)
		return status;

	if (debug)
		dump_stack(stack);

	for (status = 0, p = stack; p; p = p->next) {
		DESC *desc = p->item.d;
		const char *this_name = desc->name->item.s;
		char **these_options = NULL;

		if (strcmp(name, this_name) == 0) {
			*asked_for = desc;
			if (status)
				break;
			these_options = options;
		}

		if (!status && insmod(desc, &new_in_kernel, these_options)) {
			/*
			 * Failed,
			 * undo work done in this session so far
			 * unless the failure was on a "pull in" module.
			 */
			if (desc->mode != MODE_NORMAL)
				continue;
			/* else */
			while (new_in_kernel) {
				DESC *undo = new_in_kernel->item.d;
				call_rmmod(undo->kname, undo, 0);
				new_in_kernel = new_in_kernel->next;
			}
			status = -3;
		}
	}

	return status;
}

static int modprobe_fromlist(int argc, char *argv[], char *type, int loadall)
{
	static int loaded = 0;
	int ret = 0;
	int i;
	char *name = argv[0];
	const char *error_name = NULL;

	loaded = 0;

	for (i = 0; i < argc; ++i) {
		DESC *desc;
		GLOB_LIST *g;
		NODE *nod;
		char **options;
		char *obj;

		/*
		 * #Specification: modprobe / module option
		 * We can pass options to modules on the command line.
		 * It goes like this:
		 * #
		 * /sbin/modprobe module opt1=value opt2=value [othermodule ...]
		 * #
		 * An option is a keyword followed by an equal sign and a value.
		 * No spaces are allowed in the sequence, unless quoted.
		 *
		 * The option list ends at the end of the list or at the
		 * first non-option argument (a possible next module).
		 */
		if (strchr(argv[i], '=') != NULL)
			continue;

		/* else: argv[i] is a module name, not an option */
		name = argv[i];
		if (i + 1 < argc && strchr(argv[i + 1], '='))
			options = argv + i + 1;
		else
			options = NULL;

		if (type || strpbrk(name, SHELL_META)) {
			int alt = 0;

			g = config_locate(name, type);
			if (!g || g->pathc == 0) {
				ret = -2;	/* unknown module */
				continue;
			}

			do {
				desc = NULL;
				obj = g->pathv[alt];
				if ( obj != NULL ) {
					ret = probe_stack(stripo(g->pathv[alt]), obj, options, &desc, &error_name);
					if (ret >= -1) /* Some success */
						++loaded;
				} else {
					ret = -2;
					error_name = NULL;
				}
			} while (++alt < g->pathc && (ret < -1 || loadall));
		} else if ((g = any_probe_list(name))) {
			ret = modprobe_fromlist(g->pathc, g->pathv, NULL, 0);
		} else if ((g = any_probeall_list(name))) {
			ret = modprobe_fromlist(g->pathc, g->pathv, NULL, 1);
		} else {
			obj = NULL;

			/* probe all possible stacks with this name */
			do {
				desc = NULL;
				ret = probe_stack(name, obj, options, &desc, &error_name);
				if (ret >= -1) /* Some success */
					++loaded;
			} while (ret == -3 && /* Ouch, failed install */
				 /* Did we try a valid stack? */
				 desc && desc->objkey && desc->nod &&
				 /* Are there more modules to try? */
				 (nod = desc->nod->next) &&
				 /* With the same key? */
				 (nod = lookup_key(nod, desc->objkey)) &&
				 /* Get the name of the next object file */
				 (obj = nod->str)); /* Yes, really!!! */
		}

		if (!loadall && loaded > 0)
			return 0;
		/* Otherwise, just continue trying for more */

		readcur();
	}

	if (loaded > 0)
		return 0;
	/* else we failed. Why? */
	if (ret == -2) {
		if (error_name && error_name != name)
			error("Can't locate module %s which is needed for %s", error_name, name);
		else if (!quiet)
			error("Can't locate module %s", name);
	}
	else
		error("insmod %s failed", name);
	return -1;
}

/*
 *	Print all available module matching "pattern" and of a certain type.
 *	type may be NULL.
 */
static void modprobe_printlist(char *pattern, char *type)
{
	GLOB_LIST *g = config_lstmod(pattern, type, 0);
	int i;

	if (g)
		for (i = 0; i < g->pathc; i++)
			printf("%s\n", g->pathv[i]);
}

static void modprobe_nothing(char *str)
{
	error("Nothing to %s ???\n"
		     "Specify at least a module or a wildcard like \\*", str);
}

static void usage(void)
{
	fprintf(stderr,
		"modprobe " MODUTILS_VERSION "\n"
		"Load/Unload modules with dependencies\n"
		"\n"
		"Load module(s):\n"
		"  modprobe [-a -n -v ] [-C config ] [ -t type ] pattern OR module1 module2 ...\n"
		"List modules:\n"
		"  modprobe [-l ] [-C config ] [ -t type ] pattern\n"
		"   note: wildcard patterns should be escaped\n"
		"Show configuration:\n"
		"  modprobe [-C config ] -c\n"
		"Remove module(s) or autoclean:\n"
		"  modprobe [-C config ] -r [ module ...]\n"
		"\n"
		"options:\n"
		"\t-a, --all                  Load _all_ matching modules\n"
		"\t-c, --showconfig           Show current configuration\n"
		"\t-d, --debug                Print debugging information\n"
		"\t-h, --help                 Print this message\n"
		"\t-k, --autoclean            Set 'autoclean' on loaded modules\n"
		"\t-l, --list                 List matching modules\n"
		"\t-n, --show                 Don't actually perform the action\n"
		"\t-q, --quiet                Quiet operation\n"
		"\t-r, --remove               Remove module (stacks) or do autoclean\n"
		"\t-s, --syslog               Use syslog to report\n"
		"\t-t, --type moduletype      Only look for modules of this type\n"
		"\t-v, --verbose              Print all commands\n"
		"\t-V, --version              Show version\n"
		"\t-C, --config configfile    Use instead of /etc/modules.conf\n"
	    );
}

int main(int argc, char *argv[])
{
	int ret = 0;
	int loadall = 0; /* Load only one module out of a list */
	char *type = NULL; /* Search in all path[] */
	int remove = 0;
	int showconfig = 0;
	int list = 0;
	int o;
	char **env;
	struct option long_opts[] = {
		{"type", 1, 0, 't'},
		{"all", 0, 0, 'a'},
		{"debug", 0, 0, 'd'},
		{"showconfig", 0, 0, 'c'},
		{"list", 0, 0, 'l'},
		{"show", 0, 0, 'n'},
		{"remove", 0, 0, 'r'},
		{"verbose", 0, 0, 'v'},
		{"version", 0, 0, 'V'},
		{"autoclean", 0, 0, 'k'},
		{"syslog", 0, 0, 's'},
		{"config", 1, 0, 'C'},
		{"quiet", 1, 0, 'q'},
		{"help", 0, 0, 'h'},
		{0, 0, 0, 0}
	};
	int i, l = 1;
	char *command;

	for (i = 0; i < argc; ++i)
		l += strlen(argv[i]) + 1;
	command = alloca(l);
	*command = '\0';
	for (i = 0; i < argc; ++i) {
		strcat(command, argv[i]);
		strcat(command, " ");
	}

	error_file = "modprobe";

	/* Check for safemode before doing anything else, it affects the
	 * meaning of the parameters.  If the environment contains exactly
	 * "HOME=/", "TERM=linux", "PATH=/sbin:/usr/sbin:/bin:/usr/bin"
	 * then assume modprobe was invoked from kmod and default to safemode,
	 * this should handle existing 2.2 and 2.4 kernels.
	 *
	 * If euid != uid then use safe mode.
	 *
	 * Otherwise assume that we are invoked by a real user, use unsafe
	 * mode with their authority.
	 *
	 * In safe mode the last parameter _must_ be a module name.  No other
	 * module names or variable=value strings are allowed in safe mode.
	 */
	safemode = 1;
	for (env = environ; *env; ++env) {
		if (strcmp(*env, "HOME=/") == 0)
			continue;
		if (strcmp(*env, "TERM=linux") == 0)
			continue;
		if (strcmp(*env, "PATH=/sbin:/usr/sbin:/bin:/usr/bin") == 0)
			continue;
		safemode = 0;
		break;
	}
	if (!safemode && getuid() != geteuid())
		safemode = 1;
	if (safemode)
		--argc;		/* Do not scan last parameter in getopt */

	while ((o = getopt_long(argc, argv, "t:acdhlnqrvksC:V",
				&long_opts[0], NULL)) != EOF) {
		switch (o) {
		case 't': /* type of module */
			type = optarg;
			break;

		case 'a':
			loadall = 1;
			break;

		case 'c':
			showconfig = 1;
			break;

		case 'd':
			debug = 1;
			break;
		case 'h':
			usage();
			return 0;
			break;
		case 'l':
			list = 1;
			break;

		case 'n':
			runit = 0;
			break;

		case 'q':
			quiet = 1;
			break;

		case 'r':
			remove = 1;
			break;

		case 'v':
			flag_verbose = 1;
			break;

		case 'k':
			flag_autoclean = 1;
			quiet = 1;
			break;

		case 's':
			setsyslog("modprobe");
			break;

		case 'C':
			conf_file = optarg;
			break;

		case 'V':
			printf("modprobe version %s\n",
			       MODUTILS_VERSION);
			break;

		default:
			ret = -1;
			break;
		}
	}

	if (ret == -1) {
		usage();
		return -1;
	}
	/* else */

	if (config_read(1, NULL, "", conf_file) == -1)
		return -1;
	/* else */
	new_NODE("null", "null", &in_depfile);
	if (read_depfile() == -1)
		return -1;
	/* else */
	if (readcur() == -1)
		return -1;
	/* else */

	argc -= optind;
	argv += optind;
	if (safemode) {
		/* Now scan the last parameter, as a module name */
		if (++argc != 1) {
			error("Safe mode has more than one parameter");
			exit(1);
		}
		if (**argv == '-') {
			error("Safe mode parameter starts with '-'");
			exit(1);
		}
		if (strchr(*argv, '=')) {
			error("Safe mode parameter contains '='");
			exit(1);
		}
	}

	/*
	 * argv now points to the first non-option argument
	 * argc is the remaining argument count
	 */
	if (showconfig)
		config_show();
	else if (remove) {
		if (runit)
			snap_shot_log("start %ssafemode=%d", command, safemode);
		if (argc > 0) {
			int errs;
			for (errs = 0; argc > 0; ++argv, --argc) {
				if (unload(*argv)) {
					if (!quiet)
						perror(*argv);
					++errs;
				}
			}
			ret = errs;
		} else {
			/*
			 * Clean up "autoclean" modules, allowing the
			 * use of any pre-/post-remove entries in
			 * /etc/modules.conf
			 *
			 * This means that the kerneld autoremoval can
			 * be replaced with "modprobe -r" via crontab.
			 * Much better than "rmmod -a"...
			 */
			struct module_stat *m;
			int i;

			if (!get_kernel_info(K_INFO | K_REFS)) {
				if (runit)
					snap_shot_log("get_kernel_info failed");
				return 1;
			}
			for (m = module_stat, i = 0; i < n_module_stat; ++i, ++m) {
				if ((m->flags & NEW_MOD_AUTOCLEAN) &&
				    ((m->flags & NEW_MOD_VISITED) == 0) &&
				    (m->flags & NEW_MOD_USED_ONCE) &&
				    (m->nrefs == 0) &&
				    (m->usecount == 0)) {
					ret = call_rmmod(m->name, NULL, 0);
				}
			}
			/*
			 * Prepare for the next run by unsetting the VISITED
			 * flag on all "autoclean" modules that can be removed
			 */
			verbose("# autoclean\n");
			if (runit && delete_module(NULL)) {
				int save_errno = errno;
				perror("rmmod");
				errno = save_errno;
				if (runit)
					snap_shot_log("delete_module(NULL) failed %m");
				return 1;
			}
		}
		if (runit)
			snap_shot_log("rmmod returned %d", ret);
	} else if (list) {
		if (argc > 0)
			for (; argc > 0 && ret == 0; ++argv, --argc) {
				modprobe_printlist(*argv, type);
			}
		else
			modprobe_printlist("*", type);
	} else { /* probe module list */
		if (runit)
			snap_shot_log("start %ssafemode=%d", command, safemode);
		if (argc > 0) {
			ret = modprobe_fromlist(argc, argv, type, loadall);
		}
		else
			modprobe_nothing("load");
		if (runit)
			snap_shot_log("probe ended");
	}

	return ret;
}
