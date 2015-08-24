/*
 * Nros kernel entry. After enabling paging and protected mode, jump
 * to main().
 *
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <kpvmem.h>
#include <memory.h>
#include <params.h>
	.text
	.globl	kstart
	.type	kstart, @function
kstart = V2P_S(_kstart)

	.globl	_kstart
	.type	_kstart, @function
_kstart:
	# page size extension
	movl	%cr4, %eax
	orl	$CR4_PSE, %eax
	movl	%eax, %cr4

	# set page dir
	movl	$(V2P_S(pgdir)), %eax
	movl	%eax, %cr3

	# turn on paging
	movl	%cr0, %eax
	orl	$(CR0_PG|CR0_WP), %eax
	movl	%eax, %cr0

	# Set stack pointer and jump to main, continue executing at high
	# address. Documents say that indirect call is necessary, but I found
	# not.
	movl	$(kstack + KSTACK_SIZE), %esp
	movl	$main, %eax
	jmp	*%eax

# kernel stack
	.comm	kstack, KSTACK_SIZE
