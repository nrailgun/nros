/*
 * Carefully setup kernel <phys, virt> memory. Although at the very beginning
 * of NROS startup & bootloader. segmentation & paging has been roughly setup,
 * but only 4MB memory is configured and accessable.
 *
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <kpvmem.h>
#include <llops.h>
#include <memory.h>
#include <types.h>

static
pde_t *kpgdir;

struct kmemmap_s{
	void *virt;
	uint_t pstart, pend;
	int perm;
};

// TODO: kernel device space
static
struct kmemmap_s kmemmaps[] =
{
	/*
	 * [ 0, KERN_PSTART ) -> [ KERN_VBASE, KERN_VSTART ). Totally 1MB for
	 * I/O space.
	 */
	{ (void *) KERN_VBASE,	0,		KERN_PSTART,	PTE_W },

	/*
	 * [ KERN_PSTART, V2P(kdata)) -> [ KERN_VSTART, kdata ). Kernel .text
	 * & .rodata sections.
	 */
	{ (void *) KERN_VSTART,	KERN_PSTART, 	V2P(kdata), 	0 },

	/*
	 * [ V2P(kdata), KERN_PSTOP) -> [ kdata, ). Kernel .data section + R/W
	 * free memory.
	 */
	{ (void *) kdata,	V2P(kdata), 	KERN_PSTOP, 	PTE_W },

};

void kvm_alloc(void)
{
	lcr3(v2p(kpgdir));
}
