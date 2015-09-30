/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <assert.h>
#include <common.h>
#include <mp.h>
#include <types.h>
#include <kpvmem.h>
#include <string.h>
#include <console.h>

static
mp_fp_struct_t *mp_lookup_fp_struct_at(uint32_t phys, size_t len)
{
	uint8_t *a, *end, *p;

	a = p2v(phys);
	end = a + len;
	for (p = a; p < end; p += sizeof(mp_fp_struct_t)) {
		if (0 == memcmp(p, "_MP_", 4) && 0 == sumuc(p, sizeof(mp_fp_struct_t))) {
			printf("HAHA\n");
			return (mp_fp_struct_t *) p;
		}
	}
	return NULL;
}

static
mp_fp_struct_t *mp_lookup_fp_struct(void)
{
	uint8_t *bda = (uint8_t *) P2V(0x400); // BIOS Data Area
	uint32_t p;
	mp_fp_struct_t *mp = NULL;

	p = ((bda[0x0f] << 8) | bda[0x0e]) << 4;
	if (p) {
		/* EBDA 1st KB */
		mp = mp_lookup_fp_struct_at(p, 1024);
		if (mp) {
			return mp;
		}
	}
	else {
		/* Last KB of system base memory */
		p = (bda[0x14] << 8) | bda[0x13];
		p = (p << 10) - 1024;
		mp = mp_lookup_fp_struct_at(p, 1024);
		if (mp) {
			return mp;
		}
	}

	/* BIOS ROM [ 0xE0000, 0xFFFFF ] */
	return mp_lookup_fp_struct_at(0xf0000, 0x10000);
}

static
mp_conf_table_t *mp_lookup_conf_table(mp_fp_struct_t **mp_pt)
{
	mp_fp_struct_t *mp;
	mp_conf_table_t *conf;

	mp = mp_lookup_fp_struct();
	assert(mp);
	printf("%x\n", mp);
	//if (!mp || !mp->conf_table) {
	//	return NULL;
	//}

	// conf = (mp_conf_table_t *) p2v(mp->conf_table);
	// printf("%x\n", mp);
	// if (memcmp(conf, "PCMP", 4) != 0) {
	// 	return 0;
	// }
}

void mp_init(void)
{
	mp_fp_struct_t *mp;
	mp_conf_table_t *conftab;

	conftab = mp_lookup_conf_table(&mp);
	//if (!conftab)
	//	return;
}
