/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include "test.h"
#include "test_math.h"

#include <common.h>
#include <math.h>
#include <types.h>

#if 0
void test_sumuc(void)
{
	char a[] = {
		1, -1, 2
	};

	uchar_t uc = sum_c(a, 3);
	assert_eq(uc, 2);

	char b[] = {
		1, 1, 2, 4
	};

	uc = sum_c(b, 4);
	assert_eq(uc, 8);
}
#endif
