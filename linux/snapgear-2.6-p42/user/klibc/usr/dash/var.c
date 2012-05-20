/*-
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 * Copyright (c) 1997-2005
 *	Herbert Xu <herbert@gondor.apana.org.au>.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <unistd.h>
#include <stdlib.h>
#include <paths.h>

/*
 * Shell variables.
 */

#include "shell.h"
#include "output.h"
#include "expand.h"
#include "nodes.h"	/* for other headers */
#include "eval.h"	/* defines cmdenviron */
#include "exec.h"
#include "syntax.h"
#include "options.h"
#include "mail.h"
#include "var.h"
#include "memalloc.h"
#include "error.h"
#include "mystring.h"
#include "parser.h"
#include "show.h"
#ifndef SMALL
#include "myhistedit.h"
#endif
#include "system.h"


#define VTABSIZE 39


struct localvar *localvars;

const char defpathvar[] =
	"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
#ifdef IFS_BROKEN
const char defifsvar[] = "IFS= \t\n";
#else
const char defifs[] = " \t\n";
#endif

struct var varinit[] = {
#if ATTY
	{ 0,	VSTRFIXED|VTEXTFIXED|VUNSET,	"ATTY\0",	0 },
#endif
#ifdef IFS_BROKEN
	{ 0,	VSTRFIXED|VTEXTFIXED,		defifsvar,	0 },
#else
	{ 0,	VSTRFIXED|VTEXTFIXED|VUNSET,	"IFS\0",	0 },
#endif
	{ 0,	VSTRFIXED|VTEXTFIXED|VUNSET,	"MAIL\0",	changemail },
	{ 0,	VSTRFIXED|VTEXTFIXED|VUNSET,	"MAILPATH\0",	changemail },
	{ 0,	VSTRFIXED|VTEXTFIXED,		defpathvar,	changepath },
	{ 0,	VSTRFIXED|VTEXTFIXED,		"PS1=$ ",	0 },
	{ 0,	VSTRFIXED|VTEXTFIXED,		"PS2=> ",	0 },
	{ 0,	VSTRFIXED|VTEXTFIXED,		"PS4=+ ",	0 },
	{ 0,	VSTRFIXED|VTEXTFIXED,		"OPTIND=1",	getoptsreset },
#ifndef SMALL
	{ 0,	VSTRFIXED|VTEXTFIXED|VUNSET,	"TERM\0",	0 },
	{ 0,	VSTRFIXED|VTEXTFIXED|VUNSET,	"HISTSIZE\0",	sethistsize },
#endif
};

STATIC struct var *vartab[VTABSIZE];

STATIC void mklocal(char *);
STATIC struct var **hashvar(const char *);
STATIC int vpcmp(const void *, const void *);
STATIC struct var **findvar(struct var **, const char *);

/*
 * Initialize the varable symbol tables and import the environment
 */

#ifdef mkinit
INCLUDE <unistd.h>
INCLUDE <sys/types.h>
INCLUDE <sys/stat.h>
INCLUDE "cd.h"
INCLUDE "output.h"
INCLUDE "var.h"
MKINIT char **environ;
INIT {
	char **envp;
	static char ppid[32] = "PPID=";
	const char *p;
	struct stat st1, st2;

	initvar();
	for (envp = environ ; *envp ; envp++) {
		if (strchr(*envp, '=')) {
			setvareq(*envp, VEXPORT|VTEXTFIXED);
		}
	}

	fmtstr(ppid + 5, sizeof(ppid) - 5, "%ld", (long) getppid());
	setvareq(ppid, VTEXTFIXED);

	p = lookupvar("PWD");
	if (p)
		if (*p != '/' || stat(p, &st1) || stat(".", &st2) ||
		    st1.st_dev != st2.st_dev || st1.st_ino != st2.st_ino)
			p = 0;
	setpwd(p, 0);
}
#endif


/*
 * This routine initializes the builtin variables.  It is called when the
 * shell is initialized.
 */

void
initvar(void)
{
	struct var *vp;
	struct var *end;
	struct var **vpp;

	vp = varinit;
	end = vp + sizeof(varinit) / sizeof(varinit[0]);
	do {
		vpp = hashvar(vp->text);
		vp->next = *vpp;
		*vpp = vp;
	} while (++vp < end);
	/*
	 * PS1 depends on uid
	 */
	if (!geteuid())
		vps1.text = "PS1=# ";
}

/*
 * Safe version of setvar, returns 1 on success 0 on failure.
 */

int
setvarsafe(const char *name, const char *val, int flags)
{
	int err;
	volatile int saveint;
	struct jmploc *volatile savehandler = handler;
	struct jmploc jmploc;

	SAVEINT(saveint);
	if (setjmp(jmploc.loc))
		err = 1;
	else {
		handler = &jmploc;
		setvar(name, val, flags);
		err = 0;
	}
	handler = savehandler;
	RESTOREINT(saveint);
	return err;
}

/*
 * Set the value of a variable.  The flags argument is ored with the
 * flags of the variable.  If val is NULL, the variable is unset.
 */

void
setvar(const char *name, const char *val, int flags)
{
	char *p, *q;
	size_t namelen;
	char *nameeq;
	size_t vallen;

	q = endofname(name);
	p = strchrnul(q, '=');
	namelen = p - name;
	if (!namelen || p != q)
		sh_error("%.*s: bad variable name", namelen, name);
	vallen = 0;
	if (val == NULL) {
		flags |= VUNSET;
	} else {
		vallen = strlen(val);
	}
	INTOFF;
	p = mempcpy(nameeq = ckmalloc(namelen + vallen + 2), name, namelen);
	if (val) {
		*p++ = '=';
		p = mempcpy(p, val, vallen);
	}
	*p = '\0';
	setvareq(nameeq, flags | VNOSAVE);
	INTON;
}



/*
 * Same as setvar except that the variable and value are passed in
 * the first argument as name=value.  Since the first argument will
 * be actually stored in the table, it should not be a string that
 * will go away.
 * Called with interrupts off.
 */

void
setvareq(char *s, int flags)
{
	struct var *vp, **vpp;

	vpp = hashvar(s);
	flags |= (VEXPORT & (((unsigned) (1 - aflag)) - 1));
	vp = *findvar(vpp, s);
	if (vp) {
		if (vp->flags & VREADONLY) {
			const char *n;

			if (flags & VNOSAVE)
				free(s);
			n = vp->text;
			sh_error("%.*s: is read only", strchrnul(n, '=') - n,
				 n);
		}

		if (flags & VNOSET)
			return;

		if (vp->func && (flags & VNOFUNC) == 0)
			(*vp->func)(strchrnul(s, '=') + 1);

		if ((vp->flags & (VTEXTFIXED|VSTACK)) == 0)
			ckfree(vp->text);

		flags |= vp->flags & ~(VTEXTFIXED|VSTACK|VNOSAVE|VUNSET);
	} else {
		if (flags & VNOSET)
			return;
		/* not found */
		vp = ckmalloc(sizeof (*vp));
		vp->next = *vpp;
		vp->func = NULL;
		*vpp = vp;
	}
	if (!(flags & (VTEXTFIXED|VSTACK|VNOSAVE)))
		s = savestr(s);
	vp->text = s;
	vp->flags = flags;
}



/*
 * Process a linked list of variable assignments.
 */

void
listsetvar(struct strlist *list, int flags)
{
	struct strlist *lp;

	lp = list;
	if (!lp)
		return;
	INTOFF;
	do {
		setvareq(lp->text, flags);
	} while ((lp = lp->next));
	INTON;
}


/*
 * Find the value of a variable.  Returns NULL if not set.
 */

char *
lookupvar(const char *name)
{
	struct var *v;

	if ((v = *findvar(hashvar(name), name)) && !(v->flags & VUNSET)) {
		return strchrnul(v->text, '=') + 1;
	}
	return NULL;
}



/*
 * Search the environment of a builtin command.
 */

char *
bltinlookup(const char *name)
{
	struct strlist *sp;

	for (sp = cmdenviron ; sp ; sp = sp->next) {
		if (varequal(sp->text, name))
			return strchrnul(sp->text, '=') + 1;
	}
	return lookupvar(name);
}



/*
 * Generate a list of variables satisfying the given conditions.
 */

char **
listvars(int on, int off, char ***end)
{
	struct var **vpp;
	struct var *vp;
	char **ep;
	int mask;

	STARTSTACKSTR(ep);
	vpp = vartab;
	mask = on | off;
	do {
		for (vp = *vpp ; vp ; vp = vp->next)
			if ((vp->flags & mask) == on) {
				if (ep == stackstrend())
					ep = growstackstr();
				*ep++ = (char *) vp->text;
			}
	} while (++vpp < vartab + VTABSIZE);
	if (ep == stackstrend())
		ep = growstackstr();
	if (end)
		*end = ep;
	*ep++ = NULL;
	return grabstackstr(ep);
}



/*
 * POSIX requires that 'set' (but not export or readonly) output the
 * variables in lexicographic order - by the locale's collating order (sigh).
 * Maybe we could keep them in an ordered balanced binary tree
 * instead of hashed lists.
 * For now just roll 'em through qsort for printing...
 */

int
showvars(const char *prefix, int on, int off)
{
	const char *sep;
	char **ep, **epend;

	ep = listvars(on, off, &epend);
	qsort(ep, epend - ep, sizeof(char *), vpcmp);

	sep = *prefix ? spcstr : prefix;

	for (; ep < epend; ep++) {
		const char *p;
		const char *q;

		p = strchrnul(*ep, '=');
		q = nullstr;
		if (*p)
			q = single_quote(++p);

		out1fmt("%s%s%.*s%s\n", prefix, sep, (int)(p - *ep), *ep, q);
	}

	return 0;
}



/*
 * The export and readonly commands.
 */

int
exportcmd(int argc, char **argv)
{
	struct var *vp;
	char *name;
	const char *p;
	char **aptr;
	int flag = argv[0][0] == 'r'? VREADONLY : VEXPORT;
	int notp;

	notp = nextopt("p") - 'p';
	if (notp && ((name = *(aptr = argptr)))) {
		do {
			if ((p = strchr(name, '=')) != NULL) {
				p++;
			} else {
				if ((vp = *findvar(hashvar(name), name))) {
					vp->flags |= flag;
					continue;
				}
			}
			setvar(name, p, flag);
		} while ((name = *++aptr) != NULL);
	} else {
		showvars(argv[0], flag, 0);
	}
	return 0;
}


/*
 * The "local" command.
 */

int
localcmd(int argc, char **argv)
{
	char *name;

	argv = argptr;
	while ((name = *argv++) != NULL) {
		mklocal(name);
	}
	return 0;
}


/*
 * Make a variable a local variable.  When a variable is made local, it's
 * value and flags are saved in a localvar structure.  The saved values
 * will be restored when the shell function returns.  We handle the name
 * "-" as a special case.
 */

STATIC void
mklocal(char *name)
{
	struct localvar *lvp;
	struct var **vpp;
	struct var *vp;

	INTOFF;
	lvp = ckmalloc(sizeof (struct localvar));
	if (name[0] == '-' && name[1] == '\0') {
		char *p;
		p = ckmalloc(sizeof(optlist));
		lvp->text = memcpy(p, optlist, sizeof(optlist));
		vp = NULL;
	} else {
		char *eq;

		vpp = hashvar(name);
		vp = *findvar(vpp, name);
		eq = strchr(name, '=');
		if (vp == NULL) {
			if (eq)
				setvareq(name, VSTRFIXED);
			else
				setvar(name, NULL, VSTRFIXED);
			vp = *vpp;	/* the new variable */
			lvp->flags = VUNSET;
		} else {
			lvp->text = vp->text;
			lvp->flags = vp->flags;
			vp->flags |= VSTRFIXED|VTEXTFIXED;
			if (eq)
				setvareq(name, 0);
		}
	}
	lvp->vp = vp;
	lvp->next = localvars;
	localvars = lvp;
	INTON;
}


/*
 * Called after a function returns.
 * Interrupts must be off.
 */

void
poplocalvars(void)
{
	struct localvar *lvp;
	struct var *vp;

	while ((lvp = localvars) != NULL) {
		localvars = lvp->next;
		vp = lvp->vp;
		TRACE(("poplocalvar %s", vp ? vp->text : "-"));
		if (vp == NULL) {	/* $- saved */
			memcpy(optlist, lvp->text, sizeof(optlist));
			ckfree(lvp->text);
			optschanged();
		} else if ((lvp->flags & (VUNSET|VSTRFIXED)) == VUNSET) {
			unsetvar(vp->text);
		} else {
			if (vp->func)
				(*vp->func)(strchrnul(lvp->text, '=') + 1);
			if ((vp->flags & (VTEXTFIXED|VSTACK)) == 0)
				ckfree(vp->text);
			vp->flags = lvp->flags;
			vp->text = lvp->text;
		}
		ckfree(lvp);
	}
}


/*
 * The unset builtin command.  We unset the function before we unset the
 * variable to allow a function to be unset when there is a readonly variable
 * with the same name.
 */

int
unsetcmd(int argc, char **argv)
{
	char **ap;
	int i;
	int flag = 0;
	int ret = 0;

	while ((i = nextopt("vf")) != '\0') {
		flag = i;
	}

	for (ap = argptr; *ap ; ap++) {
		if (flag != 'f') {
			i = unsetvar(*ap);
			ret |= i;
			if (!(i & 2))
				continue;
		}
		if (flag != 'v')
			unsetfunc(*ap);
	}
	return ret & 1;
}


/*
 * Unset the specified variable.
 */

int
unsetvar(const char *s)
{
	struct var **vpp;
	struct var *vp;
	int retval;

	vpp = findvar(hashvar(s), s);
	vp = *vpp;
	retval = 2;
	if (vp) {
		int flags = vp->flags;

		retval = 1;
		if (flags & VREADONLY)
			goto out;
		if (flags & VUNSET)
			goto ok;
		if ((flags & VSTRFIXED) == 0) {
			INTOFF;
			if ((flags & (VTEXTFIXED|VSTACK)) == 0)
				ckfree(vp->text);
			*vpp = vp->next;
			ckfree(vp);
			INTON;
		} else {
			setvar(s, 0, 0);
			vp->flags &= ~VEXPORT;
		}
ok:
		retval = 0;
	}

out:
	return retval;
}



/*
 * Find the appropriate entry in the hash table from the name.
 */

STATIC struct var **
hashvar(const char *p)
{
	unsigned int hashval;

	hashval = ((unsigned char) *p) << 4;
	while (*p && *p != '=')
		hashval += (unsigned char) *p++;
	return &vartab[hashval % VTABSIZE];
}



/*
 * Compares two strings up to the first = or '\0'.  The first
 * string must be terminated by '='; the second may be terminated by
 * either '=' or '\0'.
 */

int
varcmp(const char *p, const char *q)
{
	int c, d;

	while ((c = *p) == (d = *q)) {
		if (!c || c == '=')
			goto out;
		p++;
		q++;
	}
	if (c == '=')
		c = 0;
	if (d == '=')
		d = 0;
out:
	return c - d;
}

STATIC int
vpcmp(const void *a, const void *b)
{
	return varcmp(*(const char **)a, *(const char **)b);
}

STATIC struct var **
findvar(struct var **vpp, const char *name)
{
	for (; *vpp; vpp = &(*vpp)->next) {
		if (varequal((*vpp)->text, name)) {
			break;
		}
	}
	return vpp;
}
