#include <stdio.h>
#include "ir_print.h"

void ir_print(LINKEDLIST* ircode)
{
	fprintf(stderr, "[ir_print] emitting AT&T style ASM code..\n");

	LINKEDLIST* iterator;
	iterator = ircode;

	INSTRUCTION* temp;

	while (iterator != NULL)
	{
		temp = (INSTRUCTION*)iterator->data;

		switch (temp->op)
		{
		case raw:
			printf("\t%s", temp->label);
			printf("\n");
			break;
		case pop:
			printf("\tpop %%%s\n", get_register_from_enum(temp->to));
			break;
		case push:
			printf("\tpush ");
			if (temp->to == unknown)
			{
			//else if (temp->label && strlen(temp->label) > 1)
			//	printf("%s", temp->label);
				if (temp->label)
					printf("%s", temp->label);
				else
					printf("$%d", temp->value);
			}
			else if (temp->isoffset == 1)
				printf("%d(%%%s)", temp->value, get_register_from_enum(temp->to));
			else
				printf("%%%s", get_register_from_enum(temp->to));

			printf("\n");
			break;
		case ret:
			printf("\tret\n");
			break;
		case mov:
			if (temp->from == unknown)
			{
				if(temp->label) //non-zero/not NULL
					printf("\tmovq %s, %%%s", temp->label, get_register_from_enum(temp->to));
				else
					printf("\tmovq $%d, %%%s", temp->value, get_register_from_enum(temp->to));
			}
			else if (temp->value != 0)
			{
				if(temp->reverse)
					printf("\tmovq %d(%%%s), %%%s", get_register_from_enum(temp->from), temp->value, get_register_from_enum(temp->to));
				else
					printf("\tmovq %%%s, %d(%%%s)", get_register_from_enum(temp->from), temp->value, get_register_from_enum(temp->to));
			}
			else
				printf("\tmovq %%%s, %%%s", get_register_from_enum(temp->from), get_register_from_enum(temp->to));
			printf("\n");
			break;
		case add:
			if(temp->from == unknown)
				printf("\taddq $%d, %%%s", temp->value, get_register_from_enum(temp->to));
			else
				printf("\taddq %%%s, %%%s", get_register_from_enum(temp->from), get_register_from_enum(temp->to));
			printf("\n");
			break;
		case sub:
			printf("\tsubq %%%s, %%%s", get_register_from_enum(temp->from), get_register_from_enum(temp->to));
			printf("\n");
			break;
		case mul:
			printf("\timulq %%%s, %%%s", get_register_from_enum(temp->from), get_register_from_enum(temp->to));
			printf("\n");
			break;
		case xor:
			printf("\txorq %%%s, %%%s", get_register_from_enum(temp->from), get_register_from_enum(temp->to));
			printf("\n");
			break;
		case div_:
			printf("\tidivq %%%s, %%%s", get_register_from_enum(temp->from), get_register_from_enum(temp->to));
			printf("\n");
			break;
		case call:
			printf("\tcall %s", temp->label);
			printf("\n");
			break;
		case dir:
			printf("%s\n", temp->label);
			break;
		case lbl:
			printf("%s:\n", temp->label);
			break;
		case cmp:
			printf("\tcmpq %%%s, %%%s", get_register_from_enum(temp->from), get_register_from_enum(temp->to));
			printf("\n");
			break;
		case jne:
			printf("\tjne ");
			printf("%s", temp->label);
			printf("\n");
			break;
		case je:
			printf("\tje ");
			printf("%s", temp->label);
			printf("\n");
			break;
		case jl:
			printf("\tjl ");
			printf("%s", temp->label);
			printf("\n");
			break;
		case jg:
			printf("\tjg ");
			printf("%s", temp->label);
			printf("\n");
			break;
		case jle:
			printf("\tjle ");
			printf("%s", temp->label);
			printf("\n");
			break;
		case jge:
			printf("\tjge ");
			printf("%s", temp->label);
			printf("\n");
			break;
		case jmp:
			printf("\tjmp ");
			printf("%s", temp->label);
			printf("\n");
			break;
		case not:
			printf("\tnotq ");
			printf("%s", temp->label);
			printf("\n");
			break;
		case neg:
			printf("\tnegq ");
			printf("%s", temp->label);
			printf("\n");
			break;
		case intCode:
			printf("\tint ");
			printf("$%s", get_register_from_enum(temp->to));
			printf("\n");
			break;
		case space:
			printf("%s", temp->label);
			printf(":\n\t.space ");
			printf("%d", temp->value);
			printf("\n");
			break;
		case lea:
			printf("\tleaq ");
			//ir_print_args(temp->arg1);
			printf(get_register_from_enum(temp->from));
			printf(", ");
			printf(get_register_from_enum(temp->to));
			//ir_print_args(temp->arg2);
			printf("\n");
			break;
		case inc:
			//fprintf(stderr, "inc\n");
			printf("\tincq ");
			printf("%s", get_register_from_enum(temp->to));
			//ir_print_args(temp->arg1);
			printf("\n");
			break;
		case dec:
			//fprintf(stderr, "dec\n");
			printf("\tdecq "); 
			printf("%s", get_register_from_enum(temp->to));
			printf("\n");
			break;
		default:
			break;
		}
		iterator = iterator->next;
	}
}

/*void ir_print_args(ARGS* arg)
{
	switch (arg->kind)
	{
	case args_addr:
		//fprintf(stderr, "args_addr\n");
		printf("%d(", arg->offset);
		ir_print_args(arg->base);
		printf(")");
		break;
	case args_reg:
		//fprintf(stderr, "args_reg\n");
		printf("%%%s", arg->name);
		break;
	case args_lbl:
		//fprintf(stderr, "args_lbl\n");
		printf(arg->name);
		break;
	case args_const:
		//fprintf(stderr, "args_const\n");
		printf("$%d", arg->offset);
		break;
	case args_temp:
		//fprintf(stderr, "args_temp\n");
		printf("%%temp%d", arg->identifier);
		break;
	case args_idx:
		//fprintf(stderr, "args_idx\n");
		if (arg->displace)
			ir_print_args(arg->displace);
		printf("(");
		if (arg->base)
			ir_print_args(arg->base);
		printf(", ");
		ir_print_args(arg->idx);
		printf(",8)");
		break;
	case args_const_arg:
		//fprintf(stderr, "args_const_arg\n");
		printf("%d", arg->offset);
		break;
	default:
		break;
	}
}*/

char* get_register_from_enum(REGISTER reg)
{
	switch(reg)
	{
		case rax: return "rax";
		case rbx: return "rbx";
		case rcx: return "rcx";
		case rdx: return "rdx";
		case rsi: return "rsi";
		case rdi: return "rdi";
		case rbp: return "rbp";
		case rsp: return "rsp";
		case r8: return "r8";
		case r9: return "r9";
		case r10: return "r10";
		case r11: return "r11";
		case r12: return "r12";
		case r13: return "r13";
		case r14: return "r14";
		case r15: return "r15";
		default: return NULL;
	}
}