/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <assert.h>
#include <common.h>
#include <console.h>
#include <kpvmem.h>
#include <lapic.h>
#include <llops.h>
#include <math.h>
#include <mp.h>
#include <params.h>
#include <proc.h>
#include <string.h>
#include <types.h>

bool is_mp = false;

int n_cpu = 0;

uint8_t io_apic_id = 0;

static
cpu_t *boot_cpu = NULL;

cpu_t cpus[CONFIG_MAX_NCPU];

static
mp_fp_struct_t *mp_lookup_fp_struct_at(uint32_t phys, size_t len)
{
	uint8_t *a, *end, *p;
	int rv;

	a = p2v(phys);
	end = a + len;
	for (p = a; p < end; p += sizeof(mp_fp_struct_t)) {
		if (!memcmp(p, "_MP_", 4)) {
			rv = sum_uc(p, sizeof(mp_fp_struct_t));
			if (!rv)
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
	if (!mp || !mp->conf_table) {
		return NULL;
	}

	conf = (mp_conf_table_t *) p2v(mp->conf_table);
	if (memcmp(conf, "PCMP", 4)) {
		return NULL;
	}

	if (conf->revision != 1 && conf->revision != 4)
		return NULL;

	if (sum_uc((uchar_t *) conf, conf->len))
		return NULL;

	*mp_pt = mp;
	return conf;
}

void mp_init(void)
{
	mp_fp_struct_t *mp = NULL;
	mp_conf_table_t *conf = NULL;
	mp_proc_entry_t *proc = NULL;
	io_apic_entry_t *ioae = NULL;
	uint8_t *pt = NULL;

	conf = mp_lookup_conf_table(&mp);

	if (!conf)
		return;
	is_mp = true;
	local_apic = (uint32_t *) conf->lapic_adr;

	for (pt = (uint8_t *) (conf + 1); pt < (uint8_t *) conf + conf->len; ) {
		switch (*pt)
		{
		case MP_PROC:
			proc = (mp_proc_entry_t *) pt;
			if (n_cpu != proc->apic_id) {
				printf("mp_init: ncpu=%d apicid=%d\n",
					n_cpu, proc->apic_id);
				is_mp = false;
			}
			
			if (proc->flag & MP_PROC_ENTRY_FLAG_BOOT_MP)
				boot_cpu = &cpus[n_cpu];
			cpus[n_cpu].id = n_cpu;
			n_cpu++;

			pt += sizeof(mp_proc_entry_t);
			continue;

		case MP_IOAPIC:
			ioae = (io_apic_entry_t *) pt;
			io_apic_id = ioae->id;
			pt += sizeof(io_apic_entry_t);
			continue;

		case MP_BUS:
		case MP_IOINTR:
		case MP_LINTR:
			pt += 8;
			continue;

		default:
			is_mp = false;
			panic("mp_init: unknown mp config type.");
		}
	}

	if (!is_mp) {
		n_cpu = 1;
		local_apic = NULL;
		io_apic_id = 0;
		return;
	}

	/* Select IMCR, mask external interrupts */
	if (mp->features[0]) { // TODO: IMCRP?
		outb(0x22, 0x70);
		outb(0x23, inb(0x23) | 1);
	}
}
