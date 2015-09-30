/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <math.h>
#include <types.h>

int sumi(const int a[], const size_t n)
{
	int s = 0;
	size_t i;

	for (i = 0; i < n; ++i) {
		s += a[i];
	}
	return s;
}

uchar_t sumuc(const uchar_t a[], const size_t n)
{
	int s = 0;
	size_t i;

	for (i = 0; i < n; ++i) {
		s += a[i];
	}
	return s;
}
