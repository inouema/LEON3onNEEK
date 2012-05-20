/*
 *  linux/drivers/input/serio/leon3ps2.c
 *
 *  Copyright (C) 2000-2003 Deep Blue Solutions Ltd.
 *  Copyright (C) 2002 Russell King.
 *  Copyright (C) 2005 Gaisler Research, Marcus.hellquist@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
#include <linux/module.h>
#include <linux/init.h>
#include <linux/serio.h>
#include <linux/errno.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/err.h>
#include <linux/string.h>
#include <linux/kernel.h>

#include <asm/io.h>
#include <asm/irq.h>
#include <asm/leon.h>  

unsigned int leon3ps2_kbd_irq = CONFIG_SERIO_LEON3_KEYB_IRQ;

struct leon3ps2_port {
	struct serio		*io;
	void       			*base;
	unsigned int		irq;
	unsigned int		open;
};

#define PORT(kmi) ((LEON3_APBPS2_REGS_Map*)(kmi->base))
#define GET_STATUS(kmi) (LEON_BYPASS_LOAD_PA(&(PORT(kmi)->status)))
#define GET_CTRL(kmi)   (LEON_BYPASS_LOAD_PA(&(PORT(kmi)->ctrl)))
#define GET_DATA(kmi)   (LEON_BYPASS_LOAD_PA(&(PORT(kmi)->data)))
#define SET_CTRL(kmi,v)   (LEON_BYPASS_STORE_PA(&(PORT(kmi)->ctrl),v))
#define SET_DATA(kmi,v)   (LEON_BYPASS_STORE_PA(&(PORT(kmi)->data),v))
#define SET_STATUS(kmi,v)   (LEON_BYPASS_STORE_PA(&(PORT(kmi)->status),v))
#define SET_RELOAD(kmi,v)   (LEON_BYPASS_STORE_PA(&(PORT(kmi)->reload),v))

static irqreturn_t leon3ps2_int(int irq, void *dev_id)
{
	struct leon3ps2_port *kmi = dev_id;
	unsigned long status, ctrl, scan, rxflags;
	
	while( (status=GET_STATUS(kmi)) & LEON_REG_PS2_STATUS_DR ){
		scan = GET_DATA(kmi);
		ctrl = GET_CTRL(kmi);
		rxflags  = (status & LEON_REG_PS2_STATUS_PE) ? SERIO_PARITY : 0;
		rxflags |= (status & LEON_REG_PS2_STATUS_FE) ? SERIO_FRAME : 0;
		
		if ( rxflags ){
			/* clear error bits */
			SET_STATUS(kmi,status);
		}

	  serio_interrupt(kmi->io, scan, rxflags);
	}

	return IRQ_HANDLED;
}

static int leon3ps2_write(struct serio *io, unsigned char val)
{

	struct leon3ps2_port *kmi = io -> port_data;
	unsigned int timeleft = 10000; /* timeout in 100ms */
	
	/* delay until PS/2 controller has room for more chars */
	while ( (GET_STATUS(kmi) & LEON_REG_PS2_STATUS_TF) && timeleft--)
		udelay(10);

	if (timeleft) {
		SET_DATA(kmi,val);
		SET_CTRL(kmi,LEON_REG_PS2_CTRL_RE | LEON_REG_PS2_CTRL_RI | LEON_REG_PS2_CTRL_TE);
		return 0;
	}
	return SERIO_TIMEOUT;
}

/* empty rx fifo */
void leon3ps2_clr_input(struct leon3ps2_port *kmi){
	unsigned long scan;
	while( GET_STATUS(kmi) & LEON_REG_PS2_STATUS_DR ){
		scan = GET_DATA(kmi);
	}
}

int leon3ps2_open(struct serio *io)
{
	struct leon3ps2_port *kmi = io->port_data;
 	int ret;
	
	ret = request_irq(kmi->irq, leon3ps2_int, 0, "PS/2-irq", kmi);
	if (ret) {
		printk(KERN_ERR "leon3ps2: failed to claim IRQ%d\n", kmi->irq);
		return ret;
	}

	/* clear error flags */
	SET_STATUS(kmi,0);
	
	/* Clear old data if available (unlikely) */
	leon3ps2_clr_input(kmi);
	
	/* Enable reciever and it's interrupt */
	SET_CTRL(kmi,LEON_REG_PS2_CTRL_RE | LEON_REG_PS2_CTRL_RI);

	return 0;
}

void leon3ps2_close(struct serio *io)
{
	struct leon3ps2_port *kmi = io->port_data;
	
	/* stop interrupts at PS/2 HW level */
	SET_CTRL(kmi,0);

	/* unregister PS/2 interrupt handler */
	free_irq(kmi->irq, kmi);
}

extern volatile LEON3_GpTimer_Regs_Map *LEON3_GpTimer_Regs;

#define MAX_DEVS 8
static amba_apb_device leon3ps2_devs[MAX_DEVS];
static 	struct leon3ps2_port *leon3ps2_kmis[MAX_DEVS];

static int __init leon3ps2_probe(void) {
	struct leon3ps2_port *kmi;
	struct serio *io;
	int ret = 0;
	int i, leon_ports_nr;
	unsigned long clk;

	clk =
	  ((unsigned
	    long)(((LEON3_BYPASS_LOAD_PA
		    (&LEON3_GpTimer_Regs->scalar_reload)) + 1)));
	leon_ports_nr =
	  amba_get_free_apbslv_devices(VENDOR_GAISLER,
				       GAISLER_KBD, leon3ps2_devs, MAX_DEVS);
	
	for (i = 0; i < leon_ports_nr; i++) {
	  
	  kmi = kmalloc(sizeof(struct leon3ps2_port), GFP_KERNEL);
	  io = kmalloc(sizeof(struct serio), GFP_KERNEL);
		
	  if (!kmi || !io) {
	    ret = -ENOMEM;
	    break;
	  }

	  memset(kmi, 0, sizeof(struct leon3ps2_port));
	  memset(io, 0, sizeof(struct serio));
	 
	  io->open	= leon3ps2_open;
	  io->close	= leon3ps2_close;
	  io->port_data	 = kmi;

	  kmi->io 	= io;
	  kmi->irq = leon3ps2_devs[i].irq;
	  kmi->base	= (void *)leon3ps2_devs[i].start;
	  
	  if(leon3ps2_devs[i].irq == leon3ps2_kbd_irq ){
	  io->id.type	= SERIO_LEON3PS2;
	  io->write	= leon3ps2_write;
	  strlcpy(io->name, "Leon PS/2 keyboard", sizeof(io->name));
	  strlcpy(io->phys, "Leon PS/2 keyboard", sizeof(io->phys)); 
	  printk("Attaching grlib ps2 keyboard drivers at 0x%08x, irq: %d\n",
	       (unsigned int)kmi->base, kmi->irq);
	  }
	  else{
	  io->id.type	= SERIO_PS_PSTHRU;/*  SERIO_8042;  */
	  io->write	= leon3ps2_write;
	  strlcpy(io->name, "Leon PS/2 mouse", sizeof(io->name));
	  strlcpy(io->phys, "Leon PS/2 mouse", sizeof(io->phys));
	  printk("Attaching grlib ps2 mouse drivers at 0x%08x, irq: %d\n",
	       (unsigned int)kmi->base, kmi->irq);
	  }
          
          /* Set reload register to system freq in kHz/10 */
	  SET_RELOAD(kmi, clk*100);

		leon3ps2_kmis[i] = kmi;
	  serio_register_port(kmi->io);
	}

	return ret;
}


static int __init leon3ps2_init(void)
{
	memset(leon3ps2_kmis,0,sizeof(leon3ps2_kmis));
  leon3ps2_probe();
}

static void __exit leon3ps2_exit(void)
{
	int i;
	for (i=0; i<MAX_DEVS; i++){
		if ( leon3ps2_kmis[i] ){
			serio_unregister_port(leon3ps2_kmis[i]->io);
			leon3ps2_kmis[i]=NULL;
		}
	}
}

#ifndef MODULE
static int __init leon3ps2_setup(char *options)
{
	unsigned int irq;
	char *option;
	
	printk("leon3ps2_setup: options: %s\n",options);
	
	if ( !options )
		return 1;
	
	while ((option = strsep(&options, ",")) != NULL) {
	
		/* ignore empty strings */
		if (!*option)
			continue;

		printk("leon3ps2_setup: opt: %s\n",option);
		
		if ( strcmp(option,"kbdirq") == 0 ){
			/* next option is the irq number */
			printk("leon3ps2_setup: getting irq str\n");
			
			if ( !(option=strsep(&options, ",")) )
				break;
			
			printk("leon3ps2_setup: got irq str: %s\n",option);
						
			/* get irq number */
			irq = simple_strtoul(option,NULL,0);
			if ( irq < 16 ){
				leon3ps2_kbd_irq = irq;
				printk("leon3ps2_setup: setting irq to %d\n",irq);
			}
		}
		
	}
	
	return 1;
}

__setup("grps2=", leon3ps2_setup);

/* grps2=kbdirq:irqno
 * grps2=kbdaddress:address
 * 
 */
#endif

module_init(leon3ps2_init);
module_exit(leon3ps2_exit);

MODULE_AUTHOR("Gaisler Research, Marcus.hellquist@gmail.com");
MODULE_DESCRIPTION("grlib PS2 serial i/o");
MODULE_LICENSE("GPL");
