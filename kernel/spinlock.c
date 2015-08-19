/*
 * Spin lock. Still stub now, implemented buggy.
 *
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <comm.h>
#include <errn.h>
#include <spinlock.h>

void spinlock_init(spinlock_t *lk, const char *name)
{
	lk->name = name;
	lk->locked = false;
}

void spinlock_destroy(spinlock_t *lk)
{
	lk->name = NULL;
}

void spinlock_lock(spinlock_t *lk)
{
	while (lk->locked)
		;
	lk->locked = true;
}

int spinlock_try_lock(spinlock_t *lk)
{
	switch (lk->locked)
	{
	case true:
		return -EBUSY;
	case false:
		spinlock_lock(lk);
		return 0;
	default:
		return -EINVAL;
	}
}

void spinlock_unlock(spinlock_t *lk)
{
	lk->locked = false;
}
