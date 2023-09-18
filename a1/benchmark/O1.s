	.file	"main.c"
	.text
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"The sum of the first billion integers is %ld \n"
	.align 8
.LC1:
	.string	"This summation took %ld.%ld seconds \n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB11:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	subq	$48, %rsp
	.cfi_def_cfa_offset 64
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	movq	%rsp, %rdi
	movl	$0, %esi
	call	gettimeofday@PLT
	movl	$1000000000, %eax
.L2:
	subl	$1, %eax
	jne	.L2
	leaq	16(%rsp), %rdi
	movl	$0, %esi
	call	gettimeofday@PLT
	movq	16(%rsp), %rbx
	subq	(%rsp), %rbx
	imulq	$1000000, %rbx, %rbx
	addq	24(%rsp), %rbx
	subq	8(%rsp), %rbx
	movabsq	$499999999500000000, %rsi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movabsq	$4835703278458516699, %rdx
	movq	%rbx, %rax
	imulq	%rdx
	sarq	$18, %rdx
	movq	%rdx, %rsi
	movq	%rbx, %rax
	sarq	$63, %rax
	subq	%rax, %rsi
	imulq	$1000000, %rsi, %rax
	movq	%rbx, %rdx
	subq	%rax, %rdx
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L6
	movl	$0, %eax
	addq	$48, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
.L6:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE11:
	.size	main, .-main
	.ident	"GCC: (GNU) 13.2.1 20230801"
	.section	.note.GNU-stack,"",@progbits
