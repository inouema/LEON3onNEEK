/*
 * MPC83xx SPI controller driver adapted to Gaisler Research's SPI Controller
 *
 * Maintainer of original driver: Kumar Gala
 *
 * Copyright (C) 2006 Polycom, Inc.
 * Copyright (C) 2007 Gaisler Research AB.
 *
 * Adapted to Gaisler Research's MPC83xx compatible SPI controller by
 * Jan Andersson <jan@gaisler.com>. Current changes to the original driver are:
 *   Rename mpc83xx -> gr
 *   Changed dependency from fsl_devices.h to grlib_devices.h
 *   Added auto detection of slave select register
 *   Moved toggling of chip selects to the driver from external functions.
 *   Always call get_tx when the byte counter is non-zero. If the tx buffer
 *   pointer is invalid, get_tx will return 0 and the controller will continue
 *   to receive data. 
 *   added shifting of data to td and from rd when word length != 32
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 */
#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/completion.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/irq.h>
#include <linux/device.h>
#include <linux/spi/spi.h>
#include <linux/spi/spi_bitbang.h>
#include <linux/platform_device.h>
#include <linux/grlib_devices.h>

#include <asm/irq.h>
#include <asm/io.h>

/* SPI Controller registers */
struct gr_spi_reg {
	__be32 cap;
	__be32 reserved[7];
	__be32 mode;
	__be32 event;
	__be32 mask;
	__be32 command;
	__be32 transmit;
	__be32 receive;
	__be32 slvsel;
};

/* SPI Controller capability register definitions */
#define SPCAP_SSEN(x)           (((x) >> 16) & 0x1)
#define SPCAP_SSSZ(x)           (((x) >> 24) & 0xff)

/* SPI Controller mode register definitions */
#define	SPMODE_CI_INACTIVEHIGH	(1 << 29)
#define	SPMODE_CP_BEGIN_EDGECLK	(1 << 28)
#define	SPMODE_DIV16		(1 << 27)
#define	SPMODE_REV		(1 << 26)
#define	SPMODE_MS		(1 << 25)
#define	SPMODE_ENABLE		(1 << 24)
#define	SPMODE_LEN(x)		((x) << 20)
#define	SPMODE_PM(x)		((x) << 16)

/*
 * Default for SPI Mode:
 * 	SPI MODE 0 (inactive low, phase middle, MSB, 8-bit length, slow clk
 */
#define	SPMODE_INIT_VAL (SPMODE_CI_INACTIVEHIGH | SPMODE_DIV16 | SPMODE_REV | \
			 SPMODE_MS | SPMODE_LEN(7) | SPMODE_PM(0xf))

/* SPIE register values */
#define	SPIE_NE		0x00000200	/* Not empty */
#define	SPIE_NF		0x00000100	/* Not full */

/* SPIM register values */
#define	SPIM_NE		0x00000200	/* Not empty */
#define	SPIM_NF		0x00000100	/* Not full */

/* SPI Controller driver's private data. */
struct gr_spi {
	/* bitbang has to be first */
	struct spi_bitbang bitbang;
	struct completion done;

	struct gr_spi_reg __iomem *base;

	/* rx & tx bufs from the spi_transfer */
	const void *tx;
	void *rx;

	/* functions to deal with different sized buffers */
	void (*get_rx) (u32 rx_data, struct gr_spi *);
	u32(*get_tx) (struct gr_spi *);

	unsigned int count;
	u32 irq;

	unsigned nsecs;		/* (clock cycle time)/2 */

	u32 sysclk;
	unsigned int has_slvsel;
	
	unsigned int td_shift; /* Data needs to be shifted for length /= 32 */
};

static inline void gr_spi_write_reg(__be32 __iomem * reg, u32 val)
{
	out_be32(reg, val);
}

static inline u32 gr_spi_read_reg(__be32 __iomem * reg)
{
	return in_be32(reg);
}

#define GR_SPI_RX_BUF(type) 					  \
void gr_spi_rx_buf_##type(u32 data, struct gr_spi *gr_spi) \
{									  \
	type * rx = gr_spi->rx;                                    \
        if (gr_spi->td_shift)                                       \
             *rx++ = (type)(data >> 16);				     \
        else                                                   \
	     *rx++ = (type)data;		      	  \
	gr_spi->rx = rx;						  \
}

#define GR_SPI_TX_BUF(type)				\
u32 gr_spi_tx_buf_##type(struct gr_spi *gr_spi)	\
{								\
	u32 data;						\
	const type * tx = gr_spi->tx;			\
	if (!tx)						\
		return 0;					\
	data = *tx++ << gr_spi->td_shift;  		        \
	gr_spi->tx = tx;					\
	return data;						\
}

GR_SPI_RX_BUF(u8)
GR_SPI_RX_BUF(u16)
GR_SPI_RX_BUF(u32)
GR_SPI_TX_BUF(u8)
GR_SPI_TX_BUF(u16)
GR_SPI_TX_BUF(u32)

static void 
gr_spi_activate_cs(struct gr_spi *gr_spi, u8 cs, u8 polarity)
{
	unsigned int slvsel;
	slvsel = gr_spi_read_reg(&gr_spi->base->slvsel);
	slvsel = polarity ? slvsel | (1 << cs) : slvsel & ~(1 << cs);	
	gr_spi_write_reg(&gr_spi->base->slvsel, slvsel);
}

static void 
gr_spi_deactivate_cs(struct gr_spi *gr_spi, u8 cs, u8 polarity)
{
	unsigned int slvsel;
	slvsel = gr_spi_read_reg(&gr_spi->base->slvsel);
	slvsel = polarity ? slvsel & ~(1 << cs) : slvsel | (1 << cs);
	gr_spi_write_reg(&gr_spi->base->slvsel, slvsel);
}

static void gr_spi_chipselect(struct spi_device *spi, int value)
{
	struct gr_spi *gr_spi;
	u8 pol = spi->mode & SPI_CS_HIGH ? 1 : 0;

	gr_spi = spi_master_get_devdata(spi->master);

	if (value == BITBANG_CS_INACTIVE)
		if (gr_spi->has_slvsel)
			gr_spi_deactivate_cs(gr_spi, spi->chip_select, pol);

	if (value == BITBANG_CS_ACTIVE) {
		u32 regval = gr_spi_read_reg(&gr_spi->base->mode);
		u32 len = spi->bits_per_word;
		if (len == 32) {
			len = 0;
			gr_spi->td_shift = 0;
		} else {
			len = len - 1;
			gr_spi->td_shift = 31 - len;
		}
		

		/* mask out bits we are going to set */
		regval &= ~0x38ff0000;

		if (spi->mode & SPI_CPHA)
			regval |= SPMODE_CP_BEGIN_EDGECLK;
		if (spi->mode & SPI_CPOL)
			regval |= SPMODE_CI_INACTIVEHIGH;

		regval |= SPMODE_LEN(len);

		if ((gr_spi->sysclk / spi->max_speed_hz) >= 64) {
			u8 pm = gr_spi->sysclk / (spi->max_speed_hz * 64);
			regval |= SPMODE_PM(pm) | SPMODE_DIV16;
		} else {
			u8 pm = gr_spi->sysclk / (spi->max_speed_hz * 4);
			regval |= SPMODE_PM(pm);
		}

		gr_spi_write_reg(&gr_spi->base->mode, regval);
		if (gr_spi->has_slvsel)
			gr_spi_activate_cs(gr_spi, spi->chip_select, pol);
	}
}

static
int gr_spi_setup_transfer(struct spi_device *spi, struct spi_transfer *t)
{
	struct gr_spi *gr_spi;
	u32 regval;
	u8 bits_per_word;
	u32 hz;

	gr_spi = spi_master_get_devdata(spi->master);

	if (t) {
		bits_per_word = t->bits_per_word;
		hz = t->speed_hz;
	} else {
		bits_per_word = 0;
		hz = 0;
	}

	/* spi_transfer level calls that work per-word */
	if (!bits_per_word)
		bits_per_word = spi->bits_per_word;

	/* Make sure its a bit width we support [4..16, 32] */
	if ((bits_per_word < 4)
	    || ((bits_per_word > 16) && (bits_per_word != 32)))
		return -EINVAL;

	if (bits_per_word <= 8) {
		gr_spi->get_rx = gr_spi_rx_buf_u8;
		gr_spi->get_tx = gr_spi_tx_buf_u8;
	} else if (bits_per_word <= 16) {
		gr_spi->get_rx = gr_spi_rx_buf_u16;
		gr_spi->get_tx = gr_spi_tx_buf_u16;
	} else if (bits_per_word <= 32) {
		gr_spi->get_rx = gr_spi_rx_buf_u32;
		gr_spi->get_tx = gr_spi_tx_buf_u32;
	} else
		return -EINVAL;

	/* nsecs = (clock period)/2 */
	if (!hz)
		hz = spi->max_speed_hz;
	gr_spi->nsecs = (1000000000 / 2) / hz;
	if (gr_spi->nsecs > MAX_UDELAY_MS * 1000)
		return -EINVAL;

	if (bits_per_word == 32) {
		bits_per_word = 0;
		gr_spi->td_shift = 0;
	} else { 
		bits_per_word = bits_per_word - 1;
		gr_spi->td_shift = 31 - bits_per_word;
	}

	regval = gr_spi_read_reg(&gr_spi->base->mode);

	/* Mask out bits_per_wordgth */
	regval &= 0xff0fffff;
	regval |= SPMODE_LEN(bits_per_word);

	gr_spi_write_reg(&gr_spi->base->mode, regval);

	return 0;
}

static int gr_spi_setup(struct spi_device *spi)
{
	struct spi_bitbang *bitbang;
	struct gr_spi *gr_spi;
	int retval;

	if (!spi->max_speed_hz)
		return -EINVAL;

	bitbang = spi_master_get_devdata(spi->master);
	gr_spi = spi_master_get_devdata(spi->master);

	if (!spi->bits_per_word)
		spi->bits_per_word = 8;

	retval = gr_spi_setup_transfer(spi, NULL);
	if (retval < 0)
		return retval;

	dev_dbg(&spi->dev, "%s, mode %d, %u bits/w, %u nsec\n",
		__FUNCTION__, spi->mode & (SPI_CPOL | SPI_CPHA),
		spi->bits_per_word, 2 * gr_spi->nsecs);

	/* NOTE we _need_ to call chipselect() early, ideally with adapter
	 * setup, unless the hardware defaults cooperate to avoid confusion
	 * between normal (active low) and inverted chipselects.
	 */

	/* deselect chip (low or high) */
	spin_lock(&bitbang->lock);
	if (!bitbang->busy) {
		bitbang->chipselect(spi, BITBANG_CS_INACTIVE);
		ndelay(gr_spi->nsecs);
	}
	spin_unlock(&bitbang->lock);

	return 0;
}

static int gr_spi_bufs(struct spi_device *spi, struct spi_transfer *t)
{
	struct gr_spi *gr_spi;
	u32 word;

	gr_spi = spi_master_get_devdata(spi->master);

	gr_spi->tx = t->tx_buf;
	gr_spi->rx = t->rx_buf;
	gr_spi->count = t->len;
	INIT_COMPLETION(gr_spi->done);

	/* enable rx ints */
	gr_spi_write_reg(&gr_spi->base->mask, SPIM_NE);

	/* transmit word */
	word = gr_spi->get_tx(gr_spi);
	gr_spi_write_reg(&gr_spi->base->transmit, word);

	wait_for_completion(&gr_spi->done);

	/* disable rx ints */
	gr_spi_write_reg(&gr_spi->base->mask, 0);

	return t->len - gr_spi->count;
}

irqreturn_t gr_spi_irq(s32 irq, void *context_data)
{
	struct gr_spi *gr_spi = context_data;
	u32 event;
	irqreturn_t ret = IRQ_NONE;

	/* Get interrupt events(tx/rx) */
	event = gr_spi_read_reg(&gr_spi->base->event);

	/* We need handle RX first */
	if (event & SPIE_NE) {
		u32 rx_data = gr_spi_read_reg(&gr_spi->base->receive);
		if (gr_spi->rx) 
			gr_spi->get_rx(rx_data, gr_spi);
		ret = IRQ_HANDLED;
	}

	if ((event & SPIE_NF) == 0)
		/* spin until TX is done */
		while (((event =
			 gr_spi_read_reg(&gr_spi->base->event)) &
						SPIE_NF) == 0)
			cpu_relax();
     
	gr_spi->count -= 1;
	if (gr_spi->count) {
		u32 word = gr_spi->get_tx(gr_spi);
		gr_spi_write_reg(&gr_spi->base->transmit, word);

	} else {
		complete(&gr_spi->done);
	}

	/* Clear the events */
	gr_spi_write_reg(&gr_spi->base->event, event);

	return ret;
}

static int __init gr_spi_probe(struct platform_device *dev)
{
	struct spi_master *master;
	struct gr_spi *gr_spi;
	struct grlib_spictrl_platform_data *pdata;
	struct resource *r;
	u32 regval;
	int ret = 0;

	/* Get resources(memory, IRQ) associated with the device */
	master = spi_alloc_master(&dev->dev, sizeof(struct gr_spi));

	if (master == NULL) {
		ret = -ENOMEM;
		goto err;
	}

	platform_set_drvdata(dev, master);
	pdata = dev->dev.platform_data;

	if (pdata == NULL) {
		ret = -ENODEV;
		goto free_master;
	}

	r = platform_get_resource(dev, IORESOURCE_MEM, 0);
	if (r == NULL) {
		ret = -ENODEV;
		goto free_master;
	}

	gr_spi = spi_master_get_devdata(master);
	gr_spi->bitbang.master = spi_master_get(master);
	gr_spi->bitbang.chipselect = gr_spi_chipselect;
	gr_spi->bitbang.setup_transfer = gr_spi_setup_transfer;
	gr_spi->bitbang.txrx_bufs = gr_spi_bufs;
	gr_spi->sysclk = pdata->sysclk;
	gr_spi->get_rx = gr_spi_rx_buf_u8;
	gr_spi->get_tx = gr_spi_tx_buf_u8;

	gr_spi->bitbang.master->setup = gr_spi_setup;
	init_completion(&gr_spi->done);

	gr_spi->base = ioremap(r->start, r->end - r->start + 1);
	if (gr_spi->base == NULL) {
		ret = -ENOMEM;
		goto put_master;
	}

	gr_spi->irq = platform_get_irq(dev, 0);

	if (gr_spi->irq < 0) {
		ret = -ENXIO;
		goto unmap_io;
	}

	/* Register for SPI Interrupt */
	ret = request_irq(gr_spi->irq, gr_spi_irq,
			  0, "gr_spi", gr_spi);

	if (ret != 0)
		goto unmap_io;

	master->bus_num = pdata->bus_num;

	/* Read capability register to get chip select info */
	regval = gr_spi_read_reg(&gr_spi->base->cap);
	gr_spi->has_slvsel = SPCAP_SSEN(regval);
	if (gr_spi->has_slvsel)
		master->num_chipselect = SPCAP_SSSZ(regval);
	else
		master->num_chipselect = 0;

	/* SPI controller initializations */
	gr_spi_write_reg(&gr_spi->base->mode, 0);
	gr_spi_write_reg(&gr_spi->base->mask, 0);
	gr_spi_write_reg(&gr_spi->base->command, 0);	
	gr_spi_write_reg(&gr_spi->base->event, 0xffffffff);
	gr_spi_write_reg(&gr_spi->base->slvsel, 0xffffffff);

	/* Enable SPI interface */
	regval = pdata->initial_spmode | SPMODE_INIT_VAL | SPMODE_ENABLE;
	gr_spi_write_reg(&gr_spi->base->mode, regval);

	ret = spi_bitbang_start(&gr_spi->bitbang);

	if (ret != 0)
		goto free_irq;

	printk(KERN_INFO
	       "%s: Gaisler Research SPI Controller driver at 0x%p (irq = %d)\n",
	       dev->dev.bus_id, gr_spi->base, gr_spi->irq);

	return ret;

free_irq:
	free_irq(gr_spi->irq, gr_spi);
unmap_io:
	iounmap(gr_spi->base);
put_master:
	spi_master_put(master);
free_master:
	kfree(master);
err:
	return ret;
}

static int __devexit gr_spi_remove(struct platform_device *dev)
{
	struct gr_spi *gr_spi;
	struct spi_master *master;

	master = platform_get_drvdata(dev);
	gr_spi = spi_master_get_devdata(master);

	spi_bitbang_stop(&gr_spi->bitbang);
	free_irq(gr_spi->irq, gr_spi);
	iounmap(gr_spi->base);
	spi_master_put(gr_spi->bitbang.master);

	return 0;
}

static struct platform_driver gr_spi_driver = {
	.probe = gr_spi_probe,
	.remove = __devexit_p(gr_spi_remove),
	.driver = {
		   .name = "gr_spi",
	},
};

static int __init gr_spi_init(void)
{
	return platform_driver_register(&gr_spi_driver);
}

static void __exit gr_spi_exit(void)
{
	platform_driver_unregister(&gr_spi_driver);
}

module_init(gr_spi_init);
module_exit(gr_spi_exit);

MODULE_AUTHOR("Kumar Gala");
MODULE_DESCRIPTION("MPC83xx/GRLIB SPI Driver");
MODULE_LICENSE("GPL");
