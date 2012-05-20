CFLAGS = -O2 -D__KERNEL__ -DMODULE -I../include
# For MODVERSIONS
CFLAGS += -DMODVERSIONS -include /usr/include/linux/modversions.h

all: t1.o t2.o test.o

t1.o: t1a.o t1b.o
	ld -o $@ -r $^

clean:
	rm -f *.o
