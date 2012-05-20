/* Some prototypes for extern functions. */

#include <linux/types.h>	/* for __u16 */

#if !defined(__GNUC__) && !defined(__attribute__)
#define __attribute__(x)	/* if not using GCC, turn off the __attribute__
				   compiler-advice feature. */
#endif

/* identify() is the only extern function used across two source files.  The
   others, though, were declared in hdparm.c with global scope; since other
   functions in that file have static (file) scope, I assume the difference is
   intentional. */
extern void identify (__u16 *id_supplied, const char *devname);

extern void usage_error(int out)    __attribute__((noreturn));
extern int main(int argc, char **argv) __attribute__((noreturn));
extern void flush_buffer_cache (int fd);
extern int seek_to_zero (int fd);
extern int read_big_block (int fd, char *buf);
extern void time_cache (int fd);
extern void time_device (int fd);
extern void no_scsi (void);
extern void no_xt (void);
extern void process_dev (char *devname);

