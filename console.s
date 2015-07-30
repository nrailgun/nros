	.text
	.globl cls
	.type cls, @function
cls:
	movw $0x0600, %ax
	movb $0x07, %bh
	movw $0x0000, %cx
	movw $0x184F, %dx
	int $0x10

	.globl set_cursor
	.type set_cursor, @function
set_cursor:
	movb $0x02, %ah
	movb $0x00, %bh
	movb $15, %dh
	movb $25, %dl
	int $0x10

	.globl putchar
	.type putchar, @function
putchar:
	movb $'A', %al
	movb $0x0e, %ah
	int $0x10
