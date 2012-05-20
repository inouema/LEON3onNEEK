cmd_applets/built-in.o :=  sparc-linux-gcc -nostdlib -Wl,-Bdynamic -mcpu=v8 -msoft-float -Wl,-rpath /lib  -r -o applets/built-in.o applets/applets.o
