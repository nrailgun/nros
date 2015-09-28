/*
 * Console related IO functions & definitions.
 *
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <assert.h>
#include <console.h>
#include <kpvmem.h>
#include <llops.h>
#include <string.h>
#include <varg.h>
#include <string.h>

static
ushort_t *CRT = (ushort_t *) P2V(0xB8000);

static const
uint_t CRT_PORT = 0x3D4;

static const
uint_t CNSL_NROW = 24, CNSL_NCOL = 80;

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

	if (c == '\b' && pos > 0) {
		--pos;
		CRT[pos] = (CNSL_BG << 12) | (CNSL_FG << 8) | ' ';
	}
	else if (c == '\n') {
		pos -= pos % CNSL_NCOL;
		pos += CNSL_NCOL;
	}
	else {
		CRT[pos] = (CNSL_BG << 12) | (CNSL_FG << 8) | c;
		pos++;
	}

	if (pos >= CNSL_NROW * CNSL_NCOL) {
		memmove(CRT, CRT + CNSL_NCOL,
			sizeof(*CRT) * (CNSL_NROW - 1) * CNSL_NCOL);
		pos -= CNSL_NCOL;
		memset(CRT + pos, 0, sizeof(*CRT) * CNSL_NCOL);
	}

	cnsl_set_cur_pos(pos);
}

void cnsl_puts(const char s[])
{
	while (*s) {
		cnsl_putc(*s++);
	}
}

void printf(const char fmt[], ...)
{
	char buf[320]; // 4 lines
	va_list va;
	int rv;

	va_start(va, fmt);
	rv = vsnprintf(buf, 320, fmt, va);
	if (rv > 0)
		cnsl_puts(buf);
	va_end(va);
}

void panic(const char *msg)
{
	cnsl_puts(msg);

	while (1)
		;
}
