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
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$56, %rsp
	.cfi_def_cfa_offset 80
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	movq	%rsp, %rdi
	movl	$0, %esi
	call	gettimeofday@PLT
	movl	$0, %eax
	movl	$0, %ebx
	jmp	.L2
.L3:
	movslq	%eax, %rdx
	addq	%rdx, %rbx
	addl	$1, %eax
.L2:
	cmpl	$999999999, %eax
	jle	.L3
	leaq	16(%rsp), %rdi
	movl	$0, %esi
	call	gettimeofday@PLT
	movq	16(%rsp), %rbp
	subq	(%rsp), %rbp
	imulq	$1000000, %rbp, %rbp
	movq	24(%rsp), %rax
	subq	8(%rsp), %rax
	addq	%rax, %rbp
	movq	%rbx, %rsi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movabsq	$4835703278458516699, %rdx
	movq	%rbp, %rax
	imulq	%rdx
	movq	%rdx, %rsi
	sarq	$18, %rsi
	movq	%rbp, %rax
	sarq	$63, %rax
	subq	%rax, %rsi
	imulq	$1000000, %rsi, %rax
	movq	%rbp, %rdx
	subq	%rax, %rdx
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L6
	movl	$0, %eax
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
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
