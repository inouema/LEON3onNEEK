-include $(LINUX_CONFIG)
-include $(CONFIG_CONFIG)
-include $(ARCH_CONFIG)

LINUXFILE = image
ROMFSFILE = romfs.img
LINUXIMG  = $(IMAGEDIR)/$(LINUXFILE)
ROMFSIMG  = $(IMAGEDIR)/$(ROMFSFILE)
ROMFSIMGOBJ  = $(IMAGEDIR)/rdimage.o
FLASH     = $(IMAGEDIR)/flash.bin
TOOLS     = $(ROOTDIR)/tools
TSIMIMAGE = $(IMAGEDIR)/image.tsim
DSUIMAGE = $(IMAGEDIR)/image.dsu
FLASHBZIMAGE =  $(IMAGEDIR)/image.flashbz
FLASHIMAGE =  $(IMAGEDIR)/image.flash
COMONDIR = $(ROOTDIR)/vendors/gaisler/common
COMONLIBDIR = $(COMONDIR)/lib
COMONLIB = $(COMONDIR)/lib/boot.a
TMPDIR = $(IMAGEDIR)/progs

CC=$(CROSS_COMPILE)gcc -I../common -I$(ROOTDIR)/$(LINUXDIR)/include -I. -D__KERNEL__ -Wall -mno-fpu -nostdinc -iwithprefix include -O2

ifeq ($(CONFIG_DEFAULTS_GAISLER_LEON2_MV8),y)
	ARITH_CFLAGS = -mcpu=v8
endif
ifneq ($(CONFIG_DEFAULTS_GAISLER_LEON2_FPU),y)
	ARITH_CFLAGS += -msoft-float
endif

ifeq ($(findstring glibc,$(LIBCDIR)),glibc)
MULTILIB_DIR = $(shell $(CROSS_COMPILE)gcc $(ARITH_CFLAGS) -print-multi-directory)
CROSS_COMPILER_ROOT = $(shell which $(CROSS_COMPILE)gcc | sed -e 's/bin\/sparc-linux-gcc//')
LATESTGLIBC_VERSION = $(shell ls  $(CROSS_COMPILER_ROOT)/sparc-linux/lib/libc-* | tail -n 1 | sed -e 's/^.*libc-//' -e 's/.so*//')
endif

DIRS = 

ROMFS_DIRS = \
	bin \
	dev dev/flash dev/pts dev/etherd dev/input dev/usb \
	etc etc/config etc/init.d etc/default \
	home home/nfs home/httpd home/httpd/cgi-bin \
	lib lib/modules/$(LINUX26VER) \
	mnt \
	proc \
	sbin \
	usr usr/bin usr/sbin \
	var sys

ifneq ($(CONFIG_KERNEL_ROOTMEM_ROMFS),y)
CONFIG_KERNEL_ROOTMEM_ROMFS_PRE=0
else
CONFIG_KERNEL_ROOTMEM_ROMFS_PRE=1
endif

ifneq ($(CONFIG_KERNEL_ROOTMEM_INITRAMFS),y)
CONFIG_KERNEL_ROOTMEM_INITRAMFS_PRE=0
else
CONFIG_KERNEL_ROOTMEM_INITRAMFS_PRE=1
endif

ifeq ($(CONFIG_KERNEL_ROOTMEM_ROMFS),y)
ifdef CONFIG_ROMFS_FS
FSIMG = $(ROMFSIMG)
endif
endif

DEVICES = \
	ram,b,1,0	ram1,b,1,1 \
	null,c,1,3	tty1,c,4,1	tty2,c,4,2 \
	tty,c,5,0	console,c,5,1	ttyS0,c,4,64	ttyS1,c,4,65\
	\
	fb0,c,29,0 \
	\
	hda,b,3,0      hda1,b,3,1         hda2,b,3,2       hda3,b,3,3\
	hda4,b,3,4     hdb,b,3,64         hdb1,b,3,65\
	ptyp0,c,2,0    ptyp1,c,2,1        ptyp2,c,2,2      ptyp3,c,2,3 \
	ptyp4,c,2,4    ptyp5,c,2,5        ptyp6,c,2,6      ptyp7,c,2,7 \
	ptyp8,c,2,8    ptyp9,c,2,9        ptypa,c,2,10     ptypb,c,2,11 \
	ptypc,c,2,12   ptypd,c,2,13       ptype,c,2,14     ptypf,c,2,15 \
	\
	tty0,c,4,0     tty1,c,4,1         tty2,c,4,2       tty3,c,4,3 \
	tty4,c,4,4     tty5,c,1,3         tty6,c,4,6       tty7,c,4,7 \
	tty8,c,4,8     tty9,c,4,9   \
	\
	ttyp0,c,3,0    ttyp1,c,3,1        ttyp2,c,3,2      ttyp3,c,3,3 \
	ttyp4,c,3,4    ttyp5,c,3,5        ttyp6,c,3,6      ttyp7,c,3,7 \
	ttyp8,c,3,8    ttyp9,c,3,9        ttypa,c,3,10     ttypb,c,3,11 \
	ttypc,c,3,12   ttypd,c,3,13       ttype,c,3,14     ttypf,c,3,15 \
	\
	i2c-0,c,89,0	i2c-1,c,89,1	i2c-2,c,89,2	i2c-3,c,89,3 \
	i2c-4,c,89,4	i2c-5,c,89,5	i2c-6,c,89,6	i2c-7,c,89,7 \
	\
	etherd/err,c,152,2 		  etherd/discover,c,152,3  \
	etherd/interfaces,c,152,4	  etherd/revalidate,c,152,5 \
	etherd/flush,c,152,6 	\
	etherd/e0.0,b,152,0    		  etherd/e0.1,b,152,1    \
	etherd/e0.2,b,152,2    		  etherd/e0.3,b,152,3    \
	etherd/e0.4,b,152,4    		  etherd/e0.5,b,152,5    \
	etherd/e0.6,b,152,6    		  etherd/e0.7,b,152,7    \
	etherd/e0.8,b,152,8    		  etherd/e0.9,b,152,9    \
	etherd/e0.10,b,152,10  		  etherd/e0.11,b,152,11    \
	etherd/e0.12,b,152,12   	  etherd/e0.13,b,152,13    \
	etherd/e0.14,b,152,14  		  etherd/e0.15,b,152,15    \
	\
	sda,b,8,0      sda1,b,8,1	  sda2,b,8,2       sda3,b,8,3 \
	sdb,b,8,16     sdb1,b,8,17	  sdb2,b,8,18      sdb3,b,16,19 \
	sdc,b,8,32     sdc1,b,8,33	  sdc2,b,8,34      sdc3,b,8,35 \
	sdd,b,8,48     sdd1,b,8,49	  sdd2,b,8,50      sdd3,b,8,51 \
	sde,b,8,64     sde1,b,8,65	  sde2,b,8,66      sde3,b,8,67 \
	sdf,b,8,80     sdf1,b,8,81	  sdf2,b,8,82      sdf3,b,8,83 \
	\
	input/mouse,c,10,149	input/keyboard,c,10,150	\
	\
	input/mouse0,c,13,32 	input/mouse1,c,13,33	input/mouse2,c,13,34 \
	input/mouse3,c,13,35 	input/mouse4,c,13,36	input/mouse5,c,13,37 \
	input/mouse6,c,13,38 	input/mouse7,c,13,39	input/mouse8,c,13,40 \
	input/mouse9,c,13,41 	input/mouse10,c,13,42	input/mouse11,c,13,43 \
	input/mouse12,c,13,44 	input/mouse13,c,13,45	input/mouse14,c,13,46 \
	\
	input/mice,c,13,63 \
	\
	input/event0,c,13,64 	input/event1,c,13,65 	input/event2,c,13,66 \
	input/event3,c,13,67 	input/event4,c,13,68 	input/event5,c,13,69 \
	input/event6,c,13,70 	input/event7,c,13,71 	input/event8,c,13,72 \
	input/event9,c,13,73 	input/event10,c,13,74 	input/event11,c,13,75 \
	input/event12,c,13,76 	input/event13,c,13,77 	input/event14,c,13,78 \
	\
	usb/hiddev0,c,180,96	usb/hiddev1,c,180,97	usb/hiddev2,c,180,98 \
	usb/hiddev3,c,180,99	usb/hiddev4,c,180,100	usb/hiddev5,c,180,101 \
	usb/hiddev6,c,180,102	usb/hiddev7,c,180,103	usb/hiddev8,c,180,104 \
	usb/hiddev9,c,180,105	usb/hiddev10,c,180,106	usb/hiddev11,c,180,107 \
	\
	video0,c,81,0	video1,c,81,1	video2,c,81,2 	video3,v,81,3 \
	video4,c,81,4	video5,c,81,5	video6,c,81,6 	video7,v,81,7 \
	\
	mtd0,c,90,0	mtdr0,c,90,1	mtd1,c,90,2	mtdr1,c,90,3 \
	mtd2,c,90,4	mtdr2,c,90,5	mtd3,c,90,6	mtdr3,c,90,7 \
	mtd4,c,90,8	mtdr4,c,90,9	mtd4,c,90,10	mtdr4,c,90,11

#ifdef CONFIG_VGA_CONSOLE
#DEVICES := $(DEVICES) ttyS0,c,4,1   ttyS1,c,4,2 console,c,4,1
#else
#DEVICES := $(DEVICES) ttyS0,c,4,64   ttyS1,c,4,65 console,c,4,64
#endif


all:
	dirs=$(DIRS) ; \
	for i in $$dirs ; do  make -C $$i || exit $? ; done

ifneq ($(CONFIG_KERNEL_ROOTMEM_NONE),y)
ifneq ($(CONFIG_KERNEL_INITRAMFS_SOURCE_EXCLUSIVE),y)
	#Setup basic romfs skeleton
	-rm -rf $(ROMFSDIR)/dev/* 
	[ -d $(ROMFSDIR)/$$i ] || mkdir -p $(ROMFSDIR)
	for i in $(ROMFS_DIRS); do \
		[ -d $(ROMFSDIR)/$$i ] || mkdir -p $(ROMFSDIR)/$$i; \
	done

endif
endif

clean:
	-dirs=$(DIRS) ; \
	for i in $$dirs; do [ ! -d $$i ] || make -C $$i clean; done
	rm -rf *.o 
	rm -f $(ROOTDIR)/$(LINUXDIR)/initramfs-root.txt
	make -C $(COMONLIBDIR) clean

ifneq ($(CONFIG_KERNEL_ROOTMEM_NONE),y)
ifneq ($(CONFIG_KERNEL_INITRAMFS_SOURCE_EXCLUSIVE),y)
.PHONY: romfs
romfs:
	dirs=$(DIRS) ; for i in $$dirs; do  make -C $$i romfs || exit $? ; done
ifeq ($(CONFIG_KERNEL_ROOTMEM_ROMFS),y)
	for i in $(DEVICES); do \
		devfname=`basename $$i`; \
		devpath=$${i%%$$devfname}; \
		touch $(ROMFSDIR)/dev/$$devpath/@$$devfname; \
	done
endif

ifdef CONFIG_ROMFS_FS
	$(ROMFSINST) -s /var/tmp /tmp
endif
	$(ROMFSINST) -s /var/tmp/log /dev/log
	cp -au romfs $(ROMFSDIR)/..
	-find $(ROMFSDIR) -path '*.svn*' -exec 'rm' '-rf' '{}' ';'
	chmod a+rwx $(ROMFSDIR)/etc/init.d/rcS
	echo "$(VERSIONSTR) -- " `date` > $(ROMFSDIR)/etc/version
	date '+%Y.%m.%d-%T' > $(ROMFSDIR)/etc/build-date

ifeq ($(findstring glibc,$(LIBCDIR)),glibc)
	cp $(CROSS_COMPILER_ROOT)/sparc-linux/lib/$(MULTILIB_DIR)/ld-$(LATESTGLIBC_VERSION).so $(ROMFSDIR)/lib/ld-linux.so.2
	cp $(CROSS_COMPILER_ROOT)/sparc-linux/lib/$(MULTILIB_DIR)/libc-$(LATESTGLIBC_VERSION).so $(ROMFSDIR)/lib/libc.so.6
	cp $(CROSS_COMPILER_ROOT)/sparc-linux/lib/$(MULTILIB_DIR)/libm-$(LATESTGLIBC_VERSION).so $(ROMFSDIR)/lib/libm.so.6
	echo 
	# for nsswitch to lookup "xxx_files_xxx" 
	cp $(CROSS_COMPILER_ROOT)/sparc-linux/lib/$(MULTILIB_DIR)/libnss_files-$(LATESTGLIBC_VERSION).so $(ROMFSDIR)/lib/libnss_files-$(LATESTGLIBC_VERSION).so
	ln -f -s libnss_files-$(LATESTGLIBC_VERSION).so $(ROMFSDIR)/lib/libnss_files.so  
	ln -f -s libnss_files-$(LATESTGLIBC_VERSION).so $(ROMFSDIR)/lib/libnss_files.so.2 
	echo 	
	cp $(CROSS_COMPILER_ROOT)/sparc-linux/lib/$(MULTILIB_DIR)/libnss_compat-$(LATESTGLIBC_VERSION).so $(ROMFSDIR)/lib/libnss_compat-$(LATESTGLIBC_VERSION).so
	ln -f -s libnss_compat.so.2 $(ROMFSDIR)/lib/libnss_compat.so 
	ln -f -s libnss_compat-$(LATESTGLIBC_VERSION).so $(ROMFSDIR)/lib/libnss_compat.so.2 
	echo 
	cp $(CROSS_COMPILER_ROOT)/sparc-linux/lib/$(MULTILIB_DIR)/libnsl-$(LATESTGLIBC_VERSION).so $(ROMFSDIR)/lib/libnsl-$(LATESTGLIBC_VERSION).so
	ln -f -s libnsl-$(LATESTGLIBC_VERSION).so $(ROMFSDIR)/lib/libnsl.so.1 
	ln -f -s libnsl.so.1 $(ROMFSDIR)/lib/libnsl.so 
	echo 	
	cp $(CROSS_COMPILER_ROOT)/sparc-linux/lib/$(MULTILIB_DIR)/libutil-$(LATESTGLIBC_VERSION).so $(ROMFSDIR)/lib/libutil-$(LATESTGLIBC_VERSION).so
	ln -f -s libutil-$(LATESTGLIBC_VERSION).so $(ROMFSDIR)/lib/libutil.so.1 
	ln -f -s libutil.so.1 $(ROMFSDIR)/lib/libutil.so 
	echo 
	cp $(CROSS_COMPILER_ROOT)/sparc-linux/lib/$(MULTILIB_DIR)/libcrypt-$(LATESTGLIBC_VERSION).so $(ROMFSDIR)/lib/libcrypt-$(LATESTGLIBC_VERSION).so
	ln -f -s libcrypt-$(LATESTGLIBC_VERSION).so $(ROMFSDIR)/lib/libcrypt.so.1 
	ln -f -s libcrypt.so.1 $(ROMFSDIR)/lib/libcrypt.so 
	echo 	
	#cp tcp-wrappers-7.6/libwrap.7.6.0.so $(ROMFSDIR)/lib/
	#ln -f -s libwrap.7.6.0.so $(ROMFSDIR)/lib/libwrap.so 
	#ln -f -s libwrap.7.6.0.so $(ROMFSDIR)/lib/libwrap.so. 
	echo 	
	$(CROSS_COMPILE)strip -g $(ROMFSDIR)/lib/*.so*
	echo 	
	#cp $(CROSS_COMPILER_ROOT)/sparc-linux/lib/ld-$(LATESTGLIBC_VERSION).so $(ROMFSDIR)/lib/ld-$(LATESTGLIBC_VERSION).so
	#cp $(CROSS_COMPILER_ROOT)/sparc-linux/lib/libc-$(LATESTGLIBC_VERSION).so $(ROMFSDIR)/lib/libc.so.6
endif
	[ -d $(TMPDIR) ] || mkdir -p $(TMPDIR)
	for i in `find $(ROMFSDIR)`; \
	do \
	if [ -f "$$i" -a ! -h "$$i" ]; then \
		$(CROSS_COMPILE)objdump -h $$i 2>&1 | grep -q .text ;\
		if [ $$? -eq 0 ]; then \
			make TARGET_FILE=$$i Convert; \
		fi ;\
	fi ;\
	done
	-$(STRIP) $(ROMFSDIR)/home/httpd/cgi-bin/*
	-$(STRIP) $(ROMFSDIR)/sbin/*
	-$(STRIP) $(ROMFSDIR)/bin/*
ifeq ($(CONFIG_KERNEL_ROOTMEM_INITRAMFS),y)
	#kinit requires symlink in /init
	ln -fs $(CONFIG_KERNEL_INIT_PATH) $(ROMFSDIR)/init 
	chmod +x $(ROOTDIR)/$(LINUXDIR)/scripts/gen_initramfs_list.sh
	$(ROOTDIR)/$(LINUXDIR)/scripts/gen_initramfs_list.sh $(ROMFSDIR) \
		> $(ROOTDIR)/$(LINUXDIR)/initramfs-root.txt 2>&1
	for i in $(DEVICES); do \
		name=$${i%%,*}; \
		i=$${i##$${name},}; \
		type=$${i%%,*}; \
		i=$${i##$${type},}; \
		maj=$${i%%,*}; \
		i=$${i##$${maj},}; \
		min=$${i%%,*}; \
		echo "nod /dev/$$name 0600 0 0 $$type $$maj $$min" >> $(ROOTDIR)/$(LINUXDIR)/initramfs-root.txt; \
	done
	
ifneq ($(CONFIG_KERNEL_INITRAMFS_SOURCE),"")
	cat $(CONFIG_KERNEL_INITRAMFS_SOURCE) >> $(ROOTDIR)/$(LINUXDIR)/initramfs-root.txt
endif
endif

$(ROMFSIMG):
	genromfs -v -V "ROMdisk" -f $(ROMFSIMG) -d $(ROMFSDIR)
	gzip -f $(ROMFSIMG)
	$(CROSS_COMPILE)ld -r -b binary $(ROMFSIMG).gz -o $(ROMFSIMGOBJ)
endif
endif

Convert:
	$(CROSS_COMPILE)objdump -d $(TARGET_FILE) >$(TMPDIR)/$(notdir $(TARGET_FILE)).dis

###################################################################################
# dummy rule

ifeq ($(CONFIG_KERNEL_ROOTMEM_ROMFS),y)
$(IMAGEDIR)/image.tsim2: tsim.lds.o $(LINUXIMG) prom_stage1.o $(ROMFSIMGOBJ) prom_stage2.o pgt.o
	$(CROSS_COMPILE)ld -X -T $< -o $@

genrom_rf: 
	genromfs -v -V "ROMdisk" -f $(ROMFSIMG).2 -d $(RFDIR)
	gzip -f $(ROMFSIMG).2
	$(CROSS_COMPILE)ld -r -b binary $(ROMFSIMG).2.gz -o $(ROMFSIMGOBJ)

genrom: genrom_rf $(IMAGEDIR)/image.tsim2
else

$(IMAGEDIR)/image.tsim2: tsim.lds.o $(LINUXIMG) prom_stage1.o prom_stage2.o pgt.o
	$(CROSS_COMPILE)ld -X -T $< -o $@
endif

###################################################################################
# image creation

.PHONY: image $(FSIMG)
image: $(FLASHBZIMAGE) dis
	$(if $(strip $(COPYIMAGE)),cp -r $(IMAGEDIR) $(COPYIMAGE))

$(LINUXIMG): $(FSIMG) $(ROOTDIR)/$(LINUXDIR)/arch/sparc/boot/$(LINUXFILE)
	[ -d $(IMAGEDIR) ] || mkdir -p $(IMAGEDIR)
	cp -f $(ROOTDIR)/$(LINUXDIR)/arch/sparc/boot/$(LINUXFILE) $(LINUXIMG)


dis: $(LINUXIMG)
	$(CROSS_COMPILE)objdump -d $(LINUXIMG) >$(LINUXIMG).dis
	$(CROSS_COMPILE)objdump -d $(FLASHBZIMAGE) >$(FLASHBZIMAGE).dis
	$(CROSS_COMPILE)objdump -d $(DSUIMAGE) >$(DSUIMAGE).dis
	$(CROSS_COMPILE)objdump -x $(DSUIMAGE) >$(DSUIMAGE).x
###################################################################################
#tsim loadable image

ifeq ($(CONFIG_KERNEL_ROOTMEM_ROMFS),y)
$(TSIMIMAGE): tsim.lds.o $(LINUXIMG) prom_stage1.o $(ROMFSIMGOBJ) prom_stage2.o pgt.o
	$(CROSS_COMPILE)ld -X -T $^ -o $@ #-M
	$(CROSS_COMPILE)ld -X -T $^ -o $@ 
else
$(TSIMIMAGE): tsim.lds.o $(LINUXIMG) prom_stage1.o prom_stage2.o pgt.o
	$(CROSS_COMPILE)ld -X -T $^ -o $@ 
endif

###################################################################################
#dsu loadable image, same as tsim image but without rom section

ifeq ($(CONFIG_KERNEL_ROOTMEM_ROMFS),y)
$(DSUIMAGE): dsu.lds.o $(LINUXIMG) $(ROMFSIMGOBJ) prom_stage2.o pgt.o
	$(CROSS_COMPILE)ld -X -T $^ -o $@
else
$(DSUIMAGE): dsu.lds.o $(LINUXIMG) prom_stage2.o pgt.o
	$(CROSS_COMPILE)ld -X -T $^ -o $@
endif

###################################################################################
#flashbz compressed image

$(FLASHBZIMAGE): flash.lds.o locore.o  bzmain.o $(COMONLIB) $(COMONDIR)/piggy.o 
	echo "Note: The flash image is for hardware only. "
	echo "Note: If you want to build a tsim flashloader, remove the BZIMAGE flag (otherwise no sram flag will cause problems)"
	echo "Note: if you download with dsumon use the -nosram switch if you configured for sdram "
	$(CROSS_COMPILE)ld -X -T $^ -o $@
#-M

$(COMONLIB): $(COMONDIR)/lib/_put.c $(COMONDIR)/lib/_gunzip.c $(COMONDIR)/lib/inflate.c
	make -C $(COMONLIBDIR)

$(COMONDIR)/piggy: $(DSUIMAGE) 
	$(CROSS_COMPILE)objcopy -O binary -R .note -R .comment -S  $(DSUIMAGE) $(COMONDIR)/piggy

$(COMONDIR)/piggy.gz: $(COMONDIR)/piggy 
	gzip -f -9 < $(COMONDIR)/piggy > $(COMONDIR)/piggy.gz

$(COMONDIR)/piggy.o:  $(COMONDIR)/piggy.gz 
	$(CROSS_COMPILE)ld -r -b binary -o $(COMONDIR)/piggy.o $(COMONDIR)/piggy.gz
	$(CROSS_COMPILE)size $(COMONDIR)/piggy.o

locore.o: locore.S $(COMONDIR)/prom_config.h ../common/bootloader.h
	$(CROSS_COMPILE)gcc -I../common -DBZIMAGE -D__ASSEMBLY__ -I$(ROOTDIR)/$(LINUXDIR)/include -c -o $@ $<


###################################################################################

pgt.S: $(COMONDIR)/pgt_gen.c $(COMONDIR)/bootloader.h
	gcc -I$(ROOTDIR)/$(LINUXDIR)/include -D__KERNEL__ -o pgt_gen $(COMONDIR)/pgt_gen.c && \
	./pgt_gen >pgt.S && rm pgt_gen

prom_stage1.o: prom_stage1.S $(COMONDIR)/prom_config.h $(COMONDIR)/bootloader.h

prom_stage2.o: prom_stage2.c $(COMONDIR)/prom_config.h $(COMONDIR)/bootloader.h
	$(CC) $(CFLAGS) -DCONFIG_KERNEL_ROOTMEM_INITRAMFS=$(CONFIG_KERNEL_ROOTMEM_INITRAMFS_PRE) \
			-DCONFIG_KERNEL_ROOTMEM_ROMFS="$(CONFIG_KERNEL_ROOTMEM_ROMFS_PRE)" \
			-DCONFIG_KERNEL_INIT_PATH=\"$(CONFIG_KERNEL_INIT_PATH)\" -c -o $@ $<

$(COMONDIR)/prom_stage1.S: $(COMONDIR)/prom_config.h

$(COMONDIR)/prom_stage2.c: $(COMONDIR)/prom_config.h

prom_stage1.o: prom_stage1.S $(COMONDIR)/prom_config.h
	$(CROSS_COMPILE)gcc -D__ASSEMBLY__  -I../common -I$(ROOTDIR)/$(LINUXDIR)/include  -c -o $@ $<

###################################################################################
rmdsuldso:
	-rm -f dsu.lds.o

rmflashldso:
	-rm -f flash.lds.o

.PHONY: rmremovedefs rmflashldso rmdsuldso

rmremovedefs:
	-echo "" > $(COMONDIR)/remove_predefs.h

dsu.lds.o: rmdsuldso rmremovedefs $(COMONDIR)/dsu.lds.S $(COMONDIR)/bootloader.h
	echo "" > $(COMONDIR)/remove_predefs.h
	$(CROSS_COMPILE)gcc -dM -C -E -P $(COMONDIR)/dsu.lds.S | cut -d' ' -f -2 | sed 's/#define/#undef/g' > $(COMONDIR)/remove_predefs.h
	$(CROSS_COMPILE)gcc -E -C -P -DCONFIG_KERNEL_ROOTMEM_ROMFS="$(CONFIG_KERNEL_ROOTMEM_ROMFS_PRE)" -DRDIMAGE="$(ROMFSIMGOBJ)" -DLINUXIMAGE="$(LINUXIMG)" $(COMONDIR)/dsu.lds.S -o dsu.lds.o

tsim.lds.o: rmremovedefs $(COMONDIR)/tsim.lds.S $(COMONDIR)/bootloader.h
	echo "" > $(COMONDIR)/remove_predefs.h
	$(CROSS_COMPILE)gcc -dM -C -E -P $(COMONDIR)/tsim.lds.S | cut -d' ' -f -2 | sed 's/#define/#undef/g' > $(COMONDIR)/remove_predefs.h
	$(CROSS_COMPILE)gcc -E -C -P -DCONFIG_KERNEL_ROOTMEM_ROMFS="$(CONFIG_KERNEL_ROOTMEM_ROMFS_PRE)" -DRDIMAGE="$(ROMFSIMGOBJ)" -DLINUXIMAGE="$(LINUXIMG)" $(COMONDIR)/tsim.lds.S -o tsim.lds.o

flash.lds.o: rmflashldso rmremovedefs $(COMONDIR)/flash.lds.S $(COMONDIR)/piggy $(COMONDIR)/bootloader.h
	echo "" > $(COMONDIR)/remove_predefs.h
	$(CROSS_COMPILE)gcc -dM -C -E -P $(COMONDIR)/flash.lds.S | cut -d' ' -f -2 | sed 's/#define/#undef/g' > $(COMONDIR)/remove_predefs.h
	$(CROSS_COMPILE)gcc -E -C -P -DCONFIG_KERNEL_ROOTMEM_ROMFS="$(CONFIG_KERNEL_ROOTMEM_ROMFS_PRE)" -DDATA_START=$(call _GETSIZE,$(COMONDIR)/piggy)  -DPIGGY="$(COMONDIR)/piggy.o" $(COMONDIR)/flash.lds.S -o flash.lds.o

###################################################################################
_GETSIZE = $(shell ls -la $(1) | awk '{print $$5}')

