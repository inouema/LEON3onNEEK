/*
 * Platform device support for Xilinx System ACE for Leon SoC systems.
 * Based on: FSL SoC setup code, maintained by Kumar Gala 
 * Modified by: Jan Andersson <jan@gaisler.com>
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 */

#include <linux/platform_device.h>

#include <asm/leon.h>

#ifdef CONFIG_LEON

#define GRACE_AHB_SPACE_LENGTH 256


static int __init gracectrl_platform_init(void)
{
	int node;
	unsigned int i;
	unsigned int devcnt;
	struct platform_device *acedev = NULL;
	amba_ahb_device grace;
	int retval = 0;
	struct resource rgrace[2];

	devcnt = amba_get_number_ahbslv_devices(VENDOR_GAISLER, GAISLER_GRACECTRL);

		
	for (i = 0; i < devcnt; i++) {
		memset(&rgrace,0,sizeof(rgrace));
		if (!amba_get_free_ahbslv_devices(
			    VENDOR_GAISLER, GAISLER_GRACECTRL, &grace, 1)) {
			retval = -ENODEV;
			break;
		}

		rgrace[0].start = grace.start[0];
		rgrace[0].end = grace.start[0] + GRACE_AHB_SPACE_LENGTH - 1;
		rgrace[0].flags = IORESOURCE_MEM;

		rgrace[1].start = rgrace[1].end = grace.irq;
		rgrace[1].flags = IORESOURCE_IRQ;
	  
		acedev = platform_device_register_simple(
                               "xsysace",i,rgrace,2);
	}
	
	if (devcnt == 0) {
	  retval = -ENODEV;
	};

	return retval;
}


arch_initcall(gracectrl_platform_init);

#endif
