/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <varg.h>
#include <assert.h>
#include <common.h>
#include <console.h>
#include <ctype.h>
#include <errno.h>
#include <kalloc.h>
#include <kpvmem.h>
#include <kvm.h>
#include <llops.h>
#include <memory.h>
#include <spinlock.h>
#include <types.h>

__attribute__((__aligned__(PG_SIZE)))
pde_t pgdir[N_PDENT] = {
	[0] = 0 | PTE_P | PTE_W | PTE_PS, // [ 0, 4M ) -> [ 0, 4M )

	// [ 0, 4M ) -> [ 0, 4M )
	[KERN_VBASE >> PDIDX_SHFT] = 0 | PTE_P | PTE_W | PTE_PS,
};

static test_ctype(void)
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

/*
 * Cautious: Kernel Data Area are not writable. See kvm.c for details.
 */
static test_string(void)
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

void _test_arglist(void *bar, ...)
{
	va_list v;
	int a;

	va_start(v, bar);

	a = va_arg(v, int);
	assert_eq(a, 0xDEAD);

	a = va_arg(v, int);
	assert_eq(a, 1234);

	a = va_arg(v, int);
	assert_eq(a, 'c');

	va_end(v);
}

void test_arglist(void)
{
	_test_arglist(NULL, 0xDEAD, 1234, 'c');
}

void main(void)
{
	cnsl_cls();
	cnsl_puts("NROS booting...\n");

	kalloc_init(kend, P2V(4 * 1024 * 1024));
	kvm_setup();

	// cnsl_puts("Init multi-processor...\n");
	mp_init();

	test_ctype();
	test_string();
	test_arglist();

	cnsl_puts("NROS booting done...\n");

	while (1)
		;
}
