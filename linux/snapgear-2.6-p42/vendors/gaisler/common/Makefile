
#
# config
#

VERSION=2.6.5-l1

KERNEL_ARCHIVE=linux-2.6.5.tar.bz2
PATCHES=nocache_npages_min.patch leon_kernel.patch

export KERNEL_ARCHIVE
export PATCHES

BB_ARCHIVE=busybox-1.00-pre8.tar.gz
BB_CONFIG=busybox_config

export BB_ARCHIVE
export BB_CONFIG

MKROOTFS=mkrootfs.sh

CROSS_COMPILE=sparc-linux-
export CROSS_COMPILE

OBJDUMP=$(CROSS_COMPILE)objdump
OBJCOPY=$(CROSS_COMPILE)objcopy
LD=$(CROSS_COMPILE)ld
CC=$(CROSS_COMPILE)gcc -Ilinux/include -I. -D__KERNEL__ -Wall -mno-fpu -nostdinc -iwithprefix include -O2

GENROMFS=genromfs
E2FSIMAGE=e2fsimage

IMAGE=linux/arch/sparc/boot/image

#
# primary build targets
#

all: image.tsim image.dsu

image.tsim: tsim.lds image prom_stage1.o rdimage.o prom_stage2.o pgt.o
	$(LD) -X -T $< -o $@

image.dsu: dsu.lds image prom_stage1.o rdimage.o prom_stage2.o pgt.o
	$(LD) -X -T $< -o $@

image.dat: image.dsu
	$(OBJDUMP) -s image.dsu | \
	sed -e 's/^ 4/0/;/^[0-9a-f]\{8\}/b;d' >image.dat

image.asm: image.tsim
	$(OBJDUMP) -d image.tsim >image.asm

#
# convenience targets
#

run: image.tsim
	if [ -e tsim.do ]; then tsim-leon-mmu -c tsim.do image.tsim; \
	else tsim-leon-mmu image.tsim; fi

bprom.vhd: prom_stage1.o leon
	$(OBJCOPY) -O binary prom_stage1.o leon/pmon/prom.bin && \
	cd leon/pmon && ./rom2vhdl prom.bin -o ../leon/bprom.vhd

#
# linux configuration/maintaining targets
#

extract: arc/$(KERNEL_ARCHIVE)
	scripts/extract_linux.sh

defconfig:
	[ ! -e linux ] && make extract || :
	cp arc/linux_config linux/.config
	cd linux && make ARCH=sparc KBUILD_VERBOSE=1 oldconfig

menuconfig:
	[ ! -e linux ] && make extract || :
	[ ! -e linux/.config ] && make defconfig || :
	cd linux && make ARCH=sparc KBUILD_VERBOSE=1  menuconfig

make:
	[ ! -e linux ] && make extract || :
	[ ! -e linux/.config ] && make defconfig || :
	cd linux && make ARCH=sparc KBUILD_VERBOSE=1 

mrproper:
	[ ! -e linux ] && make extract || :
	[ ! -e linux/.config ] && make defconfig || :
	cd linux && make ARCH=sparc KBUILD_VERBOSE=1  mrproper

lclean:
	[ ! -e linux ] && make extract || :
	[ ! -e linux/.config ] && make defconfig || :
	cd linux && make ARCH=sparc KBUILD_VERBOSE=1  clean

# exclude all archs except sparc here
tags:
	cd linux && \
	exuberant-ctags -R \
	--exclude=asm-a* \
	--exclude=asm-c* \
	--exclude=asm-h* \
	--exclude=asm-i* \
	--exclude=asm-m* \
	--exclude=asm-p* \
	--exclude=asm-s3* \
	--exclude=asm-sh* \
	--exclude=asm-sparc64 \
	--exclude=asm-um \
	--exclude=asm-v* \
	--exclude=asm-x* \
	--exclude=arch/a* \
	--exclude=arch/c* \
	--exclude=arch/h* \
	--exclude=arch/i* \
	--exclude=arch/m* \
	--exclude=arch/p* \
	--exclude=arch/s3* \
	--exclude=arch/sh \
	--exclude=arch/sparc64 \
	--exclude=arch/um \
	--exclude=arch/v850 \
	--exclude=arch/x*

#
# busybox configuration/maintaining targets
#

extract_bb: arc/$(BB_ARCHIVE)
	scripts/extract_bb.sh

install_bb:
	[ ! -e bb ] && make extract_bb || :
	cd bb && make dep && make && make install PREFIX=../rootfs
	-rm rdimage.o    #force rebuild

#
# cleaning targets
#

clean:
	-rm *.o image pgt.S
	make -C lib clean


dist-clean: clean
	-rm image.*

maintainer-clean: dist-clean
	-rm -fr linux bb rootfs

dist:
	./scripts/make_dist.sh linux-$(VERSION)

#
# (mostly) private targets
#

$(IMAGE):
	[ ! -e linux ] && make extract || :
	[ ! -e linux/.config ] && make defconfig || :
	cd linux && make ARCH=sparc KBUILD_VERBOSE=1

rdimage.o:
	[ ! -e rootfs ] && make mkrootfs && make install_bb || :
	$(GENROMFS) -V "ROMdisk" -f rdimage.raw -d rootfs && \
	gzip -f rdimage.raw && \
	$(LD) -r -b binary rdimage.raw.gz -o rdimage.o && \
	rm rdimage.raw*

e2fs:
	[ ! -e rootfs ] && make mkrootfs && make install_bb || :
	$(E2FSIMAGE) -s 1024 -f rdimage.raw -d rootfs && \
	gzip -f rdimage.raw && \
	$(LD) -r -b binary rdimage.raw.gz -o rdimage.o && \
	rm rdimage.raw*

mkrootfs: scripts/$(MKROOTFS)
	./scripts/$(MKROOTFS) rootfs

pgt.S: pgt_gen.c
	gcc -Ilinux/include -D__KERNEL__ -o pgt_gen pgt_gen.c && \
	./pgt_gen >pgt.S && rm pgt_gen

prom_stage2.o: prom_config.h

prom_stage1.o: prom_config.h

image: $(IMAGE)
	cp $(IMAGE) image

