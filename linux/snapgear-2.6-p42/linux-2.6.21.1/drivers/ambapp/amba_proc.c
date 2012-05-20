/*
 * /proc filesystem for amba
 *
 * Copyright (c) 2005 Emtrion GmbH
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>

#include <linux/proc_fs.h>

#include <asm/leon.h>



extern amba_confarea_type amba_conf;

struct proc_dir_entry * amba_proc_dir_entry;

int amba_read_procmem(char *buf, char **start, off_t offset, int count, int *eof, void *data)
{

	char devbuf[128];
	char vendorbuf[128];
	
	int len = 0;
	
	unsigned int i, conf, iobar, mem_start, irq, k;

	/* Print header */
	len += sprintf(buf, "%-18s%-18s%-10s%-4s%-11s%-4s%-9s\n", "device", "vendor", "mem_start", "irq", "bus_type", "id", "status");
	
	/* Search apb slave devices */

	for (i = 0; i < amba_conf.apbslv.devnr ; i++) {
		conf = amba_get_confword(amba_conf.apbslv, i, 0);

		vendor_dev_string(conf, vendorbuf, devbuf);
		irq = amba_irq(conf);
		iobar = amba_apb_get_membar(amba_conf.apbslv, i);
		mem_start = amba_iobar_start(amba_conf.apbslv.apbmst[i], iobar);
		

		/* show device, vendor and mem_start */
		len += sprintf( buf+len, "%-18s%-18s", devbuf, vendorbuf );
		
		/* show mem_start */
		len += sprintf( buf+len, "%08x  ", mem_start );
		
		/* show irq */
		if( irq )
			len += sprintf( buf+len, "%-4i", irq );
		else
			len += sprintf( buf+len, "%-4s", "" );
			
		/* show bus type and bus id */
		len += sprintf( buf+len, "%-11s%-4i", "apb_slave", i );
		
		/* show status */
		if( (amba_conf.apbslv.allocbits[i / 32] & (1 << (i & (32 - 1)))) )
			len += sprintf( buf+len, "%-6s\n", "allocated");
		else
			len += sprintf( buf+len, "%-6s\n", "free");
	}

	/* Search ahb slave devices */

	for (i = 0; i < amba_conf.ahbslv.devnr ; i++) {
		conf = amba_get_confword(amba_conf.ahbslv, i, 0);

		vendor_dev_string(conf, vendorbuf, devbuf);
		irq = amba_irq(conf);
		iobar = amba_ahb_get_membar(amba_conf.ahbslv, i, 0);
		mem_start = amba_membar_start(iobar);
		if (amba_membar_type(iobar) == AMBA_TYPE_AHBIO)
			mem_start = AMBA_TYPE_AHBIO_ADDR(mem_start);
		
		/* show device, vendor */
		len += sprintf( buf+len, "%-18s%-18s", devbuf, vendorbuf );
		
		/* show mem_start */
		len += sprintf( buf+len, "%08x  ", mem_start );
			
		/* show irq */
		if( irq )
			len += sprintf( buf+len, "%-4i", irq );
		else
			len += sprintf( buf+len, "%-4s", "" );
			
		/* show bus type and bus id */
		len += sprintf( buf+len, "%-11s%-4i", "ahb_slave", i );
		
		/* show status */
		if( (amba_conf.ahbslv.allocbits[i / 32] & (1 << (i & (32 - 1)))) )
			len += sprintf( buf+len, "%-6s\n", "allocated");
		else
			len += sprintf( buf+len, "%-6s\n", "free");
			
		/* print additionnal mem_start */
		for( k=1 ; k<4 ; k++){
			iobar = amba_ahb_get_membar(amba_conf.ahbslv, i, k);
			mem_start = amba_membar_start(iobar);
			if (amba_membar_type(iobar) == AMBA_TYPE_AHBIO)
				mem_start = AMBA_TYPE_AHBIO_ADDR(mem_start);
				
			if( mem_start )
				len += sprintf( buf+len, "%-36s%-10x\n", "", mem_start );
		}

	}
	
	/* Search ahb master devices */

	for (i = 0; i < amba_conf.ahbmst.devnr ; i++) {
		conf = amba_get_confword(amba_conf.ahbmst, i, 0);

		vendor_dev_string(conf, vendorbuf, devbuf);
		irq = amba_irq(conf);
		iobar = amba_ahb_get_membar(amba_conf.ahbmst, i, 0);
		mem_start = amba_membar_start(iobar);
		if (amba_membar_type(iobar) == AMBA_TYPE_AHBIO)
			mem_start = AMBA_TYPE_AHBIO_ADDR(mem_start);
		
		/* show device, vendor */
		len += sprintf( buf+len, "%-18s%-18s", devbuf, vendorbuf );
		
		/* show mem_start */
		len += sprintf( buf+len, "%08x  ", mem_start );
			
		/* show irq */
		if( irq )
			len += sprintf( buf+len, "%-4i", irq );
		else
			len += sprintf( buf+len, "%-4s", "" );
			
		/* show bus type and bus id */
		len += sprintf( buf+len, "%-11s%-4i", "ahb_master", i );
		
		/* show status */
		if( (amba_conf.ahbmst.allocbits[i / 32] & (1 << (i & (32 - 1)))) )
			len += sprintf( buf+len, "%-6s\n", "allocated");
		else
			len += sprintf( buf+len, "%-6s\n", "free");
			
		/* print additionnal mem_start */
		for( k=1 ; k<4 ; k++){
			iobar = amba_ahb_get_membar(amba_conf.ahbmst, i, k);
			mem_start = amba_membar_start(iobar);
			if (amba_membar_type(iobar) == AMBA_TYPE_AHBIO)
				mem_start = AMBA_TYPE_AHBIO_ADDR(mem_start);
				
			if( mem_start )
				len += sprintf( buf+len, "%-36s%-10x\n", "", mem_start );
		}

	}
		
	return len;
	
}

static int __init amba_proc_init(void)
{
	proc_mkdir("amba", proc_bus);
	create_proc_read_entry("bus/amba/devices", 0, NULL, amba_read_procmem, NULL);
	return 0;
}

__initcall(amba_proc_init);
