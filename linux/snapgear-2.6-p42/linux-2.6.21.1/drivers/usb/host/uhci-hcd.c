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
 */

#include <linux/module.h>
#include <linux/pci.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/ioport.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/unistd.h>
#include <linux/interrupt.h>
#include <linux/spinlock.h>
#include <linux/debugfs.h>
#include <linux/pm.h>
#include <linux/dmapool.h>
#include <linux/dma-mapping.h>
#include <linux/usb.h>
#include <linux/bitops.h>
#include <linux/dmi.h>

#include <asm/uaccess.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <asm/system.h>

#include "../core/hcd.h"
#include "uhci-hcd.h"
#include "pci-quirks.h"

/*
 * Version Information
 */
#define DRIVER_VERSION "v3.0"
#define DRIVER_AUTHOR "Linus 'Frodo Rabbit' Torvalds, Johannes Erdfelt, \
Randy Dunlap, Georg Acher, Deti Fliegl, Thomas Sailer, Roman Weissgaerber, \
Alan Stern"
#define DRIVER_DESC "USB Universal Host Controller Interface driver"

/* for flakey hardware, ignore overcurrent indicators */
static int ignore_oc;
module_param(ignore_oc, bool, S_IRUGO);
MODULE_PARM_DESC(ignore_oc, "ignore hardware overcurrent indications");

/*
 * debug = 0, no debugging messages
 * debug = 1, dump failed URBs except for stalls
 * debug = 2, dump all failed URBs (including stalls)
 *            show all queues in /debug/uhci/[pci_addr]
 * debug = 3, show all TDs in URBs when dumping
 */
#ifdef DEBUG
#define DEBUG_CONFIGURED	1
static int debug = 1;
module_param(debug, int, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug, "Debug level");

#else
#define DEBUG_CONFIGURED	0
#define debug			0
#endif

static char *errbuf;
#define ERRBUF_LEN    (32 * 1024)

static struct kmem_cache *uhci_up_cachep;	/* urb_priv */

static void suspend_rh(struct uhci_hcd *uhci, enum uhci_rh_state new_state);
static void wakeup_rh(struct uhci_hcd *uhci);
static void uhci_get_current_frame_number(struct uhci_hcd *uhci);
static int uhci_start(struct usb_hcd *hcd);
static void uhci_stop(struct usb_hcd *hcd);
static void uhci_hcd_endpoint_disable(struct usb_hcd *hcd,
				      struct usb_host_endpoint *hep);

/*
 * Calculate the link pointer DMA value for the first Skeleton QH in a frame.
 */
static __le32 uhci_frame_skel_link(struct uhci_hcd *uhci, int frame)
{
	int skelnum;

	/*
	 * The interrupt queues will be interleaved as evenly as possible.
	 * There's not much to be done about period-1 interrupts; they have
	 * to occur in every frame.  But we can schedule period-2 interrupts
	 * in odd-numbered frames, period-4 interrupts in frames congruent
	 * to 2 (mod 4), and so on.  This way each frame only has two
	 * interrupt QHs, which will help spread out bandwidth utilization.
	 *
	 * ffs (Find First bit Set) does exactly what we need:
	 * 1,3,5,...  => ffs = 0 => use period-2 QH = skelqh[8],
	 * 2,6,10,... => ffs = 1 => use period-4 QH = skelqh[7], etc.
	 * ffs >= 7 => not on any high-period queue, so use
	 *	period-1 QH = skelqh[9].
	 * Add in UHCI_NUMFRAMES to insure at least one bit is set.
	 */
	skelnum = 8 - (int) __ffs(frame | UHCI_NUMFRAMES);
	if (skelnum <= 1)
		skelnum = 9;
	return LINK_TO_QH(uhci->skelqh[skelnum]);
}

#include "uhci-debug.c"
#include "uhci-q.c"

#ifdef CONFIG_LEON_3
#include "uhci-grusbhub.c"
#include "uhci-grusbhc.c"
#else
#ifdef CONFIG_PCI
#include "uhci-hub.c"
#include "uhci-pci.c"
#endif /* CONFIG_PCI */ 
#endif /* CONFIG_LEON_3 */

/*
 * Allocate a frame list, and then setup the skeleton
 *
 * The hardware doesn't really know any difference
 * in the queues, but the order does matter for the
 * protocols higher up.  The order in which the queues
 * are encountered by the hardware is:
 *
 *  - All isochronous events are handled before any
 *    of the queues. We don't do that here, because
 *    we'll create the actual TD entries on demand.
 *  - The first queue is the high-period interrupt queue.
 *  - The second queue is the period-1 interrupt and async
 *    (low-speed control, full-speed control, then bulk) queue.
 *  - The third queue is the terminating bandwidth reclamation queue,
 *    which contains no members, loops back to itself, and is present
 *    only when FSBR is on and there are no full-speed control or bulk QHs.
 */
static int uhci_start(struct usb_hcd *hcd)
{
	struct uhci_hcd *uhci = hcd_to_uhci(hcd);
	int retval = -EBUSY;
	int i;
	struct dentry *dentry;

	hcd->uses_new_polling = 1;

	spin_lock_init(&uhci->lock);
	setup_timer(&uhci->fsbr_timer, uhci_fsbr_timeout,
			(unsigned long) uhci);
	INIT_LIST_HEAD(&uhci->idle_qh_list);
	init_waitqueue_head(&uhci->waitqh);

	if (DEBUG_CONFIGURED) {
		dentry = debugfs_create_file(hcd->self.bus_name,
				S_IFREG|S_IRUGO|S_IWUSR, uhci_debugfs_root,
				uhci, &uhci_debug_operations);
		if (!dentry) {
			dev_err(uhci_dev(uhci), "couldn't create uhci "
					"debugfs entry\n");
			retval = -ENOMEM;
			goto err_create_debug_entry;
		}
		uhci->dentry = dentry;
	}

	uhci->frame = dma_alloc_coherent(uhci_dev(uhci),
			UHCI_NUMFRAMES * sizeof(*uhci->frame),
			&uhci->frame_dma_handle, 0);
	if (!uhci->frame) {
		dev_err(uhci_dev(uhci), "unable to allocate "
				"consistent memory for frame list\n");
		goto err_alloc_frame;
	}
	memset(uhci->frame, 0, UHCI_NUMFRAMES * sizeof(*uhci->frame));

	uhci->frame_cpu = kcalloc(UHCI_NUMFRAMES, sizeof(*uhci->frame_cpu),
			GFP_KERNEL);
	if (!uhci->frame_cpu) {
		dev_err(uhci_dev(uhci), "unable to allocate "
				"memory for frame pointers\n");
		goto err_alloc_frame_cpu;
	}

	uhci->td_pool = dma_pool_create("uhci_td", uhci_dev(uhci),
			sizeof(struct uhci_td), 16, 0);
	if (!uhci->td_pool) {
		dev_err(uhci_dev(uhci), "unable to create td dma_pool\n");
		goto err_create_td_pool;
	}

	uhci->qh_pool = dma_pool_create("uhci_qh", uhci_dev(uhci),
			sizeof(struct uhci_qh), 16, 0);
	if (!uhci->qh_pool) {
		dev_err(uhci_dev(uhci), "unable to create qh dma_pool\n");
		goto err_create_qh_pool;
	}

	uhci->term_td = uhci_alloc_td(uhci);
	if (!uhci->term_td) {
		dev_err(uhci_dev(uhci), "unable to allocate terminating TD\n");
		goto err_alloc_term_td;
	}

	for (i = 0; i < UHCI_NUM_SKELQH; i++) {
		uhci->skelqh[i] = uhci_alloc_qh(uhci, NULL, NULL);
		if (!uhci->skelqh[i]) {
			dev_err(uhci_dev(uhci), "unable to allocate QH\n");
			goto err_alloc_skelqh;
		}
	}

	/*
	 * 8 Interrupt queues; link all higher int queues to int1 = async
	 */
	for (i = SKEL_ISO + 1; i < SKEL_ASYNC; ++i)
		uhci->skelqh[i]->link = LINK_TO_QH(uhci->skel_async_qh);
	uhci->skel_async_qh->link = UHCI_PTR_TERM;
	uhci->skel_term_qh->link = LINK_TO_QH(uhci->skel_term_qh);

	/* This dummy TD is to work around a bug in Intel PIIX controllers */
	uhci_fill_td(uhci->term_td, 0, uhci_explen(0) |
			(0x7f << TD_TOKEN_DEVADDR_SHIFT) | USB_PID_IN, 0);
	uhci->term_td->link = UHCI_PTR_TERM;
	uhci->skel_async_qh->element = uhci->skel_term_qh->element =
			LINK_TO_TD(uhci->term_td);

	/*
	 * Fill the frame list: make all entries point to the proper
	 * interrupt queue.
	 */
	for (i = 0; i < UHCI_NUMFRAMES; i++) {

		/* Only place we don't use the frame list routines */
		uhci->frame[i] = uhci_frame_skel_link(uhci, i);
	}

	/*
	 * Some architectures require a full mb() to enforce completion of
	 * the memory writes above before the I/O transfers in configure_hc().
	 */
	mb();

	configure_hc(uhci);
	uhci->is_initialized = 1;
	start_rh(uhci);
	return 0;

/*
 * error exits:
 */
err_alloc_skelqh:
	for (i = 0; i < UHCI_NUM_SKELQH; i++) {
		if (uhci->skelqh[i])
			uhci_free_qh(uhci, uhci->skelqh[i]);
	}

	uhci_free_td(uhci, uhci->term_td);

err_alloc_term_td:
	dma_pool_destroy(uhci->qh_pool);

err_create_qh_pool:
	dma_pool_destroy(uhci->td_pool);

err_create_td_pool:
	kfree(uhci->frame_cpu);

err_alloc_frame_cpu:
	dma_free_coherent(uhci_dev(uhci),
			UHCI_NUMFRAMES * sizeof(*uhci->frame),
			uhci->frame, uhci->frame_dma_handle);

err_alloc_frame:
	debugfs_remove(uhci->dentry);

err_create_debug_entry:
	return retval;
}

static void uhci_stop(struct usb_hcd *hcd)
{
	struct uhci_hcd *uhci = hcd_to_uhci(hcd);

	spin_lock_irq(&uhci->lock);
	if (test_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags) && !uhci->dead)
		uhci_hc_died(uhci);
	uhci_scan_schedule(uhci);
	spin_unlock_irq(&uhci->lock);

	del_timer_sync(&uhci->fsbr_timer);
	release_uhci(uhci);
}

#ifdef CONFIG_PM
static int uhci_rh_suspend(struct usb_hcd *hcd)
{
	struct uhci_hcd *uhci = hcd_to_uhci(hcd);
	int rc = 0;

	spin_lock_irq(&uhci->lock);
	if (!test_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags))
		rc = -ESHUTDOWN;
	else if (!uhci->dead)
		suspend_rh(uhci, UHCI_RH_SUSPENDED);
	spin_unlock_irq(&uhci->lock);
	return rc;
}

static int uhci_rh_resume(struct usb_hcd *hcd)
{
	struct uhci_hcd *uhci = hcd_to_uhci(hcd);
	int rc = 0;

	spin_lock_irq(&uhci->lock);
	if (!test_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags)) {
		dev_warn(&hcd->self.root_hub->dev, "HC isn't running!\n");
		rc = -ESHUTDOWN;
	} else if (!uhci->dead)
		wakeup_rh(uhci);
	spin_unlock_irq(&uhci->lock);
	return rc;
}

static int uhci_suspend(struct usb_hcd *hcd, pm_message_t message)
{
	struct uhci_hcd *uhci = hcd_to_uhci(hcd);
	int rc = 0;

	dev_dbg(uhci_dev(uhci), "%s\n", __FUNCTION__);

	spin_lock_irq(&uhci->lock);
	if (!test_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags) || uhci->dead)
		goto done_okay;		/* Already suspended or dead */

	if (uhci->rh_state > UHCI_RH_SUSPENDED) {
		dev_warn(uhci_dev(uhci), "Root hub isn't suspended!\n");
		rc = -EBUSY;
		goto done;
	};

	/* All PCI host controllers are required to disable IRQ generation
	 * at the source, so we must turn off PIRQ.
	 */
	pci_write_config_word(to_pci_dev(uhci_dev(uhci)), USBLEGSUP, 0);
	mb();
	hcd->poll_rh = 0;

	/* FIXME: Enable non-PME# remote wakeup? */

	/* make sure snapshot being resumed re-enumerates everything */
	if (message.event == PM_EVENT_PRETHAW)
		uhci_hc_died(uhci);

done_okay:
	clear_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);
done:
	spin_unlock_irq(&uhci->lock);
	return rc;
}

static int uhci_resume(struct usb_hcd *hcd)
{
	struct uhci_hcd *uhci = hcd_to_uhci(hcd);

	dev_dbg(uhci_dev(uhci), "%s\n", __FUNCTION__);

	/* Since we aren't in D3 any more, it's safe to set this flag
	 * even if the controller was dead.
	 */
	set_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);
	mb();

	spin_lock_irq(&uhci->lock);

	/* FIXME: Disable non-PME# remote wakeup? */

	/* The firmware or a boot kernel may have changed the controller
	 * settings during a system wakeup.  Check it and reconfigure
	 * to avoid problems.
	 */
	check_and_reset_hc(uhci);

	/* If the controller was dead before, it's back alive now */
	configure_hc(uhci);

	if (uhci->rh_state == UHCI_RH_RESET) {

		/* The controller had to be reset */
		usb_root_hub_lost_power(hcd->self.root_hub);
		suspend_rh(uhci, UHCI_RH_SUSPENDED);
	}

	spin_unlock_irq(&uhci->lock);

	if (!uhci->working_RD) {
		/* Suspended root hub needs to be polled */
		hcd->poll_rh = 1;
		usb_hcd_poll_rh_status(hcd);
	}
	return 0;
}
#endif

/* Wait until a particular device/endpoint's QH is idle, and free it */
static void uhci_hcd_endpoint_disable(struct usb_hcd *hcd,
		struct usb_host_endpoint *hep)
{
	struct uhci_hcd *uhci = hcd_to_uhci(hcd);
	struct uhci_qh *qh;

	spin_lock_irq(&uhci->lock);
	qh = (struct uhci_qh *) hep->hcpriv;
	if (qh == NULL)
		goto done;

	while (qh->state != QH_STATE_IDLE) {
		++uhci->num_waiting;
		spin_unlock_irq(&uhci->lock);
		wait_event_interruptible(uhci->waitqh,
				qh->state == QH_STATE_IDLE);
		spin_lock_irq(&uhci->lock);
		--uhci->num_waiting;
	}

	uhci_free_qh(uhci, qh);
done:
	spin_unlock_irq(&uhci->lock);
}

module_init(uhci_hcd_init);
module_exit(uhci_hcd_cleanup);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
