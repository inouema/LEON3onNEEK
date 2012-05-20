/*
 * leon_pci.c: GRPCI controller support
 * 
 *
 * The GRPCI provides two windows in the AMBA address space to which accesses are
 * translated into PCI cycles. One 256 MB big for generating PCI memory cycles and 
 * one 64 KB for PCI IO cycles.
 *  
 * This file provide low level functions for the generic PCI layer. The entry point
 * is pcic_init which detects the GRPCI core and configures the PCI resources 
 * according to the AMBA plug and play information. When the host controller is
 * configured pcic_init calls pci_scan_bus() to detect all devices and 
 * pci_assign_unassigned_resources() to allocate and assign all BARs.
 *
 * A 1:1 mapping between PCI addresses and AMBA addresses is provided. The system
 * RAM of the host is mapped at PCI address 0x40000000.
 *
 * To preserve correct byte ordering the host controller should be configured to do
 * byte twisting. If, for some reason, this is not wanted uncomment #define BT_ENABLED 1.
 * 
 * The in/out and read/write macros defined in io.h will do the necessary byte twisting for
 * 16 and 32 bit PIO acccesses. The macros __raw_read* and __raw_write* provide non twisting 
 * equivalents for memory cycles.
 *
 * The PCI IO area is remapped in pcic_init so the physical BAR values must be passed directly 
 * to in/out and the translation from physical to virtual is done in the in/out macros.
 * 
 * All PCI interrupt lines are routed to the IRQ of the GRPCI apb slave.
 *
 *   (C) Copyright Gaisler Research, 2006, 2007
 *   (C) Aeroflex Gaisler, 2008, 2009
 *
 *   Author Kristoffer Glembo <kristoffer@gaisler.com>
 *   Bits and pieces from MicroSPARC-IIep PCI controller support & MIPS PCI layer.
 */

#include <linux/autoconf.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/jiffies.h>

#include <asm/io.h>

#include <linux/ctype.h>
#include <linux/pci.h>
#include <linux/time.h>
#include <linux/timex.h>
#include <linux/interrupt.h>

#include <asm/ambapp.h>
#include <asm/leon_pci.h>
#include <asm/uaccess.h>

//#define DEBUG 1

#ifdef DEBUG
#define DBG(x...) printk(x)
#else
#define DBG(x...)
#endif


/* Uncomment if host controller byte twisting should be disabled */
#define BT_ENABLED 1

struct leon_pci pcic0 = {
    .mem_resource.name = "LEON PCI Memory space",
    .io_resource.name  = "LEON PCI IO space"
};

unsigned long leon_pci_iobase;
EXPORT_SYMBOL(leon_pci_iobase);

static int pcic_read_config_dword(unsigned int busno, unsigned int devfn,
                                  int where, u32 *value)
{
	struct leon_pci *pcic;
	unsigned long flags;
    

	pcic = &pcic0;

	local_irq_save(flags);

        LEON3_BYPASS_STORE_PA( &pcic->regs->cfg_stat, (LEON3_BYPASS_LOAD_PA(&pcic->regs->cfg_stat) & ~(0xF<<23)) | (busno<<23) ); /* Write bus number field in conf register */

        *value = LEON3_BYPASS_LOAD_PA( pcic->io_base_pa + 0x10000 + ((devfn&0xff)<<8) + (where & ~3) );

        if (LEON3_BYPASS_LOAD_PA(&pcic->regs->cfg_stat) & GRPCI_CTO) {
            *value = 0;
        }

	local_irq_restore(flags);

#ifdef BT_ENABLED
        *value = flip_dword(*value);
#endif

        DBG("pcic_read_config_dword(%d) - addr: %x, value: %x\n", busno, pcic->io_base_pa + 0x10000 + ((devfn&0xff)<<8) + (where & ~3), *value);

	return 0;
}

static int pcic_read_config(struct pci_bus *bus, unsigned int devfn,
                            int where, int size, u32 *val)
{
	unsigned int v;

        if (PCI_SLOT(devfn) > 21 || (PCI_SLOT(devfn) == 0 && bus->number == 0)) return 0;
	switch (size) {
	case 1:
            pcic_read_config_dword(bus->number, devfn, where&~3, &v);
            *val = 0xff & (v >> (8*(where & 3)));
            return 0;
	case 2:
            if (where&1) return -EINVAL;
            pcic_read_config_dword(bus->number, devfn, where&~3, &v);
            *val = 0xffff & (v >> (8*(where & 3)));
            return 0;
	case 4:
            if (where&3) return -EINVAL;
            pcic_read_config_dword(bus->number, devfn, where&~3, val);
            return 0;
	}
	return -EINVAL;
}

static int pcic_write_config_dword(unsigned int busno, unsigned int devfn,
                                   int where, u32 value)
{
        struct leon_pci *pcic;
	unsigned long flags;
        u32 val;

	pcic = &pcic0;

#ifdef BT_ENABLED
        val = flip_dword(value);
#else
        val = value;
#endif

        DBG("pcic_write_config_dword(%d) - addr %x, data: %x\n", busno, pcic->io_base_pa + 0x10000 + ((devfn&0xff)<<8) + (where & ~3), value);

	local_irq_save(flags);
        LEON3_BYPASS_STORE_PA( &pcic->regs->cfg_stat, (LEON3_BYPASS_LOAD_PA(&pcic->regs->cfg_stat) & ~(0xF<<23)) | (busno<<23) ); /* Write bus number field in conf register */
        LEON3_BYPASS_STORE_PA( pcic->io_base_pa + 0x10000 + ((devfn&0xff)<<8) + (where & ~3), val );

	local_irq_restore(flags);
	return 0;
}

static int pcic_write_config(struct pci_bus *bus, unsigned int devfn,
   int where, int size, u32 val)
{
	unsigned int v;

        if (PCI_SLOT(devfn) > 21) return 0;

	switch (size) {
	case 1:
		pcic_read_config_dword(bus->number, devfn, where&~3, &v);
		v = (v & ~(0xff << (8*(where&3)))) |
		    ((0xff&val) << (8*(where&3)));
		return pcic_write_config_dword(bus->number, devfn, where&~3, v);
	case 2:
		if (where&1) return -EINVAL;
		pcic_read_config_dword(bus->number, devfn, where&~3, &v);
		v = (v & ~(0xffff << (8*(where&3)))) |
		    ((0xffff&val) << (8*(where&3)));
		return pcic_write_config_dword(bus->number, devfn, where&~3, v);
	case 4:
		if (where&3) return -EINVAL;
		return pcic_write_config_dword(bus->number, devfn, where, val);
	}
	return -EINVAL;
}

static struct pci_ops pcic_ops = {
	.read =		pcic_read_config,
	.write =	pcic_write_config,
};

/*
 * Main entry point from the PCI subsystem.
 */
static int __init pcic_init(void)
{
	struct leon_pci *pcic;
        unsigned int addr, data;
        amba_ahb_device dev;
	amba_apb_device apbdev; 
     
	pcic = &pcic0;
      
        /* configure pci controller */

	if ( amba_get_free_apbslv_devices (VENDOR_GAISLER, GAISLER_PCIFBRG, &apbdev, 1) != 1) {
            printk("No GRPCI controller found\n");
            return 0;
        }
        
        if ( apbdev.irq == 0 ){
            printk("GRPCI: No interrupt assigned to GRPCI controller\n");
            return 0;
        }

        pcic->regs = (LEON3_GRPCI_Regs_Map *) apbdev.start;
             
     	if ( amba_get_free_ahbslv_devices(VENDOR_GAISLER, GAISLER_PCIFBRG, &dev, 1) != 1 ) {
            printk("No GRPCI controller found\n");
            return 0;
        }

        pcic->mem_resource.start = dev.start[0];
        pcic->mem_resource.end   = dev.start[0] + 0xFFFFFFF; /* 256 MB */
        pcic->mem_resource.flags = IORESOURCE_MEM;

        pcic->io_base_pa = dev.start[1];
        pcic->io_base_va = (unsigned long) ioremap(dev.start[1], 0xffff);
        set_pci_iobase(pcic->io_base_va);
        pcic->io_resource.start = pcic->io_base_pa;
        pcic->io_resource.end   = pcic->io_base_pa + 0xFFFF;    /* 64 KB */
        pcic->io_resource.flags = IORESOURCE_IO;

        pcic->irq = apbdev.irq;

        printk("Found GRPCI controller - ahb mem,io: 0x%x, 0x%x - apb 0x%x - irq: %d\n", dev.start[0], dev.start[1], apbdev.start, apbdev.irq);

#ifndef BT_ENABLED
        /* Byte twisting enabled by default. Disable if BT_ENABLED is not defined.  */
        pcic_write_config_dword(0,0,0x10, 0xffffffff);
        pcic_read_config_dword(0,0,0x10, &addr);
        pcic_write_config_dword(0,0,0x10, flip_dword(0x10000000));     /* Setup bar0 to nonzero value (grpci considers BAR==0 as invalid) */
        addr = ((~flip_dword(addr))+1)>>1;                             /* page0 is accessed through upper half of bar0 */
        LEON3_BYPASS_STORE_PA( &pcic->regs->cfg_stat , 0x10000000);    /* Setup mmap reg so we can reach bar0 */ 
        LEON3_BYPASS_STORE_PA( pcic->mem_resource.start+addr, 0);      /* Disable bytetwisting ... */
#endif

        /* set 1:1 mapping between AHB -> PCI memory */
        LEON3_BYPASS_STORE_PA( &pcic->regs->cfg_stat , (pcic->mem_resource.start & 0xf0000000));

        /* and map system RAM at pci address 0x40000000 */ 
        pcic_write_config_dword(0, 0, 0x14, 0x40000000);
        LEON3_BYPASS_STORE_PA( &pcic->regs->page1 , 0x40000000);

        /* set 1:1 mapping between AHB -> PCI io */
        LEON3_BYPASS_STORE_PA( &pcic->regs->iomap , (pcic->io_base_pa & 0xffff0000));  

        /* set as bus master and enable pci memory responses */  
        pcic_read_config_dword(0, 0, 0x4, &data);
        pcic_write_config_dword(0, 0, 0x4, data | 0x6);
	
	/* Route all PCI INTs to system interrupt controller */
	LEON3_BYPASS_STORE_PA(&pcic->regs->irq, 0xf0000);

	if (request_resource(&iomem_resource, &pcic->mem_resource) < 0)
            goto out;
        if (request_resource(&ioport_resource, &pcic->io_resource) < 0)
            goto out_free_mem_resource;

    	pcic->bus = pci_scan_bus(0, &pcic_ops, pcic);

        printk("Assigning PCI BARs.\n");
	pci_assign_unassigned_resources();

        return 0;

out_free_mem_resource:
		release_resource(&pcic->mem_resource);

out:
		printk(KERN_WARNING
		       "Skipping PCI bus scan due to resource conflict\n");
	return 0;
}


/*
 * Normally called from {do_}pci_scan_bus...
 */
void __init pcibios_fixup_bus(struct pci_bus *bus)
{
	struct pci_dev *dev;
	int i, has_io, has_mem;
	unsigned int cmd;
	struct leon_pci *pcic;

	pcic = &pcic0;
	
        /* Generic PCI bus probing sets these to point at
	 * &io{port,mem}_resouce which is wrong for us.
	 */
        bus->resource[0] = &pcic->io_resource;
        bus->resource[1] = &pcic->mem_resource;

     	list_for_each_entry(dev, &bus->devices, bus_list) {

		/*
		 * Comment from i386 branch:
		 *     There are buggy BIOSes that forget to enable I/O and memory
		 *     access to PCI devices. We try to fix this, but we need to
		 *     be sure that the BIOS didn't forget to assign an address
		 *     to the device. [mj]
		 * OBP is a case of such BIOS :-)
		 */
		has_io = has_mem = 0;
		for(i=0; i<6; i++) {

			unsigned long f = dev->resource[i].flags;
			if (f & IORESOURCE_IO) {
				has_io = 1;
			} else if (f & IORESOURCE_MEM)
				has_mem = 1;
		}
		pcic_read_config(dev->bus, dev->devfn, PCI_COMMAND, 2, &cmd);
		if (has_io && !(cmd & PCI_COMMAND_IO)) {
			printk("PCIC: Enabling I/O for device %02x:%02x\n",
				dev->bus->number, dev->devfn);
			cmd |= PCI_COMMAND_IO;
			pcic_write_config(dev->bus, dev->devfn,
			    PCI_COMMAND, 2, cmd);
		}
		if (has_mem && !(cmd & PCI_COMMAND_MEMORY)) {
			printk("PCIC: Enabling memory for device %02x:%02x\n",
				dev->bus->number, dev->devfn);
			cmd |= PCI_COMMAND_MEMORY;
			pcic_write_config(dev->bus, dev->devfn,
			    PCI_COMMAND, 2, cmd);
		}

           
                /* All slots routed to one irq */
		dev->irq = pcic->irq;
	}
}

/*
 * We need to avoid collisions with `mirrored' VGA ports
 * and other strange ISA hardware, so we always want the
 * addresses to be allocated in the 0x000-0x0ff region
 * modulo 0x400.
 *
 * Why? Because some silly external IO cards only decode
 * the low 10 bits of the IO address. The 0x00-0xff region
 * is reserved for motherboard devices that decode all 16
 * bits, so it's ok to allocate at, say, 0x2800-0x28ff,
 * but we want to try to avoid allocating at 0x2900-0x2bff
 * which might have be mirrored at 0x0100-0x03ff..
 */
void
pcibios_align_resource(void *data, struct resource *res,
		       resource_size_t size, resource_size_t align)
{
	struct pci_dev *dev = data;
	struct leon_pci *pcic = dev->sysdata;
	unsigned long start = res->start;

	if (res->flags & IORESOURCE_IO) {
		/* Make sure we start at our min on all hoses */
		if (start < PCIBIOS_MIN_IO + pcic->io_resource.start)
			start = PCIBIOS_MIN_IO + pcic->io_resource.start;

		/*
		 * Put everything into 0x00-0xff region modulo 0x400
		 */
		if (start & 0x300)
			start = (start + 0x3ff) & ~0x3ff;
	} else if (res->flags & IORESOURCE_MEM) {
		/* Make sure we start at our min on all hoses */
		if (start < PCIBIOS_MIN_MEM + pcic->mem_resource.start)
			start = PCIBIOS_MIN_MEM + pcic->mem_resource.start;
	}

	res->start = start;
}


int pcibios_enable_device(struct pci_dev *dev, int mask)
{
	u16 cmd, old_cmd;
	int idx;
	struct resource *r;

	pci_read_config_word(dev, PCI_COMMAND, &cmd);
	old_cmd = cmd;
	for(idx=0; idx<6; idx++) {
		/* Only set up the requested stuff */
		if (!(mask & (1<<idx)))
			continue;

		r = &dev->resource[idx];
		if (!r->start && r->end) {
			printk(KERN_ERR "PCI: Device %s not available because of resource collisions\n", pci_name(dev));
			return -EINVAL;
		}
		if (r->flags & IORESOURCE_IO)
			cmd |= PCI_COMMAND_IO;
		if (r->flags & IORESOURCE_MEM)
			cmd |= PCI_COMMAND_MEMORY;
	}
	if (dev->resource[PCI_ROM_RESOURCE].start)
		cmd |= PCI_COMMAND_MEMORY;
	if (cmd != old_cmd) {
		printk("PCI: Enabling device %s (%04x -> %04x)\n", pci_name(dev), old_cmd, cmd);
		pci_write_config_word(dev, PCI_COMMAND, cmd);
	}
	return 0;
}

void pcibios_set_master(struct pci_dev *dev)
{
        u8 lat;
        pci_read_config_byte(dev, PCI_LATENCY_TIMER, &lat);
        if (lat >= 16) return;
        printk("PCI: Setting latency timer of device %s to 64\n", pci_name(dev));
        pci_write_config_byte(dev, PCI_LATENCY_TIMER, 64);
}


int pcibios_assign_resource(struct pci_dev *pdev, int resource)
{
	return -ENXIO;
}



void __init pcibios_update_irq(struct pci_dev *dev, int irq)
{
        pci_write_config_byte(dev, PCI_INTERRUPT_LINE, irq);
}

/*
 * Other archs parse arguments here.
 */
char * __init pcibios_setup(char *str)
{
	return str;
}

int pcic_present(void)
{
	return 1;
}

/*
 * This probably belongs here rather than ioport.c because
 * we do not want this crud linked into SBus kernels.
 * Also, think for a moment about likes of floppy.c that
 * include architecture specific parts. They may want to redefine ins/outs.
 *
 * We do not use horroble macroses here because we want to
 * advance pointer by sizeof(size).
 */
void outsb(unsigned long addr, const void *src, unsigned long count)
{
	while (count) {
		count -= 1;
		outb(*(const char *)src, addr);
		src += 1;
		/* addr += 1; */
	}
}

void outsw(unsigned long addr, const void *src, unsigned long count)
{
	while (count) {
		count -= 2;
		outw(*(const short *)src, addr);
		src += 2;
		/* addr += 2; */
	}
}

void outsl(unsigned long addr, const void *src, unsigned long count)
{
	while (count) {
		count -= 4;
		outl(*(const long *)src, addr);
		src += 4;
		/* addr += 4; */
	}
}

void insb(unsigned long addr, void *dst, unsigned long count)
{
	while (count) {
		count -= 1;
		*(unsigned char *)dst = inb(addr);
		dst += 1;
		/* addr += 1; */
	}
}

void insw(unsigned long addr, void *dst, unsigned long count)
{
	while (count) {
		count -= 2;
		*(unsigned short *)dst = inw(addr);
		dst += 2;
		/* addr += 2; */
	}
}

void insl(unsigned long addr, void *dst, unsigned long count)
{
	while (count) {
		count -= 4;
		/*
		 * XXX I am sure we are in for an unaligned trap here.
		 */
		*(unsigned long *)dst = inl(addr);
		dst += 4;
		/* addr += 4; */
	}
}

subsys_initcall(pcic_init);
