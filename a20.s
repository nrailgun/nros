# Author: Junyu Wu

check_a20:
	movw $0x0, %ax
	movw %ax, %ds
	movw $0x500, %di
	movb $1, (%di)

	movw $0xffff, %ax
	movw %ax, %ds
	movw $0x510, %si
	movb $2, (%si)
#check_a20_die:
#	jmp check_a20_die

	movw $0, %ax
	movw %ax, %ds
	movw $0x500, %di
	cmpb $2, (%di)

	je check_a20_eq
	jmp check_a20_ne

check_a20_eq:
	movb $'D', %al
	ret
check_a20_ne:
	movb $'E', %al
	ret
