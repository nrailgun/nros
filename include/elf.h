/*
 * ELF program file related definitions. See [ Executable and Linking Format
 * (ELF) Specification ] for more details.
 *
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#ifndef __NROS_ELF_H
#define __NROS_ELF_H

#include <types.h>

#define ELF_MAGIC 0x464C457FU

struct elf_hdr {
	uint_t ei_magic;
	uchar_t ei_cls;
	uchar_t ei_endian;
	uchar_t ei_ver;
	uchar_t ei_osabi;
	uchar_t ei_obiver;
	uchar_t ei_pad[7];

	ushort_t e_type;
	ushort_t e_machine;
	uint_t e_ver;

	uint_t e_entry;
	uint_t e_phoff;
	uint_t e_shoff;
	uint_t e_flags;
	ushort_t e_ehsize;
	ushort_t e_phentsize;
	ushort_t e_phnum;
	ushort_t e_shentsize;
	ushort_t e_shnum;
	ushort_t e_shstrndx;
} __attribute__((packed));

typedef struct elf_hdr elf_hdr_t;

struct prog_hdr {
	uint_t p_type;
	uint_t p_off;
	uint_t p_vadr;
	uint_t p_padr;
	uint_t p_filesz;
	uint_t p_memsz;
	uint_t p_flags;
	uint_t p_align;
} __attribute__((packed));

typedef struct prog_hdr prog_hdr_t;

#endif /* end of include guard: __NROS_ELF_H */
