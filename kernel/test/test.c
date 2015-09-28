/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include "test.h"

#ifdef CONFIG_TEST

void test_stage1(void)
{
	test_ctype();
	test_string();
	test_arglist();
}

#endif /* end ifdef CONFIG_TEST */
