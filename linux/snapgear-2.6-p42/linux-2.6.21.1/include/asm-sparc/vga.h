/*
 *	Access to VGA videoram
 *
 *	(c) 1998 Martin Mares <mj@ucw.cz>
 */

#ifndef _LINUX_ASM_VGA_H_
#define _LINUX_ASM_VGA_H_

//#define DEBUG_SC_RW

#include <asm/types.h>
#include <asm/leon.h>

#if defined(CONFIG_LEON_3) && defined(CONFIG_VT) && defined(CONFIG_VGA_CONSOLE)

#define VT_BUF_HAVE_RW

#undef scr_writew
#undef scr_readw

#define LEON_VGAMEM_SIZE (80*51)

extern short leon_video_mem[LEON_VGAMEM_SIZE];

#define IS_VIDEO_MEMORY(a) (((unsigned long)(a) - (unsigned long)&leon_video_mem) < sizeof(leon_video_mem))
#define LEON_VGAMEM_MEM2OFF(a) (((unsigned long)(a)-(unsigned long)&leon_video_mem)/sizeof(short))
#define LEON_VGAMEM_WRITE(off,v) do {  \
   if (leon_apbvga != 0) { \
       LEON_BYPASS_STORE_PA(&leon_apbvga->write,(off<<8) | (v & 0xff)); \
   } \
} while(0)

static inline void scr_writew(u16 val, u16 *addr) {
  unsigned off = 0; unsigned char v = val & 0xff;
  if (!IS_VIDEO_MEMORY(addr) ) {
    //dbg_printf("write outside buffer %x\n",addr);
    return;
  }
  //dbg2_printf("%x\n",val);
  
  *addr = val;
  off = LEON_VGAMEM_MEM2OFF(addr);
  LEON_VGAMEM_WRITE(off,v);
  #ifdef DEBUG_SC_RW
  HARDDBG_OUT("[%08x<-%04x]\n",(unsigned int)addr,(unsigned int)val);
  #endif
}

static inline u16 scr_readw(const u16 *addr) {
  #ifdef DEBUG_SC_RW
  HARDDBG_OUT("[%08x]\n",(unsigned int)addr);
  #endif
  if (!IS_VIDEO_MEMORY(addr) )
    return 0;
  return *addr;
}

#define VGA_MAP_MEM(x,s) (x)
#endif /* defined(CONFIG_LEON_3) && defined(CONFIG_VT) && defined(CONFIG_VGA_CONSOLE) */

#endif
