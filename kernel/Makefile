include ../Makefile.config

kobjs := kentry.o main.o console.o spinlock.o kalloc.o kvm.o string.o

kernel: kernel.ld $(kobjs)
	$(LD) $(LDFLAGS) -T kernel.ld -o $@ $(kobjs)

kentry.o: kentry.S
	$(CC) $(CFLAGS) -c kentry.S

%.o: %.c
	$(CC) $(CFLAGS) -c $<

-include *.d

.PHONY: clean run
clean:
	rm -rf *.d *.o kernel

run:
	make -C .. run
