/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#ifndef __NROS_TEST_MP_H
#define __NROS_TEST_MP_H

#ifdef CONFIG_TEST

void test_mp_init(void);

#else

#define test_mp_init()

#endif

#endif /* end of include guard: __NROS_TEST_MP_H */
