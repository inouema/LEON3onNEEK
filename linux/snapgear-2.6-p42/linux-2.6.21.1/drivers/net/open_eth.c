/*
 * Ethernet driver for Open Ethernet Controller (www.opencores.org).
 *      Copyright (c) 2002 Simon Srot (simons@opencores.org)
 *
 * Based on:
 *
 * Ethernet driver for Motorola MPC8xx.
 *      Copyright (c) 1997 Dan Malek (dmalek@jlc.net)
 *
 * mcen302.c: A Linux network driver for Mototrola 68EN302 MCU
 *
 *      Copyright (C) 1999 Aplio S.A. Written by Vadim Lebedev
 *
 * Right now XXBUFF_PREALLOC must be used, because MAC does not 
 * handle unaligned buffers yet.  Also the cache inhibit calls
 * should be used some day.
 *
 */

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


#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/timer.h>
#include <linux/errno.h>
#include <linux/ioport.h>
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
#define OETH_INTERRUPT LEON_INTERRUPT_OPEN_ETH
//#define DEBUG 1
#endif

#define MACADDR0 0
#define MACADDR1 0
#define MACADDR2 0
#define MACADDR3 0
#define MACADDR4 0
#define MACADDR5 0
 

#include "open_eth.h"

//#define net_device device
//#define __pa(x) (x)
//#define __va(x) (x)
#define __clear_user(add,len) memset((add),0,(len))


#define RXBUFF_PREALLOC	1
#define TXBUFF_PREALLOC	1

//#define SRAM_BUFF	1
//#define SRAM_BUFF_BASE	(FBMEM_BASE_ADD + 0x80000)

/* The transmitter timeout
 */
#define TX_TIMEOUT	(2*HZ)

/* Buffer number (must be 2^n) 
 */
#define OETH_RXBD_NUM		8
#define OETH_TXBD_NUM		8
#define OETH_RXBD_NUM_MASK	(OETH_RXBD_NUM-1)
#define OETH_TXBD_NUM_MASK	(OETH_TXBD_NUM-1)

/* Buffer size 
 */
#define OETH_RX_BUFF_SIZE	2048
#define OETH_TX_BUFF_SIZE	2048

/* How many buffers per page 
 */
#define OETH_RX_BUFF_PPGAE	(PAGE_SIZE/OETH_RX_BUFF_SIZE)
#define OETH_TX_BUFF_PPGAE	(PAGE_SIZE/OETH_TX_BUFF_SIZE)

/* How many pages is needed for buffers 
 */
#define OETH_RX_BUFF_PAGE_NUM	(OETH_RXBD_NUM/OETH_RX_BUFF_PPGAE)
#define OETH_TX_BUFF_PAGE_NUM	(OETH_TXBD_NUM/OETH_TX_BUFF_PPGAE)

/* Buffer size  (if not XXBUF_PREALLOC 
 */
#define MAX_FRAME_SIZE		1518

/* The buffer descriptors track the ring buffers.   
 */
struct oeth_private {
	struct	sk_buff* rx_skbuff[OETH_RXBD_NUM];
	struct	sk_buff* tx_skbuff[OETH_TXBD_NUM];

	ushort	tx_next;			/* Next buffer to be sent */
	ushort	tx_last;			/* Next buffer to be checked if packet sent */
	ushort	tx_full;			/* Buffer ring fuul indicator */
	ushort	rx_cur;				/* Next buffer to be checked if packet received */

	oeth_regs	*regs;			/* Address of controller registers. */
	oeth_bd		*rx_bd_base;		/* Address of Rx BDs. */
	oeth_bd		*tx_bd_base;		/* Address of Tx BDs. */

	struct net_device_stats stats;
};

static int oeth_open(struct net_device *dev);
static int oeth_start_xmit(struct sk_buff *skb, struct net_device *dev);
static void oeth_rx(struct net_device *dev);
static void oeth_tx(struct net_device *dev);
static irqreturn_t oeth_interrupt(int irq, void *dev_id, struct pt_regs *regs);
static int oeth_close(struct net_device *dev);
static struct net_device_stats *oeth_get_stats(struct net_device *dev);
static void oeth_set_multicast_list(struct net_device *dev);
static int oeth_set_mac_address(struct net_device *dev,void *p);
static int calc_crc(char *mac_addr);

#if DEBUG
static void
oeth_print_packet(unsigned long add, int len)
{
  //	int i;

	printk("ipacket: add = %x len = %d\n", (unsigned int)add, len);
/*
	for(i = 0; i < len; i++) {
  		if(!(i % 16))
    			printk("\n");
  		printk(" %.2x", *(((unsigned char *)add) + i));
	}
*/
      printk("\n");
	printk("                             \n");
}
#endif

static int
oeth_open(struct net_device *dev)
{

	oeth_regs *regs = (oeth_regs *)dev->base_addr;

#ifndef RXBUFF_PREALLOC
	struct oeth_private *cep = (struct oeth_private *)dev->priv;
	struct  sk_buff *skb;
	volatile oeth_bd *rx_bd;
	int i;

	rx_bd = cep->rx_bd_base;

	for(i = 0; i < OETH_RXBD_NUM; i++) {

		skb = dev_alloc_skb(MAX_FRAME_SIZE);

		if (skb == NULL)
			rx_bd[i].len_status = (0 << 16) | OETH_RX_BD_IRQ;
		else
			rx_bd[i].len_status = (0 << 16) | OETH_RX_BD_EMPTY | OETH_RX_BD_IRQ;

		cep->rx_skbuff[i] = skb;

		rx_bd[i].addr = (unsigned long)skb->tail;
	}
	rx_bd[OETH_RXBD_NUM - 1].len_status |= OETH_RX_BD_WRAP;
#endif

	/* Install our interrupt handler.
	 */
	request_irq(OETH_INTERRUPT, oeth_interrupt, 0, "eth", (void *)dev);

	/* Enable receiver and transmiter 
	 */
	regs->moder |= OETH_MODER_RXEN | OETH_MODER_TXEN;

	return 0;
}

static int
oeth_close(struct net_device *dev)
{
	struct oeth_private *cep = (struct oeth_private *)dev->priv;
	oeth_regs *regs = (oeth_regs *)dev->base_addr;
	volatile oeth_bd *bdp;
	int i;

	/* Free interrupt hadler 
	 */
	free_irq(OETH_INTERRUPT, (void *)dev);

	/* Disable receiver and transmitesr 
	 */
	regs->moder &= ~(OETH_MODER_RXEN | OETH_MODER_TXEN);	

	bdp = cep->rx_bd_base;
	for (i = 0; i < OETH_RXBD_NUM; i++) {
		bdp->len_status &= ~(OETH_TX_BD_STATS | OETH_TX_BD_READY);
		bdp++;
	}

	bdp = cep->tx_bd_base;
	for (i = 0; i < OETH_TXBD_NUM; i++) {
		bdp->len_status &= ~(OETH_RX_BD_STATS | OETH_RX_BD_EMPTY);
		bdp++;
	}

#ifndef RXBUFF_PREALLOC

	/* Free all alocated rx buffers 
	 */
	for (i = 0; i < OETH_RXBD_NUM; i++) {
	
		if (cep->rx_skbuff[i] != NULL)
			dev_kfree_skb(cep->rx_skbuff[i]); //, FREE_READ);
		
	}
#endif
#ifndef TXBUFF_PREALLOC

	/* Free all alocated tx buffers 
	 */
	for (i = 0; i < OETH_TXBD_NUM; i++) {
	
		if (cep->tx_skbuff[i] != NULL)
			dev_kfree_skb(cep->tx_skbuff[i]);//, FREE_WRITE);
	}
#endif

	return 0;
}

static int
oeth_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct oeth_private *cep = (struct oeth_private *)dev->priv;
	volatile oeth_bd *bdp;
	unsigned long flags;

	/* Fill in a Tx ring entry 
	 */
	bdp = cep->tx_bd_base + cep->tx_next;

	if (cep->tx_full) {

		/* All transmit buffers are full.  Bail out.
		 */
		printk("%s: tx queue full!.\n", dev->name);
		return 1;
	}

	/* Clear all of the status flags.
	 */
	bdp->len_status &= ~OETH_TX_BD_STATS;

	/* If the frame is short, tell CPM to pad it.
	 */
	if (skb->len <= ETH_ZLEN)
		bdp->len_status |= OETH_TX_BD_PAD;
	else
		bdp->len_status &= ~OETH_TX_BD_PAD;

#if DEBUG
	printk("TX\n");
	oeth_print_packet((unsigned long)skb->data, skb->len);
#endif

#ifdef TXBUFF_PREALLOC

	/* Copy data in preallocated buffer */
	if (skb->len > OETH_TX_BUFF_SIZE) {
		printk("%s: tx frame too long!.\n", dev->name);
		return 1;
	}
	else {
		memcpy(__va((unsigned char *)bdp->addr), skb->data, skb->len); 
            __flush_page_to_ram((unsigned long)__va(bdp->addr));
      }

	bdp->len_status = (bdp->len_status & 0x0000ffff) | (skb->len << 16);

	dev_kfree_skb(skb); // 	dev_kfree_skb(skb, FREE_WRITE);
#else
	/* Set buffer length and buffer pointer.
	 */
	bdp->len_status = (bdp->len_status & 0x0000ffff) | (skb->len << 16);
	bdp->addr = (uint)__pa(skb->data);

	/* Save skb pointer.
	 */
	cep->tx_skbuff[cep->tx_next] = skb;
#endif

	cep->tx_next = (cep->tx_next + 1) & OETH_TXBD_NUM_MASK;
	
	save_flags(flags); cli();

	if (cep->tx_next == cep->tx_last)
		cep->tx_full = 1;

	/* Send it on its way.  Tell controller its ready, interrupt when done,
	 * and to put the CRC on the end.
	 */
	bdp->len_status |= (OETH_TX_BD_READY | OETH_TX_BD_IRQ | OETH_TX_BD_CRC);

	dev->trans_start = jiffies;

	restore_flags(flags);

	return 0;
}

/* The interrupt handler.
 */
static irqreturn_t
oeth_interrupt(int irq, void *dev_id, struct pt_regs *regs)
{
	struct	net_device *dev = dev_id;
	volatile struct	oeth_private *cep;
	uint	int_events;
      
#if DEBUG
      printk ("oeth_interrupt()\n");
#endif

	cep = (struct oeth_private *)dev->priv;

	/* Get the interrupt events that caused us to be here.
	 */
	int_events = cep->regs->int_src;
	cep->regs->int_src = int_events;

	/* Handle receive event in its own function.
	 */
	if (int_events & (OETH_INT_RXF | OETH_INT_RXE))
		oeth_rx(dev_id);

	/* Handle transmit event in its own function.
	 */
	if (int_events & (OETH_INT_TXB | OETH_INT_TXE)) {
		oeth_tx(dev_id);
            netif_wake_queue(dev); //mark_bh(NET_BH);
	}

	/* Check for receive busy, i.e. packets coming but no place to
	 * put them. 
	 */
	if (int_events & OETH_INT_BUSY) {
		if (!(int_events & (OETH_INT_RXF | OETH_INT_RXE)))
			oeth_rx(dev_id);
	}

	return IRQ_HANDLED;
}


static void
oeth_tx(struct net_device *dev)
{
	struct	oeth_private *cep;
	volatile oeth_bd *bdp;

#ifndef TXBUFF_PREALLOC
	struct	sk_buff *skb;
#endif

#if DEBUG
      printk ("oeth_tx()\n");
#endif

	cep = (struct oeth_private *)dev->priv;

	for (;; cep->tx_last = (cep->tx_last + 1) & OETH_TXBD_NUM_MASK) {

		bdp = cep->tx_bd_base + cep->tx_last;

		if ((bdp->len_status & OETH_TX_BD_READY) || 
			((cep->tx_last == cep->tx_next) && !cep->tx_full))
			break;

		/* Check status for errors
		 */
		if (bdp->len_status & OETH_TX_BD_LATECOL)
			cep->stats.tx_window_errors++;
		if (bdp->len_status & OETH_TX_BD_RETLIM)
			cep->stats.tx_aborted_errors++;
		if (bdp->len_status & OETH_TX_BD_UNDERRUN)
			cep->stats.tx_fifo_errors++;
		if (bdp->len_status & OETH_TX_BD_CARRIER)
			cep->stats.tx_carrier_errors++;
		if (bdp->len_status & (OETH_TX_BD_LATECOL | OETH_TX_BD_RETLIM | OETH_TX_BD_UNDERRUN))
			cep->stats.tx_errors++;

		cep->stats.tx_packets++;
		cep->stats.collisions += (bdp->len_status >> 4) & 0x000f;

#ifndef TXBUFF_PREALLOC
		skb = cep->tx_skbuff[cep->tx_last];

		/* Free the sk buffer associated with this last transmit.
		*/
		dev_kfree_skb(skb);//, FREE_WRITE);
#endif

		if (cep->tx_full)
			cep->tx_full = 0;
	}
}

static void
oeth_rx(struct net_device *dev)
{
	struct	oeth_private *cep;
	volatile oeth_bd *bdp;
	struct	sk_buff *skb;
	int	pkt_len;
	int	bad = 0;
#ifndef RXBUFF_PREALLOC
	struct	sk_buff *small_skb;
#endif
      
#if DEBUG
      printk ("oeth_rx()\n");
#endif

	cep = (struct oeth_private *)dev->priv;

	/* First, grab all of the stats for the incoming packet.
	 * These get messed up if we get called due to a busy condition.
	 */
	for (;;cep->rx_cur = (cep->rx_cur + 1) & OETH_RXBD_NUM_MASK) {

		bdp = cep->rx_bd_base + cep->rx_cur;

#ifndef RXBUFF_PREALLOC
		skb = cep->rx_skbuff[cep->rx_cur];

		if (skb == NULL) {

			skb = dev_alloc_skb(MAX_FRAME_SIZE);

			if (skb != NULL)
			{
				bdp->addr = (unsigned long) skb->tail;
				bdp->len_status |= OETH_RX_BD_EMPTY;
			}

			continue;
		}
#endif
			
		if (bdp->len_status & OETH_RX_BD_EMPTY)
			break;
			
		/* Check status for errors.
		 */
		if (bdp->len_status & (OETH_RX_BD_TOOLONG | OETH_RX_BD_SHORT)) {
                  printk ("oeth: length error\n");
			cep->stats.rx_length_errors++;
			bad = 1;
		}
		if (bdp->len_status & OETH_RX_BD_DRIBBLE) {
                  printk ("oeth: dribble error\n");
			cep->stats.rx_frame_errors++;
			bad = 1;
		}
		if (bdp->len_status & OETH_RX_BD_CRCERR) {
                  printk ("oeth: crc error\n");
			cep->stats.rx_crc_errors++;
			bad = 1;
		}
		if (bdp->len_status & OETH_RX_BD_OVERRUN) {
                  printk ("oeth: overrun error\n");
			cep->stats.rx_crc_errors++;
			bad = 1;
		}
		if (bdp->len_status & OETH_RX_BD_MISS) {
                  printk ("oeth: miss error\n");

		}
		if (bdp->len_status & OETH_RX_BD_LATECOL) {
                  printk ("oeth: latecol error\n");
			cep->stats.rx_frame_errors++;
			bad = 1;
		}
		
		
		if (bad) {

			bdp->len_status &= ~OETH_RX_BD_STATS;
      bdp->len_status |= OETH_RX_BD_EMPTY;

			continue;
		}

		/* Process the incoming frame.
		 */
		pkt_len = bdp->len_status >> 16;
        
#ifdef RXBUFF_PREALLOC
		//skb = dev_alloc_skb(pkt_len);
                skb = alloc_skb(pkt_len + 4, GFP_ATOMIC); //added from michael wurm's patches

		if (skb == NULL) {
			printk("%s: Memory squeeze, dropping packet.\n", dev->name);
			cep->stats.rx_dropped++;
		}
		else {
			skb_reserve(skb, 2); //added from michael wurm's patches
			skb->dev = dev;

                  __flush_page_to_ram((unsigned long)__va(bdp->addr));
#if DEBUG
			printk("RX\n");
                  oeth_print_packet((unsigned long)(__va(bdp->addr)), pkt_len);
#endif
			memcpy(skb_put(skb, pkt_len), (unsigned char *)__va(bdp->addr), pkt_len);
			skb->protocol = eth_type_trans(skb,dev);
			netif_rx(skb);
			cep->stats.rx_packets++;
		}

		bdp->len_status &= ~OETH_RX_BD_STATS;
		bdp->len_status |= OETH_RX_BD_EMPTY;
#else //RXBUFF_PREALLOC

		if (pkt_len < 128) {

			small_skb = dev_alloc_skb(pkt_len);

			if (small_skb) {
				small_skb->dev = dev;

                        __flush_page_to_ram(__va(bdp->addr));
#if DEBUG
				printk("RX short\n");
                        oeth_print_packet((unsigned long)(__va(bdp->addr)), bdp->len_status >> 16);
#endif
                        memcpy(skb_put(small_skb, pkt_len), (unsigned char *)__va(bdp->addr), pkt_len);

                        small_skb->protocol = eth_type_trans(small_skb,dev);
                        netif_rx(small_skb);
				cep->stats.rx_packets++;
			}
			else {
				printk("%s: Memory squeeze, dropping packet.\n", dev->name);
	                        cep->stats.rx_dropped++;
			}

			bdp->len_status &= ~OETH_RX_BD_STATS;
			bdp->len_status |= OETH_RX_BD_EMPTY;
		}
		else {
        		skb->dev = dev;
			skb_put(skb, bdp->len_status >> 16);
			skb->protocol = eth_type_trans(skb,dev);
			netif_rx(skb);
			cep->stats.rx_packets++;
#if DEBUG
			printk("RX long\n");
                        oeth_print_packet((unsigned long)(__va(bdp->addr)), bdp->len_status >> 16);
#endif
		
			skb = dev_alloc_skb(MAX_FRAME_SIZE);

			bdp->len_status &= ~OETH_RX_BD_STATS;
        
			if (skb) {
				cep->rx_skbuff[cep->rx_cur] = skb;

				bdp->addr = (unsigned long)skb->tail;
				bdp->len_status |= OETH_RX_BD_EMPTY;
			}
			else {
				cep->rx_skbuff[cep->rx_cur] = NULL;	
			}
		}
#endif //!RXBUFF_PREALLOC
	}
}

static int calc_crc(char *mac_addr)
{
	int result = 0;
	return (result & 0x3f);
}

static struct net_device_stats *oeth_get_stats(struct net_device *dev)
{
        struct oeth_private *cep = (struct oeth_private *)dev->priv;
 
        return &cep->stats;
}

static void oeth_set_multicast_list(struct net_device *dev)
{
	struct	oeth_private *cep;
	struct	dev_mc_list *dmi;
	volatile oeth_regs *regs;
	int	i;

	cep = (struct oeth_private *)dev->priv;

	/* Get pointer of controller registers.
	 */
	regs = (oeth_regs *)dev->base_addr;

	if (dev->flags & IFF_PROMISC) {
	  
		/* Log any net taps. 
		 */
		printk("%s: Promiscuous mode enabled.\n", dev->name);
		regs->moder |= OETH_MODER_PRO;
	} else {

		regs->moder &= ~OETH_MODER_PRO;

		if (dev->flags & IFF_ALLMULTI) {

			/* Catch all multicast addresses, so set the
			 * filter to all 1's.
			 */
			regs->hash_addr0 = 0xffffffff;
			regs->hash_addr1 = 0xffffffff;
		}
		else if (dev->mc_count) {

                        regs->moder |= OETH_MODER_IAM;
                        
			/* Clear filter and add the addresses in the list.
			 */
			regs->hash_addr0 = 0x00000000;
			regs->hash_addr0 = 0x00000000;

			dmi = dev->mc_list;

			for (i = 0; i < dev->mc_count; i++) {
				
				int hash_b;

				/* Only support group multicast for now.
				 */
				if (!(dmi->dmi_addr[0] & 1))
					continue;

				hash_b = calc_crc(dmi->dmi_addr); 
				if(hash_b >= 32)
					regs->hash_addr1 |= 1 << (hash_b - 32);
				else
					regs->hash_addr0 |= 1 << hash_b;
			}
		}
	}
}

static int oeth_set_mac_address(struct net_device *dev,void *p)
{
	struct sockaddr *addr=p;
	volatile oeth_regs *regs;
      
	memcpy(dev->dev_addr, addr->sa_data,dev->addr_len);
      
	regs = (oeth_regs *)dev->base_addr;
      
    
	    
// old version: sa_data is of type char, will be expanded to int when ored
// so negative values e.g 0xB5 will be expanded to 0xffffffB5 and ored
/*
	regs->mac_addr1 = 	addr->sa_data[0] << 8 	|
            			addr->sa_data[1];
        regs->mac_addr0 = 	addr->sa_data[2] << 24 	|
            			addr->sa_data[3] << 16 	|
            			addr->sa_data[4] << 8 	|
            			addr->sa_data[5];

*/

// dev_addr is of type unsigned char and will be expanded to unsigned int which is ok
	regs->mac_addr1 = 	dev->dev_addr[0] << 8 	|
            			dev->dev_addr[1];
        regs->mac_addr0 = 	dev->dev_addr[2] << 24 	|
            			dev->dev_addr[3] << 16 	|
            			dev->dev_addr[4] << 8 	|
            			dev->dev_addr[5];
	    
	    
	    
	return 0;
}

/* Initialize the Open Ethernet MAC.
 */
int do_oeth_probe(struct net_device *dev)
{
	struct oeth_private *cep;
	volatile oeth_regs *regs;
	volatile oeth_bd *tx_bd, *rx_bd;
	int i, j, k;
#ifdef SRAM_BUFF
	unsigned long mem_addr = SRAM_BUFF_BASE;
#else
	unsigned long mem_addr;
#endif


	printk("Probing Open Ethernet Core at 0x%x\n",OETH_REG_BASE);

	cep = (struct oeth_private *)dev->priv;

	/* Allocate a new 'dev' if needed. 
	 */
	if (dev == NULL) {
		/*
		 * Don't allocate the private data here, it is done later
		 * This makes it easier to free the memory when this driver
		 * is used as a module.
		 */
//		dev = init_etherdev(0, 0);
                dev=alloc_etherdev(0);		
//		dev = alloc_netdev(0, "eth0", setup_ether);
		if (dev == NULL)
			return -ENOMEM;
	}




	/* Initialize the device structure. 
	 */
	if (dev->priv == NULL) {
		cep = (struct oeth_private *)kmalloc(sizeof(*cep), GFP_KERNEL);
		dev->priv = cep;
		if (dev->priv == NULL)
			return -ENOMEM;
	}

	__clear_user(cep,sizeof(*cep));

	/* Get pointer ethernet controller configuration registers.
	 */
	cep->regs = (oeth_regs *)(OETH_REG_BASE);
	regs = (oeth_regs *)(OETH_REG_BASE);

	/* Reset the controller.
	 */
	regs->moder = OETH_MODER_RST;	/* Reset ON */
	regs->moder &= ~OETH_MODER_RST;	/* Reset OFF */

	/* Setting TXBD base to OETH_TXBD_NUM.
	 */
	regs->tx_bd_num = OETH_TXBD_NUM;
	
	/* Initialize TXBD pointer
	 */
	cep->tx_bd_base = (oeth_bd *)OETH_BD_BASE;
	tx_bd = (volatile oeth_bd *)OETH_BD_BASE;

	/* Initialize RXBD pointer
	 */
	cep->rx_bd_base = ((oeth_bd *)OETH_BD_BASE) + OETH_TXBD_NUM;
	rx_bd = ((volatile oeth_bd *)OETH_BD_BASE) + OETH_TXBD_NUM;

	/* Initialize transmit pointers.
	 */
	cep->rx_cur = 0;
	cep->tx_next = 0;
	cep->tx_last = 0;
	cep->tx_full = 0;

	/* Set min/max packet length 
	 */
	regs->packet_len = 0x00400600;

	/* Set IPGT register to recomended value 
	 */
	regs->ipgt = 0x00000012;

	/* Set IPGR1 register to recomended value 
	 */
	regs->ipgr1 = 0x0000000c;

	/* Set IPGR2 register to recomended value 
	 */
	regs->ipgr2 = 0x00000012;

	/* Set COLLCONF register to recomended value 
	 */
	regs->collconf = 0x000f003f;

	/* Set control module mode 
	 */
#if 0
	regs->ctrlmoder = OETH_CTRLMODER_TXFLOW | OETH_CTRLMODER_RXFLOW;
#else
	regs->ctrlmoder = 0;
#endif

  /* Set PHY to show Tx status, Rx status and Link status */
  /*regs->miiaddress = 20<<8;
  regs->miitx_data = 0x1422;
  regs->miicommand = OETH_MIICOMMAND_WCTRLDATA;*/
 
  // switch to 10 mbit ethernet
  regs->miiaddress = 0;
  regs->miitx_data = 0;
  regs->miicommand = OETH_MIICOMMAND_WCTRLDATA;
  
#ifdef TXBUFF_PREALLOC

	/* Initialize TXBDs.
	 */
	for(i = 0, k = 0; i < OETH_TX_BUFF_PAGE_NUM; i++) {

#ifndef SRAM_BUFF
		mem_addr = __get_free_page(GFP_KERNEL);
#endif

		for(j = 0; j < OETH_TX_BUFF_PPGAE; j++, k++) {
			tx_bd[k].len_status = OETH_TX_BD_PAD | OETH_TX_BD_CRC | OETH_RX_BD_IRQ;
			tx_bd[k].addr = __pa(mem_addr);
			mem_addr += OETH_TX_BUFF_SIZE;
		}
	}
	tx_bd[OETH_TXBD_NUM - 1].len_status |= OETH_TX_BD_WRAP;
#else

 	/* Initialize TXBDs.
	 */
	for(i = 0; i < OETH_TXBD_NUM; i++) {

		cep->tx_skbuff[i] = NULL;

		tx_bd[i].len_status = (0 << 16) | OETH_TX_BD_PAD | OETH_TX_BD_CRC | OETH_RX_BD_IRQ;
		tx_bd[i].addr = 0;
	}
	tx_bd[OETH_TXBD_NUM - 1].len_status |= OETH_TX_BD_WRAP;
#endif

#ifdef RXBUFF_PREALLOC

	/* Initialize RXBDs.
	 */
	for(i = 0, k = 0; i < OETH_RX_BUFF_PAGE_NUM; i++) {

#ifndef SRAM_BUFF
		mem_addr = __get_free_page(GFP_KERNEL);
#endif

		for(j = 0; j < OETH_RX_BUFF_PPGAE; j++, k++) {
			rx_bd[k].len_status = OETH_RX_BD_EMPTY | OETH_RX_BD_IRQ;
			rx_bd[k].addr = __pa(mem_addr);
			mem_addr += OETH_RX_BUFF_SIZE;
		}
	}
	rx_bd[OETH_RXBD_NUM - 1].len_status |= OETH_RX_BD_WRAP;

#else
	/* Initialize RXBDs.
	 */
	for(i = 0; i < OETH_RXBD_NUM; i++) {


		rx_bd[i].len_status = (0 << 16) | OETH_RX_BD_IRQ;

		cep->rx_skbuff[i] = NULL;

		rx_bd[i].addr = 0;
	}
	rx_bd[OETH_RXBD_NUM - 1].len_status |= OETH_RX_BD_WRAP;

#endif

	/* Set default ethernet station address.
	 */
	dev->dev_addr[0] = MACADDR0;
	dev->dev_addr[1] = MACADDR1;
	dev->dev_addr[2] = MACADDR2;
	dev->dev_addr[3] = MACADDR3;
	dev->dev_addr[4] = MACADDR4;
	dev->dev_addr[5] = MACADDR5;

	regs->mac_addr1 = MACADDR0 << 8 | MACADDR1;
	regs->mac_addr0 = MACADDR2 << 24 | MACADDR3 << 16 | MACADDR4 << 8 | MACADDR5;
	
	/* Clear all pending interrupts 
	 */
	regs->int_src = 0xffffffff;

	/* Promisc, IFG, CRCEn
	 */
	regs->moder |= OETH_MODER_PAD | OETH_MODER_IFG | OETH_MODER_CRCEN;

	/* Enable interrupt sources.
	 */
	regs->int_mask = OETH_INT_MASK_TXB 	| 
			OETH_INT_MASK_TXE 	| 
			OETH_INT_MASK_RXF 	| 
			OETH_INT_MASK_RXE 	|
			OETH_INT_MASK_BUSY 	|
			OETH_INT_MASK_TXC	|
			OETH_INT_MASK_RXC;

	/* Fill in the fields of the device structure with ethernet values. 
	 */
	ether_setup(dev);

	dev->base_addr = (unsigned long)OETH_REG_BASE;

	/* The Open Ethernet specific entries in the device structure. 
	 */
	dev->open = oeth_open;
	dev->hard_start_xmit = oeth_start_xmit;
	dev->stop = oeth_close;
	dev->get_stats = oeth_get_stats;
	dev->set_multicast_list = oeth_set_multicast_list;
	dev->set_mac_address = oeth_set_mac_address;

        if (register_netdev(dev)) {
               printk(KERN_ERR "open_eth: netdevice registration failed.\n");
			return -ENOMEM;
        }

	printk("%s: Open Ethernet Core Version 1.0\n", dev->name);

	return 0;
}

static struct net_device		*oeth_dev;		/* netdevice struct */
	
int  oeth_probe(void ) {

	
      printk("Init: Open Ethernet probe\n");
//      oeth_dev = init_etherdev(0, sizeof(struct oeth_private));
      oeth_dev=alloc_etherdev(sizeof(struct oeth_private));
//	oeth_dev = alloc_netdev(sizeof(struct oeth_private), "eth0", setup_ether);
      return do_oeth_probe(oeth_dev);
}

void oeth_cleanup(void) {
	
      printk("Open Ethernet Core cleanup\n");
	if (oeth_dev) {
            unregister_netdev(oeth_dev);
            kfree(oeth_dev);
      }
}

module_init(oeth_probe);
module_exit(oeth_cleanup);
MODULE_LICENSE("GPL");


