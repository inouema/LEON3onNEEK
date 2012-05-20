/* Ethernet driver for Gaisler Research's GRETH Ethernet MAC (www.gaisler.com)
 * 
 * Based on:
 * Ethernet driver for Opencores ethernet controller (www.opencores.org).
 *      Copyright (c) 2002 Simon Srot (simons@opencores.org)
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
#include <linux/jiffies.h>
#include <linux/version.h>

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

#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>

#ifdef CONFIG_LEON
#include <asm/leon.h>
#endif

#include "../../amba.h"
#include "greth.h"

#define _print printk

#define _FUNCDBG(a)
/* #define _FUNCDBG(a) printk(a) */
/* #define DEBUG */
/* #define DEBUG_TX_PACKETS */
/* #define DEBUG_RX_PACKETS */

#define RXBUFF_PREALLOC	1

#define MACADDR0 ((CONFIG_GRLIB_GAISLER_GRETH_MACMSB >> 16) & 0xff)
#define MACADDR1 ((CONFIG_GRLIB_GAISLER_GRETH_MACMSB >> 8) & 0xff)
#define MACADDR2 ((CONFIG_GRLIB_GAISLER_GRETH_MACMSB >> 0) & 0xff)
#define MACADDR3 ((CONFIG_GRLIB_GAISLER_GRETH_MACLSB >> 16) & 0xff)
#define MACADDR4 ((CONFIG_GRLIB_GAISLER_GRETH_MACLSB >> 8) & 0xff)
#define MACADDR5 ((CONFIG_GRLIB_GAISLER_GRETH_MACLSB >> 0) & 0xff)

/* How many buffers per page 
 */
#define GRETH_RX_BUF_PPGAE	(PAGE_SIZE/GRETH_RX_BUF_SIZE)
#define GRETH_TX_BUF_PPGAE	(PAGE_SIZE/GRETH_TX_BUF_SIZE)

/* How many pages are needed for buffers
 */
#define GRETH_RX_BUF_PAGE_NUM	(GRETH_RXBD_NUM/GRETH_RX_BUF_PPGAE)
#define GRETH_TX_BUF_PAGE_NUM	(GRETH_TXBD_NUM/GRETH_TX_BUF_PPGAE)

/* Buffer size, Gbit MAC uses the tagged maximum frame size which 
   is 1518 excluding CRC   */
#define MAX_FRAME_SIZE		1518 

/* The buffer descriptors track the ring buffers.   
 */
struct greth_private {
   struct sk_buff* rx_skbuff[GRETH_RXBD_NUM];
   struct sk_buff* tx_skbuff[GRETH_TXBD_NUM];
   
   u16 tx_next;			
   u16 tx_last;			
   u16 tx_free;			
   u16 rx_cur;
   
   u8 phyaddr;
   u8 sp;
   u8 gb;
   u8 fd;
   u8 multicast;
   u8 gbit_mac;
   u8 mdio_int_en;
   u8 edcl;
   u32 phy_vendor;
   u32 phy_model;
   u32 phy_rev;
   u32 phy_found;
   u32 phy_req;
   u32 auto_neg;
   u32 link_up;
   u32 ext_cap;
   u32 ext_stat;
   u32 phy_model_index;
   
   greth_regs *regs;			/* Address of controller registers. */
   greth_bd   *rx_bd_base;		/* Address of Rx BDs. */
   greth_bd   *tx_bd_base;		/* Address of Tx BDs. */
   
   int irq;
   struct net_device_stats stats;
	 spinlock_t devlock;

   struct work_struct greth_wq;
};

static int greth_open(struct net_device *dev);
static int greth_start_xmit(struct sk_buff *skb, struct net_device *dev);
static int greth_start_xmit_gbit(struct sk_buff *skb, struct net_device *dev);
static void greth_rx(struct net_device *dev);
static void greth_rx_gbit(struct net_device *dev);
static void greth_tx(struct net_device *dev);
static void greth_tx_gbit(struct net_device *dev);
static irqreturn_t greth_interrupt(int irq, void *dev_id, struct pt_regs *regs);
static int greth_close(struct net_device *dev);
static struct net_device_stats *greth_get_stats(struct net_device *dev);
static int greth_set_mac_add(struct net_device *dev, void *p);
static void greth_set_multicast_list(struct net_device *dev);

#define GRETH_REGLOAD(a)	        (LEON3_BYPASS_LOAD_PA(&(a)))
#define GRETH_REGSAVE(a,v)              (LEON3_BYPASS_STORE_PA(&(a),v))
#define GRETH_REGORIN(a,v)              (GRETH_REGSAVE(a,(GRETH_REGLOAD(a) | (v))))
#define GRETH_REGANDIN(a,v)             (GRETH_REGSAVE(a,(GRETH_REGLOAD(a) & (v))))

#define GRETH_REGLOAD_NOCACHE(a)	(LEON_BYPASSCACHE_LOAD_VA(&(a)))
#define GRETH_REGANDIN_NOCACHE(a,v) a = (GRETH_REGLOAD_NOCACHE(a) & (v))
#define GRETH_REGORIN_NOCACHE(a,v) a =  (GRETH_REGLOAD_NOCACHE(a) | (v))

#ifdef DEBUG
static void
greth_print_packet(unsigned long add, int len)
{
	int i;

	_print("ipacket: add = %x len = %d\n", add, len);
	for(i = 0; i < len; i++) {
  		if(!(i % 16))
    			_print("\n");
  		_print(" %.2x", *(((unsigned char *)add) + i));
	}
	_print("\n");
}

static void
greth_print_tx_packet(struct sk_buff *skb)
{
	int i;
        int j;
        int count;
	_print("ipacket: len = %d nr_frags = %d \n", skb->len, skb_shinfo(skb)->nr_frags);
        
        count = 0;
        for(i = 0; i < skb->len-skb->data_len; i++) {
                if(!(count % 16))
    			_print("\n");
                _print(" %.2x", *(((unsigned char *)skb->data) + i));
                count++;
        }


        for(i = 0; i < skb_shinfo(skb)->nr_frags; i++) {
                for(j = 0; j < skb_shinfo(skb)->frags[i].size; j++) {
                        if(!(count % 16))
                                _print("\n");
                        _print(" %.2x", *((unsigned char *)(__va(skb_shinfo(skb)->frags[i].page) + skb_shinfo(skb)->frags[i].page_offset+j)));
                        count++;
                }
        }
	_print("\n");
}
#endif


/* Wait for a register change with a timeout, jiffies used has time reference */
#define wait_loop(wait_statement,timeout_in_secs,goto_label_on_timeout,arg_on_timeout) \
	{ \
		unsigned long _timeout = jiffies + HZ*timeout_in_secs; \
		while( wait_statement ){ \
			if ( time_after(jiffies,_timeout) ){ \
				arg_on_timeout; \
				goto goto_label_on_timeout; \
			} \
		} \
	}

/* Return Error:
 *  0: no error
 *  -1: invalid input
 *  -2: MII busy (4s timeout)
 *  -3: MII busy after write to PHY (4s timeout)
 */
static int read_mii(int phyaddr, int regaddr, volatile greth_regs *regs)
{
	int err = 0;

	wait_loop( (GRETH_REGLOAD(regs->mdio) & GRETH_MII_BUSY), \
	           4, \
	           timeout, \
	           err=-2);
						 
	GRETH_REGSAVE(regs->mdio, ((phyaddr & 0x1F) << 11) | ((regaddr & 0x1F) << 6) | 2); 
        
	wait_loop( (GRETH_REGLOAD(regs->mdio) & GRETH_MII_BUSY), \
	           4, \
	           timeout, \
	           err=-3);
        
  if (!(GRETH_REGLOAD(regs->mdio) & GRETH_MII_NVALID)) {
		return (GRETH_REGLOAD(regs->mdio) >> 16) & 0xFFFF;
	}else {
		return -1;
  }
timeout:
	return err; 
}

/* Return Error:
 *  0: no error
 *  -2: MII busy (4s timeout)
 *  -3: MII busy after write to PHY (4s timeout)
 */
static int write_mii(int phyaddr, int regaddr, int data, volatile greth_regs *regs)
{
	int err = 0;
	
	wait_loop( (GRETH_REGLOAD(regs->mdio) & GRETH_MII_BUSY), \
	           4, \
	           timeout, \
	           err=-2);
        
	GRETH_REGSAVE(regs->mdio, ((data&0xFFFF)<<16) | ((phyaddr & 0x1F) << 11) | ((regaddr & 0x1F) << 6) | 1);
        
	wait_loop( (GRETH_REGLOAD(regs->mdio) & GRETH_MII_BUSY), \
	           4, \
	           timeout, \
	           err=-3);
						 				
	return 0;
timeout:
	return err;
}

#define write_mii_(phyaddr,regaddr,data,regs,goto_label_on_timeout,timeout_arg,store_error) \
	{ \
		int _ret; \
		_ret = write_mii(phyaddr,regaddr,data,regs); \
		if ( _ret < 0) { \
			store_error = _ret;\
			timeout_arg; \
			goto goto_label_on_timeout; \
		}\
	}

#define wait_read_mii(mask,phyaddr,regaddr,regs,timeout_in_secs,goto_label_on_timeout,timeout_arg,store_error) \
	{ \
		unsigned long _timeout = jiffies + HZ*timeout_in_secs; \
		while( ((tmp=read_mii(phyaddr,regaddr,regs))>=0) && (tmp & mask) ) { \
			if ( time_after(jiffies,_timeout) ){ \
				store_error = -10; \
				timeout_arg; \
				goto goto_label_on_timeout; \
			} \
		} \
		if ( tmp < 0 ) { \
			store_error = tmp;\
			timeout_arg; \
			goto goto_label_on_timeout; \
		} \
	}
	
#define read_mii_(result,phyaddr,regaddr,regs,goto_label_on_timeout,timeout_arg,store_error) \
	{ \
		result = read_mii(phyaddr,regaddr,regs); \
		if ( result < 0 ) { \
			store_error = result;\
			timeout_arg; \
			goto goto_label_on_timeout; \
		} \
	}

/* Determines the current operating mode after auto negotiation is finished */
int greth_aneg_get_mode(struct greth_private *cep) {
        int reg4;
        int reg5;
        int reg9;
        int reg10;
        int timeout_error;
        int timeout_error_desc;
        greth_regs *regs = cep->regs;
        
        read_mii_(reg4, cep->phyaddr, 4, regs, mode_timeout, timeout_error=0, timeout_error_desc);
        read_mii_(reg5, cep->phyaddr, 5, regs, mode_timeout, timeout_error=1, timeout_error_desc);
        reg9 = 0;
        reg10 = 0;
        if (cep->ext_stat) {
                read_mii_(reg9, cep->phyaddr, 9, regs, mode_timeout, timeout_error=2, timeout_error_desc);
                read_mii_(reg10, cep->phyaddr, 10, regs, mode_timeout, timeout_error=3, timeout_error_desc);
        }
        
        cep->gb = 0;
        cep->sp = 0;
        cep->fd = 0;
        
        /* Check if full-duplex*/
        if ( ((reg9 & ADVERTISE_1000FULL) && (reg10 & LPA_1000FULL))  ||
             ((reg4 & ADVERTISE_100FULL) && (reg5 & LPA_100FULL)) ||
             ((reg4 & ADVERTISE_10FULL) && (reg5 & LPA_10FULL)) ) {
                cep->fd = 1;
        }

        /* Check if gigabit */
        if ( ((reg9 & ADVERTISE_1000FULL) && (reg10 & LPA_1000FULL))  ||
             ((reg9 & ADVERTISE_1000HALF) && (reg10 & LPA_1000HALF)) ) {
                cep->gb = 1;
        /* or 100 mbit */       
        } else if ( ((reg4 & ADVERTISE_100FULL) && (reg5 & LPA_100FULL))  ||
             ((reg4 & ADVERTISE_100HALF) && (reg5 & LPA_100HALF)) ||
             ((reg4 & ADVERTISE_100BASE4) && (reg5 & LPA_100BASE4)) ) {
                cep->sp = 1;
        } 
        /* None, of the above, then it must be 10 Mbit which was selected
           as default */
        
        return 0;
mode_timeout:
        return -timeout_error;
        
}



int greth_renegotiate(struct greth_private *cep, int base1000x_fd, int base1000x_hd, int base100x_fd, 
                      int base100x_hd, int base10x_fd, int base10x_hd, int base100_t4) {
        
        int tmp;
        int timeout_error;
        int timeout_error_desc;
        greth_regs *regs;

        regs = cep->regs;
        
        /* Set new advertised capabilities*/
        read_mii_(tmp, cep->phyaddr, 4, regs, err_neg_timeout, timeout_error=0, timeout_error_desc);
        tmp = (tmp & 0xFC1F) | (base100_t4 << 9) | (base100x_fd << 8) | 
                (base100x_hd << 7) | (base10x_fd << 6) | (base10x_hd << 5);
        write_mii_(cep->phyaddr, 4, tmp, regs, err_neg_timeout, timeout_error=1, timeout_error_desc);

        if (cep->ext_stat) {
                read_mii_(tmp, cep->phyaddr, 9, regs, err_neg_timeout, timeout_error=2, timeout_error_desc);
                tmp = (tmp & 0xFC00) | (base1000x_fd << 9) | (base1000x_hd << 8);
                write_mii_(cep->phyaddr, 9, tmp, regs, err_neg_timeout, timeout_error=3, timeout_error_desc);
        }
        
        /* Restart auto negotiation */
        read_mii_(tmp, cep->phyaddr, 0, regs, err_neg_timeout, timeout_error=4, timeout_error_desc);
        write_mii_(cep->phyaddr, 0, tmp | (1 << 9), regs, err_neg_timeout, timeout_error=5, timeout_error_desc);
                
        return 0;

err_neg_timeout:
        
        return -timeout_error;
}

/* PHY r/w workqueue */
static void phy_detect_wq(struct work_struct *wq) 
{
        greth_regs *regs; 
        struct greth_private *cep;
        int ctrl;
        int status;
        int tmp;
        
        cep = container_of(wq, struct greth_private, greth_wq);
        regs = cep->regs;
        
        spin_lock(&cep->devlock);
        
        /* Clear interrupt */
        switch (cep->phy_model_index) {
                case 1: /* MARVELL 88EE1111 */
                        /*interrupts cleared by reading register 19 */
                        tmp = read_mii(cep->phyaddr, 19, regs);
                        break;
                case 2: /* INTEL LXT971A */
                        /*interrupts cleared by reading register 19 */
                        tmp = read_mii(cep->phyaddr, 19, regs);
                        break;
                case 3: /* NS DP83848 */
                        /*interrupts cleared by reading register 18 */
                        tmp = read_mii(cep->phyaddr, 18, regs);
                        break;
                case 4: /* NS DP83865 */
                        /*interrupts cleared by writing register 23 with ones */
                        tmp = write_mii(cep->phyaddr, 23, 0xFFF8, regs);
                        break;
                case 5: /* Vitesse VSC8641 */
                        /*interrupts cleared by reading register 26 */
                        tmp = read_mii(cep->phyaddr, 26, regs);
                        break;
                default:
                        printk("ERROR: Interrupts enabled with unknown PHY");
                        goto detect_end;
                        break;
        }
        
        if (tmp < 0) {
                printk("ERROR: MDIO read failed. State unchanged \n");
                goto detect_end;
        }
        
        /* Read phy ctrl and status register and determine current state */
        ctrl = read_mii(cep->phyaddr, 0, regs);

        status = read_mii(cep->phyaddr, 1, regs);

        cep->link_up = status & BMSR_LSTATUS;
        
        if (cep->phy_model_index == 4) { 
                /* NSDP83865 special bit for link status */
                tmp = read_mii(cep->phyaddr, 17, regs);
                cep->link_up = tmp & 0x4;
        } else if ((cep->phy_model_index == 1) || (cep->phy_model_index == 2)) {
                /* Marvell, Intel special bit for link status */
                tmp = read_mii(cep->phyaddr, 17, regs);
                cep->link_up = tmp & 0x400;
        }
        
        if ((ctrl < 0) || (status < 0) ) {
                printk("ERROR: MDIO read failed. State unchanged\n");
        } else {
                if (cep->link_up && cep->auto_neg) {
                        /* get auto negotiated mode, if it fails use 10 mbit hd */
                        if (0 > greth_aneg_get_mode(cep)) {
                                cep->gb = 0;
                                cep->sp = 0;
                                cep->fd = 0;
                        }
                        GRETH_REGANDIN(regs->control,~((1 << 8) | (1 << 7) | (1 << 4))); /* clear mode bits*/
                        GRETH_REGORIN(regs->control, (cep->gb << 8) | (cep->sp << 7) | (cep->fd << 4));
                        if ((cep->gb) && (!cep->gbit_mac)) {
                                tmp = greth_renegotiate(cep, 0, 0, 1, 1, 1, 1, 1);
                        }
                } 
        }
        
detect_end:
        spin_unlock(&cep->devlock);

}

static int
greth_open(struct net_device *dev)
{
	struct greth_private *cep = netdev_priv(dev);
        struct sk_buff *skb;
        int i;
        volatile greth_bd *rx_bd;
        
	greth_regs *regs = (greth_regs *)dev->base_addr;

	_FUNCDBG("greth_open\n");
	
        rx_bd = cep->rx_bd_base;
        
        if (cep->gbit_mac) {
                for(i = 0; i < GRETH_RXBD_NUM; i++) {
                        skb = dev_alloc_skb(MAX_FRAME_SIZE);
                        skb_reserve(skb, NET_IP_ALIGN);
                        if (skb == NULL) {
                                break;
                        }
                        rx_bd[i].stat = GRETH_BD_EN | GRETH_BD_IE;
                        rx_bd[i].addr = (uint)__pa(skb->data);
                        cep->rx_skbuff[i] = skb;
                }
        } else {
                for(i = 0; i < GRETH_RXBD_NUM; i++) {
                        rx_bd[i].stat = GRETH_BD_EN | GRETH_BD_IE;
                }
        }
        GRETH_REGORIN_NOCACHE(rx_bd[GRETH_RXBD_NUM - 1].stat, GRETH_BD_WR);

        /* Install our interrupt handler.
	 */
	request_irq(cep->irq, greth_interrupt, 0, "eth", (void *)dev);

	/* Enable receiver
	 */
	GRETH_REGORIN(regs->control, GRETH_RXEN | GRETH_RXI | GRETH_TXI);
        return 0;
        
}

static int
greth_close(struct net_device *dev)
{
	struct greth_private *cep = netdev_priv(dev);
	greth_regs *regs = (greth_regs *)dev->base_addr;
	volatile greth_bd *bdp;
	int i;

	_FUNCDBG("greth_close\n");
	
	/* Free interrupt hadler 
	 */
	free_irq(cep->irq, (void *)dev);

	/* Disable receiver and transmitesr 
	 */
	GRETH_REGANDIN(regs->control, ~(GRETH_RXEN | GRETH_TXEN));

	bdp = cep->rx_bd_base;
	for (i = 0; i < GRETH_RXBD_NUM; i++) {
	        GRETH_REGANDIN_NOCACHE(bdp->stat,~(GRETH_RXBD_STATUS | GRETH_BD_EN));
		bdp++;
	}

	bdp = cep->tx_bd_base;
	for (i = 0; i < GRETH_TXBD_NUM; i++) {
	        GRETH_REGANDIN_NOCACHE(bdp->stat, ~(GRETH_RXBD_STATUS | GRETH_BD_EN));
		bdp++;
	}
        
        if (cep->gbit_mac) {
                /* Free all allocated rx buffers */
                for (i = 0; i < GRETH_RXBD_NUM; i++) {
                        if (cep->rx_skbuff[i] != NULL)
                                dev_kfree_skb(cep->rx_skbuff[i]);
                }

                /* Free all allocated tx buffers */
                for (i = 0; i < GRETH_TXBD_NUM; i++) {
                        if (cep->tx_skbuff[i] != NULL)
                                dev_kfree_skb(cep->tx_skbuff[i]);
                }
        }
        return 0;
}

static int
greth_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct greth_private *cep = netdev_priv(dev);
	greth_regs *regs;
	volatile greth_bd *bdp;
	unsigned long flags, err=0;
        
        _FUNCDBG("greth_start_xmit\n");
	
	spin_lock_irqsave(&cep->devlock,flags);
	regs = (greth_regs *)dev->base_addr;
	
	/* Fill in a Tx ring entry 
	 */
	bdp = cep->tx_bd_base + cep->tx_next;

        if (unlikely(cep->tx_free <= 0)) {
                /* All transmit buffers are full.  Stop queue
		 */
                netif_stop_queue(dev);
                err = 1;
								goto out;
	}

#ifdef DEBUG_TX_PACKETS
	_print("TX\n");
	greth_print_packet(skb->data, skb->len);
#endif

        /* Copy data in preallocated buffer */
	if (unlikely(skb->len > MAX_FRAME_SIZE)) {
                err = 1;
								goto out;
	} else {
                memcpy((unsigned char *)__va(GRETH_REGLOAD_NOCACHE(bdp->addr)), skb->data, skb->len); 
                __flush_page_to_ram((unsigned long)__va(GRETH_REGLOAD_NOCACHE(bdp->addr)));
	}
        bdp->stat = GRETH_BD_EN | GRETH_BD_IE | (skb->len & GRETH_BD_LEN) | \
                    ((cep->tx_next == GRETH_TXBD_NUM_MASK) ? GRETH_BD_WR : 0);
	GRETH_REGORIN(regs->control, GRETH_TXEN);

        cep->tx_next = ((cep->tx_next + 1) & GRETH_TXBD_NUM_MASK);

        /* need to disable interrupts since free can be changed in interrupt handler*/
        cep->tx_free = cep->tx_free - 1;
        
        /* Send it on its way.  Tell controller its ready, interrupt when done,
	 * and to put the CRC on the end.
	 */
        dev->trans_start = jiffies;
				
        /* Turn IRQ on again */
        spin_unlock_irqrestore(&cep->devlock,flags);
				
        /* Free Socket Buffer */
        dev_kfree_skb(skb);
        return 0;
				
out:
			spin_unlock_irqrestore(&cep->devlock,flags);
        return err;
}

static int
greth_start_xmit_gbit(struct sk_buff *skb, struct net_device *dev)
{
	struct greth_private *cep = netdev_priv(dev);
	greth_regs *regs = (greth_regs *)dev->base_addr;
	volatile greth_bd *bdp;
	unsigned long flags, err=0;
        int nr_frags;
        int i;
        
        _FUNCDBG("greth_start_xmit_gbit\n");
	
	spin_lock_irqsave(&cep->devlock,flags);	
	
	regs = (greth_regs *)dev->base_addr;

        nr_frags = skb_shinfo(skb)->nr_frags;

        /* Fill in a Tx ring entry 
	 */
	bdp = cep->tx_bd_base + cep->tx_next;

        if (cep->tx_free < nr_frags + 1) {
                /* Not enough transmit buffers. stop queue
		 */
                netif_stop_queue(dev);
		err = 1;
		goto out;
	}

#ifdef DEBUG_TX_PACKETS
	_print("TX\n");
	greth_print_tx_packet(skb);
#endif

        /* Check length */
	if (unlikely(skb->len > MAX_FRAME_SIZE)) {
		err = 1;
		goto out;
	}

        /* Set buffer length and buffer pointer.
	 */
	bdp->addr = (uint)__pa(skb->data);
   
	bdp->stat = GRETH_BD_EN | GRETH_BD_IE | (skb->len & GRETH_BD_LEN) | \
                    GRETH_TXBD_IPCS | GRETH_TXBD_TCPCS | GRETH_TXBD_UDPCS | 
                    ((cep->tx_next == GRETH_TXBD_NUM_MASK) ? GRETH_BD_WR : 0) 
                    | ((nr_frags == 0) ? 0 : GRETH_TXBD_MORE);

        
        
        /* Save skb pointer.
	 */
        
        cep->tx_skbuff[cep->tx_next] = skb;           

        cep->tx_next = ((cep->tx_next + 1) & GRETH_TXBD_NUM_MASK);
        
        if (nr_frags) {
                for(i = 0; i < nr_frags; i++) {
                        bdp->stat = GRETH_BD_EN | GRETH_BD_IE | (skb_shinfo(skb)->frags[i].size & GRETH_BD_LEN) | \
                                GRETH_TXBD_IPCS | GRETH_TXBD_TCPCS | GRETH_TXBD_UDPCS | 
                                ((cep->tx_next == GRETH_TXBD_NUM_MASK) ? GRETH_BD_WR : 0) 
                                | ((i == nr_frags - 1) ? 0 : GRETH_TXBD_MORE);
                        bdp->addr = (uint)skb_shinfo(skb)->frags[i].page + skb_shinfo(skb)->frags[i].page_offset;
                        cep->tx_skbuff[cep->tx_next] = NULL;
                        cep->tx_next = ((cep->tx_next + 1) & GRETH_TXBD_NUM_MASK);
                        bdp = cep->tx_bd_base + cep->tx_next;
                }
        }
        
        /* tx_free can be changed in interrupt handler som irqs must be disabled here*/
        
	cep->tx_free = cep->tx_free - 1 - nr_frags;
        
	/* Send it on its way.  Tell controller its ready, interrupt when done,
	 * and to put the CRC on the end.
	 */
        GRETH_REGORIN(regs->control, GRETH_TXEN);

	dev->trans_start = jiffies;

out:
	spin_unlock_irqrestore(&cep->devlock,flags);        
        return err;
}

/* The interrupt handler.
 */
static irqreturn_t
greth_interrupt(int irq, void *dev_id, struct pt_regs *regs)
{
	struct	net_device *dev = dev_id;
	volatile struct	greth_private *cep;
	uint	int_events;

	_FUNCDBG("greth_interrupt\n");
	
	cep = netdev_priv(dev);

	spin_lock(&cep->devlock);
	
	/* Get the interrupt events that caused us to be here.
	 */
	int_events = GRETH_REGLOAD(cep->regs->status);
	GRETH_REGORIN(cep->regs->status, int_events & (GRETH_INT_RX | GRETH_INT_TX | GRETH_STATUS_PHYSTAT) );

	/* Handle receive event in its own function.
	 */
	if (int_events & GRETH_INT_RX) {
                if (cep->gbit_mac) {
                        greth_rx_gbit(dev_id);
                } else {
                        greth_rx(dev_id);
                }
        }
        
        /* Handle transmit event in its own function.
	 */
	if (int_events & GRETH_INT_TX) {
                if (cep->gbit_mac) {
                        greth_tx_gbit(dev_id);
                } else {
                        greth_tx(dev_id);
                }
                netif_wake_queue(dev);
        }

        /* Check for PHY status change */
        if ((int_events & GRETH_STATUS_PHYSTAT) && cep->phy_req) {
                /* start workqueue which handles slow mii ops */
                schedule_work(&cep->greth_wq);

        }
        spin_unlock(&cep->devlock);
	return IRQ_HANDLED;
}


static void
greth_tx(struct net_device *dev)
{
	struct	greth_private *cep;
	volatile greth_bd *bdp;
	unsigned int stat;
        
        _FUNCDBG("greth_tx\n");
	
	cep = netdev_priv(dev);

	for (;;) {
	  	bdp = cep->tx_bd_base + cep->tx_last;
		stat = GRETH_REGLOAD_NOCACHE(bdp->stat);
	
		if (unlikely(stat & GRETH_BD_EN))
			break;

                if (cep->tx_free == GRETH_TXBD_NUM) 
                        break;
                
                /* Check status for errors
		 */
		if (unlikely(stat & GRETH_TXBD_STATUS)) {
                        if (stat & GRETH_TXBD_ERR_AL)
                                cep->stats.tx_aborted_errors++;
                        if (stat & GRETH_TXBD_ERR_UE)
                                cep->stats.tx_fifo_errors++;
                }
                cep->stats.tx_packets++;
                cep->tx_last = (cep->tx_last + 1) & GRETH_TXBD_NUM_MASK;
                cep->tx_free++;
        }
}

static void
greth_tx_gbit(struct net_device *dev)
{
	struct	greth_private *cep;
	volatile greth_bd *bdp;
	unsigned int stat;
        struct sk_buff *skb;

        _FUNCDBG("greth_tx_gbit\n");
	
	cep = netdev_priv(dev);

	while(1) {
	  	bdp = cep->tx_bd_base + cep->tx_last;
		stat = GRETH_REGLOAD_NOCACHE(bdp->stat);
	
		if (stat & GRETH_BD_EN)
			break;
                
                if (cep->tx_free >= GRETH_TXBD_NUM) 
                        break;

		/* Check status for errors
		 */
		if (unlikely(stat & GRETH_TXBD_STATUS)) {
                        cep->stats.tx_errors++;
                        if (stat & GRETH_TXBD_ERR_AL)
                                cep->stats.tx_aborted_errors++;
                        if (stat & GRETH_TXBD_ERR_UE)
                                cep->stats.tx_fifo_errors++;
                        if (stat & GRETH_TXBD_ERR_LC)
                                cep->stats.tx_aborted_errors++;
		}
                cep->stats.tx_packets++;

                /* Free the sk buffer associated with this last transmit.
		*/
                skb = cep->tx_skbuff[cep->tx_last];
                if (skb != NULL) {
                        dev_kfree_skb_irq(skb);
                }
                cep->tx_last = (cep->tx_last + 1) & GRETH_TXBD_NUM_MASK;
                cep->tx_free++;
        }
}

static void
greth_rx(struct net_device *dev)
{
	struct	greth_private *cep;
	greth_regs *regs = (greth_regs *)dev->base_addr;
	volatile greth_bd *bdp;
	struct	sk_buff *skb;
	int	pkt_len;
	int	bad;
	unsigned int stat;
        
        _FUNCDBG("greth_rx\n");
	
	cep = netdev_priv(dev);

	/* First, grab all of the stats for the incoming packet.
	 * These get messed up if we get called due to a busy condition.
	 */
	for (;;cep->rx_cur = (cep->rx_cur + 1) & GRETH_RXBD_NUM_MASK) {

		bdp = cep->rx_bd_base + cep->rx_cur;
		stat = GRETH_REGLOAD_NOCACHE(bdp->stat);
		bad = 0;

                if (unlikely(stat & GRETH_BD_EN))
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
		if (unlikely(bad)) {
                        cep->stats.rx_errors++;
                        bdp->stat = GRETH_BD_EN | GRETH_BD_IE | ((cep->rx_cur == GRETH_RXBD_NUM_MASK) ? GRETH_BD_WR : 0);
                        GRETH_REGORIN(regs->control, GRETH_RXEN);
                        continue;
		}

		/* Process the incoming frame.
		 */
		pkt_len = stat & GRETH_BD_LEN;
                
                skb = dev_alloc_skb(pkt_len+NET_IP_ALIGN);
                
                if (unlikely(skb == NULL)) {
			printk("%s: Memory squeeze, dropping packet.\n", dev->name);
			cep->stats.rx_dropped++;
		} else {
			skb_reserve(skb, NET_IP_ALIGN);
			skb->dev = dev;
			__flush_page_to_ram((unsigned long)__va(GRETH_REGLOAD_NOCACHE(bdp->addr)));
			
#ifdef DEBUG_RX_PACKETS
			_print("RX\n");
			greth_print_packet(__va(GRETH_REGLOAD_NOCACHE(bdp->addr)), pkt_len);
#endif
                        memcpy(skb_put(skb, pkt_len), (unsigned char *)__va(GRETH_REGLOAD_NOCACHE(bdp->addr)), pkt_len);
                        skb->protocol = eth_type_trans(skb, dev);
			netif_rx(skb);
			cep->stats.rx_packets++;
		}
                bdp->stat = GRETH_BD_EN | GRETH_BD_IE | ((cep->rx_cur == GRETH_RXBD_NUM_MASK) ? GRETH_BD_WR : 0); 
		GRETH_REGORIN(regs->control, GRETH_RXEN);
        }
}

static void
greth_rx_gbit(struct net_device *dev)
{
	struct	greth_private *cep;
	greth_regs *regs = (greth_regs *)dev->base_addr;
	volatile greth_bd *bdp;
	struct	sk_buff *skb;
	int	pkt_len;
	int	bad;
	unsigned int stat;
        char    broadcast[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
        
        
        _FUNCDBG("greth_rx_gbit\n");
	
	cep = netdev_priv(dev);

	/* First, grab all of the stats for the incoming packet.
	 * These get messed up if we get called due to a busy condition.
	 */
	for (;;cep->rx_cur = (cep->rx_cur + 1) & GRETH_RXBD_NUM_MASK) {

		bdp = cep->rx_bd_base + cep->rx_cur;
		stat = GRETH_REGLOAD_NOCACHE(bdp->stat);
		bad = 0;

                skb = cep->rx_skbuff[cep->rx_cur];

                if (stat & GRETH_BD_EN)
			break;

                /* Check status for errors.
		 */
		if (stat & GRETH_RXBD_ERR_FT) {
			cep->stats.rx_length_errors++;
			bad = 1;
                } else if (stat & (GRETH_RXBD_ERR_AE | GRETH_RXBD_ERR_OE | GRETH_RXBD_ERR_LE)) {
			cep->stats.rx_frame_errors++;
			bad = 1;
                } else if (stat & GRETH_RXBD_ERR_CRC) {
			cep->stats.rx_crc_errors++;
			bad = 1;
                } 

                if (unlikely(bad)) {
                        cep->stats.rx_dropped++;
                        bdp->stat = GRETH_BD_EN | GRETH_BD_IE | ((cep->rx_cur == GRETH_RXBD_NUM_MASK) ? GRETH_BD_WR : 0);
                        GRETH_REGORIN(regs->control, GRETH_RXEN);
                        continue;
		}

                if ( !(stat & GRETH_RXBD_IP_FRAG) && (
                   ((stat & GRETH_RXBD_UDP_DEC) && !(stat & (GRETH_RXBD_UDP_CSERR | GRETH_RXBD_IP_CSERR))) || 
                   ((stat & GRETH_RXBD_TCP_DEC) && !(stat & (GRETH_RXBD_TCP_CSERR | GRETH_RXBD_IP_CSERR)))) ) {
                        skb->ip_summed = CHECKSUM_UNNECESSARY;
                } else {
                        skb->ip_summed = CHECKSUM_NONE;
                }
                
                /* Process the incoming frame.
		 */
                pkt_len = stat & GRETH_BD_LEN;
                
                if (!((memcmp(__va(bdp->addr), dev->dev_addr, dev->addr_len) == 0) || (memcmp(__va(bdp->addr), broadcast, sizeof(broadcast)) == 0)))

                {

                        u8 *p = __va(bdp->addr);
                        
                        if ((p[0] & 1) == 0)

                                printk("greth_rx_gbit: weird destination MAC address %02x:%02x:%02x:%02x:%02x:%02x, stat = 0x%08x\n", p[0], p[1], p[2], p[3], p[4], p[5], stat);
                        
                }

                skb->dev = dev;
                skb_put(skb, pkt_len);
                skb->protocol = eth_type_trans(skb, dev);
                netif_rx(skb);
                cep->stats.rx_packets++;
#ifdef DEBUG_RX_PACKETS
                _print("RX packet\n");
                greth_print_packet(__va(bdp->addr), pkt_len);
#endif
                skb = dev_alloc_skb(MAX_FRAME_SIZE);
                skb_reserve(skb, NET_IP_ALIGN);
                
                if (skb) {
                        cep->rx_skbuff[cep->rx_cur] = skb;
                        bdp->addr = (uint)__pa(skb->data);
                        bdp->stat = GRETH_BD_EN | GRETH_BD_IE | ((cep->rx_cur == GRETH_RXBD_NUM_MASK) ? GRETH_BD_WR : 0);
                        GRETH_REGORIN(regs->control, GRETH_RXEN);
                } else {
                        cep->rx_skbuff[cep->rx_cur] = NULL;	
                }
        }
        
}


static struct net_device_stats *greth_get_stats(struct net_device *dev)
{
        struct greth_private *cep = netdev_priv(dev);
 
        return &cep->stats;
}

static int greth_set_mac_add(struct net_device *dev, void *p)
{
	struct sockaddr *addr=p;
	volatile greth_regs *regs;

	memcpy(dev->dev_addr, addr->sa_data,dev->addr_len);

	regs = (greth_regs *)dev->base_addr;

	GRETH_REGSAVE(regs->esa_msb, 	
                                addr->sa_data[0] << 8 	| 
				addr->sa_data[1]);
        GRETH_REGSAVE(regs->esa_lsb,
                          	addr->sa_data[2] << 24 	| 
				addr->sa_data[3] << 16 	| 
				addr->sa_data[4] << 8 	| 
				addr->sa_data[5]);
	return 0;
}

static u32 greth_hash_get_index(__u8 *addr)
{
        return (ether_crc(6, addr)) & 0x3F;
}

static void greth_set_hash_filter(struct net_device *dev)
{
    struct dev_mc_list *curr;
    u32 mc_filter[2];
    unsigned int i, bitnr;
    volatile greth_regs *regs;

    unsigned int j;

    regs = (greth_regs *)dev->base_addr;
    mc_filter[0] = mc_filter[1] = 0;
    
    curr = dev->mc_list;

    for (i = 0; i < dev->mc_count; i++, curr = curr->next) {
            if (!curr) break;       /* unexpected end of list */
            bitnr = greth_hash_get_index(curr->dmi_addr);
            mc_filter[bitnr >> 5] |= 1 << (bitnr & 31);
    }

    GRETH_REGSAVE(regs->hash_msb, mc_filter[1]);
    GRETH_REGSAVE(regs->hash_lsb, mc_filter[0]);
}

static void greth_set_multicast_list(struct net_device *dev) {
        int cfg;
        volatile greth_regs *regs;
        struct greth_private *cep = netdev_priv(dev);
        
        regs = (greth_regs *)dev->base_addr;
        cfg = GRETH_REGLOAD(regs->control);
        if (dev->flags & IFF_PROMISC)               /* enable promiscuous mode */
                cfg |= GRETH_CTRL_PR;
        else                                        /* disable promiscuous mode */
                cfg &= ~GRETH_CTRL_PR;
        
        if (cep->multicast) {                       /* multicast if available */
                if (dev->flags & IFF_ALLMULTI) {        /* set all-multicast */
                        GRETH_REGSAVE(regs->hash_msb, -1);
                        GRETH_REGSAVE(regs->hash_lsb, -1);
                        cfg |= GRETH_CTRL_MCEN;
                        GRETH_REGSAVE(regs->control, cfg);
                        return;
                } 
                
                if (dev->mc_count == 0) {                /* empty multicast list */
                        cfg &= ~GRETH_CTRL_MCEN;
                        GRETH_REGSAVE(regs->control, cfg);
                        return;
                }
                
                /* the multicast list is not empty, setup the filter */ 
                greth_set_hash_filter(dev);
                cfg |= GRETH_CTRL_MCEN;
        }
        GRETH_REGSAVE(regs->control, cfg);
        
}



void greth_wait_jiffies(int jiffie_wait_cnt)
{
	unsigned long timeout = jiffies + jiffie_wait_cnt;
	while( 1 ){
		if ( time_after(jiffies, timeout) ){ \
			return;
		}
	}
}

/* The procedure followed in the this function to init the PHY 
 is not always optimal due to the fact that some PHYs
 do not follow the 802.3 standard with respect to how the speed, duplex,
 auto-neg and reset bits are handled. One example is that the standard requires
 that all registers are set back to their default values after reset while 
 in some PHYs requires that a reset is done when some of the bits are changed
 for the change to have effect */
int greth_phy_init(struct greth_private *cep)
{
        int i;
        int tmp;
        int tmp1;
        int tmp2;
        int done = 0;
        int autoneg_failed = 0;
        int timeout_error = 0, timeout_error_desc = 0;
        int *dbg0;
        int *dbg1;
        volatile greth_regs *regs;
        regs = cep->regs;
        cep->link_up = 0;
        cep->gb = 0;
        cep->fd = 0;
        cep->sp = 0;
        cep->phy_vendor = 0;
        cep->phy_model = 0;
        cep->phy_rev = 0;
        
        /* check that phy address is correct */
        tmp = read_mii(cep->phyaddr, 0, regs);
        if ((tmp > 0) && (tmp < 0xFFFF)) {
                cep->phy_found = 1;
        }
            
        /* phy address was not correct, scan all addresses and try to find one */
        if (!cep->phy_found) {
                i = 0;
                while (i < 32) {
                        /* negative values (read failed),
                           zero and all ones are considered an error*/
                        tmp = read_mii(i, 0, regs);
                        if ((tmp > 0) && (tmp < 0xFFFF)) {
                                cep->phyaddr = i; cep->phy_found = 1;
                                break;
                        }
                }
        }
        
        /* PHY detected find operating mode, otherwise default to 10 MBit half duplex */
        if (cep->phy_found) {
                /* reset PHY and wait for completion. do not do this if greth has edcl since 
                   if running grmon with -u this could cause deadlocks when link is temporarily
                   lost and the uart and print buffers are full. */
                if (cep->edcl == 0) {
                        write_mii_(cep->phyaddr, 0, 0x8000 | tmp, regs, err_timeout, timeout_error=2, timeout_error_desc);
                }
                
                wait_read_mii(0x8000, cep->phyaddr, 0, regs, 4, err_timeout, timeout_error=6, timeout_error_desc);
                
                tmp2 = tmp;
                
                /* Check if extended capabilities are available*/
                read_mii_(tmp, cep->phyaddr, 1, regs, err_timeout, timeout_error=8, timeout_error_desc);

                cep->link_up = tmp & BMSR_LSTATUS;
                cep->auto_neg = tmp &  BMSR_ANEGCAPABLE;
                cep->ext_cap = tmp & BMSR_ERCAP;
                cep->ext_stat = tmp & BMSR_ESTATEN;
                
                /* use default values of ctrl register until auto negotitation has finished, 
                   if aneg is available. Otherwise the values are left at 10-mbit half duplex */
                if (cep->auto_neg) {
                        cep->gb = ((tmp2 >> 6) & 1) && !((tmp2 >> 13) & 1);
                        cep->sp = !((tmp2 >> 6) & 1) && ((tmp2 >> 13) & 1); 
                        cep->fd = (tmp2 >> 8) & 1; 
                }

                /* Check if we use a gigabit phy with a 100 mbit mac. In that
                   case restart auto neg with gigabit disabled. ext_stat is mandatory
                   for gigabit PHYs but not disallowed for other PHYs. It would not 
                   make sense to have it for lower speed PHYs, but if they do
                   the renegotiation here is unnecessary but does not break anything*/
                if ((cep->ext_stat) && (!cep->gbit_mac)) {
                        tmp1 = greth_renegotiate(cep, 0, 0, 1, 1, 1, 1, 1);
                }

                /* Extended capabilities available */
                if (cep->ext_cap) {
                        
                        /* PHY detected. Now detect vendor and model from ext. regs*/
                        read_mii_(tmp1, cep->phyaddr, 2, regs, err_timeout, timeout_error=13, timeout_error_desc);
                        read_mii_(tmp2, cep->phyaddr, 3, regs, err_timeout, timeout_error=14, timeout_error_desc);

                        cep->phy_vendor = (tmp1 << 6) | ((tmp2 >> 10) & 0x3F);
                        cep->phy_rev = tmp2 & 0xF;
                        cep->phy_model = (tmp2 >> 4) & 0x3F;
                        
                        cep->phy_req = 0; cep->phy_model_index = 0;
                        /* Enable phy status interrupts for supported models */
                        if ((tmp1 == MARVELL_88EE1111_reg2) && ((tmp2 & 0xFFF0) == MARVELL_88EE1111_reg3)) {
                                cep->phy_req = 1;
                                write_mii_(cep->phyaddr, 18, 0x6C02, regs, err_timeout, timeout_error=3, timeout_error_desc);
                                cep->phy_model_index = 1;
                        } else if ((tmp1 == INTEL_LXT971A_reg2) && ((tmp2 & 0xFFF0) == INTEL_LXT971A_reg3)) {
                                cep->phy_req = 1;
                                write_mii_(cep->phyaddr, 18, 0xF2, regs, err_timeout, timeout_error=3, timeout_error_desc);
                                cep->phy_model_index = 2;
                        } else if ((tmp1 == NS_DP83848_reg2) && ((tmp2 & 0xFFF0) == NS_DP83848_reg3)) {
                                cep->phy_req = 1;
                                write_mii_(cep->phyaddr, 18, 0x3C, regs, err_timeout, timeout_error=3, timeout_error_desc);
                                cep->phy_model_index = 3;
                        } else if ((tmp1 == NS_DP83865_reg2) && ((tmp2 & 0xFFF0) == NS_DP83865_reg3)) {
                                cep->phy_req = 1;
                                write_mii_(cep->phyaddr, 21, 0xE010, regs, err_timeout, timeout_error=3, timeout_error_desc);
                                cep->phy_model_index = 4;
                        } else if ((tmp1 == VSC_8641_reg2) && ((tmp2 & 0xFFF0) == VSC_8641_reg3)) {
                                cep->phy_req = 1;
                                write_mii_(cep->phyaddr, 25, 0xF400, regs, err_timeout, timeout_error=3, timeout_error_desc);
                                cep->phy_model_index = 5;
                        }

                        if ((!cep->phy_req) || (!cep->mdio_int_en)) {
                                /* if (!cep->phy_req) { */
/*                                         printk("Unknown PHY model detected\n"); */
/*                                         printk("PHY: Vendor %x   Device %x    Revision %d\n", cep->phy_vendor, cep->phy_model, cep->phy_rev); */
/*                                 } */
/*                                 printk("Switching to default initialization\n"); */
                                /* if phy is auto_neg capable then try to finish the auto_neg process, otherwise select 10 Mb hd */
                                if (cep->auto_neg) {
                                        /* wait for auto negotiation to complete and then check operating mode */
                                        while(!done) {
                                                i = 0; done = 1;
                                                while (!( ((tmp=read_mii(cep->phyaddr, 1, regs))>=0) && ((tmp >> 5) & 1) ) ) {
                                                        greth_wait_jiffies(1);
                                                        i++;
                                                        if (i > HZ*2) { /* Wait max 2 seconds */
                                                                autoneg_failed = 1;
                                                                read_mii_(tmp1, cep->phyaddr, 0, regs, err_timeout, timeout_error=8, timeout_error_desc);
                                                                cep->gb = ((tmp1 >> 6) & 1) && !((tmp1 >> 13) & 1);
                                                                cep->sp = !((tmp1 >> 6) & 1) && ((tmp1 >> 13) & 1);
                                                                cep->fd = (tmp1 >> 8) & 1;
                                                                break;
                                                        }
                                                }
                                                if (!autoneg_failed) {
                                                        if ( tmp < 0 ){
                                                                timeout_error = 7;
                                                                timeout_error_desc = tmp;
                                                                goto err_timeout;
                                                        }
                                                        if (0 > greth_aneg_get_mode(cep)) {
                                                                cep->gb = 0;
                                                                cep->sp = 0;
                                                                cep->fd = 0;
                                                        }
                                                        if ((cep->gb == 1) && (cep->gbit_mac == 0)) {
                                                                done = 0;
                                                                greth_renegotiate(cep, 0, 0, 1, 1, 1, 1, 1);
                                                        }
                                                } /* else { */
/*                                                         printk("Auto negotiation timed out. Selecting default config\n");  */
/*                                                 } */
                                        }
                                }
                                
                        } else {
                                GRETH_REGORIN(regs->control, GRETH_CTRL_PSTATIEN);
                                if (cep->auto_neg) {
                                        /* Check if auto-neg is completed */
                                        if (tmp & BMSR_ANEGCOMPLETE) {
                                                /* Is link up? */
                                                if (cep->link_up) {
                                                        /* Fetch the current operating mode, if failed then
                                                           choose 10 mbit hd */
                                                        if (0 > greth_aneg_get_mode(cep)) {
                                                                cep->gb = 0;
                                                                cep->sp = 0;
                                                                cep->fd = 0;
                                                        }
                                                        /* Gigabit mode active for 100Mbit mac? */
                                                        if ((!cep->gbit_mac) && (cep->gb)) {
                                                                greth_renegotiate(cep, 0, 0, 1, 1, 1, 1, 1);
                                                        }
                                                }
                                        }
                                } 
                        }
                        
                }
        }
        /* set speed and duplex bits in control register */
        GRETH_REGORIN(regs->control, (cep->gb << 8) | (cep->sp << 7) | (cep->fd << 4));  
        switch(cep->phy_model_index) {
                case 1:
                        printk("Detected MARVELL 88EE1111 Revision %d \n", tmp2 & 0xF);
                        break;
                case 2:        
                        printk("Detected INTEL LXT971A Revision %d \n", tmp2 & 0xF);
                        break;
                case 3:        
                        printk("Detected National Semiconductor DP83848 Revision %d \n", tmp2 & 0xF);
                        break;
                case 4: 
                        printk("Detected National Semiconductor DP83865 Revision %d \n", tmp2 & 0xF);
                        break;
                case 5:
                        printk("Detected Vitesse VSC8641 Revision %d \n", tmp2 & 0xF);
                        break;
                default:
                        printk("Unknown PHY model detected\n");
                        printk("PHY: Vendor %x   Device %x    Revision %d\n", cep->phy_vendor, cep->phy_model, cep->phy_rev);
        }
        
        return 0;
        

err_timeout:
        return -timeout_error;
}




/* Initialize the GRETH MAC.
 */
struct net_device __init *grlib_greth_probe(int unit, amba_apb_device *adev)
{
        struct net_device *dev;
        struct greth_private *cep;
	volatile greth_regs *regs;
	volatile greth_bd *tx_bd, *rx_bd;
	int i, j, k;
        unsigned long mem_addr;
        int err;
        int tmp;
        int timeout_error;
	char *timeout_error_str[] = {
                /* 0 */ "",
                /* 1 */  "GRETH: Timeout waiting for GRETH core reset\n",
                
                /* 2 */  "GRETH: Timeout waiting for GRETH MII write 1 %d\n",
                /* 3 */  "GRETH: Timeout waiting for GRETH MII write 2 %d\n",
                /* 4 */  "GRETH: Timeout waiting for GRETH MII write 3 %d\n",
                
                /* 5 */  "GRETH: Timeout waiting for GRETH MII read 1 %d\n",
                /* 6 */  "GRETH: Timeout waiting for GRETH MII read 2 %d\n",
                /* 7 */  "GRETH: Timeout waiting for GRETH MII read 3 %d\n",
                /* 8 */  "GRETH: Timeout waiting for GRETH MII read 4 %d\n",
                /* 9 */  "GRETH: Timeout waiting for GRETH MII read 5 %d\n",
                /* 10 */ "GRETH: Timeout waiting for GRETH MII read 6 %d\n",
                /* 11 */ "GRETH: Timeout waiting for GRETH MII read 7 %d\n",
                /* 12 */ "GRETH: Timeout waiting for GRETH MII read 8 %d\n",
                /* 13 */ "GRETH: Timeout waiting for GRETH MII read 9 %d\n",
                /* 14 */ "GRETH: Timeout waiting for GRETH MII read 10 %d\n"
        };

        _FUNCDBG("grlib_greth_probe started\n");

        dev = alloc_etherdev(sizeof(struct greth_private));
        
        if (dev == NULL)
		return ERR_PTR(-ENOMEM);
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24)
	SET_MODULE_OWNER(dev);
#endif
        
        /*i = amba_get_free_apbslv_devices (VENDOR_GAISLER, GAISLER_ETHMAC, adev, 1);
        
	if (i == 0) {
                err = -ENODEV;
                goto err_out_free_dev;
		}*/
	
	printk("Probing GRETH Ethernet Core at 0x%x\n", adev->start);
	
	cep = netdev_priv(dev);
	
	spin_lock_init(&cep->devlock);

        /* Get pointer ethernet controller configuration registers.
	 */
	cep->regs = (greth_regs *)(adev->start);
	regs = (greth_regs *)(adev->start);

	cep->irq = adev->irq;

	/* Reset the controller. */
        GRETH_REGSAVE(regs->control, GRETH_RESET);
        
        /* wait max 1s for GRETH core to reset itself */
	wait_loop( (GRETH_REGLOAD(regs->control) & GRETH_RESET), \
	           1, \
	           err_timeout, \
	           timeout_error=1);
	
        /* Get the phy address which assumed to have been set
           correctly with the reset value in hardware */
        cep->phyaddr = (GRETH_REGLOAD(regs->mdio) >> 11) & 0x1F;
       
        /* Check if mac is gigabit capable */
        tmp = GRETH_REGLOAD(regs->control);
        cep->gbit_mac = (tmp >> 27) & 1;
        
        /* multicast capability */
        cep->multicast = (tmp >> 25) & 1;

        /* edcl */
        cep->edcl = (tmp >> 31) & 1;
        
        /* Check if mac is mdio interrupt capable and has irq line connected */
        cep->mdio_int_en = (tmp >> 26) & 1;
        
        /* Detect PHY and operating mode */
        timeout_error = greth_phy_init(cep);
        
        if (timeout_error < 0) {
                timeout_error = -timeout_error;
                goto err_timeout;
        }
        
        printk("%s GRETH Ethermac at [0x%x] irq %d. Running %d Mbps %s duplex\n", cep->gbit_mac ? "10/100/1000":"10/100", \
                                                                                     (unsigned int)(regs), (unsigned int)(cep->irq), \
	                                                                              cep->gb ? 1000:(cep->sp ? 100:10), cep->fd ? "full":"half");

	/* Initialize TXBD pointer
	 */
	cep->tx_bd_base =  (greth_bd *) __get_free_page(GFP_KERNEL);
	GRETH_REGSAVE(regs->tx_desc_p,(int) __pa(cep->tx_bd_base));
	tx_bd = (volatile greth_bd *)  cep->tx_bd_base;

	/* Initialize RXBD pointer
	 */
	cep->rx_bd_base =  (greth_bd *) __get_free_page(GFP_KERNEL);
	GRETH_REGSAVE(regs->rx_desc_p,(int) __pa(cep->rx_bd_base));
	rx_bd = (volatile greth_bd *)  cep->rx_bd_base;


	/* Initialize pointers.
	 */
	cep->rx_cur = 0;
	cep->tx_next = 0;
	cep->tx_last = 0;
	cep->tx_free = GRETH_TXBD_NUM;

        if (!(cep->gbit_mac)) {
                /* 10/100 MAC must preallocate buffers. Initialize TXBDs. */
                for(i = 0, k = 0; i < GRETH_TX_BUF_PAGE_NUM; i++) {
                        mem_addr = __get_free_page(GFP_KERNEL);
                        for(j = 0; j < GRETH_TX_BUF_PPGAE; j++, k++) {
                                tx_bd[k].stat = 0;
                                tx_bd[k].addr = __pa(mem_addr);
                                mem_addr += GRETH_TX_BUF_SIZE;
                                cep->tx_skbuff[k] = NULL;
                        }
                }
        } else {
                /* 10/100/1000 MAC uses Scatter Gather with any aligment.
                   SKB address pointers passed */
                for(i = 0; i < GRETH_TXBD_NUM; i++) {
                        tx_bd[i].stat = 0;
                        cep->tx_skbuff[i] = NULL;
                }
        }
        
        if(!(cep->gbit_mac)) {
                for(i = 0, k = 0; i < GRETH_RX_BUF_PAGE_NUM; i++) {
                        mem_addr = __get_free_page(GFP_KERNEL);
                        for(j = 0; j < GRETH_RX_BUF_PPGAE; j++, k++) {
                                rx_bd[k].stat = 0;
                                rx_bd[k].addr = __pa(mem_addr);
                                mem_addr += GRETH_RX_BUF_SIZE;
                                cep->rx_skbuff[k] = NULL;
                        }
                }
        } else {
                for(i = 0; i < GRETH_RXBD_NUM; i++) {
                        rx_bd[i].stat = 0;
                        cep->rx_skbuff[i] = NULL;
                }
        }
        
        /* Set default ethernet station address.
	 */
	dev->dev_addr[0] = MACADDR0;
	dev->dev_addr[1] = MACADDR1;
	dev->dev_addr[2] = MACADDR2;
	dev->dev_addr[3] = MACADDR3;
	dev->dev_addr[4] = MACADDR4;
	dev->dev_addr[5] = MACADDR5;

	GRETH_REGSAVE(regs->esa_msb, MACADDR0 << 8 | MACADDR1);
	GRETH_REGSAVE(regs->esa_lsb, MACADDR2 << 24 | MACADDR3 << 16 | MACADDR4 << 8 | MACADDR5);

        if (cep->phy_req)
                INIT_WORK(&cep->greth_wq, (void (*)(void *)) phy_detect_wq);
        
        /* Clear all pending interrupts except PHY irq
	 */
	GRETH_REGSAVE(regs->status, 0xFF);

        dev->base_addr = (unsigned long)adev->start;

	/* The GRETH Ethernet MAC specific entries in the device structure.
	 */
	dev->open = greth_open;
        if (cep->gbit_mac) {
                dev->hard_start_xmit = greth_start_xmit_gbit;
        } else {
                dev->hard_start_xmit = greth_start_xmit;
        }
        dev->stop = greth_close;
	dev->get_stats = greth_get_stats;
        
        if (cep->multicast) {
                dev->set_multicast_list = greth_set_multicast_list;
                dev->flags |= IFF_MULTICAST;
        } else {
                dev->set_multicast_list = NULL;
                dev->flags &= ~IFF_MULTICAST;
        }
        
        dev->set_mac_address = greth_set_mac_add;
        
        if (cep->gbit_mac)
                dev->features = NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_HIGHDMA;
        

	if (register_netdev(dev)) {
                printk(KERN_ERR "greth: netdevice registration failed.\n");
                err = -ENOMEM;
                goto err_out_free_dev;
        }
	
        _FUNCDBG("greth_probe exit\n");
	return dev;

err_timeout:
	err = -EIO;
	printk(timeout_error_str[timeout_error]);

err_out_free_dev:
        free_netdev(dev);
        return ERR_PTR(err);
}

/* ====================================== of driver ====================================== */

static int leon_greth_unit = 0;

static int __devinit of_greth_probe(struct of_device *op, const struct of_device_id *match)
{
	int node;
	amba_apb_device adev;
	unsigned long clk; struct net_device *net;
	struct device_node *dp = op->node; int v = 0, d = 0; unsigned int addr;
	struct uart_leon_port *port; struct amba_prom_registers *regs; int irq, line = leon_greth_unit, *irqs;
	int *vendor = of_get_property(dp, "vendor", NULL);
	int *device = of_get_property(dp, "device", NULL);
	regs = of_get_property(dp, "reg", NULL);
	irqs = of_get_property(dp, "interrupts", NULL);
	if (vendor)
		v = *vendor;
	if (device)
		d = *device;
	
	if (irqs == 0 || regs == 0 || !(v == VENDOR_GAISLER && d == GAISLER_ETHMAC)) {
		return -ENODEV;
	}
	addr = regs->phys_addr ;
	irq = *irqs;
	line = leon_greth_unit ++;
	
	printk("---------------- Match %d: 0x%x@%d : %s ----------------\n",line, addr, irq, dp->path_component_name);

	adev.start = addr;
	adev.irq = irq;
	net = grlib_greth_probe(line, &adev);
	
	return 0;
}

static struct of_device_id __initdata of_greth_match[] = {
	{
		.name = "GAISLER_ETHMAC",
	},
	{},
};

static struct of_platform_driver of_greth_driver = {
	.match_table	= of_greth_match,
	.probe		= of_greth_probe,
	.driver		= {
		.name	= "ambapp-greth",
	},
};

int __init gaisler_greth_init(void) {
	
	of_register_driver(&of_greth_driver, &of_platform_bus_type);
}

void __exit gaisler_greth_exit(void) {
	of_unregister_driver(&of_greth_driver);
}

module_init(gaisler_greth_init);
module_exit(gaisler_greth_exit);
	
/* ====================================== of driver end ====================================== */
