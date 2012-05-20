all:
	cd ncurses-5.6; CFLAGS='$(CFLAGS) -DTRACE ' ./configure --host=sparc-linux | tee ../ncurses_configure.out
	cd ncurses-5.6; CFLAGS='$(CFLAGS) -DTRACE ' make | tee ../ncurse_compile.out

romfs:
	mkdir -p $(ROMFSDIR)/usr/share/terminfo/v
	cp -r /usr/share/terminfo/v/vt102* $(ROMFSDIR)/usr/share/terminfo/v/
