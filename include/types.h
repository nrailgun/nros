/*
 * Copyright (C) Junyu Wu, 2015.
 */

#ifndef __NROS_TYPE_H
#define __NROS_TYPE_H

typedef unsigned char uint8_t;

typedef unsigned short uint16_t;

typedef unsigned int uint32_t;

typedef unsigned char uchar_t;

typedef unsigned short ushort_t;

typedef unsigned int uint_t;

typedef enum bool_e {
	false = 0, true = 1,
} bool;

typedef uint32_t pde_t;

typedef uint32_t pte_t;

typedef long unsigned int size_t;

typedef long int ptrdiff_t;

#endif /* end of include guard: __NROS_TYPE_H */
