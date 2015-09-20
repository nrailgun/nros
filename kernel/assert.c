/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <assert.h>
#include <console.h>

void assert_fail(const char assertion[], const char file[], unsigned int line,
	const char function[])
{
	panic("Assertion failed!\n");
}
