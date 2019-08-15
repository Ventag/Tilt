
f.num: 
	.string "%d\n"
f.true: 
	.string "TRUE\n"
f.false: 
	.string "FALSE\n"
f.null: 
	.string "NULL\n"
.text
.globl main
main:
	push %rbp
	movq %rsp, %rbp
	subq $8, %rsp
	push %rbx
	push $3
	push $6
	pop %rbx
	pop %rax
	xorq %rdx, %rdx
	idivq %rbx
	push %rax
	pop %rbx
	movq %rbx, -8(%rbp)
	pop %rbx
	push %rax
	push -8(%rbp)
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
