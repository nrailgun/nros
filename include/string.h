/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#ifndef __NROS_STRING_H
#define __NROS_STRING_H

#include <types.h>
#include <llops.h>
#include <console.h>

static inline
void *memset(void *dst, int c, uint_t n)
{
	if (!((uint_t) dst % 4) && !(n % 4)) {
		c &= 0xff;
		c = (c << 24) | (c << 16) | (c << 8) | c;
		stosl(dst, c, n / 4);
	}
	else {
		stosb(dst, c, n);
	}
	return dst;
}

#endif /* end of include guard: __NROS_STRING_H */
