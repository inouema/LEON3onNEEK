
EXEC = hdparm
OBJS = hdparm.o identify.o

all: $(EXEC)

$(EXEC): $(OBJS) hdparm.h
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

romfs:
	$(ROMFSINST) /bin/$(EXEC)

clean:
	-rm -f $(EXEC) *.elf *.gdb *.o

