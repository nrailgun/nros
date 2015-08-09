/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <types.h>

static
int holy_magic = 0x100;

void main(void)
{
	holy_magic = 0xabcd;

	while (1) ;
}
