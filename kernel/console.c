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

void panic(const char *msg)
{
	cnsl_puts(msg);

	while (1)
		;
}

/*
 * `itos` turn `v` into human readable string form and store `sz` bytes into
 * buffer `buf`.
 *
 * Warning: `itos` **doesn't** append terminating 0!
 */
int itos(char buf[], size_t sz, int v)
{
	int i = 0, p10 = 1, tmp;

	if (v < 0) {
		buf[i++] = '-';
		v = -v;
	}

	tmp = v;
	while (tmp /= 10)
		p10 *= 10;

	while (i < sz && p10 != 0) {
		buf[i++] = v / p10 + '0';
		v %= p10;
		p10 /= 10;
	}

	return i;
}

static
int snprintf_arg(char buf[], size_t sz, const char fmt[], va_list *va)
{
	size_t sl;
	const char *vas;
	int vai;

	switch (*++fmt)
	{
	case 's':
		vas = va_arg(*va, char *);
		sl = strlen(vas);
		if (sl > sz)
			sl = sz;
		memcpy(buf, vas, sl);
		break;

	case 'd':
		vai = va_arg(*va, int);
		sl = itos(buf, sz, vai);
		break;

	case 'c':
		assert(false);
		break;

	case '\0':
	default:
		return -1;
	}

	return sl;
}

/*
 * snprintf, like Unix snprintf. '%s' for c string, and '%c' for char, '%d' for
 * decimal integer.
 */
int snprintf(char buf[], size_t sz, const char fmt[], ...)
{
	size_t i = 0;
	int rv;
	va_list va;

	va_start(va, fmt);

	while (i < sz - 1 && *fmt) {
		if (!*fmt)
			break;

		switch (*fmt)
		{
		case '%':
			rv = snprintf_arg(buf + i, sz - 1 - i, fmt, &va);
			if (rv < 0)
				return rv;
			i += rv;
			fmt += 2;
			break;

		default:
			buf[i++] = *fmt++;
			break;
		}
	}
	assert_lt(i, sz);
	buf[i] = '\0';

	va_end(va);
	return i;
}
