/* 
 * do srmmu probe in software
 * Copyright (C) 2004 Konrad Eisele (eiselekd@web.de), Gaisler Research 
 */

#include <linux/mm.h>
#include <asm/asi.h>
#include <asm/leon.h>

#define PFN(x) ((x) >> PAGE_SHIFT)
extern unsigned long last_valid_pfn;

/* max_mapnr not initialized yet */
#define _pfn_valid(pfn)	((pfn < last_valid_pfn) && (pfn >= PFN(phys_base)))

#undef SRMMU_PTE_PMASK
#define SRMMU_PTE_PMASK 0xffffffff

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
		paddrbase = pgd & SRMMU_PTE_PMASK;
		goto ready;
	}
	if (((pgd & SRMMU_ET_MASK) != SRMMU_ET_PTD)) {
		if (srmmu_swprobe_trace) {
			printk("swprobe: pgd is invalid => 0\n");
		}
		return 0;
	}

	if (srmmu_swprobe_trace) {
		printk("swprobe:  --- pgd (%x) ---\n",pgd);
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
		paddrbase = pmd & SRMMU_PTE_PMASK;
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
		paddrbase = ped & SRMMU_PTE_PMASK;
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
/* #if defined(CONFIG_LEON) && (CONFIG_PAGE_SIZE_LEON != 0) */
/* 	switch (CONFIG_PAGE_SIZE_LEON) { */
/* 	case 1: */
/* 		ptr += (((vaddr & 0x0003e000) >> 13) * 4); */
/* 		break; */
/* 	case 2: */
/* 		ptr += (((vaddr & 0x0003c000) >> 14) * 4); */
/* 		break; */
/* 	case 3: */
/* 		ptr += (((vaddr & 0x00038000) >> 15) * 4); */
/* 		break; */
/* 	} */
/* #else */
	ptr += (((vaddr >>  LEON_PTE_SH) & LEON_PTE_M) * 4);
/* #endif	 */
	if (!_pfn_valid(PFN(ptr)))
		return 0;

	ptr = LEON_BYPASS_LOAD_PA(ptr);
	if (((ptr & SRMMU_ET_MASK) == SRMMU_ET_PTE)) {
		if (srmmu_swprobe_trace) {
			printk("swprobe: ptr is entry level 0\n");
		}
		lvl = 0;
		pte = ptr;
		paddrbase = ptr & SRMMU_PTE_PMASK;
		goto ready;
	}
	if (srmmu_swprobe_trace) {
		printk("swprobe: ptr is invalid => 0\n");
	}
	return 0;

      ready:
	switch (lvl) {
	case 0:
		
/* #if defined(CONFIG_LEON) && (CONFIG_PAGE_SIZE_LEON != 0) */
/* 		switch (CONFIG_PAGE_SIZE_LEON) { */
/* 		case 1: */
/* 			if (((pte & ~0xff) << 4) & 0x00001000 ) { */
/* 				printk("Error: 8k page ppn not aligned 0x%08x\n",((pte & ~0xff) << 4));  */
/* 			} */
/* 			paddr_calc = (vaddr & 0x00001fff) | ((pte & ~0xff) << 4); */
/* 			break; */
/* 		case 2: */
/* 			if (((pte & ~0xff) << 4) & 0x00003000 ) { */
/* 				printk("Error: 16k page ppn not aligned 0x%08x\n",((pte & ~0xff) << 4)); */
/* 			} */
/* 			paddr_calc = (vaddr & 0x00003fff) | ((pte & ~0xff) << 4); */
/* 			break; */
/* 		case 3: */
/* 			if (((pte & ~0xff) << 4) & 0x00007000 ) { */
/* 				printk("Error: 32k page ppn not aligned 0x%08x\n",((pte & ~0xff) << 4)); */
/* 			} */
/* 			paddr_calc = (vaddr & 0x00007fff) | ((pte & ~0xff) << 4); */
/* 			break; */
/* 		}		 */
/* #else */
		paddr_calc = (vaddr & ~(-1 << LEON_PTE_SH)) | ((pte & ~0xff) << 4);
/* #endif		 */
		break;
	case 1:
		paddr_calc = (vaddr & ~(-1 << LEON_PMD_SH)) | ((pte & ~0xff) << 4);
		break;
	case 2:
		paddr_calc = (vaddr & ~(-1 << LEON_PGD_SH)) | ((pte & ~0xff) << 4);
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

