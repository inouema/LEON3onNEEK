/*
 * pgt_gen.c
 *
 * small utility to generate assembler code for initial
 * page tables to be linked into kernel image. 
 *
 * Copyright (C) 2004 Stefan Holst <mail@s-holst.de>
 *
 */

#include "linux/autoconf.h"
#include "linux/kernel.h"

#include "prom_config.h"
#include "asm/asi.h"
#include "asm/pgtsrmmu.h"
#include "asm/leon.h"
#include "asm/head.h"

int main(void){ 

	unsigned long mem[LOAD_ADDR+1];
	unsigned int addr, i;

	printf("	.seg \"data\"\n");
	printf("ctx_table:\n");
	//printf("	.fill %i\n", PAGE_SIZE-8);

	/* we are now @ LEON_MEM_BASE_ADDRESS + (PAGE_SIZE*2) */

	/* ctx 0 (kernel) pgd ( SRMMU_ET_PTD | (((unsigned long)pgd) >> 4) ) */
	printf("	.word 0x%x\n", (((LEONSETUP_MEM_BASEADDR +(PAGE_MIN_SIZE*2) + 256*4) >> 4) & ~0x3) | 1);

	/* invalidate ctx 1-255 */
	printf("	.fill %i\n", 255*4 );

	printf("pgd_table:\n");
	  
	/* <one on one> for 0 - 0xf0000000 */
	addr = 0;
	for (i = 0; i < (unsigned int)( (KERNBASE&SRMMU_PGDIR_MASK)
					 >>SRMMU_PGDIR_SHIFT); i++) {
		printf("	.word 0x%x\n",  SRMMU_ET_PTE | (addr>>4)
			     | SRMMU_PRIV | SRMMU_VALID);
		addr += SRMMU_PGDIR_SIZE;
	}
	
	/* 0xf0000000-0xf1000000 : 16 MB, map to KERNEL_MEM by default
	 * (overwritten by ROMKERNEL) */
	printf("	.word 0x%x\n", SRMMU_ET_PTE | 
	    (LEONSETUP_MEM_BASEADDR >> 4) | SRMMU_PRIV | SRMMU_VALID);
	  
	//printf("	.fill %i\n", 0x4000-0x1000-0x800+15*4 );
  
  /* 0xf1000000-0xffffffff : 256-16MB, mark invalid map */
  printf("	.fill %i\n",(256-(i+1))*4);

	return 0;
}

