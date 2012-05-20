/* timer Leon3
 * Copyright (C) 2007 Konrad Eisele (eiselekd@web.de), Gaisler Research
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
#include <asm/leon3.h>
#include <asm/sbus.h>		/* for struct sbus_bus, warning suppress */
#include <asm/timer.h>
#include <asm/traps.h>
#include <asm/cacheflush.h>

#define CHECK_GPTIMER(timer,idxinst,idx)					\
	if ((&timers[idxinst].timers[idx]) != timer) {				\
	    prom_printf("invalid index: instidx:%d idx:%d \n",idxinst,idx);	\
            BUG();								\
	}

#define GPTIMER_INST_MAX 8
static sparc_gptimer_inst timers[GPTIMER_INST_MAX];
static int freetimers = 0;

static void gptimer_leon3init(sparc_gptimer_inst *timer, int idx, amba_apb_device *dev) {
    unsigned int i, j, minscalar;
    timer->base = (LEON3_GpTimer_Regs_Map *)dev->start;
    timer->baseirq = dev->irq;
    timer->config = LEON3_BYPASS_LOAD_PA(&timer->base->config);
    timer->count = timer->free = GPTIMER_CONFIG_NTIMERS(timer->config);
    timer->minscalar = timer->count + 1;
    timer->scalarreload = (unsigned int)&timer->base->scalar_reload;
    for (j = 0; j < timer->count; j++) {
	timer->timers[j].irq = timer->baseirq;
	if (GPTIMER_CONFIG_ISSEP(timer->config)) {
	    timer->timers[j].irq += j;
	}
	timer->timers[j].idxinst = idx;
	timer->timers[j].idx = j;
	timer->timers[j].ctrl = (unsigned int)&timer->base->e[j].ctrl;
	timer->timers[j].reload = (unsigned int)&timer->base->e[j].rld;
	timer->timers[j].value = (unsigned int)&timer->base->e[j].val;
	timer->timers[j].scalarreload = (unsigned int)&timer->base->scalar_reload;
	timer->timers[j].minscalar = timer->minscalar;
    }
}

sparc_gptimer *gptimer_get_nexttimer() {
    int i, j, config;
    amba_apb_device dev;
    sparc_gptimer *timer;
    
    if (freetimers == 0) {
	for (i = 0; i < GPTIMER_INST_MAX; i++) {
	    if (!timers[i].base) {
		if (amba_get_free_apbslv_devices(VENDOR_GAISLER, GAISLER_GPTIMER, &dev,1) == 1) {
		    gptimer_leon3init(&timers[i], i, &dev);
		    printk("add %d timers at 0x%x \n",timers[i].count,dev.start);	
		    freetimers += timers[i].free;
		    if (i == 0 && timers[i].base != LEON3_GpTimer_Regs) {
			prom_printf("Timer 0 not initialized correctly\n");
			BUG();
		    }
		    break;
		}
	    }
	}
    }
    
    if (freetimers== 0) {
	return 0;
    }
    for (i = 0; i < GPTIMER_INST_MAX; i++) {
	int count = timers[i].count;
	int free = timers[i].free;
	if (timers[i].base && free) {
	    int idx = count-free;
	    timers[i].free--;
	    freetimers--;
	    printk("alloc timer: instance %d timer %d \n",i,idx);	
	    return &timers[i].timers[idx];
	}
    }
    return 0;
}

void gptimer_sync(sparc_gptimer *timer) {
    int idxinst = timer->idxinst, idx = timer->idx, i;
    CHECK_GPTIMER(timer,idxinst,idx);
    
    if (GPTIMER_CONFIG_ISSEP(timers[idxinst].config)) {
	if (timer->enabled) {
#ifdef GPTIMER_DEBUG
	    printk("enable %d\n",timer->irq);
#endif	    
	    enable_irq(timer->irq);
	} else {
#ifdef GPTIMER_DEBUG
	    printk("disable %d\n",timer->irq);	
#endif	    
	    disable_irq(timer->irq);
	}
    } else {
	/* sharing irq: enable if one timer is enabled, disable if all timers are disabled */ 
	int enable = 0;
	for (i = 0; i < timers[idxinst].count - timers[idxinst].free; i++) {
	    if (timers[idxinst].timers[i].enabled) {
		enable = 1;
	    }
	}
	if (enable) {
#ifdef GPTIMER_DEBUG
	    printk("enable %d\n",timers[idxinst].baseirq);
#endif	    
	    enable_irq(timers[idxinst].baseirq);
	} else {
#ifdef GPTIMER_DEBUG
	    printk("disable %d\n",timers[idxinst].baseirq);	
#endif	    
	    disable_irq(timers[idxinst].baseirq);
	}
    }
}

void gptimer_setstate(sparc_gptimer *timer, int enable) {
    if (timer) {
	if (timer->ctrl && !enable){
	    LEON3_BYPASS_ANDIN_PA(timer->ctrl,~(LEON23_REG_TIMER_CONTROL_IQ|LEON3_GPTIMER_CTRL_PENDING));
	}
	timer->enabled = enable;
	gptimer_sync(timer);
    }
}

irqreturn_t gptimer_SameClkInt(int irq, sparc_gptimer_inst *timerinst, struct pt_regs *regs) {

    int i; 
    if (GPTIMER_CONFIG_ISSEP(timerinst->config)) {
	prom_printf("Timer without seperate interrupt assigned sameclkint callback\n");
	BUG();
    }
    for (i = 0; i < timerinst->count - timerinst->free; i++) {
	sparc_gptimer *cur = &(timerinst->timers[i]);
	if (cur->enabled) {
	    unsigned int ctrl = LEON3_BYPASS_LOAD_PA(cur->ctrl);
	    if (LEON3_GPTIMER_CTRL_ISPENDING(ctrl)) {
		LEON3_BYPASS_STORE_PA(cur->ctrl,ctrl&~LEON3_GPTIMER_CTRL_PENDING);
		if (cur->callback != NULL)
		    (*(irqreturn_t (*)(int, void *, struct pt_regs *))cur->callback) (irq,cur->arg,regs);
	    }
	}
    }
}

void gptimer_connect(sparc_gptimer *timer,GPTIMER_CALLBACK callback,int arg) {
    int idxinst = timer->idxinst, idx = timer->idx, i;
    CHECK_GPTIMER(timer,idxinst,idx);
    if (!timer->connected) {
	timer->connected = 1;
	if (GPTIMER_CONFIG_ISSEP(timers[idxinst].config)) {
	    /* each timer has own irq */
	    request_irq (timer->irq, callback, (SA_INTERRUPT | SA_STATIC_ALLOC), "timer", (int)&(timers[idxinst]));
	} else {
	    /* use one irq for all timers. Multiplex in gptimer_SameClkInt */
	    timer->callback = callback;
	    timer->arg = arg;
	    if (!timers[idxinst].connected) {
		timers[idxinst].connected = 1;
		request_irq (timers[idxinst].baseirq, gptimer_SameClkInt, (SA_INTERRUPT | SA_STATIC_ALLOC), "timer", (int)&(timers[idxinst]));
	    }
	}
    }
}










void gptimerShowTimer(unsigned int sysfreq, sparc_gptimer *timer) {
    
    unsigned int ctrl = LEON3_BYPASS_LOAD_PA(timer->ctrl);
    unsigned int reload = LEON3_BYPASS_LOAD_PA(timer->reload);
    unsigned int value = LEON3_BYPASS_LOAD_PA(timer->value);
    unsigned int scalarreload = LEON3_BYPASS_LOAD_PA(timer->scalarreload);
    printk("  reload: 0x%x\n",reload);
    printk("  value : 0x%x\n",value);
    printk("  ctrl  : 0x%x [  ",ctrl);
    if (ctrl & LEON23_REG_TIMER_CONTROL_EN) {
	printk(" EN");
    }
    if (ctrl & LEON23_REG_TIMER_CONTROL_RL) {
	printk(" RL");
    }
    if (ctrl & LEON23_REG_TIMER_CONTROL_LD) {
	printk(" LD");
    }
    if (ctrl & LEON23_REG_TIMER_CONTROL_IQ) {
	unsigned int v;
	printk(" IRQ");
	/* v = LEON3_BYPASS_LOAD_PA(LEON23_IRQ_mask_addr); */
/* 	if (v & (1 << timer->irq)) { */
/* 	    printk(" (Enabled) "); */
/* 	} */
    }
    if (ctrl & LEON3_GPTIMER_CTRL_PENDING) {
	printk(" PEND");
    }
    printk("]\n  irq   :%d\n",timer->irq);
}

void gptimer_gptimerShow(unsigned int sysfreq, sparc_gptimer *sysClkTimer, sparc_gptimer *sysAuxClkTimer, sparc_gptimer *sysTimestampTimer) {
    
    sparc_gptimer_inst timers[GPTIMER_INST_MAX];
    int c = 0, nrtimers = 0, j = 0, i;
    amba_apb_device dev;
    
    memset(timers,0,sizeof(timers));
    
    for (i = 0; i < GPTIMER_INST_MAX; i++) {
	if (!amba_find_next_apbslv_devices(VENDOR_GAISLER, GAISLER_GPTIMER, &dev,i)) {
	    break;
	}
	gptimer_leon3init(&timers[i], i, &dev);
	nrtimers += timers[i].free;
    }
    
    for (i = 0; i < GPTIMER_INST_MAX; i++) {
	if (timers[i].base) {
	    unsigned int scalarreload;
	    scalarreload = LEON3_BYPASS_LOAD_PA(timers[i].scalarreload);
	    
	    printk("Timerinstance %d: base 0x%x scalarreload:0x%x\n",i,timers[i].base,scalarreload);
	    for (j = 0; j < timers[i].count; j++,c++) {
		printk(" Timer %d(%d): base 0x%x \n",c,j,timers[i].timers[j].value);
		gptimerShowTimer(sysfreq, &timers[i].timers[j]);
		if (sysClkTimer && sysClkTimer->ctrl == timers[i].timers[j].ctrl) {
		    printk("  <= system timer\n");
		} else if (sysAuxClkTimer && sysAuxClkTimer->ctrl == timers[i].timers[j].ctrl) {
		    printk("  <= system aux timer\n");
		} else if (sysTimestampTimer && sysTimestampTimer->ctrl == timers[i].timers[j].ctrl) {
		    printk("  <= Timestamp timer\n");
		} 
	    }
	}
    }    

    printk("\n");
}
