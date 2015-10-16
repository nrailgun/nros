/*
 * Carefully setup kernel <phys, virt> memory. Although at the very beginning
 * of NROS startup & bootloader. segmentation & paging has been roughly setup,
 * but only 4MB memory is configured and accessable.
 *
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <kpvmem.h>
#include <common.h>
#include <errno.h>
#include <kalloc.h>
#include <llops.h>
#include <memory.h>
#include <types.h>
#include <memory.h>
#include <console.h>

static
pde_t *kpgdir;

struct kmem_map_s {
	void *virt_adr;
	uint32_t phys_adr, phys_stop;
	int perm;
};

static
struct kmem_map_s kmmaps[] =
{
	/*
	 * [ 0, KERN_PSTART ) -> [ KERN_VBASE, KERN_VSTART ). Totally 1MB for
	 * I/O space.
	 */
	{ (void *) KERN_VBASE, 0, KERN_PSTART, PTE_W },

	/*
	 * [ KERN_PSTART, V2P(kdata)) -> [ KERN_VSTART, kdata ). Kernel .text
	 * & .rodata sections.
	 */
	{ (void *) KERN_VSTART, KERN_PSTART, V2P(kdata), 0 },

	/*
	 * [ V2P(kdata), KERN_PSTOP) -> [ kdata, ). Kernel .data section + R/W
	 * free memory.
	 */
	{ (void *) kdata, V2P(kdata), KERN_PSTOP, PTE_W },

	/*
	 * [ DEV_SPACE, 0xffffffff ). Device Space, direct map (such as ioapic).
	 */
	{ (void *) DEV_SPACE, DEV_SPACE, 0xffffffff, PTE_W },
};

static
pte_t *find_pte(pde_t *pd, const void *a, bool new)
{
	pde_t *pde;
	pte_t *pgtab;

	pde = &pd[PDIDX(a)];

	if (*pde & PTE_P) {
		pgtab = (pte_t *) p2v(PTE_ADDR(*pde));
	}
	else {
		if (!new)
			return NULL;

		pgtab = (pte_t *) kalloc();
		if (!pgtab)
			return NULL;
		memset(pgtab, 0, PG_SIZE);
		/*
		 * v2p(pgtab) & ~0xfff has been implied. By the way, I don't
		 * know if it is a good idea to give this much previlege.
		 */
		*pde = v2p(pgtab) | PTE_P | PTE_W | PTE_U;
	}

	return &pgtab[PTIDX(a)];
}

static
int map_pages(struct kmem_map_s *kmm)
{
	uint8_t *v, *vbeg, *vend;
	uint32_t sz, pbeg;
	pte_t *pte;

	v = kmm->virt_adr;
	sz = kmm->phys_stop - kmm->phys_adr;
	pbeg = kmm->phys_adr;
	vbeg = (uint8_t *) PAGE_ROUND_UP((uint32_t) v);
	vend = (uint8_t *) PAGE_ROUND_DOWN((uint32_t) v + sz);

	while (vbeg < vend) {
		pte = find_pte(kpgdir, vbeg, true);
		if (*pte & PTE_P) {
			panic("pgtab entry remap");
		}
		*pte = pbeg | kmm->perm | PTE_P;

		vbeg += PG_SIZE;
		pbeg += PG_SIZE;
	}

	return 0;
}

static
pde_t *kvm_alloc(void)
{
	int i, rv;
	struct kmem_map_s *kmm;

	kpgdir = (pde_t *) kalloc();
	if (!kpgdir)
		return NULL;

	memset(kpgdir, 0, PG_SIZE);
	for (i = 0; i < ARRAY_LENGTH(kmmaps); i++) {
		kmm = &kmmaps[i];
		rv = map_pages(kmm);
		if (rv) {
			panic("failed to set up kernel memory map");
		}
	}
	return kpgdir;
}

void kvm_setup(void)
{
	kpgdir = kvm_alloc();
	lcr3(v2p(kpgdir));
}
