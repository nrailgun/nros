include ../Makefile.config

kernel: kernel.ld kentry.S main.c
	$(CC) $(CFLAGS) -c kentry.S
	$(CC) $(CFLAGS) -c main.c
	$(LD) $(LDFLAGS) -T kernel.ld -o $@ kentry.o main.o

.PHONY: clean run
clean:
	rm -rf *.o kernel

run:
	make -C .. run
