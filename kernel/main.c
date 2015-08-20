/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <comm.h>
#include <console.h>
#include <errn.h>
#include <kpvmem.h>
#include <llops.h>
#include <memory.h>
#include <spinlock.h>
#include <types.h>
#include <kalloc.h>

__attribute__((__aligned__(PGSIZE)))
pde_t pgdir[NPDENTRIES] = {
	[0] = 0 | PTE_P | PTE_W | PTE_PS, // [ 0, 4M ) -> [ 0, 4M )

	// [ 0, 4M ) -> [ 0, 4M )
	[KERN_VBASE >> PDXSHIFT] = 0 | PTE_P | PTE_W | PTE_PS,
};

extern char end[]; // End of kernel

void main(void)
{
	kalloc_init(end, P2V(4 * 1024 * 1024));

	cnsl_puts("hello, world", 10, 20);

	while (1)
		;
}
