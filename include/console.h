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

void panic(const char *msg) __attribute__((noreturn));

void cnsl_cls(void);

void cnsl_putc(char c);

void cnsl_puts(const char s[]);

void printf(const char fmt[], ...);

#endif /* end of include guard: __NROS_CONSOLE_H */
