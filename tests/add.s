

f.num: 
	.string "%d\n"
f.true: 
	.string "TRUE\n"
f.false: 
	.string "FALSE\n"
f.null: 
	.string "NULL\n"
.text
f_test.0:
	push %rbp
	movq %rsp, %rbp
	push %rbx
	push %rsi
	push %rdi
	subq $8, %rsp
	push %rcx
	push %rdx
	push %rbx
	push 24(%rbp)
	push 16(%rbp)
	pop %rbx
	pop %rax
	addq %rbx, %rax
	push %rax
	pop %rbx
	movq %rbx, -8(%rbp)
	pop %rbx
	push -8(%rbp)
	pop %rax
	pop %rdi
	pop %rsi
	pop %rbx
	pop %rdx
	pop %rcx
	movq %rbp, %rsp
	pop %rbp
	ret
.globl main
main:
	push %rbp
	movq %rsp, %rbp
	push %rax
	push $10
	push $20
	call f_test.0
	addq $16, %rsp
	push %rax
	pop %rax
	movq $f.num, %rdi
	movq %rax, %rsi
	movq $0, %rax
	call printf
	pop %rax
	pop %rdi
	pop %rsi
	pop %rbx
	pop %rdx
	pop %rcx
	movq %rbp, %rsp
	pop %rbp
	movq $0, %rax
	ret
