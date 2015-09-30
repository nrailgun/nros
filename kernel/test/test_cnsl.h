/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#ifndef __NROS_TEST_CNSL_H
#define __NROS_TEST_CNSL_H

#ifdef CONFIG_TEST

void test_snprintf(void);

#else

#define test_snprintf()

#endif

#endif /* end of include guard: __NROS_TEST_CNSL_H */
