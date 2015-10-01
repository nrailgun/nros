/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#ifndef __NROS_STRING_H
#define __NROS_STRING_H

#include <types.h>
#include <varg.h>

void *memset(void *dst, int c, size_t n);

void *memmove(void *dst, void *src, size_t n);

void *memcpy(void *dst, const void *src, size_t n);

int memcmp(const void *v1, const void *v2, size_t n);

int strlen(const char *s);

int strncmp(const char *s1, const char *s2, size_t n);

/*
 * Copy at most n bytes from `src' to `dst'.
 *
 * Warning: If '\0' doesn't appears in first `n' bytes in `src', `dst' won't be
 * 0 terminated.
 */
int strncpy(char *dst, const char *src, size_t n);

int vsnprintf(char buf[], size_t sz, const char fmt[], va_list va);

int snprintf(char buf[], size_t sz, const char fmt[], ...);

#endif /* end of include guard: __NROS_STRING_H */
