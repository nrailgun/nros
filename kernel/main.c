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
	cnsl_cls();
	cnsl_puts("NROS booting...\n");

	cnsl_puts("allocating frames...\n");
	kalloc_init(kend, P2V(4 * 1024 * 1024));

	cnsl_puts("carefully paging...\n");
	kvm_setup();

	mp_init();

	char msg[] =
		"NROS booting done...\n";
	cnsl_puts(msg);

	while (1)
		;
}
