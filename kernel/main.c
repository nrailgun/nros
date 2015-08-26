/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <common.h>
#include <console.h>
#include <errno.h>
#include <kalloc.h>
#include <kpvmem.h>
#include <kvm.h>
#include <llops.h>
#include <memory.h>
#include <spinlock.h>
#include <types.h>

__attribute__((__aligned__(PG_SIZE)))
pde_t pgdir[N_PDENT] = {
	[0] = 0 | PTE_P | PTE_W | PTE_PS, // [ 0, 4M ) -> [ 0, 4M )

	// [ 0, 4M ) -> [ 0, 4M )
	[KERN_VBASE >> PDIDX_SHFT] = 0 | PTE_P | PTE_W | PTE_PS,
};

void main(void)
{
	kalloc_init(kend, P2V(4 * 1024 * 1024));
	// kvm_alloc();

	cnsl_cls();
	cnsl_putc('H');
	cnsl_putc('e');
	cnsl_putc('l');
	cnsl_putc('l');
	cnsl_putc('o');
	// cnsl_puts("hello, world", 10, 20);

	while (1)
		;
}
