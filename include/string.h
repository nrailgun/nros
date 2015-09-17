/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#ifndef __NROS_STRING_H
#define __NROS_STRING_H

#include <types.h>

void *memset(void *dst, int c, size_t n);

void *memmove(void *dst, void *src, size_t n);

void *memcpy(void *dst, void *src, size_t n);

int memcmp(const void *v1, const void *v2, size_t n);

#endif /* end of include guard: __NROS_STRING_H */
