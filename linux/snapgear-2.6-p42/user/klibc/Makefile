SRCROOT = .

# kbuild compatibility
export srctree  := $(shell pwd)
export objtree  := $(shell pwd)
export KLIBCSRC := usr/klibc
export VERSION := $(shell cat $(KLIBCSRC)/version)
export KLIBCINC := usr/include
export KLIBCOBJ := usr/klibc
export KLIBCKERNELSRC := linux/
export KLIBCKERNELOBJ := linux/
include scripts/Kbuild.include

export CROSS_COMPILE=sparc-linux-
KLIBCROSS	= $(CROSS_COMPILE)
export KLIBCROSS
export CC	:= $(KLIBCROSS)gcc
export LD	:= $(KLIBCROSS)ld
export AR	:= $(KLIBCROSS)ar
export RANLIB	:= $(KLIBCROSS)ranlib
export STRIP	:= $(KLIBCROSS)strip
export NM	:= $(KLIBCROSS)nm
export OBJCOPY  := $(KLIBCROSS)objcopy
export OBJDUMP  := $(KLIBCROSS)objdump

NOSTDINC_FLAGS := -nostdlib -nostdinc -isystem $(shell $(CC) -print-file-name=include)

ARCH	          := sparc
export KLIBCARCH  ?= $(ARCH)
export KLIBCARCHDIR := $(shell echo $(KLIBCARCH) | sed -e s/s390x/s390/)

export HOSTCC     := gcc
export HOSTCFLAGS := -Wall -Wstrict-prototypes -O2 -fomit-frame-pointer
export PERL       := perl

KLIBCLEONFLAGS	  = 

ifeq ($(CONFIG_DEFAULTS_GAISLER_LEON2_MV8),y)
	KLIBCLEONFLAGS += -mcpu=v8
endif
ifneq ($(CONFIG_DEFAULTS_GAISLER_LEON2_FPU),y)
	KLIBCLEONFLAGS += -msoft-float
endif

export KLIBCLEONFLAGS

# Location for installation
export prefix      = /usr
export bindir      = $(prefix)/bin
export libdir      = $(prefix)/lib
export mandir      = $(prefix)/man
export INSTALLDIR  = $(prefix)/lib/klibc
export INSTALLROOT =

# Create a fake .config as present in the kernel tree
# But if it exists leave it alone
$(if $(wildcard $(objtree)/.config),,$(shell cp defconfig .config))

# Prefix Make commands with $(Q) to silence them
# Use quiet_cmd_xxx, cmd_xxx to create nice output
# use make V=1 to get verbose output

KBUILD_VERBOSE=1
quiet =
Q =

# If the user is running make -s (silent mode), suppress echoing of
# commands

ifneq ($(findstring s,$(MAKEFLAGS)),)
  quiet=silent_
endif

export quiet Q KBUILD_VERBOSE

ifdef CONFIG_USER_KLIBC_STATIC
kldir=static
klext=
else
kldir=shared
klext=.shared
endif

# Do not print "Entering directory ..."
MAKEFLAGS += --no-print-directory

# Shorthand to call Kbuild.klibc
klibc := -f $(srctree)/scripts/Kbuild.klibc obj

# Very first target
.PHONY: all mklinux klcc klibc 
all: mklinux klcc klibc 

mklinux: 
	ln -nsf $(ROOTDIR)/$(LINUXDIR) linux
	touch .config

.config: defconfig linux
	@echo "defconfig has changed, please remove or edit .config"
	@false

linux:
	@echo "The 'linux' symlink is missing; it should point to a kernel tree "
	@echo "configured for the $(KLIBCARCH) architecture."
	@false

rpmbuild = $(shell which rpmbuild 2>/dev/null || which rpm)

klibc.spec: klibc.spec.in $(KLIBCSRC)/version
	sed -e 's/@@VERSION@@/$(VERSION)/g' < $< > $@

# Build klcc - it is the first target
klcc: .config
	$(Q)$(MAKE) $(klibc)=klcc

klibc: .config
	$(Q)$(MAKE) $(klibc)=.

test: klibc
	$(Q)$(MAKE) $(klibc)=usr/klibc/tests


###
# allow one to say make dir/file.o
# Caveat: works only for .c files where we have a Kbuild file in same dir
%.o: %.c FORCE
	 $(Q)$(MAKE) $(klibc)=$(dir $<) $(dir $<)$(notdir $@)

%.s: %.c FORCE
	 $(Q)$(MAKE) $(klibc)=$(dir $<) $(dir $<)$(notdir $@)

%.i: %.c FORCE
	 $(Q)$(MAKE) $(klibc)=$(dir $<) $(dir $<)$(notdir $@)

FORCE: ;
###
# clean: remove generated files
# mrproper does a full cleaning including .config and linux symlink
FIND_IGNORE := \( -name .git \) -prune -o
quiet_cmd_rmfiles = $(if $(wildcard $(rm-files)),RM     $(wildcard $(rm-files)))
      cmd_rmfiles = rm -f $(rm-files)
clean:
	$(Q)$(MAKE) -f $(srctree)/scripts/Makefile.clean obj=.
	$(Q)find . $(FIND_IGNORE) \
		\( -name *.o -o -name *.a -o -name '.*.cmd' -o \
		   -name '.*.d' -o -name '.*.tmp' \) \
		-type f -print | xargs rm -f

rm-files := .config linux
distclean mrproper: clean
	 $(Q)find . $(FIND_IGNORE) \
		\( -name '*.orig' -o -name '*.rej' -o -name '*~' \
		-o -name '*.bak' -o -name '#*#' -o -name '.*.orig' \
		-o -name '.*.rej' -o -size 0 \
		-o -name '*%' -o -name '.*.cmd' -o -name 'core' \) \
		-type f -print | xargs rm -f
	$(call cmd,rmfiles)

install: all
	$(Q)$(MAKE) -f $(srctree)/scripts/Kbuild.install obj=.


.PHONY: romfs
romfs: 
	if [ "$(CONFIG_USER_KLIBC_STATIC)" != "y" ]; then \
		klso=`ls usr/klibc/klibc-*.so`; \
		$(ROMFSINST) -p 0755 $$klso /lib/`basename $$klso`; \
	fi

	#system inititalization tools
	$(ROMFSINST) -e CONFIG_USER_KLIBC_DASH usr/dash/sh$(klext)   /bin/sh
	$(ROMFSINST) -e CONFIG_USER_KLIBC_FSTYPE usr/kinit/fstype/$(kldir)/fstype /bin/fstype
	$(ROMFSINST) -e CONFIG_USER_KLIBC_GZIP  usr/gzip/gzip /bin/gzip
	$(ROMFSINST) -e CONFIG_USER_KLIBC_GZIP  usr/gzip/gunzip /bin/gunzip
	$(ROMFSINST) -e CONFIG_USER_KLIBC_GZIP  usr/gzip/zcat /bin/zcat
	$(ROMFSINST) -e CONFIG_USER_KLIBC_IPCONFIG usr/kinit/ipconfig/$(kldir)/ipconfig /bin/ipconfig
	$(ROMFSINST) -e CONFIG_USER_KLIBC_KINIT usr/kinit/kinit$(klext) /bin/kinit
	$(ROMFSINST) -e CONFIG_USER_KLIBC_NFSMOUNT usr/kinit/nfsmount/$(kldir)/nfsmount /bin/nfsmount
	$(ROMFSINST) -e CONFIG_USER_KLIBC_RESUME usr/kinit/resume/$(kldir)/resume /bin/resume
	$(ROMFSINST) -e CONFIG_USER_KLIBC_RUN_INIT usr/kinit/run-init/$(kldir)/run-init /bin/run-init

	#utilities
	$(ROMFSINST) -e CONFIG_USER_KLIBC_CAT usr/utils/$(kldir)/cat /bin/cat
	$(ROMFSINST) -e CONFIG_USER_KLIBC_CHROOT usr/utils/$(kldir)/chroot /bin/chroot
	$(ROMFSINST) -e CONFIG_USER_KLIBC_DD usr/utils/$(kldir)/dd /bin/dd
	$(ROMFSINST) -e CONFIG_USER_KLIBC_FALSE usr/utils/$(kldir)/false /bin/false
	$(ROMFSINST) -e CONFIG_USER_KLIBC_HALT usr/utils/$(kldir)/halt /bin/halt
	$(ROMFSINST) -e CONFIG_USER_KLIBC_INSMOD usr/utils/$(kldir)/insmod /bin/insmod
	$(ROMFSINST) -e CONFIG_USER_KLIBC_KILL usr/utils/$(kldir)/kill /bin/kill
	$(ROMFSINST) -e CONFIG_USER_KLIBC_LN usr/utils/$(kldir)/ln /bin/ln
	$(ROMFSINST) -e CONFIG_USER_KLIBC_MINIPS usr/utils/$(kldir)/minips /bin/minips
	$(ROMFSINST) -e CONFIG_USER_KLIBC_MKDIR usr/utils/$(kldir)/mkdir /bin/mkdir
	$(ROMFSINST) -e CONFIG_USER_KLIBC_MKFIFO usr/utils/$(kldir)/mkfifo /bin/mkfifo
	$(ROMFSINST) -e CONFIG_USER_KLIBC_MKNOD usr/utils/$(kldir)/mknod /bin/mknod
	$(ROMFSINST) -e CONFIG_USER_KLIBC_MOUNT usr/utils/$(kldir)/mount /bin/mount
	$(ROMFSINST) -e CONFIG_USER_KLIBC_NUKE usr/utils/$(kldir)/nuke /bin/nuke
	$(ROMFSINST) -e CONFIG_USER_KLIBC_PIVOT_ROOT usr/utils/$(kldir)/pivot_root /bin/pivot_root
	$(ROMFSINST) -e CONFIG_USER_KLIBC_POWEROFF usr/utils/$(kldir)/poweroff /bin/poweroff
	$(ROMFSINST) -e CONFIG_USER_KLIBC_READLINK usr/utils/$(kldir)/readlink /bin/readlink
	$(ROMFSINST) -e CONFIG_USER_KLIBC_REBOOT usr/utils/$(kldir)/reboot /bin/reboot
	$(ROMFSINST) -e CONFIG_USER_KLIBC_SLEEP usr/utils/$(kldir)/sleep /bin/sleep
	$(ROMFSINST) -e CONFIG_USER_KLIBC_TRUE usr/utils/$(kldir)/true /bin/true
	$(ROMFSINST) -e CONFIG_USER_KLIBC_UMOUNT usr/utils/$(kldir)/umount /bin/umount
	$(ROMFSINST) -e CONFIG_USER_KLIBC_UNAME usr/utils/$(kldir)/uname /bin/uname

# This does all the prep work needed to turn a freshly exported git repository
# into a release tarball tree
release: klibc.spec
	rm -f maketar.sh .config
