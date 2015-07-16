	.text

	.globl load_page_dir
	.type load_page_dir @function
load_page_dir:
	pushl %ebp
	movl %esp, %ebp
	movl 8(%ebp), %eax
	movl %eax, %cr3
	movl %ebp, %esp
	popl %ebp
	ret

	.globl enable_paging
	.type enable_paging @function
enable_paging:
	pushl %ebp
	movl %esp, %ebp
	movl %cr0, %eax
	or $0x80000000, %eax
	movl %eax, %cr0
	movl %ebp, %esp
	popl %ebp
	ret
