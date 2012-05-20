#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>
#include <sys/ioctl.h>
 
#ifdef USE_RT_SCHEDULING
# include <sched.h>
# include <sys/mman.h>
#endif
  
#include <errno.h>
#include "can4linux.h"

#define STDDEV "can0"
#define VERSION "1.6"

void usage()
{
static char *usage_text  = "\
Bei diesem Test wird mittels select() (blocked waiting) auf Can Datenpakete gewartet\n\
";
    fprintf(stderr, usage_text);
}

int main(int argc,char **argv)
{
extern char *optarg;
int c;
int can_fd;			/* CAN file descriptor */
int got;
canmsg_t rx;
char device[40];	/* string to hold the CAN device Name */
fd_set rfds;		/* file descriptors for select() */

    while ((c = getopt(argc, argv, "H")) != EOF) {
	switch (c) {
	    case 'H':
	    default: usage(); exit(0);
	}
    }
 
    sprintf(device, "/dev/%s", STDDEV);
    printf("using CAN device %s, ", device);
    
    if(( can_fd = open(device, O_RDWR )) < 0 ) {
	fprintf(stderr,"Error opening CAN device %s\n", device);
        exit(1);
    }
    printf("got can_fd  %d\n", can_fd);

 
    while(1) {
        FD_ZERO(&rfds);
        FD_SET(can_fd, &rfds);		/* watch on fd for CAN */


        printf("Select Device can0 --> blocked waiting until a message appears!");
        
	if( select(FD_SETSIZE, &rfds, NULL, NULL,     NULL  ) > 0 )
	if( FD_ISSET(can_fd, &rfds) ) {

	    got = read(can_fd, &rx, 1);

	    if( got > 0) {
	    int i;
		printf("Received at "
		"%12lu.%06lu ",
			rx.timestamp.tv_sec,
			rx.timestamp.tv_usec);
		 printf(": %c 0x%08lx : %d bytes:",
				       rx.flags & MSG_EXT ? 'X' : 'S',
				       rx.id,   rx.length);
		    if(rx.length > 0) {
			printf("\t");
			for(i = 0; i < rx.length; i++) {
			    printf("%02x ", rx.data[i]);
			}
		    }
		    printf("\n");



		fflush(stdout);
	    } else {
		printf("Received with ret=%d\n", got);
		fflush(stdout);
	    }
	}
    }


    close(can_fd);
    return 0;
}
