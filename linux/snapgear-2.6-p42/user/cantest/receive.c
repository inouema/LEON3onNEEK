
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

void usage()
{
  static char *usage_text  = "\
  Bei diesem Test wird mittels polling auf Can Datenpakete gewartet\n\
  ";
    fprintf(stderr, usage_text);
}

int main(int argc,char **argv)
{
extern char *optarg;
int c;
int fd;
int got;
canmsg_t rx;
char device[40];

    while ((c = getopt(argc, argv, "H")) != EOF) {
	switch (c) {
	    case 'H':
	    default: usage(); exit(0);
	}
    }

   
    sprintf(device, "/dev/%s", STDDEV);
    printf("using CAN device %s\n", device);
    
    if(( fd = open(device, O_RDWR )) < 0 ) {
	fprintf(stderr,"Error opening CAN device %s\n", device);
        exit(1);
    }

    printf("waiting for msg at 0x%p:\n", &rx);

    while(1) {
      got=read(fd, &rx, 1);
      if( got > 0) {
	printf("Received with ret=%d: %12lu.%06lu id=%ld len=%d msg='%X %X %X %X %X %X %X %X' flags=0x%x \n",
		    got, 
		    rx.timestamp.tv_sec,
		    rx.timestamp.tv_usec,
		    rx.id, rx.length, rx.data[0], rx.data[1], rx.data[2],
                                       rx.data[3], rx.data[4], rx.data[5],
                                        rx.data[6], rx.data[7],rx.flags );
	fflush(stdout);
      } else {
	printf("Received with ret=%d\n", got);
	fflush(stdout);
      }
      sleep(1);
    }


    close(fd);
    return 0;
}
