/*
 * drivers/ide/atactrl.c
 * Amba generic IDE interface
 */

#include <linux/init.h>
#include <linux/ide.h>
#include "ide-timing.h"
#include <linux/delay.h>

#include <asm/io.h>
#include <asm/irq.h>

#include <asm/leon.h>

#define ctrl  (0) // Control register                  
#define stat  (1) // Status register
#define pctr  (2) // PIO compatible timing register
#define pftr0 (3) // PIO fast timing register device 0
#define pftr1 (4) // PIO fast timing register device 1
#define dtr0  (5) // DMA timing register device 0
#define dtr1  (6) // DMA timing register device 1
#define bmcmd (7)  // Bus master IDE command register
#define bmvd0 (8)  // Device specific (reserved)
#define bmsta (9)  // Bus master IDE status register
#define bmvd1 (10) // Device specific (reserved)
#define prdtb (11) // Bus master IDE PRD table address

#define REMAP_CNT 12
   
struct p_timing { 
   unsigned short T1;
   unsigned short T2;
   unsigned short T4;
   unsigned short Teoc;
};

/* Multi word DMA timing parameters */
struct d_timing { 
   unsigned short Tm;   /* CS valid to DIOW/DIOR  */
   unsigned short Td;   /* DIOW/DIOR pulse width  */
   unsigned short res;  /* reserved               */
   unsigned short Teoc; /* End of cycle time      */
};

struct atactrl_s {
	unsigned long port[12];
	unsigned int  freq;
  int           dma_core;
};

static struct atactrl_s *data = NULL;

// PIO mode timing [T1 T2 T4 Teoc]
static struct p_timing piom[] = {
   { 70, 290, 30, 240 },
   { 50, 290, 20,  40 },
   { 30, 290, 15,  10 },
   { 30,  80, 10,  70 },
   { 25,  70, 10,  25 }
};

/* Multi word DMA mode timing [Tm Td res Teoc] in nS  */
/* Teoc = T0 - Tm -Td   */
static struct d_timing dmam[] = {
   { 50, 215,  0, 215 },  /*mode0, 480-50-215=215 */
   { 30,  80,  0,  40 },  /*mode1, 150-30-80=40   */
   { 25,  70,  0,  25 }   /*mode2, 120-25-70=25   */
};

static u8 atac_inb(unsigned long port){
   unsigned int tmp = *(unsigned int*)port;
   //printk("atac_inb %x : %x\n",(unsigned int)port,(tmp & 0xff));
   return tmp & 0xff;
}
static void atac_outb(u8 val, unsigned long port){
   //printk("atac_outb %x : %x\n",(unsigned int)port, (unsigned int)val);
   *(unsigned int*)port = (unsigned int)val;
}
static void atac_outw(u16 val, unsigned long port){
   //printk("atac_outw %08x : %x\n",(unsigned int)port, (unsigned int)val);
   *(unsigned int*)port = (unsigned int)((val & 0xff)<<8 | ((val>>8) & 0xff));
}

void atac_outl(u32 val, unsigned long port){
   //printk("atac_outl %08x : %x\n",(unsigned int)port, (unsigned int)val);
   *(unsigned int*)port = (unsigned int)((val));
}

static void atac_outsw(unsigned long port, void *addr, u32 count){
   unsigned char *a = addr;
   unsigned int tmp;
   unsigned int index = 0;
   //printk("atac_outsw: port: %x count: %x\n",(unsigned int)port, (unsigned int)count);
   while(count--){
      tmp = (unsigned int)((a[index+1])<<8 | ((a[index])));
      index +=2;
      *(unsigned int*)port = tmp;      
      //printk("%08x ",tmp);
      //if (!index & 8) printk("\n");
   }
   //printk("\n");
}

static u16 atac_inw(unsigned long port){
   unsigned int tmp = *(unsigned int*)port;
   //printk("atac_inw %x : %x\n",(unsigned int)port,(tmp & 0xffff));
   return (u16) ((tmp & 0xff)<<8 | ((tmp>>8) & 0xff));
}
static void atac_outbsync(ide_drive_t *drive, u8 val, unsigned long port){
   //printk("atac_outbsync %x : %x\n",(unsigned int)port, (unsigned int)val);
   *(unsigned int*)port = (unsigned int)val;
}

static void atac_insw(unsigned long port, void *addr, u32 count){
   unsigned int tmp;
   unsigned short *a = addr;
   unsigned int index = 0;
   //printk("atac_insw: port: %x count: %x\n",(unsigned int)port, (unsigned int)count);
   while(count--){
      tmp = *(unsigned int*)port;
      a[index++] = (unsigned short)((tmp & 0xff)<<8 | ((tmp>>8) & 0xff));
      //printk("%x ",(tmp & 0xffff));
      //if (!(index % 10)) printk("\n");
   }
   //printk("\n");
}
// Calculate timing values
static u8 Tvalue(unsigned short T, unsigned int freq){
   int tmp = ((T*freq)/1000) - 1;
   if (tmp < 0) return 0;
   return tmp;
}

// Calculate DMA timing values
static u8 DMA_Tvalue(unsigned short T, unsigned int freq, unsigned short offset){
  int tmp = ((T*freq)/1000) - offset;

  if((T*freq)%1000!=0){ /*round up*/
    tmp++;
  }

  if((offset==3) & (tmp<1)) return 1; /*if Teoc calculate, dont return less then 2*/

  if (tmp < 0) return 0;
  return tmp;
}

static int atac_speedproc(ide_drive_t *drive, u8 mode){
   ide_hwif_t *hwif = HWIF(drive);
   struct atactrl_s *data = hwif->hwif_data;
   int pio = mode - XFER_PIO_0;
   int dma = mode - XFER_MW_DMA_0;

   // Set drive speed
   if (ide_config_drive_speed(drive, mode))
         printk("ide%d: Drive %d didn't "
                "accept speed setting. Oh, well.\n",
                 drive->dn >> 1, drive->dn & 1);

   
   // Set Core timing register
   if ( (mode >= XFER_MW_DMA_0) ){
      if( data->dma_core && (mode <= XFER_MW_DMA_2) ){  /*init dma timing reg if dma mode selected*/
         if (drive->select.b.unit == 0){
            printk("DMA Device0\n");
            atac_outl(
               (((DMA_Tvalue(dmam[dma].Teoc,data->freq,3) & 0xff)<<24) | /*min_t(u8, pio, 4)*/
               ((DMA_Tvalue(dmam[dma].res,data->freq,1) & 0xff)<<16) |
               ((DMA_Tvalue(dmam[dma].Td,data->freq,1) & 0xff)<<8) | 
               (DMA_Tvalue(dmam[dma].Tm,data->freq,1) & 0xff))
               ,data->port[dtr0]);

         }else{
            printk("DMA Device1\n");
            atac_outl(
               (((DMA_Tvalue(dmam[dma].Teoc,data->freq,3) & 0xff)<<24) |
               ((DMA_Tvalue(dmam[dma].res,data->freq,1) & 0xff)<<16) |
               ((DMA_Tvalue(dmam[dma].Td,data->freq,1) & 0xff)<<8) | 
                (DMA_Tvalue(dmam[dma].Tm,data->freq,1) & 0xff))
               ,data->port[dtr1]);
         }
      }else{
         /* This mode is not supported by controller */
         printk("ATACTRL: speedproc: Mode %d not supported\n",mode);
         return -1;
      }
	}else{ /*init pio timing reg if not dma mode selected*/
      /* All ATACTRL (non-DMA and DMA) can do PIO 0-4 modes */
      
      /* PIO mode 5 not supported */
      if ( mode >= XFER_PIO_5 ){
         printk("ATACTRL: speedproc: PIO mode 5 not supported\n");
         return -1;
      }
      
      if (drive->select.b.unit == 0){
         printk("Device0\n");
         atac_outl(
            (((Tvalue(piom[pio].Teoc,data->freq) & 0xff)<<24) | 
             ((Tvalue(piom[pio].T4,data->freq) & 0xff)<<16) |
             ((Tvalue(piom[pio].T2,data->freq) & 0xff)<<8) | 
             (Tvalue(piom[pio].T1,data->freq) & 0xff))
            ,data->port[pftr0]);
      }else{
         printk("Device1\n");
         atac_outl(
            (((Tvalue(piom[pio].Teoc,data->freq) & 0xff)<<24) | 
             ((Tvalue(piom[pio].T4,data->freq) & 0xff)<<16) |
             ((Tvalue(piom[pio].T2,data->freq) & 0xff)<<8) | 
             (Tvalue(piom[pio].T1,data->freq) & 0xff))
            ,data->port[pftr1]);
      }
	}

   if (!drive->init_speed)
      drive->init_speed = mode;
   
   drive->current_speed = mode;
   
   return 0;
}

static void atac_tuneproc(ide_drive_t *drive, u8 pio){
   printk("ATACTRL tuneproc %d\n",pio);
   if (pio == 255) {
      atac_speedproc(drive, ide_find_best_mode(drive, XFER_PIO | XFER_EPIO));
      return;
   }

   atac_speedproc(drive, XFER_PIO_0 + min_t(u8, pio, 4));
}

/**
 *	atactrl_dma_2_pio		-	return the PIO mode matching DMA
 *	@xfer_rate: transfer speed
 *
 *	Returns the nearest equivalent PIO timing for the PIO or DMA
 *	mode requested by the controller.
 */
 
static u8 atactrl_dma_2_pio (u8 xfer_rate) {
	switch(xfer_rate) {
		case XFER_UDMA_6:
		case XFER_UDMA_5:
		case XFER_UDMA_4:
		case XFER_UDMA_3:
		case XFER_UDMA_2:
		case XFER_UDMA_1:
		case XFER_UDMA_0:
		case XFER_MW_DMA_2:
		case XFER_PIO_4:
			return 4;
		case XFER_MW_DMA_1:
		case XFER_PIO_3:
			return 3;
		case XFER_SW_DMA_2:
		case XFER_PIO_2:
			return 2;
		case XFER_MW_DMA_0:
		case XFER_SW_DMA_1:
		case XFER_SW_DMA_0:
		case XFER_PIO_1:
		case XFER_PIO_0:
		case XFER_PIO_SLOW:
		default:
			return 0;
	}
}

static int atactrl_config_drive_for_dma(ide_drive_t *drive)
{
        /*UDMA not supported, therfore the zero*/
	u8 speed = ide_dma_speed(drive, 0);

	if (!(speed)) {
		u8 tspeed = ide_get_best_pio_mode(drive, 255, 5, NULL);
		speed = atactrl_dma_2_pio(XFER_PIO_0 + tspeed);
	}

	(void) atac_speedproc(drive, speed);
	return ide_dma_enable(drive);
}

/**
 *	atactrl_config_drive_xfer_rate	-	set up an IDE device
 *	@drive: IDE drive to configure
 *
 *	Set up the ATACTRL interface for the best available speed on this
 *	interface, preferring DMA to PIO.
 */
#if 0
static int atactrl_config_drive_xfer_rate (ide_drive_t *drive)
{
	ide_hwif_t *hwif	= HWIF(drive);
	struct hd_driveid *id	= drive->id;

	drive->init_speed = 0;

	if ((id->capability & 1) && drive->autodma) {

		if (ide_use_dma(drive)) {
			if (atactrl_config_drive_for_dma(drive))
				return hwif->ide_dma_on(drive);
		}
                printk("atactrl 1: failed to activate dma\n");
		goto fast_ata_pio;

	} else if ((id->capability & 8) || (id->field_valid & 2)) {
fast_ata_pio:
		/* Find best PIO mode. */
		hwif->tuneproc(drive, 255);
		return hwif->dma_off_quietly(drive);
	}
	/* IORDY not supported */
	return 0;
}
#endif

#ifdef BLK_DEV_IDEDMA_PCI
static int atactrl_config_drive_xfer_rate (ide_drive_t *drive)
{
	struct hd_driveid *id	= drive->id;
	drive->init_speed = 0;

	if ((id->capability & 1) && drive->autodma) {
		if (ide_use_dma(drive)) {
			if (atactrl_config_drive_for_dma(drive))
				return 0;
		}
	}
   printk("ATACTRL: failed to activate DMA\n");
	return -1;
}
#endif

static int hw_setup(hw_regs_t *hw, unsigned int base, unsigned int irq, struct atactrl_s *data, unsigned long timeraddr)
{
	int i,j;
   unsigned int tmp,tmp2;

	memset(hw, 0, sizeof(hw_regs_t));
   for (i = 0; i <= IDE_STATUS_OFFSET; i++)
		hw->io_ports[i] = (unsigned long) ioremap(base + 0x40 + 0x4*i, 4);
	
   hw->io_ports[IDE_CONTROL_OFFSET] = (unsigned long)ioremap(base + 0x78, 4);
	hw->irq = irq;
   hw->chipset = ide_generic;
   
   memset (data, 0, sizeof (struct atactrl_s));
   
   for (i=0;i<REMAP_CNT;i++){
      data->port[i] = (unsigned long)ioremap(base + 0x4*i, 4);
      if (!request_region(data->port[i], 1, "ide-atactrl"))
	      break;
   }
   if (i != REMAP_CNT){
      for (j=0;j<=i;j++){
         release_region(data->port[j], 1);
      }
      return -1;
   }
   
   /* Detect if ATA controller can do DMA 
    * Only the DMA controller has the prdtb register
    */
   tmp = atac_inw(data->port[prdtb]);
   atac_outw(1,data->port[prdtb]);
   tmp2 = atac_inw(data->port[prdtb]);
   atac_outw(tmp,data->port[prdtb]); /* Restore old value */
   
   if ( tmp2 == 1 ){
      /* DMA available */
      hw->dma = NO_DMA;
      data->dma_core = 1;
   }else{
      /* DMA is not available */
      hw->dma = 0;
      data->dma_core = 0;
   }

   data->freq = *((unsigned int*)ioremap(timeraddr + 0x04, 4)) + 1;
   return 0;
}

static inline void hwif_setup(ide_hwif_t *hwif, struct atactrl_s *hwif_data, unsigned int base)
{
	default_hwif_iops(hwif);
	hwif->mmio  = 0;
	
   hwif->OUTB  = atac_outb;
	hwif->OUTBSYNC  = atac_outbsync;
	hwif->OUTW  = atac_outw;
//	hwif->OUTL  = atac_outl;
	hwif->OUTSW  = atac_outsw;
	//hwif->OUTSL = NULL;
	hwif->INB  = atac_inb;
	hwif->INW   = atac_inw;
	//hwif->INL   = NULL;
	hwif->INSW  = atac_insw;
	//hwif->INSL  = NULL;

   hwif->tuneproc = &atac_tuneproc;
   hwif->speedproc = &atac_speedproc;
   hwif->drives[0].autotune = 0;
   hwif->drives[0].autodma = 0;
   hwif->drives[1].autotune = 0;
   hwif->drives[1].autodma = 0;
   hwif->hwif_data = hwif_data;

   hwif->atapi_dma = 0;
   hwif->ultra_mask = 0x00; 
   hwif->mwdma_mask = 0x00; 
   hwif->swdma_mask = 0x00;
   hwif->autodma = 0;

#ifdef BLK_DEV_IDEDMA_PCI
   if ( hwif_data->dma_core ){
   	/* DMA init
       * Atactrl seperates registers by 4 byte adresses, so the dma register-
       * adresses must be init here insted of in ide_setup_dma where the registers
       * only are separated by one byte adress
       */
  
      hwif->chipset         = ide_generic;

      hwif->dma_base        = (unsigned long) ioremap((base+bmcmd*4)    ,4);
      hwif->dma_command     = hwif->dma_base;
      hwif->dma_vendor1	= (unsigned long) ioremap((base+bmcmd*4+1*4),4);
      hwif->dma_status	= (unsigned long) ioremap((base+bmcmd*4+2*4),4);
      hwif->dma_vendor3	= (unsigned long) ioremap((base+bmcmd*4+3*4),4);
      hwif->dma_prdtable	= (unsigned long) ioremap((base+bmcmd*4+4*4),4);

      hwif->ide_dma_check = &atactrl_config_drive_xfer_rate;

      ide_setup_dma(hwif,hwif->dma_base,20); /*20 is the adresspace for the BM registers*/
  
      /* Only multi word DMA supported at this time (maby atapi and single word?) */
      hwif->atapi_dma = 0;
      hwif->ultra_mask = 0x00;
      hwif->mwdma_mask = 0x07; 
      hwif->swdma_mask = 0x00;

      if (!noautodma){
	      hwif->autodma = 1;
      }

      hwif->drives[0].autodma = hwif->autodma;
      hwif->drives[1].autodma = hwif->autodma;
   }
#endif
}

void default_pio_mode(ide_hwif_t *hwif){
   struct atactrl_s *data = hwif->hwif_data;
   
   // Set PIO compatible timing
   atac_outl(
      (((Tvalue(piom[0].Teoc,data->freq) & 0xff)<<24) | 
       ((Tvalue(piom[0].T4,data->freq) & 0xff)<<16) |
       ((Tvalue(piom[0].T2,data->freq) & 0xff)<<8) | 
       (Tvalue(piom[0].T1,data->freq) & 0xff))
      ,data->port[pctr]);    
   // Set PIO fast timing device 0
   atac_outl(
      (((Tvalue(piom[0].Teoc,data->freq) & 0xff)<<24) | 
       ((Tvalue(piom[0].T4,data->freq) & 0xff)<<16) |
       ((Tvalue(piom[0].T2,data->freq) & 0xff)<<8) | 
       (Tvalue(piom[0].T1,data->freq) & 0xff))
      ,data->port[pftr0]);    
   // Set PIO fast timing device 1   
   atac_outl(
      (((Tvalue(piom[0].Teoc,data->freq) & 0xff)<<24) | 
       ((Tvalue(piom[0].T4,data->freq) & 0xff)<<16) |
       ((Tvalue(piom[0].T2,data->freq) & 0xff)<<8) | 
       (Tvalue(piom[0].T1,data->freq) & 0xff))
      ,data->port[pftr1]);    
   
   // Set control register
   if ( data->dma_core ){
      /*enable dma, prd endian and byte swap*/
      atac_outl(0x80008CEE,data->port[ctrl]);
   }else{
      atac_outl(0x800000ee,data->port[ctrl]);
   }
   // Read status register (clear irq)
   atac_inw(hwif->io_ports[IDE_STATUS_OFFSET]);
}

void atac_reset(ide_hwif_t *hwif){
   struct atactrl_s *data = hwif->hwif_data;
   atac_outl(0x80000001,data->port[ctrl]);
   //should sleep 25us;
   udelay(25);
   atac_outl(0x80000000,data->port[ctrl]);
   //should sleep 2ms;
   udelay(2000);
   // Read status register (clear irq)
   atac_inw(hwif->io_ports[IDE_STATUS_OFFSET]);
}

void __init atactrl_ide_init(void)
{
	hw_regs_t hw;
	ide_hwif_t *hwif=NULL;
	int i,idx,ret;
   unsigned long timeraddr;
   amba_ahb_device adev;

   data = kmalloc(sizeof(struct atactrl_s),GFP_KERNEL);
   if (data == NULL) {
      printk("data = NULL\n");
      return;
   }
     
   i = amba_get_free_ahbslv_devices (VENDOR_GAISLER, GAISLER_ATACTRL, &adev, 1);
   if (i == 0) {
		printk(KERN_ERR "ATACTRL : AMBA plug&play failed\n");
      return ;
   }
  
   timeraddr = amba_find_apbslv_addr (VENDOR_GAISLER, GAISLER_GPTIMER, NULL);
   if (timeraddr == 0) {
		printk(KERN_ERR "ATACTRL : Find timer address failed\n");
      return ;
   }
   
   ret = hw_setup(&hw, adev.start[0], adev.irq, data, timeraddr);
   
   /* Even if hw_setup failed we like to print that a controller is found */
   if ( data->dma_core ){
      printk("ATA-DMA Controller at 0x%x IRQ %d\n",adev.start[0],adev.irq);
   }else{
      printk("ATA-Controller at 0x%x IRQ %d\n",adev.start[0],adev.irq);
   }
   
   /* Did hw_setup complete sucessfully? */
	if ( ret )
      return;

	/* register if */
	idx = ide_register_hw(&hw, &hwif);
	if (idx == -1) {
		printk(KERN_ERR "ATACTRL : IDE I/F register failed\n");
		return;
	}

   hwif_setup(hwif,data,adev.start[0]);

   // Reset device
   atac_reset(hwif);

   // Set timing for PIO mode 0
   default_pio_mode(hwif);
	
   printk(KERN_INFO "ide%d: ATACTRL generic IDE interface\n", idx);
	return;

}

