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
 */

#include <linux/module.h>
#include <linux/tty.h>
#include <linux/tty_flip.h>
#include <linux/ioport.h>
#include <linux/init.h>
#include <linux/serial.h>
#include <linux/console.h>
#include <linux/sysrq.h>

#include <asm/io.h>
#include <asm/irq.h>
#include <asm/oplib.h>

#if defined(CONFIG_SERIAL_LEON_CONSOLE) && defined(CONFIG_MAGIC_SYSRQ)
#define SUPPORT_SYSRQ
#endif

#include <linux/serial_core.h>
#include <asm/leon.h>

#define UART_NR		2

#define SERIAL_LEON_MAJOR	TTY_MAJOR
#define SERIAL_LEON_MINOR	64
#define SERIAL_LEON_NR		UART_NR

#define AMBA_ISR_PASS_LIMIT	256

#define UART_GET_CHAR(p)	(LEON_BYPASS_LOAD_PA((port)->membase + (LEON_OFF_UDATA)))
#define UART_PUT_CHAR(p, v)	(LEON_BYPASS_STORE_PA((port)->membase + (LEON_OFF_UDATA),v))
#define UART_GET_STATUS(p)	(LEON_BYPASS_LOAD_PA((port)->membase + (LEON_OFF_USTAT)))
#define UART_PUT_STATUS(p,v)	(LEON_BYPASS_STORE_PA((port)->membase + (LEON_OFF_USTAT),v))
#define UART_GET_CTRL(port)   (LEON_BYPASS_LOAD_PA((port)->membase + (LEON_OFF_UCTRL)))
#define UART_PUT_CTRL(port,v) (LEON_BYPASS_STORE_PA((port)->membase + (LEON_OFF_UCTRL),v))
#define UART_GET_SCAL(port)   (LEON_BYPASS_LOAD_PA((port)->membase + (LEON_OFF_USCAL)))
#define UART_PUT_SCAL(port,v) (LEON_BYPASS_STORE_PA((port)->membase + (LEON_OFF_USCAL),v))
#define UART_RX_DATA(s)       (((s) & LEON_USTAT_DR) != 0)
#define UART_TX_READY(s)	(((s) & LEON_USTAT_TH) != 0)

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
	cr &= ~LEON_UCTRL_TI;
	UART_PUT_CTRL(port, cr);
}

static void leonuart_tx_chars(struct uart_port *port);
static void leonuart_start_tx(struct uart_port *port/*, unsigned int tty_start*/)
{
	unsigned int cr;

	cr = UART_GET_CTRL(port);
	cr |= LEON_UCTRL_TI;
	UART_PUT_CTRL(port, cr);

	if (UART_GET_STATUS(port) & LEON_USTAT_TH) {
		leonuart_tx_chars(port);
	}
}

static void leonuart_stop_rx(struct uart_port *port)
{
	unsigned int cr;

	cr = UART_GET_CTRL(port);
	cr &= ~(LEON_UCTRL_RI);
	UART_PUT_CTRL(port, cr);
}

static void leonuart_enable_ms(struct uart_port *port)
{
	/* no modem status for leon */
}

static void
#ifdef SUPPORT_SYSRQ
leonuart_rx_chars(struct uart_port *port, struct pt_regs *regs)
#else
leonuart_rx_chars(struct uart_port *port)
#endif
{
	struct tty_struct *tty = port->info->tty;
	unsigned int status, ch, flag, rsr, max_count = 256;

	status = UART_GET_STATUS(port);
	while (UART_RX_DATA(status) && max_count--) {

		//if (tty->flip.count >= TTY_FLIPBUF_SIZE) {
		//	if (tty->low_latency)
		//		tty_flip_buffer_push(tty);
			/*
			 * If this failed then we will throw away the
			 * bytes but must do so to clear interrupts.
			 */
		//}

		ch = UART_GET_CHAR(port);
		flag = TTY_NORMAL;

		port->icount.rx++;

		/*
		 * Note that the error handling code is
		 * out of the main execution path
		 */
		rsr = UART_GET_STATUS(port) | UART_DUMMY_RSR_RX;
		UART_PUT_STATUS(port, 0);
		if (rsr & LEON_USTAT_ERROR) {

			if (rsr & LEON_USTAT_BR) {
				rsr &= ~(LEON_USTAT_FE | LEON_USTAT_PE);
				port->icount.brk++;
				if (uart_handle_break(port))
					goto ignore_char;
			} else if (rsr & LEON_USTAT_PE) {
				port->icount.parity++;
			} else if (rsr & LEON_USTAT_FE) {
				port->icount.frame++;
			}
			if (rsr & LEON_USTAT_OV)
				port->icount.overrun++;

			rsr &= port->read_status_mask;

			if (rsr & LEON_USTAT_BR)
				flag = TTY_BREAK;
			else if (rsr & LEON_USTAT_PE)
				flag = TTY_PARITY;
			else if (rsr & LEON_USTAT_FE)
				flag = TTY_FRAME;
		}

		if (uart_handle_sysrq_char(port, ch))
			goto ignore_char;

		if ((rsr & port->ignore_status_mask) == 0) {
			tty_insert_flip_char(tty, ch, flag);
		}
		if (rsr & LEON_USTAT_OV) {
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

static void leonuart_tx_chars(struct uart_port *port)
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

irqreturn_t leon2uart_int(int irq, void *dev_id, struct pt_regs *regs)
{
	struct uart_port *port = dev_id;
	unsigned int status;

	spin_lock(&port->lock);

	status = UART_GET_STATUS(port);
	if (status & LEON_USTAT_DR) {
#ifdef SUPPORT_SYSRQ
		leonuart_rx_chars(port, regs);
#else
		leonuart_rx_chars(port);
#endif
	}
	if (status & LEON_USTAT_TH) {
		leonuart_tx_chars(port);
	}

	spin_unlock(&port->lock);

	return IRQ_HANDLED;
}

static unsigned int leonuart_tx_empty(struct uart_port *port)
{
	return UART_GET_STATUS(port) & LEON_USTAT_TH ? TIOCSER_TEMT : 0;
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
	retval = request_irq(port->irq, leon2uart_int, 0, "leon", port);
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
		      cr | LEON_UCTRL_RE | LEON_UCTRL_TE | LEON_UCTRL_RI |
		      LEON_UCTRL_TI);

	return 0;
}

static void leonuart_shutdown(struct uart_port *port)
{
	unsigned int cr;

	/*
	 * Free the interrupt
	 */
	free_irq(port->irq, port);

	/*
	 * disable all interrupts, disable the port
	 */
	cr = UART_GET_CTRL(port);
	UART_PUT_CTRL(port,
		      cr & ~(LEON_UCTRL_RE | LEON_UCTRL_TE | LEON_UCTRL_RI |
			     LEON_UCTRL_TI));

}

static void
leonuart_set_termios(struct uart_port *port, struct termios *termios,
		     struct termios *old)
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
	cr &= ~(LEON_UCTRL_PE | LEON_UCTRL_PS);

	if (termios->c_cflag & PARENB) {
		cr |= LEON_UCTRL_PE;
		if ((termios->c_cflag & PARODD))
			cr |= LEON_UCTRL_PS;
	}

	spin_lock_irqsave(&port->lock, flags);

	/*
	 * Update the per-port timeout.
	 */
	uart_update_timeout(port, termios->c_cflag, baud);

	port->read_status_mask = LEON_USTAT_OV;
	if (termios->c_iflag & INPCK)
		port->read_status_mask |= LEON_USTAT_FE | LEON_USTAT_PE;

	/*
	 * Characters to ignore
	 */
	port->ignore_status_mask = 0;
	if (termios->c_iflag & IGNPAR)
		port->ignore_status_mask |= LEON_USTAT_FE | LEON_USTAT_PE;

	/*
	 * Ignore all characters if CREAD is not set.
	 */
	if ((termios->c_cflag & CREAD) == 0)
		port->ignore_status_mask |=
		    LEON_USTAT_OV | LEON_USTAT_FE | LEON_USTAT_PE;

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

static struct uart_leon_port leon_ports[UART_NR] = {
	{
	 .port = {
		  .membase = (void *)(LEON_PREGS + LEON_UART0),
		  .mapbase = (LEON_PREGS + LEON_UART0),
		  .iotype = SERIAL_IO_MEM,
		  .irq = LEON_INTERRUPT_UART_0_RX_TX,
		  .uartclk = 0,
		  .fifosize = 1,
		  .ops = &leon_pops,
		  .flags = ASYNC_BOOT_AUTOCONF,
		  .line = 0,
		  },
	 },
	{
	 .port = {
		  .membase = (void *)(LEON_PREGS + LEON_UART1),
		  .mapbase = (LEON_PREGS + LEON_UART1),
		  .iotype = SERIAL_IO_MEM,
		  .irq = LEON_INTERRUPT_UART_1_RX_TX,
		  .uartclk = 0,
		  .fifosize = 1,
		  .ops = &leon_pops,
		  .flags = ASYNC_BOOT_AUTOCONF,
		  .line = 1,
		  },
	 }
};

#ifdef CONFIG_SERIAL_LEON_CONSOLE

static void
_leonuart_console_write(struct uart_port *port, const char *s, unsigned int count)
{
	unsigned int status, old_cr;
	int i;

	/*
	 *      First save the CR then disable the interrupts
	 */
	old_cr = UART_GET_CTRL(port);
	UART_PUT_CTRL(port,
		      (old_cr & ~(LEON_UCTRL_RI | LEON_UCTRL_TI)) |
		      (LEON_UCTRL_RE | LEON_UCTRL_TE));

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

static void
leonuart_console_write(struct console *co, const char *s, unsigned int count) {
        _leonuart_console_write(&leon_ports[co->index].port, s, count);
}

extern void console_print_LEON(const char *p) {
  _leonuart_console_write(&leon_ports[0].port, p, strlen(p));
}


static void __init
leonuart_console_get_options(struct uart_port *port, int *baud,
			     int *parity, int *bits)
{
	if (UART_GET_CTRL(port) & (LEON_UCTRL_RE | LEON_UCTRL_TE)) {

		unsigned int quot, status;
		status = UART_GET_STATUS(port);

		*parity = 'n';
		if (status & LEON_UCTRL_PE) {
			if ((status & LEON_UCTRL_PS) == 0)
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
	if (co->index >= UART_NR)
		co->index = 0;
	port = &leon_ports[co->index].port;

	if (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);
	else
		leonuart_console_get_options(port, &baud, &parity, &bits);

	return uart_set_options(port, co, baud, parity, bits, flow);
}

static void __init leonuart_early_setup(void)
{

	static int first = 1;
	int i;

	if (!first)
		return;
	first = 0;

	for (i = 0; i < UART_NR; i++) {
		/* assuming that bootloader or the dsumon has set up LEON_SRLD,
		 * so that timer ticks on 1mhz
		 */
		leon_ports[i].port.uartclk =
		    (LEON_REGLOAD_PA(LEON_SRLD) + 1) * 1000 * 1000;
	}
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

static int leonuart_init(void);
static int __init leonuart_console_init(void)
{
	leonuart_early_setup();
	register_console(&leon_console);
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

static int __init leonuart_init(void)
{
	int ret;
	int i;
	int node;
	int freq_khz;
	int baud_rates[UART_NR];

	printk(KERN_INFO
	       "Serial: Leon driver, author: Konrad Eisele<eiselekd@web.de>\n");

	node = prom_getchild(prom_root_node);
	freq_khz = prom_getint(node, "clock-frequency");
	baud_rates[0] = prom_getintdefault(node, "uart1_baud", 9600);
	baud_rates[1] = prom_getintdefault(node, "uart2_baud", 9600);

	printk(KERN_INFO
	       "Serial: system frequency: %i khz, baud rates: %i %i\n",
	       freq_khz, baud_rates[0], baud_rates[1]);

	ret = uart_register_driver(&leon_reg);
	leon_reg.tty_driver->init_termios.c_cflag =
	    (leon_reg.tty_driver->init_termios.c_cflag & ~CBAUD) | B38400;

	if (ret)
		return ret;

	for (i = 0; i < UART_NR; i++) {
		struct console co;
		leon_ports[i].port.uartclk = freq_khz * 1000;
		uart_add_one_port(&leon_reg, &leon_ports[i].port);
		uart_set_options(&leon_ports[i].port, &co,
				 baud_rates[i], 'n', 8, 'n');
	}

	return ret;
}

static void __exit leonuart_exit(void)
{
	int i;

	for (i = 0; i < UART_NR; i++)
		uart_remove_one_port(&leon_reg, &leon_ports[i].port);

	uart_unregister_driver(&leon_reg);
}

module_init(leonuart_init);
module_exit(leonuart_exit);

MODULE_AUTHOR("Konrad Eisele<eiselekd@web.de>, based on AMBA serial");
MODULE_DESCRIPTION("Leon2 serial port driver");
MODULE_LICENSE("GPL");
