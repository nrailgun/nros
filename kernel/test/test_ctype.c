/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <ctype.h>

#include "test.h"
#include "test_ctype.h"

#ifdef CONFIG_TEST

void test_ctype(void)
{
	char c;
	c = 'A';
	c = tolower(c);
	assert_eq(c, 'a');

	c = 'a';
	c = tolower(c);
	assert_eq(c, 'a');

	c = 'A';
	c = toupper(c);
	assert_eq(c, 'A');

	c = 'a';
	c = toupper(c);
	assert_eq(c, 'A');
}

#endif
