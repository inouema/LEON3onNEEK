/*
 *
 */

#define CONFIG_LEON
#define CONFIG_LEON3
#include <asm/leon.h>
#include <asm/ambapp.h>
#include "prom_config.h"

/* Entry for traps which jump to a programmer-specified trap handler.  */
#define TRAPR(H)  wr %g0, 0xfe0, %psr; mov %g0, %tbr; ba (H); mov %g0, %wim;
#define TRAP(H)  mov %psr, %l0; sethi %hi(H), %l4; jmp %l4+%lo(H); nop;

/* Unexcpected trap will halt the processor by forcing it to error state */
#undef BAD_TRAP
#define BAD_TRAP ta 0; nop; nop; nop;

/* Software trap. Treat as BAD_TRAP for the time being... */
#define SOFT_TRAP TRAP(_hwerr)

#define PSR_INIT   0x1FC0	/* Disable traps, set s and ps */
#define WIM_INIT   2

WINDOWSIZE = (16 * 4)
ARGPUSHSIZE = (6 * 4)
ARGPUSH = (WINDOWSIZE + 4)
MINFRAME = (WINDOWSIZE + ARGPUSHSIZE + 4)
#define STACK_ALIGN	8
#define SA(X)	(((X)+(STACK_ALIGN-1)) & ~(STACK_ALIGN-1))
	
  .section        ".start", "ax"
  .global _trap_table, start, _memcfg1, _memcfg2, _stack, _ftreg, bdinit1, bdinit2, main
  .global bootaddress


  /* Hardware traps */
start:
_trap_table:
  TRAPR(_hardreset);		! 00 reset trap 
  BAD_TRAP;      		! 01 instruction_access_exception
  BAD_TRAP;      		! 02 illegal_instruction
  BAD_TRAP;      		! 03 priveleged_instruction
  BAD_TRAP;		        ! 04 fp_disabled
  TRAP(_window_overflow);	! 05 window_overflow
  TRAP(_window_underflow);	! 06 window_underflow
	
        
!unsigned int ahbslv_scan(register unsigned int vendor,register unsigned int driver) {
!  register unsigned int conf, mbar,i, *confp;
!  register unsigned int cfg_area = (unsigned int ) (LEON3_IO_AREA | LEON3_CONF_AREA | LEON3_AHB_SLAVE_CONF_AREA);
!  for (i = 0; i < LEON3_AHB_SLAVES; i++) 
!  {
!    confp = (unsigned int*)(cfg_area + (i * LEON3_AHB_CONF_WORDS * 4));
!    conf = *confp;
!    //mbar = *(unsigned int*)(i * LEON3_AHB_CONF_WORDS+ (4 * 4));
!    if ((amba_vendor(conf) == vendor) && (amba_device(conf) == driver)) {
!      return (unsigned int)confp;
!    }
!  }
!  return 0;
!} 

        
	
         
	.section	".text"
	.align 4
ahbslv_scan:
	mov	%o0, %g1
	mov	-2048, %o5
	mov	0, %o3
	sll	%o3, 5, %o0
.LL11:
	add	%o5, %o0, %o4
	ld	[%o5+%o0], %o2
	srl	%o2, 24, %o0
	cmp	%o0, %g1
	bne,a	.LL10
	add	%o3, 1, %o3
	srl	%o2, 12, %o0
	and	%o0, 4095, %o0
	cmp	%o0, %o1
	be	.LL1
	mov	%o4, %o2
	add	%o3, 1, %o3
.LL10:
	cmp	%o3, 7
	bleu,a	.LL11
	sll	%o3, 5, %o0
	mov	0, %o2
.LL1:
	retl
	mov	%o2, %o0


!unsigned int apbslv_scan(register unsigned int base,register unsigned int vendor, register unsigned int driver) {
!  register unsigned int conf, mbar,i, *confp;
!  for (i = 0; i < LEON3_APB_SLAVES; i++) 
!  {
!    confp = (unsigned int*)(base + (i * LEON3_APB_CONF_WORDS * 4));
!    conf = *confp;
!    //mbar = *(unsigned int*)(i * LEON3_AHB_CONF_WORDS+ (4 * 4));
!    if ((amba_vendor(conf) == vendor) && (amba_device(conf) == driver)) {
!      return (unsigned int)confp;
!    }
!  }
!  return 0;
!}


         
	.section	".text"
	.align 4

apbslv_scan:
	mov	%o0, %g1
	mov	0, %o4
	sll	%o4, 3, %o0
.LL22:
	add	%g1, %o0, %o5
	ld	[%g1+%o0], %o3
	srl	%o3, 24, %o0
	cmp	%o0, %o1
	bne,a	.LL21
	add	%o4, 1, %o4
	srl	%o3, 12, %o0
	and	%o0, 4095, %o0
	cmp	%o0, %o2
	be	.LL12
	mov	%o5, %o3
	add	%o4, 1, %o4
.LL21:
	cmp	%o4, 15
	bleu,a	.LL22
	sll	%o4, 3, %o0
	mov	0, %o3
.LL12:
	retl
	mov	%o3, %o0



!unsigned int getbase(register unsigned int *mbar,register unsigned int iobase) {
!  register unsigned int conf = mbar[1];
!  return ((iobase & 0xfff00000) |
!          ((conf & 0xfff00000)>> 12)) & (((conf & 0x0000fff0) <<4) | 0xfff00000);
!  
!}
        
         
	.section	".text"
	.align 4

getbase:
	ld	[%o0+4], %o2
	sethi	%hi(-1048576), %o3
	and	%o1, %o3, %o1
	and	%o2, %o3, %o0
	srl	%o0, 12, %o0
	or	%o1, %o0, %o1
	sethi	%hi(64512), %o0
	or	%o0, 1008, %o0
	and	%o2, %o0, %o2
	sll	%o2, 4, %o2
	or	%o2, %o3, %o2
	and	%o1, %o2, %o1
	retl
	mov	%o1, %o0
        

_hardreset:
1000:
	flush

	set	0x1000f, %g2
        sta %g2, [%g0] 2          ! init cache
	
	mov %g0, %y
	clr	%g1
	clr	%g2
	clr	%g3
	clr	%g4
	clr	%g5
	clr	%g6
	clr	%g7
        
	mov %asr17, %g3
	and %g3, 0x1f, %g3
1:
	mov %g0, %l0
	mov %g0, %l1
	mov %g0, %l2
	mov %g0, %l3
	mov %g0, %l4
	mov %g0, %l5
	mov %g0, %l6
	mov %g0, %l7
	mov %g0, %o0
	mov %g0, %o1
	mov %g0, %o2
	mov %g0, %o3
	mov %g0, %o4
	mov %g0, %o5
	mov %g0, %o6
	mov %g0, %o7
	subcc %g3, 1, %g3
	bge 1b
	save

        set VENDOR_GAISLER, %o0
        set GAISLER_APBMST, %o1
        call ahbslv_scan
        nop
        
        cmp %g0,%o0
        be _start
         nop
        
        ld [%o0+16],%g1
        set LEON3_IO_AREA,%o0
        and %g1,%o0,%g1            !g1: apb base

        set LEON3_CONF_AREA,%o0
        or %g1,%o0,%g2             !g2: apb conf base


	! *********** irq *****************
        mov %g2,%o0
        set VENDOR_GAISLER, %o1
        set GAISLER_IRQMP,%o2
        call apbslv_scan
         nop
        cmp %g0,%o0
        be _start
         nop
        
        call getbase
         mov %g1,%o1
                        
        st    %g0, [%o1 + 0x0]  !irq pri   
        st    %g0, [%o1 + 0x4]  !irq pend  
        st    %g0, [%o1 + 0x8]  !irq force 
        st    %g0, [%o1 + 0xC]  !irq clear
				st		%g0, [%o1 + 0x40] !irq mask processor 0
				st		%g0, [%o1 + 0x80] !irq force processor 0	

	! ************ timer ************

        mov %g2,%o0
        set VENDOR_GAISLER, %o1
        set GAISLER_GPTIMER,%o2
        call apbslv_scan
         nop
        cmp %g0,%o0
        be _start
         nop
        
        call getbase
         mov %g1,%o1
        
	set	(BOOTLOADER_FREQ_KHZ+500)/1000, %o0		! Load timer scaler register
	sub	%o0, 1, %o0
  	st	%o0, [%o1 + 0x00] ! scaler
  	st	%o0, [%o1 + 0x04] ! scaler reload

	! ************ mctrl ************
	
        mov %g2,%o0                  ! esa mctrl
        set VENDOR_ESA, %o1
        set ESA_MCTRL,%o2
        call apbslv_scan
         nop
        cmp %g0,%o0
        be LL1mctlsdram
         nop

        call getbase
         mov %g1,%o1

	set	BOOTLOADER_memcfg1, %o0		! Load memory config register 1
	ld	[%o1+0x00], %o2		
	and	%o2, 0x300, %o2
	or	%o0, %o2, %o0
  	st	%o0, [%o1 + 0x00]
	set	BOOTLOADER_memcfg2, %o0          ! Load memory config register 2
	st	%o0, [%o1 + 0x04]
	set	((BOOTLOADER_grlib_sdram & 0x7FFF)<<12), %o0
	st	%o0, [%o1 + 0x8]
	
	ba	LL1mctlok
	nop

	! ************ gaisler sdram mctrl ************
	
LL1mctlsdram:

        set VENDOR_GAISLER, %o0
        set GAISLER_SDCTRL, %o1
        call ahbslv_scan
        nop
        
        cmp %g0,%o0
        be LL1ddr2spa               ! Scan for DDR controller
         nop

        ld [%o0+16+4],%g1            ! get io bar
        set LEON3_IO_AREA,%o0
        and %g1,%o0,%g1
	srl %g1,12,%g1
        or  %g1,%o0,%g1
	

	set	BOOTLOADER_grlib_sdram, %o0
	st	%o0, [%g1 + 0x100]
	b	LL1mctlok           ! Assume no DDR/DDR2 RAM controller
	nop
  
 	! ************ gaisler DDR2 ctrl (DDR2SPA) ************
	
LL1ddr2spa:

        set VENDOR_GAISLER, %o0
        set GAISLER_DDR2SPA, %o1
        call ahbslv_scan
        nop
        
        cmp %g0,%o0
        be LL1ddrspa                ! Scan for DDR controller
         nop
	
        ld [%o0+16+4],%g1            ! get io bar
        set LEON3_IO_AREA,%o0
        and %g1,%o0,%g1
	srl %g1,12,%g1
        or  %g1,%o0,%g1

	set	BOOTLOADER_ddr2spa_cfg1, %o0
	st	%o0, [%g1]           ! Set DDR2CFG1
	set	BOOTLOADER_ddr2spa_cfg3, %o0
	st	%o0, [%g1+0x08]      ! Set DDR2CFG3
	b	LL1mctlok           ! Assume no DDR SDRAM controller
	nop

 	! ************ gaisler DDR ctrl (DDRSPA) ************
	
LL1ddrspa:

	set VENDOR_GAISLER, %o0
	set GAISLER_DDRSPA, %o1
	call ahbslv_scan
	nop
        
	cmp %g0,%o0
	be LL1mctlok                ! assuming sram/prom ctrl
	nop

        ld [%o0+16+4],%g1            ! get io bar
        set LEON3_IO_AREA,%o0
        and %g1,%o0,%g1
	srl %g1,12,%g1
        or  %g1,%o0,%g1
	
	set	BOOTLOADER_ddrspa_cfg1, %o0
	st	%o0, [%g1]          ! Set SDCTRL

	! ************ uart ************
	
LL1mctlok:		
        mov %g2,%o0
        set VENDOR_GAISLER, %o1
        set 0x23, %o2		! DDRCTRL
        call apbslv_scan
        nop
        
        cmp %g0,%o0
        be LL1uart 
        nop

        call getbase
        mov %g1,%o1

1:
	ld [%o1 + 0x4], %o0
	andcc %o0, 1, %g0
	be 1b
	nop

	set 0x9dc00001, %o0
	st  %o0, [%o1 + 0x4]

	ld [%o1 + 0x4], %o0
	andcc %o0, 1, %g0
	be 1b
	nop


LL1uart:
        mov %g2,%o0
        set VENDOR_GAISLER, %o1
        set GAISLER_APBUART,%o2
        call apbslv_scan
         nop
        cmp %g0,%o0
        be _start
         nop
        
        call getbase
         mov %g1,%o1
        
#define UARTBASE %g5       
        mov %o1,UARTBASE             !uart base address
                
stackp:
	set	WIM_INIT, %g3
	mov	%g3, %wim
	
	set	BOOTLOADER_stack, %fp  
	andn	%fp, 0x0f, %fp
	sub	%fp, 64, %sp           


uart1:

        set	BOOTLOADER_uart, %g2		! Load UART scaler register
	st	%g2, [UARTBASE + 0x0c]  ! uart scalar
#if defined(CONFIG_UARTLOOPBACK) || (BOOTLOADER_loopback==1)
	set	0x83|(BOOTLOADER_flow<<6), %g2			! Enable uarts, (flow ctrl), loopback
#else
	set	0x03|(BOOTLOADER_flow<<6), %g2			! Enable uarts, (flow ctrl)
#endif	  
  	st	%g2, [UARTBASE + 0x08]

	!set	0x8000, %g2		! set pio directions for serial io
	!st	%g2, [%g1 + IODIR]
	!st	%g0, [%g1 + USTAT0]	
	!set	3, %g2
	!st	%g2, [%g1 + UCTRL0]	! enable receiver and transmitter

        !set	BOOTLOADER_uart, %g2		! Load UART scaler register
	!st	%g2, [%g1 + USCAL0]

#ifdef JUMP_TO

	set _bss_start,%g2
	set _bss_end,%g4
2:	stb   %g0,[%g2]
	inc  1,%g2
	cmp  %g2,%g4
	bl   2b
	nop
	
jump:
	set    JUMP_TO,%o1

	/*
	ld     [%o1] , %o2
	
	set    0xf0000000,%o3
	and    %o2,%o3,%o2	
	set    0x90000000,%o3	       ! check weather this is somewhere like a save %sp instr
	cmp    %o2,%o3
	bne    3f
	nop

	! dsumon loaded image, alread there
	call	%o1			! jump to __main, addr should be in 0x40000000
        nop

	ta 	0			! Halt if _main would return ...
	nop

	*/
	! flash resident image, decompress
3:	call	__main		
	nop

	call	%o1			! jump to __main, addr should be in 0x40000000
        nop

	/*
	ta 	0			! Halt if _main would return ...
	nop
	*/
	ba jump
	nop

	
#endif


dead:	ta 0				! if call returns...
	nop

/* Number of register windows */
#define NWINDOWS 	8

  	 		!Window overflow trap handler.
  	.global _window_overflow

	
	
_window_overflow:

  	mov  %wim, %l3       		! Calculate next WIM
  	mov  %g1, %l7           
  	srl  %l3, 1, %g1        
  	sll  %l3, NWINDOWS-1 , %l4
  	or   %l4, %g1, %g1

  	save                              ! Get into window to be saved.
  	mov  %g1, %wim
  	nop; nop; nop
        st   %l0, [%sp + 0];
        st   %l1, [%sp + 4];
        st   %l2, [%sp + 8];
        st   %l3, [%sp + 12];
        st   %l4, [%sp + 16]; 
        st   %l5, [%sp + 20];
        st   %l6, [%sp + 24]; 
        st   %l7, [%sp + 28]; 
        st   %i0, [%sp + 32]; 
        st   %i1, [%sp + 36]; 
        st   %i2, [%sp + 40]; 
        st   %i3, [%sp + 44]; 
        st   %i4, [%sp + 48]; 
        st   %i5, [%sp + 52]; 
        st   %i6, [%sp + 56]; 
        st   %i7, [%sp + 60];
  	restore				! Go back to trap window.
  	mov  %l7, %g1
  	jmp  %l1			! Re-execute save.
  	rett %l2

  /* Window underflow trap handler.  */

  	.global  _window_underflow

_window_underflow:

	mov  %wim, %l3			! Calculate next WIM
	sll  %l3, 1, %l4
  	srl  %l3, NWINDOWS-1, %l5
  	or   %l5, %l4, %l5
  	mov  %l5, %wim
  	nop; nop; nop
  	restore				! Two restores to get into the
  	restore				! window to restore
        ld   [%sp + 0], %l0; 		! Restore window from the stack
        ld   [%sp + 4], %l1; 
        ld   [%sp + 8], %l2; 
        ld   [%sp + 12], %l3; 
        ld   [%sp + 16], %l4; 
        ld   [%sp + 20], %l5; 
        ld   [%sp + 24], %l6; 
        ld   [%sp + 28], %l7; 
        ld   [%sp + 32], %i0; 
        ld   [%sp + 36], %i1; 
        ld   [%sp + 40], %i2; 
        ld   [%sp + 44], %i3; 
        ld   [%sp + 48], %i4; 
        ld   [%sp + 52], %i5; 
        ld   [%sp + 56], %i6; 
        ld   [%sp + 60], %i7;
  	save				! Get back to the trap window.
  	save
  	jmp  %l1			! Re-execute restore.
  	rett  %l2

