/*
 * Bootloader for nros.
 *
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <memory.h>
#include <params.h>
	.code16
	.text
	.globl start
	.type start, @function
start:
	cli

# init registers
	xorw	%ax, %ax
	movw	%ax, %ds
	movw	%ax, %es
	movw	%ax, %ss

#ifdef CONFIG_LOADING_MSG
	movb	$0x03, %ah
	xor	%bh, %bh
	int	$0x10 # read cursor

	movw	$0x1301, %ax
	movw	$msgl, %cx
	movw	$0x07, %bx
	movw	$msg, %bp
	int	$0x10 # write string, move cursor
#endif

# enable a20
enable_a20.1:
	inb	$0x64, %al
	testb	$0x2, %al
	jnz	enable_a20.1

	movb	$0xd1, %al
	outb	%al, $0x64

enable_a20.2:
	inb	$0x64, %al
	testb	$0x2, %al
	jnz	enable_a20.2

	movb	$0xdf, %al
	outb	%al, $0x60

# switch to protected mode
load_gdt:
	lgdt	gdt_info
	movw	$CR0_PE, %ax
	lmsw	%ax
	ljmp	$(SEG_KCODE<<3), $start32

	.code32
# 32-bit boot code
start32:
	# init protected mode registers
	movw	$(SEG_KDATA<<3), %ax
	movw	%ax, %ds
	movw	%ax, %es
	movw	%ax, %ss
	xorw	%ax, %ax
	movw	%ax, %fs
	movw	%ax, %gs

	# maybe not a great idea to set esp=0x7c00, may harm the ivt
	movl	$start, %esp
	call	bootmain

die:
	hlt
die_hang: # in case `hlt' failed
	jmp	die_hang

	.code16
.p2align 2
gdt:
	SEG_NULL_ASM
	SEG_ASM(STA_X|\
		STA_R, 0, 0xffffffff)	# code seg
	SEG_ASM(STA_W, 0, 0xffffffff)	# data seg

gdt_info:
	.word (gdt_info - gdt - 1)
	.long gdt

#ifdef CONFIG_LOADING_MSG
msg:
	.ascii	"Loading os....\n\r"
	msgl = . - msg
#endif
