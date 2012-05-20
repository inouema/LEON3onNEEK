# Makefile.in generated automatically by automake 1.4-p6 from Makefile.am

# Copyright (C) 1994, 1995-8, 1999, 2001 Free Software Foundation, Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.


SHELL = /bin/sh

srcdir = .
top_srcdir = .

prefix = /usr/local
exec_prefix = ${prefix}

bindir = ${exec_prefix}/bin
sbindir = ${exec_prefix}/sbin
libexecdir = ${exec_prefix}/libexec
datadir = ${prefix}/share
sysconfdir = ${prefix}/etc
sharedstatedir = ${prefix}/com
localstatedir = ${prefix}/var
libdir = ${exec_prefix}/lib
infodir = ${prefix}/info
includedir = ${prefix}/include
oldincludedir = /usr/include

DESTDIR =

pkgdatadir = $(datadir)/module-init-tools
pkglibdir = $(libdir)/module-init-tools
pkgincludedir = $(includedir)/module-init-tools

top_builddir = .

ACLOCAL = ${SHELL} /home/eiselekd/tmp3/module-init-tools-3.1-pre6/missing --run aclocal-1.6
AUTOCONF = ${SHELL} /home/eiselekd/tmp3/module-init-tools-3.1-pre6/missing --run autoconf
AUTOMAKE = ${SHELL} /home/eiselekd/tmp3/module-init-tools-3.1-pre6/missing --run automake-1.6
AUTOHEADER = ${SHELL} /home/eiselekd/tmp3/module-init-tools-3.1-pre6/missing --run autoheader
INSTALL_PROGRAM = ${INSTALL} $(AM_INSTALL_PROGRAM_FLAGS)
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_SCRIPT = ${INSTALL}
transform = s,x,x,

NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
build_alias = 
build_triplet = i686-pc-linux-gnu
host_alias = sparc-linux
host_triplet = sparc-unknown-linux-gnu
target_alias = 
target_triplet = sparc-unknown-linux-gnu
AMDEPBACKSLASH = \
AMTAR = ${SHELL} /home/eiselekd/tmp3/module-init-tools-3.1-pre6/missing --run tar
AWK = gawk
CC = sparc-linux-gcc
DEPDIR = .deps
INSTALL_STRIP_PROGRAM = ${SHELL} $(install_sh) -c -s
LDADD =  
MAKEINFO = ${SHELL} /home/eiselekd/tmp3/module-init-tools-3.1-pre6/missing --run makeinfo
MODULE_DIR = 
PACKAGE = module-init-tools
STRIP = sparc-linux-strip
VERSION = 3.1-pre6
am__include = include
am__quote = 
install_sh = /home/eiselekd/tmp3/module-init-tools-3.1-pre6/install-sh

insmod_SOURCES = insmod.c testing.h
lsmod_SOURCES = lsmod.c testing.h
modprobe_SOURCES = modprobe.c zlibsupport.c testing.h zlibsupport.h
rmmod_SOURCES = rmmod.c testing.h
depmod_SOURCES = depmod.c moduleops.c tables.c zlibsupport.c depmod.h moduleops.h tables.h list.h testing.h  zlibsupport.h
modinfo_SOURCES = modinfo.c zlibsupport.c testing.h zlibsupport.h

insmod_static_SOURCES = insmod.c
insmod_static_LDFLAGS = -static $(LDFLAGS)
# We don't want the $(zlib_flags) here: that makes a dynamic executable
insmod_static_LDADD = 

EXTRA_insmod_SOURCES = backwards_compat.c
EXTRA_lsmod_SOURCES = backwards_compat.c
EXTRA_modprobe_SOURCES = backwards_compat.c
EXTRA_rmmod_SOURCES = backwards_compat.c
EXTRA_insmod_static_SOURCES = backwards_compat.c
EXTRA_depmod_SOURCES = moduleops_core.c
EXTRA_modinfo_SOURCES = backwards_compat.c

MAN5 = modprobe.conf.5 modules.dep.5
MAN8 = depmod.8 insmod.8 lsmod.8 rmmod.8 modprobe.8 modinfo.8
SGML = $(addprefix doc/,  $(MAN5:%.5=%.sgml) $(MAN8:%.8=%.sgml))
man_MANS = $(MAN5) $(MAN8)
mandir = $(shell if [ `echo $(prefix)/ | tr -s /` = / ]; then echo /usr/share/man; else echo $(prefix)/man; fi)

EXTRA_DIST = generate-modprobe.conf modprobe.devfs FAQ stress_modules.sh install-with-care $(SGML) $(man_MANS)

sbin_PROGRAMS = insmod modprobe rmmod depmod modinfo insmod.static
bin_PROGRAMS = lsmod
sbin_SCRIPTS = generate-modprobe.conf
INSTALL = $(SHELL) $(top_srcdir)/install-with-care

TESTS = tests/runtests

DIST_DIR := /home/rusty/devel/kernel/www/modules/

MAINTAINERCLEANFILES := $(man_MANS)

# According to Warren Togami, RH has docbook2man in the docbook-utils rpm.
DOCBOOKTOMAN := $(shell if command -v docbook-to-man >/dev/null 2>&1; then echo docbook-to-man; else echo docbook2man; fi)
ACLOCAL_M4 = $(top_srcdir)/aclocal.m4
mkinstalldirs = $(SHELL) $(top_srcdir)/mkinstalldirs
CONFIG_CLEAN_FILES = 
PROGRAMS =  $(bin_PROGRAMS) $(sbin_PROGRAMS)


DEFS = -DPACKAGE_NAME=\"\" -DPACKAGE_TARNAME=\"\" -DPACKAGE_VERSION=\"\" -DPACKAGE_STRING=\"\" -DPACKAGE_BUGREPORT=\"\" -DPACKAGE=\"module-init-tools\" -DVERSION=\"3.1-pre6\"  -I. -I$(srcdir) 
CPPFLAGS = 
#LDFLAGS = 
LIBS = 
lsmod_OBJECTS =  lsmod.o
lsmod_LDADD = $(LDADD)
lsmod_DEPENDENCIES = 
lsmod_LDFLAGS = $(LDFLAGS)
insmod_OBJECTS =  insmod.o
insmod_LDADD = $(LDADD)
insmod_DEPENDENCIES = 
insmod_LDFLAGS = $(LDFLAGS)
modprobe_OBJECTS =  modprobe.o zlibsupport.o
modprobe_LDADD = $(LDADD)
modprobe_DEPENDENCIES = 
modprobe_LDFLAGS = $(LDFLAGS)
rmmod_OBJECTS =  rmmod.o
rmmod_LDADD = $(LDADD)
rmmod_DEPENDENCIES = 
rmmod_LDFLAGS = $(LDFLAGS)
depmod_OBJECTS =  depmod.o moduleops.o tables.o zlibsupport.o
depmod_LDADD = $(LDADD)
depmod_DEPENDENCIES = 
depmod_LDFLAGS = $(LDFLAGS)
modinfo_OBJECTS =  modinfo.o zlibsupport.o
modinfo_LDADD = $(LDADD)
modinfo_DEPENDENCIES = 
modinfo_LDFLAGS = $(LDFLAGS)
insmod_static_OBJECTS =  insmod.o 
insmod_static_DEPENDENCIES = 
SCRIPTS =  $(sbin_SCRIPTS)

#CFLAGS = -g -O2 -Wunused -Wall
COMPILE = $(CC) $(DEFS) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
CCLD = $(CC)
LINK = $(CCLD) $(AM_CFLAGS) $(CFLAGS)  -o $@
man5dir = $(mandir)/man5
man8dir = $(mandir)/man8
MANS = $(man_MANS)

NROFF = nroff
DIST_COMMON =  README AUTHORS COPYING ChangeLog INSTALL Makefile.am \
Makefile.in NEWS TODO aclocal.m4 config.guess config.sub configure \
configure.in install-sh missing mkinstalldirs


DISTFILES = $(DIST_COMMON) $(SOURCES) $(HEADERS) $(TEXINFOS) $(EXTRA_DIST)

TAR = tar
GZIP_ENV = --best
DEP_FILES =  .deps/backwards_compat.P .deps/depmod.P .deps/insmod.P \
.deps/lsmod.P .deps/modinfo.P .deps/modprobe.P .deps/moduleops.P \
.deps/moduleops_core.P .deps/rmmod.P .deps/tables.P .deps/zlibsupport.P
SOURCES = $(lsmod_SOURCES) $(EXTRA_lsmod_SOURCES) $(insmod_SOURCES) $(EXTRA_insmod_SOURCES) $(modprobe_SOURCES) $(EXTRA_modprobe_SOURCES) $(rmmod_SOURCES) $(EXTRA_rmmod_SOURCES) $(depmod_SOURCES) $(EXTRA_depmod_SOURCES) $(modinfo_SOURCES) $(EXTRA_modinfo_SOURCES) $(insmod_static_SOURCES) $(EXTRA_insmod_static_SOURCES)
OBJECTS = $(lsmod_OBJECTS) $(insmod_OBJECTS) $(modprobe_OBJECTS) $(rmmod_OBJECTS) $(depmod_OBJECTS) $(modinfo_OBJECTS) $(insmod_static_OBJECTS)

all: all-redirect
.SUFFIXES:
.SUFFIXES: .S .c .o .s
$(srcdir)/Makefile.in: Makefile.am $(top_srcdir)/configure.in $(ACLOCAL_M4) 
	cd $(top_srcdir) && $(AUTOMAKE) --gnu Makefile

Makefile: $(srcdir)/Makefile.in  $(top_builddir)/config.status $(BUILT_SOURCES)
	cd $(top_builddir) \
	  && CONFIG_FILES=$@ CONFIG_HEADERS= $(SHELL) ./config.status

$(ACLOCAL_M4):  configure.in 
	cd $(srcdir) && $(ACLOCAL)

config.status: $(srcdir)/configure $(CONFIG_STATUS_DEPENDENCIES)
	$(SHELL) ./config.status --recheck
$(srcdir)/configure: $(srcdir)/configure.in $(ACLOCAL_M4) $(CONFIGURE_DEPENDENCIES)
	cd $(srcdir) && $(AUTOCONF)

mostlyclean-binPROGRAMS:

clean-binPROGRAMS:
	-test -z "$(bin_PROGRAMS)" || rm -f $(bin_PROGRAMS)

distclean-binPROGRAMS:

maintainer-clean-binPROGRAMS:

install-binPROGRAMS: $(bin_PROGRAMS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(bindir)
	@list='$(bin_PROGRAMS)'; for p in $$list; do \
	  if test -f $$p; then \
	    echo "  $(INSTALL_PROGRAM) $$p $(DESTDIR)$(bindir)/`echo $$p|sed 's/$(EXEEXT)$$//'|sed '$(transform)'|sed 's/$$/$(EXEEXT)/'`"; \
	     $(INSTALL_PROGRAM) $$p $(DESTDIR)$(bindir)/`echo $$p|sed 's/$(EXEEXT)$$//'|sed '$(transform)'|sed 's/$$/$(EXEEXT)/'`; \
	  else :; fi; \
	done

uninstall-binPROGRAMS:
	@$(NORMAL_UNINSTALL)
	list='$(bin_PROGRAMS)'; for p in $$list; do \
	  rm -f $(DESTDIR)$(bindir)/`echo $$p|sed 's/$(EXEEXT)$$//'|sed '$(transform)'|sed 's/$$/$(EXEEXT)/'`; \
	done

mostlyclean-sbinPROGRAMS:

clean-sbinPROGRAMS:
	-test -z "$(sbin_PROGRAMS)" || rm -f $(sbin_PROGRAMS)

distclean-sbinPROGRAMS:

maintainer-clean-sbinPROGRAMS:

install-sbinPROGRAMS: $(sbin_PROGRAMS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(sbindir)
	@list='$(sbin_PROGRAMS)'; for p in $$list; do \
	  if test -f $$p; then \
	    echo "  $(INSTALL_PROGRAM) $$p $(DESTDIR)$(sbindir)/`echo $$p|sed 's/$(EXEEXT)$$//'|sed '$(transform)'|sed 's/$$/$(EXEEXT)/'`"; \
	     $(INSTALL_PROGRAM) $$p $(DESTDIR)$(sbindir)/`echo $$p|sed 's/$(EXEEXT)$$//'|sed '$(transform)'|sed 's/$$/$(EXEEXT)/'`; \
	  else :; fi; \
	done

uninstall-sbinPROGRAMS:
	@$(NORMAL_UNINSTALL)
	list='$(sbin_PROGRAMS)'; for p in $$list; do \
	  rm -f $(DESTDIR)$(sbindir)/`echo $$p|sed 's/$(EXEEXT)$$//'|sed '$(transform)'|sed 's/$$/$(EXEEXT)/'`; \
	done

.s.o:
	$(COMPILE) -c $<

.S.o:
	$(COMPILE) -c $<

mostlyclean-compile:
	-rm -f *.o core *.core

clean-compile:

distclean-compile:
	-rm -f *.tab.c

maintainer-clean-compile:

lsmod: $(lsmod_OBJECTS) $(lsmod_DEPENDENCIES)
	@rm -f lsmod
	$(LINK) $(lsmod_OBJECTS)  $(lsmod_LDADD) $(LIBS) $(lsmod_LDFLAGS)

insmod: $(insmod_OBJECTS) $(insmod_DEPENDENCIES)
	@rm -f insmod
	$(LINK) $(insmod_OBJECTS) $(insmod_LDADD) $(LIBS) $(insmod_LDFLAGS) 

modprobe: $(modprobe_OBJECTS) $(modprobe_DEPENDENCIES)
	@rm -f modprobe
	$(LINK) $(modprobe_OBJECTS) $(modprobe_LDADD) $(LIBS) $(modprobe_LDFLAGS) 

rmmod: $(rmmod_OBJECTS) $(rmmod_DEPENDENCIES)
	@rm -f rmmod
	$(LINK) $(rmmod_OBJECTS) $(rmmod_LDADD) $(LIBS) $(rmmod_LDFLAGS) 

depmod: $(depmod_OBJECTS) $(depmod_DEPENDENCIES)
	@rm -f depmod
	$(LINK) $(depmod_OBJECTS) $(depmod_LDADD) $(LIBS) $(depmod_LDFLAGS) 

modinfo: $(modinfo_OBJECTS) $(modinfo_DEPENDENCIES)
	@rm -f modinfo
	$(LINK) $(modinfo_OBJECTS) $(modinfo_LDADD) $(LIBS) $(modinfo_LDFLAGS) 

insmod.static: $(insmod_static_OBJECTS) $(insmod_static_DEPENDENCIES)
	@rm -f insmod.static
	$(LINK)  $(insmod_static_OBJECTS) $(insmod_static_LDADD) $(LIBS) $(insmod_static_LDFLAGS)

install-sbinSCRIPTS: $(sbin_SCRIPTS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(sbindir)
	@list='$(sbin_SCRIPTS)'; for p in $$list; do \
	  if test -f $$p; then \
	    echo " $(INSTALL_SCRIPT) $$p $(DESTDIR)$(sbindir)/`echo $$p|sed '$(transform)'`"; \
	    $(INSTALL_SCRIPT) $$p $(DESTDIR)$(sbindir)/`echo $$p|sed '$(transform)'`; \
	  else if test -f $(srcdir)/$$p; then \
	    echo " $(INSTALL_SCRIPT) $(srcdir)/$$p $(DESTDIR)$(sbindir)/`echo $$p|sed '$(transform)'`"; \
	    $(INSTALL_SCRIPT) $(srcdir)/$$p $(DESTDIR)$(sbindir)/`echo $$p|sed '$(transform)'`; \
	  else :; fi; fi; \
	done

uninstall-sbinSCRIPTS:
	@$(NORMAL_UNINSTALL)
	list='$(sbin_SCRIPTS)'; for p in $$list; do \
	  rm -f $(DESTDIR)$(sbindir)/`echo $$p|sed '$(transform)'`; \
	done

install-man5:
	$(mkinstalldirs) $(DESTDIR)$(man5dir)
	@list='$(man5_MANS)'; \
	l2='$(man_MANS)'; for i in $$l2; do \
	  case "$$i" in \
	    *.5*) list="$$list $$i" ;; \
	  esac; \
	done; \
	for i in $$list; do \
	  if test -f $(srcdir)/$$i; then file=$(srcdir)/$$i; \
	  else file=$$i; fi; \
	  ext=`echo $$i | sed -e 's/^.*\\.//'`; \
	  inst=`echo $$i | sed -e 's/\\.[0-9a-z]*$$//'`; \
	  inst=`echo $$inst | sed '$(transform)'`.$$ext; \
	  echo " $(INSTALL_DATA) $$file $(DESTDIR)$(man5dir)/$$inst"; \
	  $(INSTALL_DATA) $$file $(DESTDIR)$(man5dir)/$$inst; \
	done

uninstall-man5:
	@list='$(man5_MANS)'; \
	l2='$(man_MANS)'; for i in $$l2; do \
	  case "$$i" in \
	    *.5*) list="$$list $$i" ;; \
	  esac; \
	done; \
	for i in $$list; do \
	  ext=`echo $$i | sed -e 's/^.*\\.//'`; \
	  inst=`echo $$i | sed -e 's/\\.[0-9a-z]*$$//'`; \
	  inst=`echo $$inst | sed '$(transform)'`.$$ext; \
	  echo " rm -f $(DESTDIR)$(man5dir)/$$inst"; \
	  rm -f $(DESTDIR)$(man5dir)/$$inst; \
	done

install-man8:
	$(mkinstalldirs) $(DESTDIR)$(man8dir)
	@list='$(man8_MANS)'; \
	l2='$(man_MANS)'; for i in $$l2; do \
	  case "$$i" in \
	    *.8*) list="$$list $$i" ;; \
	  esac; \
	done; \
	for i in $$list; do \
	  if test -f $(srcdir)/$$i; then file=$(srcdir)/$$i; \
	  else file=$$i; fi; \
	  ext=`echo $$i | sed -e 's/^.*\\.//'`; \
	  inst=`echo $$i | sed -e 's/\\.[0-9a-z]*$$//'`; \
	  inst=`echo $$inst | sed '$(transform)'`.$$ext; \
	  echo " $(INSTALL_DATA) $$file $(DESTDIR)$(man8dir)/$$inst"; \
	  $(INSTALL_DATA) $$file $(DESTDIR)$(man8dir)/$$inst; \
	done

uninstall-man8:
	@list='$(man8_MANS)'; \
	l2='$(man_MANS)'; for i in $$l2; do \
	  case "$$i" in \
	    *.8*) list="$$list $$i" ;; \
	  esac; \
	done; \
	for i in $$list; do \
	  ext=`echo $$i | sed -e 's/^.*\\.//'`; \
	  inst=`echo $$i | sed -e 's/\\.[0-9a-z]*$$//'`; \
	  inst=`echo $$inst | sed '$(transform)'`.$$ext; \
	  echo " rm -f $(DESTDIR)$(man8dir)/$$inst"; \
	  rm -f $(DESTDIR)$(man8dir)/$$inst; \
	done
install-man: $(MANS)
	@$(NORMAL_INSTALL)
	$(MAKE) $(AM_MAKEFLAGS) install-man5 install-man8
uninstall-man:
	@$(NORMAL_UNINSTALL)
	$(MAKE) $(AM_MAKEFLAGS) uninstall-man5 uninstall-man8

tags: TAGS

ID: $(HEADERS) $(SOURCES) $(LISP)
	list='$(SOURCES) $(HEADERS)'; \
	unique=`for i in $$list; do echo $$i; done | \
	  awk '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	here=`pwd` && cd $(srcdir) \
	  && mkid -f$$here/ID $$unique $(LISP)

TAGS:  $(HEADERS) $(SOURCES)  $(TAGS_DEPENDENCIES) $(LISP)
	tags=; \
	here=`pwd`; \
	list='$(SOURCES) $(HEADERS)'; \
	unique=`for i in $$list; do echo $$i; done | \
	  awk '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	test -z "$(ETAGS_ARGS)$$unique$(LISP)$$tags" \
	  || (cd $(srcdir) && etags -o $$here/TAGS $(ETAGS_ARGS) $$tags  $$unique $(LISP))

mostlyclean-tags:

clean-tags:

distclean-tags:
	-rm -f TAGS ID

maintainer-clean-tags:

distdir = $(PACKAGE)-$(VERSION)
top_distdir = $(distdir)

# This target untars the dist file and tries a VPATH configuration.  Then
# it guarantees that the distribution is self-contained by making another
# tarfile.
distcheck: dist
	-rm -rf $(distdir)
	GZIP=$(GZIP_ENV) $(TAR) zxf $(distdir).tar.gz
	mkdir $(distdir)/=build
	mkdir $(distdir)/=inst
	dc_install_base=`cd $(distdir)/=inst && pwd`; \
	cd $(distdir)/=build \
	  && ../configure --srcdir=.. --prefix=$$dc_install_base \
	  && $(MAKE) $(AM_MAKEFLAGS) \
	  && $(MAKE) $(AM_MAKEFLAGS) dvi \
	  && $(MAKE) $(AM_MAKEFLAGS) check \
	  && $(MAKE) $(AM_MAKEFLAGS) install \
	  && $(MAKE) $(AM_MAKEFLAGS) installcheck \
	  && $(MAKE) $(AM_MAKEFLAGS) dist
	-rm -rf $(distdir)
	@banner="$(distdir).tar.gz is ready for distribution"; \
	dashes=`echo "$$banner" | sed s/./=/g`; \
	echo "$$dashes"; \
	echo "$$banner"; \
	echo "$$dashes"
dist: distdir
	-chmod -R a+r $(distdir)
	GZIP=$(GZIP_ENV) $(TAR) chozf $(distdir).tar.gz $(distdir)
	-rm -rf $(distdir)
dist-all: distdir
	-chmod -R a+r $(distdir)
	GZIP=$(GZIP_ENV) $(TAR) chozf $(distdir).tar.gz $(distdir)
	-rm -rf $(distdir)
distdir: $(DISTFILES)
	-rm -rf $(distdir)
	mkdir $(distdir)
	-chmod 777 $(distdir)
	here=`cd $(top_builddir) && pwd`; \
	top_distdir=`cd $(distdir) && pwd`; \
	distdir=`cd $(distdir) && pwd`; \
	cd $(top_srcdir) \
	  && $(AUTOMAKE) --include-deps --build-dir=$$here --srcdir-name=$(top_srcdir) --output-dir=$$top_distdir --gnu Makefile
	$(mkinstalldirs) $(distdir)/doc
	@for file in $(DISTFILES); do \
	  d=$(srcdir); \
	  if test -d $$d/$$file; then \
	    cp -pr $$d/$$file $(distdir)/$$file; \
	  else \
	    test -f $(distdir)/$$file \
	    || ln $$d/$$file $(distdir)/$$file 2> /dev/null \
	    || cp -p $$d/$$file $(distdir)/$$file || :; \
	  fi; \
	done

DEPS_MAGIC := $(shell mkdir .deps > /dev/null 2>&1 || :)

-include $(DEP_FILES)

mostlyclean-depend:

clean-depend:

distclean-depend:
	-rm -rf .deps

maintainer-clean-depend:

%.o: %.c
	@echo '$(COMPILE) -c $<'; \
	$(COMPILE) -Wp,-MD,.deps/$(*F).pp -c $<
	@-cp .deps/$(*F).pp .deps/$(*F).P; \
	tr ' ' '\012' < .deps/$(*F).pp \
	  | sed -e 's/^\\$$//' -e '/^$$/ d' -e '/:$$/ d' -e 's/$$/ :/' \
	    >> .deps/$(*F).P; \
	rm .deps/$(*F).pp

%.lo: %.c
	@echo '$(LTCOMPILE) -c $<'; \
	$(LTCOMPILE) -Wp,-MD,.deps/$(*F).pp -c $<
	@-sed -e 's/^\([^:]*\)\.o[ 	]*:/\1.lo \1.o :/' \
	  < .deps/$(*F).pp > .deps/$(*F).P; \
	tr ' ' '\012' < .deps/$(*F).pp \
	  | sed -e 's/^\\$$//' -e '/^$$/ d' -e '/:$$/ d' -e 's/$$/ :/' \
	    >> .deps/$(*F).P; \
	rm -f .deps/$(*F).pp
check-TESTS: $(TESTS)
	@failed=0; all=0; \
	srcdir=$(srcdir); export srcdir; \
	for tst in $(TESTS); do \
	  if test -f $$tst; then dir=.; \
	  else dir="$(srcdir)"; fi; \
	  if $(TESTS_ENVIRONMENT) $$dir/$$tst; then \
	    all=`expr $$all + 1`; \
	    echo "PASS: $$tst"; \
	  elif test $$? -ne 77; then \
	    all=`expr $$all + 1`; \
	    failed=`expr $$failed + 1`; \
	    echo "FAIL: $$tst"; \
	  fi; \
	done; \
	if test "$$failed" -eq 0; then \
	  banner="All $$all tests passed"; \
	else \
	  banner="$$failed of $$all tests failed"; \
	fi; \
	dashes=`echo "$$banner" | sed s/./=/g`; \
	echo "$$dashes"; \
	echo "$$banner"; \
	echo "$$dashes"; \
	test "$$failed" -eq 0
info-am:
info: info-am
dvi-am:
dvi: dvi-am
check-am: all-am
	$(MAKE) $(AM_MAKEFLAGS) check-TESTS
check: check-am
installcheck-am:
installcheck: installcheck-am
install-exec-am: install-binPROGRAMS install-sbinPROGRAMS \
		install-sbinSCRIPTS
install-exec: install-exec-am

install-data-am: install-man
install-data: install-data-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am
install: install-am
uninstall-am: uninstall-binPROGRAMS uninstall-sbinPROGRAMS \
		uninstall-sbinSCRIPTS uninstall-man
uninstall: uninstall-am
all-am: Makefile $(PROGRAMS) $(SCRIPTS) $(MANS)
all-redirect: all-am
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) AM_INSTALL_PROGRAM_FLAGS=-s install
installdirs:
	$(mkinstalldirs)  $(DESTDIR)$(bindir) $(DESTDIR)$(sbindir) \
		$(DESTDIR)$(sbindir) $(DESTDIR)$(mandir)/man5 \
		$(DESTDIR)$(mandir)/man8


mostlyclean-generic:

clean-generic:

distclean-generic:
	-rm -f Makefile $(CONFIG_CLEAN_FILES)
	-rm -f config.cache config.log stamp-h stamp-h[0-9]*

maintainer-clean-generic:
	-test -z "$(MAINTAINERCLEANFILES)" || rm -f $(MAINTAINERCLEANFILES)
mostlyclean-am:  mostlyclean-binPROGRAMS mostlyclean-sbinPROGRAMS \
		mostlyclean-compile mostlyclean-tags mostlyclean-depend \
		mostlyclean-generic

mostlyclean: mostlyclean-am

clean-am:  clean-binPROGRAMS clean-sbinPROGRAMS clean-compile clean-tags \
		clean-depend clean-generic mostlyclean-am

clean: clean-am

distclean-am:  distclean-binPROGRAMS distclean-sbinPROGRAMS \
		distclean-compile distclean-tags distclean-depend \
		distclean-generic clean-am

distclean: distclean-am
	-rm -f config.status

maintainer-clean-am:  maintainer-clean-binPROGRAMS \
		maintainer-clean-sbinPROGRAMS maintainer-clean-compile \
		maintainer-clean-tags maintainer-clean-depend \
		maintainer-clean-generic distclean-am
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."

maintainer-clean: maintainer-clean-am
	-rm -f config.status

.PHONY: mostlyclean-binPROGRAMS distclean-binPROGRAMS clean-binPROGRAMS \
maintainer-clean-binPROGRAMS uninstall-binPROGRAMS install-binPROGRAMS \
mostlyclean-sbinPROGRAMS distclean-sbinPROGRAMS clean-sbinPROGRAMS \
maintainer-clean-sbinPROGRAMS uninstall-sbinPROGRAMS \
install-sbinPROGRAMS mostlyclean-compile distclean-compile \
clean-compile maintainer-clean-compile uninstall-sbinSCRIPTS \
install-sbinSCRIPTS install-man5 uninstall-man5 install-man8 \
uninstall-man8 install-man uninstall-man tags mostlyclean-tags \
distclean-tags clean-tags maintainer-clean-tags distdir \
mostlyclean-depend distclean-depend clean-depend \
maintainer-clean-depend check-TESTS info-am info dvi-am dvi check \
check-am installcheck-am installcheck install-exec-am install-exec \
install-data-am install-data install-am install uninstall-am uninstall \
all-redirect all-am all installdirs mostlyclean-generic \
distclean-generic clean-generic maintainer-clean-generic clean \
mostlyclean distclean maintainer-clean


# docbook2man writes file itself, doesn't do stdout.
%.8: doc/%.sgml
	if [ "$(DOCBOOKTOMAN)" = "docbook2man" ]; then                     \
	    $(DOCBOOKTOMAN) $< > /dev/null 2>&1;                       \
	else                                                               \
	    $(DOCBOOKTOMAN) $< 2>&1 > $@ | sed 's/^[^:]*://';              \
	fi

%.5: doc/%.sgml
	if [ "$(DOCBOOKTOMAN)" = "docbook2man" ]; then                     \
	    $(DOCBOOKTOMAN) $< > /dev/null 2>&1;                       \
	else                                                               \
	    $(DOCBOOKTOMAN) $< 2>&1 > $@ | sed 's/^[^:]*://';              \
	fi

# docbook2man creates extra crap files which need cleaning.
distclean: killbuildmanpages

killbuildmanpages:
	rm -f doc/*.tmp manpage.refs manpage.links

tarball: $(DIST_DIR)/module-init-tools-$(VERSION).tar.gz

$(DIST_DIR)/module-init-tools-$(VERSION).tar.gz: dist
	mv module-init-tools-$(VERSION).tar.gz $@

srpm: $(DIST_DIR)/module-init-tools-$(VERSION).tar.gz
	ln -sf $(DIST_DIR)/module-init-tools-$(VERSION).tar.gz /usr/src/rpm/SOURCES/
	set -e; RELEASE=`grep '^Release:' /usr/src/rpm/SPECS/modutils.spec | awk '{ print $$2 }'`; \
	if [ "`grep '%define mit_ver' /usr/src/rpm/SPECS/modutils.spec | awk '{print $$3}'`" != $(VERSION) ]; then \
		sed -e "s/Release: $$RELEASE/Release: `expr $$RELEASE + 1`/" -e 's/%define mit_ver.*/%define mit_ver $(VERSION)/' < /usr/src/rpm/SPECS/modutils.spec > /tmp/modutils.spec; \
		rpm -ba /tmp/modutils.spec; \
		mv /usr/src/rpm/SRPMS/modutils-2.4.21-`expr $$RELEASE + 1`.src.rpm $(DIST_DIR); \
		mv /tmp/modutils.spec /usr/src/rpm/SPECS/modutils.spec; \
	else \
		rpm -ba /usr/src/rpm/SPECS/modutils.spec; \
		mv /usr/src/rpm/SRPMS/modutils-2.4.21-$$RELEASE.src.rpm $(DIST_DIR); \
	fi

# No testsuite?
tests/runtests:
	mkdir tests
	echo '#! /bin/sh' > $@
	echo '# Install the testsuite over this dir. ' >> $@
	chmod a+x $@

testsuite: $(DIST_DIR)/module-init-tools-testsuite-$(VERSION).tar.gz

$(DIST_DIR)/module-init-tools-testsuite-$(VERSION).tar.gz:
	ln -sfn `pwd` /tmp/module-init-tools-$(VERSION) 
	cd /tmp && tar --exclude '*~' -c -z -f $@ module-init-tools-$(VERSION)/tests
	rm /tmp/module-init-tools-$(VERSION)

# Pre-releases only don't get testsuites
pre-release: check clean tarball

release: check clean tarball testsuite

moveold: check-for-sbin check-for-old move-old-targets

check-for-sbin:
	if [ "`echo $(DESTDIR)$(sbindir) | tr -s / /`" = /sbin ]; then :;    \
	else								     \
		echo moveold usually only makes sense when installing into /sbin; \
		exit 1;							     \
	fi

check-for-old:
	if [ -f /sbin/lsmod.old ]; then					\
		echo Someone already moved old versions. >&2; exit 1;	\
	fi

# Don't just move symlinks, reset them to point to xxx.old.
# RedHat 8.0 doesn't ship with readlink by default.  Use ls -l.
# Also, make symlink from /bin to /sbin for lsmod (FHS compliant).
move-old-targets:
	for f in lsmod modprobe rmmod depmod insmod modinfo; do		    \
	    if [ -L /sbin/$$f ]; then					    \
		ln -sf `ls -l /sbin/$$f | sed 's/.* -> //'`.old /sbin/$$f;  \
	    fi;								    \
	    mv /sbin/$$f /sbin/$$f.old;					    \
	    if [ -f /usr/share/man/man8/$$f.8.gz ]; then		    \
		mv /usr/share/man/man8/$$f.8.gz				    \
			/usr/share/man/man8/$$f.old.8.gz;		    \
	    elif [ -f /usr/share/man/man8/$$f.8.bz2 ]; then		    \
	        mv /usr/share/man/man8/$$f.8.bz2			    \
			/usr/share/man/man8/$$f.old.8.bz2;		    \
	    else							    \
	        mv /usr/share/man/man8/$$f.8 /usr/share/man/man8/$$f.old.8; \
	    fi;								    \
	done
	for f in kallsyms ksyms; do					    \
	    if [ -L /sbin/$$f ]; then					    \
		ln -sf `ls -l /sbin/$$f | sed 's/.* -> //'`.old /sbin/$$f;  \
	    fi;								    \
	done
	ln -s /sbin/lsmod.old /bin/lsmod.old

# For installs in /usr/local/sbin
links:
	for f in insmod modprobe rmmod depmod; do ln -s /sbin/$$f $(DESTDIR)$(sbindir)/$$f.old; done
	for f in  lsmod; do ln -s /sbin/$$f $(DESTDIR)$(bindir)/$$f.old; done


romfs:
	$(ROMFSINST) /sbin/modprobe
	$(ROMFSINST) /sbin/lsmod
	$(ROMFSINST) /sbin/insmod
	$(ROMFSINST) /sbin/rmmod
	$(ROMFSINST) /sbin/depmod

# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
