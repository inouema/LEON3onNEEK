/* 
 * Copyright (C) 2004 Konrad Eisele (eiselekd@web.de), Gaisler Research
 */

#ifndef _LEON3_AMBA_H__
#define _LEON3_AMBA_H__

/*
 *  AMBA Plag & Play Bus Driver Macros
 *
 *  Macros used for AMBA Plug & Play bus scanning
 *
 *  COPYRIGHT (c) 2004.
 *  Gaisler Research
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 */

#define LEON3_IO_AREA 0xfff00000
#define LEON3_CONF_AREA 0xff000
#define LEON3_AHB_SLAVE_CONF_AREA (1 << 11)

#define LEON3_AHB_CONF_WORDS 8
#define LEON3_APB_CONF_WORDS 2
#define LEON3_AHB_MASTERS 16
#define LEON3_AHB_SLAVES 16
#define LEON3_APB_SLAVES 16
#define LEON3_APBUARTS 8

/* System IDs of LEON ASICs. Taken from GRLIB devices.vhd */
#define LEON3_NEXTREME1		0x0101
#define LEON4_NEXTREME1		0x0102
#define LEON3_RTAX_CID2		0x0202
#define LEON3_RTAX_CID5		0x0205
#define LEON3_RTAX_CID6		0x0206
#define LEON3_RTAX_CID7		0x0207
#define LEON3_RTAX_CID8		0x0208
#define ORBITA_1		0x0631
#define AEROFLEX_UT699		0x0699
#define GAISLER_GR702		0x0702
#define GAISLER_DARE1		0x0704
#define GAISLER_GR712RC		0x0712

/* Vendor codes */
#define VENDOR_GAISLER   1
#define VENDOR_PENDER    2
#define VENDOR_ESA       4
#define VENDOR_OPENCORES 8

/* Gaisler Research device id's */
#define GAISLER_LEON3    0x003
#define GAISLER_LEON3DSU 0x004
#define GAISLER_ETHAHB   0x005
#define GAISLER_APBMST   0x006
#define GAISLER_AHBUART  0x007
#define GAISLER_SRCTRL   0x008
#define GAISLER_SDCTRL   0x009
#define GAISLER_APBUART  0x00C
#define GAISLER_IRQMP    0x00D
#define GAISLER_AHBRAM   0x00E
#define GAISLER_GPTIMER  0x011
#define GAISLER_PCITRG   0x012
#define GAISLER_PCISBRG  0x013
#define GAISLER_PCIFBRG  0x014
#define GAISLER_PCITRACE 0x015
#define GAISLER_PCIDMA   0x016
#define GAISLER_AHBTRACE 0x017
#define GAISLER_ETHDSU   0x018
#define GAISLER_PIOPORT  0x01A
#define GAISLER_GRGPIO   0x01A
#define GAISLER_AHBJTAG  0x01c
#define GAISLER_ETHMAC   0x01D
#define GAISLER_AHB2AHB  0x020
#define GAISLER_USBDC    0x021 
#define GAISLER_ATACTRL  0x024
#define GAISLER_DDRSPA   0x025
#define GAISLER_USBEHC   0x026
#define GAISLER_USBUHC   0x027
#define GAISLER_I2CMST   0x028
#define GAISLER_SPICTRL  0x02D
#define GAISLER_DDR2SPA  0x02E
#define GAISLER_SPIMCTRL 0x045
#define GAISLER_LEON4    0x048
#define GAISLER_LEON4DSU 0x049
#define GAISLER_AHBSTAT  0x052
#define GAISLER_FTMCTRL  0x054
#define GAISLER_KBD      0x060
#define GAISLER_VGA      0x061
#define GAISLER_SVGA     0x063
#define GAISLER_GRSYSMON 0x066
#define GAISLER_GRACECTRL 0x067

#define GAISLER_L2TIME   0xffd	/* internal device: leon2 timer */
#define GAISLER_L2C      0xffe	/* internal device: leon2compat */
#define GAISLER_PLUGPLAY 0xfff	/* internal device: plug & play configarea */

#ifndef __ASSEMBLER__

extern inline char *gaisler_device_str(int id)
{
	switch (id) {
	case GAISLER_LEON3:
		return "GAISLER_LEON3";
	case GAISLER_LEON3DSU:
		return "GAISLER_LEON3DSU";
	case GAISLER_LEON4:
		return "GAISLER_LEON4";
	case GAISLER_LEON4DSU:
		return "GAISLER_LEON4DSU";
	case GAISLER_ETHAHB:
		return "GAISLER_ETHAHB";
	case GAISLER_ETHMAC:
	        return "GAISLER_ETHMAC";
	case GAISLER_APBMST:
		return "GAISLER_APBMST";
	case GAISLER_AHBUART:
		return "GAISLER_AHBUART";
	case GAISLER_SRCTRL:
		return "GAISLER_SRCTRL";
	case GAISLER_SDCTRL:
		return "GAISLER_SDCTRL";
	case GAISLER_APBUART:
		return "GAISLER_APBUART";
	case GAISLER_IRQMP:
		return "GAISLER_IRQMP";
	case GAISLER_AHBRAM:
		return "GAISLER_AHBRAM";
	case GAISLER_GPTIMER:
		return "GAISLER_GPTIMER";
	case GAISLER_PCITRG:
		return "GAISLER_PCITRG";
	case GAISLER_PCISBRG:
		return "GAISLER_PCISBRG";
	case GAISLER_PCIFBRG:
		return "GAISLER_PCIFBRG";
	case GAISLER_PCITRACE:
		return "GAISLER_PCITRACE";
	case GAISLER_PCIDMA:
		return "GAISLER_PCIDMA";
	case GAISLER_AHBTRACE:
		return "GAISLER_AHBTRACE";
	case GAISLER_ETHDSU:
		return "GAISLER_ETHDSU";
	case GAISLER_PIOPORT:
		return "GAISLER_PIOPORT";
	case GAISLER_AHBJTAG:
		return "GAISLER_AHBJTAG";
        case GAISLER_USBDC:        
                return "GAISLER_USBDC";
        case GAISLER_ATACTRL:
		return "GAISLER_ATACTRL";
        case GAISLER_DDRSPA:
		return "GAISLER_DDRSPA";
	case GAISLER_USBEHC:
		return "GAISLER_USBEHC";
	case GAISLER_USBUHC:
		return "GAISLER_USBUHC";
	case GAISLER_I2CMST:
 		return "GAISLER_I2CMST";
	case GAISLER_SPICTRL:
		return "GAISLER_SPICTRL";
	case GAISLER_VGA:
		return "GAISLER_VGA";
	case GAISLER_SVGA:
		return "GAISLER_SVGA";
        case GAISLER_GRSYSMON:
		return "GAISLER_GRSYSMON";
        case GAISLER_GRACECTRL:
		return "GAISLER_GRACECTRL";
	case GAISLER_KBD:
		return "GAISLER_KBD";
        case GAISLER_DDR2SPA:
		return "GAISLER_DDR2SPA";
        case GAISLER_SPIMCTRL:
		return "GAISLER_SPIMCTRL";
        case GAISLER_AHBSTAT:
		return "GAISLER_AHBSTAT";
        case GAISLER_AHB2AHB:
		return "GAISLER_AHB2AHB";
  
	case GAISLER_L2TIME:
		return "GAISLER_L2TIME";
	case GAISLER_L2C:
		return "GAISLER_L2C";
	case GAISLER_PLUGPLAY:
		return "GAISLER_PLUGPLAY";

	default:
		break;
	}
	return 0;
}

#endif

/* European Space Agency device id's */
#define ESA_LEON2        0x2
#define ESA_MCTRL        0xF
#define ESA_PCIARB       0x10

#ifndef __ASSEMBLER__

extern inline char *esa_device_str(int id)
{
	switch (id) {
	case ESA_LEON2:
		return "ESA_LEON2";
	case ESA_MCTRL:
		return "ESA_MCTRL";
	case ESA_PCIARB:
		return "ESA_PCIARB";
	default:
		break;
	}
	return 0;
}

#endif

/* Opencores device id's */
#define OPENCORES_PCIBR  0x4
#define OPENCORES_ETHMAC 0x5

#ifndef __ASSEMBLER__

extern inline char *opencores_device_str(int id)
{
	switch (id) {
	case OPENCORES_PCIBR:
		return "OPENCORES_PCIBR";
	case OPENCORES_ETHMAC:
		return "OPENCORES_ETHMAC";
	default:
		break;
	}
	return 0;
}

extern inline char *device_id2str(int vendor, int id)
{
	switch (vendor) {
	case VENDOR_GAISLER:
		return gaisler_device_str(id);
	case VENDOR_ESA:
		return esa_device_str(id);
	case VENDOR_OPENCORES:
		return opencores_device_str(id);
	case VENDOR_PENDER:
	default:
		break;
	}
	return 0;
}

extern inline char *vendor_id2str(int vendor)
{
	switch (vendor) {
	case VENDOR_GAISLER:
		return "VENDOR_GAISLER";
	case VENDOR_ESA:
		return "VENDOR_ESA";
	case VENDOR_OPENCORES:
		return "VENDOR_OPENCORES";
	case VENDOR_PENDER:
		return "VENDOR_PENDER";
	default:
		break;
	}
	return 0;
}

#ifdef CONFIG_AMBA_PROC
int amba_read_procmem(char *buf, char **start, off_t offset, int count, int *eof, void *data);
#endif
 
#endif

/* Vendor codes */

/* 
 *
 * Macros for manipulating Configuration registers  
 *
 */

#define LEON3_BYPASS_LOAD_PA(x)	(leon_load_reg ((unsigned long)(x)))
#define LEON3_BYPASS_STORE_PA(x,v) (leon_store_reg ((unsigned long)(x),(unsigned long)(v)))

#define LEON3_BYPASS_ANDIN_PA(x,v) LEON3_BYPASS_STORE_PA(x,LEON3_BYPASS_LOAD_PA(x) & v)
#define LEON3_BYPASS_ORIN_PA(x,v) LEON3_BYPASS_STORE_PA(x,LEON3_BYPASS_LOAD_PA(x) | v)

#define amba_get_confword(tab, index, word) (LEON3_BYPASS_LOAD_PA((tab).addr[(index)]+(word)))

#define amba_vendor(x) (((x) >> 24) & 0xff)

#define amba_device(x) (((x) >> 12) & 0xfff)

#define amba_ahb_get_membar(tab, index, nr) (LEON3_BYPASS_LOAD_PA((tab).addr[(index)]+4+(nr)))

#define amba_ahb_get_custom(tab, index, nr) (LEON3_BYPASS_LOAD_PA((tab).addr[(index)]+1+(nr)))

#define amba_apb_get_membar(tab, index) (LEON3_BYPASS_LOAD_PA((tab).addr[(index)]+1))

#define amba_membar_start(mbar) (((mbar) & 0xfff00000) & (((mbar) & 0xfff0) << 16))

#define amba_iobar_start(base, iobar) ((base) | ((((iobar) & 0xfff00000)>>12) & (((iobar) & 0xfff0)<<4)) )

#define amba_irq(conf) ((conf) & 0x1f)

#define amba_membar_type(mbar) ((mbar) & 0xf)

#define AMBA_TYPE_APBIO 0x1
#define AMBA_TYPE_MEM   0x2
#define AMBA_TYPE_AHBIO 0x3

#define AMBA_TYPE_AHBIO_ADDR(addr) (LEON3_IO_AREA | ((addr) >> 12))
#endif
