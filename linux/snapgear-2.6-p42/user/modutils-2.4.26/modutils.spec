Summary: Module utilities
Name: modutils
Version: 2.4.26
Release: 1
Copyright: GPL
Group: Utilities/System
Source: modutils-%{version}.tar.gz
ExclusiveOS: Linux
BuildRoot: /var/tmp/modutils-root

%description
The Linux kernel allows new kernel pieces to be loaded and old ones to
be unloaded while the kernel continues to run. These loadable pieces
are called modules, and can include device drivers and filesystems among
other things. This package includes program to load and unload programs
both automatically and manually.

This set does not include 'request-route' script nor kerneld (still
present in sources).  It is compiled without support for 2.0 and early
2.1 kernels, see INSTALL if you want modutils to run on old kernels.
It includes insmod.static for mkinitrd.

%prep
%setup
%build
CFLAGS="$RPM_OPT_FLAGS" ./configure --enable-insmod-static --mandir=%{_mandir}
make dep all

%install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/sbin
mkdir -p $RPM_BUILD_ROOT/%{mandir_}/man{1,2,5,8}
make install prefix=$RPM_BUILD_ROOT/usr exec_prefix=$RPM_BUILD_ROOT \
	     mandir=$RPM_BUILD_ROOT/%{_mandir}
# kerneld is not compiled by default, it is obsolete for kernel >= 2.1.91.
# (cd kerneld;
# make install-scripts prefix=$RPM_BUILD_ROOT/usr exec_prefix=$RPM_BUILD_ROOT
# )
# security hole, works poorly anyway
rm -f $RPM_BUILD_ROOT/sbin/request-route

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%attr(755,root,root)/sbin/depmod
%attr(755,root,root)/sbin/genksyms
%attr(755,root,root)/sbin/insmod
%attr(755,root,root)/sbin/insmod.static
#%attr(755,root,root)/sbin/kerneld
%attr(755,root,root)/sbin/ksyms
%attr(755,root,root)/sbin/lsmod
%attr(755,root,root)/sbin/modinfo
%attr(755,root,root)/sbin/modprobe
%attr(755,root,root)/sbin/rmmod
%attr(755,root,root)/sbin/kallsyms
%attr(755,root,root)/sbin/insmod_ksymoops_clean
%attr(755,root,root)/sbin/kernelversion
%attr(644,root,root)%{_mandir}/man1/kernelversion.1*
%attr(644,root,root)%{_mandir}/man2/create_module.2*
%attr(644,root,root)%{_mandir}/man2/delete_module.2*
%attr(644,root,root)%{_mandir}/man2/get_kernel_syms.2*
%attr(644,root,root)%{_mandir}/man2/init_module.2*
%attr(644,root,root)%{_mandir}/man2/query_module.2*
%attr(644,root,root)%{_mandir}/man5/modules.conf.5*
%attr(644,root,root)%{_mandir}/man8/depmod.8*
%attr(644,root,root)%{_mandir}/man8/genksyms.8*
%attr(644,root,root)%{_mandir}/man8/insmod.8*
#%attr(644,root,root)%{_mandir}/man8/kdstat.8*
#%attr(644,root,root)%{_mandir}/man8/kerneld.8*
%attr(644,root,root)%{_mandir}/man8/ksyms.8*
%attr(644,root,root)%{_mandir}/man8/lsmod.8*
%attr(644,root,root)%{_mandir}/man8/modinfo.8*
%attr(644,root,root)%{_mandir}/man8/modprobe.8*
%attr(644,root,root)%{_mandir}/man8/rmmod.8*
%attr(644,root,root)%{_mandir}/man8/kallsyms.8*
%attr(-,root,root) %doc COPYING README CREDITS TODO ChangeLog NEWS example/kallsyms.c include/kallsyms.h
