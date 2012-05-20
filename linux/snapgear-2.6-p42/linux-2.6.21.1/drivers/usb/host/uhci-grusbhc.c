/*
 * Universal Host Controller Interface driver for USB.
 *
 * Maintainer: Alan Stern <stern@rowland.harvard.edu>
 *
 * (C) Copyright 1999 Linus Torvalds
 * (C) Copyright 1999-2002 Johannes Erdfelt, johannes@erdfelt.com
 * (C) Copyright 1999 Randy Dunlap
 * (C) Copyright 1999 Georg Acher, acher@in.tum.de
 * (C) Copyright 1999 Deti Fliegl, deti@fliegl.de
 * (C) Copyright 1999 Thomas Sailer, sailer@ife.ee.ethz.ch
 * (C) Copyright 1999 Roman Weissgaerber, weissg@vienna.at
 * (C) Copyright 2000 Yggdrasil Computing, Inc. (port of new PCI interface
 *               support from usb-ohci.c by Adam Richter, adam@yggdrasil.com).
 * (C) Copyright 1999 Gregory P. Smith (from usb-ohci.c)
 * (C) Copyright 2004-2007 Alan Stern, stern@rowland.harvard.edu
 *
 * Intel documents this fairly well, and as far as I know there
 * are no royalties or anything like that, but even so there are
 * people who decided that they want to do the same thing in a
 * completely different way.
 *
 *
 * Modifed for use with the USB Host Controller in the open VHDL IP
 * library GRLIB from Gasisler Research, by jan@gaisler.com
 * Bits taken from ehci-fsl.c by Randy Vinson <rvinson@mvista.com>
 */

#define UHCI_USBLEGSUP		0xc0		/* legacy support */
#define UHCI_USBCMD		0		/* command register */
#define UHCI_USBINTR		4		/* interrupt register */
#define UHCI_USBLEGSUP_RWC	0x8f00		/* the R/WC bits */
#define UHCI_USBLEGSUP_RO	0x5040		/* R/O and reserved bits */
#define UHCI_USBCMD_RUN		0x0001		/* RUN/STOP bit */
#define UHCI_USBCMD_HCRESET	0x0002		/* Host Controller reset */
#define UHCI_USBCMD_EGSM	0x0008		/* Global Suspend Mode */
#define UHCI_USBCMD_CONFIGURE	0x0040		/* Config Flag */
#define UHCI_USBINTR_RESUME	0x0002		/* Resume interrupt enable */

#include <linux/platform_device.h>

static void grusb_reset_hc(struct platform_device *pdev, struct uhci_hcd *uhci)
{
	writew(UHCI_USBCMD_HCRESET, &uhci->regs->usbcmd); 
	udelay(5);
	if (readw(&uhci->regs->usbcmd) & UHCI_USBCMD_HCRESET)
		dev_warn(&pdev->dev, "HCReset not completed yet!\n");
	writew(0, &uhci->regs->usbintr);
	writew(0, &uhci->regs->usbcmd);
}

/*
 * Finish up a host controller reset and update the recorded state.
 */
static void finish_reset(struct uhci_hcd *uhci)
{
	int port;

	/* HCRESET doesn't affect the Suspend, Reset, and Resume Detect
	 * bits in the port status and control registers.
	 * We have to clear them by hand.
	 */
	for (port = 0; port < uhci->rh_numports; ++port)
		writew(0, &uhci->regs[port]);

	uhci->port_c_suspend = uhci->resuming_ports = 0;
	uhci->rh_state = UHCI_RH_RESET;
	uhci->is_stopped = UHCI_IS_STOPPED;
	uhci_to_hcd(uhci)->state = HC_STATE_HALT;
	uhci_to_hcd(uhci)->poll_rh = 0;

	uhci->dead = 0;		/* Full reset resurrects the controller */
}

/*
 * Last rites for a defunct/nonfunctional controller
 * or one we don't want to use any more.
 */
static void uhci_hc_died(struct uhci_hcd *uhci)
{
	uhci_get_current_frame_number(uhci);
	grusb_reset_hc(to_platform_device(uhci_dev(uhci)), uhci);
	finish_reset(uhci);
	uhci->dead = 1;

	/* The current frame may already be partway finished */
	++uhci->frame_number;
}

/*
 * Initialize a controller that was newly discovered or has lost power
 * or otherwise been reset while it was suspended.  In none of these cases
 * can we be sure of its previous state.
 */
static void check_and_reset_hc(struct uhci_hcd *uhci)
{
	unsigned int cmd, intr;
	struct platform_device *pdev = to_platform_device(uhci_dev(uhci));


	cmd = readw(&uhci->regs->usbcmd);
	if ((cmd & UHCI_USBCMD_RUN) || !(cmd & UHCI_USBCMD_CONFIGURE) ||
	    !(cmd & UHCI_USBCMD_EGSM)) {
		dev_dbg(&pdev->dev, "%s: cmd = 0x%04x\n",
			__FUNCTION__, cmd);
		goto reset_needed;
	}
	
	intr = readw(&uhci->regs->usbintr);
	if (intr & (~UHCI_USBINTR_RESUME)) {
		dev_dbg(&pdev->dev, "%s: intr = 0x%04x\n",
			__FUNCTION__, intr);
		goto reset_needed;
  }
	
	return;
	
 reset_needed:
	dev_dbg(&pdev->dev, "Performing full reset\n");
	grusb_reset_hc(pdev, uhci);
	finish_reset(uhci);
}

/*
 * Store the basic register settings needed by the controller.
 */
static void configure_hc(struct uhci_hcd *uhci)
{
	/* Set the frame length to the default: 1 ms exactly */
	writew(USBSOF_DEFAULT, &uhci->regs->sofmod);

	/* Store the frame list base address */
	writel(uhci->frame_dma_handle, &uhci->regs->flbaseadd);

	/* Set the current frame number */
	writew(uhci->frame_number & UHCI_MAX_SOF_NUMBER,
	       &uhci->regs->frnum);

	/* Mark controller as not halted before we enable interrupts */
	uhci_to_hcd(uhci)->state = HC_STATE_SUSPENDED;
	mb();
}

static void suspend_rh(struct uhci_hcd *uhci, enum uhci_rh_state new_state)
__releases(uhci->lock)
__acquires(uhci->lock)
{
	int auto_stop;
	int int_enable, egsm_enable;

	auto_stop = (new_state == UHCI_RH_AUTO_STOPPED);
	dev_dbg(&uhci_to_hcd(uhci)->self.root_hub->dev,
			"%s%s\n", __FUNCTION__,
			(auto_stop ? " (auto-stop)" : ""));

	/* If we get a suspend request when we're already auto-stopped
	 * then there's nothing to do.
	 */
	if (uhci->rh_state == UHCI_RH_AUTO_STOPPED) {
		uhci->rh_state = new_state;
		return;
	}

	/* Enable resume-detect interrupts if they work.
	 * Then enter Global Suspend mode if _it_ works, still configured.
	 */
	egsm_enable = USBCMD_EGSM;
	uhci->working_RD = 1;
	int_enable = USBINTR_RESUME;
	if (!device_may_wakeup(&uhci_to_hcd(uhci)->self.root_hub->dev))
		uhci->working_RD = int_enable = 0;

	writew(int_enable, &uhci->regs->usbintr);
	writew(USBCMD_EGSM | USBCMD_CF, &uhci->regs->usbcmd);
	mb();
	udelay(5);

	/* If we're auto-stopping then no devices have been attached
	 * for a while, so there shouldn't be any active URBs and the
	 * controller should stop after a few microseconds.  Otherwise
	 * we will give the controller one frame to stop.
	 */
	if (!auto_stop && !(readw(&uhci->regs->usbsts) & USBSTS_HCH)) {
		uhci->rh_state = UHCI_RH_SUSPENDING;
		spin_unlock_irq(&uhci->lock);
		msleep(1);
		spin_lock_irq(&uhci->lock);
		if (uhci->dead)
			return;
	}
	if (!(readw(&uhci->regs->usbsts) & USBSTS_HCH) & USBSTS_HCH)
		dev_warn(&uhci_to_hcd(uhci)->self.root_hub->dev,
			"Controller not stopped yet!\n");
		
	uhci_get_current_frame_number(uhci);

	uhci->rh_state = new_state;
	uhci->is_stopped = UHCI_IS_STOPPED;
	uhci_to_hcd(uhci)->poll_rh = !int_enable;

	uhci_scan_schedule(uhci);
	uhci_fsbr_off(uhci);
}

static void start_rh(struct uhci_hcd *uhci)
{
	uhci_to_hcd(uhci)->state = HC_STATE_RUNNING;
	uhci->is_stopped = 0;

	/* Mark it configured and running with a 64-byte max packet.
	 * All interrupts are enabled, even though RESUME won't do anything.
	 */
	writew(USBCMD_RS | USBCMD_CF | USBCMD_MAXP, &uhci->regs->usbcmd);
	writew(USBINTR_TIMEOUT | USBINTR_RESUME | USBINTR_IOC | USBINTR_SP,
	       &uhci->regs->usbintr);
	mb();
	uhci->rh_state = UHCI_RH_RUNNING;
	uhci_to_hcd(uhci)->poll_rh = 1;
}

static void wakeup_rh(struct uhci_hcd *uhci)
__releases(uhci->lock)
__acquires(uhci->lock)
{
	dev_dbg(&uhci_to_hcd(uhci)->self.root_hub->dev,
			"%s%s\n", __FUNCTION__,
			uhci->rh_state == UHCI_RH_AUTO_STOPPED ?
				" (auto-start)" : "");

	/* If we are auto-stopped then no devices are attached so there's
	 * no need for wakeup signals.  Otherwise we send Global Resume
	 * for 20 ms.
	 */
	if (uhci->rh_state == UHCI_RH_SUSPENDED) {
		uhci->rh_state = UHCI_RH_RESUMING;
		writew(USBCMD_FGR | USBCMD_EGSM | USBCMD_CF,
		       &uhci->regs->usbcmd);
		spin_unlock_irq(&uhci->lock);
		msleep(20);
		spin_lock_irq(&uhci->lock);
		if (uhci->dead)
			return;

		/* End Global Resume and wait for EOP to be sent */
		writew(USBCMD_CF, &uhci->regs->usbcmd);
		mb();
		udelay(4);
		if (readw(&uhci->regs->usbcmd) & USBCMD_FGR)
			dev_warn(uhci_dev(uhci), "FGR not stopped yet!\n");
	}

	start_rh(uhci);

	/* Restart root hub polling */
	mod_timer(&uhci_to_hcd(uhci)->rh_timer, jiffies);
}

static irqreturn_t uhci_irq(struct usb_hcd *hcd)
{
	struct uhci_hcd *uhci = hcd_to_uhci(hcd);
	unsigned short status;
	unsigned long flags;

	/*
	 * Read the interrupt status, and write it back to clear the
	 * interrupt cause.  Contrary to the UHCI specification, the
	 * "HC Halted" status bit is persistent: it is RO, not R/WC.
	 */
	status = readw(&uhci->regs->usbsts);
	if (!(status & ~USBSTS_HCH))	/* shared interrupt, not mine */
		return IRQ_NONE;
	writew(status, &uhci->regs->usbsts);		/* Clear it */

	if (status & ~(USBSTS_USBINT | USBSTS_ERROR | USBSTS_RD)) {
		if (status & USBSTS_HSE)
			dev_err(uhci_dev(uhci), "host system error, "
					"PCI problems?\n");
		if (status & USBSTS_HCPE)
			dev_err(uhci_dev(uhci), "host controller process "
					"error, something bad happened!\n");
		if (status & USBSTS_HCH) {
			spin_lock_irqsave(&uhci->lock, flags);
			if (uhci->rh_state >= UHCI_RH_RUNNING) {
				dev_err(uhci_dev(uhci),
					"host controller halted, "
					"very bad!\n");
				if (debug > 1 && errbuf) {
					/* Print the schedule for debugging */
					uhci_sprint_schedule(uhci,
							errbuf, ERRBUF_LEN);
					lprintk(errbuf);
				}
				uhci_hc_died(uhci);

				/* Force a callback in case there are
				 * pending unlinks */
				mod_timer(&hcd->rh_timer, jiffies);
			}
			spin_unlock_irqrestore(&uhci->lock, flags);
		}
	}

	if (status & USBSTS_RD)
		usb_hcd_poll_rh_status(hcd);
	else {
		spin_lock_irqsave(&uhci->lock, flags);
		uhci_scan_schedule(uhci);
		spin_unlock_irqrestore(&uhci->lock, flags);
	}

	return IRQ_HANDLED;
}

/*
 * Store the current frame number in uhci->frame_number if the controller
 * is runnning.  Expand from 11 bits (of which we use only 10) to a
 * full-sized integer.
 *
 * Like many other parts of the driver, this code relies on being polled
 * more than once per second as long as the controller is running.
 */
static void uhci_get_current_frame_number(struct uhci_hcd *uhci)
{
	if (!uhci->is_stopped) {
		unsigned delta;

		delta = (readw(&uhci->regs->frnum) - uhci->frame_number) &
				(UHCI_NUMFRAMES - 1);
		uhci->frame_number += delta;
	}
}

/*
 * De-allocate all resources
 */
static void release_uhci(struct uhci_hcd *uhci)
{
	int i;

	if (DEBUG_CONFIGURED) {
		spin_lock_irq(&uhci->lock);
		uhci->is_initialized = 0;
		spin_unlock_irq(&uhci->lock);

		debugfs_remove(uhci->dentry);
	}

	for (i = 0; i < UHCI_NUM_SKELQH; i++)
		uhci_free_qh(uhci, uhci->skelqh[i]);

	uhci_free_td(uhci, uhci->term_td);

	dma_pool_destroy(uhci->qh_pool);

	dma_pool_destroy(uhci->td_pool);

	kfree(uhci->frame_cpu);

	dma_free_coherent(uhci_dev(uhci),
			UHCI_NUMFRAMES * sizeof(*uhci->frame),
			uhci->frame, uhci->frame_dma_handle);
}

static int uhci_init(struct usb_hcd *hcd)
{
	struct uhci_hcd *uhci = hcd_to_uhci(hcd);
	unsigned io_size = (unsigned) hcd->rsrc_len;
	int port;

	uhci->regs = hcd->regs;

	/* The UHCI spec says devices must have 2 ports, and goes on to say
	 * they may have more but gives no way to determine how many there
	 * are.  However according to the UHCI spec, Bit 7 of the port
	 * status and control register is always set to 1.  So we try to
	 * use this to our advantage.  Another common failure mode when
	 * a nonexistent register is addressed is to return all ones, so
	 * we test for that also.
	 */
	for (port = 0; port < (io_size - 0x18) / 4; port++) {
		unsigned int portstatus;

		portstatus = readw(&uhci->regs->portsc[port]);
		if (!(portstatus & 0x0080) || portstatus == 0xffff)
			break;
	}
	if (debug)
		dev_info(uhci_dev(uhci), "detected %d ports\n", port);

	/* Anything greater than 7 is weird so we'll ignore it. */
	if (port > UHCI_RH_MAXCHILD) {
		dev_info(uhci_dev(uhci), "port count misdetected? "
				"forcing to 2 ports\n");
		port = 2;
	}
	uhci->rh_numports = port;

	/* Kick BIOS off this hardware and reset if the controller
	 * isn't already safely quiescent.
	 */
	check_and_reset_hc(uhci);
	return 0;
}

/* Make sure the controller is quiescent and that we're not using it
 * any more.  This is mainly for the benefit of programs which, like kexec,
 * expect the hardware to be idle: not doing DMA or generating IRQs.
 *
 * This routine may be called in a damaged or failing kernel.  Hence we
 * do not acquire the spinlock before shutting down the controller.
 */
static void uhci_shutdown(struct platform_device *pdev)
{
	struct usb_hcd *hcd = (struct usb_hcd *) platform_get_drvdata(pdev);

	uhci_hc_died(hcd_to_uhci(hcd));
}

static int uhci_hcd_get_frame_number(struct usb_hcd *hcd)
{
	struct uhci_hcd *uhci = hcd_to_uhci(hcd);
	unsigned frame_number;
	unsigned delta;

	/* Minimize latency by avoiding the spinlock */
	frame_number = uhci->frame_number;
	barrier();
	delta = (readw(&uhci->regs->frnum) - frame_number) &
		(UHCI_NUMFRAMES - 1);
	return frame_number + delta;
}

static const char hcd_name[] = "uhci_hcd";

static const struct hc_driver uhci_driver = {
	.description =		hcd_name,
	.product_desc =		"Gaisler Research UHCI Host Controller",
	.hcd_priv_size =	sizeof(struct uhci_hcd),

	/* Generic hardware linkage */
	.irq =			uhci_irq,
	.flags =		HCD_USB11,

	/* Basic lifecycle operations */
	.reset =		uhci_init,
	.start =		uhci_start,
#ifdef CONFIG_PM
	.suspend =		uhci_suspend,
	.resume =		uhci_resume,
	.bus_suspend =		uhci_rh_suspend,
	.bus_resume =		uhci_rh_resume,
#endif
	.stop =			uhci_stop,

	.urb_enqueue =		uhci_urb_enqueue,
	.urb_dequeue =		uhci_urb_dequeue,

	.endpoint_disable =	uhci_hcd_endpoint_disable,
	.get_frame_number =	uhci_hcd_get_frame_number,

	.hub_status_data =	uhci_hub_status_data,
	.hub_control =		uhci_hub_control,
};

static int uhci_hcd_grusbhc_probe(const struct hc_driver *driver,
				  struct platform_device *dev)
{
	struct usb_hcd *hcd;
	struct resource *res;
	int irq;
	int retval;
	
	pr_debug("Initializing GRLIB GRUSB UHCI Host Controller\n");
  

	res = platform_get_resource(dev, IORESOURCE_IRQ, 0);
	if (!res) {
		dev_err(&dev->dev, "Found HC with no IRQ. Check %s setup!\n",
			dev->dev.bus_id);
		return -ENODEV;
	}
   
	irq = res->start;

	hcd = usb_create_hcd(driver, &dev->dev, dev->dev.bus_id);
	if (!hcd) {
		return -ENOMEM;
		goto err1;
	}
	
	res = platform_get_resource(dev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&dev->dev,
			"Found HC with no register addr. Check %s setup!\n",
			dev->dev.bus_id);
		retval = -ENODEV;
		goto err2;
	}
    
	hcd->rsrc_start = res->start;
	hcd->rsrc_len = res->end - res->start + 1;
	if (!request_mem_region(hcd->rsrc_start, hcd->rsrc_len, driver->description)) {
		dev_dbg(&dev->dev, "request_mem_region failed\n");
		retval = -EBUSY;
		goto err2;
	}

	hcd->regs = ioremap_nocache(hcd->rsrc_start, hcd->rsrc_len);
	if (hcd->regs == NULL) {
		dev_dbg(&dev->dev, "error mapping memory\n");
		retval = -EFAULT;
		goto err3;
	}

	retval = usb_add_hcd(hcd, irq, IRQF_SHARED);
	if (retval != 0)
		goto err4;
	return retval;

 err4:
	iounmap(hcd->regs);
 err3:
	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);
 err2:
	usb_put_hcd(hcd);
 err1:
	dev_err (&dev->dev, "init %s fail, %d\n", dev->name, retval);
	return retval;
}


void uhci_hcd_grusbhc_remove(struct usb_hcd *hcd, struct platform_device *dev)
{ 
	if (!hcd)
		return;
	
	usb_remove_hcd(hcd);
	iounmap(hcd->regs);
	release_mem_region(hcd->rsrc_start,hcd->rsrc_len);
	usb_put_hcd(hcd);
}


static int uhci_grusbhc_drv_probe(struct platform_device *pdev)
{
	if (usb_disabled())
		return -ENODEV;
	
	return uhci_hcd_grusbhc_probe(&uhci_driver, pdev);

}

static int uhci_grusbhc_drv_remove(struct platform_device *pdev)
{
	struct usb_hcd *hcd = platform_get_drvdata(pdev);
	
	uhci_hcd_grusbhc_remove(hcd,pdev);

	return 0;
}

MODULE_ALIAS("grusbhc-uhci");

static struct platform_driver uhci_platform_driver = {
	.probe = uhci_grusbhc_drv_probe,
	.remove = uhci_grusbhc_drv_remove,
	.shutdown = uhci_shutdown,
	/*.suspend = , */
	/*.resume = , */
	.driver = {
		.name = "grusbhc-uhci",
	},
};
 
static int __init uhci_hcd_init(void)
{
	int retval = -ENOMEM;

	printk(KERN_INFO DRIVER_DESC " " DRIVER_VERSION "%s\n",
			ignore_oc ? ", overcurrent ignored" : "");

	if (usb_disabled())
		return -ENODEV;

	if (DEBUG_CONFIGURED) {
		errbuf = kmalloc(ERRBUF_LEN, GFP_KERNEL);
		if (!errbuf)
			goto errbuf_failed;
		uhci_debugfs_root = debugfs_create_dir("uhci", NULL);
		if (!uhci_debugfs_root)
			goto debug_failed;
	}

	uhci_up_cachep = kmem_cache_create("uhci_urb_priv",
		sizeof(struct urb_priv), 0, 0, NULL, NULL);
	if (!uhci_up_cachep)
		goto up_failed;

	retval = platform_driver_register(&uhci_platform_driver);
	if (retval)
		goto init_failed;

	return 0;

init_failed:
	kmem_cache_destroy(uhci_up_cachep);

up_failed:
	debugfs_remove(uhci_debugfs_root);

debug_failed:
	kfree(errbuf);

errbuf_failed:

	return retval;
}

static void __exit uhci_hcd_cleanup(void) 
{
	platform_driver_unregister(&uhci_platform_driver);
	kmem_cache_destroy(uhci_up_cachep);
	debugfs_remove(uhci_debugfs_root);
	kfree(errbuf);
}
