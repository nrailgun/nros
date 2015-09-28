#ifndef __NROS_TEST_H
#define __NROS_TEST_H

#include <assert.h>
#include <common.h>
#include <console.h>
#include <params.h>

#include "test_ctype.h"
#include "test_string.h"
#include "test_varg.h"

#ifdef CONFIG_TEST

void test_stage1(void);

#else

#define test_stage1()

#endif

#endif /* end of include guard: __NROS_TEST_H */
