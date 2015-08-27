/*
 * NROS kernel memory layout related definitions, and tools
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

#define KERN_PSTART 0x100000
#define KERN_PSTOP 0xE000000

#define KERN_VBASE 0x80000000
#define KERN_VSTART (KERN_VBASE + KERN_PSTART)

#define KSTACK_SIZE CONFIG_KSTACKSIZE

#ifndef __ASSEMBLER__

extern char kdata[]; // Kernel data

extern char ekdata[]; // End of kernel data

extern char kend[]; // End of kernel

#endif /* ifndef __ASSEMBLER__ */

#define V2P_S(a) ((a) - KERN_VBASE)
#define P2V_S(a) ((a) + KERN_VBASE)

#ifndef __ASSEMBLER__

#define V2P(a) (((u32_t) (a)) - KERN_VBASE)
#define P2V(a) ((void *) ((u8_t *) (a) + KERN_VBASE))

static inline
u32_t v2p(void *a) {
	return (u32_t) a - KERN_VBASE;
}

static inline
void *p2v(u32_t a) {
	return (void *) a + KERN_VBASE;
}

#endif /* ifndef __ASSEMBLER__ */

#endif /* end of include guard: __NROS_KPVMEM_H */
