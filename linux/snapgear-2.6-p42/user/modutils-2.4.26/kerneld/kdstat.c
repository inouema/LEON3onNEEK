#define CONFIG_KERNELD
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "kerneld.h"

#define MSIZE 1024
#define MAXCMD 255 /* as in kerneld.c */

/*
 * Copyright (C) 1995, Bjorn Ekwall <bj0rn@blox.se>
 *
 * See the file "COPYING" for your rights.
 *
 * This is just used to debug kerneld...
 * Show (and change) the internal kerneld state
 *
 * use as:
 *	kdstat			for just a status
 *	kdstat debug		for debugging on and off
 *	kdstat nodebug
 *	kdstat keep		for autoclean
 *	kdstat nokeep
 *	kdstat delay=10		for changing the timer interval
 *	kdstat flush		flush the IPC message queue
 */

#define REPLY_ID 1024

#ifndef KDHDR
# ifdef NEW_KERNELD_PROTOCOL
#  define KDHDR (sizeof(long) + sizeof(short) + sizeof(short))
# else
#  define KDHDR sizeof(long)
# endif
#endif

int
main(argc, argv)
int argc;
char **argv;
{
	struct kerneld_msg *msgp;
	int qid;
	int status;
	int reply;

	qid = msgget(IPC_PRIVATE, 0600 | IPC_KERNELD);
	if (qid < 0) {
		perror("kdsend");
		exit(1);
	}

	msgp = (struct kerneld_msg *)malloc(sizeof(struct kerneld_msg) + MSIZE);
#ifdef NEW_KERNELD_PROTOCOL
	msgp->version = 2;
	msgp->pid = getpid();
#endif


	msgp->mtype = MAXCMD; /* magic! */
	reply = msgp->id = REPLY_ID + getpid();
	if (argc > 1)
		strcpy(msgp->text, argv[1]);
	else
		msgp->text[0] = '\0';

	status = msgsnd(qid, (struct msgbuf *)msgp, KDHDR + strlen(msgp->text), 0);
	if (status < 0)
		perror("kdstat");

	status = msgrcv(qid, (struct msgbuf *)msgp,
			KDHDR + MSIZE, reply, MSG_NOERROR);
	if (status > 0) {
		msgp->text[status - KDHDR] = '\0';
		printf("%s", msgp->text);
	}
	else if (status < 0)
		perror("kdstat");
	else
		printf("nothing recieved\n");
	return status;
}
