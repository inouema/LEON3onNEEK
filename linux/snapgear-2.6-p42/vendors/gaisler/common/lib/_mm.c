/* Konrad Eisele <eiselekd@web.de>, 2003 */
#include <linux/kernel.h>
#include <asm/vaddrs.h>
#include <asm/asi.h>
#include <asm/leon.h>
#include <asm/pgtsrmmu.h>
#include <asm/page.h>
#include <stdarg.h>
   
int puts(const char *fmt, ...);
int sputs(char *buf, size_t size, const char *fmt, ...);
extern char _end;

#define GETVADDR(x1,x2,x3) ((((x1) << SRMMU_PGDIR_SHIFT) & SRMMU_PGDIR_MASK) | \
                            (((x2) << SRMMU_PMD_SHIFT) & SRMMU_PMD_MASK) | \
                            (((x3) << PAGE_SHIFT) & PAGE_MASK))


#define KERNEL_PTE(page_shifted) ((page_shifted)|/*SRMMU_CACHE|*/SRMMU_PRIV|SRMMU_VALID)

#define BUG_mm() \
while (1) puts("Error\n");

unsigned long get_mem (unsigned long *mem, unsigned long size, unsigned long align) {
  unsigned long r = *mem;
  int i;
  r = (r + (align-1)) & (~(align-1));
  *mem = r + size;
  for (i = 0;i < size;i++) 
        ((unsigned char *)r)[i] = 0;
  //puts ("[ get_mem at [paddr:%x]\r\n", (unsigned int)r );
  return r;
}

int inline srmmu_pte_none(unsigned long pte) {
      if (((pte & SRMMU_ET_MASK) == SRMMU_ET_PTE ) ||
          ((pte & SRMMU_ET_MASK) == SRMMU_ET_PTD )) {
            return 0;
      }
      return 1;
}

void inline srmmu_set_pte(pte_t * addr,unsigned long pte) {
      *addr = pte;
}

/* map a physical range to <vaddr> */
int  srmmu_map (unsigned long *mem,unsigned long g_pgdp, unsigned long vaddr, unsigned long paddr_beg, unsigned long paddr_end, unsigned long flags) {
      
      unsigned long *pgdp;
	unsigned long *pmdp;
	unsigned long *ptep;
      unsigned long psz, pte;
      unsigned long oldpte,*oldptep;
      
      psz = paddr_end - paddr_beg;
      if ((psz != PAGE_SIZE) && (psz != SRMMU_PMD_SIZE) && (psz != SRMMU_PGDIR_SIZE))
            BUG_mm();
      
      pte = ((paddr_beg >> 4) | flags);
      
      pgdp = (unsigned long *)(g_pgdp + ((vaddr >> SRMMU_PGDIR_SHIFT)*4));
      puts ("pgdp is %x\r\n",(unsigned int)pgdp);
      
      if (psz < SRMMU_PGDIR_SIZE) {
            if(srmmu_pte_none(*pgdp)) {
                  pmdp = (unsigned long *)get_mem(mem,SRMMU_PMD_TABLE_SIZE, SRMMU_PMD_TABLE_SIZE);
                  if (pmdp == NULL) 
                        BUG_mm();
                  puts ("create pmd table %x\r\n",(unsigned int)pmdp);
                  srmmu_set_pte((pte_t *)pgdp, (SRMMU_ET_PTD | ((unsigned long) pmdp >> 4))); 
            }
            pmdp = (unsigned long *)((unsigned long)(*pgdp))+(((vaddr & (~SRMMU_PGDIR_MASK)) >> SRMMU_PMD_SHIFT)*4);
            puts ("pmd table pointer is %x\r\n",(unsigned int)pmdp);
            if (psz < SRMMU_PMD_SIZE) {
                  if(srmmu_pte_none(*pmdp)) {
                        ptep = (pte_t *) get_mem(mem,SRMMU_PTE_TABLE_SIZE,SRMMU_PTE_TABLE_SIZE);
                        if (ptep == NULL)
                              BUG_mm();
                        puts ("create pte table %x\r\n",(unsigned int)ptep);
                        srmmu_set_pte((pte_t *)pmdp, (SRMMU_ET_PTD | ((unsigned long) ptep >> 4))); 
                  }
                   
                  ptep = (unsigned long *)((unsigned long)(*pmdp))+(((vaddr & (~SRMMU_PMD_MASK)) >> PAGE_SHIFT)*4);
                  puts ("pte table pointer is %x\r\n",(unsigned int)ptep);
                  oldptep = (unsigned long *)(ptep);
                  oldpte = *oldptep;
                  if(!srmmu_pte_none(*oldptep)) 
                        goto filled;
                  
                  srmmu_set_pte((pte_t *)ptep,pte);
                  puts ("Map pte table(at %x) with pte(%x)\r\n",(unsigned int)ptep,(unsigned int)pte);
                  return 0;
            }
            else {                  
                  oldptep = (unsigned long *)pmdp;
                  oldpte = *oldptep;
                  if(!srmmu_pte_none(*oldptep)) 
                        goto filled;
                  
                  srmmu_set_pte((pte_t *)pmdp,pte);
                  puts ("Map pmd table(at %x) with pte(%x)\r\n",(unsigned int)pmdp,(unsigned int)pte);
                  return 0;
            }
}
      else {
            oldptep = (unsigned long *)(pgdp);
            oldpte = *oldptep;
            if(!srmmu_pte_none(*oldptep)) 
                  goto filled;
            
            puts ("Map pgd table(at %x) with pte(%x)\r\n",(unsigned int)pgdp,(unsigned int)pte);
            srmmu_set_pte((pte_t *)pgdp,pte);
            return 0;
      }
      
filled:
      BUG_mm();

      if (((oldpte&SRMMU_PTE_PMASK)<<4) != pte)                              
            return 1;
      return 0;
}



unsigned long get_mem (unsigned long *mem, unsigned long size, unsigned long align);
void setup_mm( unsigned long *mem,unsigned long *ctxtbl) {
      
      unsigned int i;
      unsigned long addr, addr_pgd;
      unsigned long *pgdp,*pgd,*pgdk,*ctx;
      unsigned long textflags, dataflags;

      // get one context table and one pgd
      *ctxtbl = (unsigned long) ctx = (unsigned long *) get_mem(mem,256*4,0x400);
      pgdp = pgd = (unsigned long *) get_mem(mem,SRMMU_PGD_TABLE_SIZE,SRMMU_PGD_TABLE_SIZE);
      // ctx 0 (kernel) pgd 
      (*(ctx++)) = SRMMU_ET_PTD | (((unsigned long)pgd) >> 4);
      // invalidate ctx 1-255 
      for (i = 1;i < 256;i++) 
            (*(ctx++)) = 0;
      
      addr = 0;
      /* <one on one> for 0 - 0xf0000000 */
      for (i = 0;i < (unsigned int)((KERNBASE&SRMMU_PGDIR_MASK)>>SRMMU_PGDIR_SHIFT);i++) {
            (*(pgd++)) = KERNEL_PTE(SRMMU_ET_PTE | (addr>>4));
            addr += SRMMU_PGDIR_SIZE;
      }
      addr_pgd = addr;
      
      pgdk = pgd;
      (*(pgd++)) = KERNEL_PTE(SRMMU_ET_PTE|(LEONSETUP_MEM_BASEADDR >> 4)); /* 0xf0000000-0xf1000000 : 16 MB, map to KERNEL_MEM by default (overwritten by ROMKERNEL) */
      
      //int __init srmmu_map (unsigned long *mem,unsigned long g_pgdp, unsigned long vaddr, unsigned long paddr_beg, unsigned long paddr_end, unsigned long flags) {

      /* map dummy LINUX_OPPROM_BEGVM - LINUX_OPPROM_ENDVM*/
      /*for (paddr = 0,vaddr = LINUX_OPPROM_BEGVM;vaddr < LINUX_OPPROM_ENDVM;vaddr+=SRMMU_PMD_SIZE,paddr+=SRMMU_PMD_SIZE) {
            srmmu_map (mem,pgdp, vaddr, paddr, paddr+SRMMU_PMD_SIZE, KERNEL_PTE(SRMMU_ET_PTE));
            }*/


      

      
      /* <one on one> for 0xf1000000 - 0xff000000 */
      /*addr_pgd += SRMMU_PGDIR_SIZE;
      for (i++;i<256;i++) {
            (*(pgd++)) = KERNEL_PTE(SRMMU_ET_PTE | (addr_pgd>>4));
            addr_pgd += SRMMU_PGDIR_SIZE;
            }*/
      
      textflags = 0; dataflags = 0;
      

      /* map 0x80000000 to page LEON_VA_ONCHIPREGS*/
      /*pmd = (unsigned long *) get_mem(mem,SRMMU_PMD_TABLE_SIZE,SRMMU_PMD_TABLE_SIZE);
      ptd = (unsigned long *) get_mem(mem,SRMMU_PTE_TABLE_SIZE,SRMMU_PTE_TABLE_SIZE);
      
      *(pgdp + ((LEON_VA_ONCHIPREGS >> SRMMU_PGDIR_SHIFT) & SRMMU_PTRS_PER_PGD-1)) = SRMMU_ET_PTD | (((unsigned long)pmd)>>4);
      *(pmd  + ((LEON_VA_ONCHIPREGS >> SRMMU_PMD_SHIFT) & SRMMU_PTRS_PER_PMD-1)) = SRMMU_ET_PTD | (((unsigned long)ptd)>>4);
      *(ptd  + ((LEON_VA_ONCHIPREGS >> PAGE_SHIFT) & SRMMU_PTRS_PER_PTE-1)) = KERNEL_PTE(SRMMU_ET_PTE | (LEON_PREGS >> 4));
      
      puts (" * peripheral at: (%x)(%x)(%x), base:%x\r\n", 
            ((LEON_VA_ONCHIPREGS >> SRMMU_PGDIR_SHIFT) & SRMMU_PTRS_PER_PGD-1),
            ((LEON_VA_ONCHIPREGS >> SRMMU_PMD_SHIFT) & SRMMU_PTRS_PER_PMD-1),
            ((LEON_VA_ONCHIPREGS >> PAGE_SHIFT) & SRMMU_PTRS_PER_PTE-1),
            pgdp);*/

      //puts ("* Creation of page tables suceeded\r\n");
}



#if !defined(__OPTIMIZE__)
void srmmu_set_ctable_ptr(unsigned long paddr)
{
	paddr = ((paddr >> 4) & SRMMU_CTX_PMASK);
	__asm__ __volatile__("sta %0, [%1] %2\n\t" : :
			     "r" (paddr), "r" (SRMMU_CTXTBL_PTR),
			     "i" (ASI_M_MMUREGS) :
			     "memory");
}

void srmmu_set_context(int context)
{
	__asm__ __volatile__("sta %0, [%1] %2\n\t" : :
			     "r" (context), "r" (SRMMU_CTX_REG),
			     "i" (ASI_M_MMUREGS) : "memory");
}

void srmmu_set_mmureg(unsigned long regval)
{
	__asm__ __volatile__("sta %0, [%%g0] %1\n\t" : :
			     "r" (regval), "i" (ASI_M_MMUREGS) : "memory");

}
#endif
