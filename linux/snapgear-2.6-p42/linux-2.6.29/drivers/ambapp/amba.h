#ifndef DRIVERS_AMBAPP_AMBA_H
#define DRIVERS_AMBAPP_AMBA_H

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

#ifndef __ASSEMBLER__
extern unsigned long amba_find_apbslv_addr(unsigned long vendor,
					   unsigned long device,
					   unsigned long *irq);
extern int amba_get_free_apbslv_devices(int vendor, int device, amba_apb_device * dev,
					int nr);

extern int amba_is_init;


#endif

#endif
