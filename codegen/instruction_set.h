#ifndef __instruction_set_h
#define __instruction_set_h

typedef enum OPCODE
{
	dir, lbl, mov, call, push, pop,
	add, sub, ret, xor, div_, mul, cmp, jne,
	je, jmp, jge, jle, jl, jg, not, neg, intCode,
	space, lea, inc, dec
} OPCODE;

typedef enum REGISTER
{
	unknown, rax, rbx, rcx, rdx, rsi, rdi, rbp, rsp,
	r8, r9, r10, r11, r12, r13, r14, r15
} REGISTER;

typedef enum ARGS_KIND
{
	args_addr, args_reg, args_lbl, args_const,
	args_temp, args_idx, args_const_arg
} ARGS_KIND;

typedef struct INSTRUCTION
{
	OPCODE op;
	REGISTER to;
	REGISTER from;
	char* label;
	int value;
	int isoffset;

	struct INSTRUCTION *args1;
	struct INSTRUCTION *args2;
} INSTRUCTION;

INSTRUCTION* _pop(REGISTER);
INSTRUCTION* _push(REGISTER, int value, int ifoffset);
INSTRUCTION* _ret();
INSTRUCTION* _mov(REGISTER, REGISTER, int, char*);
INSTRUCTION* _add(REGISTER, REGISTER);
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
INSTRUCTION* _neg(char*);
INSTRUCTION* _int(int);
INSTRUCTION* _spc(char*, int);
INSTRUCTION* _lea(int, REGISTER);
INSTRUCTION* _inc(REGISTER);
INSTRUCTION* _dec(REGISTER);

/*typedef struct INSTRUCTION
{
	int id;
	char* label;
	OPCODE op;
	struct ARGS* arg1;
	struct ARGS* arg2;

} INSTRUCTION;*/

/*typedef struct ARGS
{
	int identifier;
	ARGS_KIND kind;
	char* label;
	char* name;
	int offset;
	struct ARGS* displace;
	struct ARGS* base;
	struct ARGS* idx;
} ARGS;*/

/*INSTRUCTION* create_ir_mov(ARGS*, ARGS*);
INSTRUCTION* create_ir_cmp(ARGS*, ARGS*);
INSTRUCTION* create_ir_call(ARGS*);
INSTRUCTION* create_ir_push(ARGS*);
INSTRUCTION* create_ir_not(ARGS*);
INSTRUCTION* create_ir_neg(ARGS*);
INSTRUCTION* create_ir_intcode(char*);
INSTRUCTION* create_ir_jmp(char*);
INSTRUCTION* create_ir_jne(char*);
INSTRUCTION* create_ir_je(char*);
INSTRUCTION* create_ir_jg(char*);
INSTRUCTION* create_ir_jl(char*);
INSTRUCTION* create_ir_jge(char*);
INSTRUCTION* create_ir_jle(char*);
INSTRUCTION* create_ir_inc(ARGS*);
INSTRUCTION* create_ir_dec(ARGS*);
INSTRUCTION* create_ir_pop(ARGS*);
INSTRUCTION* create_ir_add(ARGS*, ARGS*);
INSTRUCTION* create_ir_sub(ARGS*, ARGS*);
INSTRUCTION* create_ir_mul(ARGS*, ARGS*);
INSTRUCTION* create_ir_xor(ARGS*, ARGS*);
INSTRUCTION* create_ir_div(ARGS*);
INSTRUCTION* create_ir_label(char*);
INSTRUCTION* create_ir_directive(char*);
INSTRUCTION* create_ir_space(ARGS*, ARGS*);
INSTRUCTION* create_ir_lea(ARGS*, ARGS*);
INSTRUCTION* create_ir_ret();

ARGS* create_address_args(int i, ARGS*);
ARGS* create_register_args(char* name);
ARGS* create_label_args(char*);
ARGS* create_constant_args(int);
ARGS* create_simple_const_args(int);
ARGS* create_temp_args(int);
ARGS* create_index_args(ARGS*, ARGS*, ARGS*);*/
#endif