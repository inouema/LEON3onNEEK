/*
 * include/linux/grlib_devices.h
 *
 * Definitions for devices in Gaisler Research's IP Core Library GRLIB
 *
 * This program is free software; you can redistribute it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#ifdef __KERNEL__
#ifndef _GRLIB_DEVICE_H_
#define _GRLIB_DEVICE_H_

#include <linux/types.h>

/* Initialization data for SPICTRL driver, based on MPC83xx */
struct grlib_spictrl_platform_data {
	u32 	initial_spmode;	/* initial SPMODE value */
	u16	bus_num;

	/* board specific information */
	u32	sysclk;
};

#endif
#endif
