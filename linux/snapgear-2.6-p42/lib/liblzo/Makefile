all:
	# Configure only first time
	if [ ! -f .configured ]; then \
	 cd liblzo; ./configure --host=sparc-linux; cd ..; \
	 touch .configured; \
	fi
	make -C liblzo

# nothing to install
romfs:

clean:
	-rm -f .configured
	make -C liblzo clean
