#ifndef __SPARC_LEON_PCI_H
#define __SPARC_LEON_PCI_H

#ifndef __ASSEMBLY__

#include <linux/types.h>
#include <linux/smp.h>
#include <linux/pci.h>
#include <linux/ioport.h>
#include <asm/leon.h>

#define GRPCI_CTO 0x100

struct leon_pci {

        LEON3_GRPCI_Regs_Map    *regs;
        int                     irq;

        struct resource         mem_resource;
        struct resource         io_resource;
        unsigned long           io_base_pa;
        unsigned long           io_base_va;

        struct pci_bus          *bus;
      
};

extern struct leon_pci pcic0;

#endif




#endif /* !(__SPARC_LEON_PCI_H) */
