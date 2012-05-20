OUTPUT_FORMAT("elf32-sparc", "elf32-sparc", "elf32-sparc")
OUTPUT_ARCH(sparc)
ENTRY(_start)
SECTIONS
{
        .rom 0 : {
                _start = .;
                prom_stage1.o(.text)
        }

        . = 0x40000000;
        .stage2 : {
                prom_stage2.o(.img.main.text)
                prom_stage2.o
                . = ALIGN(0x1000);
                pgt.o
        }
        . = ALIGN(0x4000);
        .vmlinux : {
                /* check layout: resemble vmlinux's layout (sparc-linux-objdump -s vmlinux)*/
                /home/eiselekd/snapgear/snapgear-patch/images/image (.text)
                /home/eiselekd/snapgear/snapgear-patch/images/image (.rodata)
                /home/eiselekd/snapgear/snapgear-patch/images/image (.pci_fixup)
                /home/eiselekd/snapgear/snapgear-patch/images/image (__ksymtab)
                /home/eiselekd/snapgear/snapgear-patch/images/image (__ksymtab_gpl)
                /home/eiselekd/snapgear/snapgear-patch/images/image (__kcrctab)
                /home/eiselekd/snapgear/snapgear-patch/images/image (__kcrctab_gpl)
                /home/eiselekd/snapgear/snapgear-patch/images/image (__param)
                /home/eiselekd/snapgear/snapgear-patch/images/image (.data)
                /home/eiselekd/snapgear/snapgear-patch/images/image (.data.init)
                /home/eiselekd/snapgear/snapgear-patch/images/image (.fixup)
                /home/eiselekd/snapgear/snapgear-patch/images/image (__ex_table)
                . = ALIGN(4096);
                /home/eiselekd/snapgear/snapgear-patch/images/image (.init.text)
                /home/eiselekd/snapgear/snapgear-patch/images/image (.init.data)
                . = ALIGN(16);
                /home/eiselekd/snapgear/snapgear-patch/images/image (.init.setup)
                /home/eiselekd/snapgear/snapgear-patch/images/image (__param)
                /home/eiselekd/snapgear/snapgear-patch/images/image (.initcall.init)
                /home/eiselekd/snapgear/snapgear-patch/images/image (.con_initcall.init)
                /home/eiselekd/snapgear/snapgear-patch/images/image (.security_initcall.init)
                . = ALIGN(4096);
                /home/eiselekd/snapgear/snapgear-patch/images/image (.init.ramfs)
                . = ALIGN(32);
                . = ALIGN(4096);
                . = ALIGN(32);
                /home/eiselekd/snapgear/snapgear-patch/images/image (.data.cacheline_aligned)
        }

        .bss : {
                *(.bss)
        }

        .rdimage : {
                . = ALIGN(0x1000);
                initrd_start = .;
                /home/eiselekd/snapgear/snapgear-patch/images/rdimage.o
                initrd_end = .;
        }

        /DISCARD/ : {
                *(.exit.text)
                *(.exit.data)
                *(.exitcall.exit)
                *(.comment)
        }
}
