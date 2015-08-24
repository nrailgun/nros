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

__attribute__((__aligned__(PG_SIZE)))
pde_t pgdir[N_PDENT] = {
	[0] = 0 | PTE_P | PTE_W | PTE_PS, // [ 0, 4M ) -> [ 0, 4M )

	// [ 0, 4M ) -> [ 0, 4M )
	[KERN_VBASE >> PDIDX_SHFT] = 0 | PTE_P | PTE_W | PTE_PS,
};

extern char kend[]; // End of kernel

void main(void)
{
	kalloc_init(kend, P2V(4 * 1024 * 1024));

	cnsl_puts("hello, world", 10, 20);

	while (1)
		;
}
