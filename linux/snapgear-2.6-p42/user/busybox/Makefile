
VER=1.8.2

ifeq ($(CONFIG_DEFAULTS_GAISLER_LEON2_MV8),y)
  ifeq ($(CONFIG_DEFAULTS_GAISLER_LEON2_FPU),y)
    ARCH2=sparc_v8fpu
  else
    ARCH2=sparc_v8soft
  endif
else
  ifeq ($(CONFIG_DEFAULTS_GAISLER_LEON2_FPU),y)
    ARCH2=sparc_v7fpu
  else
    ARCH2=sparc_v7soft
  endif
endif

ifeq  ($(CONFIG_DEFAULTS_LIBC_UCLIBC_FROM_COMPILER),y)
  ARCH3=$(ARCH2)-uc
else
  ARCH3=$(ARCH2)
endif

KBUILD_SRC=
CONFIG_MODULES=

all:
	@if [ ! -f busybox-$(VER)/.config ]; then \
	  make -C busybox-$(VER) ARCH=$(ARCH3) V=1 defconfig; \
	fi
	make -C busybox-$(VER) ARCH=$(ARCH3) V=1
	
# Configure busybox
xconfig:
	make -C busybox-$(VER) ARCH=$(ARCH3) xconfig

# Install busybox to romfs directory
romfs: all
	make -C busybox-$(VER) ARCH=$(ARCH3) CONFIG_PREFIX=$(ROMFSDIR) install

# Clean up busybox
clean:
	make -C busybox-$(VER) ARCH=$(ARCH3) mrproper
