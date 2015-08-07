/*
 * Copyright (C) Junyu Wu, 2015.
 */

#include <types.h>
#include <memory.h>
#include <llops.h>

#define SECTOR_SIZE 512

static
void wait_disk(void)
{
	while ((inb(0x1F7) & 0xC0) != 0x40) {
	}
}

static
void read_sectors(uchar_t *p, uint_t off)
{
	wait_disk();
	outb(0x1F2, 1); // cnt
	outb(0x1F3, off);
	outb(0x1F4, off >> 8);
	outb(0x1F5, off >> 16);
	outb(0x1F6, (off >> 24) | 0xE0);
	outb(0x1F7, 0x20); // read sector

	wait_disk();
	insl(0x1F0, p, SECTOR_SIZE / 4);
}

void bootmain(void)
{
	read_sectors((uchar_t *) 0x10000, 1);
}
