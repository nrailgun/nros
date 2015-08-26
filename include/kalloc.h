/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <common.h>
#include <errno.h>
#include <spinlock.h>
#include <types.h>
#include <memory.h>
#include <string.h>

void kalloc_init(void *vbeg, void *vend);

void kfree(void *p);

void *kalloc(void);
