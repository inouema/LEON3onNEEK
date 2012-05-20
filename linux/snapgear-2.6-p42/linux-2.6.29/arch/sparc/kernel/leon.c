/* Copyright (C) 2009 Daniel Hellstrom (daniel@gaisler.com), Konrad Eisele (konrad@gaisler.com) Gaisler-Aeroflex AB */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/of.h>
#include <linux/interrupt.h>
#include <asm/prom.h>
#include <asm/oplib.h>
#include <asm/leon.h>
#include <asm/timer.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>

#include "prom.h"
#include "irq.h"

volatile LEON3_IrqCtrl_Regs_Map *LEON3_IrqCtrl_Regs = 0;
volatile LEON3_GpTimer_Regs_Map *LEON3_GpTimer_Regs = 0;
amba_apb_device leon_percpu_timer_dev[16];
#define LEON3_SMPTicker_Regs ((LEON3_GpTimer_Regs_Map *)leon_percpu_timer_dev[0].start)
int leondebug_irq_disable;
int leon_debug_irqout;
static int dummy_master_l10_counter;

unsigned long LEON3_GpTimer_Irq;
unsigned int sparc_leon_eirq = 0;
#undef LEON_IMASK
#define LEON_IMASK ((&LEON3_IrqCtrl_Regs ->mask[0]))

/* Return the IRQ of the pending IRQ on the extended IRQ controller */
int sparc_leon_eirq_get(int eirq, int cpu)
{
	return LEON3_BYPASS_LOAD_PA(&LEON3_IrqCtrl_Regs->intid[cpu]) & 0x1f;
}

irqreturn_t sparc_leon_eirq_isr(int dummy, void *dev_id)
{
	printk("sparc_leon_eirq_isr: ERROR EXTENDED IRQ\n");
	return IRQ_HANDLED;
}

/* The extended IRQ controller has been found, this function registers it */
void sparc_leon_eirq_register(int eirq)
{
	int irq;

	/* Register a "BAD" handler for this interrupt, it should never happen */
	irq = request_irq(eirq, sparc_leon_eirq_isr,
			  (IRQF_DISABLED | SA_STATIC_ALLOC), "extirq", NULL);

	if (irq) {
		printk("sparc_leon_eirq_register: unable to attach IRQ%d\n",
		       eirq);
	} else {
		sparc_leon_eirq = eirq;
	}

}

static inline unsigned long get_irqmask(unsigned int irq)
{
	unsigned long mask;

	if (!irq || ((irq > 0xf) && !sparc_leon_eirq)
	    || ((irq > 0x1f) && sparc_leon_eirq)) {
		printk("leon_get_irqmask: false irq number: %d\n", irq);
		mask = 0;
	} else {
		mask = LEON_HARD_INT(irq);
	}
	return mask;
}

void leon_enable_irq(unsigned int irq_nr)
{
	unsigned long mask, flags;
	mask = get_irqmask(irq_nr);
	local_irq_save(flags);
	LEON3_BYPASS_STORE_PA(LEON_IMASK,
			      (LEON3_BYPASS_LOAD_PA(LEON_IMASK) | (mask)));
	local_irq_restore(flags);
}

void leon_disable_irq(unsigned int irq_nr)
{
	unsigned long mask, flags;
	mask = get_irqmask(irq_nr);
	local_irq_save(flags);
	LEON3_BYPASS_STORE_PA(LEON_IMASK,
			      (LEON3_BYPASS_LOAD_PA(LEON_IMASK) & ~(mask)));
	local_irq_restore(flags);

}

void __init leon_init_timers(irq_handler_t counter_fn)
{
	int irq;

	leondebug_irq_disable = 0;
	leon_debug_irqout = 0;
	master_l10_counter = &dummy_master_l10_counter;
	dummy_master_l10_counter = 0;

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
		leon_percpu_timer_dev[0].irq = LEON3_GpTimer_Irq + 1;

		if (!
		    (LEON3_BYPASS_LOAD_PA(&LEON3_GpTimer_Regs->config) &
		     (1 << LEON3_GPTIMER_SEPIRQ))) {
			prom_printf
			    ("irq timer not configured with seperate irqs \n");
			BUG();
		}

		LEON3_BYPASS_STORE_PA(&LEON3_GpTimer_Regs->e[1].val, 0);
		LEON3_BYPASS_STORE_PA(&LEON3_GpTimer_Regs->e[1].rld,
				      (((1000000 / 100) - 1)));
		LEON3_BYPASS_STORE_PA(&LEON3_GpTimer_Regs->e[1].ctrl, 0);
#else
		{
			leon_percpu_timer_dev[0].start = 0;
			int i =
			    amba_get_free_apbslv_devices(VENDOR_GAISLER,
							 GAISLER_GPTIMER,
							 leon_percpu_timer_dev,
							 2);
			if (i < 1) {
				prom_printf
				    ("Cannot lock GAISLER_GPTIMER timer for smp-ticker\n");
				BUG();
			}
			if (leon_percpu_timer_dev[0].start ==
			    LEON3_GpTimer_Regs) {
				if (i < 2) {
					prom_printf
					    ("Cannot lock GAISLER_GPTIMER timer for smp-ticker\n");
					BUG();
				}
				leon_percpu_timer_dev[0] =
				    leon_percpu_timer_dev[1];
			}

			printk("Leon smp ticker at 0x%x irq %d\n",
			       leon_percpu_timer_dev[0].start,
			       leon_percpu_timer_dev[0].irq);

			LEON3_BYPASS_STORE_PA(&LEON3_SMPTicker_Regs->e[0].val,
					      0);
			LEON3_BYPASS_STORE_PA(&LEON3_SMPTicker_Regs->e[0].rld,
					      (((1000000 / 100) - 1)));
			LEON3_BYPASS_STORE_PA(&LEON3_SMPTicker_Regs->e[0].ctrl,
					      0);

			// copy over 100hz scaler
			LEON3_BYPASS_STORE_PA(&LEON3_SMPTicker_Regs->scalar,
					      LEON3_BYPASS_LOAD_PA
					      (&LEON3_GpTimer_Regs->scalar));
			LEON3_BYPASS_STORE_PA(&LEON3_SMPTicker_Regs->
					      scalar_reload,
					      LEON3_BYPASS_LOAD_PA
					      (&LEON3_GpTimer_Regs->
					       scalar_reload));

		}
# endif
# endif
	} else {
		while (1)
			printk("No Timer/irqctrl found\n");
	}


	irq = request_irq(LEON3_GpTimer_Irq,
			  counter_fn,
			  (IRQF_DISABLED | SA_STATIC_ALLOC), "timer", NULL);

	if (irq) {
		printk("leon_time_init: unable to attach IRQ%d\n",
		       LEON_INTERRUPT_TIMER1);
		prom_halt();
	}
# ifdef CONFIG_SMP
	{
		unsigned long flags;
		struct tt_entry *trap_table =
		    &sparc_ttable[SP_TRAP_IRQ1 +
				  (leon_percpu_timer_dev[0].irq - 1)];

		extern unsigned int real_irq_entry[], smpleon_ticker[];
		extern unsigned int patchme_maybe_smp_msg[];

		/* For SMP we use the level 14 ticker, however the bootup code
		 * has copied the firmwares level 14 vector into boot cpu's
		 * trap table, we must fix this now or we get squashed.
		 */
		local_irq_save(flags);

		patchme_maybe_smp_msg[0] = 0x01000000;	/* NOP out the branch */

		/* Adjust so that we jump directly to smpleon_ticker */
		trap_table->inst_three += smpleon_ticker - real_irq_entry;

		local_flush_cache_all();
		local_irq_restore(flags);
	}
# endif

	if (LEON3_GpTimer_Regs) {
		LEON3_BYPASS_STORE_PA(&LEON3_GpTimer_Regs->e[0].ctrl,
				      LEON3_GPTIMER_EN |
				      LEON3_GPTIMER_RL |
				      LEON3_GPTIMER_LD | LEON3_GPTIMER_IRQEN);
#if defined(CONFIG_SMP)
# if defined (CONFIG_LEONSMP_USETIMER2)
		LEON3_BYPASS_STORE_PA(&LEON3_GpTimer_Regs->e[1].ctrl,
				      LEON3_GPTIMER_EN |
				      LEON3_GPTIMER_RL |
				      LEON3_GPTIMER_LD | LEON3_GPTIMER_IRQEN);

# else
		LEON3_BYPASS_STORE_PA(&LEON3_SMPTicker_Regs->e[0].ctrl,
				      LEON3_GPTIMER_EN |
				      LEON3_GPTIMER_RL |
				      LEON3_GPTIMER_LD | LEON3_GPTIMER_IRQEN);
# endif
#endif
	}

}

void leon_clear_clock_irq(void)
{
}

void leon_load_profile_irq(int cpu, unsigned int limit)
{
	BUG();
}

#if defined(CONFIG_LEON) 
 void _amba_init(struct device_node *dp, struct device_node ***nextp);
#endif

 void console_print_LEON(const char *p);
 

 void __init leon_trans_init(struct device_node *dp)
{
	if (strcmp(dp->type, "cpu") == 0 && strcmp(dp->name, "<NULL>") == 0) {
		struct property *p;
		if ((p = of_find_property(dp, "mid", 0))) {
			int mid;
			dp->name = prom_early_alloc(5 + 1);
			memcpy(&mid, p->value, p->length);
			sprintf((char *)dp->name, "cpu%.2d", mid);
		}
	}
}

 void __init leon_node_init(struct device_node *dp, struct device_node ***nextp)
{
	if (strcmp(dp->type, "ambapp") == 0 && strcmp(dp->name, "ambapp0") == 0) {
#if defined(CONFIG_LEON) 
		_amba_init(dp, nextp);
#endif
	} 
}

void __init leon_init_IRQ(void)
{
	sparc_init_timers = leon_init_timers;

	BTFIXUPSET_CALL(enable_irq, leon_enable_irq, BTFIXUPCALL_NORM);
	BTFIXUPSET_CALL(disable_irq, leon_disable_irq, BTFIXUPCALL_NORM);
	BTFIXUPSET_CALL(enable_pil_irq, leon_enable_irq, BTFIXUPCALL_NORM);
	BTFIXUPSET_CALL(disable_pil_irq, leon_disable_irq, BTFIXUPCALL_NORM);

	BTFIXUPSET_CALL(clear_clock_irq, leon_clear_clock_irq,
			BTFIXUPCALL_NORM);
	BTFIXUPSET_CALL(load_profile_irq, leon_load_profile_irq,
			BTFIXUPCALL_NOP);

#ifdef CONFIG_SMP
	BTFIXUPSET_CALL(set_cpu_int, leon_set_cpu_int, BTFIXUPCALL_NORM);
	BTFIXUPSET_CALL(clear_cpu_int, leon_clear_ipi, BTFIXUPCALL_NORM);
	BTFIXUPSET_CALL(set_irq_udt, leon_set_udt, BTFIXUPCALL_NORM);
#endif

}


