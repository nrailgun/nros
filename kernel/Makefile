include ../Makefile.config

kern_objs := kentry.o main.o console.o spinlock.o kalloc.o kvm.o string.o \
	mp.o math.o ctype.o assert.o

test_objs := test/test.o test/test_ctype.o test/test_string.o test/test_varg.o \
	test/test_cnsl.o

kernel: kernel.ld $(kern_objs) $(test_objs)
	$(LD) $(LDFLAGS) -T kernel.ld -o $@ $(kern_objs) $(test_objs)

kentry.o: kentry.S
	$(CC) $(CFLAGS) -o $@ -c kentry.S

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

-include *.d test/*.d

.PHONY: clean run
clean:
	rm -rf *.d *.o test/*.d test/*.o kernel

run:
	make -C .. run
