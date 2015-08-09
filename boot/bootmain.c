/*
 * Copyright (C) Junyu Wu, 2015.
 */

#include <types.h>
#include <memory.h>
#include <llops.h>
#include <elf.h>

#define SECTOR_SIZE 512

static
void wait_disk(void)
{
	while ((inb(0x1F7) & 0xC0) != 0x40) {
	}
}

static
void read_sector(uchar_t *p, uint_t sect)
{
	wait_disk();
	outb(0x1F2, 1); // cnt
	outb(0x1F3, sect);
	outb(0x1F4, sect >> 8);
	outb(0x1F5, sect >> 16);
	outb(0x1F6, (sect >> 24) | 0xE0);
	outb(0x1F7, 0x20); // read sector

	wait_disk();
	insl(0x1F0, p, SECTOR_SIZE / 4);
}

static void
read_seg(uchar_t *pa, uint_t cnt, uint_t off)
{
	uchar_t *epa;

	epa = pa + cnt;
	pa -= off % SECTOR_SIZE;

	off /= SECTOR_SIZE;
	for (; pa < epa; pa += SECTOR_SIZE, off++)
		read_sector(pa, off);
}

typedef void (* entry_t)(void);

void bootmain(void)
{
	elf_hdr_t *elf;
	prog_hdr_t *ph, *eph;
	uchar_t *pa;
	entry_t entry;

	elf = (elf_hdr_t *) 0x10000;
	elf->ei_magic = 0x01020304;

	read_seg((uchar_t *) elf, 4096, SECTOR_SIZE);
	if (elf->ei_magic != ELF_MAGIC) {
		elf->ei_magic = ('E' << 16) | ('R' << 8) | 'R';
		return;
	}

	ph = (prog_hdr_t *) ((char *) elf + elf->e_phoff);
	eph = ph + elf->e_phnum;
	for (; ph < eph; ph++) {
		pa = (uchar_t *) ph->p_padr;
		read_seg(pa, ph->p_filesz, ph->p_off + SECTOR_SIZE);
		if (ph->p_memsz > ph->p_filesz) {
			stosb(pa + ph->p_filesz, 0, ph->p_memsz - ph->p_filesz);
		}
	}

	entry = (entry_t) elf->e_entry;
	entry();
}
