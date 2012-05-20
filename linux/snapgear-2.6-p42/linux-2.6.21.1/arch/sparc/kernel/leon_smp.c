/* sun4m_smp.c: Sparc SUN4M SMP support.
 *
 * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)
 */

#include <asm/head.h>

#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/threads.h>
#include <linux/smp.h>
#include <linux/smp_lock.h>
#include <linux/interrupt.h>
#include <linux/kernel_stat.h>
#include <linux/init.h>
#include <linux/spinlock.h>
#include <linux/mm.h>
#include <linux/swap.h>
#include <linux/profile.h>
#include <linux/pm.h>

#include <asm/cacheflush.h>
#include <asm/tlbflush.h>

#include <asm/ptrace.h>
#include <asm/atomic.h>
#include <asm/irq_regs.h>

#include <asm/delay.h>
#include <asm/irq.h>
#include <asm/page.h>
#include <asm/pgalloc.h>
#include <asm/pgtable.h>
#include <asm/oplib.h>
#include <asm/cpudata.h>
#include <asm/asi.h>
#include <asm/leon.h>

#ifdef CONFIG_LEON_3

extern ctxd_t *srmmu_ctx_table_phys;

extern void calibrate_delay(void);

/* extern int smp_num_cpus; */
/* extern int smp_threads_ready; */
extern volatile unsigned long cpu_callin_map[NR_CPUS];
extern unsigned char boot_cpu_id;
/* extern int smp_activated; */
/* extern volatile int __cpu_number_map[NR_CPUS]; */
/* extern volatile int __cpu_logical_map[NR_CPUS]; */
/* extern volatile unsigned long ipi_count; */
/* extern volatile int smp_process_available; */
//extern volatile int smp_commenced;

extern cpumask_t smp_commenced_mask;

extern int __leon_processor_id(void);
void __init leon_configure_cache_smp(void);
void leon_enable_irq_cpu(unsigned int irq_nr,unsigned int cpu);

/*#define SMP_DEBUG*/

#ifdef SMP_DEBUG
#define SMP_PRINTK(x)	printk x
#else
#define SMP_PRINTK(x)
#endif

#ifdef CONFIG_LEON_3
extern volatile LEON3_IrqCtrl_Regs_Map *LEON3_IrqCtrl_Regs;	/* drivers/amba/amba.c:amba_init() */
#endif

static inline unsigned long swap(volatile unsigned long *ptr, unsigned long val)
{
	__asm__ __volatile__("swapa [%1] %2, %0\n\t"
                             : "=&r" (val)
                             :  "r" (ptr), "i" (ASI_LEON_DCACHE_MISS)
                             : "memory");
	return val;
}

static void smp_setup_percpu_timer(void);
extern void cpu_probe(void);

void __cpuinit leon_callin(void)
{
	int cpuid = hard_smpleon_processor_id();

        //printk("cpu came up\n");
        
	local_flush_cache_all();
	local_flush_tlb_all();
	leon_configure_cache_smp();
        
	/* set_irq_udt(boot_cpu_id); */

	/* Get our local ticker going. */
        smp_setup_percpu_timer();

	calibrate_delay();
	smp_store_cpu_info(cpuid);

	local_flush_cache_all();
	local_flush_tlb_all();

	/*
	 * Unblock the master CPU _only_ when the scheduler state
	 * of all secondary CPUs will be up-to-date, so after
	 * the SMP initialization the master will be just allowed
	 * to call the scheduler code.
	 */
	/* Allow master to continue. */
	swap(&cpu_callin_map[cpuid], 1);

        //printk("do flush\n");
        
	local_flush_cache_all();
	local_flush_tlb_all();
	
	cpu_probe();

	/* Fix idle thread fields. */
	__asm__ __volatile__("ld [%0], %%g6\n\t"
			     : : "r" (&current_set[cpuid])
			     : "memory" /* paranoid */);

	/* Attach to the address space of init_task. */
	atomic_inc(&init_mm.mm_count);
	current->active_mm = &init_mm;

	while (!cpu_isset(cpuid, smp_commenced_mask))
		mb();

	local_irq_enable();
        cpu_set(cpuid, cpu_online_map);
}

extern void cpu_idle(void);
extern void init_IRQ(void);
extern void cpu_panic(void);

/*
 *	Cycle through the processors asking the PROM to start each one.
 */
 
extern struct linux_prom_registers smp_penguin_ctable;
extern unsigned long trapbase_cpu1[];
extern unsigned long trapbase_cpu2[];
extern unsigned long trapbase_cpu3[];

void __init leon_configure_cache_smp(void) {
  unsigned long cfg = sparc_leon3_get_dcachecfg();
  int me = smp_processor_id();
  
  if (ASI_LEON3_SYSCTRL_CFG_SSIZE(cfg) > 4) {
    printk("Note: SMP with snooping only works on 4k cache, found %dk(0x%x) on cpu %d, disabling caches\n",(unsigned int)ASI_LEON3_SYSCTRL_CFG_SSIZE(cfg),(unsigned int)cfg,(unsigned int)me);
    sparc_leon3_disable_cache();
  } else {
    if (cfg & ASI_LEON3_SYSCTRL_CFG_SNOOPING) {
      sparc_leon3_enable_snooping();
    } else {
      printk("Note: You have to enable snooping in the vhdl model cpu %d, disabling caches\n",me);
      sparc_leon3_disable_cache();
    }
  }

  //sparc_leon3_disable_cache();
  
  local_flush_cache_all();
  local_flush_tlb_all();
}

void leon_smp_setbroadcast(unsigned int mask) 
{
    int broadcast = ((LEON3_BYPASS_LOAD_PA(&(LEON3_IrqCtrl_Regs->mpstatus)) >> LEON3_IRQMPSTATUS_BROADCAST) & 1);
    if (!broadcast) {
	prom_printf("######## !!!! The irqmp-ctrl must have broadcast enabled, smp wont work !!!!! ####### nr cpus: %d\n",leon_smp_nrcpus());
	if (leon_smp_nrcpus() > 1) {
	    BUG();
	} else {
	    prom_printf("continue anyway\n");
	    return;
	}
    }
    LEON_BYPASS_STORE_PA(&(LEON3_IrqCtrl_Regs->mpbroadcast),mask);
}

unsigned int leon_smp_getbroadcast(void ) 
{
    unsigned int mask;
    mask = LEON_BYPASS_LOAD_PA(&(LEON3_IrqCtrl_Regs->mpbroadcast));
    return mask;
}

int leon_smp_nrcpus(void) 
{
        int nrcpu = ((LEON3_BYPASS_LOAD_PA(&(LEON3_IrqCtrl_Regs->mpstatus)) >> LEON3_IRQMPSTATUS_CPUNR) & 0xf)  + 1;
	return nrcpu;
}

void __init leon_boot_cpus(void)
{
	int nrcpu = leon_smp_nrcpus();
	int me = smp_processor_id();

 	printk("%d:(%d:%d) cpus mpirq at 0x%x \n",(unsigned int)me,(unsigned int)nrcpu,(unsigned int)NR_CPUS,(unsigned int)&(LEON3_IrqCtrl_Regs->mpstatus));  

        leon_enable_irq_cpu(LEON3_IRQ_CROSS_CALL,me);
        leon_enable_irq_cpu(LEON3_IRQ_TICKER,me);
        leon_enable_irq_cpu(LEON3_IRQ_RESCHEDULE,me);

	leon_smp_setbroadcast(1<<LEON3_IRQ_TICKER);

        leon_configure_cache_smp();
        smp_setup_percpu_timer();
	local_flush_cache_all();
        
}


int __cpuinit leon_boot_one_cpu(int i) 
{

  struct task_struct *p;
  int timeout;

  /* Cook up an idler for this guy. */
  p = fork_idle(i);
  //cpucount++;
  current_set[i] = task_thread_info(p);
  
  /* See trampoline.S:leon_smp_cpu_startup for details... */
  
  /*
   * Initialize the contexts table
   * Since the call to prom_startcpu() trashes the structure,
   * we need to re-initialize it for each cpu
   */
  smp_penguin_ctable.which_io = 0;
  smp_penguin_ctable.phys_addr = (unsigned int) srmmu_ctx_table_phys;
  smp_penguin_ctable.reg_size = 0;
  
  /* whirrr, whirrr, whirrrrrrrrr... */
  printk("Starting CPU %d : (irqmp: 0x%x)\n", (unsigned int)i,(unsigned int)&LEON3_IrqCtrl_Regs->mpstatus);
  local_flush_cache_all();
  
  LEON_BYPASS_STORE_PA(&(LEON3_IrqCtrl_Regs->mpstatus),1<<i);
  
  /*prom_startcpu(cpu_data(i).prom_node,
    &smp_penguin_ctable, 0, (char *)entry);*/
  
  /* wheee... it's going... */
  for(timeout = 0; timeout < 10000; timeout++) {
    if(cpu_callin_map[i])
      break;
    udelay(200);
  }
  printk("Started CPU %d \n", (unsigned int)i);
  
  if(!(cpu_callin_map[i])) {
    printk("Processor %d is stuck.\n", i);
    return -ENODEV;
  } else {
    leon_enable_irq_cpu(LEON3_IRQ_CROSS_CALL,i);
    leon_enable_irq_cpu(LEON3_IRQ_TICKER,i);
    leon_enable_irq_cpu(LEON3_IRQ_RESCHEDULE,i);
  }

  local_flush_cache_all();
  return 0;
}

void __init leon_smp_done(void)
{
        
	int i, first;
	int *prev;

	/* setup cpu list for irq rotation */
	first = 0;
	prev = &first;
	for (i = 0; i < NR_CPUS; i++) {
		if (cpu_online(i)) {
			*prev = i;
			prev = &cpu_data(i).next;
		}
	}
	*prev = first;
	local_flush_cache_all();

	/* Free unneeded trap tables */
	if (!cpu_isset(1, cpu_present_map)) {
		ClearPageReserved(virt_to_page(trapbase_cpu1));
		init_page_count(virt_to_page(trapbase_cpu1));
		free_page((unsigned long)trapbase_cpu1);
		totalram_pages++;
		num_physpages++;
	}
	if (!cpu_isset(2, cpu_present_map)) {
		ClearPageReserved(virt_to_page(trapbase_cpu2));
		init_page_count(virt_to_page(trapbase_cpu2));
		free_page((unsigned long)trapbase_cpu2);
		totalram_pages++;
		num_physpages++;
	}
	if (!cpu_isset(3, cpu_present_map)) {
		ClearPageReserved(virt_to_page(trapbase_cpu3));
		init_page_count(virt_to_page(trapbase_cpu3));
		free_page((unsigned long)trapbase_cpu3);
		totalram_pages++;
		num_physpages++;
	}

	/* Ok, they are spinning and ready to go. */
}

/* At each hardware IRQ, we get this called to forward IRQ reception
 * to the next processor.  The caller must disable the IRQ level being
 * serviced globally so that there are no double interrupts received.
 *
 * XXX See sparc64 irq.c.
 */
void leon_irq_rotate(int cpu)
{
}

/* Cross calls, in order to work efficiently and atomically do all
 * the message passing work themselves, only stopcpu and reschedule
 * messages come through here.
 */
void leon_message_pass(int target, int msg, unsigned long data, int wait)
{
	static unsigned long smp_cpu_in_msg[NR_CPUS];
	cpumask_t mask;
	int me = smp_processor_id();
	int irq, i;

	//printk("message %d->%d\n",me,target);  

	if(msg == MSG_RESCHEDULE) {
		irq = LEON3_IRQ_RESCHEDULE;

		if(smp_cpu_in_msg[me])
			return;
	} else if(msg == MSG_STOP_CPU) {
		irq = LEON3_IRQ_TICKER;
	} else {
		goto barf;
	}

	smp_cpu_in_msg[me]++;
	if(target == MSG_ALL_BUT_SELF || target == MSG_ALL) {
                mask = cpu_online_map;
		if(target == MSG_ALL_BUT_SELF)
			cpu_clear(me, mask);
		for(i = 0; i < 4; i++) {
			if (cpu_isset(i, mask))
				set_cpu_int(i, irq);
		}
	} else {
		set_cpu_int(target, irq);
	}
	smp_cpu_in_msg[me]--;

	return;
barf:
	printk("Yeeee, trying to send SMP msg(%d) on cpu %d\n", msg, me);
	panic("Bogon SMP message pass.");
}

static struct smp_funcall {
	smpfunc_t func;
	unsigned long arg1;
	unsigned long arg2;
	unsigned long arg3;
	unsigned long arg4;
	unsigned long arg5;
	unsigned long processors_in[NR_CPUS];  /* Set when ipi entered. */
	unsigned long processors_out[NR_CPUS]; /* Set when ipi exited. */
} ccall_info;

static DEFINE_SPINLOCK(cross_call_lock);

/* Cross calls must be serialized, at least currently. */
void leon_cross_call(smpfunc_t func, unsigned long arg1, unsigned long arg2,
		    unsigned long arg3, unsigned long arg4, unsigned long arg5)
{
                register int ncpus = NR_CPUS; //smp_num_cpus;
		unsigned long flags;

		spin_lock_irqsave(&cross_call_lock, flags);

		/* Init function glue. */
		ccall_info.func = func;
		ccall_info.arg1 = arg1;
		ccall_info.arg2 = arg2;
		ccall_info.arg3 = arg3;
		ccall_info.arg4 = arg4;
		ccall_info.arg5 = arg5;

		/* Init receive/complete mapping, plus fire the IPI's off. */
		{
			cpumask_t mask = cpu_online_map;
			register int i;

			cpu_clear(smp_processor_id(), mask);
			for(i = 0; i < ncpus; i++) {
				if (cpu_isset(i, mask)) {
					ccall_info.processors_in[i] = 0;
					ccall_info.processors_out[i] = 0;
					set_cpu_int(i, LEON3_IRQ_CROSS_CALL);
				} else {
					ccall_info.processors_in[i] = 1;
					ccall_info.processors_out[i] = 1;
				}
			}
		}

		{
			register int i;

			i = 0;
			do {
				while(!ccall_info.processors_in[i])
					barrier();
			} while(++i < ncpus);

			i = 0;
			do {
				while(!ccall_info.processors_out[i])
					barrier();
			} while(++i < ncpus);
		}

		spin_unlock_irqrestore(&cross_call_lock, flags);
}

/* Running cross calls. */
void leon_cross_call_irq(void)
{
	int i = smp_processor_id();
	//printk("crosscall on %d\n",i);  

	ccall_info.processors_in[i] = 1;
	ccall_info.func(ccall_info.arg1, ccall_info.arg2, ccall_info.arg3,
			ccall_info.arg4, ccall_info.arg5);
	ccall_info.processors_out[i] = 1;
}

void leon_percpu_timer_interrupt(struct pt_regs *regs)
{
	struct pt_regs *old_regs;
	int cpu = smp_processor_id();
	
	old_regs = set_irq_regs(regs);

	/*printk("percpu_timer on %d\n",cpu);  */

	/* if (cpu == 0) { */
/* 	    cpumask_t mask = cpu_online_map; */
/* 	    for(i = 1; i < ncpus; i++) { */
/* 		if (cpu_isset(i, mask)) { */
/* 		    set_cpu_int(i,LEON3_IRQ_TICKER); */
/* 		} */
/* 	    } */
/* 	} else { */
/* 	    /\*printk("percpu_timer on %d\n",cpu);  *\/ */
/* 	} */
	
	clear_profile_irq(cpu);

	profile_tick(CPU_PROFILING);

	if(!--prof_counter(cpu)) {
		int user = user_mode(regs);

		irq_enter();
		update_process_times(user);
		irq_exit();

		prof_counter(cpu) = prof_multiplier(cpu);
	}
	set_irq_regs(old_regs);
}

extern unsigned int lvl14_resolution;

amba_apb_device leon_percpu_timer_dev[16];
           
static void __init smp_setup_percpu_timer(void)
{
	int cpu = smp_processor_id();

        
	prof_counter(cpu) = prof_multiplier(cpu) = 1;
/* 	load_profile_irq(cpu, lvl14_resolution); */

/* 	if(cpu == boot_cpu_id) */
/* 		enable_pil_irq(14); */
}

void __init leon_blackbox_id(unsigned *addr)
{
	int rd = *addr & 0x3e000000;
	int rs1 = rd >> 11;
        
        //patch places where ___b_hard_smp_processor_id appears
        addr[0] = 0x81444000 | rd;		/* rd %asr17, reg */
	addr[1] = 0x8130201c | rd | rs1;    	/* srl reg, 0x1c, reg */
	addr[2] = 0x01000000;    	        /* nop */
}

void __init leon_blackbox_current(unsigned *addr)
{
	int rd = *addr & 0x3e000000;
	int rs1 = rd >> 11;

        //patch LOAD_CURRENT macro where ___b_load_current appears
	addr[0] = 0x81444000 | rd;		/* rd %asr17, reg */
	addr[2] = 0x8130201c | rd | rs1;    	/* srl reg, 0x1c, reg */
	addr[4] = 0x81282002 | rd | rs1;    	/* sll reg, 0x2, reg */
	
}

void __init leon_init_smp(void)
{
  extern unsigned int t_nmi[], linux_trap_ipi15_leon[], linux_trap_ipi15_sun4m[];
  /* Patch ipi15 trap table */
  t_nmi[1] = t_nmi[1] + (linux_trap_ipi15_leon - linux_trap_ipi15_sun4m);
  
  BTFIXUPSET_BLACKBOX(hard_smp_processor_id, leon_blackbox_id);
  BTFIXUPSET_BLACKBOX(load_current, leon_blackbox_current);
  BTFIXUPSET_CALL(smp_cross_call, leon_cross_call, BTFIXUPCALL_NORM);
  BTFIXUPSET_CALL(smp_message_pass, leon_message_pass, BTFIXUPCALL_NORM);
  BTFIXUPSET_CALL(__hard_smp_processor_id, __leon_processor_id, BTFIXUPCALL_NORM);
}

#endif
