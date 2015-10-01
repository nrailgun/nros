PROJS = boot kernel

nros: $(PROJS) nros.img
	dd if=boot/bootloader of=nros.img conv=notrunc
	dd if=kernel/kernel of=nros.img seek=1 conv=notrunc

nros.img:
	dd if=/dev/zero of=nros.img count=10000
	chmod a+x nros.img

boot:
	make -C boot

kernel:
	make -C kernel

.PHONY: nros $(PROJS) clean run
run:
	qemu-system-i386 -hda nros.img -smp 2 -m 512 &

clean:
	(for i in $(PROJS); do \
		make -C $$i clean; \
	done)
	rm -rf *.o *.img *.iso
