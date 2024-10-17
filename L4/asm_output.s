	.file	"mergesort.c"
	.text
	.globl	array
	.data
	.align 32
	.type	array, @object
	.size	array, 52
array:
	.long	4
	.long	15
	.long	6
	.long	2
	.long	21
	.long	17
	.long	11
	.long	16
	.long	8
	.long	13
	.long	14
	.long	1
	.long	9
	.globl	temp
	.bss
	.align 32
	.type	temp, @object
	.size	temp, 52
temp:
	.zero	52
	.text
	.globl	copy
	.type	copy, @function
copy:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	jmp	.L2
.L3:
	movq	-8(%rbp), %rdx
	leaq	4(%rdx), %rax
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rax
	leaq	4(%rax), %rcx
	movq	%rcx, -24(%rbp)
	movl	(%rdx), %edx
	movl	%edx, (%rax)
.L2:
	movq	-8(%rbp), %rax
	cmpq	-16(%rbp), %rax
	jbe	.L3
	movq	-24(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	copy, .-copy
	.globl	merge
	.type	merge, @function
merge:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$56, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%rdx, -56(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-48(%rbp), %rax
	addq	$4, %rax
	movq	%rax, -24(%rbp)
	leaq	temp(%rip), %rax
	movq	%rax, -16(%rbp)
	jmp	.L6
.L9:
	movq	-40(%rbp), %rax
	movl	(%rax), %edx
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	jg	.L7
	movq	-40(%rbp), %rdx
	leaq	4(%rdx), %rax
	movq	%rax, -40(%rbp)
	movq	-16(%rbp), %rax
	leaq	4(%rax), %rcx
	movq	%rcx, -16(%rbp)
	movl	(%rdx), %edx
	movl	%edx, (%rax)
	jmp	.L6
.L7:
	movq	-24(%rbp), %rdx
	leaq	4(%rdx), %rax
	movq	%rax, -24(%rbp)
	movq	-16(%rbp), %rax
	leaq	4(%rax), %rcx
	movq	%rcx, -16(%rbp)
	movl	(%rdx), %edx
	movl	%edx, (%rax)
.L6:
	movq	-40(%rbp), %rax
	cmpq	-48(%rbp), %rax
	ja	.L8
	movq	-24(%rbp), %rax
	cmpq	-56(%rbp), %rax
	jbe	.L9
.L8:
	movq	-16(%rbp), %rdx
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	copy
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-56(%rbp), %rcx
	movq	-24(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	copy
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	leaq	-4(%rax), %rcx
	movq	-8(%rbp), %rax
	movq	%rax, %rdx
	movq	%rcx, %rsi
	leaq	temp(%rip), %rax
	movq	%rax, %rdi
	call	copy
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	merge, .-merge
	.globl	mergesort
	.type	mergesort, @function
mergesort:
.LFB2:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	cmpq	-32(%rbp), %rax
	jnb	.L12
	movq	-32(%rbp), %rax
	subq	-24(%rbp), %rax
	sarq	$2, %rax
	movq	%rax, %rdx
	shrq	$63, %rdx
	addq	%rdx, %rax
	sarq	%rax
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	mergesort
	movq	-8(%rbp), %rax
	leaq	4(%rax), %rdx
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	mergesort
	movq	-32(%rbp), %rdx
	movq	-8(%rbp), %rcx
	movq	-24(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	merge
.L12:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	mergesort, .-mergesort
	.globl	main
	.type	main, @function
main:
.LFB3:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	48+array(%rip), %rax
	movq	%rax, %rsi
	leaq	array(%rip), %rax
	movq	%rax, %rdi
	call	mergesort
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
