#define CONFIG_SERIO_LEON3_KEYB_IRQ 0x6
#define CONFIG_PAGE_SIZE_LEON_4K 1
#define CONFIG_LEON 1
#define CONFIG_SERIO_LEON3 1
#define CONFIG_LEON_3 1
#if defined(CONFIG_PAGE_SIZE_LEON_8K)
#define CONFIG_PAGE_SIZE_LEON 1
#elif defined(CONFIG_PAGE_SIZE_LEON_16K)
#define CONFIG_PAGE_SIZE_LEON 2
#elif defined(CONFIG_PAGE_SIZE_LEON_32K)
#define CONFIG_PAGE_SIZE_LEON 3
#else
#define CONFIG_PAGE_SIZE_LEON 0
#endif
