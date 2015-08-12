/*
 * Console related IO functions & definitions.
 *
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#ifndef __NROS_CONSOLE_H
#define __NROS_CONSOLE_H

#include <types.h>

enum video_type_e {
	VIDEO_TYPE_NONE       = 0x00,
	VIDEO_TYPE_COLOR      = 0x20,
	VIDEO_TYPE_MONOCHROME = 0x30,
};

typedef enum video_type_e video_type_t;

enum video_text_color_e {
	VIDEO_TEXT_COLOR_BLACK = 0x00,
	VIDEO_TEXT_COLOR_BLUE  = 0x07,
	VIDEO_TEXT_COLOR_LGRAY = 0x07,
	VIDEO_TEXT_COLOR_LRED  = 0x0C,
};

typedef enum video_text_color_e video_text_color_t;

void cnsl_putc(uchar_t c, uint_t row, uint_t col,
	video_text_color_t bg, video_text_color_t fg);

void cnsl_puts(uchar_t s[], uint_t row, uint_t col);

#endif /* end of include guard: __NROS_CONSOLE_H */
