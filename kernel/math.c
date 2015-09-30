/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <math.h>
#include <types.h>

int sum_i(const int a[], const size_t n)
{
	int s = 0;
	size_t i;

	for (i = 0; i < n; ++i) {
		s += a[i];
	}
	return s;
}

uchar_t
getsum(uchar_t *addr, int len)
{
  int i, sum;
  
  sum = 0;
  for(i=0; i<len; i++)
    sum += addr[i];
  return sum;
}

uchar_t sum_c(const uchar_t *a, const int n)
{
	int i, s = 0;

	for (i = 0; i < n; ++i) {
		s += a[i];
	}
	return s;
}
