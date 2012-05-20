
DISTDIR=0.94.14rc21

# configure the BOA webserver build environment

ifeq ($(LINUXDIR),linux-2.0.x)
all: configure20 compile
else
all: configure26 compile
endif

# install into romfs directory
romfs: all
	-cd $(DISTDIR)/src ; \
	 mkdir -p $(ROOTDIR)/romfs/bin ; \
	 $(ROMFSINST) /bin/boa
#	cp -f $(DISTDIR)/src/boa $(ROOTDIR)/romfs/bin/boa

# may fail if no Makefile present (no configuration done)
clean:
	-make -C $(DISTDIR) clean

mrclean:
	-make -C $(DISTDIR) mrclean

configure26:	
	@echo "************************************************"
	@echo
	@echo " SnapGear is not prepared for BOA $(DISTDIR)"
	@echo " using linux-2.6.x"
	@echo " edit the user/boa-xx/Makefile for support"
	@echo
	@echo "************************************************"
#	exit(-1)
	cd $(DISTDIR) ; \
	  if [ ! -f src/config.h ]; then \
	    ./configure \
		--host=sparc-linux \
		"CFLAGS=$(CFLAGS)" \
# config script did not do everything right though... \
# we use a prepepared config.h file instead \
#	    cp -f config.h_2.6.x $(DISTDIR)/src/config.h ; \
	  fi

configure20:
	echo "CFLAGS=$(CFLAGS)" > mu.txt
	echo "LDFLAGS=$(LDLAGS)" >> mu.txt
	echo "LIBS=$(LIBS)" >> mu.txt
	echo "CPPFLAGS=$(CPPFLAGS)" >> mu.txt
	@cd $(DISTDIR) ; \
	  if [ ! -f src/config.h ]; then \
	    ./configure \
		--host=sparc-linux \
		--includedir=$(ROOTDIR)/uClibc/include \
		"LDFLAGS=-g -nostartfiles -L$(ROOTDIR)/lib/uClibc/lib -L$(ROOTDIR)/lib/libnet -Wl,-Bstatic -mno-relax -elf2flt -mpic-none -lcrypt -nodefaultlibs" \
		"CFLAGS=$(CFLAGS)" \
		"LIBS=$(ROOTDIR)/lib/uClibc/lib/crt1.o $(ROOTDIR)/lib/uClibc/lib/crti.o -lc -lgcc $(ROOTDIR)/lib/uClibc/lib/crtn.o" \
		CPPFLAGS=-I$(ROOTDIR)/uClibc/include ; \
# config script did not do everything right though... \
# we use a prepepared config.h file instead \
#	    cp -f config.h_2.0.x $(DISTDIR)/src/config.h ; \
	  fi

compile:
	$(MAKE) -C $(DISTDIR) all
