
VER=1.2.0

# MTD-UTILS need ACL, LZO and ATTR library
CFLAGS   += -I$(ROOTDIR)/lib/libacl/include -I$(ROOTDIR)/lib/liblzo/include -I$(ROOTDIR)/lib/zlib
CPPFLAGS += -I$(ROOTDIR)/lib/libacl/include -I$(ROOTDIR)/lib/liblzo/include -I$(ROOTDIR)/lib/zlib
LDFLAGS  += -L$(ROOTDIR)/lib/libacl/libacl/.libs -L$(ROOTDIR)/lib/liblzo/libs -L$(ROOTDIR)/lib/zlib

# Make mtd-utils
all:
	make -C mtd-utils-$(VER)

# Install mtd-utils to romfs directory
romfs: all
	make -C mtd-utils-$(VER) install DESTDIR=$(ROMFSDIR)

# Clean up mtd-utils
clean:
	rm -f .configured
	make -C mtd-utils-$(VER) clean
