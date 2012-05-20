#include <linux/module.h>
#include <errno.h>
#include <linux/kerneld.h>

/*
 * Test persistent module storage by doing:
 *
 *  insmod ./check_persist.o value=1
 */

#define Key "you can use any string as a key"

/* You can use _anything_ as a value as long as you know its size! */
static int value;

int
init_module(void)
{
	int oldval;

	if (get_persist(Key, (void *)&oldval, sizeof(int)) > 0)
		printk("found old value: %d\n", oldval);
	else
		printk("no old value\n");

	if (set_persist(Key, (void *)&value, sizeof(int)) < 0)
		printk("set_persist failed\n");
	else
		printk("new value: %d\n", value);

	return -EBUSY;
}

void
cleanup_module(void)
{
}
