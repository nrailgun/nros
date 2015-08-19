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

__attribute__((__aligned__(PGSIZE)))
pde_t pgdir[NPDENTRIES] = {
	[0] = 0 | PTE_P | PTE_W | PTE_PS, // [ 0, 4M ) -> [ 0, 4M )

	// [ 0, 4M ) -> [ 0, 4M )
	[KERN_VBASE >> PDXSHIFT] = 0 | PTE_P | PTE_W | PTE_PS,
};

void main(void)
{
	spinlock_t lk;
	int i;

	spinlock_init(&lk, "testlock");
	spinlock_lock(&lk);
	i = spinlock_try_lock(&lk);
	if (i == -EBUSY)
		cnsl_puts("Good", 10, 20);
	else
		cnsl_puts("Bad", 10, 20);

	spinlock_unlock(&lk);
	i = spinlock_try_lock(&lk);
	if (i != -EBUSY)
		cnsl_puts("Good", 11, 20);
	else
		cnsl_puts("Bad", 11, 20);

	spinlock_destroy(&lk);
	cnsl_puts("It's End", 12, 20);

	while (1)
		;
}
