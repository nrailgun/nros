/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <types.h>
#include <llops.h>
#include <string.h>

void *memset(void *dst, int c, uint_t n)
{
	if (!((uint_t) dst % 4) && !(n % 4)) {
		c &= 0xff;
		c = (c << 24) | (c << 16) | (c << 8) | c;
		stosl(dst, c, n / 4);
	}
	else {
		stosb(dst, c, n);
	}
	return dst;
}

void *memmove(void *dst, void *src, uint_t n)
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
