/*
 * Commonly used macros, definitions, and functions.
 *
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#ifndef __NROS_COMMON_H
#define __NROS_COMMON_H

#include <types.h>

#define NULL ((void *) 0)

#define ARRAY_LENGTH(a) (sizeof(a) / sizeof(*a))

#define ROUND_UP(a, b) (((a) + b - 1) & ~(b - 1))

#define ROUND_DOWN(a, b) ((a) & ~(b - 1))

#endif /* end of include guard: __NROS_COMMON_H */
