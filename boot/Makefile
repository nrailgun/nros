include ../Makefile.config

#BOOT_DEFINES = -DCONFIG_LOADING_MSG

bootloader: boot.S bootmain.c setup.ld
	$(CC) $(CFLAGS) $(BOOT_DEFINES) -c boot.S
	$(CC) $(CFLAGS) -c bootmain.c
	$(LD) -T setup.ld -o bootloader boot.o bootmain.o

.PHONY: clean run
clean:
	rm -rf *.o bootloader

run:
	qemu-system-i386 -hda bootloader &
