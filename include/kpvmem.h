/*
 * Nros kernel memory layout related definitions, and tools
 * to convert phisical / virtual memory.
 *
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#ifndef __NROS_KPVMEM_H
#define __NROS_KPVMEM_H

#include <params.h>

#ifndef __ASSEMBLER__

#include <types.h>

#endif /* ifndef __ASSEMBLER__ */

#define KERN_PBASE 0x100000

#define KERN_VBASE 0x80000000
#define KERN_VLINK (KERNEL_BASE + KERN_PBASE)

#define KSTACK_SIZE CONFIG_KSTACKSIZE

#define V2P_S(a) ((a) - KERN_VBASE)
#define P2V_S(a) ((a) + KERN_VBASE)

#ifndef __ASSEMBLER__

static inline
uint_t v2p(void *a) {
	return (uint_t) a - KERN_VBASE;
}

static inline
void *p2v(uint_t a) {
	return (void *) a + KERN_VBASE;
}

#endif /* ifndef __ASSEMBLER__ */

#endif /* end of include guard: __NROS_KPVMEM_H */
