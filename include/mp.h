/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#ifndef __NROS_MP_H
#define __NROS_MP_H

#include <types.h>

struct mp_fp_struct_s
{
	u8_t	signature[4];	// "_MP_"
	u32_t	conf_table;	// MP config table phys addr
	u8_t	len;
	u8_t	revision;
	u8_t	chksum;
	u8_t	def_conf;
	u32_t	features;
} __attribute__((packed));

typedef struct mp_fp_struct_s mp_fp_struct_t;

struct mp_conf_table_s
{
	u8_t	signature[4];	// "PCMP"
	u16_t	len;
	u8_t	revision;
	u8_t	chksum;
	u8_t	oem_id[8];
	u8_t	prod_id[12];
	u32_t	oem_tab;
	u16_t	oem_tab_sz;
	u16_t	ent_cnt;
	u32_t	lapic_adr;	// Mem mapped addr of local APICs
	u16_t	ext_tab_len;
	u8_t	ext_tab_chksum;
	u8_t	reserved;
} __attribute__((packed));

typedef struct mp_conf_table_s mp_conf_table_t;

#endif /* end of include guard: __NROS_MP_H */
