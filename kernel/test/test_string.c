/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <string.h>

#include "test.h"
#include "test_string.h"

#ifdef CONFIG_TEST

/*
 * Cautious: Kernel Data Area are not writable. See kvm.c for details.
 */
void test_string(void)
{
	char *s, *s1, *s2;
	size_t l;
	int rv;

	s = "hello";
	l = strlen(s);
	assert_eq(l, 5);

	s = "";
	l = strlen(s);
	assert_eq(l, 0);

	s = "!";
	l = strlen(s);
	assert_eq(l, 1);

	s1 = "hello";
	s2 = "hello";

	rv = strncmp(s1, s2, 5);
	assert_eq(rv, 0);

	rv = strncmp(s1, s2, 4);
	assert_eq(rv, 0);

	rv = strncmp(s1, s2, 1);
	assert_eq(rv, 0);

	rv = strncmp(s1, s2, 0);
	assert_eq(rv, 0);

	s1 = "hello";
	s2 = "helxo";

	rv = strncmp(s1, s2, 5);
	assert_ne(rv, 0);

	rv = strncmp(s1, s2, 4);
	assert_ne(rv, 0);

	rv = strncmp(s1, s2, 1);
	assert_eq(rv, 0);

	rv = strncmp(s1, s2, 0);
	assert_eq(rv, 0);

	s1 = "h";
	s2 = "h";

	rv = strncmp(s1, s2, 10);
	assert_eq(rv, 0);

	s1 = "h";
	s2 = "x";

	rv = strncmp(s1, s2, 10);
	assert_ne(rv, 0);

	s1 = "";
	s2 = "";

	rv = strncmp(s1, s2, 10);
	assert_eq(rv, 0);

	char a1[] = "0123456789";
	char a2[] = "hello";

	rv = strncpy(a1, a2, 0);
	assert_eq(strncmp(a1, "0123456789", 11), 0);
	assert_eq(strncmp(a2, "hello", 6), 0);

	rv = strncpy(a1, a2, 10);
	assert_eq(strncmp(a1, a2, 6), 0);
	assert_eq(strncmp(a1, a2, 5), 0);
	assert_eq(strncmp(a1, "hello", 6), 0);
	assert_eq(strncmp(a2, "hello", 6), 0);

	char a3[] = "xxxxxx";
	rv = strncpy(a1, a3, 2);
	assert_eq(strncmp(a1, a3, 2), 0);
	assert_ne(strncmp(a1, a3, 3), 0);
}

void test_memcmp(void)
{
	int a[] = { 1, 4, -5 };
	int b[] = { 1, 4, -5 };
	int c[] = { 1, 4, -4 };

	int rv;

	assert(sizeof(a) == sizeof(b));
	assert(sizeof(a) == sizeof(c));

	rv = memcmp(a, b, sizeof(a));
	assert_eq(rv, 0);

	rv = memcmp(a, c, sizeof(a));
	assert_ne(rv, 0);

	rv = memcmp(a, b, 8);
	assert_eq(rv, 0);

	rv = memcmp(a, c, 8);
	assert_eq(rv, 0);

	char d[] = "hello";
	char e[] = "hexlo";
	rv = memcmp(d, e, 2);
	assert_eq(rv, 0);

	rv = memcmp(d, e, 4);
	assert_ne(rv, 0);
}

#endif
