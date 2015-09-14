/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#ifndef __NROS_MP_H
#define __NROS_MP_H

#include <types.h>

struct mp_fp_struct_s
{
	uint8_t		signature[4];	// "_MP_"
	uint32_t	conf_table;	// MP config table phys addr
	uint8_t		len;
	uint8_t		revision;
	uint8_t		chksum;
	uint8_t		def_conf;
	uint32_t	features;
} __attribute__((packed));

typedef struct mp_fp_struct_s mp_fp_struct_t;

struct mp_conf_table_s
{
	uint8_t		signature[4];	// "PCMP"
	uint16_t	len;
	uint8_t		revision;
	uint8_t		chksum;
	uint8_t		oem_id[8];
	uint8_t		prod_id[12];
	uint32_t	oem_tab;
	uint16_t	oem_tab_sz;
	uint16_t	ent_cnt;
	uint32_t	lapic_adr;	// Memory mapped addr of local APICs
	uint16_t	ext_tab_len;
	uint8_t		ext_tab_chksum;
	uint8_t		reserved;
} __attribute__((packed));

typedef struct mp_conf_table_s mp_conf_table_t;

struct mp_proc_entry_s
{
	uint8_t		type;
	uint8_t		apic_id;
	uint8_t		apic_vers;
	uint8_t		flag;
	uint8_t		signature[4];
	uint32_t	feature_flag;
	uint32_t	reserved[2];
} __attribute__((packed));

typedef struct mp_proc_entry_s mp_proc_entry_t;

struct io_apic_entry_s
{
	uint8_t		type;	// Always 2
	uint8_t		id;
	uint8_t		vers;
	uint8_t		flag;	// Ignore on bit 0 set
	uint32_t	adr;	// Memory mapped address of IO APIC
} __attribute__((packed));

typedef struct io_apic_entry_s io_apic_entry_t;

enum {
	MP_PROC		= 0x00,
	MP_BUS		= 0x01,
	MP_IOAPIC	= 0x02,
	MP_IOINTR	= 0x03,
	MP_LINTR	= 0x04,
};

void mp_init(void);

#endif /* end of include guard: __NROS_MP_H */
