myos.iso: isodir/boot/grub myos.bin
	cp myos.bin isodir/boot
	cp grub.cfg isodir/boot/grub
	grub-mkrescue -o myos.iso isodir

isodir/boot/grub:
	mkdir -p $@

myos.bin: boot.o kernel.o enable_paging.o
	i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib $? -lgcc

boot.o:
	i686-elf-as boot.s -o boot.o

kernel.o: kernel.c
	i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

enable_paging.o: enable_paging.s
	i686-elf-as $? -o $@

.PHONY: qemu clean

qemu:
	qemu-system-i386 -cdrom myos.iso

clean:
	rm -rf isodir boot.o kernel.o enable_paging.o myos.bin myos.iso
