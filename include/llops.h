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
uint8_t inb(uint16_t port)
{
	uint8_t c;
	
	__asm__ __volatile__("in %1, %0" : "=a"(c) : "d"(port));
	return c;
}

static inline
void outb(uint16_t port, uint8_t b)
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
void stosb(void *p, uint32_t d, int cnt)
{
	__asm__ __volatile__("cld; rep stosb"
		: "=D"(p), "=c"(cnt)
		: "0"(p), "1"(cnt), "a"(d)
		: "memory", "cc");
}

static inline
void stosl(void *p, uint32_t d, int cnt)
{
	__asm__ __volatile__("cld; rep stosl"
		: "=D"(p), "=c"(cnt)
		: "0"(p), "1"(cnt), "a"(d)
		: "memory", "cc");
}

static inline
void lcr3(uint32_t pgdir)
{
	__asm__ __volatile__ ("movl %0, %%cr3"
		:
		: "r"(pgdir)
		);
}

#endif /* end of include guard: __NROS_LLOPS_H */
