/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <varg.h>

#include "test.h"
#include "test_varg.h"

static
void _test_arglist(void *bar, ...)
{
	va_list v;
	int a;

	va_start(v, bar);

	a = va_arg(v, int);
	assert_eq(a, 0xDEAD);

	a = va_arg(v, int);
	assert_eq(a, 1234);

	a = va_arg(v, int);
	assert_eq(a, 'c');

	va_end(v);
}

void test_arglist(void)
{
	_test_arglist(NULL, 0xDEAD, 1234, 'c');
}
