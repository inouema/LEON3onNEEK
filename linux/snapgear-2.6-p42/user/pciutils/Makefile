
VER=3.1.3
ZVER=1.2.3

all:
	make -C pciutils-$(VER)

# Install pci-utils to romfs directory
romfs: all
	make -C pciutils-$(VER) romfs

# Clean up pciutils
clean:
	make -C pciutils-$(VER) clean
