#include <linux/module.h>
#include <linux/version.h>

static int printk;
#if LINUX_VERSION_CODE >= 131584 /* 2.2.0 */
MODULE_PARM(printk, "i");
#endif

int init_module(void)
{
  printk=2;
  return 0;
}

void cleanup_module(void)
{
}
