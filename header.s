	.code16
	.text
	.globl _start
	.type _start, @function
_start:
	movw $buf, %si
1:
	cmp $0x00, (%si)
	je 1f

	movb (%si), %al
	movb $0x0E, %ah
	int $0x10

	inc %si
	jmp 1b

1:
	movb $'%', %al
	movb $0x0E, %ah
	int $0x10
	hlt

	.data
buf:
	.asciz "hello, world"
