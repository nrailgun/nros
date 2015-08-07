/*
 * Interfaces for C code to some low level operations.
 *
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#ifndef __NROS_LLOPS_H
#define __NROS_LLOPS_H

#include <types.h>

#define GCC_ASM_NEWLINE "\n\t"

static inline
uchar_t inb(ushort_t port)
{
	uchar_t c;
	
	asm volatile("in %1, %0" : "=a"(c) : "d"(port));
	return c;
}

static inline
void outb(ushort_t port, uchar_t b)
{
	asm volatile("out %0, %1" : : "a"(b), "d"(port));
}

static inline
void insl(int port, void *p, int cnt)
{
	asm volatile("cld; rep insl"
		: "=D"(p), "=c"(cnt)
		: "d"(port), "0"(p), "1"(cnt)
		: "memory", "cc");
}

#endif /* end of include guard: __NROS_LLOPS_H */
