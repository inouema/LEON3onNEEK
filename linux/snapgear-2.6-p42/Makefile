############################################################################

#
# Makefile -- Top level uClinux makefile.
#
# Copyright (c) 2001-2004, SnapGear (www.snapgear.com)
# Copyright (c) 2001, Lineo
#

VERSIONPKG = 3.1.0
VERSIONSTR = $(CONFIG_VENDOR)/$(CONFIG_PRODUCT) Version $(VERSIONPKG)

############################################################################
#
# Lets work out what the user wants, and if they have configured us yet
#

ifeq (.config,$(wildcard .config))
include .config

all: linux_headers subdirs romfs linux modules modules_install image
else
all: config_error
endif

############################################################################
#
# Get the core stuff worked out
#

LINUXDIR = $(CONFIG_LINUXDIR)
LIBCDIR  = $(CONFIG_LIBCDIR)
ROOTDIR  = $(shell pwd)
PATH	 := $(PATH):$(ROOTDIR)/tools
HOSTCC   = cc
IMAGEDIR = $(ROOTDIR)/images
RELDIR   = $(ROOTDIR)/release
ROMFSDIR = $(ROOTDIR)/romfs
ROMFSINST= romfs-inst.sh
SCRIPTSDIR = $(ROOTDIR)/config/scripts
TFTPDIR    = /tftpboot
LINUX26VER = 2.6.21.1
LINUX26VER_29 = 2.6.29

LINUX_VERSION_PRE=linux-$(shell expr "$(LINUXDIR)" : "linux-\\([0-9]*\\.[0-9]*\\)")

LINUX_CONFIG  = $(ROOTDIR)/$(LINUXDIR)/.config
CONFIG_CONFIG = $(ROOTDIR)/config/.config
MODULES_CONFIG = $(ROOTDIR)/modules/.config
BUSYBOX_CONFIG = $(ROOTDIR)/user/busybox/busybox-1.8.2/.config

CONFIG_SHELL := $(shell if [ -x "$$BASH" ]; then echo $$BASH; \
	  else if [ -x /bin/bash ]; then echo /bin/bash; \
	  else echo sh; fi ; fi)

ifeq (config.arch,$(wildcard config.arch))
include config.arch
ARCH_CONFIG = $(ROOTDIR)/config.arch
export ARCH_CONFIG
endif

ifneq ($(SUBARCH),)
# Using UML, so make the kernel and non-kernel with different ARCHs
MAKEARCH = $(MAKE) ARCH=$(SUBARCH) CROSS_COMPILE=$(CROSS_COMPILE)
MAKEARCH_KERNEL = $(MAKE) ARCH=$(ARCH) SUBARCH=$(SUBARCH) CROSS_COMPILE=$(CROSS_COMPILE)
else
MAKEARCH = $(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE)
MAKEARCH_KERNEL = $(MAKEARCH)
endif

ifeq ($(CONFIG_KERNEL_ROOTMEM_NONE),y)
 DIRS    = $(VENDOR_TOPDIRS) 
 VENDDIR = $(ROOTDIR)/vendors/$(CONFIG_VENDOR)/$(CONFIG_PRODUCT)/.
else 
 ifeq ($(CONFIG_KERNEL_INITRAMFS_SOURCE_EXCLUSIVE),y)
   DIRS    = $(VENDOR_TOPDIRS) 
   VENDDIR = $(ROOTDIR)/vendors/$(CONFIG_VENDOR)/$(CONFIG_PRODUCT)/.
 else
     ifeq ($(CONFIG_DEFAULTS_LIBC_NONE),y)
     #Do not build additional C libraries if C system library is disabled
     DIRS    = user $(VENDOR_TOPDIRS) 
     VENDDIR = $(ROOTDIR)/vendors/$(CONFIG_VENDOR)/$(CONFIG_PRODUCT)/.

     else
   DIRS    = lib user $(VENDOR_TOPDIRS) 
   VENDDIR = $(ROOTDIR)/vendors/$(CONFIG_VENDOR)/$(CONFIG_PRODUCT)/.
 endif
 endif
endif

export VENDOR PRODUCT ROOTDIR LINUXDIR HOSTCC CONFIG_SHELL
export CONFIG_CONFIG LINUX_CONFIG ROMFSDIR SCRIPTSDIR
export VERSIONPKG VERSIONSTR ROMFSINST PATH IMAGEDIR RELDIR RELFILES TFTPDIR

############################################################################

#
# Config stuff,  we recall ourselves to load the new config.arch before
# running the kernel and other config scripts
#

.PHONY: config.tk config.in

config.in:
	config/mkconfig > config.in

config.tk: config.in
	$(MAKE) -C $(SCRIPTSDIR) tkparse
	ARCH=dummy $(SCRIPTSDIR)/tkparse < config.in > config.tmp
	@if [ -f /usr/local/bin/wish ];	then \
		echo '#!'"/usr/local/bin/wish -f" > config.tk; \
	else \
		echo '#!'"/usr/bin/wish -f" > config.tk; \
	fi
	cat $(SCRIPTSDIR)/header.tk >> ./config.tk
	cat config.tmp >> config.tk
	rm -f config.tmp
	echo "set defaults \"/dev/null\"" >> config.tk
	echo "set help_file \"config/Configure.help\"" >> config.tk
	cat $(SCRIPTSDIR)/tail.tk >> config.tk
	chmod 755 config.tk

save_config:
	cp .config .config.vendor.tmp;
ifeq ($(CONFIG_DEFAULTS_KERNEL_2_6_21_1),y)
	cp -f linux-2.6.21.1/.config .config.linux.tmp
else
	cp -f linux-2.0.x/.config .config.linux.tmp
endif
	echo NOLL, $(LINUX_CONFIG), $(LINUXDIR);
	read;

restore_config:
	cp .config.vendor.tmp .config;
	cp .config.linux.tmp $(LINUX_CONFIG);
	echo ETT, $(LINUX_CONFIG), $(LINUXDIR);
	read;

do_oldconfig_linux:
	$(MAKE) ARCH=sparc -C $(LINUXDIR) oldconfig;

install_linux_config:
	cp -f $(CFG) $(LINUX_CONFIG)
	$(MAKE) ARCH=sparc -C $(LINUXDIR) oldconfig;

prepare_config:
	sed 's/^CONFIG\_INITRAMFS\_SOURCE.*$$/CONFIG_INITRAMFS_SOURCE=\"\"/g' -i $(LINUX_CONFIG);
	@if egrep "^CONFIG_KERNEL_ROOTMEM_INITRAMFS=y" .config > /dev/null; then \
		if egrep "^CONFIG_INITRAMFS_SOURCE" $(LINUX_CONFIG) >/dev/null; then \
			sed 's/^CONFIG\_INITRAMFS\_SOURCE.*$$/CONFIG_INITRAMFS_SOURCE=\"initramfs-root\.txt\"/g' -i $(LINUX_CONFIG); \
		else \
                	echo CONFIG_INITRAMFS_SOURCE=\"initramfs-root\.txt\" >> $(LINUX_CONFIG); \
                fi; \
	fi

	@if egrep "^CONFIG_KERNEL_INITRAMFS_SOURCE_EXCLUSIVE=y" .config > /dev/null; then \
		TMP_SOURCE=`egrep "^CONFIG_KERNEL_INITRAMFS_SOURCE=" .config | sed -e 's/^.*=//g' -e 's/"//g'`; \
		sed s:^CONFIG\_INITRAMFS\_SOURCE.*$$:CONFIG_INITRAMFS_SOURCE=\"$${TMP_SOURCE}\":g -i $(LINUX_CONFIG); \
	fi

vendor_script:
ifeq ($(CONFIG_DEFAULTS_GAISLER_LEON3MMU),y)
	sh vendors/gaisler/leon3mmu/config.pl;
endif
ifeq ($(CONFIG_DEFAULTS_GAISLER_LEON2MMU),y)
	sh vendors/gaisler/leon2mmu/config.pl;
endif
ifeq ($(CONFIG_DEFAULTS_GAISLER_LEON3),y)
	sh vendors/gaisler/leon3/config.pl;
endif
ifeq ($(CONFIG_DEFAULTS_GAISLER_LEON2),y)
	sh vendors/gaisler/leon2/config.pl;
endif

.PHONY: xconfig
xconfig: config.tk
	@wish -f config.tk
	@if [ ! -f .config ]; then \
		echo; \
		echo "You have not saved your config, please re-run make config"; \
		echo; \
		exit 1; \
	 fi
	@if egrep "^CONFIG_TEMPLATES_UPDATE=y" .config > /dev/null; then \
		$(MAKE) template_config; \
		config/setconfig template; \
	else \
		config/setconfig defaults; \
	fi
	
	$(MAKE) prepare_config

	@if egrep "^CONFIG_DEFAULTS_KERNEL=y" .config > /dev/null; then \
		$(MAKE) linux_xconfig; \
	 fi
	@if egrep "^CONFIG_DEFAULTS_MODULES=y" .config > /dev/null; then \
		$(MAKE) modules_xconfig; \
	 fi
	@if egrep "^CONFIG_DEFAULTS_VENDOR=y" .config > /dev/null; then \
		$(MAKE) config_xconfig; \
	 fi
	@config/setconfig final

.PHONY: config
config: config.in
	@HELP_FILE=config/Configure.help \
		$(CONFIG_SHELL) $(SCRIPTSDIR)/Configure config.in
	@if egrep "^CONFIG_TEMPLATES_UPDATE=y" .config > /dev/null; then \
		$(MAKE) template_config; \
		config/setconfig defaults; \
		$(MAKE) template_config; \
	else \
		config/setconfig defaults; \
	fi
	@sed 's/^CONFIG\_INITRAMFS\_SOURCE.*$$/CONFIG_INITRAMFS_SOURCE=\"\"/g' -i $(LINUX_CONFIG)
	@if egrep "^CONFIG_KERNEL_ROOTMEM_INITRAMFS=y" .config > /dev/null; then \
		sed 's/^CONFIG\_INITRAMFS\_SOURCE.*$$/CONFIG_INITRAMFS_SOURCE=\"initramfs-root\.txt\"/g' -i $(LINUX_CONFIG); \
	fi
	@if egrep "^CONFIG_KERNEL_INITRAMFS_SOURCE_EXCLUSIVE=y" .config > /dev/null; then \
		TMP_SOURCE=`egrep "^CONFIG_KERNEL_INITRAMFS_SOURCE=" .config | sed -e 's/^.*=//g' -e 's/"//g'`; \
		sed s:^CONFIG\_INITRAMFS\_SOURCE.*$$:CONFIG_INITRAMFS_SOURCE=\"$${TMP_SOURCE}\":g -i $(LINUX_CONFIG); \
	fi
	@if egrep "^CONFIG_DEFAULTS_KERNEL=y" .config > /dev/null; then \
		$(MAKE) linux_config; \
	 fi
	@if egrep "^CONFIG_DEFAULTS_MODULES=y" .config > /dev/null; then \
		$(MAKE) modules_config; \
	 fi
	@if egrep "^CONFIG_DEFAULTS_VENDOR=y" .config > /dev/null; then \
		$(MAKE) config_config; \
	 fi
	@config/setconfig final

.PHONY: menuconfig
menuconfig: config.in
	$(MAKE) -C $(SCRIPTSDIR)/lxdialog all
	@HELP_FILE=config/Configure.help \
		$(CONFIG_SHELL) $(SCRIPTSDIR)/Menuconfig config.in
	@if [ ! -f .config ]; then \
		echo; \
		echo "You have not saved your config, please re-run make config"; \
		echo; \
		exit 1; \
	 fi	
	@if egrep "^CONFIG_TEMPLATES_UPDATE=y" .config > /dev/null; then \
		$(MAKE) template_config; \
		config/setconfig defaults; \
		$(MAKE) template_config; \
	else \
		config/setconfig defaults; \
	fi

	@sed 's/^CONFIG\_INITRAMFS\_SOURCE.*$$/CONFIG_INITRAMFS_SOURCE=\"\"/g' -i $(LINUX_CONFIG)
	@if egrep "^CONFIG_KERNEL_ROOTMEM_INITRAMFS=y" .config > /dev/null; then \
		sed 's/^CONFIG\_INITRAMFS\_SOURCE.*$$/CONFIG_INITRAMFS_SOURCE=\"initramfs-root\.txt\"/g' -i $(LINUX_CONFIG); \
	fi
	@if egrep "^CONFIG_KERNEL_INITRAMFS_SOURCE_EXCLUSIVE=y" .config > /dev/null; then \
		TMP_SOURCE=`egrep "^CONFIG_KERNEL_INITRAMFS_SOURCE=" .config | sed -e 's/^.*=//g' -e 's/"//g'`; \
		sed s:^CONFIG\_INITRAMFS\_SOURCE.*$$:CONFIG_INITRAMFS_SOURCE=\"$${TMP_SOURCE}\":g -i $(LINUX_CONFIG); \
	fi
	@if egrep "^CONFIG_DEFAULTS_KERNEL=y" .config > /dev/null; then \
		$(MAKE) linux_menuconfig; \
	 fi
	@if egrep "^CONFIG_DEFAULTS_MODULES=y" .config > /dev/null; then \
		$(MAKE) modules_menuconfig; \
	 fi
	@if egrep "^CONFIG_DEFAULTS_VENDOR=y" .config > /dev/null; then \
		$(MAKE) config_menuconfig; \
	 fi
	@config/setconfig final

.PHONY: oldconfig
oldconfig:
	@$(MAKE) oldconfig_linux
	@$(MAKE) oldconfig_modules
	@$(MAKE) oldconfig_config
	@$(MAKE) oldconfig_uClibc
	@config/setconfig final

.PHONY: modules
modules:
	. $(LINUXDIR)/.config; if [ "$$CONFIG_MODULES" = "y" ]; then \
		[ -d $(LINUXDIR)/modules ] || mkdir $(LINUXDIR)/modules; \
		$(MAKEARCH_KERNEL) -C $(LINUXDIR) modules; \
	fi

.PHONY: modules_install
modules_install:
	. $(LINUXDIR)/.config; if [ "$$CONFIG_MODULES" = "y" ]; then \
		[ -d $(ROMFSDIR)/lib/modules ] || mkdir -p $(ROMFSDIR)/lib/modules; \
		$(MAKEARCH_KERNEL) -C $(LINUXDIR) INSTALL_MOD_PATH=$(ROMFSDIR) DEPMOD=true modules_install; \
		rm -f $(ROMFSDIR)/lib/modules/*/build; \
		find $(ROMFSDIR)/lib/modules -type f | xargs -r $(STRIP) -g; \
	fi

linux_xconfig:
	$(MAKEARCH_KERNEL) -C $(LINUXDIR) xconfig
linux_menuconfig:
	$(MAKEARCH_KERNEL) -C $(LINUXDIR) menuconfig
linux_config:
	$(MAKEARCH_KERNEL) -C $(LINUXDIR) config
modules_xconfig:
	[ ! -d modules ] || $(MAKEARCH) -C modules xconfig
modules_menuconfig:
	[ ! -d modules ] || $(MAKEARCH) -C modules menuconfig
modules_config:
	[ ! -d modules ] || $(MAKEARCH) -C modules config
modules_clean:
	-[ ! -d modules ] || $(MAKEARCH) -C modules clean
config_xconfig:
	$(MAKEARCH) -C config xconfig
config_menuconfig:
	$(MAKEARCH) -C config menuconfig
config_config:
	$(MAKEARCH) -C config config
oldconfig_config:
	$(MAKEARCH) -C config oldconfig
oldconfig_modules:
	[ ! -d modules ] || $(MAKEARCH) -C modules oldconfig
oldconfig_linux:
	$(MAKEARCH_KERNEL) -C $(LINUXDIR) oldconfig
oldconfig_uClibc:
	[ -z "$(findstring uClibc,$(LIBCDIR))" ] || $(MAKEARCH) -C $(LIBCDIR) oldconfig

# Copies a template configuration to .config and linux-X/.config
# Template configurations are found in vendor/gaisler/target/templates/template/vendor.config
# and vendor/gaisler/target/templates/template/linux.config
#
template_config:
	@echo
	@echo "* Replacing configuration with template config *"
	@echo
	@template_cfg=`egrep "^CONFIG_TEMPLATE_" .config`;\
	 if [ -n "$${template_cfg}" ]; then \
	   target=`echo $${template_cfg} | cut -d'_' -f3 | tr [:upper:] [:lower:]`; \
	   template=`echo $${template_cfg} | cut -d'_' -f4-| cut -d'=' -f1 | tr [:upper:] [:lower:]`; \
	   dir=vendors/gaisler/$${target}/templates/$${template}; \
	   echo "*********** scanning $${dir}, $${target}, $${template}  *********"; \
	   if [ -f "$${dir}/vendor.config" ]; then \
	     cp -f $${dir}/vendor.config .config; \
	   fi; \
	   if [ -f "$${dir}/linux.config" ]; then \
             $(MAKE) install_linux_config CFG=$${dir}/linux.config; \
	   fi; \
	   if [ -f "$${dir}/apps.config" ]; then \
	     mv -f $(CONFIG_CONFIG) $(CONFIG_CONFIG).old; \
	     cp -f $${dir}/apps.config $(CONFIG_CONFIG); \
	   fi; \
	   if [ -f "$${dir}/busybox.config" ]; then \
	     mv -f $(BUSYBOX_CONFIG) $(BUSYBOX_CONFIG).old; \
	     cp -f $${dir}/busybox.config $(BUSYBOX_CONFIG); \
	   fi; \
	 fi

############################################################################
#
# normal make targets
#

.PHONY: romfs
romfs:
	for dir in $(DIRS) ; do [ ! -d $$dir ] || $(MAKEARCH) -C $$dir romfs || exit 1 ; done
	-find $(ROMFSDIR)/. -name CVS | xargs -r rm -rf

.PHONY: image
image:
	[ -d $(IMAGEDIR) ] || mkdir $(IMAGEDIR)
	$(MAKEARCH) -C $(VENDDIR) image COPYIMAGE=$(COPYIMAGE)

.PHONY: netflash
netflash netflash_only:
	make -C prop/mstools CONFIG_PROP_MSTOOLS_NETFLASH_NETFLASH=y

.PHONY: release
release:
	make -C release release

%_fullrelease:
	make -C release $@
#
# fancy target that allows a vendor to have other top level
# make targets,  for example "make vendor_flash" will run the
# vendor_flash target in the vendors directory
#

vendor_%:
	$(MAKEARCH) -C $(VENDDIR) $@

.PHONY: linux
linux linux%_only:
	@if [ $(LINUX_VERSION_PRE) != linux-2.6 -a ! -f $(LINUXDIR)/.depend ] ; then \
               echo "ERROR: you need to do a 'make dep' first" ; \
               exit 1 ; \
       fi
	$(MAKEARCH_KERNEL) -C $(LINUXDIR) $(LINUXTARGET) || exit 1
	if [ -f $(LINUXDIR)/vmlinux ]; then \
		ln -f $(LINUXDIR)/vmlinux $(LINUXDIR)/linux ; \
	fi

.PHONY: linux_headers
linux_headers:
ifeq ($(CONFIG_DEFAULTS_KERNEL_2_0),y)
	$(MAKEARCH_KERNEL) -C $(LINUXDIR) dep
else
	$(MAKEARCH_KERNEL) -C $(LINUXDIR) prepare
endif

.PHONY: subdirs
subdirs: 
	for dir in $(DIRS) ; do [ ! -d $$dir ] || $(MAKEARCH_KERNEL) -C $$dir || exit 1 ; done

dep:
	@if [ ! -f $(LINUXDIR)/.config ] ; then \
		echo "ERROR: you need to do a 'make config' first" ; \
		exit 1 ; \
	fi
	$(MAKEARCH_KERNEL) -C $(LINUXDIR) dep

# This one removes all executables from the tree and forces their relinking
.PHONY: relink
relink:
	find user -name '*.gdb' | sed 's/^\(.*\)\.gdb/\1 \1.gdb/' | xargs rm -f
	find prop -name '*.gdb' | sed 's/^\(.*\)\.gdb/\1 \1.gdb/' | xargs rm -f
	find $(VENDDIR) -name '*.gdb' | sed 's/^\(.*\)\.gdb/\1 \1.gdb/' | xargs rm -f

clean: modules_clean
	for dir in $(LINUXDIR) $(DIRS); do [ ! -d $$dir ] || $(MAKEARCH) -C $$dir clean ; done
	rm -rf $(ROMFSDIR)/*
	rm -rf $(IMAGEDIR)/*
	rm -f config.tk
	rm -f $(LINUXDIR)/linux
	rm -rf $(LINUXDIR)/net/ipsec/alg/libaes $(LINUXDIR)/net/ipsec/alg/perlasm
	make -C $(VENDDIR) clean

real_clean mrproper: clean
	-$(MAKEARCH_KERNEL) -C $(LINUXDIR) mrproper
	-$(MAKEARCH) -C config clean
	-$(MAKEARCH) -C uClibc distclean
	-$(MAKEARCH) -C $(RELDIR) clean
	rm -rf romfs config.in config.arch config.tk images
	rm -f modules/config.tk
	rm -rf .config .config.old .oldconfig autoconf.h
	find . -type f | grep "~$$" | xargs echo $$1

distclean: mrproper
	-$(MAKEARCH_KERNEL) -C $(LINUXDIR) distclean
	-rm -f user/tinylogin/applet_source_list user/tinylogin/config.h

%_only:
	[ ! -d "$(@:_only=)" ] || $(MAKEARCH) -C $(@:_only=)

%_clean:
	[ ! -d "$(@:_clean=)" ] || $(MAKEARCH) -C $(@:_clean=) clean

config_error:
	@echo "*************************************************"
	@echo "You have not run make config."
	@echo "The build sequence for this source tree is:"
	@echo "1. 'make config' or 'make xconfig'"
	@echo "2. 'make dep'"
	@echo "3. 'make'"
	@echo "*************************************************"
	@exit 1

prune:
	$(MAKE) -C user prune

dist-prep:
	-find $(ROOTDIR) -name 'Makefile*.bin' | while read t; do \
		$(MAKEARCH) -C `dirname $$t` -f `basename $$t` $@; \
	 done

############################################################################
