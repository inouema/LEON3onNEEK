/* 
 * Copyright (C) 2004 Konrad Eisele (eiselekd@web.de, konrad@gaisler.com), Gaisler Research
 * Copyright (C) 2004 Stefan Holst (mail@s-holst.de), Uni-Stuttgart
 * Copyright (C) 2009 Daniel Hellstrom (daniel@gaisler.com), Konrad Eisele (konrad@gaisler.com) Gaisler-Aeroflex AB 
 */

#ifndef LEON_H_INCLUDE
#define LEON_H_INCLUDE

#if defined(CONFIG_LEON) 

#define ASI_LEON_NOCACHE	0x01

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
			     "=r"(retval):"r"(paddr), "i"(ASI_LEON_NOCACHE));
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
			     "=r"(retval):"r"(paddr), "i"(ASI_LEON_BYPASS));
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

#define LEON3_BYPASS_LOAD_PA(x)	(leon_load_reg ((unsigned long)(x)))
#define LEON3_BYPASS_STORE_PA(x,v) (leon_store_reg ((unsigned long)(x),(unsigned long)(v)))
#define LEON3_BYPASS_ANDIN_PA(x,v) LEON3_BYPASS_STORE_PA(x,LEON3_BYPASS_LOAD_PA(x) & v)
#define LEON3_BYPASS_ORIN_PA(x,v) LEON3_BYPASS_STORE_PA(x,LEON3_BYPASS_LOAD_PA(x) | v)

#define LEON_BYPASS_LOAD_PA(x)		leon_load_reg ((unsigned long)(x))
#define LEON_BYPASSCACHE_LOAD_VA(x)	leon_readnobuffer_reg ((unsigned long)(x))
#define LEON_BYPASS_STORE_PA(x,v)	leon_store_reg((unsigned long)(x),(unsigned long)(v))
#define LEON_REGLOAD_PA(x)		leon_load_reg ((unsigned long)(x)+LEON_PREGS)
#define LEON_REGSTORE_PA(x,v)		leon_store_reg((unsigned long)(x)+LEON_PREGS,(unsigned long)(v))
#define LEON_REGSTORE_OR_PA(x,v)	LEON_REGSTORE_PA(x,LEON_REGLOAD_PA(x)|(unsigned long)(v))
#define LEON_REGSTORE_AND_PA(x,v)	LEON_REGSTORE_PA(x,LEON_REGLOAD_PA(x)&(unsigned long)(v))

/*#define LEONSETUP_MEM_BASEADDR 0x40000000*/

#define HARDDBG_PRINTF(fmt,arg...) do {   \
        char b[1000];                     \
        sprintf(b,fmt,##arg);             \
        console_print_LEON(b); } while (0)
#define HARDDBG_FUNC            HARDDBG_PRINTF("[->%03d @ %22s()]:\n" , __LINE__, __FUNCTION__);
#define HARDDBG_FUNCOUT         HARDDBG_PRINTF("[<-%03d @ %22s()]:\n" , __LINE__, __FUNCTION__);
#define HARDDBG_OUT(fmt,arg...) HARDDBG_PRINTF("[->%03d @ %22s()]:" fmt , __LINE__, __FUNCTION__,##arg);

#endif /* !ASM */

#if 1

#ifndef __ASSEMBLER__

/*
 *  The following defines the bits in the LEON UART Status Registers.
 */

#define LEON_REG_UART_STATUS_DR   0x00000001	/* Data Ready */
#define LEON_REG_UART_STATUS_TSE  0x00000002	/* TX Send Register Empty */
#define LEON_REG_UART_STATUS_THE  0x00000004	/* TX Hold Register Empty */
#define LEON_REG_UART_STATUS_BR   0x00000008	/* Break Error */
#define LEON_REG_UART_STATUS_OE   0x00000010	/* RX Overrun Error */
#define LEON_REG_UART_STATUS_PE   0x00000020	/* RX Parity Error */
#define LEON_REG_UART_STATUS_FE   0x00000040	/* RX Framing Error */
#define LEON_REG_UART_STATUS_ERR  0x00000078	/* Error Mask */

/*
 *  The following defines the bits in the LEON UART Ctrl Registers.
 */

#define LEON_REG_UART_CTRL_RE     0x00000001	/* Receiver enable */
#define LEON_REG_UART_CTRL_TE     0x00000002	/* Transmitter enable */
#define LEON_REG_UART_CTRL_RI     0x00000004	/* Receiver interrupt enable */
#define LEON_REG_UART_CTRL_TI     0x00000008	/* Transmitter interrupt enable */
#define LEON_REG_UART_CTRL_PS     0x00000010	/* Parity select */
#define LEON_REG_UART_CTRL_PE     0x00000020	/* Parity enable */
#define LEON_REG_UART_CTRL_FL     0x00000040	/* Flow control enable */
#define LEON_REG_UART_CTRL_LB     0x00000080	/* Loop Back enable */

#define LEON3_GPTIMER_EN 1
#define LEON3_GPTIMER_RL 2
#define LEON3_GPTIMER_LD 4
#define LEON3_GPTIMER_IRQEN 8
#define LEON3_GPTIMER_SEPIRQ 8

#define LEON23_REG_TIMER_CONTROL_EN    0x00000001	/* 1 = enable counting */
						   /* 0 = hold scalar and counter */
#define LEON23_REG_TIMER_CONTROL_RL    0x00000002	/* 1 = reload at 0 */
						   /* 0 = stop at 0 */
#define LEON23_REG_TIMER_CONTROL_LD    0x00000004	/* 1 = load counter */
						   /* 0 = no function */
#define LEON23_REG_TIMER_CONTROL_IQ    0x00000008	/* 1 = irq enable */
						   /* 0 = no function */

/*
 *  The following defines the bits in the LEON PS/2 Status Registers.
 */

#define LEON_REG_PS2_STATUS_DR   0x00000001	/* Data Ready */
#define LEON_REG_PS2_STATUS_PE   0x00000002	/* Parity error */
#define LEON_REG_PS2_STATUS_FE   0x00000004	/* Framing error */
#define LEON_REG_PS2_STATUS_KI   0x00000008	/* Keyboard inhibit */
#define LEON_REG_PS2_STATUS_RF   0x00000010	/* RX buffer full */
#define LEON_REG_PS2_STATUS_TF   0x00000020	/* TX buffer full */

/*
 *  The following defines the bits in the LEON PS/2 Ctrl Registers.
 */

#define LEON_REG_PS2_CTRL_RE     0x00000001	/* Receiver enable */
#define LEON_REG_PS2_CTRL_TE     0x00000002	/* Transmitter enable */
#define LEON_REG_PS2_CTRL_RI     0x00000004	/* Keyboard receive interrupt  */
#define LEON_REG_PS2_CTRL_TI     0x00000008	/* Keyboard transmit interrupt */

#define LEON3_IRQMPSTATUS_CPUNR     28
#define LEON3_IRQMPSTATUS_BROADCAST 27

struct amba_prom_registers {
	unsigned int phys_addr;	/* The physical address of this register */
	unsigned int reg_size;	/* How many bytes does this register take up? */
};

typedef struct {
	volatile unsigned int ilevel;
	volatile unsigned int ipend;
	volatile unsigned int iforce;
	volatile unsigned int iclear;
	volatile unsigned int mpstatus;
	volatile unsigned int mpbroadcast;
	volatile unsigned int notused02;
	volatile unsigned int notused03;
	volatile unsigned int notused10;
	volatile unsigned int notused11;
	volatile unsigned int notused12;
	volatile unsigned int notused13;
	volatile unsigned int notused20;
	volatile unsigned int notused21;
	volatile unsigned int notused22;
	volatile unsigned int notused23;
	volatile unsigned int mask[16];
	volatile unsigned int force[16];
	/* Extended IRQ registers */
	volatile unsigned int intid[16];	/* 0xc0 */
} LEON3_IrqCtrl_Regs_Map;

typedef struct {
	volatile unsigned int data;
	volatile unsigned int status;
	volatile unsigned int ctrl;
	volatile unsigned int scaler;
} LEON3_APBUART_Regs_Map;

typedef struct {
	volatile unsigned int val;
	volatile unsigned int rld;
	volatile unsigned int ctrl;
	volatile unsigned int unused;
} LEON3_GpTimerElem_Regs_Map;

typedef struct {
	volatile unsigned int scalar;
	volatile unsigned int scalar_reload;
	volatile unsigned int config;
	volatile unsigned int unused;
	volatile LEON3_GpTimerElem_Regs_Map e[8];
} LEON3_GpTimer_Regs_Map;

#define GPTIMER_CONFIG_IRQNT(a) (((a) >> 3) & 0x1f)
#define GPTIMER_CONFIG_ISSEP(a) ((a)&(1<<8))
#define GPTIMER_CONFIG_NTIMERS(a) ((a)&(0x7))
#define LEON3_GPTIMER_CTRL_PENDING 0x10
#define LEON3_GPTIMER_CONFIG_NRTIMERS(c) ((c)->config & 0x7)
#define LEON3_GPTIMER_CTRL_ISPENDING(r) (((r)&LEON3_GPTIMER_CTRL_PENDING)?1:0)

typedef void (*GPTIMER_CALLBACK) (void);
typedef struct _sparc_gptimer {
	LEON3_GpTimer_Regs_Map *inst;
	unsigned int ctrl, reload, value, scalarreload;
	int irq, flags, idxinst, idx, enabled, connected, minscalar;
	int ticksPerSecond, stat;
	GPTIMER_CALLBACK callback;
	int arg;
} sparc_gptimer;

#define GPTIMER_INST_TIMER_MAX 8
typedef struct _sparc_gptimer_inst {
	LEON3_GpTimer_Regs_Map *base;
	unsigned int scalarreload;
	int count, baseirq, free, config, connected, minscalar;
	sparc_gptimer timers[GPTIMER_INST_TIMER_MAX];
} sparc_gptimer_inst;

typedef struct {
	volatile unsigned int iodata;
	volatile unsigned int ioout;
	volatile unsigned int iodir;
	volatile unsigned int irqmask;
	volatile unsigned int irqpol;
	volatile unsigned int irqedge;
} LEON3_IOPORT_Regs_Map;

typedef struct {
	volatile unsigned int write;
	volatile unsigned int dummy;
	volatile unsigned int txcolor;
	volatile unsigned int bgcolor;
} LEON3_VGA_Regs_Map;

typedef struct {
	volatile unsigned int status;	/* 0x00 */
	volatile unsigned int video_length;	/* 0x04 */
	volatile unsigned int front_porch;	/* 0x08 */
	volatile unsigned int sync_length;	/* 0x0c */
	volatile unsigned int line_length;	/* 0x10 */
	volatile unsigned int fb_pos;	/* 0x14 */
	volatile unsigned int clk_vector[4];	/* 0x18 */
	volatile unsigned int clut;	/* 0x28 */
} LEON3_GRVGA_Regs_Map;

typedef struct {
	volatile unsigned int data;
	volatile unsigned int status;
	volatile unsigned int ctrl;
	volatile unsigned int reload;
} LEON3_APBPS2_REGS_Map;

typedef struct {
	volatile unsigned int cfg_stat;
	volatile unsigned int bar0;
	volatile unsigned int page0;
	volatile unsigned int bar1;
	volatile unsigned int page1;
	volatile unsigned int iomap;
	volatile unsigned int stat_cmd;
	volatile unsigned int irq;
} LEON3_GRPCI_Regs_Map;

/*
 *  Types and structure used for AMBA Plug & Play bus scanning 
 */

#define AMBA_MAXAPB_DEVS 64
#define AMBA_MAXAPB_DEVS_PERBUS 16

typedef struct amba_device_table {
	int devnr;		/* number of devices on AHB or APB bus */
	unsigned int *addr[16];	/* addresses to the devices configuration tables */
	unsigned int allocbits[1];	/* 0=unallocated, 1=allocated driver */
} amba_device_table;

typedef struct amba_apbslv_device_table {
	int devnr;		/* number of devices on AHB or APB bus */
	unsigned int *addr[AMBA_MAXAPB_DEVS];	/* addresses to the devices configuration tables */
	unsigned int apbmst[AMBA_MAXAPB_DEVS];	/* apb master if a entry is a apb slave */
	unsigned int apbmstidx[AMBA_MAXAPB_DEVS];	/* apb master idx if a entry is a apb slave */
	unsigned int allocbits[4];	/* 0=unallocated, 1=allocated driver */
} amba_apbslv_device_table;

typedef struct _amba_confarea_type {
	struct _amba_confarea_type *next;	/* next bus in chain */
	amba_device_table ahbmst;
	amba_device_table ahbslv;
	amba_apbslv_device_table apbslv;
	unsigned int apbmst;
} amba_confarea_type;

// collect apb slaves
typedef struct amba_apb_device {
	unsigned int start, irq, bus_id;
	amba_confarea_type *bus;
} amba_apb_device;

// collect ahb slaves
typedef struct amba_ahb_device {
	unsigned int start[4], irq, bus_id;
	amba_confarea_type *bus;
} amba_ahb_device;

extern void sparc_leon_eirq_register(int eirq);

#if defined(CONFIG_SMP) 
# define LEON3_IRQ_RESCHEDULE		13
# define LEON3_IRQ_TICKER		(leon_percpu_timer_dev[0].irq)
# define LEON3_IRQ_CROSS_CALL		15
#endif

#define ASI_LEON3_SYSCTRL		0x02
#define ASI_LEON3_SYSCTRL_ICFG		0x08
#define ASI_LEON3_SYSCTRL_DCFG		0x0c
#define ASI_LEON3_SYSCTRL_CFG_SNOOPING (1<<27)
#define ASI_LEON3_SYSCTRL_CFG_SSIZE(c) (1<<((c>>20)&0xf))

/* GCC for the host includes this, older GCC versions complain about
 * sparc assembler if host is not a SPARC.
 */
#ifdef __sparc

extern __inline__ unsigned long sparc_leon3_get_dcachecfg(void)
{
	unsigned int retval;
	__asm__ __volatile__("lda [%1] %2, %0\n\t":
			     "=r"(retval):
			     "r"(ASI_LEON3_SYSCTRL_DCFG),
			     "i"(ASI_LEON3_SYSCTRL));
	return (retval);
}

/*enable snooping*/
extern __inline__ void sparc_leon3_enable_snooping(void)
{
	__asm__ volatile ("lda [%%g0] 2, %%l1\n\t"
			  "set 0x800000, %%l2\n\t"
			  "or  %%l2, %%l1, %%l2\n\t"
			  "sta %%l2, [%%g0] 2\n\t":::"l1", "l2");
};

extern __inline__ void sparc_leon3_disable_cache(void)
{
	__asm__ volatile ("lda [%%g0] 2, %%l1\n\t"
			  "set 0x00000f, %%l2\n\t"
			  "andn  %%l2, %%l1, %%l2\n\t"
			  "sta %%l2, [%%g0] 2\n\t":::"l1", "l2");
};
#endif

#endif //!__ASSEMBLER__

#if defined(PAGE_SIZE_LEON_8K)
#define CONFIG_PAGE_SIZE_LEON 1
#elif defined(PAGE_SIZE_LEON_16K)
#define CONFIG_PAGE_SIZE_LEON 2)
#else
#define CONFIG_PAGE_SIZE_LEON 0
#endif

#if CONFIG_PAGE_SIZE_LEON == 0
/* [ 8, 6, 6 ] + 12 */
#define LEON_PGD_SH 24
#define LEON_PGD_M  0xff
#define LEON_PMD_SH 18
#define LEON_PMD_SH_V (LEON_PGD_SH-2)
#define LEON_PMD_M  0x3f
#define LEON_PTE_SH 12
#define LEON_PTE_M  0x3f
#elif CONFIG_PAGE_SIZE_LEON == 1
/* [ 7, 6, 6 ] + 13 */
#define LEON_PGD_SH 25
#define LEON_PGD_M  0x7f
#define LEON_PMD_SH 19
#define LEON_PMD_SH_V (LEON_PGD_SH-1)
#define LEON_PMD_M  0x3f
#define LEON_PTE_SH 13
#define LEON_PTE_M  0x3f
#elif CONFIG_PAGE_SIZE_LEON == 2
/* [ 6, 6, 6 ] + 14 */
#define LEON_PGD_SH 26
#define LEON_PGD_M  0x3f
#define LEON_PMD_SH 20
#define LEON_PMD_SH_V (LEON_PGD_SH-0)
#define LEON_PMD_M  0x3f
#define LEON_PTE_SH 14
#define LEON_PTE_M  0x3f
#elif CONFIG_PAGE_SIZE_LEON == 3
/* [ 4, 7, 6 ] + 15 */
#define LEON_PGD_SH 28
#define LEON_PGD_M  0x0f
#define LEON_PMD_SH 21
#define LEON_PMD_SH_V (LEON_PGD_SH-0)
#define LEON_PMD_M  0x7f
#define LEON_PTE_SH 15
#define LEON_PTE_M  0x3f
#else
#error cannot determine CONFIG_PAGE_SIZE_LEON
#endif

#endif // LEON3

#define PAGE_MIN_SHIFT   (12)
#define PAGE_MIN_SIZE    (1UL << PAGE_MIN_SHIFT)

#define LEON3_XCCR_SETS_MASK  0x07000000UL
#define LEON3_XCCR_SSIZE_MASK 0x00f00000UL

#define LEON2_CCR_DSETS_MASK 0x03000000UL
#define LEON2_CFG_SSIZE_MASK 0x00007000UL

#ifndef __ASSEMBLY__
#define srmmu_hwprobe(addr) (srmmu_swprobe(addr,0) & SRMMU_PTE_PMASK)
extern unsigned long srmmu_swprobe(unsigned long vaddr, unsigned long *paddr);
extern void leon_flush_icache_all(void);
extern void leon_flush_dcache_all(void);
extern void leon_flush_cache_all(void);
extern void leon_flush_tlb_all(void);
extern int leon_flush_during_switch;
extern int leon_flush_needed(void);

/* struct that hold LEON3 cache configuration registers */
struct leon3_cacheregs {	/* ASI=2 Address - name */
	unsigned long ccr;	/* 0x00 - Cache Control Register  */
	unsigned long iccr;	/* 0x08 - Instruction Cache Configuration Register */
	unsigned long dccr;	/* 0x0c - Data Cache Configuration Register */
};

/* struct that hold LEON2 cache configuration register & configuration register */
struct leon2_cacheregs {
	unsigned long ccr, cfg;
};


#endif

#define LEON3_IO_AREA 0xfff00000
#define LEON3_CONF_AREA 0xff000
#define LEON3_AHB_SLAVE_CONF_AREA (1 << 11)

#define LEON3_AHB_CONF_WORDS 8
#define LEON3_APB_CONF_WORDS 2
#define LEON3_AHB_MASTERS 16
#define LEON3_AHB_SLAVES 16
#define LEON3_APB_SLAVES 16
#define LEON3_APBUARTS 8

/* Vendor codes */
#define VENDOR_GAISLER   1
#define VENDOR_PENDER    2
#define VENDOR_ESA       4
#define VENDOR_OPENCORES 8

/* Gaisler Research device id's */
#define GAISLER_LEON3    0x003
#define GAISLER_LEON3DSU 0x004
#define GAISLER_ETHAHB   0x005
#define GAISLER_APBMST   0x006
#define GAISLER_AHBUART  0x007
#define GAISLER_SRCTRL   0x008
#define GAISLER_SDCTRL   0x009
#define GAISLER_APBUART  0x00C
#define GAISLER_IRQMP    0x00D
#define GAISLER_AHBRAM   0x00E
#define GAISLER_GPTIMER  0x011
#define GAISLER_PCITRG   0x012
#define GAISLER_PCISBRG  0x013
#define GAISLER_PCIFBRG  0x014
#define GAISLER_PCITRACE 0x015
#define GAISLER_PCIDMA   0x016
#define GAISLER_AHBTRACE 0x017
#define GAISLER_ETHDSU   0x018
#define GAISLER_PIOPORT  0x01A
#define GAISLER_GRGPIO   0x01A
#define GAISLER_AHBJTAG  0x01c
#define GAISLER_ETHMAC   0x01D
#define GAISLER_AHB2AHB  0x020
#define GAISLER_USBDC    0x021
#define GAISLER_ATACTRL  0x024
#define GAISLER_DDRSPA   0x025
#define GAISLER_USBEHC   0x026
#define GAISLER_USBUHC   0x027
#define GAISLER_I2CMST   0x028
#define GAISLER_SPICTRL  0x02D
#define GAISLER_DDR2SPA  0x02E
#define GAISLER_SPIMCTRL 0x045
#define GAISLER_LEON4    0x048
#define GAISLER_LEON4DSU 0x049
#define GAISLER_AHBSTAT  0x052
#define GAISLER_FTMCTRL  0x054
#define GAISLER_KBD      0x060
#define GAISLER_VGA      0x061
#define GAISLER_SVGA     0x063
#define GAISLER_GRSYSMON 0x066
#define GAISLER_GRACECTRL 0x067

#define GAISLER_L2TIME   0xffd	/* internal device: leon2 timer */
#define GAISLER_L2C      0xffe	/* internal device: leon2compat */
#define GAISLER_PLUGPLAY 0xfff	/* internal device: plug & play configarea */

#define amba_vendor(x) (((x) >> 24) & 0xff)

#define amba_device(x) (((x) >> 12) & 0xfff)

#endif //defined(CONFIG_LEON)

#endif
