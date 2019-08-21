#ifndef __instruction_set_h
#define __instruction_set_h

typedef enum OPCODE
{
	raw, dir, lbl, mov, call, push, pop,
	add, sub, ret, xor, div_, mul, cmp, jne,
	je, jmp, jge, jle, jl, jg, not, neg,
	space, lea, inc, dec
} OPCODE;

typedef enum REGISTER
{
	unknown, rax, rbx, rcx, rdx, rsi, rdi, rbp, rsp,
	r8, r9, r10, r11, r12, r13, r14, r15
} REGISTER;

typedef struct INSTRUCTION
{
	OPCODE op;
	REGISTER to;
	REGISTER from;
	char* label;
	int value;
	int isoffset;
	int reverse;
} INSTRUCTION;

INSTRUCTION* _raw(char* data);
INSTRUCTION* _pop(REGISTER);
INSTRUCTION* _push(REGISTER, int value, int ifoffset, char* label);
INSTRUCTION* _ret();
INSTRUCTION* _mov(REGISTER, REGISTER, int, char*, int);
INSTRUCTION* _add(REGISTER, REGISTER, int);
INSTRUCTION* _sub(REGISTER, REGISTER);
INSTRUCTION* _mul(REGISTER, REGISTER);
INSTRUCTION* _xor(REGISTER, REGISTER);
INSTRUCTION* _div(REGISTER);
INSTRUCTION* _call(char*);// revisit
INSTRUCTION* _dir(char*);
INSTRUCTION* _lbl(char*);
INSTRUCTION* _cmp(REGISTER, REGISTER);
INSTRUCTION* _jne(char*);
INSTRUCTION* _je(char*);
INSTRUCTION* _jl(char*);
INSTRUCTION* _jg(char*);
INSTRUCTION* _jle(char*);
INSTRUCTION* _jge(char*);
INSTRUCTION* _jmp(char*);
INSTRUCTION* _not(char*);
INSTRUCTION* _neg(REGISTER);
INSTRUCTION* _int(int);
INSTRUCTION* _spc(char*, int);
INSTRUCTION* _lea(int, REGISTER);
INSTRUCTION* _inc(REGISTER);
INSTRUCTION* _dec(REGISTER);
#endif