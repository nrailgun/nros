include ../Makefile.config

kernel: main.c kernel.ld
	$(CC) $(CFLAGS) -c main.c
	$(LD) $(LDFLAGS) -T kernel.ld -o $@ main.o

.PHONY: clean run
clean:
	rm -rf *.o kernel

run:
	make -C .. run
