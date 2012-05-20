/* Konrad Eisele <eiselekd@web.de>, 2003 */
#include <stdarg.h>
#include <linux/autoconf.h>
#include <linux/types.h>
#include <linux/string.h>
#include <linux/ctype.h>
#include <linux/kernel.h>


size_t lo_strnlen(const char * s, size_t count)
{
	const char *sc;

	for (sc = s; count-- && *sc != '\0'; ++sc)
		/* nothing */;
	return sc - s;
}

int lo_vsnprintf(char *buf, size_t size, const char *fmt, va_list args)
{
	int len;
	unsigned long long num;
	int i,j,n;
	char *str, *end, c;
	const char *s;
	int flags;
	int field_width;
	int precision;
	int qualifier;	

	str = buf;
	end = buf + size - 1;

	if (end < buf - 1) {
		end = ((void *) -1);
		size = end - buf + 1;
	}

	for (; *fmt ; ++fmt) {
		if (*fmt != '%') {
			if (str <= end)
				*str = *fmt;
			++str;
			continue;
		}

		/* process flags */
		flags = 0;
		/* get field width */
		field_width = -1;
		/* get the precision */
		precision = -1;
		/* get the conversion qualifier */
		qualifier = 'l';

            ++fmt;
		/* default base */
		switch (*fmt) {
			case 'c':
				c = (unsigned char) va_arg(args, int);
				if (str <= end)
					*str = c;
				++str;
				while (--field_width > 0) {
					if (str <= end)
						*str = ' ';
					++str;
				}
				continue;

			case 's':
				s = va_arg(args, char *);
				if (!s)
					s = "<NULL>";

				len = lo_strnlen(s, precision);

				for (i = 0; i < len; ++i) {
					if (str <= end)
						*str = *s;
					++str; ++s;
				}
				while (len < field_width--) {
					if (str <= end)
						*str = ' ';
					++str;
				}
				continue;


			case '%':
				if (str <= end)
					*str = '%';
				++str;
				continue;

			case 'x':
				break;

			default:
				if (str <= end)
					*str = '%';
				++str;
				if (*fmt) {
					if (str <= end)
						*str = *fmt;
					++str;
				} else {
					--fmt;
				}
				continue;
		}
            num = va_arg(args, unsigned long);
            for (j=0,i=0;i<8 && str <= end;i++) {
                  if ( (n = ((unsigned long)(num & (0xf0000000ul>>(i*4)))) >> ((7-i)*4)) || j != 0) {
                        j = 1;
                        if (n >= 10)
                              n += 'a'-10;
                        else
                              n += '0';
                        *str = n;
                        ++str;
                  }
            }
            if (j == 0 && str <= end) {
                  *str = '0';
                  ++str;
            }
	}
	if (str <= end)
		*str = '\0';
	else if (size > 0)
		/* don't write out a null byte if the buf size is zero */
		*end = '\0';
	/* the trailing null byte doesn't count towards the total
	* ++str;
	*/
	return str-buf;
}

/**
 * lo_snprintf - Format a string and place it in a buffer
 * @buf: The buffer to place the result into
 * @size: The size of the buffer, including the trailing null space
 * @fmt: The format string to use
 * @...: Arguments for the format string
 */
int lo_snprintf(char * buf, size_t size, const char *fmt, ...)
{
	va_list args;
	int i;

	va_start(args, fmt);
	i=lo_vsnprintf(buf,size,fmt,args);
	va_end(args);
	return i;
}

/**
 * lo_vsprintf - Format a string and place it in a buffer
 * @buf: The buffer to place the result into
 * @fmt: The format string to use
 * @args: Arguments for the format string
 *
 * Call this function if you are already dealing with a va_list.
 * You probably want lo_sprintf instead.
 */
int lo_vsprintf(char *buf, const char *fmt, va_list args)
{
	return lo_vsnprintf(buf, 0xFFFFFFFFUL, fmt, args);
}


/**
 * sprintf - Format a string and place it in a buffer
 * @buf: The buffer to place the result into
 * @fmt: The format string to use
 * @...: Arguments for the format string
 */
int lo_sprintf(char * buf, const char *fmt, ...)
{
	va_list args;
	int i;

	va_start(args, fmt);
	i=lo_vsprintf(buf,fmt,args);
	va_end(args);
	return i;
}


#define CONFIG_LEON
/*#define CONFIG_LEON_3*/
#include <asm/leon.h>

int sputs(char *buf, size_t size, const char *fmt, ...) {
	va_list args;
	int printed_len;

	va_start(args, fmt);
	printed_len = lo_vsnprintf(buf, size, fmt, args);
	va_end(args);
      return printed_len;
}

#ifdef CONFIG_LEON_3

unsigned int leon3_ahbslv_scan(register unsigned int vendor,register unsigned int driver) {
  register unsigned int conf,i, *confp;
  register unsigned int cfg_area = (unsigned int ) (LEON3_IO_AREA | LEON3_CONF_AREA | LEON3_AHB_SLAVE_CONF_AREA);
  for (i = 0; i < LEON3_AHB_SLAVES; i++) 
  {
    confp = (unsigned int*)(cfg_area + (i * LEON3_AHB_CONF_WORDS * 4));
    conf = *confp;
    //mbar = *(unsigned int*)(i * LEON3_AHB_CONF_WORDS+ (4 * 4));
    if ((amba_vendor(conf) == vendor) && (amba_device(conf) == driver)) {
      return (unsigned int)confp;
    }
  }
  return 0;
}

unsigned int *leon3_apbslv_scan(register unsigned int base,register unsigned int vendor, register unsigned int driver) {
  register unsigned int conf,i, *confp;
  for (i = 0; i < LEON3_APB_SLAVES; i++) 
  {
    confp = (unsigned int*)(base + (i * LEON3_APB_CONF_WORDS * 4));
    conf = *confp;
    if ((amba_vendor(conf) == vendor) && (amba_device(conf) == driver)) {
      return confp;
    }
  }
  return 0;
}

unsigned int *leon3_getbase(register unsigned int *mbar,register unsigned int iobase) {
  register unsigned int conf = mbar[1];
  return (unsigned int *)(((iobase & 0xfff00000) |
          ((conf & 0xfff00000)>> 12)) & (((conf & 0x0000fff0) <<4) | 0xfff00000));
  
}

unsigned int *leon3_getapbbase(register unsigned int vendor,register unsigned int driver) {
    unsigned int *b;
    unsigned int apb = leon3_ahbslv_scan(VENDOR_GAISLER,GAISLER_APBMST);
    apb = (*(unsigned int *)(apb + 16)) & LEON3_IO_AREA;
    apb |= LEON3_CONF_AREA;
    b = leon3_apbslv_scan(apb,vendor,driver);
    b = leon3_getbase(b,apb);
    return b;
}

void leon_putchar(const char ch) {

  int loops = 0;
  LEON3_APBUART_Regs_Map *uart_regs = (LEON3_APBUART_Regs_Map *)leon3_getapbbase(VENDOR_GAISLER,GAISLER_APBUART);
  if (uart_regs) {
    while (!(uart_regs->status & LEON_REG_UART_STATUS_THE) && (loops < 100000))
      loops++;
    
    uart_regs->data = ch;
    
    loops = 0;
    while (!(uart_regs->status & LEON_REG_UART_STATUS_TSE) && (loops < 100000))
      loops++;
  }
}


#else

void leon_putchar(const char c) {

  while ((LEON_REGLOAD_PA(LEON_USTAT0)  & 4) == 0);
  LEON_REGSTORE_PA(LEON_UDATA0,c);
}

#endif

int puts(const char *fmt, ...)
{
	va_list args;
	int printed_len;
	char printk_buf[1024];
	char *p = printk_buf;
	
	/* Emit the output into the temporary buffer */
	va_start(args, fmt);
	printed_len = lo_vsnprintf(printk_buf, sizeof(printk_buf), fmt, args);
	va_end(args);

      while (printed_len-- != 0) {
        leon_putchar(*p);
            p++;
      }
	return printed_len;
}
