/*
 *  linux/arch/sparc/mm/leon.c
 *
 * Copyright (C) 2004 Konrad Eisele (eiselekd@web.de, konrad@gaisler.com), Gaisler Research
 * Copyright (C) 2009 Daniel Hellstrom (daniel@gaisler.com), Konrad Eisele (konrad@gaisler.com) Gaisler-Aeroflex AB 
 *
 * do srmmu probe in software
 */

#include <linux/kernel.h>
#include <linux/mm.h>
#include <asm/asi.h>
#include <asm/leon.h>

int leon_flush_during_switch = 1;

#define PFN(x) ((x) >> PAGE_SHIFT)
extern unsigned long last_valid_pfn;
/* max_mapnr not initialized yet */
#define _pfn_valid(pfn)	((pfn < last_valid_pfn) && (pfn >= PFN(phys_base)))
#define _SRMMU_PTE_PMASK 0xffffffff

int srmmu_swprobe_trace = 0;
unsigned long srmmu_swprobe(unsigned long vaddr, unsigned long *paddr)
{

	unsigned int ctxtbl;
	unsigned int pgd, pmd, ped;
	unsigned int ptr;
	unsigned int lvl, pte, paddrbase;
	unsigned int ctx;
	unsigned int paddr_calc;

	paddrbase = 0;

	if (srmmu_swprobe_trace) {
		printk("swprobe: trace on\n");
	}

	if (!(ctxtbl = srmmu_get_ctable_ptr())) {
		if (srmmu_swprobe_trace) {
			printk("swprobe: srmmu_get_ctable_ptr returned 0=>0\n");
		}
		return 0;
	}
	if (!_pfn_valid(PFN(ctxtbl))) {
		if (srmmu_swprobe_trace) {
			printk("swprobe: !_pfn_valid(%x)=>0\n", PFN(ctxtbl));
		}
		return 0;
	}

	ctx = srmmu_get_context();
	if (srmmu_swprobe_trace) {
		printk("swprobe:  --- ctx (%x) ---\n", ctx);
	}

	pgd = LEON_BYPASS_LOAD_PA(ctxtbl + (ctx * 4));

	if (((pgd & SRMMU_ET_MASK) == SRMMU_ET_PTE)) {
		if (srmmu_swprobe_trace) {
			printk("swprobe: pgd is entry level 3\n");
		}
		lvl = 3;
		pte = pgd;
		paddrbase = pgd & _SRMMU_PTE_PMASK;
		goto ready;
	}
	if (((pgd & SRMMU_ET_MASK) != SRMMU_ET_PTD)) {
		if (srmmu_swprobe_trace) {
			printk("swprobe: pgd is invalid => 0\n");
		}
		return 0;
	}

	if (srmmu_swprobe_trace) {
		printk("swprobe:  --- pgd (%x) ---\n", pgd);
	}

	ptr = (pgd & SRMMU_PTD_PMASK) << 4;
	ptr += ((((vaddr) >> LEON_PGD_SH) & LEON_PGD_M) * 4);
	if (!_pfn_valid(PFN(ptr))) {
		return 0;
	}

	pmd = LEON_BYPASS_LOAD_PA(ptr);
	if (((pmd & SRMMU_ET_MASK) == SRMMU_ET_PTE)) {
		if (srmmu_swprobe_trace) {
			printk("swprobe: pmd is entry level 2\n");
		}
		lvl = 2;
		pte = pmd;
		paddrbase = pmd & _SRMMU_PTE_PMASK;
		goto ready;
	}
	if (((pmd & SRMMU_ET_MASK) != SRMMU_ET_PTD)) {
		if (srmmu_swprobe_trace) {
			printk("swprobe: pmd is invalid => 0\n");
		}
		return 0;
	}

	if (srmmu_swprobe_trace) {
		printk("swprobe:  --- pmd (%x) ---\n", pmd);
	}

	ptr = (pmd & SRMMU_PTD_PMASK) << 4;
	ptr += (((vaddr >> LEON_PMD_SH) & LEON_PMD_M) * 4);
	if (!_pfn_valid(PFN(ptr))) {
		if (srmmu_swprobe_trace) {
			printk("swprobe: !_pfn_valid(%x)=>0\n", PFN(ptr));
		}
		return 0;
	}

	ped = LEON_BYPASS_LOAD_PA(ptr);

	if (((ped & SRMMU_ET_MASK) == SRMMU_ET_PTE)) {
		if (srmmu_swprobe_trace) {
			printk("swprobe: ped is entry level 1\n");
		}
		lvl = 1;
		pte = ped;
		paddrbase = ped & _SRMMU_PTE_PMASK;
		goto ready;
	}
	if (((ped & SRMMU_ET_MASK) != SRMMU_ET_PTD)) {
		if (srmmu_swprobe_trace) {
			printk("swprobe: ped is invalid => 0\n");
		}
		return 0;
	}

	if (srmmu_swprobe_trace) {
		printk("swprobe:  --- ped (%x) ---\n", ped);
	}

	ptr = (ped & SRMMU_PTD_PMASK) << 4;
	ptr += (((vaddr >> LEON_PTE_SH) & LEON_PTE_M) * 4);
	if (!_pfn_valid(PFN(ptr)))
		return 0;

	ptr = LEON_BYPASS_LOAD_PA(ptr);
	if (((ptr & SRMMU_ET_MASK) == SRMMU_ET_PTE)) {
		if (srmmu_swprobe_trace) {
			printk("swprobe: ptr is entry level 0\n");
		}
		lvl = 0;
		pte = ptr;
		paddrbase = ptr & _SRMMU_PTE_PMASK;
		goto ready;
	}
	if (srmmu_swprobe_trace) {
		printk("swprobe: ptr is invalid => 0\n");
	}
	return 0;

      ready:
	switch (lvl) {
	case 0:
		paddr_calc =
		    (vaddr & ~(-1 << LEON_PTE_SH)) | ((pte & ~0xff) << 4);
		break;
	case 1:
		paddr_calc =
		    (vaddr & ~(-1 << LEON_PMD_SH)) | ((pte & ~0xff) << 4);
		break;
	case 2:
		paddr_calc =
		    (vaddr & ~(-1 << LEON_PGD_SH)) | ((pte & ~0xff) << 4);
		break;
	default:
	case 3:
		paddr_calc = vaddr;
		break;
	}
	if (srmmu_swprobe_trace) {
		printk("swprobe: padde %x\n", paddr_calc);
	}
	if (paddr) {
		*paddr = paddr_calc;
	}
	return paddrbase;
}

void leon_flush_icache_all(void)
{
#if defined( CONFIG_LEON) 
	__asm__ __volatile__(" flush ");	//iflush 
#endif
}

void leon_flush_dcache_all(void)
{
#if defined( CONFIG_LEON) 
      __asm__ __volatile__("sta %%g0, [%%g0] %0\n\t"::"i"(ASI_LEON_DFLUSH):"memory");
#endif
}

void leon_flush_pcache_all(struct vm_area_struct *vma, unsigned long page)
{
	if (vma->vm_flags & VM_EXEC)
		leon_flush_icache_all();
	leon_flush_dcache_all();
}

void leon_flush_cache_all(void)
{
#if defined( CONFIG_LEON) 
	__asm__ __volatile__(" flush ");	//iflush 
      __asm__ __volatile__("sta %%g0, [%%g0] %0\n\t"::"i"(ASI_LEON_DFLUSH):"memory");
#endif
}

void leon_flush_tlb_all(void)
{
#if defined( CONFIG_LEON) 
	leon_flush_cache_all();
	__asm__ __volatile__("sta %%g0, [%0] %1\n\t"::"r"(0x400),
			     "i"(ASI_LEON_MMUFLUSH):"memory");
#endif
}

/* get all cache regs */
void leon3_getCacheRegs(struct leon3_cacheregs *regs)
{
	unsigned long ccr, iccr, dccr;

	if (!regs)
		return;
	/* Get Cache regs from "Cache ASI" address 0x0, 0x8 and 0xC */
	__asm__ __volatile__("lda [%%g0] %3, %0\n\t" "mov 0x08, %%g1\n\t" "lda [%%g1] %3, %1\n\t" "mov 0x0c, %%g1\n\t" "lda [%%g1] %3, %2\n\t":"=r"(ccr), "=r"(iccr), "=r"(dccr)	/* output */
			     :"i"(ASI_LEON_CACHEREGS)	/* input */
			     :"g1"	/* clobber list */
	    );
	regs->ccr = ccr;
	regs->iccr = iccr;
	regs->dccr = dccr;
}

/* Due to virtual cache we need to check cache configuration if 
 * it is possible to skip flushing in some cases.
 * 
 * Leon2 and Leon3 differ in their way of telling cache information
 *
 */
int leon_flush_needed(void)
{
	int flush_needed = -1;
	unsigned int ssize, sets;
	char *setStr[4] =
	    { "direct mapped", "2-way associative", "3-way associative",
		"4-way associative"
	};
	/* leon 3 */
	struct leon3_cacheregs cregs;
	leon3_getCacheRegs(&cregs);
	sets = (cregs.dccr & LEON3_XCCR_SETS_MASK) >> 24;
	ssize = 1 << ((cregs.dccr & LEON3_XCCR_SSIZE_MASK) >> 20);	/* (ssize=>realsize) 0=>1k, 1=>2k, 2=>4k, 3=>8k ... */

	printk("CACHE: %s cache, set size %dk\n",
	       sets > 3 ? "unknown" : setStr[sets], ssize);
	if ((ssize <= (PAGE_SIZE / 1024)) && (sets == 0)) {
		/* Set Size <= Page size  ==> flush on every context switch not needed. */
		flush_needed = 0;
		printk("CACHE: not flushing on every context switch\n");
	}
	return flush_needed;
}
