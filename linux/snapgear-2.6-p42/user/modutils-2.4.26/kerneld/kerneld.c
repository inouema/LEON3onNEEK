/*
 * This is kerneld, the user level handler of kernel requests.
 * Copyright (C) 1995, 1996 Bjorn Ekwall <bj0rn@blox.se>
 * See the file "COPYING" for your rights.
 *
 *
 * The requests arrive on a specific IPC message queue,
 * and the type of the message specifies the request.
 *
 * The message consists of a header followed by "char text[]".
 * The parameter for the request is stored in the "text" field.
 * If the "id" field in the header is non-zero, then the kernel expects
 * an answer, where the message type of the answer should be "id".
 * In the return message, the "id" will contain the status of the request.
 * If the "id" of the request is zero, the kernel does not expect an answer.
 *
 * The "text" field can be used to return any generated information.
 * (See e.g. KERNELD_SYSTEM)
 *
 * (C) Bjorn Ekwall <bj0rn@blox.se> in May 1995
 * This software is placed under the GPL, the text of which can be found
 * in the root directory of this release.
 */
/*
 * Blocking/unblocking of SIGCHLD due to: Eduardo Blanco <ejbs@cs.cs.com.uy>
 * Better error reports by: Lars Fenneberg <in5y050@public.uni-hamburg.de>
 * memmove instead of memcpy: Ton Nijkes <tonn@wau.mis.ah.nl>
 * Kerneld warnings: Steve Dodd <dirk@loth.demon.co.uk>
 */

#define CONFIG_KERNELD
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <syslog.h>
#include <linux/unistd.h>
#include <asm/param.h>
#include <signal.h>
#include <errno.h>
#include <sys/utsname.h>

#include "kerneld.h"
#include "version.h"
#include "module.h"

#define MAXCMD 255
/*
 * The _real_ maximum message type is KERNELD_MAXCMD,
 * but we reserve some types for other daemons...
 */

#define MSIZE 1024 /* might be MSGMAX instead... almost 4k nowadays */
#define DELAY_TIME 60 /* adjustable with the "delay=..." parameter */
#define JOB_DONE 0
#define REQUEST_ROUTE "/sbin/request-route"

#ifdef DEBUG
time_t t0;
#define DPRINT(arg) if (debug) { printf("%d:", (int)time(0) - (int)t0);printf arg; }
#else
#define DPRINT(arg)
#endif


struct clear_text {
	int message;
	char *text;
} clear_text[] = {
	{ KERNELD_CANCEL_RELEASE_MODULE, "cancel_release_module" },
	{ KERNELD_SYSTEM, "system" },
	{ KERNELD_REQUEST_MODULE, "request_module" },
	{ KERNELD_DELAYED_RELEASE_MODULE, "delayed_release_module" },
	{ KERNELD_RELEASE_MODULE, "release_module" },
	{ KERNELD_REQUEST_ROUTE, "request_route" },
	{ KERNELD_BLANKER, "screenblanker" },
#ifdef KERNELD_GET_PERSIST
	{ KERNELD_GET_PERSIST, "get_persist" },
	{ KERNELD_SET_PERSIST, "set_persist" },
#endif
	{ MAXCMD, "debug" },
	{ 0, 0 }
};

#ifdef NO_GDBM
typedef struct {
	char *dptr;
	int   dsize;
} datum;
#else
#include <gdbm.h>
#endif

struct persist_t {
	struct persist_t *next;
	datum val;
	datum key;
};

struct persist_t *persist_head;

char kd_dbmfile[200]; /* or whatever... */
int have_request_route; /* set in gdbm_reload, i.e. also at "kill -1" */

#ifndef NO_GDBM
GDBM_FILE dbf;

GDBM_FILE kddbmopen(int how)
{
	return dbf = gdbm_open(kd_dbmfile, 0, how, 0600, NULL);
}
#endif

void gdbm_reload(int dummy)
{
#ifndef NO_GDBM
	datum key, nextkey, data;
	struct persist_t *p = persist_head;
	struct persist_t *x;

	if (kddbmopen(GDBM_READER)) {
		/* clean any up old data */
		while ((x = p)) {
			p = p->next;
			free(x->key.dptr);
			free(x->val.dptr);
			free(x);
		}
		persist_head = NULL;

		key = gdbm_firstkey(dbf);
		while (key.dptr) {
			data = gdbm_fetch(dbf, key);
			/* Create entry */
			x = (struct persist_t *)malloc(sizeof(*x));
			if (x == NULL)
				/* fail, ignore request */
				return;
			x->key = key;
			x->val = data;
			x->next = persist_head;
			persist_head = x;
			nextkey = gdbm_nextkey(dbf, key);
			key = nextkey;
		}
		gdbm_close(dbf);
	}
#endif
#ifndef NO_ROUTE
	if (access(REQUEST_ROUTE, X_OK) == 0)
		have_request_route = 1;
	else
#endif
		have_request_route = 0;
}

int qid;

/*
 * If "kerneld" is called with the argument "keep",
 * all requests for module release will be ignored.
 *
 * If "delay=10" is used as an argument, the default delay
 * will be changed from the preset value of 60.
 */
int keep = 0;
int delay = DELAY_TIME;
int debug = 0;
int want_type = -MAXCMD;
int dev_null;

struct job {
	struct job *next;
	pid_t pid;
	int status;
	int reply_size;
	int reply_fd;
	struct kerneld_msg msg;
};

struct job *job_head = NULL;
/*
 * Handle both old and new kerneld message formats
 */
struct oldkerneld_msg {
	long mtype;
	long id;
	char text[1];
};


int do_msgsnd(int msqid, struct kerneld_msg *msg, size_t msgsz, int msgflg)
{
#ifdef NEW_KERNELD_PROTOCOL /* i.e. using extended kerneld protocol */
	if (msg->version == 0) {
		if (msgsz) {
			struct oldkerneld_msg *omsg =
				(struct oldkerneld_msg *)msg;
			memmove(omsg->text, msg->text, msgsz);
		}
	}
	else
		msgsz += sizeof(short int) + sizeof(short int);
#endif
	msgsz += sizeof(long);
	return msgsnd(msqid, (struct msgbuf *)msg, msgsz, msgflg);
}


int do_msgrcv(int msqid, struct kerneld_msg *msg, size_t msgsz, long msgtyp, int msgflg)
{
	int sz;

	sz = msgrcv(msqid, (struct msgbuf *)msg, msgsz, msgtyp, msgflg);
#ifdef NEW_KERNELD_PROTOCOL /* i.e. using extended kerneld protocol */
	if (sz > 0) {
		if (msg->version != 2) {
			struct oldkerneld_msg *omsg =
				(struct oldkerneld_msg *)msg;
			memmove(msg->text, omsg->text, sz);
			msg->pid = msg->version = 0;
			sz += sizeof(short int) + sizeof(short int);
		}
	}
#endif
	return sz;
}

void do_putenv(struct job *job)
{
#ifdef NEW_KERNELD_PROTOCOL /* i.e. using extended kerneld protocol */
	char triggerpid[30];

	if (job->msg.version != 0) {
		sprintf(triggerpid, "KERNELD_TRIGGER=%d", job->msg.pid);
		putenv(triggerpid);
	}
#endif
}


/*
 * Get clear text corresponding to message type
 */
char * type2text(int type)
{
	int chk;

	for (chk = 0; clear_text[chk].message != 0; ++chk) {
		if (clear_text[chk].message == type)
			break;
	}
	return (clear_text[chk].text)?(clear_text[chk].text):"unknown";
}

/*
	Generate an error message with the syslog facility.
*/
void kerneld_error (const char *ctl, ...)
{
	char buf[1024];
	va_list list;

	va_start (list,ctl);
	vsnprintf (buf, sizeof buf, ctl, list);
	va_end (list);
	syslog (LOG_ERR,"%s",buf);
}

void kerneld_perror (char *name)
{
	kerneld_error ("error: %s: %s", name, strerror(errno));
	exit (1);
}

volatile int timer = 0;
extern int errno;

void
handle_child(int sig)
{
	struct job *job;
	int pid;
	int status;

	while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
		for (job = job_head; job; job = job->next) {
			if (job->pid == pid) {
				job->pid = JOB_DONE;
				job->status = WEXITSTATUS(status);
				/* don't break, more jobs might be waiting... */
				DPRINT(("SIGCHLD: job=%p, pid=%d, status=%d\n",
					job, pid, job->status));
			}
		}
	}
}

void
handle_timer(int sig)
{
	timer = 1;
	alarm(delay);
}


/*
	Check if a request for a module is pending.
	If it is, then we just returned the pid of the original
	request.

	When this request will return, all "job" with the same pid
	will get the result. newjob->pid will be set to JOB_DONE
	and kerneld will send back the return code to all caller.
*/
static int check_pending_load (struct job *newjob)
{
	int pid = -1;
	struct job *job;
	for (job = job_head; job; job = job->next) {
		if (job->msg.mtype == KERNELD_REQUEST_MODULE
			&& strcmp(job->msg.text,newjob->msg.text)==0){
			pid = job->pid;
		}
	}
	return pid;
}

/*
 * Execute the requested kerneld task, return pid or -errno.
 * If pid is set to 0 then no process has been spawned.
 *
 * Note that the job has been allocated with calloc, so all
 * fields are already zero (including the status).
 */
int
spawn_it(struct job *newjob)
{
	struct job *job;
#ifdef KERNELD_GET_PERSIST
	struct persist_t *persist;
#endif
	int pipes[2];
	int status;
	int pid = 0;
	int op;

	switch (op = newjob->msg.mtype) {
	case KERNELD_CANCEL_RELEASE_MODULE:
		if (keep)
			break;
		/* else */
		for (job = job_head; job; job = job->next) {
			if ((job->msg.mtype == KERNELD_DELAYED_RELEASE_MODULE)
			     && (job->pid != JOB_DONE) &&
			     (strcmp(job->msg.text, newjob->msg.text) == 0)) {
				kill(job->pid, SIGINT);
				DPRINT(("job (%08lx), pid %d terminated\n",
					(long)job, job->pid));
			}
		}
		break;

	case KERNELD_SYSTEM:
		if (newjob->msg.id) /* reply wanted */
			pipe(pipes);
		if ((pid = fork()) == 0) {
			if (newjob->msg.id) { /* reply wanted */
				close(1);
				dup(pipes[1]);
				close(pipes[0]);
				close(pipes[1]);

				close(0);close(2);
				dup(dev_null); dup(dev_null);
			}
			else {
				close(0);close(1);close(2);
				dup(dev_null); dup(dev_null); dup(dev_null);
			}

			do_putenv(newjob);
			/* signal(SIGCHLD, SIG_DFL); */
			status = system(newjob->msg.text);
			exit(WEXITSTATUS(status));
		}
		if ((pid > 0) && newjob->msg.id) { /* reply wanted */
			newjob->reply_fd = pipes[0];
			close(pipes[1]);
		}
		break;

	case KERNELD_REQUEST_MODULE:
		if (!keep)
			/*
			 * re-arm the timer for auto-removal,
			 * keep an auto-loaded module at least this long
			 */
			alarm(delay);
		pid = check_pending_load (newjob);
		if (pid == -1
			&& (pid = fork()) == 0) {
			close(0);close(1);close(2);
			dup(dev_null); dup(dev_null); dup(dev_null);
			do_putenv(newjob);
			execlp("/sbin/modprobe", "modprobe", "-k", "-s",
						newjob->msg.text, 0);
			kerneld_perror("/sbin/modprobe");
			sleep(2);
			exit(1);
		}
		break;

	case KERNELD_DELAYED_RELEASE_MODULE:
	case KERNELD_RELEASE_MODULE:
		if (keep)
			pid = 0;
		/* else */
		if ((pid = fork()) == 0) {
			close(0);close(1);close(2);
			dup(dev_null); dup(dev_null); dup(dev_null);
			if (op == KERNELD_DELAYED_RELEASE_MODULE)
				sleep(delay);
			do_putenv(newjob);
			execlp("/sbin/modprobe", "modprobe", "-r", "-s",
						newjob->msg.text, 0);
			kerneld_perror("/sbin/modprobe");
			sleep(2);
			exit(1);
		}
		break;

	case KERNELD_REQUEST_ROUTE:
		/* set in gdbm_reload, i.e. also at "kill -1" */
		if (!have_request_route)
			break;

		/* check if there is a previous similar route request running */
		for (job = job_head; job; job = job->next) {
			if ((job->msg.mtype == KERNELD_REQUEST_ROUTE)
			     && job->pid && (job->pid != JOB_DONE) &&
			     (strcmp(job->msg.text, newjob->msg.text) == 0)) {
				/* wait for the same pid */
				pid = job->pid;
				DPRINT(("job (%08lx), depends on job(%08lx)\n",
					(long)newjob, (long)job));
				break; /* for-loop */
			}
		}
		/* no previous request is running, so start a new one */
		if ((pid == 0) && ((pid = fork()) == 0)) {
			close(0);close(1);close(2);
			dup(dev_null); dup(dev_null); dup(dev_null);
			do_putenv(newjob);
			execlp(REQUEST_ROUTE, "request-route",
				newjob->msg.text, 0);
			kerneld_perror(REQUEST_ROUTE);
			sleep(2);
			exit(1);
		}
		break;

	case KERNELD_BLANKER:
		/* Find any previous running blanker */
		for (job = job_head; job; job = job->next) {
			if ((job->msg.mtype == KERNELD_BLANKER)
			     && job->pid && (job->pid != JOB_DONE)) {
				pid = job->pid;
				DPRINT(("job (%08lx), depends on job(%08lx)\n",
					(long)newjob, (long)job));
				break; /* for-loop */
			}
		}

		if (strcmp(newjob->msg.text, "on") == 0) {
			if ((pid == 0) && ((pid = fork()) == 0)) {
				/* no previus blanker is running */
				close(0);close(1);close(2);
				dup(dev_null); dup(dev_null); dup(dev_null);
				do_putenv(newjob);
				execlp("/sbin/screenblanker","screenblanker",0);
				kerneld_perror("/sbin/screenblanker");
				sleep(2);
				exit(1);
			}
		} else { /* turn the blanker off */
			/* Note that pid is already set to the correct value */
			/* Let the screen blanker report back instead */
			if (pid != 0) {
				job->msg.id = newjob->msg.id;
				kill((pid_t)pid, SIGQUIT);
			} else { /* something has happened to the blanker */
				/* fake a "finish_jobs()" */
				newjob->msg.mtype = newjob->msg.id;
				newjob->msg.id = 1;
				do_msgsnd(qid, &newjob->msg, 0, 0);
			}
			pid = 0;
			newjob->msg.id = 0;
		}
		break;

	case MAXCMD: /* debug entry, used by kdstat */
		{
			char *p = newjob->msg.text;
			struct msgbuf msgp;
			int done = 0;
			int count = 0;

			if (strcmp(p, "debug") == 0)
				debug = 1;
			else if (strcmp(p, "nodebug") == 0)
				debug = 0;
			else if (strcmp(p, "keep") == 0)
				keep = 1;
			else if (strcmp(p, "nokeep") == 0)
				keep = 0;
			else if (strncmp(p, "delay=", 6) == 0) {
				count = atoi(p + 6);
				if (count) {
					delay = count;
					alarm(delay);
				}
			}
			else if (strcmp(p, "flush") == 0) {
				count = 0;
				while (msgrcv(qid, &msgp, 1, 0,
					IPC_NOWAIT | MSG_NOERROR) >= 0)
					++count;
				sprintf(p, "flushed %d entries\n", count);
				p += strlen(p);

			}

			sprintf(p, "Version " MODUTILS_VERSION ", pid=%d, delay=%d, %skeep, %sdebug\n",
				getpid(), delay, keep?"":"no", debug?"":"no");
			p += strlen(p);

			count = 0;
			for (job = job_head; job; job = job->next) {
				if (p - newjob->msg.text > MSIZE - 40) {
					done = 1;
					break; /* for-loop */
				}
				++count;
				if (count == 1) {
					sprintf(p, "job queue:\n");
					p += strlen(p);
				}
				sprintf(p, "pid %d, type %s ('%s')"
#ifdef NEW_KERNELD_PROTOCOL /* i.e. using extended kerneld protocol */
					" from pid %d"
#endif
					"\n",
					job->pid,
					type2text((int)job->msg.mtype),
					job->msg.text
#ifdef NEW_KERNELD_PROTOCOL /* i.e. using extended kerneld protocol */
					, job->msg.pid
#endif
					);
				p += strlen(p);
			}

			if (!done && !count) {
				sprintf(p, "no jobs waiting\n");
				p += strlen(p);
			}

		}
		newjob->reply_size = strlen(newjob->msg.text);
		break;
#if 0
	case GENERIC_EXAMPLE:
		/* get the parameter from newjob->msg.text */
		/* if it's illegal, set newjob->status to the error number */
		/* else if it is an internal job: */
		/*     do it and copy any result back to newjob->msg.text */
		/*     update newjob->reply_size with the size (in bytes) */
		/*     update newjob->status if it shouldn't be 0 */
		/* else the job should be spawned: */
		/*     set up the parameters and fork a new process */
		/*     set pid to the pid of the new process */
		break;
#endif

#ifdef KERNELD_GET_PERSIST
	case KERNELD_GET_PERSIST:
		for (persist = persist_head; persist; persist = persist->next) {
			if ((strcmp(newjob->msg.text, persist->key.dptr) == 0)
					&& persist->val.dsize) {
				newjob->reply_size = persist->val.dsize;
				memcpy(newjob->msg.text, persist->val.dptr,
					newjob->reply_size);
				newjob->status = newjob->reply_size;
				break;
			}
		}
		break;

	case KERNELD_SET_PERSIST:
		{
		struct __persist *k = (struct __persist *)newjob->msg.text;
		struct persist_t **prev;

		if (k->keylen == 0)
			break;

		for (prev = &persist_head, persist = persist_head; persist;
		prev = &(persist->next), persist = persist->next) {
			if (strcmp(k->arr, persist->key.dptr) == 0)
				break;
		}
		if ((persist)) { /* Previously defined */
			if (k->arglen == 0) {
				/* Remove entry */
				*prev = persist->next;
#ifndef NO_GDBM
				if (kddbmopen(GDBM_WRITER)) {
					gdbm_delete(dbf, persist->val);
					gdbm_close(dbf);
				}
#endif
				free(persist->key.dptr);
				free(persist->val.dptr);
				free(persist);
				break;
			}
			/* else */
			if (k->arglen != persist->val.dsize) {
				char *p;

				if ((p = malloc(k->arglen)) == NULL)
					/* fail, but keep the old value */
					break;
				/* else */
				free(persist->val.dptr);
				persist->val.dptr = p;
				persist->val.dsize = k->arglen;
			}
		}
		else { /* Not previously defined */
			if (k->arglen == 0)
				break;

			/* Create entry */
			persist = (struct persist_t *)malloc(sizeof(*persist));
			if (persist == NULL)
				/* fail, ignore request */
				break;

			if ((persist->key.dptr = malloc(k->keylen)) == NULL) {
				free(persist);
				/* fail, ignore request */
				break;
			}
			if ((persist->val.dptr = malloc(k->arglen)) == NULL) {
				free(persist->key.dptr);
				free(persist);
				/* fail, ignore request */
				break;
			}
			strcpy(persist->key.dptr, k->arr);
			persist->key.dsize = k->keylen;
			persist->val.dsize = k->arglen;
			persist->next = persist_head;
			persist_head = persist;
		}
		/* Update value */
		if (memcmp(persist->val.dptr, k->arr + k->keylen, k->arglen) == 0)
			break;
		/* else */
		memcpy(persist->val.dptr, k->arr + k->keylen, k->arglen);
#ifndef NO_GDBM
		if (kddbmopen(GDBM_WRCREAT)) {
			gdbm_store(dbf, persist->key, persist->val, GDBM_REPLACE);
			gdbm_close(dbf);
		}
#endif
		}
		break;
#endif

	default: /* unknown */
		kerneld_error ("kerneld: unknown message type: %d", op);
		newjob->status = 1; /* failed... ? */
		break;
	}

	return pid;
}

/*
 * Look for finished jobs and take care of them.
 * Return < 0 if fatal error
 */
int
finish_jobs()
{
	struct job *job;
	struct job **pjob;
	int status = 0;

	DPRINT(("finish_jobs\n"));
	for (pjob = &job_head, job = job_head; job && (status >= 0); job = *pjob) {
		if (job->pid == JOB_DONE) {
			/*
			 * Does the kernel expect an answer?
			 */
			if (job->msg.id) {
				if (job->reply_fd) {
					struct timeval timeout = { 0, 0 };
					fd_set	readfds;

					FD_ZERO(&readfds);
					FD_SET(job->reply_fd, &readfds);
					if ((select(job->reply_fd + 1, &readfds,
						(fd_set *)NULL,
						(fd_set *)NULL, &timeout) > 0) &&
					FD_ISSET(job->reply_fd, &readfds)) {
						job->reply_size = read(job->reply_fd,
							job->msg.text, MSIZE);
					}
					close(job->reply_fd);
				}
				job->msg.mtype = job->msg.id;
				job->msg.id = job->status;

				status = do_msgsnd(qid, &job->msg,
						((job->reply_size > 0) ?
						job->reply_size : 0)
						, 0);
			}
			/*
			 * unlink the job
			 */
			DPRINT(("job (%08lx) unlinked\n", (long)job));
			*pjob = job->next;
			free(job);
		}
		else /* job not done */
			pjob = &(job->next);
	}

	return status;
}

void
do_timer()
{
	timer = 0;
	if (!keep) {
		/* Thanks Jacques!!! */
		struct job *job;

		for (job = job_head; job; job = job->next)
			if (job->msg.mtype == KERNELD_REQUEST_MODULE)
				break;
		if (job == NULL)
			delete_module(NULL);
	}
}

int
main(int argc, char *argv[])
{
	struct job *job;
	int pid;
	int status;
	struct utsname uts_info;
	struct sigaction sa;
	sigset_t hold_signals;

	uname(&uts_info);

#ifdef NEW_KERNELD_PROTOCOL
	if (uts_info.release[0] < '2' ||
	    (uts_info.release[0] == '2' && uts_info.release[2] == '0')) {
		printf("kerneld: warning, "
			"kerneld compiled with NEW_KERNELD_PROTOCOL "
			"running on\n\t kernel <= 2.0; "
			"may well not work correctly.\n" );
	}
#endif

	if (uts_info.release[0] == '2' && uts_info.release[2] == '1') {
		printf("kerneld: hmm, no idea whether this version "
			"of kerneld will work with your 2.1.x kernel.\n"
			"Upgrade to 2.2.x?\n");
}

	if (uts_info.release[0] > '2' ||
	    (uts_info.release[0] == '2' && uts_info.release[2] > '1') ) {
		printf("kerneld: you almost certainly don't want to be running "
			"kerneld with >= 2.2.x\n\t kernels; "
			"read /usr/src/linux/Documentation/kmod.txt.\n");
	}

	/* make me a daemon */
	if ((pid = fork()) != 0) {
		printf("Starting kerneld, version " MODUTILS_VERSION " (pid %d)\n", pid);
		exit(0);
	}

	openlog ("kerneld",0,LOG_DAEMON);
	if ((qid = msgget(IPC_PRIVATE, S_IRWXU | IPC_CREAT | IPC_KERNELD)) < 0){
		kerneld_error("Can't initialise message queue: %s",strerror(errno));
		exit(1);
	}

#ifdef DEBUG
	t0 = time(0);
#endif

	setbuf(stdout, NULL);
	syslog (LOG_INFO,"started, pid=%d, qid=%d", getpid(), qid);

	uname(&uts_info);
	sprintf(kd_dbmfile, "/lib/modules/%s/persist.gdbm", uts_info.release);
	gdbm_reload(0); /* dummy arg */

	setsid();

	sigemptyset(&hold_signals);
	sigaddset(&hold_signals, SIGCHLD);
	sigaddset(&hold_signals, SIGHUP);

	sa.sa_mask = hold_signals;
	sa.sa_flags = SA_RESTART;

	sa.sa_handler = handle_child;
	if (sigaction(SIGCHLD, &sa, NULL) < 0) {
		kerneld_perror("sigaction(SIGCHLD)");
	}

	sa.sa_handler = handle_timer;
	if (sigaction(SIGALRM, &sa, NULL) < 0) {
		kerneld_perror("sigaction(SIGARLM)");
	}

	sa.sa_handler = gdbm_reload;
	if (sigaction(SIGHUP, &sa, NULL) < 0) {
		kerneld_perror("sigaction(SIGHUP)");
	}

	while (argc > 1) {
		if (strcmp(argv[1], "keep") == 0)
			keep = 1;
		else if (strncmp(argv[1], "delay=", 6) == 0)
			delay = atoi(&(argv[1][6]));
		else if (strcmp(argv[1], "debug") == 0)
			debug = 1;
		else if (strncmp(argv[1], "type=", 5) == 0)
			want_type = atoi(&(argv[1][5]));
		++argv;
		--argc;
	}

	dev_null = open("/dev/null", O_RDWR);

	if (!keep)
		alarm(delay); /* start the timer task */

	for (;;) {
		job = (struct job *)calloc(1, sizeof(struct job) + MSIZE);
		if (job == NULL) {
			kerneld_perror("calloc(job)");
		}

	restart:
		while ((status = do_msgrcv(qid, &job->msg,
			MSIZE, want_type, MSG_NOERROR)) == 0)
			/*keep on*/;

		if (status < 0) {
			/* was the msgrcv interrupted by a signal? */
			if (errno == EINTR) {
				if (timer) {
					do_timer();
				}
				if (finish_jobs() < 0) {
					break; /* fatal error */
				}
				/* else */
				goto restart; /* wait for message */
			}
			/* else */
			break; /* some other error */
		}
		/* else, we got a message */

		/* null-terminate the message */
		status = (status >= MSIZE) ? (MSIZE - 1) : status;
		((struct msgbuf *)&job->msg)->mtext[status] = '\0';
		DPRINT(("job (%08lx) scheduled, type %s ('%s')\n", (long)job,
			type2text((int)job->msg.mtype), job->msg.text));

		/* Don't trap SIGCHLD til we add the job to the queue */
		sigprocmask(SIG_BLOCK, &hold_signals, NULL);
		if ((pid = spawn_it(job)) < 0)
			break; /* fatal error */

		/*
		 * Link this job into the job queue if something was
		 * spawned or if someone is waiting for an answer.
		 */
		if ((pid > 0) || (job->msg.id != 0)) {
			job->pid = pid;
			job->next = job_head;
			job_head = job;
			DPRINT(("job (%08lx) stored, pid=%d\n", (long)job,pid));
			/* take care of all tasks, including non-spawned ones */
			if (finish_jobs() < 0)
				break; /* fatal error */
		}
		else { /* all work requested has been performed */
			DPRINT(("job (%08lx) released\n", (long)job));
			free(job);
		}
		sigprocmask(SIG_UNBLOCK, &hold_signals, NULL);
	}

	kerneld_perror("exit");
	return 1;
}
