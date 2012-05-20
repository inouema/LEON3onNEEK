#include <linux/module.h>

char *foo = "failed";

extern void printme(void);

int init_module(void)
{
  printme();
  return 0;
}

void cleanup_module(void)
{
}
