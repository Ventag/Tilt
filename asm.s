f_test.0:
	push %rbp
	movq %rsp, %rbp
	push %rbx
	push %rsi
	push %rdi
	push %rcx
	push %rdx
	push 24(%rbp)
	push 16(%rbp)
	pop %rbx
	pop %rcx
	subq %rbx, %rcx
	push %rcx
	pop %rax
	pop %rdx
	pop %rcx
	pop %rdi
	pop %rsi
	pop %rbx
	movq %rbp, %rsp
	pop %rbp
.globl main
main:
	push %rbp
	movq %rsp, %rbp
	push $4
	push $3
	call f_test.0
	pop %rdx
	pop %rcx
	pop %rdi
	pop %rsi
	pop %rbx
	movq %rbp, %rsp
	pop %rbp
