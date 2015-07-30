	.code16
	.text
BOOTSEG = 0x07c0
INITSEG = 0x9000

	.globl start
	.type start, @function
start:
	movw $BOOTSEG, %ax
	movw %ax, %ds
	movw $INITSEG, %ax
	movw %ax, %es
	movw $256, %cx
	sub %si, %si
	sub %di, %di
	rep movsw
	ljmp $INITSEG, $init_regs

init_regs:
	movw %cs, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %ss
	movw $0x400, %sp

print_msg:
	movb $0x03, %ah
	xor %bh, %bh
	int $0x10

	movw $19, %cx
	movw $0x07, %bx
	movw $msg, %bp
	movw $0x1301, %ax
	int $0x10

save_cursor:
	movb $0x03, %ah
	xor %bh, %bh
	int $0x10
	movw %dx, 510

load_os:
	nop

	cli
move_os:
	nop

load_dt:
	movw %cs, %ax
	movw %ax, %ds
	#lidt idt_48
	lgdt gdt_48

bootload_ok:
	movb $0x0e, %ah
	movb $'E', %al
	int $0x10
hang:
	jmp hang
	hlt

	.data
msg:
	.ascii "loading nros..."
	.byte 13, 10, 13, 10

idt_48:
	.word 0, 0, 0

gdt_48:
	.word 0x800
	.word gdt, 0x9

gdt:
	.word 0, 0, 0, 0
	.word 0x07FF # 8Mb - limit=2047 (2048*4096=8Mb)
	.word 0x0000 # base address=0
	.word 0x9A00 # code read/exec
	.word 0x00C0 # granularity=4096, 386

	.word 0x07FF # 8Mb - limit=2047 (2048*4096=8Mb)
	.word 0x0000 # base address=0
	.word 0x9200 # data read/write
	.word 0x00C0 # granularity=4096, 386
