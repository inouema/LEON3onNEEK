#include "remove_predefs.h"
#include "bootloader.h"

OUTPUT_FORMAT("elf32-sparc", "elf32-sparc", "elf32-sparc")
OUTPUT_ARCH(sparc)
ENTRY(_start)
SECTIONS
{
        .rom 0 : {
                _start = .;
                prom_stage1.o(.text)
        }

        . = BOOTLOADER_physbase /*0x40000000*/;
        .stage2 : {
                prom_stage2.o(.img.main.text)
                prom_stage2.o
        	. = ALIGN(0x2000);
                _bootloader_ph = .;
		pgt.o
	}
#if defined(CONFIG_LEON) && (defined(CONFIG_PAGE_SIZE_LEON_8K)||defined(CONFIG_PAGE_SIZE_LEON_16K)||defined(CONFIG_PAGE_SIZE_LEON_32K))
        . = ALIGN(0x8000);
#else
        . = ALIGN(0x4000);
#endif  
        .vmlinux : {
                LINUXIMAGE (.text)
								. = ALIGN(4096);
                LINUXIMAGE (.rodata)
		LINUXIMAGE (.pci_fixup)
		LINUXIMAGE (.rio_route)
		LINUXIMAGE (__ksymtab)
		LINUXIMAGE (__ksymtab_gpl)
		LINUXIMAGE (__ksymtab_unused)
		LINUXIMAGE (__ksymtab_unused_gpl)
		LINUXIMAGE (__ksymtab_gpl_future)
		LINUXIMAGE (__kcrctab)
		LINUXIMAGE (__kcrctab_gpl)
		LINUXIMAGE (__kcrctab_unused)
		LINUXIMAGE (__kcrctab_unused_gpl)
		LINUXIMAGE (__kcrctab_gpl_future)
		. = ALIGN(4096);
		LINUXIMAGE (__param)
    LINUXIMAGE (.data)
    LINUXIMAGE (.data.init)
    LINUXIMAGE (.fixup)
    LINUXIMAGE (__ex_table)
		. = ALIGN(4096);
		__init_begin = .;
    LINUXIMAGE (.init.text)
    LINUXIMAGE (.init.data)
		. = ALIGN(16);
    LINUXIMAGE (.init.setup)
    LINUXIMAGE (.initcall.init)
    LINUXIMAGE (.con_initcall.init)
    LINUXIMAGE (.security_initcall.init)

#if (CONFIG_KERNEL_ROOTMEM_INITRAMFS == 1)
		. = ALIGN(4096);
    LINUXIMAGE (.init.ramfs)
#endif

		. = ALIGN(32);
    LINUXIMAGE (.data.percpu)
		. = ALIGN(4096);
  	__init_end = .;
  	. = ALIGN(32);
    LINUXIMAGE (.data.cacheline_aligned)
        }

	bss_start = .; 
	.bss : {
                *(.bss)
        }
	bss_end = .; 
	
#if (CONFIG_KERNEL_ROOTMEM_ROMFS == 1)
        .rdimage : {
                . = ALIGN(0x1000);
                initrd_start = .;
                RDIMAGE 
                initrd_end = .;
		. = ALIGN(16);
        }
#endif

        /DISCARD/ : {
                *(.exit.text)
                *(.exit.data)
                *(.exitcall.exit)
                *(.comment)
                *(.debug_aranges)
                *(.debug_pubnames)
                *(.debug_abbrev)
                *(.debug_info)
                *(.debug_line)
                *(.debug_frame)
                *(.debug_str)
                *(.debug_ranges)
        }
}
