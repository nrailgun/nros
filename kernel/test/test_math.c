/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include "test.h"
#include "test_math.h"

#include <common.h>
#include <math.h>
#include <types.h>

void test_sum_c(void)
{
	uchar_t a[] = {
		1, -1, 2
	};

	uchar_t uc = sum_uc(a, 3);
	assert_eq(uc, 2);

	uchar_t b[] = {
		1, 1, 2, 4
	};

	uc = sum_uc(b, 4);
	assert_eq(uc, 8);
}
