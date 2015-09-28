/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <assert.h>
#include <console.h>
#include <llops.h>
#include <string.h>
#include <types.h>

void *memset(void *dst, int c, size_t n)
{
	if (!((size_t) dst % 4) && !(n % 4)) {
		c &= 0xff;
		c = (c << 24) | (c << 16) | (c << 8) | c;
		stosl(dst, c, n / 4);
	}
	else {
		stosb(dst, c, n);
	}
	return dst;
}

// TODO: need TEST
void *memmove(void *dst, void *src, size_t n)
{
	char *ss, *sd;
	int i;

	if (src == dst || !n)
		return dst;

	ss = (char *) src;
	sd = (char *) dst;

	if (ss + n <= sd || ss > sd) { // no overlap
		i = 0;
		while (i < n) {
			sd[i] = ss[i];
			i++;
		}
	}

	else { // if (ss < sd) { // ss:ss+n overlaps sd:sd+n
		i = n - 1;
		do {
			sd[i] = ss[i];
		} while (i--);
	}

	return dst;
}

void *memcpy(void *dst, const void *src, size_t n)
{
	size_t i;
	char *cd = (char *) dst;
	const char *cs = (const char *) src;

	for (i = 0; i < n; i++) {
		cd[i] = cs[i];
	}
}

int memcmp(const void *v1, const void *v2, size_t n)
{
	uchar_t *s1, *s2;

	s1 = (uchar_t *) v1;
	s2 = (uchar_t *) v2;

	while (n--) {
		if (*s1 != *s2)
			return *s1 - *s2;
		s1++;
		s2++;
	}
}

int strlen(const char *s)
{
	size_t l = 0;

	while (*s++)
		l++;

	return l;
}

int strncmp(const char *s1, const char *s2, size_t n)
{
	while (n--) {
		if (!*s1 && !*s2)
			return 0;

		if (*s1 != *s2)
			return *s1 - *s2;

		s1++;
		s2++;
	}
	return 0;
}

int strncpy(char *dst, const char *src, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++) {
		if (!*src) {
			*dst = '\0';
			return i;
		}

		*dst++ = *src++;
	}

	assert_eq(i, n);
	return n - 1;
}
