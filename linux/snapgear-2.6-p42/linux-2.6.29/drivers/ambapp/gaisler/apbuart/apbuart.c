/*
 *  linux/drivers/serial/leon.c
 *
 *  Driver for Leon serial ports
 *
 *  Based on linux/drivers/serial/amba.c , Documentation/serial/driver
 * 
 *  Copyright 1999 ARM Limited
 *  Copyright (C) 2000 Deep Blue Solutions Ltd.
 * 
 *  Modified for Leon by Konrad Eisele <eiselekd@web.de>, 2003
 *  Modified for linux 2.6.18 by Daniel Hellström <daniel@gaisler.com>, 2006
 *  Modified by Gilead Kutnick <kutnickg@zin-tech.com>, 2008
 */

#include <linux/module.h>
#include <linux/tty.h>
#include <linux/ioport.h>
#include <linux/init.h>
#include <linux/serial.h>
#include <linux/console.h>
#include <linux/sysrq.h>
#include <linux/kthread.h>
#include <linux/device.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>

#include <asm/io.h>
#include <asm/irq.h>
#include <asm/oplib.h>


#if defined(CONFIG_GRLIB_GAISLER_APBUART_CONSOLE) && defined(CONFIG_MAGIC_SYSRQ)
#define SUPPORT_SYSRQ
#endif

#include <linux/serial_core.h>
#include <asm/leon.h>
#include "../../amba.h"
#include "../../ambapp.h"

#define UART_NR		8
int leon_ports_nr = 0;

#define SERIAL_LEON_MAJOR	TTY_MAJOR
#define SERIAL_LEON_MINOR	64
#define SERIAL_LEON_NR		UART_NR

#define AMBA_ISR_PASS_LIMIT	256

#define APBBASE(port) ((LEON3_APBUART_Regs_Map *)((port)->membase))

#define APBBASE_DATA_P(port) (&(APBBASE(port)->data))
#define APBBASE_STATUS_P(port) (&(APBBASE(port)->status))
#define APBBASE_CTRL_P(port) (&(APBBASE(port)->ctrl))
#define APBBASE_SCALAR_P(port) (&(APBBASE(port)->scaler))

#define UART_GET_CHAR(port)	(LEON_BYPASS_LOAD_PA(APBBASE_DATA_P(port)))
#define UART_PUT_CHAR(port, v)	(LEON_BYPASS_STORE_PA(APBBASE_DATA_P(port),v))
#define UART_GET_STATUS(port)	(LEON_BYPASS_LOAD_PA(APBBASE_STATUS_P(port)))
#define UART_PUT_STATUS(port,v)	(LEON_BYPASS_STORE_PA(APBBASE_STATUS_P(port),v))
#define UART_GET_CTRL(port)   (LEON_BYPASS_LOAD_PA(APBBASE_CTRL_P(port)))
#define UART_PUT_CTRL(port,v) (LEON_BYPASS_STORE_PA(APBBASE_CTRL_P(port),v))
#define UART_GET_SCAL(port)   (LEON_BYPASS_LOAD_PA(APBBASE_SCALAR_P(port)))
#define UART_PUT_SCAL(port,v) (LEON_BYPASS_STORE_PA(APBBASE_SCALAR_P(port),v))
#define UART_RX_DATA(s)       (((s) & LEON_REG_UART_STATUS_DR) != 0)
#define UART_TX_READY(s)	(((s) & LEON_REG_UART_STATUS_THE) != 0)

#define UART_DUMMY_RSR_RX	0x8000	/* for ignore all read */

/* We wrap our port structure around the generic uart_port */
struct uart_leon_port {
	struct uart_port port;
	unsigned int old_status;
};

static void leonuart_stop_tx(struct uart_port *port/*, unsigned int tty_stop*/)
{
	unsigned int cr;

	cr = UART_GET_CTRL(port);
	cr &= ~LEON_REG_UART_CTRL_TI;
	UART_PUT_CTRL(port, cr);
}

//static 
void leonuart_tx_chars(struct uart_port *port);
static void leonuart_start_tx(struct uart_port *port/*, unsigned int tty_start*/)
{
	unsigned int cr;

	cr = UART_GET_CTRL(port);
	cr |= LEON_REG_UART_CTRL_TI;
	UART_PUT_CTRL(port, cr);

	if (UART_GET_STATUS(port) & LEON_REG_UART_STATUS_THE) {
		leonuart_tx_chars(port);
	}
}

static void leonuart_stop_rx(struct uart_port *port)
{
	unsigned int cr;

	cr = UART_GET_CTRL(port);
	cr &= ~(LEON_REG_UART_CTRL_RI);
	UART_PUT_CTRL(port, cr);
}

static void leonuart_enable_ms(struct uart_port *port)
{
	/* no modem status for leon */
}

//static 
void
#ifdef SUPPORT_SYSRQ
leonuart_rx_chars(struct uart_port *port, struct pt_regs *regs)
#else
leonuart_rx_chars(struct uart_port *port)
#endif
{
	struct tty_struct *tty = port->info->port.tty;
	unsigned int status, ch, rsr, flag;
	unsigned int max_chars = port->fifosize;

	status = UART_GET_STATUS(port);
	while (UART_RX_DATA(status) && (max_chars--)) {
		/*
		if (tty->flip.count >= TTY_FLIPBUF_SIZE) {
			tty->flip.work.func((void *)tty);
			if (tty->flip.count >= TTY_FLIPBUF_SIZE) {
				printk(KERN_WARNING "TTY_DONT_FLIP set\n");
				return;
			}
		}
		*/
		ch = UART_GET_CHAR(port);
		flag = TTY_NORMAL;
		
		/**tty->flip.char_buf_ptr = ch;
		*tty->flip.flag_buf_ptr = TTY_NORMAL;*/
		port->icount.rx++;

		/*
		 * Note that the error handling code is
		 * out of the main execution path
		 */
		rsr = UART_GET_STATUS(port) | UART_DUMMY_RSR_RX;
		UART_PUT_STATUS(port, 0);
		if (rsr & LEON_REG_UART_STATUS_ERR) {

			if (rsr & LEON_REG_UART_STATUS_BR) {
				rsr &=
				    ~(LEON_REG_UART_STATUS_FE |
				      LEON_REG_UART_STATUS_PE);
				port->icount.brk++;
				if (uart_handle_break(port))
					goto ignore_char;
			} else if (rsr & LEON_REG_UART_STATUS_PE) {
				port->icount.parity++;
			} else if (rsr & LEON_REG_UART_STATUS_FE) {
				port->icount.frame++;
			}
			if (rsr & LEON_REG_UART_STATUS_OE)
				port->icount.overrun++;

			rsr &= port->read_status_mask;
/*
			if (rsr & LEON_REG_UART_STATUS_PE)
				*tty->flip.flag_buf_ptr = TTY_PARITY;
			else if (rsr & LEON_REG_UART_STATUS_FE)
				*tty->flip.flag_buf_ptr = TTY_FRAME;
				*/
			if (rsr & LEON_REG_UART_STATUS_PE)
				flag = TTY_PARITY;
			else if (rsr & LEON_REG_UART_STATUS_FE)
				flag = TTY_FRAME;
		}

		if (uart_handle_sysrq_char(port, ch))
			goto ignore_char;
/*
		if ((rsr & port->ignore_status_mask) == 0) {
			tty->flip.flag_buf_ptr++;
			tty->flip.char_buf_ptr++;
			tty->flip.count++;
		}
		*/
		if ((rsr & port->ignore_status_mask) == 0) {
			tty_insert_flip_char(tty, ch, flag);
		}
		
		if ( rsr & LEON_REG_UART_STATUS_OE ) {
			/*
			 * Overrun is special, since it's reported
			 * immediately, and doesn't affect the current
			 * character
			 */
			tty_insert_flip_char(tty, 0, TTY_OVERRUN);
		}
      ignore_char:
		status = UART_GET_STATUS(port);
	}
	tty_flip_buffer_push(tty);
	return;
}

//static 
void leonuart_tx_chars(struct uart_port *port)
{
	struct circ_buf *xmit = &port->info->xmit;
	int count;

	if (port->x_char) {
		UART_PUT_CHAR(port, port->x_char);
		port->icount.tx++;
		port->x_char = 0;
		return;
	}
	if (uart_circ_empty(xmit) || uart_tx_stopped(port)) {
		leonuart_stop_tx(port);
		return;
	}

	count = port->fifosize >> 1;	//amba: fill FIFO
	do {
		UART_PUT_CHAR(port, xmit->buf[xmit->tail]);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
		if (uart_circ_empty(xmit))
			break;
	} while (--count > 0);

	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(port);

	if (uart_circ_empty(xmit))
		leonuart_stop_tx(port);
}

//static
#ifdef SUPPORT_SYSRQ
irqreturn_t leonuart_int(int irq, void *dev_id, struct pt_regs *regs)
#else
irqreturn_t leonuart_int(int irq, void *dev_id)
#endif
{
	struct uart_port *port = dev_id;
	unsigned int status;

	spin_lock(&port->lock);

	status = UART_GET_STATUS(port);
	if (status & LEON_REG_UART_STATUS_DR) {
#ifdef SUPPORT_SYSRQ
		leonuart_rx_chars(port, regs);
#else
		leonuart_rx_chars(port);
#endif
	}
	if (status & LEON_REG_UART_STATUS_THE) {
		leonuart_tx_chars(port);
	}
	spin_unlock(&port->lock);
	return IRQ_HANDLED;
}

static unsigned int leonuart_tx_empty(struct uart_port *port)
{
	return UART_GET_STATUS(port) & LEON_REG_UART_STATUS_THE ? TIOCSER_TEMT :
	    0;
}

static unsigned int leonuart_get_mctrl(struct uart_port *port)
{
	unsigned int result = 0;

	/*
	   no modem status for leon
	 */

	return result;
}

static void leonuart_set_mctrl(struct uart_port *port, unsigned int mctrl)
{
	/* no modem status for leon */
}

static void leonuart_break_ctl(struct uart_port *port, int break_state)
{
	/* no break for leon */
}

static int leonuart_startup(struct uart_port *port)
{
	struct uart_leon_port *uap = (struct uart_leon_port *)port;
	int retval;
	unsigned int cr;

	/*
	 * Allocate the IRQ
	 */
	retval = request_irq(port->irq, leonuart_int, 0, "leon", port);
	if (retval)
		return retval;

	/*
	 * initialise the old status of the modem signals
	 */
	uap->old_status = 0;

	/*
	 * Finally, enable interrupts
	 */
	cr = UART_GET_CTRL(port);
	UART_PUT_CTRL(port,
		      cr | LEON_REG_UART_CTRL_RE | LEON_REG_UART_CTRL_TE |
		      LEON_REG_UART_CTRL_RI | LEON_REG_UART_CTRL_TI);

	return 0;
}

static void leonuart_shutdown(struct uart_port *port)
{
	unsigned int cr;

  /*
	 * disable all interrupts, disable the port
	 */
	cr = UART_GET_CTRL(port);
	UART_PUT_CTRL(port,
		      cr & ~(LEON_REG_UART_CTRL_RE | LEON_REG_UART_CTRL_TE |
			     LEON_REG_UART_CTRL_RI | LEON_REG_UART_CTRL_TI));

	/*
	 * Free the interrupt
	 */
	free_irq(port->irq, port);
}

static void
leonuart_set_termios(struct uart_port *port, struct ktermios *termios,
		     struct ktermios *old)
{
	unsigned int cr;
	unsigned long flags;
	unsigned int baud, quot;

	/*
	 * Ask the core to calculate the divisor for us.
	 */
	baud = uart_get_baud_rate(port, termios, old, 0, port->uartclk / 16);
	if (baud == 0) {
		panic("invalid baudrate %i\n", port->uartclk / 16);
	}
	quot = (uart_get_divisor(port, baud)) * 2;	//uart_get_divisor calc a *16 uart freq, leon is *8
	cr = UART_GET_CTRL(port);
	cr &= ~(LEON_REG_UART_CTRL_PE | LEON_REG_UART_CTRL_PS);

	if (termios->c_cflag & PARENB) {
		cr |= LEON_REG_UART_CTRL_PE;
		if ((termios->c_cflag & PARODD))
			cr |= LEON_REG_UART_CTRL_PS;
	}

	/*
 	 * Enable flow control.
 	 */

	if (termios->c_cflag & CRTSCTS) {
		cr |= LEON_REG_UART_CTRL_FL;
	}

	spin_lock_irqsave(&port->lock, flags);

	/*
	 * Update the per-port timeout.
	 */
	uart_update_timeout(port, termios->c_cflag, baud);

	port->read_status_mask = LEON_REG_UART_STATUS_OE;
	if (termios->c_iflag & INPCK)
		port->read_status_mask |=
		    LEON_REG_UART_STATUS_FE | LEON_REG_UART_STATUS_PE;

	/*
	 * Characters to ignore
	 */
	port->ignore_status_mask = 0;
	if (termios->c_iflag & IGNPAR)
		port->ignore_status_mask |=
		    LEON_REG_UART_STATUS_FE | LEON_REG_UART_STATUS_PE;

	/*
	 * Ignore all characters if CREAD is not set.
	 */
	if ((termios->c_cflag & CREAD) == 0) {
		port->ignore_status_mask |= UART_DUMMY_RSR_RX;
	}

	/* Set baud rate */
	quot -= 1;
	UART_PUT_SCAL(port, quot);
	UART_PUT_CTRL(port, cr);

	spin_unlock_irqrestore(&port->lock, flags);
}

static const char *leonuart_type(struct uart_port *port)
{
	return port->type == PORT_LEON ? "Leon" : NULL;
}

/*
 * Release the memory region(s) being used by 'port'
 */
static void leonuart_release_port(struct uart_port *port)
{
}

/*
 * Request the memory region(s) being used by 'port'
 */
static int leonuart_request_port(struct uart_port *port)
{
	return 0;
}

/*
 * Configure/autoconfigure the port.
 */
static void leonuart_config_port(struct uart_port *port, int flags)
{
	if (flags & UART_CONFIG_TYPE) {
		port->type = PORT_LEON;
		leonuart_request_port(port);
	}
}

/*
 * verify the new serial_struct (for TIOCSSERIAL).
 */
static int leonuart_verify_port(struct uart_port *port,
				struct serial_struct *ser)
{
	int ret = 0;
	if (ser->type != PORT_UNKNOWN && ser->type != PORT_LEON)
		ret = -EINVAL;
	if (ser->irq < 0 || ser->irq >= NR_IRQS)
		ret = -EINVAL;
	if (ser->baud_base < 9600)
		ret = -EINVAL;
	return ret;
}

static struct uart_ops leon_pops = {
	.tx_empty = leonuart_tx_empty,
	.set_mctrl = leonuart_set_mctrl,
	.get_mctrl = leonuart_get_mctrl,
	.stop_tx = leonuart_stop_tx,
	.start_tx = leonuart_start_tx,
	.stop_rx = leonuart_stop_rx,
	.enable_ms = leonuart_enable_ms,
	.break_ctl = leonuart_break_ctl,
	.startup = leonuart_startup,
	.shutdown = leonuart_shutdown,
	.set_termios = leonuart_set_termios,
	.type = leonuart_type,
	.release_port = leonuart_release_port,
	.request_port = leonuart_request_port,
	.config_port = leonuart_config_port,
	.verify_port = leonuart_verify_port,
};

static struct uart_leon_port leon_ports[UART_NR];
/* = {
	{
		.port	= {
			.membase	= (void*) (LEON_PREGS+LEON_UART0),
			.mapbase	= (LEON_PREGS+LEON_UART0),
			.iotype	= SERIAL_IO_MEM,
			.irq		= LEON_INTERRUPT_UART_0_RX_TX,
			.uartclk	= 0,
			.fifosize	= 1,
			.ops		= &leon_pops,
			.flags	= ASYNC_BOOT_AUTOCONF,
			.line		= 0,
		},
	},
	{
		.port	= {
			.membase	= (void*) (LEON_PREGS+LEON_UART1),
			.mapbase	= (LEON_PREGS+LEON_UART1),
			.iotype	= SERIAL_IO_MEM,
			.irq		= LEON_INTERRUPT_UART_1_RX_TX, 
			.uartclk	= 0,
			.fifosize	= 1,
			.ops		= &leon_pops,
			.flags	= ASYNC_BOOT_AUTOCONF,
			.line		= 1,
		},
	}
};*/

extern volatile LEON3_GpTimer_Regs_Map *LEON3_GpTimer_Regs;

static int apbuart_scan_fifo_size(struct uart_port *port, int portnumber)
{
	int ctrl;
	int status;
	int fifosize;
	unsigned long flags;

	ctrl = UART_GET_CTRL(port);

	printk("Testing fifo size for UART port %i: ", portnumber);

	/*
 	 * Enable the transceiver and wait for it to be ready to send data.
 	 * Clear interrupts so that this process will not be externally
 	 * interrupted in the middle (which can cause the transceiver to
 	 * drain prematurely). 
 	 */

	local_irq_save(flags);

	UART_PUT_CTRL(port, ctrl | LEON_REG_UART_CTRL_TE);

	while (!UART_TX_READY(UART_GET_STATUS(port)));

	/*
 	 * Disable the transceiver so data isn't actually sent during the
	 * actual test.
	 */

	UART_PUT_CTRL(port, ctrl & ~(LEON_REG_UART_CTRL_TE));

	fifosize = 1;
	UART_PUT_CHAR(port, 0);

	/*
 	 * So long as transmitting a character increments the tranceivier FIFO
 	 * length the FIFO must be at least that big. These bytes will automatically
 	 * drain off of the FIFO.
 	 */

	status = UART_GET_STATUS(port);
	while (((status >> 20) & 0x3F) == fifosize) {
		fifosize++;
		UART_PUT_CHAR(port, 0);
		status = UART_GET_STATUS(port);
	}

	fifosize--;

	UART_PUT_CTRL(port, ctrl);
	local_irq_restore(flags);

	printk("got %i bytes.\n", fifosize);

	if (fifosize == 0) {
		fifosize = 1;
	}

	return fifosize;
}

static void apbuart_flush_fifo(struct uart_port *port)
{
	int i;

	for (i = 0; i < port->fifosize; i++) {
		UART_GET_CHAR(port);
	}
}


/* rs_init inits the driver */
static int _apbuart_init_bases_done = 0;
static void __init _apbuart_init_bases(void)
{
	int i;
	amba_apb_device dev[8];
	if (!_apbuart_init_bases_done) {
		unsigned long clk =
		    ((unsigned
		      long)(((LEON3_BYPASS_LOAD_PA
			      (&LEON3_GpTimer_Regs->scalar_reload)) + 1)));
		printk("Attaching grlib apbuart serial drivers (clk:%ihz):\n",
		       (int)clk);
		leon_ports_nr =
		    amba_get_free_apbslv_devices(VENDOR_GAISLER,
						 GAISLER_APBUART, dev, 8);

		for (i = 0; i < leon_ports_nr; i++) {
			leon_ports[i].port.membase = (void *)dev[i].start;
			leon_ports[i].port.mapbase = dev[i].start;
			leon_ports[i].port.irq = dev[i].irq;
			leon_ports[i].port.iotype = SERIAL_IO_MEM;
			leon_ports[i].port.uartclk = clk * 1000 * 1000;
			leon_ports[i].port.fifosize = 1;
			leon_ports[i].port.ops = &leon_pops;
			leon_ports[i].port.flags = ASYNC_BOOT_AUTOCONF;
			leon_ports[i].port.line = i;
		}
		_apbuart_init_bases_done = 1;
	}
}

#ifdef CONFIG_GRLIB_GAISLER_APBUART_CONSOLE

static void
leonuart_console_write(struct console *co, const char *s, unsigned int count)
{
	struct uart_port *port = &leon_ports[co->index].port;
	unsigned int status, old_cr;
	int i;

	/*
	 *      First save the CR then disable the interrupts
	 */
	old_cr = UART_GET_CTRL(port);
	UART_PUT_CTRL(port,
		      (old_cr &
		       ~(LEON_REG_UART_CTRL_RI | LEON_REG_UART_CTRL_TI)) |
		      (LEON_REG_UART_CTRL_RE | LEON_REG_UART_CTRL_TE));

	/*
	 *      Now, do each character
	 */
	for (i = 0; i < count; i++) {
		do {
			status = UART_GET_STATUS(port);
		} while (!UART_TX_READY(status));
		UART_PUT_CHAR(port, s[i]);
		if (s[i] == '\n') {
			do {
				status = UART_GET_STATUS(port);
			} while (!UART_TX_READY(status));
			UART_PUT_CHAR(port, '\r');
		}
	}

	/*
	 *      Finally, wait for transmitter to become empty
	 *      and restore the TCR
	 */
	do {
		status = UART_GET_STATUS(port);
	} while (!UART_TX_READY(status));
	UART_PUT_CTRL(port, old_cr);
}

static void __init
leonuart_console_get_options(struct uart_port *port, int *baud,
			     int *parity, int *bits)
{
	if (UART_GET_CTRL(port) &
	    (LEON_REG_UART_CTRL_RE | LEON_REG_UART_CTRL_TE)) {

		unsigned int quot, status;
		status = UART_GET_STATUS(port);

		*parity = 'n';
		if (status & LEON_REG_UART_CTRL_PE) {
			if ((status & LEON_REG_UART_CTRL_PS) == 0)
				*parity = 'e';
			else
				*parity = 'o';
		}

		*bits = 8;
		quot = UART_GET_SCAL(port) / 8;
		*baud = port->uartclk / (16 * (quot + 1));
	}
}

static int __init leonuart_console_setup(struct console *co, char *options)
{
	struct uart_port *port;
	int baud = 38400;
	int bits = 8;
	int parity = 'n';
	int flow = 'n';

	/*
	 * Check whether an invalid uart number has been specified, and
	 * if so, search for the first available port that does have
	 * console support.
	 */
	if (co->index >= leon_ports_nr)
		co->index = 0;
	port = &leon_ports[co->index].port;

	if (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);
	else
		leonuart_console_get_options(port, &baud, &parity, &bits);

	return uart_set_options(port, co, baud, parity, bits, flow);
}

static struct uart_driver leon_reg;
static struct console leon_console = {
	.name = "ttyS",
	.write = leonuart_console_write,
	.device = uart_console_device,
	.setup = leonuart_console_setup,
	.flags = CON_PRINTBUFFER,
	.index = -1,
	.data = &leon_reg,
};

//static int leonuart_init(void);
static int __init leonuart_console_init(void)
{
	_apbuart_init_bases();
	/*#if !(defined(CONFIG_VT) && defined(CONFIG_VGA_CONSOLE))*/
	register_console(&leon_console);
	/*#endif*/	
	return 0;
}

console_initcall(leonuart_console_init);

#define LEON_CONSOLE	&leon_console
#else
#define LEON_CONSOLE	NULL
#endif

static struct uart_driver leon_reg = {
	.owner = THIS_MODULE,
	.driver_name = "serial",
/*	.devfs_name = "tts/",*/
	.dev_name = "ttyS",
	.major = SERIAL_LEON_MAJOR,
	.minor = SERIAL_LEON_MINOR,
	.nr = UART_NR,
	.cons = LEON_CONSOLE,
};

/* ====================================== of driver ====================================== */

static int leon_line_nr = 0;

static int __devinit apbuart_probe(struct of_device *op, const struct of_device_id *match)
{
	struct console co;
	int node;
	int freq_khz;
	int baud_rates[UART_NR];
	unsigned long clk;
	struct device_node *dp = op->node; int v = 0, d = 0; unsigned int addr;
	struct uart_leon_port *port; struct amba_prom_registers *regs; int irq, line, *irqs;
	int *vendor = of_get_property(dp, "vendor", NULL);
	int *device = of_get_property(dp, "device", NULL);
	regs = of_get_property(dp, "reg", NULL);
	irqs = of_get_property(dp, "interrupts", NULL);
	if (vendor)
		v = *vendor;
	if (device)
		d = *device;
	
	if (LEON3_GpTimer_Regs == 0 || irqs == 0 || regs == 0 || !(v == VENDOR_GAISLER && d == GAISLER_APBUART)) {
		return -ENODEV;
	}
	addr = regs->phys_addr ;
	irq = *irqs;
	
	port = kzalloc(sizeof(struct uart_leon_port), GFP_KERNEL);
	if (unlikely(!port))
		return -ENOMEM;

	node = prom_getchild(prom_root_node);
	freq_khz = prom_getint(node, "clock-frequency");
	clk = ((unsigned long)(((LEON3_BYPASS_LOAD_PA(&LEON3_GpTimer_Regs->scalar_reload)) + 1)));
	
	port->port.membase = (void *)addr;
	port->port.mapbase = addr;
	port->port.irq = irq;
	port->port.iotype = SERIAL_IO_MEM;
	port->port.uartclk = clk * 1000 * 1000;
	port->port.fifosize = 1;
	port->port.ops = &leon_pops;
	port->port.flags = ASYNC_BOOT_AUTOCONF;
	port->port.line = line = leon_line_nr++;

	port->port.uartclk = freq_khz * 1000;
	uart_add_one_port(&leon_reg, port);
	uart_set_options(port, &co, line >= UART_NR ? 9600 : baud_rates[line], 'n', 8, 'n');
	port->port.fifosize = apbuart_scan_fifo_size(port, line);
	apbuart_flush_fifo(port);
	
	printk("---------------- Match %d: 0x%x@%d : %s ----------------\n",line,addr, irq,dp->path_component_name);
	return 0;
}

static struct of_device_id __initdata apbuart_match[] = {
	{
		.name = "GAISLER_APBUART",
	},
	{},
};

static struct of_platform_driver apbuart_driver = {
	.match_table	= apbuart_match,
	.probe		= apbuart_probe,
	.driver		= {
		.name	= "ambapp-apbuart",
	},
};

/* ====================================== of driver end ====================================== */



int __init gaisler_apbuart_init(void)
{
	int ret;
	int i;
	int node;
	int freq_khz;
	int baud_rates[UART_NR];

	_apbuart_init_bases();
	node = prom_getchild(prom_root_node);
	freq_khz = prom_getint(node, "clock-frequency");

	printk(KERN_INFO "grlib apbuart: %i serial driver(s) at [",
	       leon_ports_nr);
	for (i = 0; i < UART_NR; i++) {
		baud_rates[i] = 9600;
	}
	for (i = 0; i < leon_ports_nr; i++) {
		baud_rates[i] = prom_getintdefault(node, "uart1_baud", 9600);
		if (i != 0) {
			printk(",");
		}
		printk("0x%x", (unsigned int)leon_ports[i].port.mapbase);
		printk("(irq %i)", leon_ports[i].port.irq);
	}
	printk("]\n");

	baud_rates[0] = prom_getintdefault(node, "uart1_baud", 9600);
	baud_rates[1] = prom_getintdefault(node, "uart2_baud", 9600);

	printk(KERN_INFO 
	       "grlib apbuart: system frequency: %i khz, baud rates: %i %i\n",
	       freq_khz, baud_rates[0], baud_rates[1]);

	ret = uart_register_driver(&leon_reg);
	leon_reg.tty_driver->init_termios.c_cflag =
	    (leon_reg.tty_driver->init_termios.c_cflag & ~CBAUD) | B38400;

	if (ret)
		return ret;

	/*
 	 * Set the FIFO size after the baud rates are set so it'll be done at an
 	 * appropriate rate. Also flush the FIFOs just in case they have lingering
 	 * data.
 	 */

	of_register_driver(&apbuart_driver, &of_platform_bus_type);
	
	/*for (i = 0; i < leon_ports_nr; i++) {
		struct console co;
		leon_ports[i].port.uartclk = freq_khz * 1000;
		uart_add_one_port(&leon_reg, &leon_ports[i].port);
		uart_set_options(&leon_ports[i].port, &co,
				 baud_rates[i], 'n', 8, 'n');
		leon_ports[i].port.fifosize = apbuart_scan_fifo_size(i);
		apbuart_flush_fifo(&leon_ports[i].port);
		}*/
	
	
	return ret;
}

static void __exit gaisler_apbuart_exit(void)
{
	int i;

	for (i = 0; i < leon_ports_nr; i++)
		uart_remove_one_port(&leon_reg, &leon_ports[i].port);

	uart_unregister_driver(&leon_reg);

}

module_init(gaisler_apbuart_init);
module_exit(gaisler_apbuart_exit);

MODULE_AUTHOR("Konrad Eisele<eiselekd@web.de>, based on AMBA serial");
MODULE_DESCRIPTION("grlib apbuart serial driver");
MODULE_LICENSE("GPL");

void leon3_rs_put_char_base(LEON3_APBUART_Regs_Map * uart_regs, char ch)
{
	int flags, loops;

	local_irq_save(flags);
	loops = 0;
	while (!
	       (LEON3_BYPASS_LOAD_PA(&(uart_regs->status)) &
		LEON_REG_UART_STATUS_THE) && (loops < 100000))
		loops++;

	LEON3_BYPASS_STORE_PA(&(uart_regs->data), ch);

	loops = 0;
	while (!
	       (LEON3_BYPASS_LOAD_PA(&(uart_regs->status)) &
		LEON_REG_UART_STATUS_TSE) && (loops < 100000))
		loops++;
	local_irq_restore(flags);
}

void leon3_rs_put_char(char ch)
{
	LEON3_APBUART_Regs_Map *b =
	    (LEON3_APBUART_Regs_Map *) amba_find_apbslv_addr(VENDOR_GAISLER,
							     GAISLER_APBUART,
							     0);
	if (b) {
		leon3_rs_put_char_base(b, ch);
	}
}

void console_print_LEON(const char *p)
{
	char c;
	LEON3_APBUART_Regs_Map *b;


	if (!amba_is_init)
	  return;
	b = (LEON3_APBUART_Regs_Map *) amba_find_apbslv_addr(VENDOR_GAISLER,
							     GAISLER_APBUART,
							     0);
	if (b) {
	  while ((c = *(p++)) != 0) {
	    if (c == '\n')
	      leon3_rs_put_char_base(b, '\r');
	    leon3_rs_put_char_base(b, c);
	  }
	}
	
	/* Comment this if you want to have a strict interrupt-driven output */
	/* rs_fair_output(); */

	return;
}
