/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <math.h>
#include <types.h>

uchar_t sum_uc(uchar_t a[], size_t len)
{
	size_t i;
	uchar_t sum = 0;

	for (i = 0; i < len; ++i) {
		sum += a[i];
	}
	return sum;
}
