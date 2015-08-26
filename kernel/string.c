/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <types.h>
#include <llops.h>
#include <string.h>

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
