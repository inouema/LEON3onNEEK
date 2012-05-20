all:
	cd zile-2.2.56;  CFLAGS='$(CFLAGS) -I/home/eiselekd/snapgear-dir/snapgear_26/snapgear/user/ncurses/ncurses-5.6/include -Wl,-L/home/eiselekd/snapgear-dir/snapgear_26/snapgear/user/ncurses/ncurses-5.6/lib/'  \
	./configure --host=sparc-linux | tee ../zile_configure.out
	cd zile-2.2.56;  CFLAGS='$(CFLAGS) -I/home/eiselekd/snapgear-dir/snapgear_26/snapgear/user/ncurses/ncurses-5.6/include -Wl,-L/home/eiselekd/snapgear-dir/snapgear_26/snapgear/user/ncurses/ncurses-5.6/lib/' \
	make | tee ../zile_compile.out

romfs:
	cp zile-2.2.56/src/zile $(ROMFSDIR)/bin/zile; chmod a+rx $(ROMFSDIR)/bin/zile
