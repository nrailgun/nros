/*
 * Console related IO functions & definitions.
 *
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <console.h>
#include <kpvmem.h>
#include <llops.h>

static
ushort_t *CRT = (ushort_t *) P2V(0xB8000);

static const
uint_t CRT_PORT = 0x3D4;

static const
uint_t CNSL_NROW = 25, CNSL_NCOL = 80;

static const
video_text_color_t CNSL_BG = VIDEO_TEXT_COLOR_BLACK;

static const
video_text_color_t CNSL_FG = VIDEO_TEXT_COLOR_LRED;

static
uint_t cnsl_cur_pos(void)
{
	uint_t pos;

	outb(CRT_PORT, 14);
	pos = inb(CRT_PORT + 1);
	outb(CRT_PORT, 15);
	pos = inb(CRT_PORT + 1) | (pos << 8);

	return pos;
}

static
void cnsl_set_cur_pos(uint_t pos)
{
	outb(CRT_PORT, 14);
	outb(CRT_PORT + 1, pos >> 8);
	outb(CRT_PORT, 15);
	outb(CRT_PORT + 1, pos & 0xff);
}

void cnsl_cls(void)
{
	int i, j, pos;

	for (i = 0; i < CNSL_NROW; i++) {
		for (j = 0; j < CNSL_NCOL; j++) {
			pos = i * CNSL_NCOL + j;
			CRT[pos] = (CNSL_BG << 12) | (CNSL_FG << 8) | ' ';
		}
	}
	cnsl_set_cur_pos(0);
}

void cnsl_putc(char c)
{
	uint_t pos;

	pos = cnsl_cur_pos();
	CRT[pos] = (CNSL_BG << 12) | (CNSL_FG << 8) | c;
	cnsl_set_cur_pos(++pos);
}

void panic(const char *msg)
{
	// cnsl_puts(msg, 0, 0);
	while (1)
		;
}
