/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#ifndef __NROS_TEST_VARG_H
#define __NROS_TEST_VARG_H

#ifdef CONFIG_TEST

void test_arglist(void);

#else

#define test_arglist()

#endif

#endif /* end of include guard: __NROS_TEST_VARG_H */
