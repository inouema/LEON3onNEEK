#include "remove_predefs.h"
#include "bootloader.h"

bootaddress = BOOTLOADER_physbase/*0x40000000*/;
	
OUTPUT_ARCH(sparc)
ENTRY(_start)
SECTIONS
{
  . = 0;
  _load_addr = .;

  . = 0;
  _text = .;

  .text : {
    _start = .;
    *(.start)
    *(.text)
    *(.fixup)
    *(.gnu.warning)
    *(.rodata)
    *(.rodata.*)
    *(.glue_7)
    *(.glue_7t)
    . = ALIGN(4);
    input_data = .;
    PIGGY
    input_data_end = .;

    _got_start = .;
    *(.got) 
    _got_end = .;
    *(.got.plt)

    . = ALIGN(4);
  }
  _etext = .;
  
  . = BOOTLOADER_physbase/*0x40000000*/ + DATA_START;
  .data			: { *(.data) }
  _edata = .;
  _bss_start = .;
  __bss_start = .;
  .bss			: { *(.bss) }
  _bss_end = .;
  _end = .;

  .stack (NOLOAD)	: { *(.stack) }

  .stab 0		: { *(.stab) }
  .stabstr 0		: { *(.stabstr) }
  .stab.excl 0		: { *(.stab.excl) }
  .stab.exclstr 0	: { *(.stab.exclstr) }
  .stab.index 0		: { *(.stab.index) }
  .stab.indexstr 0	: { *(.stab.indexstr) }
  .comment 0		: { *(.comment) }
}

