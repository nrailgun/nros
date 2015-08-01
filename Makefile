CC = gcc
INCLUDES = -I.
CFLAGS = $(INCLUDES) -m32 -nostdinc -fno-builtin -ggdb -O -static \
	-fno-strict-aliasing -fno-pic -fno-omit-frame-pointer \
	-fno-stack-protector -Werror

bootloader.img: boot.S bootmain.c setup.ld
	$(CC) $(CFLAGS) -c boot.S
	$(CC) $(CFLAGS) -c bootmain.c
	ld -T setup.ld -o bootloader.img boot.o bootmain.o

#bootloader.img: boot.s setup.ld
#	as -o boot.o boot.s
#	ld -T setup.ld -o bootloader.img boot.o

.PHONY: run clean qemu
run:
	qemu-system-i386 -hda bootloader.img &

clean:
	rm -rf isodir boot.o kernel.o enable_paging.o myos.bin myos.iso
	rm -rf *.o a.out *.img
