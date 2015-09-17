/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <common.h>
#include <console.h>
#include <ctype.h>
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

static test_ctype(void)
{
	char c;
	c = 'A';
	c = tolower(c);
	cnsl_putc(c);
	c = 'a';
	c = tolower(c);
	cnsl_putc(c);

	c = 'A';
	c = toupper(c);
	cnsl_putc(c);
	c = 'a';
	c = toupper(c);
	cnsl_putc(c);

	cnsl_puts("\n");
}

void main(void)
{
	cnsl_cls();
	cnsl_puts("NROS booting...\n");

	kalloc_init(kend, P2V(4 * 1024 * 1024));
	kvm_setup();

	cnsl_puts("Init multi-processor...\n");
	mp_init();

	test_ctype();

	cnsl_puts("NROS booting done...\n");

	while (1)
		;
}
