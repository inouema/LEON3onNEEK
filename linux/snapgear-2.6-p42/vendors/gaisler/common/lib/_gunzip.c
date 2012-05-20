/*
 * misc.c
 * 
 * This is a collection of several routines from gzip-1.0.3 
 * adapted for Linux.
 *
 * malloc by Hannu Savolainen 1993 and Matthias Urlichs 1994
 *
 * Modified for ARM Linux by Russell King
 *
 * Nicolas Pitre <nico@visuaide.com>  1999/04/14 :
 *  For this code to run directly from Flash, all constant variables must
 *  be marked with 'const' and all other variables initialized at run-time 
 *  only.  This way all non constant variables will end up in the bss segment,
 *  which should point to addresses in RAM and cleared to 0 on start.
 *  This allows for a much quicker boot time.
 */


#include <linux/kernel.h>

//#include <asm/uaccess.h>

int puts(const char *fmt, ...);

#undef memset
#undef memcpy
void* lelomemset(void *, int, int);
void* lelomemcpy(void *, __const void *, int);
#undef memset(a,b,c) lelomemset(a,b,c)
#undef memcpy(a,b,c) lelomemcpy(a,b,c)
#define memzero(s, n) lelomemset ((s), 0, (n))
#define memcpy(a,b,c) lelomemcpy (a,b,c)



#ifdef STANDALONE_DEBUG
#define puts printf
#endif

#define __ptr_t void *


/*
 * gzip delarations
 */
#define OF(args)  args
#define STATIC static

typedef unsigned char  uch;
typedef unsigned short ush;
typedef unsigned long  ulg;

#define WSIZE 0x8000		/* Window size must be at least 32k, */
				/* and a power of two */

static uch *inbuf;		/* input buffer */
static uch window[WSIZE];	/* Sliding window buffer */

static unsigned insize;		/* valid bytes in inbuf */
static unsigned inptr;		/* index of next byte to be processed in inbuf */
static unsigned outcnt;		/* bytes in output buffer */
 
/* gzip flag byte */
#define ASCII_FLAG   0x01 /* bit 0 set: file probably ascii text */
#define CONTINUATION 0x02 /* bit 1 set: continuation of multi-part gzip file */
#define EXTRA_FIELD  0x04 /* bit 2 set: extra field present */
#define ORIG_NAME    0x08 /* bit 3 set: original file name present */
#define COMMENT      0x10 /* bit 4 set: file comment present */
#define ENCRYPTED    0x20 /* bit 5 set: file is encrypted */
#define RESERVED     0xC0 /* bit 6,7:   reserved */

#define get_byte()  (inptr < insize ? inbuf[inptr++] : fill_inbuf())

/* Diagnostic functions */
#ifdef DEBUG
#  define Assert(cond,msg) {if(!(cond)) error(msg);}
#  define Trace(x) fprintf x
#  define Tracev(x) {if (verbose) fprintf x ;}
#  define Tracevv(x) {if (verbose>1) fprintf x ;}
#  define Tracec(c,x) {if (verbose && (c)) fprintf x ;}
#  define Tracecv(c,x) {if (verbose>1 && (c)) fprintf x ;}
#else
#  define Assert(cond,msg)
#  define Trace(x)
#  define Tracev(x)
#  define Tracevv(x)
#  define Tracec(c,x)
#  define Tracecv(c,x)
#endif

static int  fill_inbuf(void);
static void flush_window(void);
static void error(char *m);
static void gzip_mark(void **);
static void gzip_release(void **);

extern char input_data[];
extern char input_data_end[];

static uch *output_data;
static ulg output_ptr;
static ulg bytes_out;

static void *malloc(int size);
static void free(void *where);
static void error(char *m);
static void gzip_mark(void **);
static void gzip_release(void **);

extern int end;
static ulg free_mem_ptr;
static ulg free_mem_ptr_end;

#define HEAP_SIZE 0x2000

#include "inflate.c"

#ifndef STANDALONE_DEBUG
static void *malloc(int size)
{
	void *p;

	if (size <0) error("Malloc error\n");
	if (free_mem_ptr <= 0) error("Memory error\n");

	free_mem_ptr = (free_mem_ptr + 3) & ~3;	/* Align */

	p = (void *)free_mem_ptr;
	free_mem_ptr += size;

	if (free_mem_ptr >= free_mem_ptr_end)
		error("Out of memory");
	return p;
}

static void free(void *where) { 
/* gzip_mark & gzip_release do the free */
}

static void gzip_mark(void **ptr)
{
	*ptr = (void *) free_mem_ptr;
}

static void gzip_release(void **ptr)
{
	free_mem_ptr = (long) *ptr;
}
#else
static void gzip_mark(void **ptr)
{
}

static void gzip_release(void **ptr)
{
}
#endif


void* lelomemset(void* s, int c, int n) {

	int i;
	char *ss = (char*)s;

	for (i=0;i<n;i++) ss[i] = c;
	return s;
}

void* lelomemcpy(void* __dest, __const void* __src, int __n) {

	int i;
	char *d = (char *)__dest, *s = (char *)__src;

	for (i=0;i<__n;i++) d[i] = s[i];
	return __dest;
}

/* ===========================================================================
 * Fill the input buffer. This is called only when the buffer is empty
 * and at least one byte is really needed.
 */
int fill_inbuf(void)
{

	if (insize != 0)
		error("ran out of input data\n");

	inbuf = input_data;
	insize = &input_data_end[0] - &input_data[0];

	puts ("  - Inputbuffer [ptr: %x, sz: %x]\r\n",inbuf,insize);
      
	inptr = 1;
	return inbuf[0];
}

/* ===========================================================================
 * Write the output window window[0..outcnt-1] and update crc and bytes_out.
 * (Used for the decompressed data only.)
 */
void flush_window(void)
{
	ulg c = crc;
	unsigned n;
	uch *in, *out, ch;

	in = window;
	out = &output_data[output_ptr];
	for (n = 0; n < outcnt; n++) {
		ch = *out++ = *in++;
		c = crc_32_tab[((int)c ^ ch) & 0xff] ^ (c >> 8);
	}
	crc = c;
	bytes_out += (ulg)outcnt;
	output_ptr += (ulg)outcnt;
	outcnt = 0;
	puts(".");
}

static void error(char *x)
{
	puts("\n\n");
	puts(x);
	puts("\n\n -- System halted");

	while(1);	/* Halt */
}


ulg
decompress_kernel(ulg output_start, ulg free_mem_ptr_p, ulg free_mem_ptr_end_p)
{
	output_data		= (uch *)output_start;	/* Points to kernel start */
	free_mem_ptr	        = free_mem_ptr_p;
	free_mem_ptr_end	= free_mem_ptr_end_p;
      
	puts ("output_data:%x,free_mem_ptr:%x,free_mem_ptr_end:%x\n",output_data,free_mem_ptr,free_mem_ptr_end);
	makecrc();
	gunzip(); 
      
      puts("\ndone [sz:0x%x], booting the kernel.\r\n",bytes_out);
      return bytes_out;
}






