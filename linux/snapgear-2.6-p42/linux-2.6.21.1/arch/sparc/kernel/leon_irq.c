/* 
 * irq handling for Leon2/3
 * Copyright (C) 2004 Konrad Eisele (eiselekd@web.de), Gaisler Research
 * Copyright (C) 2004 Stefan Holst (mail@s-holst.de), Uni-Stuttgart
 */

#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/interrupt.h>
#include <linux/signal.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/irq.h>
#include <asm/pgtsrmmu.h>
#include <asm/leon.h>
#include <asm/sbus.h>		/* for struct sbus_bus, warning suppress */
#include <asm/timer.h>

#include <asm/traps.h>
#include <asm/cacheflush.h>

#define CONFIG_LEONSMP_USETIMER2 

/* scaled down to timer to 1Mhz, used in sparc/kernel/leon_irq.c */
#define CLOCK_TIMER_SCALAR 25

#ifdef CONFIG_LEON_3
extern volatile LEON3_IrqCtrl_Regs_Map *LEON3_IrqCtrl_Regs;	/* drivers/amba/amba.c:amba_init() */
extern volatile LEON3_GpTimer_Regs_Map *LEON3_GpTimer_Regs;
extern unsigned long LEON3_GpTimer_Irq;	/* drivers/amba.c:amba_init() */
unsigned int sparc_leon_eirq = 0;
#undef LEON_IMASK
#define LEON_IMASK ((&LEON3_IrqCtrl_Regs ->mask[0]))
#endif

static inline unsigned long get_irqmask(unsigned int irq)
{
	unsigned long mask;
	
#ifdef CONFIG_LEON_3
	if (!irq || ((irq > 0xf) && !sparc_leon_eirq) || ((irq > 0x1f) && sparc_leon_eirq) ) {
#else
	if (!irq || (irq > 0xf) ) {
#endif
		printk("leon_get_irqmask: false irq number: %d\n", irq);
		mask = 0;
	} else {
		mask = LEON_HARD_INT(irq);
	}
	return mask;
}

#ifdef CONFIG_LEON_3
/* Return the IRQ of the pending IRQ on the extended IRQ controller */
int sparc_leon_eirq_get(int eirq, int cpu)
{
	return LEON3_BYPASS_LOAD_PA(&LEON3_IrqCtrl_Regs->intid[cpu]) & 0x1f;
}

irqreturn_t sparc_leon_eirq_isr(int irq, void *priv, struct pt_regs *regs)
{
	printk("sparc_leon_eirq_isr: ERROR EXTENDED IRQ\n");
	return IRQ_HANDLED;
}

/* The extended IRQ controller has been found, this function registers it */
void sparc_leon_eirq_register(int eirq)
{
	/* Register a "BAD" handler for this interrupt, it should never happen */
	request_irq(eirq, sparc_leon_eirq_isr, 
		(SA_INTERRUPT | SA_STATIC_ALLOC), "extirq", NULL);

	sparc_leon_eirq = eirq;
}
#endif

void leon_disable_irq(unsigned int irq_nr)
{
	unsigned long mask, flags;
	mask = get_irqmask(irq_nr);
	local_irq_save(flags);
#ifdef CONFIG_LEON_3
	LEON3_BYPASS_STORE_PA(LEON_IMASK,
			      (LEON3_BYPASS_LOAD_PA(LEON_IMASK) & ~(mask)));
#else
	LEON_REGSTORE_PA(LEON_IMASK, (LEON_REGLOAD_PA(LEON_IMASK) & ~(mask)));
#endif
	local_irq_restore(flags);
}

void leon_enable_irq(unsigned int irq_nr)
{
	unsigned long mask, flags;
	mask = get_irqmask(irq_nr);
	local_irq_save(flags);
#ifdef CONFIG_LEON_3
	LEON3_BYPASS_STORE_PA(LEON_IMASK,
			      (LEON3_BYPASS_LOAD_PA(LEON_IMASK) | (mask)));
#else
	LEON_REGSTORE_PA(LEON_IMASK, (LEON_REGLOAD_PA(LEON_IMASK) | (mask)));
#endif
	local_irq_restore(flags);
}

#if defined(CONFIG_SMP) && defined(CONFIG_LEON_3)
void leon_enable_irq_cpu(unsigned int irq_nr,unsigned int cpu) {
  unsigned long mask, flags, *addr;
  mask = get_irqmask(irq_nr);
  local_irq_save(flags);
  addr = (unsigned long *)&(LEON3_IrqCtrl_Regs ->mask[cpu]);
  LEON3_BYPASS_STORE_PA(addr, (LEON3_BYPASS_LOAD_PA(addr) | (mask)));
  local_irq_restore(flags);
}
#endif

/* We assume the caller is local cli()'d when these are called, or else
 * very bizarre behavior will result. */
void leon_disable_pil_irq(unsigned int pil)
{
	unsigned long mask = get_irqmask(pil);
#ifdef CONFIG_LEON_3
	LEON3_BYPASS_STORE_PA(LEON_IMASK,
			      LEON3_BYPASS_LOAD_PA(LEON_IMASK) & ~(mask));
#else
	LEON_REGSTORE_PA(LEON_IMASK, LEON_REGLOAD_PA(LEON_IMASK) & ~(mask));
#endif
}

void leon_enable_pil_irq(unsigned int pil)
{
	unsigned long mask = get_irqmask(pil);
#ifdef CONFIG_LEON_3
	LEON3_BYPASS_STORE_PA(LEON_IMASK,
			      LEON3_BYPASS_LOAD_PA(LEON_IMASK) | (mask));
#else
	LEON_REGSTORE_PA(LEON_IMASK, LEON_REGLOAD_PA(LEON_IMASK) | (mask));
#endif
}

int leondebug_irq_disable;
int leon_debug_irqout;
static int dummy_master_l10_counter;
static int dummy_master_l10_limit;

/* called by time_init():timer.c */
void __init
leon_init_timers(irqreturn_t(*counter_fn) (int, void *, struct pt_regs *))
{
	int irq;

	leondebug_irq_disable = 0;
	leon_debug_irqout = 0;


#ifdef CONFIG_LEON_3
	if (LEON3_GpTimer_Regs && LEON3_IrqCtrl_Regs) {
		//regs -> timerctrl1 = 0;
		//regs -> timercnt1 = 0;
		//regs -> timerload1 = (((1000000/100) - 1));
		LEON3_BYPASS_STORE_PA(&LEON3_GpTimer_Regs->e[0].val, 0);
		LEON3_BYPASS_STORE_PA(&LEON3_GpTimer_Regs->e[0].rld,
				      (((1000000 / 100) - 1)));
		LEON3_BYPASS_STORE_PA(&LEON3_GpTimer_Regs->e[0].ctrl, 0);
		
#ifdef CONFIG_SMP
# if defined (CONFIG_LEONSMP_USETIMER2)
          leon_percpu_timer_dev[0].start = (int)LEON3_GpTimer_Regs;
          leon_percpu_timer_dev[0].irq = LEON3_GpTimer_Irq+1;

	  if (!(LEON3_BYPASS_LOAD_PA(&LEON3_GpTimer_Regs->config) & (1<<LEON3_GPTIMER_SEPIRQ))) {
	      prom_printf("irq timer not configured with seperate irqs \n");
	      BUG();
	  }
	  
          LEON3_BYPASS_STORE_PA(&LEON3_GpTimer_Regs ->e[1].val,0);
          LEON3_BYPASS_STORE_PA(&LEON3_GpTimer_Regs ->e[1].rld,(((1000000/100) - 1)));
          LEON3_BYPASS_STORE_PA(&LEON3_GpTimer_Regs ->e[1].ctrl,0);
#else
         {
           leon_percpu_timer_dev[0].start = 0;
           int i = amba_get_free_apbslv_devices (VENDOR_GAISLER, GAISLER_GPTIMER, leon_percpu_timer_dev, 2);
           if (i < 1) {
             prom_printf("Cannot lock GAISLER_GPTIMER timer for smp-ticker\n");
             BUG();
           }
	   if (leon_percpu_timer_dev[0].start == LEON3_GpTimer_Regs) {
	       if (i < 2) {
		   prom_printf("Cannot lock GAISLER_GPTIMER timer for smp-ticker\n");
		   BUG();
               }
	       leon_percpu_timer_dev[0] = leon_percpu_timer_dev[1];
	   }
	   
	   
           printk("Leon smp ticker at 0x%x irq %d\n",leon_percpu_timer_dev[0].start,leon_percpu_timer_dev[0].irq);
           
           #define LEON3_SMPTicker_Regs ((LEON3_GpTimer_Regs_Map *)leon_percpu_timer_dev[0].start)
           
           LEON3_BYPASS_STORE_PA(&LEON3_SMPTicker_Regs->e[0].val,0);
           LEON3_BYPASS_STORE_PA(&LEON3_SMPTicker_Regs->e[0].rld,(((1000000/100) - 1)));
           LEON3_BYPASS_STORE_PA(&LEON3_SMPTicker_Regs->e[0].ctrl,0);

           // copy over 100hz scaler
           LEON3_BYPASS_STORE_PA(&LEON3_SMPTicker_Regs->scalar, LEON3_BYPASS_LOAD_PA(&LEON3_GpTimer_Regs ->scalar));
           LEON3_BYPASS_STORE_PA(&LEON3_SMPTicker_Regs->scalar_reload,LEON3_BYPASS_LOAD_PA(&LEON3_GpTimer_Regs ->scalar_reload));

         } 
# endif          
# endif          
	


		
	} else {
		while (1)
			printk("No Timer/irqctrl found\n");
	}
#else
	LEON_REGSTORE_PA(LEON_TCTRL0, 0);
	LEON_REGSTORE_PA(LEON_TCNT0, 0);
	LEON_REGSTORE_PA(LEON_TRLD0, (((1000000 / HZ) - 1)));
#endif
	
	printk("Todo: init master_l10_counter\r\n");
	master_l10_counter = &dummy_master_l10_counter;
	master_l10_limit = &dummy_master_l10_limit;
	dummy_master_l10_counter = 0;
	dummy_master_l10_limit = 0;

#ifdef CONFIG_LEON_3
	irq = request_irq(LEON3_GpTimer_Irq,
			  counter_fn,
			  (SA_INTERRUPT | SA_STATIC_ALLOC), "timer", NULL);
#else
	irq = request_irq(LEON_INTERRUPT_TIMER1,
			  counter_fn,
			  (SA_INTERRUPT | SA_STATIC_ALLOC), "timer", NULL);
#endif

	if (irq) {
		printk("leon_time_init: unable to attach IRQ%d\n",
		       LEON_INTERRUPT_TIMER1);
		prom_halt();
	}

#ifdef CONFIG_LEON_3
# ifdef CONFIG_SMP
	{
 		unsigned long flags; 
 		struct tt_entry *trap_table = &sparc_ttable[SP_TRAP_IRQ1 + (leon_percpu_timer_dev[0].irq - 1)];
                
 		extern unsigned int real_irq_entry[], smpleon_ticker[]; 
 		extern unsigned int patchme_maybe_smp_msg[]; 
 		
		/* For SMP we use the level 14 ticker, however the bootup code
		 * has copied the firmwares level 14 vector into boot cpu's
		 * trap table, we must fix this now or we get squashed.
		 */
 		local_irq_save(flags); 

                patchme_maybe_smp_msg[0] = 0x01000000; /* NOP out the branch */ 
                
		/* Adjust so that we jump directly to smpleon_ticker */ 
		trap_table->inst_three += smpleon_ticker - real_irq_entry;

                local_flush_cache_all(); 
 		local_irq_restore(flags); 
	}
# endif
#endif

	
#ifdef CONFIG_LEON_3
	LEON3_BYPASS_STORE_PA(&LEON3_GpTimer_Regs->e[0].ctrl,
			      LEON3_GPTIMER_EN |
			      LEON3_GPTIMER_RL |
			      LEON3_GPTIMER_LD | LEON3_GPTIMER_IRQEN);
#if defined(CONFIG_SMP)
# if defined (CONFIG_LEONSMP_USETIMER2)
        LEON3_BYPASS_STORE_PA(&LEON3_GpTimer_Regs ->e[1].ctrl,
          LEON3_GPTIMER_EN |
          LEON3_GPTIMER_RL |
          LEON3_GPTIMER_LD |
          LEON3_GPTIMER_IRQEN);
# else
        LEON3_BYPASS_STORE_PA(&LEON3_SMPTicker_Regs ->e[0].ctrl,
          LEON3_GPTIMER_EN |
          LEON3_GPTIMER_RL |
          LEON3_GPTIMER_LD |
          LEON3_GPTIMER_IRQEN);
# endif        
#endif        
#else
	/* enable, load reload into counter, set automatic reload */
	LEON_REGSTORE_PA(LEON_TCTRL0, 0x7);
#endif
}

void leon_clear_clock_irq(void)
{
}

void leon_clear_profile_irq(int cpu)
{
	BUG();
}

void leon_load_profile_irq(int cpu, unsigned int limit)
{
	BUG();
}

unsigned int leon_sbint_to_irq(struct sbus_dev *sdev, unsigned int sbint)
{
	BUG();
	return 0;
}

#if 0
static char *leon_irq_itoa(unsigned int irq)
{
	static char buff[16];
	sprintf(buff, "%d", irq);
	return buff;
}
#endif

#ifdef CONFIG_SMP
static void leon_set_cpu_int(int cpu, int level)
{
  	unsigned long mask;
	mask = get_irqmask(level);
#ifdef CONFIG_LEON_3
	//printk("leon_set_cpu_int: 0x%x <- 0x%x\n",&LEON3_IrqCtrl_Regs->force[cpu],mask);
	
	LEON3_BYPASS_STORE_PA(&LEON3_IrqCtrl_Regs->force[cpu], mask);
#endif
}

static void leon_clear_ipi(int cpu, int level)
{
  	unsigned long mask;
	mask = get_irqmask(level);
#ifdef CONFIG_LEON_3
	LEON3_BYPASS_STORE_PA(&LEON3_IrqCtrl_Regs->force[cpu], mask<<16);
#endif
}

static void leon_set_udt(int cpu)
{
}
#endif

void __init leon_init_IRQ(void)
{
	sparc_init_timers = leon_init_timers;

	BTFIXUPSET_CALL(sbint_to_irq, leon_sbint_to_irq, BTFIXUPCALL_NORM);

	BTFIXUPSET_CALL(enable_irq, leon_enable_irq, BTFIXUPCALL_NORM);
	BTFIXUPSET_CALL(disable_irq, leon_disable_irq, BTFIXUPCALL_NORM);
	BTFIXUPSET_CALL(enable_pil_irq, leon_enable_irq, BTFIXUPCALL_NORM);
	BTFIXUPSET_CALL(disable_pil_irq, leon_disable_irq, BTFIXUPCALL_NORM);

	BTFIXUPSET_CALL(clear_clock_irq, leon_clear_clock_irq,
			BTFIXUPCALL_NORM);
	BTFIXUPSET_CALL(clear_profile_irq, leon_clear_profile_irq,
			BTFIXUPCALL_NOP);
	BTFIXUPSET_CALL(load_profile_irq, leon_load_profile_irq,
			BTFIXUPCALL_NOP);
/*	BTFIXUPSET_CALL(__irq_itoa, leon_irq_itoa, BTFIXUPCALL_NORM);*/

#ifdef CONFIG_SMP
	BTFIXUPSET_CALL(set_cpu_int, leon_set_cpu_int, BTFIXUPCALL_NORM);
	BTFIXUPSET_CALL(clear_cpu_int, leon_clear_ipi, BTFIXUPCALL_NORM);
	BTFIXUPSET_CALL(set_irq_udt, leon_set_udt, BTFIXUPCALL_NORM);
#endif

}
