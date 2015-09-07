/*
 * Page-frame allocator. The size of page is 4096.
 *
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <common.h>
#include <console.h>
#include <errno.h>
#include <kpvmem.h>
#include <memory.h>
#include <spinlock.h>
#include <string.h>
#include <types.h>

struct frame_run_s {
	struct frame_run_s *nxt;
};

typedef struct frame_run_s frame_run_t;

struct {
	spinlock_t lock;
	bool use_lock;
	frame_run_t *free_frames;
} kmemory;

static
void free_range(void *vbeg, void *vend);

void kalloc_init(void *vbeg, void *vend)
{
	kmemory.use_lock = false;
	spinlock_init(&kmemory.lock, "kmemory");
	free_range(vbeg, vend);
}

void kfree(void *pt)
{
	frame_run_t *fr;

	if ((uint32_t) pt % PG_SIZE || (char *) pt < kend) {
		panic("kfree, frame not aligned");
	}

	memset(pt, 0, PG_SIZE);
	if (kmemory.use_lock) {
		spinlock_lock(&kmemory.lock);
	}

	fr = pt;
	fr->nxt = kmemory.free_frames;
	kmemory.free_frames = fr;

	if (kmemory.use_lock) {
		spinlock_unlock(&kmemory.lock);
	}
}

static
void free_range(void *vbeg, void *vend)
{
	uint8_t *pt;

	pt = (uint8_t *) PAGE_ROUND_UP((uint32_t) vbeg);
	for (; pt + PG_SIZE <= (uint8_t *) vend; pt += PG_SIZE) {
		kfree(pt);
	}
}

void *kalloc(void)
{
	frame_run_t *fr;

	if (kmemory.use_lock)
		spinlock_lock(&kmemory.lock);

	fr = kmemory.free_frames;
	if (!fr)
		goto kalloc_unlock;
	kmemory.free_frames = fr->nxt;

kalloc_unlock:
	if (kmemory.use_lock)
		spinlock_unlock(&kmemory.lock);

	return fr;
}
