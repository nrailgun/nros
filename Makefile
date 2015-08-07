CC = gcc
INCLUDES = -I.
CFLAGS = $(INCLUDES) -m32 -nostdinc -fno-builtin -ggdb -O -static \
	-fno-strict-aliasing -fno-pic -fno-omit-frame-pointer \
	-fno-stack-protector -Werror

all: nros.img bootloader kernel
	dd if=bootloader of=nros.img conv=notrunc
	dd if=kernel of=nros.img seek=1 conv=notrunc

nros.img:
	dd if=/dev/zero of=nros.img count=10000
	chmod a+x nros.img

DEPS = llops.h memory.h types.h

bootloader: boot.S bootmain.c setup.ld $(DEPS)
	$(CC) $(CFLAGS) -c boot.S
	$(CC) $(CFLAGS) -c bootmain.c
	ld -T setup.ld -o $@ boot.o bootmain.o

kernel:
	echo -n '0987654321' > $@

.PHONY: run clean qemu
run:
	qemu-system-i386 -hda nros.img &

clean:
	rm -rf *.o *.img bootloader
