#define CONFIG_KERNELD
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "kerneld.h"

#define MSIZE 1024

#ifndef KDHDR
# ifdef NEW_KERNELD_PROTOCOL
#  define KDHDR (sizeof(long) + sizeof(short) + sizeof(short))
# else
#  define KDHDR sizeof(long)
# endif
#endif

/*
 * Copyright (C) 1995, Bjorn Ekwall <bj0rn@blox.se>
 *
 * See the file "COPYING" for your rights.
 *
 * Fake a call to kerneld.
 * This is just used to debug kerneld...
 *
 * All calls are with id=0, i.e. no response from kerneld, unless
 * the option "-r" is used, which will use reply type = current pid + 1024.
 * Note: this message type will _not_ be intercepted by the kernel
 * or kerneld, since the kernel listens for messages >= 0x7fff0000
 * and kerneld listens for messages <= 255 !
 *
 * Usage: kdsend type message
 * where type should be the numeric value of the request
 * Example: "kdsend 2 ppp" will load the ppp stack
 *          "kdsend 4 ppp" will remove the ppp stack (if possible) after 60 sec
 *	    "kdsend -r 1 ls" will execute ls and return the result.
 *
 * See <linux/kerneld.h> for possible types...
 */

#define REPLY_ID 1024

int
main(argc, argv)
int argc;
char **argv;
{
	struct kerneld_msg *msgp;
	int msgtyp;
	int qid;
	int status;
	int reply = 0;

	if ((argc > 1) && (strcmp(argv[1], "-r") == 0)) {
		reply = 1;
		++argv;
		--argc;
	}
	if (argc < 2) {
		fprintf(stderr, "use: kdsend [-r] type message\n");
		exit(1);
	}

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

	if ((msgtyp = atol(argv[1])) == 0)
		msgtyp = 1; /* ksystem */
	msgp->mtype = msgtyp;
	if (reply)
		reply = msgp->id = REPLY_ID + getpid();
	else
		msgp->id = 0;
	if (argc == 3)
		strcpy(msgp->text, argv[2]);
	else
		msgp->text[0] = '\0';

	status = msgsnd(qid, (struct msgbuf *)msgp,
		KDHDR + strlen(msgp->text), 0);
	if (status < 0)
		perror("kdsend");

	if (reply) {
		status = msgrcv(qid, (struct msgbuf *)msgp,
			KDHDR + MSIZE, reply, MSG_NOERROR);
		if (status > 0) {
			msgp->text[status - KDHDR] = '\0';
			printf("recieved %d bytes: '%s'\n", status, msgp->text);
		}
		else if (status < 0)
			perror("kdsend");
		else
			printf("nothing recieved\n");
	}
	return status;
}
