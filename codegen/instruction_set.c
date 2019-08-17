#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instruction_set.h"
#include "../symbols/memory.h"

INSTRUCTION* _raw(char* data)
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->label = data;
	ir->op = raw;
	return ir;
}

INSTRUCTION* _pop(REGISTER to)
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = pop;
	ir->to = to;
	return ir;
}

INSTRUCTION* _push(REGISTER to, int val, int isoffset, char* label)
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = push;
	ir->to = to; // set to unknown if value is pushed
	ir->value = val;
	ir->isoffset = isoffset;
	ir->label = label;
	return ir;
}

INSTRUCTION* _ret()
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = ret;
	return ir;
}

INSTRUCTION* _mov(REGISTER from, REGISTER to, int value, char* label, int reverse	)
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = mov;
	ir->from = from;
	ir->to = to;
	ir->value = value;
	ir->label = label;
	ir->reverse = reverse;
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

INSTRUCTION* _neg(REGISTER reg)
{
	INSTRUCTION* ir = NEW(INSTRUCTION);
	ir->op = neg;
	ir->from = reg;
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