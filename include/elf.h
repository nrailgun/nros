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
	u32_t ei_magic;
	u8_t ei_cls;
	u8_t ei_endian;
	u8_t ei_ver;
	u8_t ei_osabi;
	u8_t ei_obiver;
	u8_t ei_pad[7];

	u16_t e_type;
	u16_t e_machine;
	u32_t e_ver;

	u32_t e_entry;
	u32_t e_phoff;
	u32_t e_shoff;
	u32_t e_flags;
	u16_t e_ehsize;
	u16_t e_phentsize;
	u16_t e_phnum;
	u16_t e_shentsize;
	u16_t e_shnum;
	u16_t e_shstrndx;
} __attribute__((packed));

typedef struct elf_hdr elf_hdr_t;

struct prog_hdr {
	u32_t p_type;
	u32_t p_off;
	u32_t p_vadr;
	u32_t p_padr;
	u32_t p_filesz;
	u32_t p_memsz;
	u32_t p_flags;
	u32_t p_align;
} __attribute__((packed));

typedef struct prog_hdr prog_hdr_t;

#endif /* end of include guard: __NROS_ELF_H */
