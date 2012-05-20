cmd_libbb/makedev.o := sparc-linux-gcc -Wp,-MD,libbb/.makedev.o.d   -std=gnu99 -Iinclude -Ilibbb  -I/home/inouema/work/LEON/linux/snapgear-2.6-p42/user/busybox/busybox-1.8.2/libbb -include include/autoconf.h -D_GNU_SOURCE -DNDEBUG -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -D"BB_VER=KBUILD_STR(1.8.2)" -DBB_BT=AUTOCONF_TIMESTAMP -D_FORTIFY_SOURCE=2 -mcpu=v8 -msoft-float -idirafter /home/inouema/work/LEON/linux/snapgear-2.6-p42/linux-2.6.21.1/include -idirafter /home/inouema/work/LEON/linux/snapgear-2.6-p42   -Wall -Wshadow -Wwrite-strings -Wundef -Wstrict-prototypes  -Wmissing-prototypes -Wmissing-declarations -Os -fno-builtin-strlen -finline-limit=0 -fomit-frame-pointer -ffunction-sections -fdata-sections -fno-guess-branch-probability -funsigned-char -static-libgcc -falign-functions=1 -falign-jumps=1 -falign-labels=1 -falign-loops=1 -mv8 -msoft-float -Wdeclaration-after-statement     -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(makedev)"  -D"KBUILD_MODNAME=KBUILD_STR(makedev)" -c -o libbb/makedev.o libbb/makedev.c

deps_libbb/makedev.o := \
  libbb/makedev.c \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/features.h \
    $(wildcard include/config/c99.h) \
    $(wildcard include/config/ix.h) \
    $(wildcard include/config/ix2.h) \
    $(wildcard include/config/ix199309.h) \
    $(wildcard include/config/ix199506.h) \
    $(wildcard include/config/en.h) \
    $(wildcard include/config/en/extended.h) \
    $(wildcard include/config/x98.h) \
    $(wildcard include/config/en2k.h) \
    $(wildcard include/config/gefile.h) \
    $(wildcard include/config/gefile64.h) \
    $(wildcard include/config/e/offset64.h) \
    $(wildcard include/config/.h) \
    $(wildcard include/config/d.h) \
    $(wildcard include/config/c.h) \
    $(wildcard include/config/ntrant.h) \
    $(wildcard include/config/i.h) \
    $(wildcard include/config/ern/inlines.h) \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/sys/cdefs.h \
    $(wildcard include/config/espaces.h) \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/gnu/stubs.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/gnu/stubs_withoutfloat.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/sys/sysmacros.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/wordsize.h \

libbb/makedev.o: $(deps_libbb/makedev.o)

$(deps_libbb/makedev.o):
