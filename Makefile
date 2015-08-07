PROJS = boot kernel

nros: $(PROJS) nros.img
	(for i in $(PROJS); do \
		make -C $$i; \
	done)
	dd if=boot/bootloader of=nros.img conv=notrunc
	dd if=kernel/kernel of=nros.img seek=1 conv=notrunc

nros.img:
	dd if=/dev/zero of=nros.img count=10000
	chmod a+x nros.img

.PHONY: nros clean qemu
qemu:
	qemu-system-i386 -hda nros.img &

clean:
	(for i in $(PROJS); do \
		make -C $$i clean; \
	done)
	rm -rf *.o *.img *.iso
