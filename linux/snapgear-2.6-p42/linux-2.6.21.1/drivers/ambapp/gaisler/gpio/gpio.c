#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#ifdef CONFIG_LEON
#include <asm/leon.h>
#endif
#include "gpio.h"

MODULE_LICENSE ("GPL");

//#define GPIO_DEBUG_ON 1
//#define GPIO_DEBUG_WRITE_ON 1
//#define GPIO_DEBUG_GPIO_READ 1
//#define GPIO_DEBUG_JTAG 1
//#define GPIO_DEBUG_TAP 1

#define GPIO_MAX_DEVICES 4
#define GPIO_OFFSET 0

int gpio_major = 212;
int gpio_minor = 0;

int cdev_count = 0;
#ifdef CONFIG_LEON    
amba_apb_device adev[GPIO_MAX_DEVICES];
#endif

struct cdev cdev[GPIO_MAX_DEVICES];
int gpio_busy[GPIO_MAX_DEVICES];

static int gpio_open (struct inode *inode, struct file *file);
static int gpio_release (struct inode *inode, struct file *file);
static int gpio_ioctl (struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg);

struct file_operations gpio_fops = {
    .owner   = THIS_MODULE,
    .open    = gpio_open,
    .release = gpio_release,
    .ioctl   = gpio_ioctl
};

static int gpio_open (struct inode *inode, struct file *file) {
    int idx = iminor (inode);
    if (idx >= cdev_count) {
	printk (KERN_WARNING "GRGPIO: device %d doesnt exist (%d)\n", idx, cdev_count);
	return -ENODEV;
    }
    if (gpio_busy[idx]) {
	printk (KERN_WARNING "GRGPIO: device %d already opened\n", idx);
	return -EBUSY;
    }
    printk (KERN_INFO "GRGPIO: device %d opened\n",idx);
    gpio_busy[idx] = 1;
    return 0;
}

static int gpio_release (struct inode *inode, struct file *file) {
    int idx = iminor (inode);
    gpio_busy[idx] = 0;
    printk (KERN_INFO "GRGPIO: device %d released\n",idx);
    return 0;
}

int gpio_ioctl (struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
    int err = 0; int retval = 0, data = 0;
#ifdef CONFIG_LEON
    LEON3_GPIO_IOPORT_Regs_Map *regs;
#endif    
    int idx = iminor (inode);
    if (idx >= cdev_count) {
	printk (KERN_WARNING "GRGPIO: device %d doesnt exist (%d)\n", idx, cdev_count);
	return -ENODEV;
    }
#ifdef CONFIG_LEON
    regs = (LEON3_GPIO_IOPORT_Regs_Map *)adev[idx].start;
#endif    
    if (_IOC_DIR(cmd) & _IOC_WRITE)
	err = !access_ok(VERIFY_WRITE, (void __user *)arg, _IOC_SIZE(cmd));
    if ((!err) && (_IOC_DIR(cmd) & _IOC_READ))
	err = !access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd));
    if (err) return -EFAULT;
    
    switch (cmd) {
    case GR_GPIO_SET_OUT:
	if ((retval = __get_user(data, (int __user *)arg)) == 0) {
#ifdef GPIO_DEBUG_ON       
	    printk (KERN_INFO "GRGPIO: GR_GPIO_SET_OUT(0x%x)\n",data);
#endif	    
#ifdef CONFIG_LEON
	    LEON3_BYPASS_STORE_PA(&(regs->ioout),data);
#endif	
	}
	return retval;
    case GR_GPIO_GET_IN:
#ifdef CONFIG_LEON
	data = LEON3_BYPASS_LOAD_PA(&(regs->iodata));
#else
	data = 1;
#endif	
	if ((retval = __put_user(data, (int __user *)arg)) == 0) {
#ifdef GPIO_DEBUG_ON       
	    printk (KERN_INFO "GRGPIO: GR_GPIO_GET_IN=>(0x%x)\n",data);
#endif	    
	}
	return retval;
    case GR_GPIO_SET_DIR:
	if ((retval = __get_user(data, (int __user *)arg)) == 0) {
#ifdef GPIO_DEBUG_ON       
	    printk (KERN_INFO "GRGPIO: GR_GPIO_SET_DIR(0x%x)\n",data);
#endif	    
#ifdef CONFIG_LEON
	    LEON3_BYPASS_STORE_PA(&(regs->iodir),data);
#endif	
	}
	return retval;
    case GR_GPIO_GET_DIR:
#ifdef CONFIG_LEON
	data = LEON3_BYPASS_LOAD_PA(&(regs->iodir));
	
#else
	data = 2;
#endif	
	if ((retval = __put_user(data, (int __user *)arg)) == 0) {
#ifdef GPIO_DEBUG_ON       
	    printk (KERN_INFO "GRGPIO: GR_GPIO_GET_DIR=>(0x%x)\n",data);
#endif	    
	}
	return retval;
    }
    return -EINVAL;
}

#ifndef CONFIG_LEON    

static void char_reg_setup_cdev (int minor) {
    int error, devno = MKDEV (gpio_major, minor);
    cdev_init (&cdev[minor], &gpio_fops);
    cdev[minor].owner = THIS_MODULE;
    cdev[minor].ops = &gpio_fops;
    error = cdev_add (&cdev[minor], devno , 1);
    if (error) {
	printk (KERN_NOTICE "GRGPIO: Error %d adding char_reg_setup_cdev for device %d", error, minor);
    }
}

#endif

static int __init gpio_init (void) {
    int result, devno;    
    
    memset(gpio_busy,0,sizeof(gpio_busy));
    memset(cdev,0,sizeof(cdev));
    
    devno = MKDEV (gpio_major, gpio_minor);
    result = register_chrdev_region (devno, GPIO_MAX_DEVICES, "gpio");
    if (result<0) {
	printk (KERN_WARNING "GRGPIO: can't get major number %d\n", gpio_major);
	return result;
    }

#ifdef CONFIG_LEON    
    if (GPIO_OFFSET) {
	if ((cdev_count = amba_get_free_apbslv_devices (VENDOR_GAISLER, GAISLER_GRGPIO, adev, GPIO_OFFSET)) != GPIO_OFFSET) {
	    printk (KERN_WARNING "GRGPIO: can't skip over first %d gpio ports\n", GPIO_OFFSET);
	    return -EINVAL;
	}
    }
    
    cdev_count = amba_get_free_apbslv_devices (VENDOR_GAISLER, GAISLER_GRGPIO, adev, GPIO_MAX_DEVICES);
    if ( cdev_count < 1 ){
        printk ("GRGPIO: no cores available\n");
        return 0;
    }
    
#else
    cdev_count = 2;
    for (i = 0; i < cdev_count; i++) {
	char_reg_setup_cdev(i);
	printk (KERN_INFO "GRGPIO: host dummy registered \n" );
    }
#endif    
    
    return 0;
}

static void __exit gpio_exit (void) {
    int i;
    dev_t devno = MKDEV (gpio_major, gpio_minor);
    for (i = 0; i < cdev_count; i++) {
	cdev_del (&cdev[i]);
    }
    unregister_chrdev_region (devno, GPIO_MAX_DEVICES);
    printk (KERN_INFO "gpio: char driver cleaned up\n");
}

module_init (gpio_init);
module_exit (gpio_exit);

