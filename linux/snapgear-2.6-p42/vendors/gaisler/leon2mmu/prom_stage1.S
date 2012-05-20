#define CONFIG_LEON
#define CONFIG_LEON3

/*
 * prom.S
 *
 * a minimal boot prom for essential initialisations.
 * most values are hardcoded and/or can be configured
 * in prom_config.h
 *
 * Copyright (C) 2004 Stefan Holst <mail@s-holst.de>
 *
 */

#include "prom_config.h"

	.seg	"text"

_start:
	wr	%g0, 0xfe0, %psr
	mov	%g0, %tbr
	mov	%g0, %wim
	flush
	set	PREGS, %g1		! on-chip register base address

        st    %g2, [%g1 + 0x14]	! clear some LEON registers
        st    %g0, [%g1 + 0x08]     
        st    %g0, [%g1 + 0x90]     
        st    %g0, [%g1 + 0x94]    
        st    %g0, [%g1 + 0x98]   
        st    %g0, [%g1 + 0x9C]  
        st    %g0, [%g1 + 0xA0] 
        st    %g0, [%g1 + 0xA4]
        st    %g0, [%g1 + 0xA8]
        st    %g0, [%g1 + 0x78]
        st    %g0, [%g1 + 0x88]
        
	set	0xaa00, %g2		! io port initialization
	st    %g2, [%g1 + 0xA0] 

#ifdef ENABLE_CACHE
cache:
	set	0x1000f, %g2
	st	%g2, [%g1 + CCTRL]	! enable cache
#endif

fpu:
	ld	[%g1 + LCONF], %o1	! probe for Meiko FPU
	and	%o1, 0x10, %o1
	sll	%o1, 8, %o1
	wr	%o1, 0xe0, %psr

	set	BOOTLOADER_memcfg1, %g2		! Load memory config register 1
	ld	[%g1], %g3		! 
	and	%g3, 0x300, %g3
	or	%g2, %g3, %g2
  	st	%g2, [%g1 + MCFG1]
	set	BOOTLOADER_memcfg2, %g2
	st	%g2, [%g1 + MCFG2]
 
stackp:
	set	BOOTLOADER_stack, %fp  
	andn	%fp, 0x0f, %fp
	sub	%fp, 64, %sp           

timer:
	set	(BOOTLOADER_FREQ_KHZ+500)/1000, %g2	! Load timer scaler register
	sub	%g2, 1, %g2
	st	%g2, [%g1 + SRLD]
	st	%g2, [%g1 + SCNT] 

uart1:
	set	0x8000, %g2		! set pio directions for serial io
	st	%g2, [%g1 + IODIR]
	st	%g0, [%g1 + USTAT0]	
	set	3, %g2
	st	%g2, [%g1 + UCTRL0]	! enable receiver and transmitter

        set	BOOTLOADER_uart, %g2		! Load UART scaler register
	st	%g2, [%g1 + USCAL0]
  	

#ifdef JUMP_TO

jump:	
	set	JUMP_TO, %o1
	call	%o1
	nop

#endif


dead:	ta 0				! if call returns...
	nop

