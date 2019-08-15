#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instruction_set.h"
#include "../symbols/memory.h"

INSTRUCTION* _pop(REGISTER to)
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = pop;
	ir->to = to;
	return ir;
}

INSTRUCTION* _push(REGISTER to, int val, int isoffset)
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = push;
	ir->to = to; // set to unknown if value is pushed
	ir->value = val;
	ir->isoffset = isoffset;
	return ir;
}

INSTRUCTION* _ret()
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = ret;
	return ir;
}

INSTRUCTION* _mov(REGISTER from, REGISTER to, int value, char* label)
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = mov;
	ir->from = from;
	ir->to = to;
	ir->value = value;
	ir->label = label;
	return ir;
}

INSTRUCTION* _add(REGISTER from, REGISTER to)
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = add;
	ir->from = from;
	ir->to = to;
	return ir;
}

INSTRUCTION* _sub(REGISTER from, REGISTER to)
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = sub;
	ir->from = from;
	ir->to = to;
	return ir;
}

INSTRUCTION* _mul(REGISTER from, REGISTER to)
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = mul;
	ir->from = from;
	ir->to = to;
	return ir;
}

INSTRUCTION* _xor(REGISTER from, REGISTER to)
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = xor;
	ir->from = from;
	ir->to = to;
	return ir;
}

INSTRUCTION* _div(REGISTER from)
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = div_;
	ir->from = from;
	return ir;
}

INSTRUCTION* _call(char* label)// revisit
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = call;
	ir->label = label;
	return ir;
}

INSTRUCTION* _dir(char* label)
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = dir;
	ir->label = label;
	return ir;
}

INSTRUCTION* _lbl(char* label)
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = lbl;
	ir->label = label;
	return ir;
}

INSTRUCTION* _cmp(REGISTER from, REGISTER to)
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = cmp;
	ir->from = from;
	ir->to = to;
	return ir;
}

INSTRUCTION* _jne(char* label)
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = jne;
	ir->label = label;
	return ir;
}

INSTRUCTION* _je(char* label)
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = je;
	ir->label = label;
	return ir;
}

INSTRUCTION* _jl(char* label)
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = jl;
	ir->label = label;
	return ir;
}

INSTRUCTION* _jg(char* label)
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = jg;
	ir->label = label;
	return ir;
}

INSTRUCTION* _jle(char* label)
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = jle;
	ir->label = label;
	return ir;
}

INSTRUCTION* _jge(char* label)
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = jge;
	ir->label = label;
	return ir;
}

INSTRUCTION* _jmp(char* label)
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = jmp;
	ir->label = label;
	return ir;
}

INSTRUCTION* _not(char* label)
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = not;
	ir->label = label;
	return ir;
}

INSTRUCTION* _neg(char* label)
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = neg;
	ir->label = label;
	return ir;
}

INSTRUCTION* _int(int val)
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = intCode;
	ir->value = val;
	return ir;
}

INSTRUCTION* _spc(char* label, int val)
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = space;
	ir->label = label;
	ir->value = val;
	return ir;
}

INSTRUCTION* _lea(int address, REGISTER to)
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = lea;
	ir->value = address;
	ir->to = to;
	return ir;
}

INSTRUCTION* _inc(REGISTER to)
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = inc;
	ir->to = to;
	return ir;
}

INSTRUCTION* _dec(REGISTER to)
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = dec;
	ir->to = to;
	return ir;
}

/*INSTRUCTION* create_ir_mov(ARGS* arg1, ARGS* arg2)
{
	INSTRUCTION* inst = NEW(INSTRUCTION);
	inst->id = 0;
	inst->op = mov;
	inst->arg1 = arg1;
	inst->arg2 = arg2;
	return inst;
}

INSTRUCTION* create_ir_cmp(ARGS* arg1, ARGS* arg2)
{
	INSTRUCTION* inst = NEW(INSTRUCTION);
	inst->id = 0;
	inst->op = cmp;
	inst->arg1 = arg1;
	inst->arg2 = arg2;
	return inst;
}
INSTRUCTION* create_ir_call(ARGS* arg1)
{
	INSTRUCTION* inst = NEW(INSTRUCTION);
	inst->id = 0;
	inst->op = call;
	inst->arg1 = arg1;
	return inst;
}
INSTRUCTION* create_ir_push(ARGS* arg1)
{
	INSTRUCTION* inst = NEW(INSTRUCTION);
	inst->id = 0;
	inst->op = push;
	inst->arg1 = arg1;
	return inst;
}
INSTRUCTION* create_ir_not(ARGS* arg1)
{
	INSTRUCTION* inst = NEW(INSTRUCTION);
	inst->id = 0;
	inst->op = not;
	inst->arg1 = arg1;
	return inst;
}
INSTRUCTION* create_ir_neg(ARGS* arg1) 
{
	INSTRUCTION* inst = NEW(INSTRUCTION);
	inst->id = 0;
	inst->op = neg;
	inst->arg1 = arg1;
	return inst;
}
INSTRUCTION* create_ir_intcode(char* label)
{
	INSTRUCTION* inst = NEW(INSTRUCTION);
	inst->id = 0;
	inst->op = intCode;
	inst->label = malloc(sizeof(label) + 1);
	strcpy(inst->label, label);
	return inst;
}
INSTRUCTION* create_ir_jmp(char* label)
{
	INSTRUCTION* inst = NEW(INSTRUCTION);
	inst->id = 0;
	inst->op = jmp;
	inst->label = malloc(sizeof(label) + 1);
	strcpy(inst->label, label);
	return inst;
}
INSTRUCTION* create_ir_jne(char* label)
{
	INSTRUCTION* inst = NEW(INSTRUCTION);
	inst->id = 0;
	inst->op = jne;
	inst->label = malloc(sizeof(label) + 1);
	strcpy(inst->label, label);
	return inst;
}
INSTRUCTION* create_ir_je(char* label) 
{
	INSTRUCTION* inst = NEW(INSTRUCTION);
	inst->id = 0;
	inst->op = je;
	inst->label = malloc(sizeof(label) + 1);
	strcpy(inst->label, label);
	return inst;
}
INSTRUCTION* create_ir_jg(char* label) 
{
	INSTRUCTION* inst = NEW(INSTRUCTION);
	inst->id = 0;
	inst->op = jg;
	inst->label = malloc(sizeof(label) + 1);
	strcpy(inst->label, label);
	return inst;
}
INSTRUCTION* create_ir_jl(char* label)
{
	INSTRUCTION* inst = NEW(INSTRUCTION);
	inst->id = 0;
	inst->op = jl;
	inst->label = malloc(sizeof(label) + 1);
	strcpy(inst->label, label);
	return inst;
}
INSTRUCTION* create_ir_jge(char* label) 
{
	INSTRUCTION* inst = NEW(INSTRUCTION);
	inst->id = 0;
	inst->op = jge;
	inst->label = malloc(sizeof(label) + 1);
	strcpy(inst->label, label);
	return inst;
}
INSTRUCTION* create_ir_jle(char* label)
{
	INSTRUCTION* inst = NEW(INSTRUCTION);
	inst->id = 0;
	inst->op = jle;
	inst->label = malloc(sizeof(label) + 1);
	strcpy(inst->label, label);
	return inst;
}
INSTRUCTION* create_ir_inc(ARGS* arg)
{
	INSTRUCTION* inst = NEW(INSTRUCTION);
	inst->id = 0;
	inst->op = inc;
	inst->arg1 = arg;
	return inst;
}
INSTRUCTION* create_ir_dec(ARGS* arg)
{
	INSTRUCTION* inst = NEW(INSTRUCTION);
	inst->id = 0;
	inst->op = dec;
	inst->arg1 = arg;
	return inst;
}
INSTRUCTION* create_ir_pop(ARGS* arg)
{
	INSTRUCTION* inst = NEW(INSTRUCTION);
	inst->id = 0;
	inst->op = pop;
	inst->arg1 = arg;
	return inst;
}
INSTRUCTION* create_ir_add(ARGS* arg1, ARGS* arg2)
{
	INSTRUCTION* inst = NEW(INSTRUCTION);
	inst->id = 0;
	inst->op = add;
	inst->arg1 = arg1;
	inst->arg2 = arg2;
	return inst;
}
INSTRUCTION* create_ir_sub(ARGS* arg1, ARGS* arg2)
{
	INSTRUCTION* inst = NEW(INSTRUCTION);
	inst->id = 0;
	inst->op = sub;
	inst->arg1 = arg1;
	inst->arg2 = arg2;
	return inst;
}
INSTRUCTION* create_ir_mul(ARGS* arg1, ARGS* arg2)
{
	INSTRUCTION* inst = NEW(INSTRUCTION);
	inst->id = 0;
	inst->op = mul;
	inst->arg1 = arg1;
	inst->arg2 = arg2;
	return inst;
}
INSTRUCTION* create_ir_xor(ARGS* arg1, ARGS* arg2)
{
	INSTRUCTION* inst = NEW(INSTRUCTION);
	inst->id = 0;
	inst->op = xor;
	inst->arg1 = arg1;
	inst->arg2 = arg2;
	return inst;
}
INSTRUCTION* create_ir_div(ARGS* arg1)
{
	INSTRUCTION* inst = NEW(INSTRUCTION);
	inst->id = 0;
	inst->op = _div;
	inst->arg1 = arg1;
	return inst;
}
INSTRUCTION* create_ir_label(char* lbl)
{
	INSTRUCTION* inst = NEW(INSTRUCTION);
	inst->id = 0;
	inst->op = label;
	inst->label = malloc(sizeof(lbl) + 1);
	strcpy(inst->label, lbl);
	return inst;
}
INSTRUCTION* create_ir_directive(char* label)
{
	INSTRUCTION* inst = NEW(INSTRUCTION);
	inst->id = 0;
	inst->op = directive;
	inst->label = label;//malloc(sizeof(label) + 1);
	//strcpy(inst->label, label);
	return inst;
}
INSTRUCTION* create_ir_space(ARGS* arg1, ARGS* arg2)
{
	INSTRUCTION* inst = NEW(INSTRUCTION);
	inst->id = 0;
	inst->op = space;
	inst->arg1 = arg1;
	inst->arg2 = arg2;
	return inst;
}
INSTRUCTION* create_ir_lea(ARGS* arg1, ARGS* arg2)
{
	INSTRUCTION* inst = NEW(INSTRUCTION);
	inst->id = 0;
	inst->op = lea;
	inst->arg1 = arg1;
	inst->arg2 = arg2;
	return inst;
}
INSTRUCTION* create_ir_ret()
{
	INSTRUCTION* inst = NEW(INSTRUCTION);
	inst->id = 0;
	inst->op = ret;
	return inst;
}
ARGS* create_address_args(int i, ARGS* base)
{
	ARGS* arg = NEW(ARGS);
	arg->kind = args_addr;
	arg->base = base;
	arg->offset = i;
	return arg;
}
ARGS* create_register_args(char* name)
{
	ARGS* arg = NEW(ARGS);
	arg->kind = args_reg;
	arg->name = malloc(sizeof(name) + 1);
	strcpy(arg->name, name);
	return arg;
}
ARGS* create_label_args(char* name)
{
	ARGS* arg = NEW(ARGS);
	arg->kind = args_lbl;
	arg->name = malloc(sizeof(name) + 1);
	strcpy(arg->name, name);
	return arg;
}
ARGS* create_constant_args(int i)
{
	ARGS* arg = NEW(ARGS);
	arg->kind = args_const;
	arg->offset = i;
	return arg;
}
ARGS* create_simple_const_args(int i)
{
	ARGS* arg = NEW(ARGS);
	arg->kind = args_const_arg;
	arg->offset = i;
	return arg;
}
ARGS* create_temp_args(int i)
{
	ARGS* arg = NEW(ARGS);
	arg->kind = args_temp;
	arg->identifier = i;
	return arg;
}
ARGS* create_index_args(ARGS* displace, ARGS* base, ARGS* idx)
{
	ARGS* arg = NEW(ARGS);
	arg->kind = args_idx;
	arg->displace = displace;
	arg->base = base;
	arg->idx = idx;
	return arg;
}*/