/* Konrad Eisele <eiselekd@web.de>, 2003 */
#include <linux/kernel.h>
#include <linux/kdev_t.h>
#include <linux/major.h>
#include <linux/root_dev.h>
#include <linux/fs.h>
#include <asm/page.h>
#include "common.h"
#include <stdarg.h>
 
int main(void);
extern unsigned char _dsu_sbss,_dsu_ebss;
extern char initrd_end,initrd_start,kernel_end;
void setup_mm( unsigned long *mem,unsigned long *ctxtbl); 


#define __img_main_text		__attribute__ ((__section__ (".img.main.text")))
 
// mark as section .img.main.text, to be referenced in linker script
int __img_main_text __main(void){ 
      //char *p =  &_dsu_sbss;
      unsigned long mem,  i,j, k, ctx;
      struct leon_setup *args;
      void (*kernel)(unsigned long);
             
      main(); 
      
      /* kernel args at first PAGE, bootloader Pagetablehirarchy at second PAGE*/ 
      args = (struct leon_setup *) LEONSETUP_MEM_BASEADDR;
      mem = LEONSETUP_MEM_BASEADDR + PAGE_SIZE;
      args ->args[0] = 0;
      args ->freq_kh = BOOTLOADER_FREQ_KHZ;
      args ->uart_baud[0] = BOOTLOADER_BAUD;
      args ->uart_baud[1] = BOOTLOADER_BAUD;
      args ->root_dev = Root_RAM0;
      /* should be romfs */
      args ->root_mountflags_or = MS_RDONLY;
      args ->initrd_start = (unsigned long)(&initrd_start - LEONSETUP_MEM_BASEADDR);
      args ->initrd_size = &initrd_end-&initrd_start;
        
      /* copy from rom */    
      if ( (unsigned long)(&initrd_start) < LEONSETUP_MEM_BASEADDR ) {
	char *p1,*p2;
	args ->initrd_start = PAGE_ALIGN( ((unsigned long)(&kernel_end)) - KERNBASE) ;
	p1 = (char *)(args ->initrd_start + LEONSETUP_MEM_BASEADDR);
	p2 = &initrd_start;
	puts("* Copying rdimage from rom 0x%x to ram %x ...\r\n",p2,p1);
	for (i = 0, j = 0; i < args ->initrd_size;i++,j++) {
	  p1[i] = p2[i];
	  if (j > 50000) {puts(".");j = 0;}
	}
	puts ("\r\n");
      }

      /*Setting up Page Table Hirarchy*/
      puts("* Setting up Page Table Hirarchy\r\n");
      setup_mm(&mem,&ctx);
      
      /*Setting up Kernel params*/
      j = PAGE_ALIGN(LEONSETUP_MEM_BASEADDR);
      k = (LEONSETUP_MEM_BASEADDR + BOOTLOADER_ramsize) - j;
#ifdef CONFIG_BLK_DEV_INITRD


      sputs((char *)&args ->args[0] , PAGE_SIZE, " LD_LIBRARY_PATH=/lib initrd=0x%x,0x%x  ", //LD_LIBRARY_PATH=/lib
	    args ->initrd_start + LEONSETUP_MEM_BASEADDR,
	    args ->initrd_start + LEONSETUP_MEM_BASEADDR + args ->initrd_size);
 
      //console=ttyLeon0,38400n8r console=ttyLeon0,19200n8r console=tty
#endif
      
      puts("* calling kernel  with arguments: %s\r\n",(char *)&args ->args[0]);
      
      srmmu_set_ctable_ptr((unsigned long) ctx);
      srmmu_set_context(0);
      
      __asm__ __volatile__("flush\n\t");

      srmmu_set_mmureg(0x1); 
      kernel = (void (*)(unsigned long)) KERNBASE+LOAD_ADDR;
      kernel(KERNBASE);

      return 1;
}
 
