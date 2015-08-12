/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <types.h>
#include <memory.h>
#include <kpvmem.h>
#include <llops.h>

#define MARK(adr) *(int *) (0x80000000 + adr) = 0xdeaddead

__attribute__((__aligned__(PGSIZE)))
pde_t pgdir[NPDENTRIES] = {
	[0] = 0 | PTE_P | PTE_W | PTE_PS, // [ 0, 4M ) -> [ 0, 4M )

	// [ 0, 4M ) -> [ 0, 4M )
	[KERN_VBASE >> PDXSHIFT] = 0 | PTE_P | PTE_W | PTE_PS,
};

void putc_console(char c, uint_t off)
{
	volatile char *video;
	
	video = (volatile char *) (0xb8000 + off * 2);
	*video++ = c;
	*video = 0x07;
}

void puts_console(const char *str, uint_t off)
{
	int i;

	for (i = 0; str[i]; i++) {
		putc_console(str[i], off++);
	}
}

void main(void)
{
	puts_console("hello, world, I love this.", 0);

	MARK(0x3000);

	while (1);
}
