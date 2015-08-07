include ../Makefile.config

bootloader: boot.S bootmain.c setup.ld
	$(CC) $(CFLAGS) -c boot.S
	$(CC) $(CFLAGS) -c bootmain.c
	ld -T setup.ld -o $@ boot.o bootmain.o

.PHONY: clean
clean:
	rm -rf *.o bootloader
