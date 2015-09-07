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
	uint32_t ei_magic;
	uint8_t ei_cls;
	uint8_t ei_endian;
	uint8_t ei_ver;
	uint8_t ei_osabi;
	uint8_t ei_obiver;
	uint8_t ei_pad[7];

	uint16_t e_type;
	uint16_t e_machine;
	uint32_t e_ver;

	uint32_t e_entry;
	uint32_t e_phoff;
	uint32_t e_shoff;
	uint32_t e_flags;
	uint16_t e_ehsize;
	uint16_t e_phentsize;
	uint16_t e_phnum;
	uint16_t e_shentsize;
	uint16_t e_shnum;
	uint16_t e_shstrndx;
} __attribute__((packed));

typedef struct elf_hdr elf_hdr_t;

struct prog_hdr {
	uint32_t p_type;
	uint32_t p_off;
	uint32_t p_vadr;
	uint32_t p_padr;
	uint32_t p_filesz;
	uint32_t p_memsz;
	uint32_t p_flags;
	uint32_t p_align;
} __attribute__((packed));

typedef struct prog_hdr prog_hdr_t;

#endif /* end of include guard: __NROS_ELF_H */
