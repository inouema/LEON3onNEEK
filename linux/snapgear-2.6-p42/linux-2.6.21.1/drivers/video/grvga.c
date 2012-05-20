/*
 * grvga.c : Gaisler Framebuffer driver.
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/tty.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/fb.h>
#include <linux/init.h>
#include <asm/leon.h>  
#include <linux/platform_device.h>

#define _CACHE_MASK (7<<3)
static int running = 0;
static unsigned int mem_size;
static unsigned char fb_hard = 0; /* 1: Use fb_addr */
static unsigned long fb_addr; 
static struct fb_var_screeninfo screendata;
static struct fb_fix_screeninfo screeninfo;

struct grvga_par {
	LEON3_GRVGA_Regs_Map *regs;
	/*unsigned long *vga_regs[11];*/
	/*int clk_vector[4];*/
	
	
	u32 color_palette[256];
};

static struct fb_var_screeninfo m640x480 __initdata = {
  .xres =		640,
  .yres =		480,
  .xres_virtual =	640,
  .yres_virtual =	480,
  .pixclock = 	        40000,
  .left_margin =	48,
  .right_margin =	16,
  .upper_margin =	31,
  .lower_margin =	11,
  .hsync_len =	96,
  .vsync_len =	2,
};

static struct fb_var_screeninfo m800x480 __initdata = {
  .xres =		800,
  .yres =		480,
  .xres_virtual =	800,
  .yres_virtual =	480,
  .pixclock = 	        30120,
  .left_margin =	216,
  .right_margin =	16,
  .upper_margin =	35,
  .lower_margin =	10,
  .hsync_len =	48,
  .vsync_len =	3,
};   

static struct fb_var_screeninfo m800x600x60 __initdata = {
	.xres =		800,
	.yres =		600,
	.xres_virtual =	800,
	.yres_virtual =	600,    
      	.pixclock =	25000,
      	.left_margin =	88,
      	.right_margin =	40,
      	.upper_margin =	23,
      	.lower_margin =	1,
      	.hsync_len =	128,
      	.vsync_len =	4,
};

static struct fb_var_screeninfo m800x600x72 __initdata = {
	.xres =		800,
	.yres =		600,
	.xres_virtual =	800,
	.yres_virtual =	600,    
      	.pixclock =	20000,
      	.left_margin =	64,
      	.right_margin =	56,
      	.upper_margin =	23,
      	.lower_margin =	37,
      	.hsync_len =	120,
      	.vsync_len =	6,
};

static struct fb_var_screeninfo m1024x768 __initdata = {
	.xres =		1024,
	.yres =		768,
	.xres_virtual =	1024,
	.yres_virtual =	768,	
      	.pixclock =	15385,
      	.left_margin =	160,
      	.right_margin =	24,
      	.upper_margin =	29,
      	.lower_margin =	3,
      	.hsync_len =	136,
      	.vsync_len =	6,
};

static struct fb_fix_screeninfo grvga_fix __initdata = {
	.id =		"Gaisler SVGA",
	.type =		FB_TYPE_PACKED_PIXELS, 
	.xpanstep =	0,
	.ypanstep =	0,
	.ywrapstep =	0,
	.accel =	FB_ACCEL_NONE,
};

/*
 *  Interface used by the world
 */

int grvga_init(void);
int grvga_setup(char *);

/*--------------------------------------------------
 *
 */

static int grvga_check_var(struct fb_var_screeninfo *var,
			 struct fb_info *info);
static int grvga_set_par(struct fb_info *info);
static int grvga_setcolreg(u_int regno, u_int red, u_int green, u_int blue,
			 u_int transp, struct fb_info *info);
static int grvga_pan_display(struct fb_var_screeninfo *var,
			   struct fb_info *info);
static int grvga_mmap(struct fb_info *info, struct vm_area_struct *vma);

static int grvga_fb_blank(int blank_mode, struct fb_info *info);

static struct fb_ops grvga_ops = {
  .owner          = THIS_MODULE,
  .fb_check_var   = grvga_check_var,
  .fb_set_par	    = grvga_set_par,
  .fb_setcolreg	  = grvga_setcolreg,
  .fb_pan_display = grvga_pan_display,
  .fb_fillrect	  = cfb_fillrect,
  .fb_copyarea	  = cfb_copyarea,
  .fb_imageblit	  = cfb_imageblit,
  .fb_cursor	  = NULL,//soft_cursor, /* not required any more */
  .fb_mmap	  = grvga_mmap,
  .fb_blank       = grvga_fb_blank,
};

static u_long get_line_length(int xres_virtual, int bpp)
{
	u_long length;

	length = xres_virtual * bpp;
	length = (length + 31) & ~31;
	length >>= 3;
	return (length);
}


static int grvga_check_var(struct fb_var_screeninfo *var,
			 struct fb_info *info)
{
	u_long line_length;

	/*
	 *  FB_VMODE_CONUPDATE and FB_VMODE_SMOOTH_XPAN are equal!
	 *  as FB_VMODE_SMOOTH_XPAN is only used internally
	 */
	if (var->vmode & FB_VMODE_CONUPDATE) {
		var->vmode |= FB_VMODE_YWRAP;
		var->xoffset = info->var.xoffset;
		var->yoffset = info->var.yoffset;
	}

	/*
	 *  Some very basic checks
	 */
	if (!var->xres)
		var->xres = 1;
	if (!var->yres)
		var->yres = 1;
	if (var->xres > var->xres_virtual)
		var->xres_virtual = var->xres;
	if (var->yres > var->yres_virtual)
		var->yres_virtual = var->yres;
	if (var->bits_per_pixel <= 1)
		var->bits_per_pixel = 1;
	else if (var->bits_per_pixel <= 8)
		var->bits_per_pixel = 8;
	else if (var->bits_per_pixel <= 16)
		var->bits_per_pixel = 16;
	else if (var->bits_per_pixel <= 24)
		var->bits_per_pixel = 24;
	else if (var->bits_per_pixel <= 32)
		var->bits_per_pixel = 32;
	else
		return -EINVAL;

	if (var->xres_virtual < var->xoffset + var->xres)
		var->xres_virtual = var->xoffset + var->xres;
	if (var->yres_virtual < var->yoffset + var->yres)
		var->yres_virtual = var->yoffset + var->yres;

	/*
	 *  Memory limit
	 */
	line_length =
	    get_line_length(var->xres_virtual, var->bits_per_pixel);
	if (line_length * var->yres_virtual > mem_size)
		return -ENOMEM;

	/*
	 * Now that we checked it we alter var. The reason being is that the video
	 * mode passed in might not work but slight changes to it might make it 
	 * work. This way we let the user know what is acceptable.
	 */
	switch (var->bits_per_pixel) {
	case 1:
	case 8:
		var->red.offset = 0;
		var->red.length = 8;
		var->green.offset = 0;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		var->transp.offset = 0;
		var->transp.length = 0;
		break;
	case 16:		/* RGBA 5551 */
		if (var->transp.length) {
			var->red.offset = 0;
			var->red.length = 5;
			var->green.offset = 5;
			var->green.length = 5;
			var->blue.offset = 10;
			var->blue.length = 5;
			var->transp.offset = 15;
			var->transp.length = 1;
		} else {	/* RGB 565 */
			var->red.offset = 0;
			var->red.length = 5;
			var->green.offset = 5;
			var->green.length = 6;
			var->blue.offset = 11;
			var->blue.length = 5;
			var->transp.offset = 0;
			var->transp.length = 0;
		}
		break;
	case 24:		/* RGB 888 */
		var->red.offset = 0;
		var->red.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->blue.offset = 16;
		var->blue.length = 8;
		var->transp.offset = 0;
		var->transp.length = 0;
		break;
	case 32:		/* RGBA 8888 */
		var->red.offset = 0;
		var->red.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->blue.offset = 16;
		var->blue.length = 8;
		var->transp.offset = 24;
		var->transp.length = 8;
		break;
	}
	var->red.msb_right = 0;
	var->green.msb_right = 0;
	var->blue.msb_right = 0;
	var->transp.msb_right = 0;

	return 0;
}

static int grvga_set_par(struct fb_info *info)
{
 
  int func=0,clk_sel=-1,i;
	struct grvga_par *par = info->par;
  
  par->regs->video_length = ((info->var.yres -1) << 16) + (info->var.xres -1);   
  par->regs->front_porch  = (info->var.lower_margin << 16) + (info->var.right_margin); 
  par->regs->sync_length  = (info->var.vsync_len << 16) + (info->var.hsync_len);
  par->regs->line_length   = ((info->var.yres + info->var.lower_margin + info->var.upper_margin + info->var.vsync_len -1) <<16) +
                 (info->var.xres + info->var.right_margin + info->var.left_margin + info->var.hsync_len -1);

  

  switch(info->var.bits_per_pixel){
  case 8:
    info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
    info->var.red   = (struct fb_bitfield) {0,8,0};
    info->var.green = (struct fb_bitfield) {0,8,0};
    info->var.blue  = (struct fb_bitfield) {0,8,0};
    info->var.transp = (struct fb_bitfield) {0,0,0};
    func = 1;
    break;
  case 16:
    info->fix.visual = FB_VISUAL_TRUECOLOR;
    info->var.red   = (struct fb_bitfield) {11,5,0};
    info->var.green = (struct fb_bitfield) {5,6,0};
    info->var.blue  = (struct fb_bitfield) {0,5,0};
    info->var.transp = (struct fb_bitfield) {0,0,0};
    func = 2;
    break;
  case 32:
    info->fix.visual = FB_VISUAL_TRUECOLOR;
    info->var.red   = (struct fb_bitfield) {16,8,0};
    info->var.green = (struct fb_bitfield) {8,8,0};
    info->var.blue  = (struct fb_bitfield) {0,8,0};
    info->var.transp = (struct fb_bitfield) {24,8,0};
    func = 3;
    break;
	default:
		return -1;
  } 
  
  for (i = 0; i <= 3 ; i++){
    if (info -> var.pixclock == par->regs->clk_vector[i]){
    clk_sel = i;
    }
  }
	if ( clk_sel < 0 )
		return -1;
 
  par->regs->status = ((clk_sel << 6) | (func << 4)) | running;

  info->fix.line_length = get_line_length(info->var.xres_virtual,
					  info->var.bits_per_pixel);
  return 0;
}

static int grvga_setcolreg(u_int regno, u_int red, u_int green, u_int blue,
			 u_int transp, struct fb_info *info)
{
	struct grvga_par *par;
	
	if (regno >= 256)	/* no. of hw registers */
		return 1;
	/*
	 * Program hardware... do anything you want with transp
	 */

	/* grayscale works only partially under directcolor */

	

	if (info->var.grayscale) {
		/* grayscale = 0.30*R + 0.59*G + 0.11*B */
		red = green = blue =
		    (red * 77 + green * 151 + blue * 28) >> 8;
	}
	
	par = info->par;

	/* Directcolor:
	 *   var->{color}.offset contains start of bitfield
	 *   var->{color}.length contains length of bitfield
	 *   {hardwarespecific} contains width of RAMDAC
	 *   cmap[X] is programmed to (X << red.offset) | (X << green.offset) | (X << blue.offset)
	 *   RAMDAC[X] is programmed to (red, green, blue)
	 *
	 * Pseudocolor:
	 *    uses offset = 0 && length = RAMDAC register width.
	 *    var->{color}.offset is 0
	 *    var->{color}.length contains widht of DAC
	 *    cmap is not used
	 *    RAMDAC[X] is programmed to (red, green, blue)
	 * Truecolor:
	 *    does not use DAC. Usually 3 are present.
	 *    var->{color}.offset contains start of bitfield
	 *    var->{color}.length contains length of bitfield
	 *    cmap is programmed to (red << red.offset) | (green << green.offset) |
	 *                      (blue << blue.offset) | (transp << transp.offset)
	 *    RAMDAC does not exist
	 */
#define CNVT_TOHW(val,width) ((((val)<<(width))+0x7FFF-(val))>>16)
	switch (info->fix.visual) {
	case FB_VISUAL_TRUECOLOR:
	case FB_VISUAL_PSEUDOCOLOR:
		red = CNVT_TOHW(red, info->var.red.length);
		green = CNVT_TOHW(green, info->var.green.length);
		blue = CNVT_TOHW(blue, info->var.blue.length);
		transp = CNVT_TOHW(transp, info->var.transp.length);
		par->regs->clut = (regno << 24) + (red << 16) + (green << 8) + blue; 
		break;
	case FB_VISUAL_DIRECTCOLOR:
		red = CNVT_TOHW(red, 8);	/* expect 8 bit DAC */
		green = CNVT_TOHW(green, 8);
		blue = CNVT_TOHW(blue, 8);
		/* hey, there is bug in transp handling... */
		transp = CNVT_TOHW(transp, 8);
		
		break;
	}
#undef CNVT_TOHW
	/* Truecolor has hardware independent palette */
	if (info->fix.visual == FB_VISUAL_TRUECOLOR) {
		u32 v;
		if (regno >= 16)
			return 1;

		v = (red << info->var.red.offset) |
		    (green << info->var.green.offset) |
		    (blue << info->var.blue.offset) |
		    (transp << info->var.transp.offset);
		switch (info->var.bits_per_pixel) {
		case 8:
			break;
		case 16:
			((u32 *) (info->pseudo_palette))[regno] = v;
			break;
		case 24:
		case 32:
			((u32 *) (info->pseudo_palette))[regno] = v;
			break;
		}
		return 0;
	}
	return 0;
}

static int grvga_pan_display(struct fb_var_screeninfo *var,
			   struct fb_info *info)
{
	
	if (var->vmode & FB_VMODE_YWRAP) {
		if (var->yoffset < 0
		    || var->yoffset >= info->var.yres_virtual
		    || var->xoffset)
			return -EINVAL;
	} else {
		if (var->xoffset + var->xres > info->var.xres_virtual ||
		    var->yoffset + var->yres > info->var.yres_virtual)
			return -EINVAL;
	}
	info->var.xoffset = var->xoffset;
	info->var.yoffset = var->yoffset;
	if (var->vmode & FB_VMODE_YWRAP)
		info->var.vmode |= FB_VMODE_YWRAP;
	else
		info->var.vmode &= ~FB_VMODE_YWRAP;
	return 0;
}

static int grvga_mmap(struct fb_info *info, struct vm_area_struct *vma)
{
	unsigned int len;
	unsigned long start=0, off;

	if (vma->vm_pgoff > (~0UL >> PAGE_SHIFT)) {
		return -EINVAL;
	}
	
	start = (info->fix.smem_start) & PAGE_MASK;
	len = PAGE_ALIGN((start & ~PAGE_MASK) + info->fix.smem_len);

	off = vma->vm_pgoff << PAGE_SHIFT;

	if ((vma->vm_end - vma->vm_start + off) > len) {
	  return -EINVAL;
	}

	off += start;
	vma->vm_pgoff = off >> PAGE_SHIFT;

	/* LEON SPARC note:
	 * Due to write through cache AND not hardware acceleration 
	 * modifying the framebuffer it is OK to cache.
	 *
	 * On NON-Cache systems uncomment:
	 * vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	 */
	vma->vm_flags |= VM_IO | VM_RESERVED;

	if (io_remap_pfn_range(vma, vma->vm_start, off >> PAGE_SHIFT,
				vma->vm_end - vma->vm_start,
				vma->vm_page_prot)) {
	  return -EAGAIN;
	}

	return 0;
}

static int grvga_fb_blank(int blank_mode, struct fb_info *info)
{
    return 0;
}

int __init grvga_setup(char *options)
{
	char *this_opt;
	int custom = 0;
	int count = 0;

	if (!options || !*options){
		/* Default to low resolution, Add video=grvga:... to kernel command line */
		printk("GRVGA: Defaulting to 640x480 8-bit resolution\n");
		screendata = m640x480;
		screeninfo = grvga_fix;
		screendata.bits_per_pixel = 8;
		mem_size = 640*480*1;
		return 1;
	}
	
	while ((this_opt = strsep(&options, ",")) != NULL) {
		if (!*this_opt)
			continue;
		
		if(custom){
		  switch(count){
		  case 0:
		    screendata.pixclock = simple_strtoul(this_opt,NULL,0);
		    count++;
		    break;
		  case 1:
		    screendata.xres = screendata.xres_virtual = simple_strtoul(this_opt,NULL,0);
		    count++;
		    break;
		  case 2:
		    screendata.right_margin = simple_strtoul(this_opt,NULL,0);
		    count++;
		    break; 
		  case 3:
		    screendata.hsync_len = simple_strtoul(this_opt,NULL,0);
		    count++;
		    break; 
		  case 4:
		    screendata.left_margin = simple_strtoul(this_opt,NULL,0);
		    count++;
		    break;
		  case 5:
		    screendata.yres = screendata.yres_virtual = simple_strtoul(this_opt,NULL,0);
		    count++;
		    break;
		  case 6:
		    screendata.lower_margin = simple_strtoul(this_opt,NULL,0);
		    count++;
		    break; 
		  case 7:
		    screendata.vsync_len = simple_strtoul(this_opt,NULL,0);
		    count++;
		    break; 
		  case 8:
		    screendata.upper_margin = simple_strtoul(this_opt,NULL,0);
		    count++;
		    break;
  		  case 9:
		    screeninfo = grvga_fix;
		    screendata.bits_per_pixel = simple_strtoul(this_opt,NULL,0);
		    count++;
		    break;
		  case 10:
		    mem_size = simple_strtoul(this_opt,NULL,0);  
                    count++;
                    break;
                  case 11:
                    fb_addr = simple_strtoul(this_opt,NULL,0);
                    fb_hard = 1;
                    custom = 0;
                    break;
		  }
		}
		
		if (!strncmp(this_opt, "1024x768@60", 11)){
		  screendata = m1024x768;
		  custom = 1;
		  count = 9;
		  continue;
		}
		if (!strncmp(this_opt, "800x600@60", 10)){
		  screendata = m800x600x60;
		  custom = 1;
		  count = 9;
		  continue;
		}
		if (!strncmp(this_opt, "640x480@60", 10)){
		  screendata = m640x480;
		  custom = 1;
		  count = 9;
		  continue;
		}

		if (!strncmp(this_opt, "800x600@72", 10)){
		  screendata = m800x600x72;
		  custom = 1;
		  count = 9;
		  continue;
		}
                
                if (!strncmp(this_opt, "800x480", 7)){
		  screendata = m800x480;
		  custom = 1;
		  count = 9;
		  continue;
		}

		if (!strncmp(this_opt, "custom", 6)){
		  custom = 1;
		  printk("Custom mode is set\n");
		}
	}
	screendata.grayscale = 0,
	screendata.nonstd    = 0,
	screendata.height    = -1,
	screendata.width     = -1,
	screendata.activate  = FB_ACTIVATE_NOW,
	screendata.vmode     = FB_VMODE_NONINTERLACED;
	
	return 1;
}

static void grvga_platform_release(struct device *device)
{
	// This is called when the reference count goes to zero.
}

static int __init grvga_probe(struct device *device)
{
	struct platform_device *dev = to_platform_device(device);
	struct fb_info *info;
	int retval = -ENOMEM;
	unsigned long virtual_start;
	unsigned long physical_start;
	unsigned long page;
	int i;
	unsigned int REG_BASE;
	struct grvga_par *par;

	amba_apb_device devi[1];
	
	i = amba_get_free_apbslv_devices(VENDOR_GAISLER,GAISLER_SVGA, devi, 1);
	
	if ( i < 1 ){
		/* did not find device */
		return -ENODEV;
	}
	
	REG_BASE = (unsigned int)devi[0].start;

        if (fb_hard) {
           /* Got framebuffer base address from argument list */
           printk(KERN_INFO "GRVGA: Using specificed framebuffer base address: 0x%08lx\n",
                  fb_addr);
           physical_start = fb_addr;

           if (!request_mem_region(physical_start, mem_size, dev->name)) {
              printk(KERN_INFO "GRVGA: Request mem region failed\n");
              return -ENOMEM;
           }

           virtual_start = (unsigned long)ioremap(physical_start, mem_size);

           if (!virtual_start) {
              printk(KERN_INFO "GRVGA: Error mapping memory\n");
              return -ENOMEM;
           }
        } else {
           /* ----------- Allocate our frambuffer memory --------------------- */

           virtual_start = (unsigned long ) __get_free_pages(GFP_ATOMIC | GFP_DMA,
                                                             get_order(mem_size));
           if (!virtual_start){
              printk("GRVGA: Unable to allocate framebuffer memory (%d bytes)\n",mem_size);
              return -ENOMEM;
           }

           /* ----------- Translate to physical address --------------------- */
           
           /* 	physical_start = virt_to_bus((void *)virtual_start); */
           physical_start = __pa(virtual_start);
        
           /* -------------------------------------------------------------- 
            * Set page reserved so that mmap will work. This is necessary
            * since we'll be remapping normal memory.
            */
           
           for (page = virtual_start;
                page < PAGE_ALIGN(virtual_start + mem_size);
                page += PAGE_SIZE) {
              SetPageReserved(virt_to_page(page));
           }
        }

	memset((unsigned long *) virtual_start, 0, mem_size); 

	info = framebuffer_alloc(sizeof(struct grvga_par), &dev->dev);
	if (!info){
		printk("GRVGA: failed to allocate mem with framebuffer_alloc\n");
		goto err;
	}

	/* get virtual address to HW regs, and make them available */
	par = info->par;
	par->regs = (LEON3_GRVGA_Regs_Map *) ioremap(REG_BASE, sizeof(LEON3_GRVGA_Regs_Map));

	info->var = screendata;
	info->screen_base = (char __iomem *) virtual_start;
	info->fbops = &grvga_ops;
	info->fix = screeninfo;
	info->fix.smem_start = physical_start;
	info->fix.smem_len   = mem_size;
	info->pseudo_palette = par->color_palette;
	info->flags = FBINFO_FLAG_DEFAULT;

	retval = fb_alloc_cmap(&info->cmap, 256, 0);
	if (retval < 0){
		printk("GRVGA: failed to allocate mem with fb_alloc_cmap\n");
		goto err1;
	}

	dev_set_drvdata(&dev->dev, info);
	
	printk("Framebuffer address from node : 0x%x\n",(unsigned int)info->screen_base);
	printk("Framebuffer address from videomemory : 0x%x\n", (unsigned int)physical_start);
	par->regs->fb_pos = physical_start;
	par->regs->status = par->regs->status | 1;
	running = 1;
	printk(KERN_INFO
	       "fb%d: Gaisler frame buffer device, using %uK of video memory\n",
	       info->node, mem_size >> 10);


	grvga_set_par(info);

	retval = register_framebuffer(info);
	if (retval < 0){
		printk("GRVGA: failed to register framebuffer\n");
		goto err2;
	}
	
	return 0;
err2:
	fb_dealloc_cmap(&info->cmap);
err1:
	framebuffer_release(info);
err:
	/* 	vfree(videomemory);    Not needed */
	return retval;
}

static int grvga_remove(struct device *device)
{
	struct fb_info *info = dev_get_drvdata(device);

	if (info) {
	  unregister_framebuffer(info);
	  framebuffer_release(info);
	}
	return 0;
}

static struct device_driver grvga_driver = {
	.name	= "grvga",
	.bus	= &platform_bus_type,
	.probe	= grvga_probe,
	.remove = grvga_remove,
};

static struct platform_device grvga_device = {
  .name	= "grvga",
  .id	= 0,
  .dev	= {
            .release = grvga_platform_release,
          }
};

int __init grvga_init(void)
{

  int ret;
  char *options = NULL;
  
	memset(&screendata,0,sizeof(struct fb_var_screeninfo));
	memset(&screeninfo,0,sizeof(struct fb_fix_screeninfo));

  if (fb_get_options("grvga", &options))
    return -ENODEV;
  grvga_setup(options);

  ret = driver_register(&grvga_driver);

  if (!ret) {
    ret = platform_device_register(&grvga_device);
    if (ret)
      driver_unregister(&grvga_driver);
  }
  return ret;
}

module_init(grvga_init);

#ifdef MODULE
static void __exit grvga_exit(void)
{
	platform_device_unregister(&grvga_device);
	driver_unregister(&grvga_driver);
}

module_exit(grvga_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hans Soderlund");
MODULE_DESCRIPTION("Gaisler framebuffer device driver");
#endif				/* MODULE */
