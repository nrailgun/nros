/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#ifndef __NROS_TEST_STRING_H
#define __NROS_TEST_STRING_H

#ifdef CONFIG_TEST

void test_string(void);

void test_memcmp(void);

#else

#define test_string()

#endif

#endif /* end of include guard: __NROS_TEST_STRING_H */
