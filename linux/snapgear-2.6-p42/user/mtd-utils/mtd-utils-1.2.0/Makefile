
# -*- sh -*-

SBINDIR=/usr/sbin
MANDIR=/usr/share/man
INCLUDEDIR=/usr/include

CROSS=sparc-linux-
CC := $(CROSS)gcc
CFLAGS ?= -O2 -g
CFLAGS += -Wall
# -I../acl-2.2.48/include
CPPFLAGS += -I./include 
#-I../acl-2.2.48/include -I../lzo-2.03/include -I/home/daniel/dist_debug/snapgear-2.6-p39/lib/zlib
LDFLAGS += 
#-L../acl-2.2.48/libacl/.libs -L../lzo-2.03/src/.libs -L/home/daniel/dist_debug/snapgear-2.6-p39/lib/zlib

ifeq ($(origin CROSS),undefined)
  BUILDDIR := .
else
# Remove the trailing slash to make the directory name
  BUILDDIR := $(CROSS:-=)
endif

ifeq ($(WITHOUT_XATTR), 1)
  CPPFLAGS += -DWITHOUT_XATTR
endif

RAWTARGETS = ftl_format flash_erase flash_eraseall nanddump doc_loadbios \
	ftl_check mkfs.jffs2 flash_lock flash_unlock flash_info \
	flash_otp_info flash_otp_dump mtd_debug flashcp nandwrite nandtest \
	jffs2dump \
	nftldump nftl_format docfdisk \
	rfddump rfdformat \
	 \
	sumtool #jffs2reader
# serve_image recv_image [REMOVED FROM BUILD]

TARGETS = $(foreach target,$(RAWTARGETS),$(BUILDDIR)/$(target))

SYMLINKS =

%: %.o
	$(CC) $(CFLAGS) $(LDFLAGS) -g -o $@ $^

$(BUILDDIR)/%.o: %.c
	mkdir -p $(BUILDDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $< -g -Wp,-MD,$(BUILDDIR)/.$(<F).dep

.SUFFIXES:

all: $(TARGETS)
#	make -C $(BUILDDIR)/ubi-utils

IGNORE=${wildcard $(BUILDDIR)/.*.c.dep}
-include ${IGNORE}

clean:
	rm -f $(BUILDDIR)/*.o $(TARGETS) $(BUILDDIR)/.*.c.dep $(SYMLINKS)
	if [ "$(BUILDDIR)x" != ".x" ]; then rm -rf $(BUILDDIR); fi
#	make -C $(BUILDDIR)/ubi-utils clean

$(SYMLINKS):
	ln -sf ../fs/jffs2/$@ $@

$(BUILDDIR)/mkfs.jffs2: $(BUILDDIR)/crc32.o \
			$(BUILDDIR)/compr_rtime.o \
			$(BUILDDIR)/mkfs.jffs2.o \
			$(BUILDDIR)/compr_zlib.o \
			$(BUILDDIR)/compr_lzo.o \
			$(BUILDDIR)/compr.o \
			$(BUILDDIR)/rbtree.o
	$(CC) $(LDFLAGS) -o $@ $^ -lz -llzo2

$(BUILDDIR)/flash_eraseall: $(BUILDDIR)/crc32.o $(BUILDDIR)/flash_eraseall.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILDDIR)/jffs2reader: $(BUILDDIR)/jffs2reader.o
	$(CC) $(LDFLAGS) -o $@ $^ -lz

$(BUILDDIR)/jffs2dump: $(BUILDDIR)/jffs2dump.o $(BUILDDIR)/crc32.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILDDIR)/sumtool: $(BUILDDIR)/sumtool.o $(BUILDDIR)/crc32.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILDDIR)/serve_image: $(BUILDDIR)/serve_image.o $(BUILDDIR)/crc32.o $(BUILDDIR)/fec.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILDDIR)/recv_image: $(BUILDDIR)/recv_image.o $(BUILDDIR)/crc32.o $(BUILDDIR)/fec.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILDDIR)/fectest: $(BUILDDIR)/fectest.o $(BUILDDIR)/crc32.o $(BUILDDIR)/fec.o
	$(CC) $(LDFLAGS) -o $@ $^



install: ${TARGETS}
	mkdir -p ${DESTDIR}/${SBINDIR}
	install -m0755 ${TARGETS} ${DESTDIR}/${SBINDIR}/
	mkdir -p ${DESTDIR}/${MANDIR}/man1
	gzip -9c mkfs.jffs2.1 > ${DESTDIR}/${MANDIR}/man1/mkfs.jffs2.1.gz
#	make -C $(BUILDDIR)/ubi-utils install
