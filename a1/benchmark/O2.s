	.file	"main.c"
	.text
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"The sum of the first billion integers is %ld \n"
	.align 8
.LC1:
	.string	"This summation took %ld.%ld seconds \n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB11:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	xorl	%esi, %esi
	subq	$48, %rsp
	.cfi_def_cfa_offset 64
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	movq	%rsp, %rdi
	call	gettimeofday@PLT
	xorl	%esi, %esi
	leaq	16(%rsp), %rdi
	call	gettimeofday@PLT
	movq	16(%rsp), %rbx
	leaq	.LC0(%rip), %rdi
	xorl	%eax, %eax
	movabsq	$499999999500000000, %rsi
	subq	(%rsp), %rbx
	imulq	$1000000, %rbx, %rbx
	addq	24(%rsp), %rbx
	subq	8(%rsp), %rbx
	call	printf@PLT
	leaq	.LC1(%rip), %rdi
	movabsq	$4835703278458516699, %rax
	imulq	%rbx
	movq	%rbx, %rax
	sarq	$63, %rax
	sarq	$18, %rdx
	movq	%rdx, %rsi
	movq	%rbx, %rdx
	subq	%rax, %rsi
	imulq	$1000000, %rsi, %rax
	subq	%rax, %rdx
	xorl	%eax, %eax
	call	printf@PLT
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L5
	addq	$48, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
.L5:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE11:
	.size	main, .-main
	.ident	"GCC: (GNU) 13.2.1 20230801"
	.section	.note.GNU-stack,"",@progbits
