/*
 * Platform device support for OC I2C-master for Leon SoC systems.
 * Based on: FSL SoC setup code, maintained by Kumar Gala 
 * Modified by: Jan Andersson <jan@gaisler.com>
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 */

#include <linux/platform_device.h>
#include <linux/i2c-ocores.h>

#include <asm/oplib.h>

#include <asm/leon.h>

#ifdef CONFIG_LEON

#define I2C_APB_SPACE_LENGTH 256

static struct ocores_i2c_platform_data gri2c_pdata;

static int __init gri2c_platform_init(void)
{
	int node;
	unsigned int i;
	unsigned int devcnt;
	struct platform_device *i2cdev = NULL;
	amba_apb_device ai2c;
	int retval = 0;
	struct resource ri2c[2];

	devcnt = amba_get_number_apbslv_devices(VENDOR_GAISLER, GAISLER_I2CMST);

	node = prom_getchild(prom_root_node);
	gri2c_pdata.clock_khz = prom_getint(node, "clock-frequency");
	gri2c_pdata.regstep = 4;
		
	for (i = 0; i < devcnt; i++) {
		memset(&ri2c,0,sizeof(ri2c));
		if (!amba_get_free_apbslv_devices(
			    VENDOR_GAISLER,GAISLER_I2CMST, &ai2c, 1)) {
			retval = -ENODEV;
			break;
		}

		ri2c[0].start = ai2c.start;
		ri2c[0].end = ai2c.start + I2C_APB_SPACE_LENGTH - 1;
		ri2c[0].flags = IORESOURCE_MEM;

		ri2c[1].start = ri2c[1].end = ai2c.irq;
		ri2c[1].flags = IORESOURCE_IRQ;
	  
		i2cdev = platform_device_register_simple(
			"ocores-i2c",i,ri2c,2);
		i2cdev->dev.platform_data = &gri2c_pdata;
	}
	
	if (devcnt == 0) {
	  retval = -ENODEV;
	};

	return retval;
}


arch_initcall(gri2c_platform_init);

#endif
