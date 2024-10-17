	.file	"mergesort.c"
	.text
	.globl	copy
	.type	copy, @function
copy:
.LFB23:
	.cfi_startproc
	endbr64
	cmpq	%rsi, %rdi
	ja	.L4
	movq	%rdx, %r8
	movq	%rdi, %rcx
.L3:
	addq	$4, %rcx
	addq	$4, %r8
	movl	-4(%rcx), %r9d
	movl	%r9d, -4(%r8)
	cmpq	%rcx, %rsi
	jnb	.L3
	subq	%rdi, %rsi
	shrq	$2, %rsi
	leaq	4(%rdx,%rsi,4), %rax
	ret
.L4:
	movq	%rdx, %rax
	ret
	.cfi_endproc
.LFE23:
	.size	copy, .-copy
	.globl	merge
	.type	merge, @function
merge:
.LFB24:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %r12
	movq	%rdx, %rbp
	leaq	4(%rsi), %rbx
	cmpq	%rsi, %rdi
	ja	.L12
	cmpq	%rdx, %rbx
	ja	.L12
	leaq	4+temp(%rip), %rax
	jmp	.L10
.L8:
	addq	$4, %rbx
	movq	%rax, %r8
	movl	%ecx, %edx
.L9:
	movl	%edx, -4(%rax)
	addq	$4, %rax
	cmpq	%rsi, %rdi
	ja	.L7
	cmpq	%rbp, %rbx
	ja	.L7
.L10:
	movl	(%rdi), %edx
	movl	(%rbx), %ecx
	cmpl	%ecx, %edx
	jg	.L8
	addq	$4, %rdi
	movq	%rax, %r8
	jmp	.L9
.L12:
	movq	%r12, %rdi
	leaq	temp(%rip), %r8
.L7:
	movq	%r8, %rdx
	call	copy
	movq	%rax, %rdx
	movq	%rbp, %rsi
	movq	%rbx, %rdi
	call	copy
	leaq	-4(%rax), %rsi
	movq	%r12, %rdx
	leaq	temp(%rip), %rdi
	call	copy
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE24:
	.size	merge, .-merge
	.globl	mergesort
	.type	mergesort, @function
mergesort:
.LFB25:
	.cfi_startproc
	endbr64
	cmpq	%rsi, %rdi
	jb	.L21
	ret
.L21:
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %rbx
	movq	%rsi, %rbp
	movq	%rsi, %rax
	subq	%rdi, %rax
	movq	%rax, %rdx
	sarq	$2, %rdx
	shrq	$63, %rax
	addq	%rdx, %rax
	sarq	%rax
	leaq	(%rdi,%rax,4), %r12
	movq	%r12, %rsi
	call	mergesort
	leaq	4(%r12), %rdi
	movq	%rbp, %rsi
	call	mergesort
	movq	%rbp, %rdx
	movq	%r12, %rsi
	movq	%rbx, %rdi
	call	merge
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE25:
	.size	mergesort, .-mergesort
	.globl	main
	.type	main, @function
main:
.LFB26:
	.cfi_startproc
	endbr64
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	leaq	48+array(%rip), %rsi
	leaq	-48(%rsi), %rdi
	call	mergesort
	movl	$0, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE26:
	.size	main, .-main
	.globl	temp
	.bss
	.align 32
	.type	temp, @object
	.size	temp, 52
temp:
	.zero	52
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
