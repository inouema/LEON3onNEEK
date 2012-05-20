#include <linux/config.h>
#include <linux/kernel.h>
#include <asm/asi.h>
#include <asm/asi.h>
#include <asm/leon.h>
#include <asm/pgtsrmmu.h>
#include <asm/page.h>
#include <asm/head.h>
#include "../bootloader.h"

int puts(const char *fmt, ...);
int lelomm(void);
int sputs(char *buf, size_t size, const char *fmt, ...);
unsigned long decompress_kernel(unsigned long output_start, unsigned long free_mem_ptr_p, unsigned long free_mem_ptr_end_p);
int main(void);

