/*
 * Copyright (C) Junyu Wu, 2015.
 */

#ifndef __NROS_TYPE_H
#define __NROS_TYPE_H

typedef unsigned char u8_t;

typedef unsigned short u16_t;

typedef unsigned int u32_t;

typedef unsigned char uchar_t;

typedef unsigned short ushort_t;

typedef unsigned int uint_t;

typedef enum bool_e {
	false = 0, true = 1,
} bool;

typedef u32_t pde_t;

typedef u32_t pte_t;

#endif /* end of include guard: __NROS_TYPE_H */
