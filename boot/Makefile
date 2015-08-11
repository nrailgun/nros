include ../Makefile.config

bootobjs := boot.o bootmain.o

bootloader: setup.ld $(bootobjs)
	$(LD) -T setup.ld -o $@ $(bootobjs)

boot.o: boot.S
	$(CC) $(CFLAGS) -c $<

%.o: %.c
	$(CC) $(CFLAGS) -c $<

-include *.d

.PHONY: clean run
clean:
	rm -rf *.d *.o bootloader

run:
	qemu-system-i386 -hda bootloader &
