.text
f_fac.0:
	push %rbp
	movq %rsp, %rbp
	push %rbx
	push %rsi
	push %rdi
	push %rcx
	push %rdx
	push %rax
	push 16(%rbp)
	push $0
	pop %rbx
	pop %rax
	cmpq %rbx, %rax
	je c_btrue.2
	push $0
	pop %rbx
	jmp c_bfalse.2
c_btrue.2:
	push $1
	pop %rbx
c_bfalse.2:
	push %rbx
	pop %rbx
	movq $1, %r9
	cmpq %r9, %rbx
	je c_btrue.1
	push 16(%rbp)
	push $1
	pop %rbx
	pop %rax
	cmpq %rbx, %rax
	je c_btrue.5
	push $0
	pop %rbx
	jmp c_bfalse.5
c_btrue.5:
	push $1
	pop %rbx
c_bfalse.5:
	push %rbx
	pop %rbx
	cmpq %r9, %rbx
	je c_btrue.1
	movq $0, %rbx
	jmp c_bfalse.1
c_btrue.1:
	movq %r9, %rbx
c_bfalse.1:
	push %rbx
	pop %rax
	push %r10
	movq $1, %r10
	cmpq %r10, %rax
	jne c_else.0
	push $1
	pop %rax
	pop %rdx
	pop %rcx
	pop %rdi
	pop %rsi
	pop %rbx
	movq %rbp, %rsp
	pop %rbp
	ret
	jmp c_end.0
c_else.0:
	push 16(%rbp)
	push 16(%rbp)
	push $1
	pop %rbx
	pop %rcx
	subq %rbx, %rcx
	push %rcx
	call f_fac.0
	addq $8, %rsp
	push %rax
	pop %rbx
	pop %rcx
	imulq %rbx, %rcx
	push %rcx
	pop %rax
	pop %rdx
	pop %rcx
	pop %rdi
	pop %rsi
	pop %rbx
	movq %rbp, %rsp
	pop %rbp
	ret
c_end.0:
	pop %rax
.globl main
main:
	push %rbp
	movq %rsp, %rbp
	push %rax
	push $5
	call f_fac.0
	addq $8, %rsp
	push %rax
	pop %rsi
	movq $pnum, %rdi
	movq $0, %rax
	call printf
	pop %rax
	pop %rdx
	pop %rcx
	pop %rdi
	pop %rsi
	pop %rbx
	movq %rbp, %rsp
	pop %rbp
	movq $0, %rax
	ret
.data
pnum: 
	.string "%d\n"
ptrue: 
	.string "true\n"
pfalse: 
	.string "false\n"
pnull: 
	.string "null\n"
heap_pointer:
	.space 8192
heap_next:
	.space 8
