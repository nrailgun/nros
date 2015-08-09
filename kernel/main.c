/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <types.h>
#include <memory.h>
#include <kpvmem.h>

__attribute__((__aligned__(PGSIZE)))
pgdir_entry_t pgdir[NPDENTRIES] = {
	[0] = 0 | PTE_P | PTE_W | PTE_PS, // [ 0, 4M ) -> [ 0, 4M )
	[KERNEL_VBASE >> PDXSHIFT] = 0 | PTE_P | PTE_W | PTE_PS, // [ 0, 4M ) -> [ 0, 4M )
};

int holy_magic;

void main(void)
{
	holy_magic = 0xaabbccdd;

	while (1)
		;
}
