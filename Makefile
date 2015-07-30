bootloader.img: boot.s setup.ld
	as -o boot.o boot.s
	ld -T setup.ld -o bootloader.img boot.o

.PHONY: run clean qemu
run:
	qemu-system-i386 -hda bootloader.img &

clean:
	rm -rf isodir boot.o kernel.o enable_paging.o myos.bin myos.iso
	rm -rf *.o a.out *.img
