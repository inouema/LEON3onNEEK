

EXEC1 = can1
OBJS1 = can_send.o

EXEC2 = can2
OBJS2 = receive_select.o

EXEC3 = can3
OBJS3 = receive.o


all: $(EXEC1)  $(EXEC2)  $(EXEC3)  

$(EXEC1): $(OBJS1)
	$(CC) $(LDFLAGS) -o $@ $(OBJS1) $(LDLIBS$(LDLIBS_$@))

$(EXEC2): $(OBJS2)
	$(CC) $(LDFLAGS) -o $@ $(OBJS2) $(LDLIBS$(LDLIBS_$@))


$(EXEC3): $(OBJS3)
	$(CC) $(LDFLAGS) -o $@ $(OBJS3) $(LDLIBS$(LDLIBS_$@))

romfs:
	$(ROMFSINST) /bin/$(EXEC1)
	$(ROMFSINST) /bin/$(EXEC2)
	$(ROMFSINST) /bin/$(EXEC3)
	



clean:
	-rm -f $(EXEC) *.elf *.gdb *.o

