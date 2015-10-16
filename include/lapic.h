/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#ifndef __NROS_LAPIC_H
#define __NROS_LAPIC_H

#include <common.h>
#include <types.h>

extern volatile
uint32_t *local_apic;

void lapic_init(void);

#endif /* end of include guard: __NROS_LAPIC_H */
