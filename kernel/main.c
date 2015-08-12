/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <types.h>
#include <memory.h>
#include <kpvmem.h>
#include <llops.h>
#include <console.h>

__attribute__((__aligned__(PGSIZE)))
pde_t pgdir[NPDENTRIES] = {
	[0] = 0 | PTE_P | PTE_W | PTE_PS, // [ 0, 4M ) -> [ 0, 4M )

	// [ 0, 4M ) -> [ 0, 4M )
	[KERN_VBASE >> PDXSHIFT] = 0 | PTE_P | PTE_W | PTE_PS,
};

void main(void)
{
	cnsl_puts("hello, kernel", 10, 20);

	while (1)
		;
}
