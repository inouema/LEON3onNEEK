#include <linux/module.h>
#include <linux/version.h>

static int fail=0;
static char modname[40] = { '\0' };
static char *load = modname;
#if LINUX_VERSION_CODE >= 131584 /* 2.2.0 */
#include <linux/kmod.h>
MODULE_PARM(fail, "i");
MODULE_PARM(load, "s");
#else
#include <linux/kerneld.h>
#endif

int init_module(void)
{
  printk("fail=%d\n", fail);
  printk("load=<%s>\n", load);

  if (load[0])
	request_module(load);

  return fail;
}

void cleanup_module(void)
{
}
