/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <varg.h>
#include <assert.h>
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
#include <mp.h>

#include "test/test.h"
#include "test/test_ctype.h"
#include "test/test_string.h"
#include "test/test_varg.h"
#include "test/test_cnsl.h"

__attribute__((__aligned__(PG_SIZE)))
pde_t pgdir[N_PDENT] = {
	[0] = 0 | PTE_P | PTE_W | PTE_PS, // [ 0, 4M ) -> [ 0, 4M )

	// [ 0, 4M ) -> [ 0, 4M )
	[KERN_VBASE >> PDIDX_SHFT] = 0 | PTE_P | PTE_W | PTE_PS,
};

int main(void)
{
	cnsl_cls();
	cnsl_puts("NROS booting...\n");

	kalloc_init(kend, P2V(4 * 1024 * 1024));
	kvm_setup();

	mp_init();

	cnsl_puts("NROS booting done...\n");
	while (1)
		;
}
