/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <console.h>
#include <string.h>

#include "test.h"
#include "test_cnsl.h"

#ifdef CONFIG_TEST

void test_snprintf_s(void)
{
	char buf[10];
	int rv;

	rv = snprintf(buf, 10, "");
	assert_eq(rv, 0);
	assert_eq(buf[0], '\0');
	rv = strncmp(buf, "", 10);
	assert_eq(rv, 0);

	rv = snprintf(buf, 10, "100word\n");
	assert_eq(rv, 8);
	assert_eq(buf[8], '\0');
	rv = strncmp(buf, "100word\n", 10);
	assert_eq(rv, 0);

	rv = snprintf(buf, 10, "0123456789");
	assert_eq(rv, 9);
	assert_eq(buf[9], '\0');
	rv = strncmp(buf, "012345678", 10);
	assert_eq(rv, 0);

	rv = snprintf(buf, 10, "value:%s", "");
	assert_eq(rv, 6);
	assert_eq(buf[6], '\0');
	rv = strncmp(buf, "value:", 10);
	assert_eq(rv, 0);

	rv = snprintf(buf, 10, "value:%s", "Ha");
	assert_eq(rv, 8);
	assert_eq(buf[8], '\0');
	rv = strncmp(buf, "value:Ha", 10);
	assert_eq(rv, 0);

	rv = snprintf(buf, 10, "value:%s", "HaHaHa");
	assert_eq(rv, 9);
	assert_eq(buf[9], '\0');
	rv = strncmp(buf, "value:HaH", 10);
	assert_eq(rv, 0);

	rv = snprintf(buf, 10, "<%s>", "int");
	assert_eq(rv, 5);
	assert_eq(buf[5], '\0');
	rv = strncmp(buf, "<int>", 10);
	assert_eq(rv, 0);

}

void test_snprintf_d(void)
{
	char buf[5];
	int rv;

	rv = snprintf(buf, 5, "%d", 0);
	assert_eq(rv, 1);
	assert_eq(buf[1], '\0');
	rv = strncmp(buf, "0", 5);
	assert_eq(rv, 0);

	rv = snprintf(buf, 5, "%d", 10);
	assert_eq(rv, 2);
	assert_eq(buf[2], '\0');
	rv = strncmp(buf, "10", 5);
	assert_eq(rv, 0);

	rv = snprintf(buf, 5, "%d", -10);
	assert_eq(rv, 3);
	assert_eq(buf[3], '\0');
	rv = strncmp(buf, "-10", 5);
	assert_eq(rv, 0);

	rv = snprintf(buf, 5, "%dx", -10);
	assert_eq(rv, 4);
	assert_eq(buf[4], '\0');
	rv = strncmp(buf, "-10x", 5);
	assert_eq(rv, 0);

	rv = snprintf(buf, 5, "%d", 9999);
	assert_eq(rv, 4);
	assert_eq(buf[4], '\0');
	rv = strncmp(buf, "9999", 5);
	assert_eq(rv, 0);

	rv = snprintf(buf, 5, "%d", -999);
	assert_eq(rv, 4);
	assert_eq(buf[4], '\0');
	rv = strncmp(buf, "-999", 5);
	assert_eq(rv, 0);

	rv = snprintf(buf, 5, "%d", 22222);
	assert_eq(rv, 4);
	assert_eq(buf[4], '\0');
	rv = strncmp(buf, "2222", 5);
	assert_eq(rv, 0);

	rv = snprintf(buf, 5, "%d", -9999);
	assert_eq(rv, 4);
	assert_eq(buf[4], '\0');
	rv = strncmp(buf, "-999", 5);
	assert_eq(rv, 0);

	rv = snprintf(buf, 5, "%s:%d", "x", 12);
	assert_eq(rv, 4);
	assert_eq(buf[4], '\0');
	rv = strncmp(buf, "x:12", 5);
	assert_eq(rv, 0);
}

void test_snprintf(void)
{
	test_snprintf_s();
	test_snprintf_d();
}

#endif
