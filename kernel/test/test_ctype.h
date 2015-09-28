/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#ifndef __NROS_TEST_CTYPE_H
#define __NROS_TEST_CTYPE_H

#ifdef CONFIG_TEST

void test_ctype(void);

#else

#define test_ctype()

#endif

#endif /* end of include guard: __NROS_TEST_CTYPE_H */
