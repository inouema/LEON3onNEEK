/*
 * Gaisler Research USB Device Controller driver
 *
 * Copyright (C) 2008 Ceton Corporation
 *      by Austin Foxley
 *
 */

/*
 * This driver is for the device-side USB Controller from Gaisler Research
 * It has up to 16 endpoints each configurable to be IN, OUT and CONTROL, BULK,
 * ISOCH, or INTERRUPT.
 *
 * Only DMA is supported for moving data into and out of the core
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/ioport.h>
#include <linux/slab.h>
#include <linux/smp_lock.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/timer.h>
#include <linux/list.h>
#include <linux/interrupt.h>
#include <linux/proc_fs.h>
#include <linux/device.h>
#include <linux/usb/ch9.h>
#include <linux/usb_gadget.h>
#include <linux/dma-mapping.h>
#include <linux/dmapool.h>

#include <asm/byteorder.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <asm/system.h>
#include <asm/unaligned.h>

#include <asm-sparc/leon.h>


#include "gr_udc.h"

#define	DRIVER_DESC		"Gaisler Research USB Device Controller"
#define	DRIVER_VERSION		"20080502"

#define	DMA_ADDR_INVALID	(~(dma_addr_t)0)

#define MAX_USED_DESC           128

#define MIN(a,b) ( (a) < (b) ? (a) : (b) )

/* keeping it simple:
 * - one bus driver, initted first;
 * - one function driver, initted second
 */

static struct gr_udc	*the_controller;

static struct work_struct gr_udc_wq;

static const char driver_name [] = "gr_udc";
static const char driver_desc [] = DRIVER_DESC;

MODULE_AUTHOR("Austin Foxley <austinf@cetoncorp.com>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

//#define gr_read32(x)	(leon_load_reg ((unsigned long)(x)))
//#define gr_write32(x,v) (leon_store_reg ((unsigned long)(x),(unsigned long)(v)))
#define gr_read32_nocache(a)   (LEON_BYPASSCACHE_LOAD_VA(&(a)))

#define gr_read32(x)	(in_be32((x)))
#define gr_write32(x,v) (out_be32((x), (v)))

#define sdump_buffer(buffer, length, name) mod_sdump_buffer( "gr_udc", __FUNCTION__, __LINE__, (buffer), (length), (name))

void mod_sdump_buffer( const char * module_name, const char * function, int line, const uint8_t* buf, uint32_t length, const char* name)
{
	int i, j, i_valid;
	u32 remainder = (length % 16);
	u32 top_len = length + (remainder ? 16 - remainder : 0); 
	u32 char_index;
	u8 c;
	
	if (name) {
		printk("%s:%i DUMP: \"%s\" (%p) length %d\n", function, line, name, buf, length);
	} else {
		printk("%s:%i DUMP: (%p) length %d\n", function, line, buf, length);
	}
	
	printk("%08d  ", 0);
    
	for(i=0; i<top_len; i++) {
		
		i_valid = (i < length);
		
		if (i_valid) {
			printk("%02x ", buf[i]);
		} else {
			printk("   ");
		}
		
		if(i % 16 == 15 && i != 0) {
			printk("  |");
			j = 0;
			for(j=0; j<16; j++) {
				char_index = i - 15 + j;
				if (char_index < length) {
					c = buf[char_index];
					printk("%c", (c >= '0' && c <= 'z') ? c : '.');
				} else {
					printk("%c", ' ');
				}
			}
            if (i == top_len - 1) {
                printk("|");
            } else {
                printk("|\n%08d  ", i+1);
            }
            
		} else if (i % 8 == 7) {
			printk(" ");
		}
		
		
	}
	printk( "\n");
}

/*-------------------------------------------------------------------------*/

static void 
ep0_dummy_complete(struct usb_ep* _ep, struct usb_request* _req);

static void 
gr_ep_nuke(struct gr_ep *, int status);

static struct usb_request *
gr_alloc_request(struct usb_ep *_ep, gfp_t gfp_flags);

static void
gr_free_request(struct usb_ep *_ep, struct usb_request *_req);

static int
gr_queue(struct usb_ep *_ep, struct usb_request *_req, gfp_t gfp_flags);


/* return size of hardware buffer for endpoint ep*/
static int gr_ep_buffer_size(struct gr_ep* ep) {
        
	return ((gr_read32( GR_EP( ep ) + GR_EP_CTRL ) >> 21) & 0x7FF)*8;
}

static u8 bw_buffer[1024];
ktime_t start_time;
ktime_t end_time;
int iterations = 0;

#define GR_BANDWIDTH_ITERATIONS 385024

static void
bandwidth_complete(struct usb_ep* _ep, struct usb_request* _req)
{
	int status;

	if(_req->status != -ESHUTDOWN) {

		if(iterations < GR_BANDWIDTH_ITERATIONS) {

			iterations++;
			status = gr_queue(_ep, _req, GFP_ATOMIC);

			if( status < 0 ) {
				ERROR("error gr_queue'ing bw_req status=%d", status);
				gr_free_request(_ep, _req);
			}
		} else {
			uint64_t startns;
			uint64_t endns;
			uint64_t diff_time;
			uint64_t len;
			uint64_t bw=0;

			end_time = timespec_to_ktime(CURRENT_TIME);
			//math
			
			startns = ktime_to_ns(start_time);
			endns = ktime_to_ns(end_time);
			diff_time = endns-startns;

			len = iterations*1024;

			if(diff_time != 0)
				bw = ((len*8*1000000000)/(diff_time*1024*1024));
			else
				ERROR("diff_time == 0");

			//print
			INFO("Sent %d MB in %lld nsec resulting in a bandwidth of %lld Mbps",
					((uint32_t)(len/1024/1024)),
					diff_time,
					bw);
			gr_free_request(_ep, _req);
		}
	} else {
		gr_free_request(_ep, _req);
	}
}

static void
start_bandwidth_test(struct gr_udc* dev, struct gr_ep* ep)
{
	struct gr_request* bw_req = NULL;
	struct usb_request* _bw_req = NULL;
	int status;

	_bw_req = gr_alloc_request(&ep->ep, GFP_KERNEL);
	if(!_bw_req) {
		ERROR("error allocing bw_req");
		return;
	}

	iterations = 0;

	bw_req = container_of(_bw_req, struct gr_request, req);
	bw_req->req.complete = bandwidth_complete;
	bw_req->req.buf = bw_buffer;
	bw_req->req.length = 1024;

	start_time = timespec_to_ktime(CURRENT_TIME);
	status = gr_queue(&ep->ep, _bw_req, GFP_ATOMIC);

        if( status < 0 ) {
                ERROR("error gr_queue'ing bw_req status=%d", status);
		return;
        }
}

static int
gr_ep_enable(struct usb_ep *_ep, const struct usb_endpoint_descriptor *desc)
{
	struct gr_udc* dev;
	struct gr_ep* ep;
        u32 type;
        u8 mode;
        u8 nt;
        u16 max;
	u16 buffer_size = 0;
        u32 ctrl_val;
        u8 dir;
        unsigned long flags;

	ep = container_of(_ep, struct gr_ep, ep);
	if (!_ep || !desc || ep->desc
			|| desc->bDescriptorType != USB_DT_ENDPOINT) {
		return -EINVAL;
        }

	dev = ep->dev;

        //'ep0' IN and OUT are reserved
	if (ep == &dev->ep[0] || ep == &dev->ep[dev->nepo]) {
		return -EINVAL;
        }

	if (!dev->driver || dev->gadget.speed == USB_SPEED_UNKNOWN) {
		return -ESHUTDOWN;
        }

        //make sure we are clear for enabling
        if( gr_read32( GR_EP( ep ) + GR_EP_CTRL ) & GR_EP_CTRL_EV ) {
                return -EBUSY;
        }
        
        if( !ep->stopped ) {
                return -EBUSY;
        }
 
        dir = (USB_DIR_IN & desc->bEndpointAddress) != 0;

        if (ep->is_in != dir) {
                return -EINVAL;
        }

        //check OUT ep num 
        if( !ep->is_in && ( ep->num < 0 || ep->num >= dev->nepo) ) {
                return -EINVAL;
        }

        //check IN ep num
        if( ep->is_in && ( ep->num < 0 || ep->num >= dev->nepi) ) {
                return -EINVAL;
        }

    
        type = desc->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK;

        switch( type ) {
        case USB_ENDPOINT_XFER_CONTROL:    
            mode = 0;
            break;    
        case USB_ENDPOINT_XFER_ISOC:
            mode = 1;
            break;
        case USB_ENDPOINT_XFER_BULK:
            mode = 2;
            break;
        case USB_ENDPOINT_XFER_INT:
            mode = 3;
            break;
        default:
            WARNING("unknown xfer type");
            return -EINVAL;
        }

        /* bits 10-0 set the max payload. 12-11 set the number of 
           additional transactions */
        max = 0x7FF & le16_to_cpu( get_unaligned( &desc->wMaxPacketSize ) );
        nt = 0x3 & (le16_to_cpu( get_unaligned( &desc->wMaxPacketSize ) ) >> 11);
	buffer_size = gr_ep_buffer_size(ep);
	if(max > buffer_size) {
		ERROR("tried to set max payload size to %d which is greater than HW supports (%d)", max, buffer_size);
		return -EINVAL;

	}

	//cannot have max payload size 0 and we explicitly check this to avoid
	//divide by zero in bytes_per_buffer calculation
	if(max == 0) {
		ERROR("tried to set max payload size to 0");
		return -EINVAL;
	}
    
        spin_lock_irqsave( &ep->dev->lock, flags );

        ep->stopped = 0;
        ep->desc = desc;
        ep->ep.maxpacket = max;
        ep->dma_start = 0;
        
        //The biggest multiple of max that fits into the buffer
	ep->bytes_per_buffer = ((int)(buffer_size / max))*max;
        
        ctrl_val = ( max << GR_EP_CTRL_MAXPL_POS ) 
                | ( nt << GR_EP_CTRL_NT_POS ) 
                | ( mode << GR_EP_CTRL_TT_POS ) 
                | GR_EP_CTRL_EV;
        gr_write32( GR_EP( ep ) + GR_EP_CTRL, ctrl_val );
        
        gr_write32( GR_EP( ep ) + GR_EP_DMACTRL, GR_EP_DMACTRL_IE | GR_EP_DMACTRL_AI );
        
        spin_unlock_irqrestore( &ep->dev->lock, flags );

//	if(ep->num == 1 && ep->is_in) {
//		start_bandwidth_test(dev, ep);
//	}

	INFO("%s enabled", ep->ep.name);
	return 0;
}

static void gr_ep_reset(struct gr_ep *ep)
{
        //reset the hardware state of this endpoint
        gr_write32( GR_EP( ep ) + GR_EP_CTRL, 0);
        //DMACTRL at same address as SLAVECTRL register
        //so the same write can be used for both configs
        gr_write32( GR_EP( ep ) + GR_EP_DMACTRL, 0 );
        
	ep->ep.maxpacket = EP_DEF_PL_SIZE;
	ep->desc = NULL;
	ep->stopped = 1;
}

static int gr_ep_disable(struct usb_ep *_ep)
{
	struct gr_ep	*ep;
	struct gr_udc	*dev;
	unsigned long	flags;

	ep = container_of(_ep, struct gr_ep, ep);
	if (!_ep || !ep->desc)
		return -ENODEV;
	dev = ep->dev;
	if (dev->ep0state == EP0_SUSPEND)
		return -EBUSY;

        // kill all pending requests for this endpoint
        // reset the hardware state of this endpoint
	INFO("disable %s", _ep->name);

	spin_lock_irqsave(&dev->lock, flags);
	gr_ep_nuke(ep, -ESHUTDOWN);
	gr_ep_reset(ep);
	spin_unlock_irqrestore(&dev->lock, flags);

	return 0;
}

/*-------------------------------------------------------------------------*/

static struct usb_request *
gr_alloc_request(struct usb_ep *_ep, gfp_t gfp_flags)
{
	struct gr_request	*req;

	if (!_ep)
		return NULL;
	req = kzalloc(sizeof *req, gfp_flags);
	if (!req)
		return NULL;

	req->req.dma = DMA_ADDR_INVALID;
	INIT_LIST_HEAD(&req->queue);
	return &req->req;
}

static void
gr_free_request(struct usb_ep *_ep, struct usb_request *_req)
{
	struct gr_request	*req;

	if (!_ep || !_req)
		return;

	req = container_of(_req, struct gr_request, req);
	WARN_ON(!list_empty(&req->queue));
        kfree(req);
}

/*-------------------------------------------------------------------------*/

/* allocating buffers this way eliminates dma mapping overhead, which
 * on some platforms will mean eliminating a per-io buffer copy.  with
 * some kinds of system caches, further tweaks may still be needed.
 */
static void *
gr_alloc_buffer(struct usb_ep *_ep, unsigned bytes,
			dma_addr_t *dma, gfp_t gfp_flags)
{
	void		*retval;
	struct gr_ep	*ep;
        
        ep = container_of(_ep, struct gr_ep, ep);
	if (!_ep)
		return NULL;
	*dma = DMA_ADDR_INVALID;
        
        retval = dma_alloc_coherent( &ep->dev->gadget.dev, bytes, dma, gfp_flags );
    
	return retval;
}

static void
gr_free_buffer(struct usb_ep *_ep, void *buf, dma_addr_t dma, unsigned bytes)
{
        if (dma != DMA_ADDR_INVALID) {
		struct gr_ep	*ep;

		ep = container_of(_ep, struct gr_ep, ep);
		if (!_ep)
			return;
		
                dma_free_coherent( &ep->dev->gadget.dev, bytes, buf, dma );
	}
}

static gr_dma_desc_t* 
gr_setup_dma_desc( struct gr_ep* ep, dma_addr_t addr, unsigned size, gr_dma_desc_t* next)
{
        dma_addr_t paddr;
        
        gr_dma_desc_t* dma_desc = (gr_dma_desc_t *)dma_pool_alloc( ep->dev->desc_pool, GFP_KERNEL, &paddr);
        if (!dma_desc) {
                ERROR("Error allocating dma_pool\n");
                return -ENOMEM;
        }

        dma_desc->desc_phys = paddr;
        
        dma_desc->addr = addr;
        dma_desc->next = 0;
        dma_desc->desc_next = NULL;
        if (ep->is_in) {
                dma_desc->next = next->desc_phys;
                dma_desc->desc_next = next;
        }
        
        if( ep->is_in ) {
                dma_desc->ctrl = GR_DESC_IN_CTRL_IE 
                        | GR_DESC_IN_CTRL_EN  | GR_DESC_IN_CTRL_NX
                        | ( GR_DESC_IN_CTRL_LEN_MASK & size );
        } else {
                /* Length field will be set by usb core when packet has
                   been received*/    
                dma_desc->ctrl = GR_DESC_OUT_CTRL_IE
                        | GR_DESC_OUT_CTRL_EN;
        }
        
        return dma_desc;
}

static gr_dma_desc_t* 
gr_set_dma_desc( struct gr_ep* ep, dma_addr_t addr, unsigned size, gr_dma_desc_t* next)
{
        gr_dma_desc_t* dma_desc;
        
        dma_desc = ep->last_desc;
        dma_desc->addr = addr;
        dma_desc->next = next->desc_phys;
        dma_desc->desc_next = next;
        if (ep->is_in) {
                dma_desc->ctrl = GR_DESC_IN_CTRL_IE 
                        | GR_DESC_IN_CTRL_EN | GR_DESC_IN_CTRL_NX
                        | ( GR_DESC_IN_CTRL_LEN_MASK & size );
        } else {
                /* Length field will be set by usb core when packet has
                   been received*/    
                dma_desc->ctrl = GR_DESC_OUT_CTRL_IE
                        | GR_DESC_OUT_CTRL_EN;
        }
        return dma_desc;
}

static gr_dma_desc_t* 
gr_alloc_dma_desc( struct gr_ep* ep )
{
        dma_addr_t paddr;
        gr_dma_desc_t* dma_desc = (gr_dma_desc_t *)dma_pool_alloc( ep->dev->desc_pool, GFP_KERNEL, &paddr);

        if (!dma_desc) {
                ERROR("Error allocating dma_pool\n");
                return -ENOMEM;
        }
        
        dma_desc->desc_phys = paddr;
        dma_desc->addr = 0;
        dma_desc->ctrl = 0;
        dma_desc->next = 0;
        dma_desc->desc_next = NULL;
        
        return dma_desc;
}


static gr_dma_desc_t* 
gr_cleanup_dma_desc( gr_dma_desc_t* desc, struct gr_udc* dev)
{
        gr_dma_desc_t* next = desc->desc_next;
        dma_pool_free(dev->desc_pool, desc, (dma_addr_t)desc->desc_phys);
        return next;
}

static void
gr_finish_request(struct gr_ep *ep, struct gr_request *req, int status)
{
	struct gr_udc* dev;
        struct list_head *pos;
        unsigned stopped = ep->stopped;
        gr_dma_desc_t* dma_desc = NULL;
        gr_dma_desc_t* dma_desc_prev = NULL;
        int i;

	list_del_init( &req->queue );

        ep->dma_start = 0;
        
        if( likely( req->req.status == -EINPROGRESS ) )
		req->req.status = status;
	else
		status = req->req.status;

	dev = ep->dev;
	if( req->mapped ) {
		dma_unmap_single(NULL, req->req.dma, req->req.length,
			ep->is_in ? DMA_TO_DEVICE : DMA_FROM_DEVICE);
		req->req.dma = DMA_ADDR_INVALID;
		req->mapped = 0;
	}

	dma_desc = req->start_desc;
   	//cleanup descriptor list
        while(dma_desc) {

		if(!ep->is_in) {
			req->req.actual += dma_desc->ctrl & GR_DESC_OUT_CTRL_LEN_MASK;
		}
                dma_desc_prev = dma_desc;
                dma_desc = gr_cleanup_dma_desc( dma_desc, dev );
                if (dma_desc_prev == req->last_desc)
                        break;
        }
        
        if (ep->is_in) {
                req->req.actual = req->req.length;
        }
        
        req->dma_desc = NULL;
	req->last_desc = NULL;

        if( ep->is_in ) {

		//unmap frag list
                for(i=0; i<req->req.nr_frags; i++) {
                    
                        usb_request_frag_t* frag = &req->req.frags[i];
                        dma_unmap_page( NULL, frag->dma, frag->size, DMA_TO_DEVICE );
                }
        } else {
            
		//sdump_buffer(req->req.buf, req->req.actual, "received");
	}
//	if(ep->num > 0) {
//		INFO("complete %s req %p stat %d len %u/%u",
//			ep->ep.name, &req->req, status,
//	        req->req.actual, req->req.length);
//	}


        if( req->req.complete ) {
                /* don't modify queue heads during completion callback */
                //ep->stopped = 1; //TODO: what if the callback wants to stop the endpoint? this will overwrite it when it returns
                spin_unlock(&dev->lock);
                req->req.complete(&ep->ep, &req->req);
                spin_lock(&dev->lock);
                //ep->stopped = stopped;
        }

}

/*-------------------------------------------------------------------------*/
static int 
gr_start_dma(struct gr_ep *ep, struct gr_request *req)
{
        u32 cur_dmactrl;
    
        if( !req->dma_desc ) {
		/* A descriptor should already have been allocated*/
		return -ENOMEM;
        }

        //set the desc ptr in the hardware
        if (!ep->is_in)
                gr_write32( GR_EP( ep ) + GR_EP_DMAADDR, (u32)req->dma_desc->desc_phys  );

        cur_dmactrl = gr_read32( GR_EP( ep ) + GR_EP_DMACTRL );
        gr_write32( GR_EP( ep ) + GR_EP_DMACTRL, cur_dmactrl | GR_EP_DMACTRL_DA );

        ep->dma_start = 1;
        
        return 0;
}

static void gr_dma_advance(struct gr_udc *dev, struct gr_ep *ep)
{
	struct gr_request		*req;
        struct list_head                *pos;

        req = list_entry(ep->queue.next, struct gr_request, queue);

	INFO("done %s %s dma, %u/%u bytes, req %p",
             ep->ep.name, ep->is_in ? "IN" : "OUT",
		req->req.actual, req->req.length, req);

        gr_finish_request( ep, req, 0 );


        if (!ep->dma_start && !list_empty( &ep->queue)) {
                req = list_entry(ep->queue.next, struct gr_request, queue);
                gr_start_dma(ep, req);
	}
}


/* Abort DMA for an endpoint. Sets the abort DMA bit which causes an
   ongoing DMA transfer to be cancelled */
static void gr_abort_dma(struct gr_ep* ep, int status)
{
        u32 cur_dmactrl;
        cur_dmactrl = gr_read32( GR_EP( ep ) + GR_EP_DMACTRL );
        gr_write32( GR_EP( ep ) + GR_EP_DMACTRL, cur_dmactrl & ~GR_EP_DMACTRL_DA  );
}

static int
gr_setup_out_desc_list(struct gr_ep* ep, struct gr_request* req)
{
	int bytes_left;
	int bytes_used;
	int bytes_for_desc;
        gr_dma_desc_t* dma_desc;
        struct gr_udc *dev;
        dev = ep->dev;
        
        bytes_left = req->req.length;
	bytes_used = 0;

	bytes_for_desc = MIN(bytes_left, ep->ep.maxpacket);
        req->dma_desc = gr_setup_dma_desc( ep, req->req.dma, bytes_for_desc, NULL );
	req->last_desc = req->dma_desc;
        req->start_desc = req->dma_desc;
        bytes_left -= bytes_for_desc;
	bytes_used += bytes_for_desc;

        while(bytes_left > 0) {

		bytes_for_desc = MIN(bytes_left, ep->ep.maxpacket);
		dma_desc = gr_setup_dma_desc( ep, req->req.dma + bytes_used, bytes_for_desc, NULL );
		bytes_left -= bytes_for_desc;
		bytes_used += bytes_for_desc;
                
                req->last_desc->desc_next = dma_desc;
		req->last_desc->next = (u32)dma_desc->desc_phys;
                
                req->last_desc->ctrl |= GR_DESC_IN_CTRL_NX;
                
                //we setup the descriptor list for the whole buffer but don't
		//enable them until we decide they should be used, which happens
		//in the interrupt handler when the len recieved == maxpacket. We
		//setup the entire buffer descriptor list now instead of as we go
		//to avoid setting up descriptor lists in the interrupt handler.
		dma_desc->ctrl &= ~GR_DESC_OUT_CTRL_EN;

                req->last_desc = dma_desc;
        }
        
        //we need to add an extra 0 length descriptor on the end for the OUT
	//direction in case the received size is EXACTLY the length of all our
	//descriptors put together. This is used to tell us when the end of a
	//tranfer happens in that case
	//TODO: figure out how to actually do this?
//	dma_desc = gr_setup_dma_desc( ep, 0, 0 );
//	req->last_desc->desc_next = dma_desc;
//	req->last_desc->next = (u32)dma_desc->desc_phys;
//	req->last_desc->ctrl |= GR_DESC_IN_CTRL_NX;
//	dma_desc->ctrl &= ~GR_DESC_OUT_CTRL_EN;

	//the list is setup but we want the IRQ to check the descriptors as
	//the interrupts happen and it will move the last_desc ptr forward as
	//it needs to
	/* req->last_desc = req->dma_desc; */
/*         printk("dd: %x, ld: %x\n", req->dma_desc, req->last_desc); */
        
}

static int
gr_setup_in_desc_list(struct gr_ep* ep, struct gr_request* req)
{
	int bytes_left;
	int bytes_left_hw;
	int bytes_used;
	int bytes_for_desc;
        gr_dma_desc_t* dma_desc;
        int i;
        struct gr_udc *dev;
        dev = ep->dev;

	bytes_left_hw = ep->bytes_per_buffer;

	bytes_left = req->req.length;
	bytes_used = 0;
        
        dma_desc = gr_alloc_dma_desc( ep );
        bytes_for_desc = MIN(bytes_left, bytes_left_hw);
        if (ep->last_desc) {
                req->dma_desc = gr_set_dma_desc( ep, req->req.dma, bytes_for_desc, dma_desc );
        } else {
                req->dma_desc = gr_setup_dma_desc( ep, req->req.dma, bytes_for_desc, dma_desc );
                gr_write32( GR_EP( ep ) + GR_EP_DMAADDR, (u32)req->dma_desc->desc_phys  );
        }

        req->last_desc = req->dma_desc;
        req->start_desc = req->dma_desc;
	bytes_left -= bytes_for_desc;
	bytes_used += bytes_for_desc;
	bytes_left_hw -= bytes_for_desc;

        
        ep->last_desc = dma_desc;
        
        //if buffer can take more and there is more to give
	if(bytes_left_hw && (bytes_left || req->req.nr_frags > 0)) {
		req->last_desc->ctrl |= GR_DESC_IN_CTRL_MO;
	} else {
		bytes_left_hw = ep->bytes_per_buffer;
	}

	while(bytes_left > 0) {

                dma_desc = gr_alloc_dma_desc( ep );
		bytes_for_desc = MIN(bytes_left, bytes_left_hw);

                //for IN packets we only want to be told when its done on the last
		//packet. For OUT packets we want to be told every packet so we can
		//find out when the transfer is finished (len < maxpacket)
		req->last_desc->ctrl &= ~GR_DESC_IN_CTRL_IE;

                req->last_desc = gr_set_dma_desc( ep, req->req.dma + bytes_used, bytes_for_desc, dma_desc );

		bytes_left -= bytes_for_desc;
		bytes_used += bytes_for_desc;
		bytes_left_hw -= bytes_for_desc;

                //if buffer can take more and there is more to give
		if(bytes_left_hw && (bytes_left || req->req.nr_frags > 0)) {
			req->last_desc->ctrl |= GR_DESC_IN_CTRL_MO;
		} else {
			bytes_left_hw = ep->bytes_per_buffer;
		}
                ep->last_desc = dma_desc;
	}

	for(i=0; i<req->req.nr_frags; i++) {

		usb_request_frag_t* frag = &req->req.frags[i];

		frag->dma = dma_map_page( NULL, frag->page, frag->page_offset, frag->size, DMA_TO_DEVICE );

		bytes_left = frag->size;
		bytes_used = 0;
		while(bytes_left > 0) {

			bytes_for_desc = MIN(bytes_left, bytes_left_hw);

			dma_desc = gr_setup_dma_desc( ep, frag->dma + bytes_used, bytes_for_desc, dma_desc );
			bytes_left -= bytes_for_desc;
			bytes_used += bytes_for_desc;
			bytes_left_hw -= bytes_for_desc;

			req->last_desc->desc_next = dma_desc;
			req->last_desc->next = (u32)dma_desc->desc_phys;
			req->last_desc->ctrl &= ~GR_DESC_IN_CTRL_IE;
			req->last_desc->ctrl |= GR_DESC_IN_CTRL_NX;

			req->last_desc = dma_desc;

			//if buffer can take more and there is more to give
			if(bytes_left_hw && (bytes_left || req->req.nr_frags > (i+1))) {
				req->last_desc->ctrl |= GR_DESC_IN_CTRL_MO;
			} else {
				bytes_left_hw = ep->bytes_per_buffer;
			}
		}
	}

	if(req->req.zero && !(req->req.length % ep->ep.maxpacket)) {
                //Add an extra zero length packet
                dma_desc = gr_alloc_dma_desc( ep );
                req->last_desc->ctrl &= ~GR_DESC_IN_CTRL_IE;
                req->last_desc = gr_set_dma_desc( ep, 0, 0, dma_desc );
                ep->last_desc = dma_desc;
        }
        
}


static int
gr_queue(struct usb_ep *_ep, struct usb_request *_req, gfp_t gfp_flags)
{
	struct gr_request	*req;
	struct gr_ep		*ep;
        struct gr_udc		*dev;
	unsigned long		flags;
	int			status;
        struct list_head        *pos;

        req = container_of(_req, struct gr_request, req);
	if (unlikely(!_req || !_req->complete
			|| !_req->buf || !list_empty(&req->queue))) {
                if(_req) {
			INFO("req->complete %p req->buf %p list_empty %d", _req->complete, _req->buf, list_empty(&req->queue));
		} else {
			INFO("_req == NULL");
		}
                return -EINVAL;
	}

	ep = container_of(_ep, struct gr_ep, ep);

        dev = ep->dev;

        /* if a data stage is present in the out direction for a control
           transfer then the endpoint must be changed since the gadget only
           allows for one endpoint being used for the ep0 setup function, and
           it is the IN0 endpoint per default for the gr_udc*/

        if ((ep->num == 0) && (dev->ep0state == EP0_OUT) && ep->is_in) 
                ep = (struct gr_ep *)&dev->ep[0];
              
        if (unlikely(!_ep || (!ep->desc && ep->num != 0))) {
		if(_ep) {
			INFO("ep->desc %p ep->num %d", ep->desc, ep->num);
		} else {
			INFO("_ep == NULL");
		}
		return -EINVAL;
	}

	if (unlikely(!dev->driver || dev->gadget.speed == USB_SPEED_UNKNOWN)) {
		return -ESHUTDOWN;
	}

	/* can't touch registers when suspended */
	if (dev->ep0state == EP0_SUSPEND) {
		return -EBUSY;
	}
    
        /* set up dma mapping in case the caller didn't */
        if (_req->dma == DMA_ADDR_INVALID) {
             _req->dma = dma_map_single( NULL, _req->buf, _req->length,
             ep->is_in ? DMA_TO_DEVICE : DMA_FROM_DEVICE);
             req->mapped = 1;
        }
        
    
        
        if(ep->is_in) {
                gr_setup_in_desc_list(ep, req);
        } else {
                gr_setup_out_desc_list(ep, req);
        }
        
        spin_lock_irqsave(&dev->lock, flags);

	_req->status = -EINPROGRESS;
	_req->actual = 0;

        // setup and start start dma
	status = 0;
        
        if (!ep->dma_start && likely(!ep->stopped)) {        
		/* 
                 * dma:  done after dma completion IRQ (or error)
		 */
                status = gr_start_dma(ep, req);
                
		if (unlikely(status != 0)) {
			if (status > 0)
				status = 0;
			req = NULL;
		}
        } /* else dma irq handler advances the queue. */
        
        if (likely(req != 0))
		list_add_tail(&req->queue, &ep->queue);

        spin_unlock_irqrestore(&dev->lock, flags); 

	return status;
}

/* dequeue ALL requests */
static void gr_ep_nuke(struct gr_ep *ep, int status)
{
        unsigned long           flags;
	struct gr_request	*req;
        struct gr_udc		*dev;

        dev = ep->dev;

        spin_lock_irqsave(&dev->lock, flags);
	ep->stopped = 1;

        if (ep->last_desc) {
                gr_cleanup_dma_desc( ep->last_desc, dev );
                ep->last_desc = NULL;
        }

        gr_abort_dma( ep, status );

        if (list_empty(&ep->queue))
		return;
   
        while (!list_empty(&ep->queue)) {
		req = list_entry(ep->queue.next, struct gr_request, queue);
                gr_finish_request( ep, req, status );
	}
        
        spin_unlock_irqrestore(&dev->lock, flags);
}

/* dequeue JUST ONE request */
static int gr_dequeue(struct usb_ep *_ep, struct usb_request *_req)
{
	struct gr_request	*req;
	struct gr_ep		*ep;
	struct gr_udc		*dev;
	unsigned long		flags;

	ep = container_of(_ep, struct gr_ep, ep);
	if (!_ep || !_req || (!ep->desc && ep->num != 0))
		return -EINVAL;
	dev = ep->dev;
	if (!dev->driver)
		return -ESHUTDOWN;

	/* we can't touch (dma) registers when suspended */
	if (dev->ep0state == EP0_SUSPEND)
		return -EBUSY;

	INFO("%s %s %s %p", __FUNCTION__, _ep->name,
		ep->is_in ? "IN" : "OUT",
		_req);

	spin_lock_irqsave(&dev->lock, flags);

	/* make sure it's actually queued on this endpoint */
	list_for_each_entry (req, &ep->queue, queue) {
		if (&req->req == _req)
			break;
	}
	if (&req->req != _req) {
		spin_unlock_irqrestore (&dev->lock, flags);
		return -EINVAL;
	}

        // this request is currently being processed
        if( ep->queue.next == &req->queue && !ep->stopped ) {
                gr_abort_dma( ep, -ECONNRESET );
                //gr_finish_request( ep, req, -ECONNRESET );
                gr_dma_advance( dev, ep ); 
        } else if( !list_empty( &req->queue ) ) {
                //gr_finish_request( ep, req, -ECONNRESET );
                gr_dma_advance( dev, ep );
        } else {
                req = NULL;
        }

	spin_unlock_irqrestore(&dev->lock, flags);

	return req ? 0 : -EOPNOTSUPP;
}

/*-------------------------------------------------------------------------*/

static void gr_clear_halt(struct gr_ep *ep)
{
        u32 cur_ctrl;
	INFO("%s clear halt", ep->ep.name); 

        cur_ctrl = gr_read32( GR_EP( ep ) + GR_EP_CTRL );
        
        cur_ctrl &= ~GR_EP_CTRL_EH;
        gr_write32( GR_EP( ep ) + GR_EP_CTRL, cur_ctrl );
        
	if (ep->stopped) {
                struct gr_request	*req;
                ep->stopped = 0;

                if (list_empty(&ep->queue))
                        return;
                req = list_entry(ep->queue.next, struct gr_request,
                                 queue);
                /* gr_start_dma( ep, req ); */
        }
}

static int gr_set_halt(struct usb_ep *_ep, int value)
{
	struct gr_ep	*ep;
	unsigned long	flags;
	int		retval = 0;

        if (!_ep)
		return -ENODEV;
	ep = container_of (_ep, struct gr_ep, ep);

        if (ep->num == 0) {
		if (value) {
			ep->dev->ep0state = EP0_STALL;
			ep->dev->ep[0].stopped = 1;
		} else
			return -EINVAL;

	/* don't change EPxSTATUS_EP_INVALID to READY */
	} else if (!ep->desc) {
		WARNING("%s %s inactive?", __FUNCTION__, ep->ep.name);
		return -EINVAL;
	}

        /* gr_ep_nuke(ep, -ESHUTDOWN); */
        
        spin_lock_irqsave(&ep->dev->lock, flags);
	
        
        /* if (!list_empty(&ep->queue)) { */
/*                 retval = -EAGAIN; */
/*         } else  */
        if (!value) {
                gr_clear_halt( ep );
        } else {
                u32 cur_ctrl;
		ep->stopped = 1;
		INFO("%s set halt", ep->ep.name);

                cur_ctrl = gr_read32( GR_EP( ep ) + GR_EP_CTRL );
                // clear pending IN buffers and set HALT
                cur_ctrl |= GR_EP_CTRL_CB | GR_EP_CTRL_EH;
                gr_write32( GR_EP( ep ) + GR_EP_CTRL, cur_ctrl );
        }
	
        spin_unlock_irqrestore(&ep->dev->lock, flags);
	return retval;
}


/* Return the total number of bytes currently stored in the
   internal buffers of the endpoint */
static int gr_fifo_status(struct usb_ep *_ep)
{
	struct gr_ep			*ep;
	u32				status;
        u32                             bytes = 0;
        
        if (!_ep)
		return -ENODEV;
	ep = container_of(_ep, struct gr_ep, ep);

        status = gr_read32( GR_EP( ep ) + GR_EP_STATUS );
        
        if (status & GR_EP_STATUS_B0)
                bytes += ((status & GR_EP_STATUS_B0CNT_MSK) >> GR_EP_STATUS_B0CNT_POS);
        if (status & GR_EP_STATUS_B1)
                bytes += ((status & GR_EP_STATUS_B1CNT_MSK) >> GR_EP_STATUS_B1CNT_POS);

        return bytes;
}


/* Empty data from internal buffers of an endpoint.  */
static void gr_fifo_flush(struct usb_ep *_ep)
{

        struct gr_ep			*ep;
	u32				cur_ctrl;

	if (!_ep)
		return;
	ep = container_of(_ep, struct gr_ep, ep);
	INFO("%s %s", __FUNCTION__, ep->ep.name);

        cur_ctrl = gr_read32( GR_EP( ep ) + GR_EP_CTRL );
        cur_ctrl |= GR_EP_CTRL_CB;
        gr_write32( GR_EP( ep ) + GR_EP_CTRL, cur_ctrl );
}

static struct usb_ep_ops gr_ep_ops = {
	.enable		= gr_ep_enable,
	.disable	= gr_ep_disable,

	.alloc_request	= gr_alloc_request,
	.free_request	= gr_free_request,

	.alloc_buffer	= gr_alloc_buffer,
	.free_buffer	= gr_free_buffer,

	.queue		= gr_queue,
	.dequeue	= gr_dequeue,

	.set_halt	= gr_set_halt,
	.fifo_status	= gr_fifo_status,
	.fifo_flush	= gr_fifo_flush,
};

/*-------------------------------------------------------------------------*/
/* Get latest received frame number */ 
static int gr_get_frame(struct usb_gadget *_gadget)
{
	struct gr_udc *dev;
        if (!_gadget) 
                return -ENODEV;
        dev = container_of (_gadget, struct gr_udc, gadget);
        return (gr_read32(dev->base + GR_GLOBAL_STATUS) & 0x7FF);
}

/* Remote wakeup */
static int gr_wakeup(struct usb_gadget *_gadget) 
{
        struct gr_udc *dev;
        unsigned long flags;
        
        if (!_gadget)
                return -ENODEV;
        dev = container_of (_gadget, struct gr_udc, gadget);
        
        /* Remote wakeup feature not enabled by host*/
        if (!dev->remote_wakeup) 
                return -EINVAL;
        
        spin_lock_irqsave( dev->lock, flags );
        gr_write32( dev->base + GR_GLOBAL_CTRL, gr_read32(dev->base + GR_GLOBAL_CTRL) | GR_GLOBAL_CTRL_RW  );
        spin_unlock_irqrestore(&dev->lock, flags);
        return 0;
}

static int gr_pullup(struct usb_gadget *_gadget, int is_on) 
{
        struct gr_udc   *dev;
	u32             tmp;
	unsigned long   flags;

	if (!_gadget)
		return -ENODEV;
	dev = container_of (_gadget, struct gr_udc, gadget);

	spin_lock_irqsave (&dev->lock, flags);
	tmp = gr_read32(dev->base + GR_GLOBAL_CTRL);
        if (is_on)
		tmp |= GR_GLOBAL_CTRL_EP;
	else
		tmp &= ~GR_GLOBAL_CTRL_EP;
	gr_write32( dev->base + GR_GLOBAL_CTRL, tmp);
	spin_unlock_irqrestore (&dev->lock, flags);

	return 0;
}

static const struct usb_gadget_ops gr_ops = {
	.get_frame	= gr_get_frame,
	.wakeup         = gr_wakeup,
        .pullup         = gr_pullup,
	// others not supported
};

/*-------------------------------------------------------------------------*/
static void ep0_test_mode_complete(struct usb_ep* _ep, struct usb_request* _req)
{
        u32 ctrl;
        struct gr_ep *ep;
        struct gr_udc *dev;
        ep = container_of(_ep, struct gr_ep, ep);
        dev = ep->dev;
        
        ctrl = gr_read32(dev->base + GR_GLOBAL_CTRL);
        ctrl = ctrl | GR_GLOBAL_CTRL_TM | (dev->test_mode << GR_GLOBAL_CTRL_TS_POS);
        
        gr_write32(dev->base + GR_GLOBAL_CTRL, ctrl);
}

static void ep0_dummy_complete(struct usb_ep* _ep, struct usb_request* _req)
{
	//nothing needs to be done here
}

/* This is run when a SET_ADDRESS request is received. First writes
   the new address to the control register which is updated internally
   when the next IN packet is ACKED. Then a zero size IN packet is
   enabled */
int gr_set_address(struct gr_udc *dev, u8 address) {

        u32 ctrl;
	int status = -1;
        
        dev->address = address;
        
        INFO("setting address to %d", dev->address);

	ctrl = gr_read32(dev->base + GR_GLOBAL_CTRL);
	ctrl = (ctrl & ~0xFF) | (dev->address << 1) | GR_GLOBAL_CTRL_SU;
	gr_write32(dev->base + GR_GLOBAL_CTRL, ctrl);

        dev->ep0reqi->req.complete = ep0_dummy_complete;
	dev->ep0reqi->req.length = 0;
        status = gr_queue(&dev->ep[dev->nepo].ep, &dev->ep0reqi->req, GFP_ATOMIC);

        if( status < 0 ) {
                ERROR("error gr_queue'ing ep0reqi status=%d", status);
        }
        
	return status;
}

int gr_get_device_status(struct gr_udc *dev) {

	int status = -1;

	dev->ep0reqi->req.complete = ep0_dummy_complete;
	((u8*)dev->ep0reqi->req.buf)[0] = 1; 
	((u8*)dev->ep0reqi->req.buf)[1] = dev->remote_wakeup;
	dev->ep0reqi->req.length = 2;
        
        status = gr_queue(&dev->ep[dev->nepo].ep, &dev->ep0reqi->req, GFP_ATOMIC);

        if( status < 0 ) {
                ERROR("error gr_queue'ing ep0reqi status=%d", status);
        }
        
	return status;
}

int gr_get_interface_status(struct gr_udc *dev, u8 interface) {

	int status = -1;

	dev->ep0reqi->req.complete = ep0_dummy_complete;
	((u8*)dev->ep0reqi->req.buf)[0] = 0;
	((u8*)dev->ep0reqi->req.buf)[1] = 0;
	dev->ep0reqi->req.length = 2;
        
        status = gr_queue(&dev->ep[dev->nepo].ep, &dev->ep0reqi->req, GFP_ATOMIC);

    if( status < 0 ) {
	    ERROR("error gr_queue'ing ep0reqi status=%d", status);
    }

	return status;
}

int gr_get_endpoint_status(struct gr_udc *dev, int epnum, int is_in) {

	int status = -1;

	int ep_index = epnum + (is_in ? dev->nepo : 0);
	struct gr_ep* ep = &dev->ep[ep_index];

        u32 cur_ctrl = gr_read32( GR_EP( ep ) + GR_EP_CTRL );

	dev->ep0reqi->req.complete = ep0_dummy_complete;
	((u8*)dev->ep0reqi->req.buf)[0] = (cur_ctrl & GR_EP_CTRL_EH ? 1 : 0);
	((u8*)dev->ep0reqi->req.buf)[1] = 0;
	dev->ep0reqi->req.length = 2;

        status = gr_queue(&dev->ep[dev->nepo].ep, &dev->ep0reqi->req, GFP_ATOMIC);

        if( status < 0 ) {
                ERROR("error gr_queue'ing ep0reqi status=%d", status);
        }
        
	return status;
}

int gr_get_status(struct gr_udc *dev, u8 recipient, u16 index) {

	int status = -1;

	switch(recipient & 0x3) { //recipient
		case USB_RECIP_DEVICE:
			if(index == 0) {
				status = gr_get_device_status(dev);
			}
			break;
		case USB_RECIP_INTERFACE:
			if(dev->configured) {
				status = gr_get_interface_status(dev, index & 0xFF);
			}
			break;
		case USB_RECIP_ENDPOINT:
		{
			int epnum = index & 0xF;
			int is_in = (index >> 7) & 0x1;

//			int epnum = (index >> 4) & 0xF;
//			int is_in = (index >> 3) & 0x1;

			if(dev->configured || epnum == 0) {

				if( (!is_in && epnum < dev->nepo) ||
					( is_in && epnum < dev->nepi) ) {

					status = gr_get_endpoint_status(dev, epnum, is_in);
				}
			}
			break;
		}

		case USB_RECIP_OTHER:
		default:
			//STALL
			break;
	}
	return status;
}

int gr_set_feature(struct gr_udc *dev, u8 recipient, u16 feature_selector, u16 index) {

	int status = -1;

        switch(recipient & 0x3) { //recipient
		case USB_RECIP_DEVICE:
			switch(feature_selector) {

				case USB_DEVICE_REMOTE_WAKEUP:
                                        //Enable remote wakeup
					dev->remote_wakeup = 1;
                                        dev->ep0reqi->req.complete = ep0_dummy_complete;
                                        dev->ep0reqi->req.length = 0;
                                        gr_queue( &dev->ep[dev->nepo].ep, &dev->ep0reqi->req, GFP_ATOMIC );
					break;
				case USB_DEVICE_TEST_MODE:
				{
					dev->test_mode = (index >> 8);
					dev->ep0reqi->req.complete = ep0_test_mode_complete;
                                        dev->ep0reqi->req.length = 0;
                                        gr_queue( &dev->ep[dev->nepo].ep, &dev->ep0reqi->req, GFP_ATOMIC );
                                        break;
				}
			}
			break;
		case USB_RECIP_ENDPOINT:
                        switch(feature_selector) {

				case USB_ENDPOINT_HALT:
				{
                                        int epnum = index & 0xF;
					int is_in = (index >> 7) & 0x1;
					if(dev->configured || epnum == 0) {

						if( (!is_in && epnum < dev->nepo) ||
							( is_in && epnum < dev->nepi) ) {

                                                                int ep_index = epnum + (is_in ? dev->nepo : 0);
								struct gr_ep* ep = &dev->ep[ep_index];
                                                                status = gr_set_halt(&ep->ep, 1);
                                                                
						}
					}
                                        /* Handle status stage */
                                        if (status >= 0) {
                                                /* dev->ep0state = EP0_STATUS; */
                                                dev->ep0reqi->req.complete = ep0_dummy_complete;
                                                dev->ep0reqi->req.length = 0;
                                                gr_queue( &dev->ep[dev->nepo].ep, &dev->ep0reqi->req, GFP_ATOMIC );
                                        }
                                        break;
				}
			}
			break;

		case USB_RECIP_INTERFACE:
		case USB_RECIP_OTHER:
		default:
			//STALL
			break;
	}

	return status;
}

int gr_clear_feature(struct gr_udc *dev, u8 recipient, u16 feature_selector, u16 index) {

	int status = -1;

	switch(recipient & 0x3) { //recipient
		case USB_RECIP_DEVICE:
			switch(feature_selector) {

				case USB_DEVICE_REMOTE_WAKEUP:
                                        //disable remote wakeup feature
					dev->remote_wakeup = 0;
                                        dev->ep0reqi->req.complete = ep0_dummy_complete;
                                        dev->ep0reqi->req.length = 0;
                                        gr_queue( &dev->ep[dev->nepo].ep, &dev->ep0reqi->req, GFP_ATOMIC );
                                        status = 0;
					break;

				default:
					break;
			}
			break;
		case USB_RECIP_ENDPOINT:
			switch(feature_selector) {

				case USB_ENDPOINT_HALT:
				{
					int epnum = index & 0xF;
					int is_in = (index >> 7) & 0x1;
					if(dev->configured || epnum == 0) {

						if( (!is_in && epnum < dev->nepo) ||
							( is_in && epnum < dev->nepi) ) {

								int ep_index = epnum + (is_in ? dev->nepo : 0);
								struct gr_ep* ep = &dev->ep[ep_index];
								status = gr_set_halt(&ep->ep, 0);
						}
					}
                                        if (status >= 0) {
                                                /* dev->ep0state = EP0_STATUS; */
                                                dev->ep0reqi->req.complete = ep0_dummy_complete;
                                                dev->ep0reqi->req.length = 0;
                                                gr_queue( &dev->ep[dev->nepo].ep, &dev->ep0reqi->req, GFP_ATOMIC );
                                        }
                                        break;
				}

				default:
					break;
			}
			break;

		case USB_RECIP_INTERFACE:
		case USB_RECIP_OTHER:
		default:
			//STALL
			break;
	}

	return status;
}

static void ep0_complete(struct usb_ep* _ep, struct usb_request* _req)
{
	struct gr_ep	*ep;
	struct gr_udc	*dev;
        struct list_head *pos;
	int status;
        int i;
	u16 wValue;
	u16 wIndex;
        u16 wLength;
        union {
           struct usb_ctrlrequest		ctrl;
           u8 raw[8];
           u32 word[2];
        } u;

	ep = container_of(_ep, struct gr_ep, ep);
	dev = ep->dev;
        
	if(_req->status != -ESHUTDOWN) {
                
                //no setup requests are zero length, most likely status stage change
		if(_req->actual != 0) {

			// read SETUP packet and enter DATA stage
			for( i=0; i < _req->actual; i++ ) {
				u.raw[i] = ((u8*)_req->buf)[i];
			}
		

			wValue = le16_to_cpu(u.ctrl.wValue);
			wIndex = le16_to_cpu(u.ctrl.wIndex);
                        wLength = le16_to_cpu(u.ctrl.wLength);

                        INFO("SETUP %02x.%02x v%04x i%04x l%04x",
                             u.ctrl.bRequestType, u.ctrl.bRequest,
                             wValue, wIndex,
                             wLength);

                        dev->req_config = (u.ctrl.bRequest == USB_REQ_SET_CONFIGURATION
						&& u.ctrl.bRequestType == USB_RECIP_DEVICE);
			if (unlikely(dev->req_config))
				dev->configured = (wValue != 0);

                        if (!(u.ctrl.bRequestType & USB_DIR_IN) && (wLength != 0)) {
                                dev->ep0state = EP0_OUT;
                        } else {
                                dev->ep0state = EP0_IN;
                        }
                        
                        switch(u.ctrl.bRequest) {
				case USB_REQ_SET_ADDRESS:
					status = gr_set_address(dev, (u8)(wValue & 0xFF));
                                        break;
				case USB_REQ_GET_STATUS:
					status = gr_get_status(dev, u.ctrl.bRequestType, wIndex);
                                        break;
				case USB_REQ_SET_FEATURE:
                                        status = gr_set_feature(dev, u.ctrl.bRequestType, wValue, wIndex);
                                        break;
				case USB_REQ_CLEAR_FEATURE:
					status = gr_clear_feature(dev, u.ctrl.bRequestType, wValue, wIndex);
                                        break;
				default:
					/* delegate the rest to the gadget driver.
					 * it may respond after this irq handler returns.
					 */
					//spin_unlock (&dev->lock);
                                        status = dev->driver->setup(&dev->gadget, &u.ctrl);
					//spin_lock (&dev->lock);
					break;
			}

                        if (unlikely(status < 0)) { //STALL
                                u32 cur_ctrl;
				/* WARNING("req %02x.%02x protocol STALL; err %d", */
/* 						u.ctrl.bRequestType, u.ctrl.bRequest, status); */

/* 				sdump_buffer( &u, sizeof(u), "unknown request" ); */

				cur_ctrl = gr_read32( GR_EP( &dev->ep[0] ) + GR_EP_CTRL );
				gr_write32( GR_EP( &dev->ep[0] ) + GR_EP_CTRL, GR_EP_CTRL_CS | cur_ctrl );
				cur_ctrl = gr_read32( GR_EP( &dev->ep[dev->nepo] ) + GR_EP_CTRL );
				gr_write32( GR_EP( &dev->ep[dev->nepo] ) + GR_EP_CTRL, GR_EP_CTRL_CS | cur_ctrl );
			}

                        /* Handle status stage for OUT data transfer in control data stage*/
                        if (dev->ep0state == EP0_OUT) {
                                dev->ep0state = EP0_STATUS;
                                /* dev->ep0reqi->req.complete = ep0_dummy_complete; */
/*                                 dev->ep0reqi->req.length = 0; */
/*                                 gr_queue( &dev->ep[dev->nepo].ep, &dev->ep0reqi->req, GFP_ATOMIC ); */
                        }

		}
                
                if (dev->ep0state != EP0_STATUS) 
                        dev->ep0state = EP0_IDLE;
		dev->ep[0].stopped = 0;
		dev->ep[dev->nepo].stopped = 0;
                
                status = gr_queue( &dev->ep[0].ep, &dev->ep0reqo->req, GFP_ATOMIC );

                if( status < 0 ) {
			ERROR("error gr_queue'ing ep0reqo status=%d", status);
			dev->ep[0].stopped = 1;
		}
	}
}

static void gr_udc_reinit (struct gr_udc *dev)
{
        static char *onames [] = 
        {"ep0out", "ep1out", "ep2out", "ep3out", "ep4out", "ep5out", 
         "ep6out", "ep7out", "ep8out", "ep9out", "ep10out", "ep11out", 
         "ep12out", "ep13out", "ep14out", "ep15out"};
        
        static char *inames [] = 
        {"ep0in", "ep1in", "ep2in", "ep3in", "ep4in", "ep5in", 
         "ep6in", "ep7in", "ep8in", "ep9in", "ep10in", "ep11in", 
         "ep12in", "ep13in", "ep14in", "ep15in"};
        
	unsigned i;
        struct usb_request * _req = NULL;
        struct list_head *pos;
        
        u32 ctrl_val;

	dev->address = 0;

	if(dev->ep0reqo) {
                kfree(dev->ep0reqo->req.buf);
                gr_ep_nuke(&dev->ep[0], -ESHUTDOWN);
                gr_free_request(&dev->ep[0].ep, &dev->ep0reqo->req);
        }

	if(dev->ep0reqi) {
                kfree(dev->ep0reqi->req.buf);
		gr_ep_nuke(&dev->ep[dev->nepo], -ESHUTDOWN);
		gr_free_request(&dev->ep[dev->nepo].ep, &dev->ep0reqi->req);
        }

	_req = gr_alloc_request( &dev->ep[0].ep, GFP_KERNEL );
	_req->complete = ep0_complete;
	dev->ep0reqo = container_of( _req, struct gr_request, req );
	dev->ep0reqo->req.buf = kmalloc( PAGE_SIZE, GFP_DMA | GFP_KERNEL );
	dev->ep0reqo->req.length = MAX_EP0_SIZE;

	_req = gr_alloc_request( &dev->ep[dev->nepo].ep, GFP_KERNEL );
	_req->complete = NULL; //gets set as used
	dev->ep0reqi = container_of( _req, struct gr_request, req );
	dev->ep0reqi->req.buf = kmalloc( PAGE_SIZE, GFP_DMA | GFP_KERNEL );
	dev->ep0reqi->req.length = MAX_EP0_SIZE;
        
        if( !dev->ep0reqo->req.buf ) {
		ERROR("can't alloc request");
		return;
	}

	if( !dev->ep0reqi->req.buf ) {
		ERROR("can't alloc request");
		return;
	}

	INIT_LIST_HEAD (&dev->gadget.ep_list);
	dev->gadget.ep0 = &dev->ep [dev->nepo].ep;
	dev->gadget.speed = USB_SPEED_UNKNOWN;
	dev->ep0state = EP0_DISCONNECT;

        for (i = 0; i < dev->nepo; i++) {
		struct gr_ep *ep = &dev->ep[i];

		ep->num = i;
		ep->ep.name = onames[i];
		ep->is_in = 0;
                ep->last_desc = NULL;
                
                ep->ep.ops = &gr_ep_ops;
		/* ep0 should not be on the list, remove later*/
		list_add_tail (&ep->ep.ep_list, &dev->gadget.ep_list);
		ep->dev = dev;

		INIT_LIST_HEAD (&ep->queue);

		gr_ep_reset(ep);
	}

        for (i = 0; i < dev->nepi; i++) {
		struct gr_ep *ep = &dev->ep[i+dev->nepo];

		ep->num = i;
		ep->ep.name = inames[i];
		ep->is_in = 1;
                ep->last_desc = NULL;
		
		ep->ep.ops = &gr_ep_ops;
		/* ep0 should not be on the list remove later*/
		list_add_tail (&ep->ep.ep_list, &dev->gadget.ep_list);
		ep->dev = dev;

		INIT_LIST_HEAD (&ep->queue);

		gr_ep_reset(ep);
	}
        

        /* Set remote wakeup capability to disabled which is what it must be
           per default.*/
        dev->remote_wakeup = 0;
	dev->ep[0].ep.maxpacket = MAX_EP0_SIZE;
	dev->ep[dev->nepo].ep.maxpacket = MAX_EP0_SIZE;
	dev->ep[0].bytes_per_buffer = MAX_EP0_SIZE;
	dev->ep[dev->nepo].bytes_per_buffer = MAX_EP0_SIZE;
	/* remove ep0 IN/OUT from ep list*/
	list_del_init (&dev->ep[0].ep.ep_list);
	list_del_init (&dev->ep[dev->nepo].ep.ep_list);
        ctrl_val = ( MAX_EP0_SIZE << GR_EP_CTRL_MAXPL_POS ) | GR_EP_CTRL_EV;
        gr_write32( GR_EP( &dev->ep[0] ) + GR_EP_CTRL, ctrl_val );
        gr_write32( GR_EP( &dev->ep[dev->nepo] ) + GR_EP_CTRL, ctrl_val );
        gr_write32( GR_EP( &dev->ep[0] ) + GR_EP_DMACTRL, GR_EP_DMACTRL_IE | GR_EP_DMACTRL_AI );
        gr_write32( GR_EP( &dev->ep[dev->nepo] ) + GR_EP_DMACTRL, GR_EP_DMACTRL_IE | GR_EP_DMACTRL_AI );

}

static void gr_udc_reset(struct gr_udc *dev, int remote_wakeup)
{
	u32 ctrl =  GR_GLOBAL_CTRL_SI | GR_GLOBAL_CTRL_UI | GR_GLOBAL_CTRL_SP | GR_GLOBAL_CTRL_EP;

	if(remote_wakeup) {
		ctrl |= GR_GLOBAL_CTRL_RW;
	}

        gr_write32( dev->base + GR_GLOBAL_CTRL, ctrl );
}

static void ep0_start(struct gr_udc *dev)
{
        int status;
	//unsigned			i;
        
	INFO("%s", __FUNCTION__);

	dev->ep0state = EP0_IDLE;
	dev->ep[0].stopped = 0;
	dev->ep[dev->nepo].stopped = 0;
        dev->ep[0].dma_start = 0;
        dev->ep[dev->nepo].dma_start = 0;

        status = gr_queue( &dev->ep[0].ep, &dev->ep0reqo->req, GFP_ATOMIC );
        
        if( status < 0 ) {
                ERROR("error gr_queue'ing ep0reqo status=%d", status);
                dev->ep[0].stopped = 1;
                return;
        }

}

static void gr_udc_enable(struct gr_udc *dev)
{
        u32 status = gr_read32( dev->base + GR_GLOBAL_STATUS );
        //start ep0 and turn on interrupts
        if( status & GR_GLOBAL_STATUS_VB ) {
                
                //This is the case that we are already plugged in when the driver
                //starts
                dev->gadget.speed = ( status & GR_GLOBAL_STATUS_SP ) ? USB_SPEED_HIGH : USB_SPEED_FULL;
                gr_udc_reset( dev, 1 );
                dev->vbus_valid = 1;
                
        } else {
                gr_write32( dev->base + GR_GLOBAL_CTRL, GR_GLOBAL_CTRL_UI );
        }
        gr_pullup(&dev->gadget, 1);
}

/*-------------------------------------------------------------------------*/
static int gr_probe(void);

/* when a driver is successfully registered, it will receive
 * control requests including set_configuration(), which enables
 * non-control requests.  then usb traffic follows until a
 * disconnect is reported.  then a host may connect again, or
 * the driver might get unbound.
 */
int usb_gadget_register_driver(struct usb_gadget_driver *driver)
{
	struct gr_udc	*dev = NULL;
	int		retval;

	retval = gr_probe();
        if(retval) {
		return retval;
	}

	dev = the_controller;

	if (!driver
            || driver->speed < USB_SPEED_FULL
            || !driver->bind
			|| !driver->disconnect
			|| !driver->setup) {
		return -EINVAL;
	}

	if (!dev) {
		return -ENODEV;
	}
	if (dev->driver) {
		return -EBUSY;
	}

        gr_udc_reinit( dev );

	/* hook up the driver */
	driver->driver.bus = NULL;
	dev->driver = driver;
	dev->gadget.dev.driver = &driver->driver;
        retval = driver->bind(&dev->gadget);
        if (retval) {
		INFO("bind to driver %s --> error %d",
				driver->driver.name, retval);
		dev->driver = NULL;
		dev->gadget.dev.driver = NULL;
                the_controller = NULL;
                device_unregister(&dev->gadget.dev);
                amba_free_ahbslv_device(dev->amba_dev);
                return retval;
	}

        dev->vbus_valid = 0;

	/* then enable host detection and ep0; and we're ready
	 * for set_configuration as well as eventual disconnect.
	 */
        
        /* init to known state, then setup irqs */
	gr_udc_enable( dev );
	dev->irq_enabled = 1;

	printk("registered gadget driver '%s'", driver->driver.name);
	return 0;
}
EXPORT_SYMBOL(usb_gadget_register_driver);

static void
gr_stop_activity(struct gr_udc *dev, struct usb_gadget_driver *driver)
{
	unsigned	i;

	INFO("%s", __FUNCTION__);

	if (dev->gadget.speed == USB_SPEED_UNKNOWN)
		driver = NULL;

	//only turn on VBUS interrupt
	gr_write32( dev->base + GR_GLOBAL_CTRL, GR_GLOBAL_CTRL_UI );

        for (i = 0; i < dev->nepi; i++) {
		struct gr_ep *ep = &dev->ep[i];
		gr_ep_nuke(ep, -ESHUTDOWN);
	}
        
        for (i = 0; i < dev->nepi; i++) {
		struct gr_ep *ep = &dev->ep[i+dev->nepo];
		gr_ep_nuke(ep, -ESHUTDOWN);
	}

	if (driver) {
		spin_unlock(&dev->lock);
		driver->disconnect(&dev->gadget);
		spin_lock(&dev->lock);
	}
        gr_pullup(&dev->gadget, 0);
}

int usb_gadget_unregister_driver(struct usb_gadget_driver *driver)
{
	struct gr_udc	*dev = the_controller;
	unsigned long	flags;

	if (!dev)
		return -ENODEV;
	if (!driver || driver != dev->driver || !driver->unbind)
		return -EINVAL;

	spin_lock_irqsave(&dev->lock, flags);

	dev->irq_enabled = 0;
	dev->driver = NULL;
	gr_stop_activity(dev, driver);
        dma_pool_destroy(dev->desc_pool);
        
        gr_write32( dev->base + GR_GLOBAL_CTRL, 0); //disable irqs

	spin_unlock_irqrestore(&dev->lock, flags);

	driver->unbind(&dev->gadget);

	if (dev->got_irq)
		free_irq(dev->irq, dev);
	if (dev->base)
		iounmap(dev->base);

        device_unregister(&dev->gadget.dev);

	dev->base = NULL;
	the_controller = NULL;

	INFO("unregistered driver '%s'", driver->driver.name);
	return 0;
}
EXPORT_SYMBOL(usb_gadget_unregister_driver);

static void data_wq(unsigned long unused) 
{
        struct gr_udc *dev = the_controller;
        struct gr_ep *ep;
        int handled = 0;
        u32 status;
        int i;
	static int n = 0;

        spin_lock(&dev->lock);
        
        // check IN ep interrupts. We check these before the OUT eps because some
	// gadgets reuse the request that might already be currently outstanding
	// and needs to be completed (mainly setup requests)
        for( i=0; i<dev->nepi; i++ ) {
		ep = &dev->ep[i+dev->nepo];

		if(!ep->stopped && !list_empty(&ep->queue)) {
			struct gr_request* req = list_entry(ep->queue.next, struct gr_request, queue);

                        if( req->last_desc ) {
                                //Check if last descriptor for this request has been finished
				if( !( gr_read32_nocache(req->last_desc->ctrl) & GR_DESC_IN_CTRL_EN ) ) {
					//write complete
                                        handled = 1;
                                        gr_dma_advance( ep->dev, ep );
					//goto end;
				}
			}
		}
	}
        
        /// check OUT ep interrupts
        for( i=0; i < dev->nepo; i++ ) {
                ep = &dev->ep[i];
		if(!ep->stopped && !list_empty(&ep->queue)) {
			struct gr_request* req = list_entry(ep->queue.next, struct gr_request, queue);
                        if( req->dma_desc ) { 
				u32 ctrl = gr_read32_nocache(req->dma_desc->ctrl);
				if( !( ctrl & GR_DESC_OUT_CTRL_EN ) ) {
                                        u16 len = ctrl & GR_DESC_OUT_CTRL_LEN_MASK;
                                        if(len < ep->ep.maxpacket) {
                                                //read complete
                                                handled = 1;
                                                /* enable IN 0 packet for status stage */
                                                if (dev->ep0state == EP0_STATUS) {
                                                        dev->ep0reqi->req.complete = ep0_dummy_complete;
                                                        dev->ep0reqi->req.length = 0;
                                                        gr_queue( &dev->ep[dev->nepo].ep, &dev->ep0reqi->req, GFP_ATOMIC );
                                                        dev->ep0state = EP0_IDLE;
                                                }
                                                gr_dma_advance( ep->dev, ep );
                                        } else {
                                                if(req->dma_desc->desc_next) {
                                                        //the transfer is larger than maxpacket and we need to
							//accumulate buffers so tell the HW the next
							//descriptor is valid.
							u32 ep_dmactrl = gr_read32(GR_EP(ep) + GR_EP_DMACTRL);
							req->dma_desc = req->dma_desc->desc_next;
                                                        req->dma_desc->ctrl |= GR_DESC_OUT_CTRL_EN;
//							gr_write32( GR_EP( ep ) + GR_EP_DMAADDR, req->last_desc->desc_phys  );
							ep_dmactrl |= GR_EP_DMACTRL_DA;
							gr_write32(GR_EP(ep) + GR_EP_DMACTRL, ep_dmactrl);
                                                } else {
                                                        //we don't have enough buffer space for the whole
							//transfer. Assume the transfer was "exact length"
							//and we should finish the request
                                                        
                                                        /* enable IN 0 packet for status stage */
                                                        if (dev->ep0state == EP0_STATUS) {
                                                                dev->ep0reqi->req.complete = ep0_dummy_complete;
                                                                dev->ep0reqi->req.length = 0;
                                                                gr_queue( &dev->ep[dev->nepo].ep, &dev->ep0reqi->req, GFP_ATOMIC );
                                                                dev->ep0state = EP0_IDLE;
                                                        }
                                                        gr_dma_advance( ep->dev, ep );
						}
					}

					//goto end;
				}
			}
		}
	}

        status = gr_read32( dev->base + GR_GLOBAL_STATUS );

//	INFO("[%lld] gr_irq %d status %08X", ktime_to_ns(timespec_to_ktime(CURRENT_TIME)), n++, status);

//	if( ( dev->vbus_valid && !( status & GR_GLOBAL_STATUS_VB ) ) ||
	if(	( !dev->vbus_valid && ( status & GR_GLOBAL_STATUS_VB ) ) ) {
		
		if( !dev->vbus_valid ) {
			dev->vbus_valid = 1;
			//VBUS valid detected
			INFO("[%lld] vbus valid detected %08X new speed is %s",
					ktime_to_ns(timespec_to_ktime(CURRENT_TIME)),
					status & GR_GLOBAL_STATUS_VB,
					(status & GR_GLOBAL_STATUS_SP ) ? "USB_SPEED_FULL" : "USB_SPEED_HIGH");
			gr_udc_reset( dev, 0 );
                        dev->gadget.speed = ( status & GR_GLOBAL_STATUS_SP ) ? USB_SPEED_FULL : USB_SPEED_HIGH;
		} else {
			//disconnect
			INFO("[%lld] vbus invalid detected %08X", ktime_to_ns(timespec_to_ktime(CURRENT_TIME)), status & GR_GLOBAL_STATUS_VB);
			dev->vbus_valid = 0;
			gr_stop_activity( dev, dev->driver );
			dev->ep0state = EP0_DISCONNECT;
		}
		handled = 1;
	}

	if( status & GR_GLOBAL_STATUS_UR ) {
		// USB reset detected
		n++;
		INFO("[%lld] host USB reset is done new speed is %s",
				ktime_to_ns(timespec_to_ktime(CURRENT_TIME)),
				(status & GR_GLOBAL_STATUS_SP ) ? "USB_SPEED_FULL" : "USB_SPEED_HIGH");
		gr_udc_reinit( dev );
		dev->gadget.speed = ( status & GR_GLOBAL_STATUS_SP ) ? USB_SPEED_FULL : USB_SPEED_HIGH;
		ep0_start( dev );
		gr_write32( dev->base + GR_GLOBAL_STATUS, GR_GLOBAL_STATUS_UR );
		handled = 1;
	}

	if( ( dev->gadget.speed != USB_SPEED_HIGH && !(status & GR_GLOBAL_STATUS_SP ) ) ||
		( dev->gadget.speed != USB_SPEED_FULL && (status & GR_GLOBAL_STATUS_SP ) ) ) {

		INFO("[%lld] USB Speed change to %s",
				ktime_to_ns(timespec_to_ktime(CURRENT_TIME)),
				(status & GR_GLOBAL_STATUS_SP ) ? "USB_SPEED_FULL" : "USB_SPEED_HIGH");
		dev->gadget.speed = ( status & GR_GLOBAL_STATUS_SP ) ? USB_SPEED_FULL : USB_SPEED_HIGH;
		handled = 1;
	}

	if( ( ( dev->ep0state == EP0_SUSPEND ) &&  ( status & GR_GLOBAL_STATUS_SU ) ) || //come out of suspend
		( ( dev->ep0state != EP0_SUSPEND ) && !( status & GR_GLOBAL_STATUS_SU ) ) ) { //go into suspend
		// device is suspended
		if( dev->ep0state != EP0_SUSPEND ) {
			INFO("[%lld] USB suspend", ktime_to_ns(timespec_to_ktime(CURRENT_TIME)));
			dev->ep0state = EP0_SUSPEND;
			if( ( dev->gadget.speed != USB_SPEED_UNKNOWN )
					&& dev->driver
					&& dev->driver->suspend ) {
				spin_unlock( &dev->lock );
				dev->driver->suspend( &dev->gadget );
				spin_lock( &dev->lock );
			}
		} else {
			INFO("[%lld] USB resume", ktime_to_ns(timespec_to_ktime(CURRENT_TIME)));
			dev->ep0state = EP0_IDLE;
			if( ( dev->gadget.speed != USB_SPEED_UNKNOWN )
					&& dev->driver
					&& dev->driver->resume ) {

				spin_unlock( &dev->lock );
				dev->driver->resume( &dev->gadget );
				spin_lock( &dev->lock );
			}
		}
		handled = 1;
	}

		

        //check amba dma errors. Only check if we didn't find anything else to
	//handle because this shouldn't happen if we did everything right
	if(!handled) {
		for(i=0; i < dev->nepo; i++) {
			ep = &dev->ep[i];
			if(gr_read32( GR_EP(ep) + GR_EP_DMACTRL ) & GR_EP_DMACTRL_AE ) {
				ERROR("AMBA Error occured for descriptor on ep%d%s", i, ep->is_in ? "IN" : "OUT");
				handled = 1;
			}
		}	
	
		for(i=0; i < dev->nepi; i++) {
			ep = &dev->ep[i+dev->nepo];
			if(gr_read32( GR_EP(ep) + GR_EP_DMACTRL ) & GR_EP_DMACTRL_AE ) {
				ERROR("AMBA Error occured for descriptor on ep%d%s", i, ep->is_in ? "IN" : "OUT");
				handled = 1;
			}
		}
	}

end:


        spin_unlock(&dev->lock);

}

/*-------------------------------------------------------------------------*/

static irqreturn_t gr_irq(int irq, void *_dev)
{
	struct gr_udc			*dev = _dev;
	
        if(unlikely(!dev->irq_enabled)) {
		return IRQ_RETVAL(0);
	}
        
	/* tasklet_schedule(&gr_udc_tasklet); */
        schedule_work(&gr_udc_wq);
        

        return IRQ_RETVAL(1);
}

/*-------------------------------------------------------------------------*/

static void gadget_release(struct device *_dev)
{
	struct gr_udc	*dev = dev_get_drvdata(_dev);
        kfree(dev);
}

/* wrap this driver around the amba device, but
 * don't respond over USB until a gadget driver binds to us.
 */

static int gr_probe(void)
{
	struct gr_udc		*dev = NULL;
	int			retval = 0;
        int                     tmp;
        
        amba_ahb_device amba_dev[1];
	/* if you want to support more than one controller in a system,
	 * usb_gadget_driver_{register,unregister}() must change.
	 */
	if (the_controller) {
		WARNING("ignoring");
		return -EBUSY;
	}

        if( !amba_get_free_ahbslv_devices( VENDOR_GAISLER, GAISLER_USBDC, amba_dev, 1 ) ) {
                WARNING("could not find amba slave with id's %08x %08x", VENDOR_GAISLER, GAISLER_USBDC );
                return -ENODEV;
        }

	/* alloc, and start init */
	dev = kzalloc (sizeof *dev, GFP_KERNEL);
	if (dev == NULL) {
		retval = -ENOMEM;
		goto err;
	}

        dev->amba_dev = amba_dev;
        
        spin_lock_init(&dev->lock);
	dev->gadget.ops = &gr_ops;

	/* the "gadget" abstracts/virtualizes the controller */
	strcpy(dev->gadget.dev.bus_id, "gadget");
	dev->gadget.dev.parent = NULL;
	dev->gadget.dev.dma_mask = 0;
	dev->gadget.dev.release = gadget_release;
	dev->gadget.name = driver_name;
        dev->gadget.is_dualspeed = 1;
        INIT_LIST_HEAD(&dev->gadget.dev.dma_pools);
        
        dev->enabled = 1;
        dev->base = ioremap_nocache( amba_dev[0].start[0], GAISLER_USBD_REGION_SIZE );
        dev->irq = amba_dev[0].irq;

        if( dev->base == NULL ) {
                ERROR("can't map memory");
                retval = -EFAULT;
                goto err;
        }

        INFO("%s", driver_desc);
	INFO("version: " DRIVER_VERSION " %s", "using dma");
        INFO("irq: %d, base mem %p", dev->irq, dev->base);

	//clear all interrupt enables that might be left on since last boot
	gr_write32( dev->base + GR_GLOBAL_CTRL, 0);

        /* Determine number of endpoints and data interface mode */
        tmp = gr_read32(dev->base + GR_GLOBAL_STATUS);
        dev->nepi = ((tmp >> 28) & 0xF) + 1;  
        dev->nepo = ((tmp >> 24) & 0xF) + 1;  
        dev->is_mst = (tmp >> 23) & 1;
        
        if( request_irq( dev->irq, gr_irq, IRQF_SHARED/*|IRQF_SAMPLE_RANDOM*/,
                         driver_name, dev ) != 0 ) {
		ERROR("request interrupt %d failed", dev->irq);
		retval = -EBUSY;
		goto err;
	}
        dev->got_irq = 1;
        
        INIT_WORK(&gr_udc_wq, (void (*)(void *)) data_wq);

        /* done */
	the_controller = dev;
        retval = device_register(&dev->gadget.dev);

        /* Create DMA pool for descriptors */ 
        dev->desc_pool = dma_pool_create("desc_pool", &dev->gadget.dev, sizeof(struct gr_dma_desc), 4, 0);
        
        if (!dev->desc_pool) {
                ERROR("can't alloc memory pool");
                retval = -ENOMEM;
                goto err;
        }

        return retval;

err:
	if (dev) {
		if(dev->base) {
			iounmap(dev->base);
		}
                kfree(dev);
	}

	return retval;
}


/*-------------------------------------------------------------------------*/

static int __init init (void)
{
	return 0;
}
module_init (init);

static void __exit cleanup (void)
{
}
module_exit (cleanup);
