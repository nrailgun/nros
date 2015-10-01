/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <assert.h>
#include <console.h>
#include <string.h>

void assert_fail(const char assertion[], const char file[], unsigned int line,
	const char function[])
{
	char msg[256];

	snprintf(msg, 256, "%s:%d:%s: assertion '%s' failed.\n",
		file, line, function, assertion);
	panic(msg);
}
