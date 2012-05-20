cmd_libbb/appletlib.o := sparc-linux-gcc -Wp,-MD,libbb/.appletlib.o.d   -std=gnu99 -Iinclude -Ilibbb  -I/home/inouema/work/LEON/linux/snapgear-2.6-p42/user/busybox/busybox-1.8.2/libbb -include include/autoconf.h -D_GNU_SOURCE -DNDEBUG -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -D"BB_VER=KBUILD_STR(1.8.2)" -DBB_BT=AUTOCONF_TIMESTAMP -D_FORTIFY_SOURCE=2 -mcpu=v8 -msoft-float -idirafter /home/inouema/work/LEON/linux/snapgear-2.6-p42/linux-2.6.21.1/include -idirafter /home/inouema/work/LEON/linux/snapgear-2.6-p42   -Wall -Wshadow -Wwrite-strings -Wundef -Wstrict-prototypes  -Wmissing-prototypes -Wmissing-declarations -Os -fno-builtin-strlen -finline-limit=0 -fomit-frame-pointer -ffunction-sections -fdata-sections -fno-guess-branch-probability -funsigned-char -static-libgcc -falign-functions=1 -falign-jumps=1 -falign-labels=1 -falign-loops=1 -mv8 -msoft-float -Wdeclaration-after-statement     -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(appletlib)"  -D"KBUILD_MODNAME=KBUILD_STR(appletlib)" -c -o libbb/appletlib.o libbb/appletlib.c

deps_libbb/appletlib.o := \
  libbb/appletlib.c \
    $(wildcard include/config/show/usage.h) \
    $(wildcard include/config/feature/compress/usage.h) \
    $(wildcard include/config/feature/sh/standalone.h) \
    $(wildcard include/config/locale/support.h) \
    $(wildcard include/config/feature/individual.h) \
    $(wildcard include/config/ture/suid.h) \
    $(wildcard include/config/feature/suid/config.h) \
    $(wildcard include/config/feature/suid.h) \
    $(wildcard include/config/feature/suid/config/quiet.h) \
    $(wildcard include/config/quiet.h) \
    $(wildcard include/config/feature/installer.h) \
    $(wildcard include/config/feature/autowidth.h) \
    $(wildcard include/config/build/libbusybox.h) \
  /opt/sparc-linux-3.4.4/lib/gcc/sparc-linux/3.4.4/../../../../sparc-linux/sys-include/assert.h \
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
  include/busybox.h \
    $(wildcard include/config/feature/prefer/applets.h) \
    $(wildcard include/config/feature/shared/busybox.h) \
  include/libbb.h \
    $(wildcard include/config/selinux.h) \
    $(wildcard include/config/feature/shadowpasswds.h) \
    $(wildcard include/config/lfs.h) \
    $(wildcard include/config/feature/buffers/go/on/stack.h) \
    $(wildcard include/config/buffer.h) \
    $(wildcard include/config/ubuffer.h) \
    $(wildcard include/config/feature/buffers/go/in/bss.h) \
    $(wildcard include/config/feature/ipv6.h) \
    $(wildcard include/config/ture/ipv6.h) \
    $(wildcard include/config/busybox/exec/path.h) \
    $(wildcard include/config/getopt/long.h) \
    $(wildcard include/config/feature/pidfile.h) \
    $(wildcard include/config/feature/syslog.h) \
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
  include/applets.h \
    $(wildcard include/config/feature/verbose/usage.h) \
    $(wildcard include/config/ture/installer.h) \
    $(wildcard include/config/ture/prefer/applets.h) \
    $(wildcard include/config/install/no/usr.h) \
    $(wildcard include/config/t.h) \
    $(wildcard include/config/group.h) \
    $(wildcard include/config/user.h) \
    $(wildcard include/config/timex.h) \
    $(wildcard include/config/applet.h) \
    $(wildcard include/config/ing.h) \
    $(wildcard include/config/ename.h) \
    $(wildcard include/config/onfig.h) \
    $(wildcard include/config/h.h) \
    $(wildcard include/config/zip2.h) \
    $(wildcard include/config/p2.h) \
    $(wildcard include/config/v.h) \
    $(wildcard include/config/ttr.h) \
    $(wildcard include/config/on.h) \
    $(wildcard include/config/rp.h) \
    $(wildcard include/config/od.h) \
    $(wildcard include/config/wn.h) \
    $(wildcard include/config/asswd.h) \
    $(wildcard include/config/st.h) \
    $(wildcard include/config/oot.h) \
    $(wildcard include/config/um.h) \
    $(wildcard include/config/ar.h) \
    $(wildcard include/config/m.h) \
    $(wildcard include/config/applet/noexec.h) \
    $(wildcard include/config/o.h) \
    $(wildcard include/config/nd.h) \
    $(wildcard include/config/ntab.h) \
    $(wildcard include/config/ptpw.h) \
    $(wildcard include/config/yhack.h) \
    $(wildcard include/config/e.h) \
    $(wildcard include/config/llocvt.h) \
    $(wildcard include/config/fsd.h) \
    $(wildcard include/config//dhcprelay.h) \
    $(wildcard include/config/f.h) \
    $(wildcard include/config/name.h) \
    $(wildcard include/config/sg.h) \
    $(wildcard include/config/2unix.h) \
    $(wildcard include/config/g.h) \
    $(wildcard include/config/g/deb.h) \
    $(wildcard include/config/pkmap.h) \
    $(wildcard include/config//dumpleases.h) \
    $(wildcard include/config/sck.h) \
    $(wildcard include/config/abel.h) \
    $(wildcard include/config/ture/grep/egrep/alias.h) \
    $(wildcard include/config/ct.h) \
    $(wildcard include/config/dir.h) \
    $(wildcard include/config/uidgid.h) \
    $(wildcard include/config/er/wake.h) \
    $(wildcard include/config/and.h) \
    $(wildcard include/config/r.h) \
    $(wildcard include/config/eidentd.h) \
    $(wildcard include/config/se.h) \
    $(wildcard include/config/et.h) \
    $(wildcard include/config/lush.h) \
    $(wildcard include/config/ormat.h) \
    $(wildcard include/config/sk.h) \
    $(wildcard include/config/ture/grep/fgrep/alias.h) \
    $(wildcard include/config/dfs.h) \
    $(wildcard include/config/eramdisk.h) \
    $(wildcard include/config/k.h) \
    $(wildcard include/config/k/minix.h) \
    $(wildcard include/config/get.h) \
    $(wildcard include/config/put.h) \
    $(wildcard include/config/er.h) \
    $(wildcard include/config/enforce.h) \
    $(wildcard include/config/opt.h) \
    $(wildcard include/config/sebool.h) \
    $(wildcard include/config/ty.h) \
    $(wildcard include/config/p.h) \
    $(wildcard include/config/zip.h) \
    $(wildcard include/config/arm.h) \
    $(wildcard include/config/dump.h) \
    $(wildcard include/config/tid.h) \
    $(wildcard include/config/tname.h) \
    $(wildcard include/config/pd.h) \
    $(wildcard include/config/lock.h) \
    $(wildcard include/config/pdown.h) \
    $(wildcard include/config/td.h) \
    $(wildcard include/config/mod.h) \
    $(wildcard include/config/tall.h) \
    $(wildcard include/config/feature/ip/address.h) \
    $(wildcard include/config/feature/ip/route.h) \
    $(wildcard include/config/feature/ip/link.h) \
    $(wildcard include/config/feature/ip/tunnel.h) \
    $(wildcard include/config/feature/ip/rule.h) \
    $(wildcard include/config/ddr.h) \
    $(wildcard include/config/alc.h) \
    $(wildcard include/config/rm.h) \
    $(wildcard include/config/s.h) \
    $(wildcard include/config/ink.h) \
    $(wildcard include/config/oute.h) \
    $(wildcard include/config/ule.h) \
    $(wildcard include/config/unnel.h) \
    $(wildcard include/config//mode.h) \
    $(wildcard include/config/l.h) \
    $(wildcard include/config/lall.h) \
    $(wildcard include/config/lall5.h) \
    $(wildcard include/config/gd.h) \
    $(wildcard include/config/gth.h) \
    $(wildcard include/config/arch.h) \
    $(wildcard include/config/ture/initrd.h) \
    $(wildcard include/config/d/policy.h) \
    $(wildcard include/config/dfont.h) \
    $(wildcard include/config/dkmap.h) \
    $(wildcard include/config/ger.h) \
    $(wildcard include/config/in.h) \
    $(wildcard include/config/read.h) \
    $(wildcard include/config/etup.h) \
    $(wildcard include/config/zma.h) \
    $(wildcard include/config/edevs.h) \
    $(wildcard include/config/chpathcon.h) \
    $(wildcard include/config/sum.h) \
    $(wildcard include/config/rocom.h) \
    $(wildcard include/config/ir.h) \
    $(wildcard include/config/2fs.h) \
    $(wildcard include/config/ifo.h) \
    $(wildcard include/config/s/minix.h) \
    $(wildcard include/config/wap.h) \
    $(wildcard include/config/emp.h) \
    $(wildcard include/config/probe.h) \
    $(wildcard include/config/nt.h) \
    $(wildcard include/config/sktop.h) \
    $(wildcard include/config/ntpoint.h) \
    $(wildcard include/config/eif.h) \
    $(wildcard include/config/stat.h) \
    $(wildcard include/config/ter.h) \
    $(wildcard include/config/up.h) \
    $(wildcard include/config/ookup.h) \
    $(wildcard include/config/nvt.h) \
    $(wildcard include/config/swd.h) \
    $(wildcard include/config/ch.h) \
    $(wildcard include/config/ep.h) \
    $(wildcard include/config/of.h) \
    $(wildcard include/config/g6.h) \
    $(wildcard include/config/e/progress.h) \
    $(wildcard include/config/ot/root.h) \
    $(wildcard include/config/ll.h) \
    $(wildcard include/config/ntenv.h) \
    $(wildcard include/config/ntf.h) \
    $(wildcard include/config/an.h) \
    $(wildcard include/config/dautorun.h) \
    $(wildcard include/config/te.h) \
    $(wildcard include/config/dahead.h) \
    $(wildcard include/config/dlink.h) \
    $(wildcard include/config/dprofile.h) \
    $(wildcard include/config/lpath.h) \
    $(wildcard include/config/ice.h) \
    $(wildcard include/config/ize.h) \
    $(wildcard include/config/torecon.h) \
    $(wildcard include/config/applet/nofork.h) \
    $(wildcard include/config/2cpio.h) \
    $(wildcard include/config//parts.h) \
    $(wildcard include/config/con.h) \
    $(wildcard include/config/level.h) \
    $(wildcard include/config/sv.h) \
    $(wildcard include/config/svdir.h) \
    $(wildcard include/config/inuxenabled.h) \
    $(wildcard include/config/console.h) \
    $(wildcard include/config/files.h) \
    $(wildcard include/config/keycodes.h) \
    $(wildcard include/config/logcons.h) \
    $(wildcard include/config/sid.h) \
    $(wildcard include/config/ture/sh/is/ash.h) \
    $(wildcard include/config/ture/sh/is/hush.h) \
    $(wildcard include/config/ture/sh/is/lash.h) \
    $(wildcard include/config/ture/sh/is/msh.h) \
    $(wildcard include/config/1sum.h) \
    $(wildcard include/config/ttach.h) \
    $(wildcard include/config/tlimit.h) \
    $(wildcard include/config/it.h) \
    $(wildcard include/config/rt/stop/daemon.h) \
    $(wildcard include/config/ings.h) \
    $(wildcard include/config/y.h) \
    $(wildcard include/config/ogin.h) \
    $(wildcard include/config/ogd.h) \
    $(wildcard include/config/ponoff.h) \
    $(wildcard include/config/tch/root.h) \
    $(wildcard include/config/sysctl.h) \
    $(wildcard include/config/logd.h) \
    $(wildcard include/config/kset.h) \
    $(wildcard include/config/svd.h) \
    $(wildcard include/config/net.h) \
    $(wildcard include/config/netd.h) \
    $(wildcard include/config/feature/tftp/get.h) \
    $(wildcard include/config/feature/tftp/put.h) \
    $(wildcard include/config/ceroute.h) \
    $(wildcard include/config/size.h) \
    $(wildcard include/config/e2fs.h) \
    $(wildcard include/config//udhcpc.h) \
    $(wildcard include/config//udhcpd.h) \
    $(wildcard include/config/unt.h) \
    $(wildcard include/config/me.h) \
    $(wildcard include/config/ompress.h) \
    $(wildcard include/config/xpand.h) \
    $(wildcard include/config/q.h) \
    $(wildcard include/config/x2dos.h) \
    $(wildcard include/config/ip.h) \
    $(wildcard include/config/ime.h) \
    $(wildcard include/config/eep.h) \
    $(wildcard include/config/ecode.h) \
    $(wildcard include/config/ncode.h) \
    $(wildcard include/config/nfig.h) \
    $(wildcard include/config/ck.h) \
    $(wildcard include/config/chdog.h) \
    $(wildcard include/config/ami.h) \
    $(wildcard include/config/gs.h) \
  include/usage_compressed.h \
  include/unarchive.h \

libbb/appletlib.o: $(deps_libbb/appletlib.o)

$(deps_libbb/appletlib.o):
