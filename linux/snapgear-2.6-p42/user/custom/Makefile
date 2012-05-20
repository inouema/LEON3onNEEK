

EXEC1 = test
OBJS1 = test.o
EXEC2 = test.sig
OBJS2 = test.sig.o
EXEC3 = test.sig2
OBJS3 = test.sig2.o
EXEC4 = testsin
OBJS4 = testsin.o
EXEC5 = testthread
OBJS5 = test_thread.o
EXEC6 = testnet
OBJS6 = testnet.o
EXEC7 = testcpp
OBJS7 = testcpp.o

%o : %cxx
	$(CXX) -v -I /opt/sparc-linux/include/c++/3.2.2 -I /opt/sparc-linux/include/c++/3.2.2/backward -I /opt/sparc-linux/include/c++/3.2.2/sparc-linux $(CFLAGS) -c -o $@ $< 

#all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5) $(EXEC7) INSMODEXE
all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5) $(EXEC6) INSMODEXE  #$(EXEC7) 

$(EXEC1): $(OBJS1)
	$(CC) $(LDFLAGS) -o $@ $(OBJS1) $(LDLIBS$(LDLIBS_$@))

$(EXEC2): $(OBJS2)
	$(CC) $(LDFLAGS) -o $@ $(OBJS2) $(LDLIBS$(LDLIBS_$@))

$(EXEC3): $(OBJS3)
	$(CC) $(LDFLAGS) -o $@ $(OBJS3) $(LDLIBS$(LDLIBS_$@))

$(EXEC4): $(OBJS4)
	echo "LDFLAGS: $(LDFLAGS)"
	$(CC) $(LDFLAGS) -o $@ $(OBJS4) $(LDLIBS$(LDLIBS_$@)) -lm -lgcc -lm -lgcc

$(EXEC5): $(OBJS5)
	$(CC) $(LDFLAGS) -o $@ $(OBJS5) -lpthread $(LDLIBS$(LDLIBS_$@)) 

$(EXEC6): $(OBJS6)
	$(CC) $(LDFLAGS) -o $@ $(OBJS6) $(LDLIBS$(LDLIBS_$@)) 

$(EXEC7): $(OBJS7)
	$(CC) -Wl,--start-group $(LDXXFLAGS) -o $@ $(OBJS7) -lstdc++ $(LDXXLIBS) -Wl,--end-group #-Wl,-M




INSMODEXE: 
#	make -C $(ROOTDIR)/$(LINUXDIR) SUBDIRS=$(shell pwd)/modules modules

romfs:
#	$(ROMFSINST) /bin/$(EXEC1)
#	$(ROMFSINST) /bin/$(EXEC2)
#	$(ROMFSINST) /bin/$(EXEC3)
	$(ROMFSINST) /bin/$(EXEC4)
#	$(ROMFSINST) /bin/$(EXEC5)
	$(ROMFSINST) /bin/$(EXEC6)
#	$(ROMFSINST) /bin/$(EXEC7)
#	make -C modules romfs

clean:
	-rm -f $(EXEC) *.elf *.gdb *.o test test.sig test.sig2 testcpp testnet testsin testthread
	make -C modules clean 
