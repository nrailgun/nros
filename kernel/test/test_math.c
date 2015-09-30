/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include "test.h"
#include "test_math.h"

#include <common.h>
#include <math.h>
#include <types.h>

void test_sumuc(void)
{
	char a[] = {
		1, -1, 2
	};

	uchar_t uc = sumuc(a, 3);
	assert_eq(uc, 2);

	char b[] = {
		1, 1, 2, 4
	};

	uc = sumuc(b, 4);
	assert_eq(uc, 8);
}
