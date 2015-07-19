/*
 */
	.code16
	.text

	.globl _start
_start:
	movb $'h', %al
	movb $0x0E, %ah
	int $0x10

	movb $'e', %al
	movb $0x0E, %ah
	int $0x10

	movb $'l', %al
	movb $0x0E, %ah
	int $0x10

	movb $'l', %al
	movb $0x0E, %ah
	int $0x10

	movb $'o', %al
	movb $0x0E, %ah
	int $0x10
