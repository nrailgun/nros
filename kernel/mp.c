/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <common.h>
#include <mp.h>
#include <types.h>
#include <kpvmem.h>
#include <string.h>

static
mp_fp_struct_t *mp_lookup_fp_struct_at(uint32_t *phys, size_t len)
{
	uchar_t *a, *end, *p;

	a = p2v(phys);
	end = a + len;
	for (p = a; p < end; p += sizeof(mp_fp_struct_t)) {
		// TODO: memcpy, sum
	}
}

static
mp_fp_struct_t *mp_lookup_fp_struct(void)
{
	uchar_t *bda = (uchar_t *) P2V(0x400); // BIOS Data Area
	uint32_t p;

	p = (bda[0x0f] << 8) | bda[0x0e];
	p <<= 4;

	/* BIOS ROM [ 0xE0000, 0xFFFFF ] */
	return mp_lookup_fp_struct_at(0xf0000, 0x10000);
}

static
mp_conf_table_t *mp_lookup_conf_table(mp_fp_struct_t **mp_pt)
{
	mp_fp_struct_t *mp;
	mp_conf_table_t *conf;

	mp = mp_lookup_fp_struct();
	if (!mp || !mp->conf_table)
		return NULL;
}

void mp_init(void)
{
	mp_fp_struct_t *mp;
	mp_conf_table_t *conftab;

	conftab = mp_lookup_conf_table(&mp);
	if (!conftab)
		return;
}
