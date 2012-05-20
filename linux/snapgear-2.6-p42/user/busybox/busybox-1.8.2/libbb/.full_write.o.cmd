cmd_libbb/full_write.o := sparc-linux-gcc -Wp,-MD,libbb/.full_write.o.d   -std=gnu99 -Iinclude -Ilibbb  -I/home/inouema/work/LEON/linux/snapgear-2.6-p42/user/busybox/busybox-1.8.2/libbb -include include/autoconf.h -D_GNU_SOURCE -DNDEBUG -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -D"BB_VER=KBUILD_STR(1.8.2)" -DBB_BT=AUTOCONF_TIMESTAMP -D_FORTIFY_SOURCE=2 -mcpu=v8 -msoft-float -idirafter /home/inouema/work/LEON/linux/snapgear-2.6-p42/linux-2.6.21.1/include -idirafter /home/inouema/work/LEON/linux/snapgear-2.6-p42   -Wall -Wshadow -Wwrite-strings -Wundef -Wstrict-prototypes  -Wmissing-prototypes -Wmissing-declarations -Os -fno-builtin-strlen -finline-limit=0 -fomit-frame-pointer -ffunction-sections -fdata-sections -fno-guess-branch-probability -funsigned-char -static-libgcc -falign-functions=1 -falign-jumps=1 -falign-labels=1 -falign-loops=1 -mv8 -msoft-float -Wdeclaration-after-statement     -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(full_write)"  -D"KBUILD_MODNAME=KBUILD_STR(full_write)" -c -o libbb/full_write.o libbb/full_write.c

deps_libbb/full_write.o := \
  libbb/full_write.c \
  include/libbb.h \
    $(wildcard include/config/selinux.h) \
    $(wildcard include/config/locale/support.h) \
    $(wildcard include/config/feature/shadowpasswds.h) \
    $(wildcard include/config/lfs.h) \
    $(wildcard include/config/feature/buffers/go/on/stack.h) \
    $(wildcard include/config/buffer.h) \
    $(wildcard include/config/ubuffer.h) \
    $(wildcard include/config/feature/buffers/go/in/bss.h) \
    $(wildcard include/config/feature/ipv6.h) \
    $(wildcard include/config/ture/ipv6.h) \
    $(wildcard include/config/feature/prefer/applets.h) \
    $(wildcard include/config/busybox/exec/path.h) \
    $(wildcard include/config/getopt/long.h) \
    $(wildcard include/config/feature/pidfile.h) \
    $(wildcard include/config/feature/syslog.h) \
    $(wildcard include/config/feature/individual.h) \
    $(wildcard include/config/route.h) \
    $(wildcard include/config/gunzip.h) \
    $(wildcard include/config/bunzip2.h) \
    $(wildcard include/config/ktop.h) \
    $(wildcard include/config/ioctl/hex2str/error.h) \
    $(wildcard include/config/feature/editing.h) \
    $(wildcard include/config/feature/editing/history.h) \
    $(wildcard include/config/ture/editing/savehistory.h) \
    $(wildcard include/config/feature/editing/savehistory.h) \
    $(wildcard include/config/feature/tab/completion.h) \
    $(wildcard include/config/feature/username/completion.h) \
    $(wildcard include/config/feature/editing/vi.h) \
    $(wildcard include/config/inux.h) \
    $(wildcard include/config/feature/topmem.h) \
    $(wildcard include/config/pgrep.h) \
    $(wildcard include/config/pkill.h) \
    $(wildcard include/config/feature/devfs.h) \
  include/platform.h \
    $(wildcard include/config/werror.h) \
    $(wildcard include/config///.h) \
    $(wildcard include/config//nommu.h) \
    $(wildcard include/config//mmu.h) \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/byteswap.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/byteswap.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/endian.h \
    $(wildcard include/config/.h) \
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
    $(wildcard include/config/d.h) \
    $(wildcard include/config/c.h) \
    $(wildcard include/config/ntrant.h) \
    $(wildcard include/config/i.h) \
    $(wildcard include/config/ern/inlines.h) \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/sys/cdefs.h \
    $(wildcard include/config/espaces.h) \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/gnu/stubs.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/gnu/stubs_withoutfloat.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/endian.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/arpa/inet.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/netinet/in.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/stdint.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/wchar.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/wordsize.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/types.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/include/stddef.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/typesizes.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/socket.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/include/limits.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/sys/types.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/time.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/sys/select.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/select.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/sigset.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/time.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/sys/sysmacros.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/pthreadtypes.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/sched.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/sockaddr.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/asm/socket.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/asm/sockios.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/in.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/include/stdbool.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/sys/mount.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/sys/ioctl.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/ioctls.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/asm/ioctls.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/asm/ioctl.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/linux/sockios.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/ioctl-types.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/sys/ttydefaults.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/ctype.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/xlocale.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/dirent.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/dirent.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/posix1_lim.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/local_lim.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/linux/limits.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/errno.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/errno.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/linux/errno.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/asm/errno.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/asm-generic/errno-base.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/fcntl.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/fcntl.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/sys/stat.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/stat.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/inttypes.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/mntent.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/stdio.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/paths.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/netdb.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/rpc/netdb.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/siginfo.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/netdb.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/setjmp.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/setjmp.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/signal.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/signum.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/sigaction.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/sigcontext.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/sigstack.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/sys/ucontext.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/sigthread.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/libio.h \
    $(wildcard include/config/a.h) \
    $(wildcard include/config/ar/t.h) \
    $(wildcard include/config//io/file.h) \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/_G_config.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/wchar.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/gconv.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/include/stdarg.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/stdio_lim.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/sys_errlist.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/stdlib.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/waitflags.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/waitstatus.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/alloca.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/string.h \
    $(wildcard include/config/ing/inlines.h) \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/sys/poll.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/poll.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/sys/mman.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/mman.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/sys/socket.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/sys/uio.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/uio.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/sys/statfs.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/statfs.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/sys/time.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/sys/wait.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/sys/resource.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/resource.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/termios.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/termios.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/unistd.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/posix_opt.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/environments.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/confname.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/getopt.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/utime.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/locale.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/bits/locale.h \
  include/pwd_.h \
    $(wildcard include/config/use/bb/pwd/grp.h) \
  include/grp_.h \
  include/shadow_.h \
    $(wildcard include/config/use/bb/shadow.h) \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/sys/param.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/linux/param.h \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/asm/param.h \
  include/xatonum.h \

libbb/full_write.o: $(deps_libbb/full_write.o)

$(deps_libbb/full_write.o):
