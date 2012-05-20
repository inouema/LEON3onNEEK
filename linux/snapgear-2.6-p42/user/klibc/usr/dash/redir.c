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

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/param.h>	/* PIPE_BUF */
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

/*
 * Code for dealing with input/output redirection.
 */

#include "main.h"
#include "shell.h"
#include "nodes.h"
#include "jobs.h"
#include "options.h"
#include "expand.h"
#include "redir.h"
#include "output.h"
#include "memalloc.h"
#include "error.h"


#define EMPTY -2		/* marks an unused slot in redirtab */
#ifndef PIPE_BUF
# define PIPESIZE 4096		/* amount of buffering in a pipe */
#else
# define PIPESIZE PIPE_BUF
#endif


MKINIT
struct redirtab {
	struct redirtab *next;
	int renamed[10];
	int nullredirs;
};


MKINIT struct redirtab *redirlist;
MKINIT int nullredirs;

STATIC int openredirect(union node *);
#ifdef notyet
STATIC void dupredirect(union node *, int, char[10]);
#else
STATIC void dupredirect(union node *, int);
#endif
STATIC int openhere(union node *);
STATIC int noclobberopen(const char *);


/*
 * Process a list of redirection commands.  If the REDIR_PUSH flag is set,
 * old file descriptors are stashed away so that the redirection can be
 * undone by calling popredir.  If the REDIR_BACKQ flag is set, then the
 * standard output, and the standard error if it becomes a duplicate of
 * stdout, is saved in memory.
 */

void
redirect(union node *redir, int flags)
{
	union node *n;
	struct redirtab *sv;
	int i;
	int fd;
	int newfd;
	int *p;
#if notyet
	char memory[10];	/* file descriptors to write to memory */

	for (i = 10 ; --i >= 0 ; )
		memory[i] = 0;
	memory[1] = flags & REDIR_BACKQ;
#endif
	nullredirs++;
	if (!redir) {
		return;
	}
	sv = NULL;
	INTOFF;
	if (flags & REDIR_PUSH) {
		struct redirtab *q;
		q = ckmalloc(sizeof (struct redirtab));
		q->next = redirlist;
		redirlist = q;
		q->nullredirs = nullredirs - 1;
		for (i = 0 ; i < 10 ; i++)
			q->renamed[i] = EMPTY;
		nullredirs = 0;
		sv = q;
	}
	n = redir;
	do {
		fd = n->nfile.fd;
		if ((n->nfile.type == NTOFD || n->nfile.type == NFROMFD) &&
		    n->ndup.dupfd == fd)
			continue; /* redirect from/to same file descriptor */

		newfd = openredirect(n);
		if (fd == newfd)
			continue;
		if (sv && *(p = &sv->renamed[fd]) == EMPTY) {
			int i = fcntl(fd, F_DUPFD, 10);
			if (i == -1) {
				i = errno;
				if (i != EBADF) {
					const char *m = strerror(i);
					close(newfd);
					sh_error("%d: %s", fd, m);
					/* NOTREACHED */
				}
			} else {
				*p = i;
				close(fd);
			}
		} else {
			close(fd);
		}
#ifdef notyet
		dupredirect(n, newfd, memory);
#else
		dupredirect(n, newfd);
#endif
	} while ((n = n->nfile.next));
	INTON;
#ifdef notyet
	if (memory[1])
		out1 = &memout;
	if (memory[2])
		out2 = &memout;
#endif
	if (flags & REDIR_SAVEFD2 && sv && sv->renamed[2] >= 0)
		preverrout.fd = sv->renamed[2];
}


STATIC int
openredirect(union node *redir)
{
	char *fname;
	int f;

	switch (redir->nfile.type) {
	case NFROM:
		fname = redir->nfile.expfname;
		if ((f = open64(fname, O_RDONLY)) < 0)
			goto eopen;
		break;
	case NFROMTO:
		fname = redir->nfile.expfname;
		if ((f = open64(fname, O_RDWR|O_CREAT|O_TRUNC, 0666)) < 0)
			goto ecreate;
		break;
	case NTO:
		/* Take care of noclobber mode. */
		if (Cflag) {
			fname = redir->nfile.expfname;
			if ((f = noclobberopen(fname)) < 0)
				goto ecreate;
			break;
		}
		/* FALLTHROUGH */
	case NCLOBBER:
		fname = redir->nfile.expfname;
		if ((f = open64(fname, O_WRONLY|O_CREAT|O_TRUNC, 0666)) < 0)
			goto ecreate;
		break;
	case NAPPEND:
		fname = redir->nfile.expfname;
		if ((f = open64(fname, O_WRONLY|O_CREAT|O_APPEND, 0666)) < 0)
			goto ecreate;
		break;
	default:
#ifdef DEBUG
		abort();
#endif
		/* Fall through to eliminate warning. */
	case NTOFD:
	case NFROMFD:
		f = -1;
		break;
	case NHERE:
	case NXHERE:
		f = openhere(redir);
		break;
	}

	return f;
ecreate:
	sh_error("cannot create %s: %s", fname, errmsg(errno, E_CREAT));
eopen:
	sh_error("cannot open %s: %s", fname, errmsg(errno, E_OPEN));
}


STATIC void
#ifdef notyet
dupredirect(redir, f, memory)
#else
dupredirect(redir, f)
#endif
	union node *redir;
	int f;
#ifdef notyet
	char memory[10];
#endif
	{
	int fd = redir->nfile.fd;

#ifdef notyet
	memory[fd] = 0;
#endif
	if (redir->nfile.type == NTOFD || redir->nfile.type == NFROMFD) {
		if (redir->ndup.dupfd >= 0) {	/* if not ">&-" */
#ifdef notyet
			if (memory[redir->ndup.dupfd])
				memory[fd] = 1;
			else
#endif
				copyfd(redir->ndup.dupfd, fd);
		}
		return;
	}

	if (f != fd) {
		copyfd(f, fd);
		close(f);
	}
	return;
}


/*
 * Handle here documents.  Normally we fork off a process to write the
 * data to a pipe.  If the document is short, we can stuff the data in
 * the pipe without forking.
 */

STATIC int
openhere(union node *redir)
{
	int pip[2];
	size_t len = 0;

	if (pipe(pip) < 0)
		sh_error("Pipe call failed");
	if (redir->type == NHERE) {
		len = strlen(redir->nhere.doc->narg.text);
		if (len <= PIPESIZE) {
			xwrite(pip[1], redir->nhere.doc->narg.text, len);
			goto out;
		}
	}
	if (forkshell((struct job *)NULL, (union node *)NULL, FORK_NOJOB) == 0) {
		close(pip[0]);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGHUP, SIG_IGN);
#ifdef SIGTSTP
		signal(SIGTSTP, SIG_IGN);
#endif
		signal(SIGPIPE, SIG_DFL);
		if (redir->type == NHERE)
			xwrite(pip[1], redir->nhere.doc->narg.text, len);
		else
			expandhere(redir->nhere.doc, pip[1]);
		_exit(0);
	}
out:
	close(pip[1]);
	return pip[0];
}



/*
 * Undo the effects of the last redirection.
 */

void
popredir(int drop)
{
	struct redirtab *rp;
	int i;

	if (--nullredirs >= 0)
		return;
	INTOFF;
	rp = redirlist;
	for (i = 0 ; i < 10 ; i++) {
		if (rp->renamed[i] != EMPTY) {
			if (!drop) {
				close(i);
				copyfd(rp->renamed[i], i);
			}
			close(rp->renamed[i]);
		}
	}
	redirlist = rp->next;
	nullredirs = rp->nullredirs;
	ckfree(rp);
	INTON;
}

/*
 * Undo all redirections.  Called on error or interrupt.
 */

#ifdef mkinit

INCLUDE "redir.h"

RESET {
	clearredir(0);
}

#endif

/*
 * Discard all saved file descriptors.
 */

void
clearredir(int drop)
{
	for (;;) {
		nullredirs = 0;
		if (!redirlist)
			break;
		popredir(drop);
	}
}



/*
 * Copy a file descriptor to be >= to.  Returns -1
 * if the source file descriptor is closed, EMPTY if there are no unused
 * file descriptors left.
 */

int
copyfd(int from, int to)
{
	int newfd;

	newfd = fcntl(from, F_DUPFD, to);
	if (newfd < 0) {
		int errno2 = errno;
		if (errno2 == EMFILE)
			return EMPTY;
		else
			sh_error("%d: %s", from, strerror(errno2));
	}
	return newfd;
}


/*
 * Open a file in noclobber mode.
 * The code was copied from bash.
 */
int
noclobberopen(fname)
	const char *fname;
{
	int r, fd;
	struct stat64 finfo, finfo2;

	/*
	 * If the file exists and is a regular file, return an error
	 * immediately.
	 */
	r = stat64(fname, &finfo);
	if (r == 0 && S_ISREG(finfo.st_mode)) {
		errno = EEXIST;
		return -1;
	}

	/*
	 * If the file was not present (r != 0), make sure we open it
	 * exclusively so that if it is created before we open it, our open
	 * will fail.  Make sure that we do not truncate an existing file.
	 * Note that we don't turn on O_EXCL unless the stat failed -- if the
	 * file was not a regular file, we leave O_EXCL off.
	 */
	if (r != 0)
		return open64(fname, O_WRONLY|O_CREAT|O_EXCL, 0666);
	fd = open64(fname, O_WRONLY|O_CREAT, 0666);

	/* If the open failed, return the file descriptor right away. */
	if (fd < 0)
		return fd;

	/*
	 * OK, the open succeeded, but the file may have been changed from a
	 * non-regular file to a regular file between the stat and the open.
	 * We are assuming that the O_EXCL open handles the case where FILENAME
	 * did not exist and is symlinked to an existing file between the stat
	 * and open.
	 */

	/*
	 * If we can open it and fstat the file descriptor, and neither check
	 * revealed that it was a regular file, and the file has not been
	 * replaced, return the file descriptor.
	 */
	 if (fstat64(fd, &finfo2) == 0 && !S_ISREG(finfo2.st_mode) &&
	     finfo.st_dev == finfo2.st_dev && finfo.st_ino == finfo2.st_ino)
	 	return fd;

	/* The file has been replaced.  badness. */
	close(fd);
	errno = EEXIST;
	return -1;
}


int
redirectsafe(union node *redir, int flags)
{
	int err;
	volatile int saveint;
	struct jmploc *volatile savehandler = handler;
	struct jmploc jmploc;

	SAVEINT(saveint);
	if (!(err = setjmp(jmploc.loc) * 2)) {
		handler = &jmploc;
		redirect(redir, flags);
	}
	handler = savehandler;
	if (err && exception != EXERROR)
		longjmp(handler->loc, 1);
	RESTOREINT(saveint);
	return err;
}
