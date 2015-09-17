/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <ctype.h>
#include <types.h>
#include <common.h>

int islower(int c)
{
	if (c >= 'a' && c <= 'z')
		return true;

	return false;
}

int isupper(int c)
{
	if (c >= 'A' && c <= 'Z')
		return true;

	return false;
}

int isalpha(int c)
{
	return islower(c) || isupper(c);
}

int isdigit(int c)
{
	return c >= '0' && c <= '9';
}

int isalnum(int c)
{
	return isalpha(c) || isdigit(c);
}

int isspace(int c)
{
	static const char spaces[] = {
		' ', '\t', '\n', '\v', '\f', '\r'
	};

	size_t i;
	for (i = 0; i < ARRAY_LENGTH(spaces); ++i) {
		if (c == spaces[i])
			return true;
	}

	return false;
}

int tolower(int c)
{
	static const
		int d = 'a' - 'A';

	if (isupper(c))
		return c + d;
	return c;
}

int toupper(int c)
{
	static const
		int d = 'a' - 'A';

	if (islower(c))
		return c - d;
	return c;
}

#if 0

int iscntrl(int c);

int isgraph(int c);

int ispunct(int c);

int isxdigit(int c);
#endif
