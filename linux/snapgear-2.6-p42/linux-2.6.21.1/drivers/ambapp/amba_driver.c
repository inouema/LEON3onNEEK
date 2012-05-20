#include <linux/ptrace.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/module.h>

#include <asm/leon.h>

//#define DEBUG_CONFIG

/* Structure containing address to devices found on the Amba Plug&Play bus */
extern amba_confarea_type amba_conf;


//get number of apb slaves
int amba_get_number_apbslv_devices(int vendor, int device)
{
	int i,j=0,conf;
        amba_confarea_type *a_conf = &amba_conf;
        
        while (a_conf != NULL) {
           for (i = 0; i < a_conf->apbslv.devnr ; i++) {
              conf = amba_get_confword(a_conf->apbslv, i, 0);
              if ((amba_vendor(conf) == vendor)
                  && (amba_device(conf) == device))
                 j++;
           }
           a_conf = a_conf->next;
        }
        return j;
}

int amba_find_next_apbslv_devices(int vendor, int device, amba_apb_device * dev, int nr)
{
	unsigned int i, conf, iobar, j = 0;
	amba_confarea_type *a_conf = &amba_conf;

#ifdef DEBUG_CONFIG
	printk("Apbslv: search for apdslv devices v:0x%x d:0x%x\n",vendor,device);
#endif
        while (a_conf != NULL) {
           for (i = 0; i < a_conf->apbslv.devnr; i++) {
              conf = amba_get_confword(a_conf->apbslv, i, 0);
#ifdef DEBUG_CONFIG
              printk("Apbslv: check(%x:%x)==(%x:%x)\n", vendor, device,
                     amba_vendor(conf), amba_device(conf));
#endif
              if ((amba_vendor(conf) == vendor) && (amba_device(conf) == device)) {
                 if (j == nr) {
		    dev[0].irq = amba_irq(conf);
		    iobar =
			amba_apb_get_membar(a_conf->apbslv, i);
#ifdef DEBUG_CONFIG
		    printk("Apbslv: found device idx %i cfgidx:%d(%x:%x) iobar 0x%08x at addr:0x%08x\n",
			   j, i, vendor, device,iobar,(a_conf->apbslv).addr[(i)]+1);
#endif
		    dev[0].start =
			amba_iobar_start(a_conf->apbslv.apbmst[i], iobar);
#ifdef DEBUG_CONFIG
		    printk(" +bar: 0x%x base:0x%x iobar:0x%x\n", dev[0].start,a_conf->apbslv.apbmst[i],((((iobar) & 0xfff00000)>>12) & (((iobar) & 0xfff0)<<4)));
#endif

                    dev[0].bus = a_conf;

		    return 1;
                 }
                 j++;
              }
           }
           a_conf = a_conf->next;
        }
        return 0;
}

//collect apb slaves
int amba_get_free_apbslv_devices(int vendor, int device, amba_apb_device * dev,
				 int nr)
{
	unsigned int i, conf, iobar, j = 0;
        amba_confarea_type *a_conf = &amba_conf;
#ifdef DEBUG_CONFIG
	printk("Apbslv: search for apbslv devices\n");
#endif
        while (a_conf != NULL) {
           for (i = 0; i < a_conf->apbslv.devnr && j < nr; i++) {
              conf = amba_get_confword(a_conf->apbslv, i, 0);
#ifdef DEBUG_CONFIG
              printk("Apbslv: check(%x:%x)==(%x:%x)\n", vendor, device,
		       amba_vendor(conf), amba_device(conf));
#endif
              if ((amba_vendor(conf) == vendor)
                  && (amba_device(conf) == device)) {
                 if (!
                     (a_conf->apbslv.
                      allocbits[i / 32] & (1 << (i & (32 - 1))))) {
#ifdef DEBUG_CONFIG
                    printk("Apbslv: alloc device idx %i (%x:%x)\n",
                           j, vendor, device);
#endif
                    a_conf->apbslv.allocbits[i / 32] |=
                       (1 << (i & (32 - 1)));
                    dev[j].irq = amba_irq(conf);
                    iobar =
                       amba_apb_get_membar(a_conf->apbslv, i);
                    dev[j].start =
                       amba_iobar_start(a_conf->apbslv.apbmst[i], iobar);
                    dev[j].bus_id = i; 
#ifdef DEBUG_CONFIG
                    printk(" +bar: 0x%x \n", dev[j].start);
#endif
                    dev[j].bus = a_conf;
                    
                    j++;
                 }
              }
           }
           a_conf = a_conf->next;
        }
	return j;
}

void amba_free_apbslv_device(amba_apb_device * dev){

       dev->bus->apbslv.allocbits[dev->bus_id / 32] &= ~(1 << (dev->bus_id & (32 - 1)));
       
}

//get number of ahb slaves
int amba_get_number_ahbslv_devices(int vendor, int device)
{

	int i,j=0,conf;
        amba_confarea_type *a_conf = &amba_conf;

        while (a_conf != NULL) {
           for (i = 0; i < a_conf->ahbslv.devnr ; i++) {
              conf = amba_get_confword(a_conf->ahbslv, i, 0);
              if ((amba_vendor(conf) == vendor)
                  && (amba_device(conf) == device))
                 j++;
           }
           a_conf = a_conf->next;
        }
	return j;
}

//collect ahb slaves
int amba_get_free_ahbslv_devices(int vendor, int device, amba_ahb_device * dev,
				 int nr)
{
	unsigned int addr, i, conf, iobar, j = 0, k;
        amba_confarea_type *a_conf = &amba_conf;

#ifdef DEBUG_CONFIG
	printk("Ahbslv: search for ahbslv devices\n");
#endif
        while (a_conf != NULL) {
	for (i = 0; i < a_conf->ahbslv.devnr && j < nr; i++) {
		conf = amba_get_confword(a_conf->ahbslv, i, 0);
#ifdef DEBUG_CONFIG
		printk("Ahbslv: check(%x:%x)==(%x:%x)\n", vendor, device,
		       amba_vendor(conf), amba_device(conf));
#endif
		if ((amba_vendor(conf) == vendor)
		    && (amba_device(conf) == device)) {
			if (!
			    (a_conf->ahbslv.
			     allocbits[i / 32] & (1 << (i & (32 - 1))))) {
#ifdef DEBUG_CONFIG
				printk("Ahbslv: alloc device idx %i (%x:%x)\n",
				       j, vendor, device);
#endif
				a_conf->ahbslv.allocbits[i / 32] |=
				    (1 << (i & (32 - 1)));
				dev[j].irq = amba_irq(conf);
				dev[j].bus_id = i;
                                dev[j].bus = a_conf;
				for (k = 0; k < 4; k++) {
					iobar =
					    amba_ahb_get_membar(a_conf->
								ahbslv, i, k);
					addr = amba_membar_start(iobar);
					if (amba_membar_type(iobar) ==
					    AMBA_TYPE_AHBIO) {
						addr =
						    AMBA_TYPE_AHBIO_ADDR(addr);
					}
					dev[j].start[k] = addr;
#ifdef DEBUG_CONFIG
					printk(" +%i: 0x%x \n", k,
					       dev[j].start[k]);
#endif
				}
				j++;
			}
		}
	}
        a_conf = a_conf->next;
        }
	return j;
}

void amba_free_ahbslv_device(amba_ahb_device * dev){

	dev->bus->ahbslv.allocbits[dev->bus_id / 32] &= ~(1 << (dev->bus_id & (32 - 1)) );

}

EXPORT_SYMBOL(amba_get_number_apbslv_devices);
EXPORT_SYMBOL(amba_get_free_apbslv_devices);
EXPORT_SYMBOL(amba_free_apbslv_device);

EXPORT_SYMBOL(amba_get_number_ahbslv_devices);
EXPORT_SYMBOL(amba_get_free_ahbslv_devices);
EXPORT_SYMBOL(amba_free_ahbslv_device);

