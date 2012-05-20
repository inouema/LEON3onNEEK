# $Id: Makefile,v 1.10 2000/02/23 08:17:46 jj Exp $
# Makefile for the Sparc boot stuff.
#
# Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
# Copyright (C) 1997,1998 Jakub Jelinek (jj@ultra.linux.cz)

ROOT_IMG	:= /usr/src/root.img
ELFTOAOUT	:= elftoaout

hostprogs-y	:= piggyback btfixupprep
targets		:= tftpboot.img btfix.o btfix.S image

MKIMAGE		:= $(srctree)/scripts/mkuboot.sh

quiet_cmd_elftoaout	= ELFTOAOUT $@
      cmd_elftoaout	= $(ELFTOAOUT) $(obj)/image -o $@
quiet_cmd_piggy		= PIGGY   $@
      cmd_piggy		= $(obj)/piggyback $@ $(obj)/System.map $(ROOT_IMG)
quiet_cmd_btfix		= BTFIX   $@
      cmd_btfix		= $(OBJDUMP) -x vmlinux | $(obj)/btfixupprep > $@
quiet_cmd_sysmap        = SYSMAP  $(obj)/System.map
      cmd_sysmap        = $(CONFIG_SHELL) $(srctree)/scripts/mksysmap
quiet_cmd_image = LD      $@
      cmd_image = $(LD) $(LDFLAGS) $(EXTRA_LDFLAGS) $(LDFLAGS_$(@F)) -o $@

define rule_image
	$(if $($(quiet)cmd_image),               \
	  echo '  $($(quiet)cmd_image)' &&)      \
	  $(cmd_image);                          \
	$(if $($(quiet)cmd_sysmap),              \
	  echo '  $($(quiet)cmd_sysmap)' &&)  \
	$(cmd_sysmap) $@ $(obj)/System.map;      \
	if [ $$? -ne 0 ]; then                   \
		rm -f $@;                        \
		/bin/false;                      \
	fi;                                      \
	echo 'cmd_$@ := $(cmd_image)' > $(@D)/.$(@F).cmd
endef

BTOBJS := $(HEAD_Y) $(INIT_Y)
BTLIBS := $(CORE_Y) $(LIBS_Y) $(DRIVERS_Y) $(NET_Y)
LDFLAGS_image := -T arch/sparc/kernel/vmlinux.lds $(BTOBJS) \
                  --start-group $(BTLIBS) --end-group \
                  $(kallsyms.o) $(obj)/btfix.o

# Link the final image including btfixup'ed symbols.
# This is a replacement for the link done in the top-level Makefile.
# Note: No dependency on the prerequisite files since that would require
# make to try check if they are updated - and due to changes
# in gcc options (path for example) this would result in
# these files being recompiled for each build.
$(obj)/image: $(obj)/btfix.o FORCE
	$(call if_changed_rule,image)

$(obj)/tftpboot.img: $(obj)/piggyback $(obj)/System.map $(obj)/image FORCE
	$(call if_changed,elftoaout)
	$(call if_changed,piggy)

$(obj)/btfix.S: $(obj)/btfixupprep vmlinux FORCE
	$(call if_changed,btfix)

# The following lines make a readable image for U-Boot.
#  uImage   - Binary file read by U-boot
#  uImage.o - object file of uImage for loading with a
#             flash programmer understanding ELF.

OBJCOPYFLAGS_image.bin := -S -O binary -R .note -R .comment
$(obj)/image.bin: $(obj)/image FORCE
	$(call if_changed,objcopy)

$(obj)/image.gz: $(obj)/image.bin
	$(call if_changed,gzip)

# Start of Main memory
ifndef UIMAGE_LOADADDR
UIMAGE_LOADADDR=0x40004000
endif

# The first sector after the U-Boot image (256k)
ifndef UIMAGE_FLASHADDR
UIMAGE_FLASHADDR=0x00040000
endif

quiet_cmd_uimage = UIMAGE  $@
      cmd_uimage = $(CONFIG_SHELL) $(MKIMAGE) -A sparc -O linux -T kernel \
               -C gzip -a $(UIMAGE_LOADADDR) -e 0xf0004000 -n 'Linux-$(KERNELRELEASE)' \
               -d $< $@

targets += uImage
$(obj)/uImage: $(obj)/image.gz
	$(call if_changed,uimage)
	sparc-linux-ld -Tdata $(UIMAGE_FLASHADDR) -r -b binary arch/sparc/boot/uImage -o arch/sparc/boot/uImage.o
	@echo '  Image $@ is ready'
