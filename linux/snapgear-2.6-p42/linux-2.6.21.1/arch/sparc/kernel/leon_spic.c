/*
 * Platform device support for GRLIB SPI controller for Leon SoC systems.
 * Based on: FSL SoC setup code, maintained by Kumar Gala 
 * Modified by: Jan Andersson <jan@gaisler.com>
 *
 * This file contains both the SoC specific code and declarations of slave
 * devices. Currently there is no board specific initalization code for
 * GRLIB/Leon systems. Each user tailors her/his own system and the SPI 
 * support may require some manual tweaking of the code below....
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 */

#include <linux/grlib_devices.h>
#include <linux/platform_device.h>
#include <linux/spi/spi.h>
#include <linux/spi/flash.h>

#include <asm/oplib.h>

#include <asm/leon.h>

#ifdef CONFIG_LEON

#define SPI_APB_SPACE_LENGTH 256

/* SPI devices */
#ifdef CONFIG_MTD_M25P80
static struct flash_platform_data m25pxx_info = {
	.name = NULL,
	.parts = NULL,
	.nr_parts = 0,
	.type = "m25p05", /* Is this the M25Pxx device on your board? */
};
#endif

/* List of SPI devices present on this board */
static struct spi_board_info spi_board_info[] __initdata = {
#ifdef CONFIG_MTD_M25P80
{
	.modalias	= "m25p80",
	.platform_data	= &m25pxx_info,
	.mode		= SPI_MODE_0,
	.irq		= 0,
	.max_speed_hz	= 10000 /* max sample rate at 3V */ * 16,
	.bus_num	= 1,
	.chip_select	= 0, /* Chip/Slave select line, change if necessary */
},
#endif
};

static struct grlib_spictrl_platform_data grspi_pdata;

static int __init grspi_platform_init(void)
{
	int node;
	unsigned int i;
	unsigned int devcnt;
	struct platform_device *spidev = NULL;
	amba_apb_device aspi;
	int retval = 0;
	struct resource rspi[2];

	spi_register_board_info(spi_board_info, ARRAY_SIZE(spi_board_info));

	devcnt = amba_get_number_apbslv_devices(VENDOR_GAISLER, GAISLER_SPICTRL);

	node = prom_getchild(prom_root_node);
	grspi_pdata.initial_spmode = 0;
	grspi_pdata.sysclk = prom_getint(node, "clock-frequency");
		
	for (i = 0; i < devcnt; i++) {
		memset(&rspi,0,sizeof(rspi));
		if (!amba_get_free_apbslv_devices(
			    VENDOR_GAISLER,GAISLER_SPICTRL, &aspi, 1)) {
			retval = -ENODEV;
			break;
		}

		grspi_pdata.bus_num = i+1;
		
		rspi[0].start = aspi.start;
		rspi[0].end = aspi.start + SPI_APB_SPACE_LENGTH - 1;
		rspi[0].flags = IORESOURCE_MEM;

		rspi[1].start = rspi[1].end = aspi.irq;
		rspi[1].flags = IORESOURCE_IRQ;
	  
		spidev = platform_device_register_simple(
			"gr_spi",i,rspi,2);
		spidev->dev.platform_data = &grspi_pdata;
	}
	
	if (devcnt == 0) {
		retval = -ENODEV;
	} 
	
	return retval;
}


arch_initcall(grspi_platform_init);

#endif
