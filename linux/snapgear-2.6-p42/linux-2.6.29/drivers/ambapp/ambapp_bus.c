#include <linux/module.h>
#include <linux/wait.h>
#include <linux/errno.h>
#include <linux/kthread.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/idr.h>
#include <linux/jiffies.h>
#include <linux/string.h>
#include <linux/rwsem.h>
#include <linux/semaphore.h>
#include <asm/system.h>

#include <asm/leon.h>
#include "amba.h"
#include "ambapp.h"

#define _STATIC_ 

