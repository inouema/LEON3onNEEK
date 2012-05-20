/* Ethernet driver for Gaisler Research's GRETH Ethernet MAC, PCI version (www.gaisler.com)
 * 
 * Based on:
 * Ethernet driver for Opencores ethernet controller (www.opencores.org).
 *      Copyright (c) 2002 Simon Srot (simons@opencores.org)
 *
 */

#include <linux/autoconf.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/string.h>
#include <linux/ptrace.h>
#include <linux/errno.h>
#include <linux/ioport.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/inet.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/skbuff.h>

#include <asm/irq.h>
#include <asm/pgtable.h>
#include <asm/bitops.h>
#include <asm/cacheflush.h>

#include <linux/config.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/timer.h>
#include <linux/errno.h>
#include <linux/ioport.h>
#include <linux/pci.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/skbuff.h>
#include <linux/init.h>
#include <linux/spinlock.h>
#include <linux/ethtool.h>
#include <linux/delay.h>
#include <linux/rtnetlink.h>
#include <linux/mii.h>
#include <linux/crc32.h>
#include <asm/processor.h>	/* Processor type for cache alignment. */
#include <asm/bitops.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <asm/uaccess.h>

#ifdef CONFIG_LEON
#include <asm/leon.h>
#endif

#include "greth_pci.h"

#define _FUNCDBG(a) 
//#define _FUNCDBG(a) printk(a)

//#define DEBUG 1 
//#define DEBUG_TX_PACKETS 1
//#define DEBUG_RX_PACKETS 1 

#ifndef DEBUG
#  define assert(expr) do {} while (0)
#else
#  define assert(expr) \
        if(unlikely(!(expr))) {				        \
        printk(KERN_ERR "Assertion failed! %s,%s,%s,line=%d\n",	\
        #expr,__FILE__,__FUNCTION__,__LINE__);		        \
        }
#endif

#define BT_ENABLED 1

#define MACADDR0 (0xDE)
#define MACADDR1 (0xAD)
#define MACADDR2 (0xBE)
#define MACADDR3 (0xEF)
#define MACADDR4 (0x00)
#define MACADDR5 (0x40)

/* How many buffers per page 
 */
#define GRETH_RX_BUF_PPGAE	(PAGE_SIZE/GRETH_RX_BUF_SIZE)
#define GRETH_TX_BUF_PPGAE	(PAGE_SIZE/GRETH_TX_BUF_SIZE)

/* How many pages is needed for buffers
 */
#define GRETH_RX_BUF_PAGE_NUM	(GRETH_RXBD_NUM/GRETH_RX_BUF_PPGAE)
#define GRETH_TX_BUF_PAGE_NUM	(GRETH_TXBD_NUM/GRETH_TX_BUF_PPGAE)

/* Buffer size 
 */
#define MAX_FRAME_SIZE		1516

/* The buffer descriptors track the ring buffers.   
 */
struct greth_private {	

    struct pci_dev *pci_dev;
    void *mmio_addr;

    greth_regs *regs;
    volatile unsigned int *pci_reg;

    struct sk_buff* rx_skbuff[GRETH_RXBD_NUM];
    struct sk_buff* tx_skbuff[GRETH_TXBD_NUM];
  
    ushort tx_next;			
    ushort tx_last;			
    ushort tx_full;			
    ushort rx_cur;				
  
    greth_bd   *rx_bd_base;		/* Address of Rx BDs. */
    greth_bd   *tx_bd_base;		/* Address of Tx BDs. */
    dma_addr_t tx_bd_base_phys;
    dma_addr_t rx_bd_base_phys;

    struct net_device_stats stats;
    int irq;
};

//#define VENDOR 0x1438
//#define DEVICE 0x1202
#define VENDOR 0xfeed
#define DEVICE 0xbacc

static struct pci_device_id greth_pci_tbl[] = {
	{VENDOR, DEVICE, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{0,}
};

MODULE_DEVICE_TABLE (pci, greth_pci_tbl);
MODULE_AUTHOR ("Kristoffer Carlsson <kristoffer@gaisler.com>");
MODULE_DESCRIPTION ("GRETH PCI driver");
MODULE_LICENSE("GPL");

static int greth_open(struct net_device *dev);
static int greth_start_xmit(struct sk_buff *skb, struct net_device *dev);
static void greth_rx(struct net_device *dev);
static void greth_tx(struct net_device *dev);
static irqreturn_t greth_interrupt(int irq, void *dev_id, struct pt_regs *regs);
static int greth_close(struct net_device *dev);
static struct net_device_stats *greth_get_stats(struct net_device *dev);
static void greth_set_mac_add(struct net_device *dev, void *p);
static void greth_set_multicast_list(struct net_device *dev);


#define greth_read __raw_readl
#define greth_write __raw_writel

#define GRETH_REGLOAD(reg)      ((unsigned long) greth_read (&reg))
#define GRETH_REGSAVE(reg,v)    greth_write ((v),&reg)
#define GRETH_REGORIN(reg,v) (GRETH_REGSAVE(reg,(GRETH_REGLOAD(reg) | (v))))
#define GRETH_REGANDIN(reg,v) (GRETH_REGSAVE(reg,(GRETH_REGLOAD(reg) & (v))))

#if DEBUG
static void
greth_print_packet(unsigned long add, int len)
{
	int i;

	printk("ipacket: add = %x len = %d\n", add, len);
	for(i = 0; i < len; i++) {
  		if(!(i % 16))
    			printk("\n");
  		printk(" %.2x", *(((unsigned char *)add) + i));
	}
	printk("\n");
}
#endif

static int read_mii(int addr, volatile greth_regs *regs)
{

  while (GRETH_REGLOAD(regs->mdio) & GRETH_MII_BUSY) {}

  GRETH_REGSAVE(regs->mdio, (0 << 11) | ((addr&0x1F) << 6) | 2);
  
  while (GRETH_REGLOAD(regs->mdio) & GRETH_MII_BUSY) {}

  if (!(GRETH_REGLOAD(regs->mdio) & GRETH_MII_NVALID)) { 
    return (GRETH_REGLOAD(regs->mdio)>>16)&0xFFFF; 
  }
  else {
    return -1;
  }
}

static void write_mii(int addr, int data, volatile greth_regs *regs)
{
  while (GRETH_REGLOAD(regs->mdio) & GRETH_MII_BUSY) {} 

  GRETH_REGSAVE(regs->mdio, ((data&0xFFFF)<<16) | (0 << 11) | ((addr&0x1F) << 6) | 1);

  while (GRETH_REGLOAD(regs->mdio) & GRETH_MII_BUSY) {} 

}

static int
greth_open(struct net_device *dev)
{
	struct greth_private *cep = (struct greth_private *)dev->priv;
	greth_regs *regs = (greth_regs *)dev->base_addr;
	volatile greth_bd *bdp;
        int i;

	_FUNCDBG("greth_open\n");

        cep->rx_cur = 0;
	cep->tx_next = 0;
	cep->tx_last = 0;
	cep->tx_full = 0;

	GRETH_REGSAVE(regs->tx_desc_p,(int) ((cep->tx_bd_base_phys)&~0xf0000000) | 0xe0000000);
	GRETH_REGSAVE(regs->rx_desc_p,(int) ((cep->rx_bd_base_phys)&~0xf0000000) | 0xe0000000);

        bdp = cep->rx_bd_base;

	for (i = 0; i < GRETH_RXBD_NUM-1; i++) {
            bdp->stat = (GRETH_BD_IE| GRETH_BD_EN);
            bdp++;
	}
        bdp->stat |= (GRETH_BD_WR | GRETH_BD_IE | GRETH_BD_EN);


	/* Install our interrupt handler.
	 */
	request_irq(dev->irq, greth_interrupt, SA_SHIRQ, dev->name, (void *)dev);

	/* Enable receiver and irqs
	 */
	GRETH_REGORIN(regs->control, GRETH_RXEN | GRETH_RXI | GRETH_TXI);

//	netif_start_queue (dev);

        _FUNCDBG("greth_open exit\n");
	return 0;
}

static int
greth_close(struct net_device *dev)
{
	struct greth_private *cep = (struct greth_private *)dev->priv;
	greth_regs *regs = (greth_regs *)dev->base_addr;
	volatile greth_bd *bdp;
	int i;

	_FUNCDBG("greth_close\n");

	netif_stop_queue (dev);

	/* Free interrupt hadler 
	 */
	free_irq(dev->irq, (void *)dev);

	/* Disable receiver and transmitesr 
	 */
	GRETH_REGANDIN(regs->control, ~(GRETH_RXEN | GRETH_TXEN));

	bdp = cep->rx_bd_base;

	for (i = 0; i < GRETH_RXBD_NUM; i++) {
            bdp->stat = 0;
            bdp++;
	}

	bdp = cep->tx_bd_base;
	for (i = 0; i < GRETH_TXBD_NUM; i++) {
            bdp->stat = 0;
            bdp++;
	}

	return 0;
}

static int
greth_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct greth_private *cep = (struct greth_private *)dev->priv;
	greth_regs *regs = dev->base_addr;
	volatile greth_bd *bdp;
	unsigned long flags;
	static spinlock_t spin_lock = SPIN_LOCK_UNLOCKED;
        u32 addr;

	_FUNCDBG("greth_start_xmit\n");
	
	/* Fill in a Tx ring entry 
	 */
	bdp = cep->tx_bd_base + cep->tx_next;

	if (cep->tx_full) {
            
            netif_stop_queue(dev);
            printk("%s: tx queue full!.\n", dev->name);
            return 1;
	}

#if DEBUG_TX_PACKETS
	printk("TX\n");
	greth_print_packet(skb->data, skb->len);
#endif

	if (skb->len > MAX_FRAME_SIZE) {
		printk("%s: tx frame too long!.\n", dev->name);
		return 1;
	}
	else {
            
          addr = (bdp->addr & ~0xf0000000) | 0x40000000;

	  memcpy((unsigned char *)__va(addr), skb->data, skb->len); 
          pci_dma_sync_single_for_device(cep->pci_dev, addr, skb->len, PCI_DMA_TODEVICE);

	}

	bdp->stat = GRETH_BD_IE | (skb->len & GRETH_BD_LEN) | ((cep->tx_next == GRETH_TXBD_NUM_MASK) ? GRETH_BD_WR : 0); 

	dev->trans_start = jiffies;

	dev_kfree_skb(skb); 

	cep->tx_next = (cep->tx_next + 1) & GRETH_TXBD_NUM_MASK;

        save_flags(flags); cli();

	if (cep->tx_next == cep->tx_last)
		cep->tx_full = 1;

	bdp->stat |= GRETH_BD_EN; 

	GRETH_REGORIN(regs->control,GRETH_TXEN); 


	restore_flags(flags);

	return 0;
}

/* The interrupt handler.
 */
irqreturn_t
greth_interrupt(int irq, void *dev_id, struct pt_regs *regs)
{
	struct	net_device *dev = (struct net_device *) dev_id;	
        greth_regs *regs = dev->base_addr;
	volatile struct	greth_private *cep;
	uint	int_events;
        int handled = 0; 

	_FUNCDBG("greth_interrupt\n");


      	cep = (struct greth_private *)dev->priv;

     
   	/* Get the interrupt events that caused us to be here.
	 */
	int_events = GRETH_REGLOAD(regs->status);

        if ( (int_events & GRETH_INTMASK) == 0)
            goto out;

      	/* Handle receive event in its own function.
	 */
	if (int_events & (GRETH_INT_RX|GRETH_INT_RXERR)) {
                GRETH_REGSAVE(regs->status, GRETH_INT_RX|GRETH_INT_RXERR);
                greth_rx(dev);
                handled = 1;
        }

	/* Handle transmit event in its own function.
	 */
	if (int_events & (GRETH_INT_TX|GRETH_INT_TXERR)) {
                GRETH_REGSAVE(regs->status, GRETH_INT_TX|GRETH_INT_TXERR);
		greth_tx(dev);
                netif_wake_queue(dev);
                handled = 1;
	}


out:       
      
	return IRQ_RETVAL(handled);
}


static void
greth_tx(struct net_device *dev)
{

	struct	greth_private *cep;
	volatile greth_bd *bdp;
	unsigned int stat;
        int i=0;

	_FUNCDBG("greth_tx\n");
	
	cep = (struct greth_private *)dev->priv;

	while (1) { 

	  	bdp = cep->tx_bd_base + cep->tx_last;
		stat = bdp->stat;

		if ((stat & GRETH_BD_EN) || ((cep->tx_last == cep->tx_next) && !cep->tx_full)) {
                    break;
                }
            

		/* Check status for errors
		 */
		if (stat & GRETH_TXBD_STATUS) {
		  if (stat & GRETH_TXBD_ERR_AL) 
		    cep->stats.tx_aborted_errors++;
		  if (stat & GRETH_TXBD_ERR_UE) 
		    cep->stats.tx_fifo_errors++;
		}

		cep->stats.tx_packets++;

		if (cep->tx_full) {
                    netif_wake_queue(dev);
                    cep->tx_full = 0;
                }


                cep->tx_last = (cep->tx_last + 1) & GRETH_TXBD_NUM_MASK;
	}
}

static void
greth_rx(struct net_device *dev)
{
	struct	greth_private *cep;
	greth_regs *regs = dev->base_addr;
	volatile greth_bd *bdp;
	struct	sk_buff *skb;
	int	pkt_len;
	int	bad = 0;
	
	unsigned int stat;
        u32 addr;

	_FUNCDBG("greth_rx\n");
	
	cep = (struct greth_private *)dev->priv;

	/* First, grab all of the stats for the incoming packet.
	 * These get messed up if we get called due to a busy condition.
	 */
	for (;;cep->rx_cur = (cep->rx_cur + 1) & GRETH_RXBD_NUM_MASK) {

		bdp = cep->rx_bd_base + cep->rx_cur;
		stat = bdp->stat;

	
		if (stat & GRETH_BD_EN)
			break;
			
		/* Check status for errors.
		 */
		if (stat & GRETH_RXBD_ERR_FT) { 
			cep->stats.rx_length_errors++;
			bad = 1;
		}
		if (stat & (GRETH_RXBD_ERR_AE | GRETH_RXBD_ERR_OE)) {
			cep->stats.rx_frame_errors++;
			bad = 1;
		}
		if (stat & GRETH_RXBD_ERR_CRC) { 
			cep->stats.rx_crc_errors++;
			bad = 1;
		}
		
		if (bad) {
		  printk("Bad packet received.\n");
		  bdp->stat = GRETH_BD_EN | GRETH_BD_IE | ((cep->rx_cur == GRETH_RXBD_NUM_MASK) ? GRETH_BD_WR : 0); 
		  GRETH_REGORIN(regs->control, GRETH_RXEN); 
                  bad = 0;
		  continue;
		}

		/* Process the incoming frame.
		 */
		pkt_len = stat & GRETH_BD_LEN; 

		skb = dev_alloc_skb(pkt_len + 4);

		if (skb == NULL) {
			printk("%s: Memory squeeze, dropping packet.\n", dev->name);
			cep->stats.rx_dropped++;
		}
		else {
			skb_reserve(skb, 2);
			skb->dev = dev;	

                        addr = (bdp->addr & ~0xf0000000) | 0x40000000;
//                        printk("addr: %x\n", addr);
                        pci_dma_sync_single_for_cpu(cep->pci_dev, addr, GRETH_RX_BUF_SIZE, PCI_DMA_FROMDEVICE);
                    			
#if DEBUG_RX_PACKETS
			printk("RX\n");
			greth_print_packet(__va(addr), pkt_len); 
#endif
			memcpy(skb_put(skb, pkt_len), (unsigned char *) __va(addr), pkt_len); 


			skb->protocol = eth_type_trans(skb,dev);
			netif_rx(skb);
			cep->stats.rx_packets++;
		}

		bdp->stat = GRETH_BD_EN | GRETH_BD_IE | ((cep->rx_cur == GRETH_RXBD_NUM_MASK) ? GRETH_BD_WR : 0); 

            
		GRETH_REGORIN(regs->control, GRETH_RXEN); 

	}
}


static struct net_device_stats *greth_get_stats(struct net_device *dev)
{
        struct greth_private *cep = (struct greth_private *)dev->priv;
 
        return &cep->stats;
}

static void greth_set_mac_add(struct net_device *dev, void *p)
{
	struct sockaddr *addr=p;
	volatile greth_regs *regs;

	memcpy(dev->dev_addr, addr->sa_data,dev->addr_len);

	regs = (greth_regs *)dev->base_addr;

	GRETH_REGSAVE(regs->esa_msb, 	addr->sa_data[0] << 8 	| 
				addr->sa_data[1]);
        GRETH_REGSAVE(regs->esa_lsb, 	addr->sa_data[2] << 24 	| 
				addr->sa_data[3] << 16 	| 
				addr->sa_data[4] << 8 	| 
				addr->sa_data[5]);

}

static void greth_set_multicast_list(struct net_device *dev) {
  ;
}

static void __greth_cleanup_dev (struct net_device *dev)
{
        struct greth_private *cep;
	struct pci_dev *pdev;

	assert (dev != NULL);
	assert (dev->priv != NULL);

        cep = dev->priv;
	assert (cep->pci_dev != NULL);
	pdev = cep->pci_dev;


	if (cep->mmio_addr)
		iounmap (cep->mmio_addr);

	/* it's ok to call this even if we have no regions to free */
	pci_release_regions (pdev);

	free_netdev(dev);

	pci_set_drvdata (pdev, NULL);
}

/* Initialize the GRETH MAC.
 */
int greth_pci_init(struct pci_dev *pdev, const struct pci_device_id *ent)
{
        struct net_device *dev = NULL;
        struct greth_private *cep;
	volatile greth_bd *tx_bd, *rx_bd;
	volatile greth_regs *regs;
	int i, j, k, tmp;

	unsigned long mem_addr;
        dma_addr_t dma_handle;

        
        void *ioaddr;
     	u8 tmp8;
	int rc;
	unsigned long mmio_start, mmio_end, mmio_flags, mmio_len;
	u32 version;


	/* dev and dev->priv zeroed in alloc_etherdev */
	dev = alloc_etherdev (sizeof (*cep));
	if (dev == NULL) {
		printk (KERN_ERR "%s: Unable to alloc new net device\n", pci_name(pdev));
		return -ENOMEM;
	}
	SET_MODULE_OWNER(dev);
	SET_NETDEV_DEV(dev, &pdev->dev);

	cep = dev->priv;
	cep->pci_dev = pdev;

	rc = pci_enable_device (pdev);
	if (rc)
		goto err_out;


	mmio_start = pci_resource_start (pdev, 0);
	mmio_end = pci_resource_end (pdev, 0);
	mmio_flags = pci_resource_flags (pdev, 0);
	mmio_len = pci_resource_len (pdev, 0);

 
	/* make sure PCI base addr 1 is MMIO */
	if (!(mmio_flags & IORESOURCE_MEM)) {
		printk (KERN_ERR "%s: region #1 not an MMIO resource, aborting\n", pci_name(pdev));
		rc = -ENODEV;
		goto err_out;
	}

	rc = pci_request_regions (pdev, "greth_pci");
	if (rc)
		goto err_out;


	/* enable PCI bus-mastering */
	pci_set_master (pdev);

	/* ioremap MMIO region */
	ioaddr = ioremap (mmio_start, mmio_len);
	if (ioaddr == NULL) {
		printk (KERN_ERR "%s: cannot remap MMIO, aborting\n", pci_name(pdev));
		rc = -EIO;
		goto err_out;
	}
	dev->base_addr = (long) ioaddr+0xf00;
	cep->mmio_addr = ioaddr;
	regs = (greth_regs *) (dev->base_addr);

#ifndef BT_ENABLED
        GRETH_REGSAVE(*(ioaddr+(mmio_len>>1)), 0x80000000);
#else
        writel(0x80000001, (ioaddr+(mmio_len>>1))); /* accesses to page0 aren't twisted */
#endif

        cep->pci_reg = ioaddr+0x400;
        GRETH_REGORIN(*cep->pci_reg, 0x40000000);

      	/* Reset the controller. */
	GRETH_REGSAVE(regs->control,GRETH_RESET); 
	
	while (GRETH_REGLOAD(regs->control) & GRETH_RESET) 
	  ;
   

	/* Configure PHY  */

	write_mii(0, 0x8000, regs); /* reset phy */
	while ( (tmp=read_mii(0, regs)) & 0x8000)
	  ;

	i = 0;
	if (tmp & 0x1000) { /* augo neg */
	  while ( !(read_mii(1, regs) & 0x20 ) ) {
		i++;
		if (i>50000) {
		  printk("Auto-negotiation failed\n");
		  break;
		}
	  }
	}

	tmp = read_mii(0, regs);

	if (tmp & 0x0100) {
	  /* set full duplex */
	  GRETH_REGORIN(regs->control,GRETH_FD); 
	}

	/* Initialize TXBD pointer
	 */
        
	cep->tx_bd_base =  (greth_bd *) pci_alloc_consistent(pdev, 1024, &cep->tx_bd_base_phys);

	GRETH_REGSAVE(regs->tx_desc_p,(int) ((cep->tx_bd_base_phys)&~0xf0000000) | 0xe0000000);
	tx_bd = (volatile greth_bd *)  cep->tx_bd_base;

	/* Initialize RXBD pointer
	 */
	cep->rx_bd_base =  (greth_bd *) pci_alloc_consistent(pdev, 1024, &cep->rx_bd_base_phys);
	GRETH_REGSAVE(regs->rx_desc_p,(int)  ((cep->rx_bd_base_phys)&~0xf0000000) | 0xe0000000); 
	rx_bd = (volatile greth_bd *)  cep->rx_bd_base;



	/* Initialize TXBDs.
	 */
	for(i = 0, k = 0; i < GRETH_TX_BUF_PAGE_NUM; i++) {

            mem_addr = __get_free_page(GFP_KERNEL);
            dma_handle = pci_map_single(pdev, mem_addr, GRETH_TX_BUF_SIZE, PCI_DMA_TODEVICE);


            for(j = 0; j < GRETH_TX_BUF_PPGAE; j++, k++) {
                tx_bd[k].addr = (unsigned int) ((dma_handle&~0xf0000000)|0xe0000000); 
                tx_bd[k].stat = 0;
                mem_addr += GRETH_TX_BUF_SIZE;	
                dma_handle += GRETH_TX_BUF_SIZE;
            }
	}
	tx_bd[GRETH_TXBD_NUM - 1].stat |= GRETH_BD_WR;

	/* Initialize RXBDs. */

	for(i = 0, k = 0; i < GRETH_RX_BUF_PAGE_NUM; i++) {

		mem_addr = __get_free_page(GFP_KERNEL);       
                dma_handle = pci_map_single(pdev, mem_addr, GRETH_RX_BUF_SIZE, PCI_DMA_FROMDEVICE);


		for(j = 0; j < GRETH_RX_BUF_PPGAE; j++, k++) {
		  rx_bd[k].addr = ((dma_handle&~0xf0000000)|0xe0000000);
                  mem_addr += GRETH_RX_BUF_SIZE;
                  dma_handle += GRETH_RX_BUF_SIZE;
		}
	}

	rx_bd[GRETH_RXBD_NUM - 1].stat |= GRETH_BD_WR;

	/* Set default ethernet station address.
	 */
	dev->dev_addr[0] = MACADDR0;
	dev->dev_addr[1] = MACADDR1;
	dev->dev_addr[2] = MACADDR2;
	dev->dev_addr[3] = MACADDR3;
	dev->dev_addr[4] = MACADDR4;
	dev->dev_addr[5] = MACADDR5;

	GRETH_REGSAVE(regs->esa_msb,MACADDR0 << 8 | MACADDR1); 
	GRETH_REGSAVE(regs->esa_lsb,MACADDR2 << 24 | MACADDR3 << 16 | MACADDR4 << 8 | MACADDR5);
	
	/* Clear all pending interrupts 
	 */
	GRETH_REGSAVE(regs->status,0); 


	/* Fill in the fields of the device structure with ethernet values. 
	 */
	ether_setup(dev);

	/* The GRETH Ethernet MAC specific entries in the device structure. 
	 */
	dev->open = greth_open;
	dev->hard_start_xmit = greth_start_xmit;
	dev->stop = greth_close;
	dev->get_stats = greth_get_stats;
	dev->set_multicast_list = greth_set_multicast_list;
	dev->set_mac_address = greth_set_mac_add;
        dev->irq = pdev->irq;

	if (register_netdev(dev)) {
	  kfree(dev->priv);
	  printk(KERN_ERR "greth: netdevice registration failed.\n");
	  return -ENOMEM;
       }


	printk("GRETH PCI Ethermac %s at [0x%x] irq %d. Running %d Mbps %s duplex\n", dev->name ? dev->name : "", (unsigned int)(regs), (unsigned int)(pdev->irq), \
	                                                                              ((tmp&0x2040) == 0x2000) ? 100:10, (tmp&0x0100) ? "full":"half");
	
	_FUNCDBG("greth_init exit\n");
	return 0;

err_out:
	__greth_cleanup_dev (dev);
	return 0;
}


static void __devexit greth_remove (struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata (pdev);

	unregister_netdev (dev);	
        __greth_cleanup_dev (dev);
}

static struct pci_driver greth_pci_driver = {
	.name		= "GRETH PCI",
	.id_table	= greth_pci_tbl,
	.probe		= greth_pci_init,
	.remove		= __devexit_p(greth_remove),
};


static int __init greth_init_module (void)
{
	return pci_module_init (&greth_pci_driver);
}


static void __exit greth_cleanup_module (void)
{
	pci_unregister_driver (&greth_pci_driver);
}


module_init(greth_init_module);
module_exit(greth_cleanup_module);
