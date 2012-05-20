/* 
 * Copyright (C) 2004 Konrad Eisele (eiselekd@web.de), Gaisler Research
 * Copyright (C) 2004 Stefan Holst (mail@s-holst.de), Uni-Stuttgart
 */

#ifndef LEON_H_INCLUDE
#define LEON_H_INCLUDE

#if defined(CONFIG_LEON) || defined(CONFIG_LEON_3)

#include <asm/vaddrs.h>

/* memory mapped leon control registers */
#define LEON_PREGS	0x80000000
#define LEON_MCFG1	0x00
#define LEON_MCFG2	0x04
#define LEON_ECTRL	0x08
#define LEON_FADDR	0x0c
#define LEON_MSTAT	0x10
#define LEON_CCTRL	0x14
#define LEON_PWDOWN	0x18
#define LEON_WPROT1	0x1C
#define LEON_WPROT2	0x20
#define LEON_LCONF	0x24
#define LEON_TCNT0	0x40
#define LEON_TRLD0	0x44
#define LEON_TCTRL0	0x48
#define LEON_TCNT1	0x50
#define LEON_TRLD1	0x54
#define LEON_TCTRL1	0x58
#define LEON_SCNT	0x60
#define LEON_SRLD	0x64
#define LEON_UART0	0x70
#define LEON_UDATA0	0x70
#define LEON_USTAT0	0x74
#define LEON_UCTRL0	0x78
#define LEON_USCAL0	0x7c
#define LEON_UART1	0x80
#define LEON_UDATA1	0x80
#define LEON_USTAT1	0x84
#define LEON_UCTRL1	0x88
#define LEON_USCAL1	0x8c
#define LEON_IMASK	0x90
#define LEON_IPEND	0x94
#define LEON_IFORCE	0x98
#define LEON_ICLEAR	0x9c
#define LEON_IOREG	0xA0
#define LEON_IODIR	0xA4
#define LEON_IOICONF	0xA8
#define LEON_IPEND2	0xB0
#define LEON_IMASK2	0xB4
#define LEON_ISTAT2	0xB8
#define LEON_ICLEAR2	0xBC

#define ASI_LEON_NOCACHE	0x01

#ifndef CONFIG_LEON_3

/* ASI codes */
#define ASI_LEON_PCI		0x04
#define ASI_LEON_IFLUSH		0x05
#define ASI_LEON_DFLUSH		0x06
#define ASI_LEON_ITAG		0x0c
#define ASI_LEON_IDATA		0x0d
#define ASI_LEON_DTAG		0x0e
#define ASI_LEON_DDATA		0x0f
#define ASI_LEON_MMUFLUSH	0x18
#define ASI_LEON_MMUREGS	0x19
#define ASI_LEON_BYPASS		0x1c
#define ASI_LEON_FLUSH_PAGE	0x10
/*
#define ASI_LEON_FLUSH_SEGMENT	0x11
#define ASI_LEON_FLUSH_REGION	0x12
*/
#define ASI_LEON_FLUSH_CTX	0x13
#define ASI_LEON_DCTX		0x14
#define ASI_LEON_ICTX		0x15
#define ASI_MMU_DIAG		0x1d

#define ASI_LEON_DCACHE_MISS	0x1

#else

#define ASI_LEON_DCACHE_MISS	0x1

#define ASI_LEON_CACHEREGS 0x02
#define ASI_LEON_IFLUSH		0x10
#define ASI_LEON_DFLUSH		0x11

#define ASI_LEON_MMUFLUSH	0x18
#define ASI_LEON_MMUREGS	0x19
#define ASI_LEON_BYPASS		0x1c
#define ASI_LEON_FLUSH_PAGE	0x10

/*
constant ASI_SYSR    : asi_type := "00010"; -- 0x02
constant ASI_UINST   : asi_type := "01000"; -- 0x08
constant ASI_SINST   : asi_type := "01001"; -- 0x09
constant ASI_UDATA   : asi_type := "01010"; -- 0x0A
constant ASI_SDATA   : asi_type := "01011"; -- 0x0B
constant ASI_ITAG    : asi_type := "01100"; -- 0x0C
constant ASI_IDATA   : asi_type := "01101"; -- 0x0D
constant ASI_DTAG    : asi_type := "01110"; -- 0x0E
constant ASI_DDATA   : asi_type := "01111"; -- 0x0F
constant ASI_IFLUSH  : asi_type := "10000"; -- 0x10
constant ASI_DFLUSH  : asi_type := "10001"; -- 0x11

constant ASI_FLUSH_PAGE     : std_logic_vector(4 downto 0) := "10000";  -- 0x10 i/dcache flush page
constant ASI_FLUSH_CTX      : std_logic_vector(4 downto 0) := "10011";  -- 0x13 i/dcache flush ctx

constant ASI_DCTX           : std_logic_vector(4 downto 0) := "10100";  -- 0x14 dcache ctx
constant ASI_ICTX           : std_logic_vector(4 downto 0) := "10101";  -- 0x15 icache ctx

constant ASI_MMUFLUSHPROBE  : std_logic_vector(4 downto 0) := "11000";  -- 0x18 i/dtlb flush/(probe)
constant ASI_MMUREGS        : std_logic_vector(4 downto 0) := "11001";  -- 0x19 mmu regs access
constant ASI_MMU_BP         : std_logic_vector(4 downto 0) := "11100";  -- 0x1c mmu Bypass 
constant ASI_MMU_DIAG       : std_logic_vector(4 downto 0) := "11101";  -- 0x1d mmu diagnostic 
constant ASI_MMU_DSU        : std_logic_vector(4 downto 0) := "11111";  -- 0x1f mmu diagnostic 
*/
#endif

/* mmu register access, ASI_LEON_MMUREGS */
#define LEON_CNR_CTRL		0x000
#define LEON_CNR_CTXP		0x100
#define LEON_CNR_CTX		0x200
#define LEON_CNR_F		0x300
#define LEON_CNR_FADDR		0x400

#define LEON_CNR_CTX_NCTX	256	/*number of MMU ctx */

#define LEON_CNR_CTRL_TLBDIS	0x80000000

#define LEON_MMUTLB_ENT_MAX	64

/*
 * diagnostic access from mmutlb.vhd:
 * 0: pte address
 * 4: pte
 * 8: additional flags
 */
#define LEON_DIAGF_LVL		0x3
#define LEON_DIAGF_WR		0x8
#define LEON_DIAGF_WR_SHIFT	3
#define LEON_DIAGF_HIT		0x10
#define LEON_DIAGF_HIT_SHIFT	4
#define LEON_DIAGF_CTX		0x1fe0
#define LEON_DIAGF_CTX_SHIFT	5
#define LEON_DIAGF_VALID	0x2000
#define LEON_DIAGF_VALID_SHIFT	13

/*
 *  Interrupt Sources
 *
 *  The interrupt source numbers directly map to the trap type and to 
 *  the bits used in the Interrupt Clear, Interrupt Force, Interrupt Mask,
 *  and the Interrupt Pending Registers.
 */
#define LEON_INTERRUPT_CORRECTABLE_MEMORY_ERROR	1
#define LEON_INTERRUPT_UART_1_RX_TX		2
#define LEON_INTERRUPT_UART_0_RX_TX		3
#define LEON_INTERRUPT_EXTERNAL_0		4
#define LEON_INTERRUPT_EXTERNAL_1		5
#define LEON_INTERRUPT_EXTERNAL_2		6
#define LEON_INTERRUPT_EXTERNAL_3		7
#define LEON_INTERRUPT_TIMER1			8
#define LEON_INTERRUPT_TIMER2			9
#define LEON_INTERRUPT_EMPTY1			10
#define LEON_INTERRUPT_EMPTY2			11
#define LEON_INTERRUPT_OPEN_ETH			12
#define LEON_INTERRUPT_EMPTY4			13
#define LEON_INTERRUPT_EMPTY5			14
#define LEON_INTERRUPT_EMPTY6			15

/* irq masks */
#define LEON_HARD_INT(x)	(1 << (x))	/* irq 0-15 */
#define LEON_IRQMASK_R		0x0000fffe	/* bit 15- 1 of lregs.irqmask */
#define LEON_IRQPRIO_R		0xfffe0000	/* bit 31-17 of lregs.irqmask */

/* leon uart register definitions */
#define LEON_OFF_UDATA	0x0
#define LEON_OFF_USTAT	0x4
#define LEON_OFF_UCTRL	0x8
#define LEON_OFF_USCAL	0xc

#define LEON_UCTRL_RE	0x01
#define LEON_UCTRL_TE	0x02
#define LEON_UCTRL_RI	0x04
#define LEON_UCTRL_TI	0x08
#define LEON_UCTRL_PS	0x10
#define LEON_UCTRL_PE	0x20
#define LEON_UCTRL_FL	0x40
#define LEON_UCTRL_LB	0x80

#define LEON_USTAT_DR	0x01
#define LEON_USTAT_TS	0x02
#define LEON_USTAT_TH	0x04
#define LEON_USTAT_BR	0x08
#define LEON_USTAT_OV	0x10
#define LEON_USTAT_PE	0x20
#define LEON_USTAT_FE	0x40

#define LEON_MCFG2_SRAMDIS		0x00002000
#define LEON_MCFG2_SDRAMEN		0x00004000
#define LEON_MCFG2_SRAMBANKSZ		0x00001e00	/* [12-9] */
#define LEON_MCFG2_SRAMBANKSZ_SHIFT	9
#define LEON_MCFG2_SDRAMBANKSZ		0x03800000	/* [25-23] */
#define LEON_MCFG2_SDRAMBANKSZ_SHIFT	23

#define LEON_TCNT0_MASK	0x7fffff

#define LEON_USTAT_ERROR (LEON_USTAT_OV|LEON_USTAT_PE|LEON_USTAT_FE)	/*no break yet */

#ifdef CONFIG_OPEN_ETH
#define LEON_ETH_BASE_ADD ((unsigned long)LEON_VA_ETHERMAC)
/* map leon on ethermac adress space at pa 0xb0000000 */
#define LEON_VA_ETHERMAC     DVMA_VADDR
#endif

#ifndef __ASSEMBLY__

/* do a virtual address read without cache */
static __inline__ unsigned long leon_readnobuffer_reg(unsigned long paddr)
{
	unsigned long retval;
	__asm__ __volatile__("lda [%1] %2, %0\n\t":
			     "=r"(retval): "r"(paddr), "i"(ASI_LEON_NOCACHE));
	return retval;
}

/* do a physical address bypass write, i.e. for 0x80000000 */
static __inline__ void leon_store_reg(unsigned long paddr, unsigned long value)
{
	__asm__ __volatile__("sta %0, [%1] %2\n\t"::"r"(value), "r"(paddr),
			     "i"(ASI_LEON_BYPASS):"memory");
}

/* do a physical address bypass load, i.e. for 0x80000000 */
static __inline__ unsigned long leon_load_reg(unsigned long paddr)
{
	unsigned long retval;
	__asm__ __volatile__("lda [%1] %2, %0\n\t":
			     "=r"(retval): "r"(paddr), "i"(ASI_LEON_BYPASS));
	return retval;
}

extern __inline__ void leon_srmmu_disabletlb(void)
{
	unsigned int retval;
	__asm__ __volatile__("lda [%%g0] %2, %0\n\t":"=r"(retval):"r"(0),
			     "i"(ASI_LEON_MMUREGS));
	retval |= LEON_CNR_CTRL_TLBDIS;
	__asm__ __volatile__("sta %0, [%%g0] %2\n\t"::"r"(retval), "r"(0),
			     "i"(ASI_LEON_MMUREGS):"memory");
}

extern __inline__ void leon_srmmu_enabletlb(void)
{
	unsigned int retval;
	__asm__ __volatile__("lda [%%g0] %2, %0\n\t":"=r"(retval):"r"(0),
			     "i"(ASI_LEON_MMUREGS));
	retval = retval & ~LEON_CNR_CTRL_TLBDIS;
	__asm__ __volatile__("sta %0, [%%g0] %2\n\t"::"r"(retval), "r"(0),
			     "i"(ASI_LEON_MMUREGS):"memory");
}

#define LEON_BYPASS_LOAD_PA(x)		leon_load_reg ((unsigned long)(x))
#define LEON_BYPASSCACHE_LOAD_VA(x)	leon_readnobuffer_reg ((unsigned long)(x))
#define LEON_BYPASS_STORE_PA(x,v)	leon_store_reg((unsigned long)(x),(unsigned long)(v))
#define LEON_REGLOAD_PA(x)		leon_load_reg ((unsigned long)(x)+LEON_PREGS)
#define LEON_REGSTORE_PA(x,v)		leon_store_reg((unsigned long)(x)+LEON_PREGS,(unsigned long)(v))
#define LEON_REGSTORE_OR_PA(x,v)	LEON_REGSTORE_PA(x,LEON_REGLOAD_PA(x)|(unsigned long)(v))
#define LEON_REGSTORE_AND_PA(x,v)	LEON_REGSTORE_PA(x,LEON_REGLOAD_PA(x)&(unsigned long)(v))

extern unsigned long srmmu_swprobe(unsigned long vaddr, unsigned long *paddr);
extern void leon_inherit_prom_mappings(unsigned long start, unsigned long end);
extern void leon23_wait_for(int ms);

/*#define LEONSETUP_MEM_BASEADDR 0x40000000*/

extern void console_print_LEON(const char *p);
#define HARDDBG_PRINTF(fmt,arg...) do {   \
        char b[1000];                     \
        sprintf(b,fmt,##arg);             \
        console_print_LEON(b); } while (0)
#define HARDDBG_FUNC            HARDDBG_PRINTF("[->%03d @ %22s()]:\n" , __LINE__, __FUNCTION__);
#define HARDDBG_FUNCOUT         HARDDBG_PRINTF("[<-%03d @ %22s()]:\n" , __LINE__, __FUNCTION__);
#define HARDDBG_OUT(fmt,arg...) HARDDBG_PRINTF("[->%03d @ %22s()]:" fmt , __LINE__, __FUNCTION__,##arg);

#endif				/* !ASM */

#ifdef CONFIG_LEON_3
#include <asm/leon3.h>
#endif

#endif				//defined(CONFIG_LEON) || defined(CONFIG_LEON_3)

#endif
