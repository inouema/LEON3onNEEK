
lib-y 			= _put.o _gunzip.o 

CC=$(CROSS_COMPILE)gcc -I../common -I$(ROOTDIR)/$(LINUXDIR)/include -I$(ROOTDIR)/$(LINUXDIR)/arch/sparc/include -I. -D__KERNEL__ -Wall -mno-fpu -nostdinc -iwithprefix include -O2

all: $(lib-y) 
	$(CROSS_COMPILE)ar rcs boot.a $(lib-y)

_gunzip.o: _gunzip.c inflate.c 

clean:
	rm -f *.o *.a
