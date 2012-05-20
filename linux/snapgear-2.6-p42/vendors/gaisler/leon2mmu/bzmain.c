// Konrad Eisele <eiselekd@web.de>, 2003: arch/sparc/leon/boot/tsim/main.c

#include "prom_config.h"

#include <linux/autoconf.h>
#include <linux/kernel.h>
#include <asm/asi.h>
#include <asm/leon.h>
#include <asm/pgtsrmmu.h>
#include <asm/page.h>
#include <stdarg.h>

int puts(const char *fmt, ...);
int lelomm(void);
int sputs(char *buf, size_t size, const char *fmt, ...);
unsigned long decompress_kernel(unsigned long output_start, unsigned long free_mem_ptr_p, unsigned long free_mem_ptr_end_p);
int main(void);


extern char _end, _kernel_phybss_start, _kernel_phybss_end;

#define LELO_STACKSIZE 0x1000

int __main(void) {
      
      unsigned long stackpointer;
      
      __asm__ __volatile__("mov %%sp,%0\n\t" : "=&r" (stackpointer));
      stackpointer -= LELO_STACKSIZE;
      
      puts ("decompress_kernel(to: %x,freemem:%x,freemem_end:%x)\r\n",
	    LEONSETUP_MEM_BASEADDR ,(unsigned long)&_end,stackpointer);

      decompress_kernel(LEONSETUP_MEM_BASEADDR , 
                         (unsigned long)&_end, 
                         stackpointer);
      
      return 0;
}


 
