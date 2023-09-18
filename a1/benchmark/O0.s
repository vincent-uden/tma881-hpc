	.file	"main.c"
	.text
	.section	.rodata
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
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-48(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	gettimeofday@PLT
	movq	$0, -64(%rbp)
	movl	$0, -68(%rbp)
	jmp	.L2
.L3:
	movl	-68(%rbp), %eax
	cltq
	addq	%rax, -64(%rbp)
	addl	$1, -68(%rbp)
.L2:
	cmpl	$999999999, -68(%rbp)
	jle	.L3
	leaq	-32(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	gettimeofday@PLT
	movq	$0, -56(%rbp)
	movq	-32(%rbp), %rdx
	movq	-48(%rbp), %rax
	subq	%rax, %rdx
	imulq	$1000000, %rdx, %rax
	addq	%rax, -56(%rbp)
	movq	-24(%rbp), %rdx
	movq	-40(%rbp), %rax
	subq	%rax, %rdx
	addq	%rdx, -56(%rbp)
	movq	-64(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-56(%rbp), %rsi
	movabsq	$4835703278458516699, %rdx
	movq	%rsi, %rax
	imulq	%rdx
	sarq	$18, %rdx
	movq	%rsi, %rax
	sarq	$63, %rax
	movq	%rdx, %rcx
	subq	%rax, %rcx
	imulq	$1000000, %rcx, %rax
	movq	%rsi, %rcx
	subq	%rax, %rcx
	movq	-56(%rbp), %rsi
	movabsq	$4835703278458516699, %rdx
	movq	%rsi, %rax
	imulq	%rdx
	movq	%rdx, %rax
	sarq	$18, %rax
	sarq	$63, %rsi
	movq	%rsi, %rdx
	subq	%rdx, %rax
	movq	%rcx, %rdx
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L5
	call	__stack_chk_fail@PLT
.L5:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 13.2.1 20230801"
	.section	.note.GNU-stack,"",@progbits
