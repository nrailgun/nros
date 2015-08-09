/*
 * Interfaces for C code to some low level operations.
 *
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#ifndef __NROS_LLOPS_H
#define __NROS_LLOPS_H

#include <types.h>

// #define GCC_ASM_NEWLINE "\n\t"

static inline
uchar_t inb(ushort_t port)
{
	uchar_t c;
	
	__asm__ __volatile__("in %1, %0" : "=a"(c) : "d"(port));
	return c;
}

static inline
void outb(ushort_t port, uchar_t b)
{
	__asm__ __volatile__("out %0, %1" : : "a"(b), "d"(port));
}

static inline
void insl(int port, void *p, int cnt)
{
	__asm__ __volatile__("cld; rep insl"
		: "=D"(p), "=c"(cnt)
		: "d"(port), "0"(p), "1"(cnt)
		: "memory", "cc");
}

static inline
void stosb(void *p, uint_t d, int cnt)
{
	__asm__ __volatile__("cld; rep stosb"
		: "=D"(p), "=c"(cnt)
		: "0"(p), "1"(cnt), "a"(d)
		: "memory", "cc");
}

static inline
void stosl(void *p, uint_t d, int cnt)
{
	__asm__ __volatile__("cld; rep stosl"
		: "=D"(p), "=c"(cnt)
		: "0"(p), "1"(cnt), "a"(d)
		: "memory", "cc");
}

#endif /* end of include guard: __NROS_LLOPS_H */
