/*
 * Console related IO functions & definitions.
 *
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <console.h>

#define VIDEO_MEMORY_TEXT	0xB8000
#define VIDEO_MEMORY_TEXT_NROW	25
#define VIDEO_MEMORY_TEXT_NCOL	80

/*
 * Write charater `c' to text mode video memory, with foreground color `fg' and
 * background color `bg', at row `row', col `col'. It's user's duty to ensure
 * `row''s and `col''s validity.
 */
void cnsl_putc(uchar_t c, uint_t row, uint_t col,
	video_text_color_t bg, video_text_color_t fg)
{
	ushort_t *m, u;
	
	m = (ushort_t *) VIDEO_MEMORY_TEXT + VIDEO_MEMORY_TEXT_NCOL * row + col;
	u = (bg << 12) | (fg << 8) | c;
	*m = u;
}

void cnsl_puts(uchar_t s[], uint_t row, uint_t col)
{
	// Trick: col >= 80 won't harm
	for (; *s; s++) {
		cnsl_putc(*s, row, col++,
			VIDEO_TEXT_COLOR_BLACK, VIDEO_TEXT_COLOR_LRED);
	}
}
