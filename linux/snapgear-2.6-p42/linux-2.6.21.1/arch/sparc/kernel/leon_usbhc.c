/*
 * Platform device support for GRUSBHC for Leon SoC systems.
 * Based on: FSL SoC setup code, maintained by Kumar Gala 
 * Modified by: Jan Andersson
 *
 * FIXME: unregister drivers on failure
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 */

#include <linux/platform_device.h>

#include <asm/leon.h>

#ifdef CONFIG_LEON

#define GRUSBHC_APB_SPACE_LENGTH 256
#define GRUSBHC_AHB_SPACE_LENGTH 256

static int __init grusbhc_platform_init(void)
{
	unsigned int i;
	unsigned int devcnt;
	struct platform_device *grusbhc_uhci = NULL, *grusbhc_ehci = NULL;
	amba_apb_device ehc;
	amba_ahb_device uhc;
	int retval = 0;
	struct resource ruhc[2];
	struct resource rehc[2];

	/* Try to locate GRUSBHC 1.1 controllers */
	devcnt = amba_get_number_ahbslv_devices(VENDOR_GAISLER, GAISLER_USBUHC);

	for (i = 0; i < devcnt; i++) {
		memset(&ruhc,0,sizeof(ruhc));
		if (!amba_get_free_ahbslv_devices(
			    VENDOR_GAISLER,GAISLER_USBUHC, &uhc, 1)) {
			retval = -ENODEV;
			break;
		}
		ruhc[0].start = uhc.start[0];
		ruhc[0].end = uhc.start[0] + GRUSBHC_AHB_SPACE_LENGTH - 1;
		ruhc[0].flags = IORESOURCE_MEM;

		ruhc[1].start = ruhc[1].end = uhc.irq;
		ruhc[1].flags = IORESOURCE_IRQ;
	  
		grusbhc_uhci = 
			platform_device_register_simple("grusbhc-uhci",i,ruhc,2);
	
		grusbhc_uhci->dev.coherent_dma_mask =  0xffffffffUL;
		grusbhc_uhci->dev.dma_mask = 
			&grusbhc_uhci->dev.coherent_dma_mask;
	}
	
	if (devcnt == 0) {
	  retval = -ENODEV;
	};

	/* Try to locate GRUSBHC 2.0 controllers */
	
	devcnt = amba_get_number_apbslv_devices(VENDOR_GAISLER, GAISLER_USBEHC);
	
	for (i = 0; i < devcnt; i++) {
		memset(&rehc,0,sizeof(rehc));
		if (!amba_get_free_apbslv_devices(
			    VENDOR_GAISLER,GAISLER_USBEHC,&ehc,1)) {
			retval = -ENODEV;
			break;
		}
		rehc[0].start =  ehc.start;
		rehc[0].end = ehc.start + GRUSBHC_APB_SPACE_LENGTH - 1;
		rehc[0].flags = IORESOURCE_MEM;
		rehc[1].start = rehc[1].end = ehc.irq;
		rehc[1].flags = IORESOURCE_IRQ;
	  
		grusbhc_ehci = 
			platform_device_register_simple("grusbhc-ehci",i,rehc,2);
		
		grusbhc_ehci->dev.coherent_dma_mask = 0xffffffffUL;
		grusbhc_ehci->dev.dma_mask = 
			&grusbhc_ehci->dev.coherent_dma_mask;
	}
	if (devcnt == 0 && retval == -ENODEV) {
	  retval = -ENODEV;
	};

	return retval;
 
}


arch_initcall(grusbhc_platform_init);

#endif
