.text
.globl main
main:
	push %rbp
	movq %rsp, %rbp
	push %rax
	push %rcx
	push %rdx
	push %rbx
	push $a
	pop %rcx
	movq heap_next, %rax
	movq %rax, %rcx
	push $7
	pop %rdx
	xorq %rbx, %rbx
	mov rdx, (rax,rbx,8)
	incq rdx
	imul $8, rdx
	add %rdx, heap_next
	pop %rbx
	pop %rdx
	pop %rcx
	pop %rax
	push %rbx
	push $7
	pop %rbx
	push %rdi
	push %rsi
	push a
	pop %rsi
	push $0
	pop %rdi
	incq rdi
	push (%rsi,rdi,8)
	pop %rcx
	mov rbx, (rcx)
	pop %rbx
	push %rax
	push %rdi
	push %rsi
	push a
	pop %rsi
	push $0
	pop %rdi
	incq rdi
	push (%rsi,rdi,8)
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
a:
	.space 8
