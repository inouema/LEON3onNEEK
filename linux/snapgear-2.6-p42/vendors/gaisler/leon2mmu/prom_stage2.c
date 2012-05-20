/*
 * main.c
 *
 * __main is located at 0x40000000 and called by prom.S. it inits mmu, and
 * calls the kernel with adequate parameters. emulates a sparc v0 prom for
 * kernel.
 *
 * Copyright (C) 2003 Konrad Eisele <eiselekd@web.de>
 * Copyright (C) 2004 Stefan Holst <mail@s-holst.de>
 *
 */

#include "prom_config.h"
//#include "../common/lib/_put.c"

#include "linux/autoconf.h"
#include "linux/kernel.h"
#include "asm/asi.h"
#include "asm/pgtsrmmu.h"
#include "asm/leon.h"
#include "asm/page.h"
#include "asm/head.h"
#include "linux/kdev_t.h"
#include "linux/major.h"
#include "linux/root_dev.h"
#include "linux/fs.h"

#include "linux/string.h"
#include "linux/init.h"
#include "asm/oplib.h"
#include "asm/idprom.h"
#include "asm/machines.h" 
#include "asm/sun4prom.h"
#include "asm/contregs.h"

/* for __va */
#define phys_base LEONSETUP_MEM_BASEADDR

struct property {
	char *name;
	char *value;
	int length;
};

struct node {
	int level;
	struct property *properties;
};

static void leon_reboot(char *bcommand);
static void leon_halt(void);
static int leon_nbputchar(int c);
static int leon_nbgetchar(void);

static int no_nextnode(int node);
static int no_child(int node);
static int no_proplen(int node,char *name);
static int no_getprop(int node,char *name,char *value);
static int no_setprop(int node,char *name,char *value,int len);
static char *no_nextprop(int node,char *name);

/* a self contained prom info structure */

struct leon_prom_info {
	int freq_khz;
	int leon_nctx;
	int mids[1];
	int baudrates[2];
	struct property root_properties[4];
	struct property cpu_properties[7];
	struct idprom idprom;
	struct linux_nodeops nodeops;
	struct linux_mlist_v0 *totphys_p;
	struct linux_mlist_v0 totphys;
	struct linux_mlist_v0 *avail_p;
	struct linux_mlist_v0 avail;
	struct linux_mlist_v0 *prommap_p;
	void (*synchook)(void);
	struct linux_arguments_v0 *bootargs_p;
	struct linux_arguments_v0 bootargs;
	struct linux_romvec romvec;
	struct node nodes[4];
	char s_device_type[12];
	char s_cpu[4];
	char s_mid[4];
	char s_idprom[7];
	char s_compatability[14];
	char s_leon2[6];
	char s_mmu_nctx[9];
	char s_frequency[16];
	char s_uart1_baud[11];
	char s_uart2_baud[11];
	char arg[];
};

/* static prom info */
static struct leon_prom_info spi = {
	0,
	256,
	{ /* mids */
		0
	},
	{
	  38400, 38400
	},
	{
	  {__va(spi.s_device_type), __va(spi.s_idprom), 4},
	  {__va(spi.s_idprom), (char *)__va(&spi.idprom), sizeof(struct idprom)},
	  {__va(spi.s_compatability), __va(spi.s_leon2), 5},
	  {NULL, NULL, -1}
	},
	{
	  {__va(spi.s_device_type), __va(spi.s_cpu), 4},
		{__va(spi.s_mid), (char *)__va(&spi.mids[0]), 4},
	  {__va(spi.s_mmu_nctx), (char *)__va(&spi.leon_nctx), 4},
	  {__va(spi.s_frequency), (char *)__va(&spi.freq_khz), 4},
	  {__va(spi.s_uart1_baud), (char *)__va(&spi.baudrates[0]), 4},
	  {__va(spi.s_uart2_baud), (char *)__va(&spi.baudrates[1]), 4},
	  {NULL, NULL, -1}
	},
	{
	  0x01, /* format */
	  M_LEON2 | M_LEON2_SOC, /* machine type */
	  {0,0,0,0,0,0}, /* eth */
	  0, /* date */
	  0, /* sernum */
	  0, /* checksum */
	  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} /* reserved */
	},
	{
	  __va(no_nextnode),
	  __va(no_child),
	  __va(no_proplen),
	  __va(no_getprop),
	  __va(no_setprop),
	  __va(no_nextprop)
	},
	__va(&spi.totphys),
	{
	  NULL,
	  (char *)LEONSETUP_MEM_BASEADDR,
	  0,
	},
	__va(&spi.avail),
	{
	  NULL,
	  (char *)LEONSETUP_MEM_BASEADDR,
	  0,
	},
	NULL, /* prommap_p */
	NULL,
	__va(&spi.bootargs),
	{
	  { NULL, __va(spi.arg), NULL /*...*/ },
	  /*...*/
	},
	{
	  0,
	  0, /* sun4c v0 prom */
	  0, 0,
	  { __va(&spi.totphys_p), __va(&spi.prommap_p), __va(&spi.avail_p) },
	  __va(&spi.nodeops),
	  NULL, { NULL /* ... */ },
	  NULL, NULL,
	  NULL, NULL,  /* pv_getchar, pv_putchar */
	  __va(leon_nbgetchar), __va(leon_nbputchar),
	  NULL,
	  __va(leon_reboot),
	  NULL,
	  NULL,
	  NULL,
	  __va(leon_halt),
	  __va(&spi.synchook),
	  { NULL },
	  __va(&spi.bootargs_p)
	  /*...*/
	},
	{
	  { 0, __va(spi.root_properties+3) /* NULL, NULL, -1 */ }, 
	  { 0, __va(spi.root_properties) },
	  { 1, __va(spi.cpu_properties) },
	  { -1,__va(spi.root_properties+3) /* NULL, NULL, -1 */ }
	},
	"device_type",
	"cpu",
	"mid",
	"idprom",
	"compatability",
	"leon2",
	"mmu-nctx",
	"clock-frequency",
	"uart1_baud",
	"uart2_baud",
	CONFIG_KERNEL_COMMAND_LINE
	
	#if (CONFIG_KERNEL_ROOTMEM_INITRAMFS  == 1)
   " rdinit="
	#else
   " init="
	#endif 

   CONFIG_KERNEL_INIT_PATH
};

#ifdef CONFIG_KERNEL_ROOTMEM_ROMFS
/* from arch/sparc/kernel/setup.c */
#define RAMDISK_LOAD_FLAG 0x4000
extern unsigned short root_flags;
extern unsigned short root_dev;
extern unsigned short ram_flags;
extern unsigned int sparc_ramdisk_image;
extern unsigned int sparc_ramdisk_size;
extern int root_mountflags;

extern char initrd_end, initrd_start;
#endif

//static spinlock_t con_lock = SPIN_LOCK_UNLOCKED;

static void leon_reboot(char *bcommand)
{
  //unsigned long flags;
	//_prom_spin_lock_irqsave(&con_lock, flags);
	while (1) { printk(__va("Can't reboot\n")); };
	//_prom_spin_unlock_irqrestore(&con_lock, flags);
}

static void leon_halt(void)
{
  //unsigned long flags;
  //_prom_spin_lock_irqsave(&con_lock, flags);
	while (1) { printk(__va("Halt\n")); };
	//_prom_spin_unlock_irqrestore(&con_lock, flags);
}

/* get single char, don't care for blocking*/
static int leon_nbgetchar(void) {
	BUG();
	return -1;
}

/* put single char, don't care for blocking*/
static int leon_nbputchar(int c) {
      
	unsigned int old_cr;

	old_cr = LEON_REGLOAD_PA(LEON_UCTRL0);
	LEON_REGSTORE_PA(LEON_UCTRL0,(old_cr & ~(LEON_UCTRL_TI)) | (LEON_UCTRL_TE));
	
	while (!(LEON_REGLOAD_PA(LEON_USTAT0) & 0x4));
	LEON_REGSTORE_PA(LEON_UDATA0, (unsigned char)c);
	
	while (!(LEON_REGLOAD_PA(LEON_USTAT0) & 0x4));
	LEON_REGSTORE_PA(LEON_UCTRL0,old_cr);
	return 0;
}

/* node ops */

#define nodes ((struct node *)__va(&spi.nodes))

static int no_nextnode(int node)
{
	if (nodes[node].level == nodes[node+1].level)
		return node+1;
	return -1;
}

static int no_child(int node)
{
	if (nodes[node].level == nodes[node+1].level-1)
		return node+1;
	return -1;
}

static struct property *find_property(int node,char *name)
{
	struct property *prop = &nodes[node].properties[0];
	while (prop && prop->name) {
		if (strcmp(prop->name,name) == 0) return prop;
		prop++;
	}
	return NULL;
}

static int no_proplen(int node,char *name)
{
	struct property *prop = find_property(node,name);
	if (prop) return prop->length;
	return -1;
}

static int no_getprop(int node,char *name,char *value)
{
	struct property *prop = find_property(node,name);
	if (prop) {
		memcpy(value,prop->value,prop->length);
		return 1;
	}
	return -1;
}

static int no_setprop(int node,char *name,char *value,int len)
{
	return -1;
}

static char *no_nextprop(int node,char *name)
{
	struct property *prop;
	if (!name || !name[0] ){
	    return nodes[node].properties[0].name;
	}
	prop = find_property(node,name);
	if (prop) return prop[1].name;
	return NULL;
}

#define GETREGSP(sp) __asm__ __volatile__("mov %%sp, %0" : "=r" (sp))

static void leon_prom_init()
{         
	unsigned long i;
	unsigned char cksum, *ptr;

	unsigned long memctrl1;
	unsigned long memctrl2;
	unsigned long sp,banks=1;
        GETREGSP(sp);
        
	/*
	 * the frequency is actually detected using
	 * (LEON_REGLOAD_PA(LEON_SRLD)+1) * 1000 * 1000; assuming that
	 * bootloader or the dsumon has set up LEON_SRLD, so that timer ticks
	 * on 1mhz
	 */
	spi.freq_khz = (*((unsigned long*)(LEON_PREGS+LEON_SRLD))+1) * 1000;

        /* The mcfg1,mcf2 memsize calcualtions is not used.*/
	/* figure out ram size */
	
	memctrl1 = *((unsigned long*)(LEON_PREGS+LEON_MCFG1));
	memctrl2 = *((unsigned long*)(LEON_PREGS+LEON_MCFG2));

	spi.totphys.num_bytes = 0;
        /*
	if (memctrl2 & LEON_MCFG2_SRAMDIS) {
		if (memctrl2 & LEON_MCFG2_SDRAMEN) {
			i = (memctrl2 & LEON_MCFG2_SDRAMBANKSZ)
			     >> LEON_MCFG2_SDRAMBANKSZ_SHIFT;
			spi.totphys.num_bytes = (4 << i)*1024*1024;

                        {
                          // test for 2. sdram bank 
                          unsigned long addr = 0x40000000+spi.totphys.num_bytes;
                          unsigned long old1 = *(unsigned long*)(addr);
                          unsigned long old2 = *(unsigned long*)(addr+4);
                          *(unsigned long*)(addr) = old1 + 1;
                          *(unsigned long*)(addr+4) = old1 + 2;
                          if ((old1+1) == *(unsigned long*)(addr)) {
                            spi.totphys.num_bytes = spi.totphys.num_bytes + spi.totphys.num_bytes;
                            banks++;
                          }
                          *(unsigned long*)(addr) = old1;
                          *(unsigned long*)(addr+4) = old2;
                        }
                        
		} else {
                  while(1) { //puts("Neather SRAM not SDRAM is enabled\n");
                  }
                }
                
        } else {
		i = (memctrl2 & LEON_MCFG2_SRAMBANKSZ)
		     >> LEON_MCFG2_SRAMBANKSZ_SHIFT;
		spi.totphys.num_bytes = (8 << i)*1024; // starting from 8 k 
                
                if (memctrl2 & LEON_MCFG2_SDRAMEN) {
//puts("Note: Numa architecture not supported. Not useing sdram.\n");
                }

                {
                  // test for 2.-4. sdram bank 
                  unsigned long sz = spi.totphys.num_bytes;
                  unsigned long j,addr = 0x40000000+sz;
                  for (j = 0;j < 3;j++,addr = addr+sz) {
                    unsigned long old1 = *(unsigned long*)(addr);
                    unsigned long old2 = *(unsigned long*)(addr+4);
                    *(unsigned long*)(addr) = old1 + 1;
                    *(unsigned long*)(addr+4) = old1 + 2;
                    if (old1+1 == *(unsigned long*)(addr)) {
                      spi.totphys.num_bytes = spi.totphys.num_bytes + sz;
                      banks++;
                    }
                    *(unsigned long*)(addr) = old1;
                    *(unsigned long*)(addr+4) = old2;
                  }
                }
        }
        if (!spi.totphys.num_bytes) {
		leon_halt();
                }
        */
        //puts("prom_stage2.c: lolevel-config MCFG1: 0x%x MCFG2: 0x%x => 0x%x(%i banks)\n",memctrl1,memctrl2,spi.totphys.num_bytes,banks);
        sp = sp - LEONSETUP_MEM_BASEADDR /*0x40000000*/; 
        spi.totphys.num_bytes = (sp + 0x1000) & ~(0xfff);
        //puts("prom_stage2.c: sp-memsize-config sp: 0x%x             => 0x%x\n",sp,spi.totphys.num_bytes);

	spi.avail.num_bytes = spi.totphys.num_bytes;

	ptr = (unsigned char *)&spi.idprom;
	for (i = cksum = 0; i <= 0x0E; i++)
		  cksum ^= *ptr++;
	spi.idprom.id_cksum = cksum;
}

__inline__ void mark()
{
	__asm__ __volatile__(
         "sethi	%%hi(%0), %%l0    \n\t" \
  	 "st    %%g0,[%%lo(%0)+%%l0]\n\t" \
	 : : "i" (LEONSETUP_MEM_BASEADDR) : "l0" );
}

extern unsigned short bss_start,bss_end;

/* mark as section .img.main.text, to be referenced in linker script */
int __attribute__ ((__section__ (".img.main.text"))) __main(void){ 

        char *c;
	void (*kernel)(struct linux_romvec *);

	/* clear bss */
	c = (char *)&bss_start;
	while (c < ((char *)&bss_end) ) { *c=0; c++; }
	
	/* init prom info struct */
	
	leon_prom_init();

#ifdef CONFIG_KERNEL_ROOTMEM_ROMFS
	/* boot options */
	
	root_dev           = 0x100; /* HACK: was Root_RAM0; */
	root_flags         = 0x0800 | RAMDISK_LOAD_FLAG;
	root_mountflags   |= MS_RDONLY;

	sparc_ramdisk_image = (unsigned long)&initrd_start 
				- LEONSETUP_MEM_BASEADDR;
	sparc_ramdisk_size = &initrd_end - &initrd_start;
#endif

	/* mark as used for bootloader */
	mark();
	
	/* turn on mmu */
	
	extern unsigned long _bootloader_ph;
	srmmu_set_ctable_ptr(&_bootloader_ph /*LEONSETUP_MEM_BASEADDR + PAGE_SIZE*/);
	//srmmu_set_ctable_ptr(LEONSETUP_MEM_BASEADDR + PAGE_SIZE);
	srmmu_set_context(0);
	__asm__ __volatile__("flush\n\t");
	srmmu_set_mmureg(0x00000001); 
        leon_flush_tlb_all();
	void leon_flush_cache_all();

	/* call kernel */
	
	kernel = (void (*)(struct linux_romvec*)) KERNBASE+LOAD_ADDR;
	kernel(__va(&spi.romvec));
	
	return 1;
}
