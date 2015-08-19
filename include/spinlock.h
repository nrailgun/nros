/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#ifndef __NROS_SPINLOCK_H
#define __NROS_SPINLOCK_H

#include <types.h>

struct spinlock_s {
	const char *name;
	bool locked;
};

typedef struct spinlock_s spinlock_t;

void spinlock_init(spinlock_t *lk, const char *name);

void spinlock_destroy(spinlock_t *lk);

void spinlock_lock(spinlock_t *lk);

int spinlock_try_lock(spinlock_t *lk);

void spinlock_unlock(spinlock_t *lk);

#endif /* end of include guard: __NROS_SPINLOCK_H */
