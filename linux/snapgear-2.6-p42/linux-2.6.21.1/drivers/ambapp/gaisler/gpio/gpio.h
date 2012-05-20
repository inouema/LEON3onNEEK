#ifndef GP_GPIO_H
#define GP_GPIO_H

#ifdef __KERNEL__
#include <linux/ioctl.h>
#else
#include <sys/ioctl.h>
#endif

#define GR_GPIO_GET_DIR		_IOW('g', 0x01, int)			/* get direction register */
#define GR_GPIO_SET_DIR		_IOR('g', 0x02, int)			/* set direction register */

#define GR_GPIO_GET_IN		_IOW('g', 0x03, int)			/* get input */
#define GR_GPIO_SET_OUT		_IOR('g', 0x04, int)			/* set output */

typedef struct {
  volatile unsigned int iodata;
  volatile unsigned int ioout;
  volatile unsigned int iodir;
  volatile unsigned int irqmask;
  volatile unsigned int irqpol;
  volatile unsigned int irqedge;
} LEON3_GPIO_IOPORT_Regs_Map;

#endif  /*GP_GPIO_H*/

