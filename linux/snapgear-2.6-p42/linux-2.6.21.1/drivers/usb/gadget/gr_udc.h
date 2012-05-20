/*
 * Gaisler Research USB Device Controller driver
 *
 * Copyright (C) 2008 Ceton Corporation
 *      by Austin Foxley
 *
 */
#include <asm/leon.h>

#define GAISLER_USBD_REGION_SIZE 1024

/*
 * Control registers on the AMBA bus
 */

#define GR_DESC_OUT_CTRL    0x00
#define GR_DESC_OUT_CTRL_SE (1<<17)
#define GR_DESC_OUT_CTRL_IE (1<<15)
#define GR_DESC_OUT_CTRL_NX (1<<14)
#define GR_DESC_OUT_CTRL_EN (1<<13)
#define GR_DESC_OUT_CTRL_LEN_MASK   0xfff
#define GR_DESC_OUT_ADDR    0x04
#define GR_DESC_OUT_NDP     0x08

#define GR_DESC_IN_CTRL     0x00
#define GR_DESC_IN_CTRL_MO  (1<<18)
#define GR_DESC_IN_CTRL_PI  (1<<17)
#define GR_DESC_IN_CTRL_ML  (1<<16)
#define GR_DESC_IN_CTRL_IE  (1<<15)
#define GR_DESC_IN_CTRL_NX  (1<<14)
#define GR_DESC_IN_CTRL_EN  (1<<13)
#define GR_DESC_IN_CTRL_LEN_MASK    0x1fff
#define GR_DESC_IN_ADDR     0x04
#define GR_DESC_IN_NDP      0x08

#define GR_EP(ep) ((ep)->dev->base + ((ep)->is_in ? 0x100 : 0) + ((ep)->num * 16))

#define GR_EP_CTRL          0x00
#define GR_EP_CTRL_PI       (1<<20)
#define GR_EP_CTRL_CB       (1<<19)
#define GR_EP_CTRL_CS       (1<<18)
#define GR_EP_CTRL_MAXPL_LEN    (10)
#define GR_EP_CTRL_MAXPL_POS    (7)
#define GR_EP_CTRL_NT_LEN       (2)
#define GR_EP_CTRL_NT_POS       (5)
#define GR_EP_CTRL_TT_LEN       (2)
#define GR_EP_CTRL_TT_POS       (3)
#define GR_EP_CTRL_EH       (1<<2)
#define GR_EP_CTRL_ED       (1<<1)
#define GR_EP_CTRL_EV       (1<<0)

#define GR_EP_SLAVECTRL         0x04
#define GR_EP_SLAVECTRL_BUFCNT  (0xfff8)
#define GR_EP_SLAVECTRL_DA      (1<<2)
#define GR_EP_SLAVECTRL_BS      (1<<1)
#define GR_EP_SLAVECTRL_CB      (1<<0)

#define GR_EP_DMACTRL       0x04
#define GR_EP_DMACTRL_AE    (1<<10)
#define GR_EP_DMACTRL_AI    (1<<2)
#define GR_EP_DMACTRL_IE    (1<<1)
#define GR_EP_DMACTRL_DA    (1<<0)

#define GR_EP_SLAVE_DATA    0x08
#define GR_EP_DMAADDR       0x08
#define GR_EP_DMAADDR_MASK  0xfffffffc

#define GR_EP_STATUS        0x0c
#define GR_EP_STATUS_PT     (1<<29)
#define GR_EP_STATUS_PR     (1<<29)
#define GR_EP_STATUS_B1CNT_MSK  0x1FFF0000
#define GR_EP_STATUS_B1CNT_LEN  (13)
#define GR_EP_STATUS_B1CNT_POS  (16)
#define GR_EP_STATUS_B0CNT_MSK  0x0000FFF8
#define GR_EP_STATUS_B0CNT_LEN  (13)
#define GR_EP_STATUS_B0CNT_POS  (3)
#define GR_EP_STATUS_B1     (1<<2)
#define GR_EP_STATUS_B0     (1<<1)
#define GR_EP_STATUS_BS     (1<<0)


#define GR_GLOBAL_CTRL      0x200
#define GR_GLOBAL_CTRL_SI   (1<<31)
#define GR_GLOBAL_CTRL_UI   (1<<30)
#define GR_GLOBAL_CTRL_VI   (1<<29)
#define GR_GLOBAL_CTRL_SP   (1<<28)
#define GR_GLOBAL_CTRL_FI   (1<<27)
#define GR_GLOBAL_CTRL_EP   (1<<14)
#define GR_GLOBAL_CTRL_DH   (1<<13)
#define GR_GLOBAL_CTRL_RW   (1<<12)
#define GR_GLOBAL_CTRL_TS_LEN   (3)
#define GR_GLOBAL_CTRL_TS_POS   (9)
#define GR_GLOBAL_CTRL_TM   (1<<8)
#define GR_GLOBAL_CTRL_UA_LEN   (7)
#define GR_GLOBAL_CTRL_UA_POS   (1)
#define GR_GLOBAL_CTRL_SU   (1<<0)

#define GR_GLOBAL_STATUS    0x204
#define GR_GLOBAL_STATUS_NEPI_LEN (4)
#define GR_GLOBAL_STATUS_NEPI_POS (28)
#define GR_GLOBAL_STATUS_NEPO_LEN (4)
#define GR_GLOBAL_STATUS_NEPO_POS (23)
#define GR_GLOBAL_STATUS_DM   (1<<23)
#define GR_GLOBAL_STATUS_SU (1<<17)
#define GR_GLOBAL_STATUS_UR (1<<16)
#define GR_GLOBAL_STATUS_VB (1<<15)
#define GR_GLOBAL_STATUS_SP (1<<14)
#define GR_GLOBAL_STATUS_AF_LEN (3)
#define GR_GLOBAL_STATUS_AF_POS (11)
#define GR_GLOBAL_STATUS_FN_LEN (10)
#define GR_GLOBAL_STATUS_FN_POS (0)

#define	EP_DEF_PL_SIZE	1024
#define MAX_EP0_SIZE    64

/*-------------------------------------------------------------------------*/

/* DRIVER DATA STRUCTURES and UTILITIES */
typedef struct gr_dma_desc {
    u32 ctrl;
    u32 addr;
    u32 next;

    //THESE MUST BE LAST BECAUSE HW USES PREV THREE
    u32 desc_phys;
    struct gr_dma_desc* desc_next;
} gr_dma_desc_t;

struct gr_ep {
	struct usb_ep ep;
	struct gr_udc* dev;
	int bytes_per_buffer;
        unsigned int dma_start;
        struct gr_dma_desc_t *last_desc;
        
        unsigned num:8,
	         is_in:1,
                 stopped:1;

   
        /* analogous to a host-side qh */
	struct list_head queue;
	const struct usb_endpoint_descriptor* desc;
};

struct gr_request {
	struct usb_request req;
	struct list_head queue;
	unsigned mapped:1;
        gr_dma_desc_t* start_desc;
        gr_dma_desc_t* dma_desc; 
	gr_dma_desc_t* last_desc;
};

enum ep0state {
	EP0_DISCONNECT,		/* no host */
	EP0_IDLE,		/* between STATUS ack and SETUP report */
	EP0_IN, EP0_OUT, 	/* data stage */
	EP0_STATUS,		/* status stage */
	EP0_STALL,		/* data or status stages */
	EP0_SUSPEND,		/* usb suspend */
};

struct gr_udc {
	struct usb_gadget gadget;
	spinlock_t lock;
	struct gr_ep ep[32];
	struct usb_gadget_driver* driver;
        amba_ahb_device *amba_dev;
        struct dma_pool *desc_pool;
   
        enum ep0state ep0state;
	struct gr_request* ep0reqo;
        struct gr_request* ep0reqi;
   
        unsigned got_irq:1,
	         req_config:1,
	         configured:1,
	         enabled:1;

        u8* __iomem base;
        u32 irq;
        u8 vbus_valid;
	u8 irq_enabled;
	u8 address;
        u8 remote_wakeup;
        u8 test_mode;
        
        unsigned int nepi;
        unsigned int nepo;
        unsigned is_mst;
   
};

/*-------------------------------------------------------------------------*/

#define xprintk(level,fmt,args...) \
	printk(level "%s-%s(%i): " fmt "\n", driver_name , __FUNCTION__, __LINE__, ## args)

#define ERROR(fmt,args...) \
	xprintk(KERN_ERR , fmt , ## args)

#define WARNING(fmt,args...) \
	xprintk(KERN_WARNING , fmt , ## args)


#define INFO(fmt,args...) 

/* #define INFO(fmt,args...) \ */
/* 	xprintk(KERN_INFO , fmt , ## args) */


