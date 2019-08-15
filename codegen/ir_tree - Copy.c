#include <stdio.h>

#include "ir_tree.h"
#include "../symbols/stack.h"
#include "../symbols/linkedlist.h"

#define OFFSET_SIZE 8

STACK* function_stack;
LINKEDLIST* irlist;
LINKEDLIST* datalist;

// callee save registers
ARGS *rbx, *r12, *r13, *r14, *r15;
// caller save registers
ARGS *rcx, *rdx, *rsi, *rdi, *r8, *r9, *r10, *r11;
// stack pointer
ARGS *rsp;
// base pointer
ARGS *rbp;
// return value
ARGS *rax;

ARGS *one, *zero;
ARGS *heap_base, *heap_free;
ARGS *print_int, *print_null, *print_true, *print_false;

INSTRUCTION *push_rbx, *push_r12, *push_r13, *push_r14, *push_r15;
INSTRUCTION *push_rcx, *push_rdx, *push_rsi, *push_rdi, *push_r8, *push_r9, *push_r10, *push_r11;
INSTRUCTION *push_rsp, *push_rbp, *push_rax;

INSTRUCTION *pop_rbx, *pop_r12, *pop_r13, *pop_r14, *pop_r15;
INSTRUCTION *pop_rcx, *pop_rdx, *pop_rsi, *pop_rdi, *pop_r8, *pop_r9, *pop_r10, *pop_r11;
INSTRUCTION *pop_rsp, *pop_rbp, *pop_rax;

int label_count = 0;
int should_print = 0;
int offset_depth = 0;
int var_offset = 8;

void init_registers()
{
	// callee save
	rbx = create_register_args("rbx");
	r12 = create_register_args("r12");
	r13 = create_register_args("r13");
	r14 = create_register_args("r14");
	r15 = create_register_args("r15");

	// caller save
	rcx = create_register_args("rcx");
	rdx = create_register_args("rdx");
	rsi = create_register_args("rsi");
	rdi = create_register_args("rdi");
	r8 = create_register_args("r8");
	r9 = create_register_args("r9");
	r10 = create_register_args("r10");
	r11 = create_register_args("r11");

	// stack/base/return pointers
	rsp = create_register_args("rsp");
	rbp = create_register_args("rbp");
	rax = create_register_args("rax");

	// push instructions
	push_rbx = create_ir_push(rbx);
	push_r12 = create_ir_push(r12);
	push_r13 = create_ir_push(r13);
	push_r14 = create_ir_push(r14);
	push_r15 = create_ir_push(r15);

	push_rcx = create_ir_push(rcx);
	push_rdx = create_ir_push(rdx);
	push_rsi = create_ir_push(rsi);
	push_rdi = create_ir_push(rdi);
	push_r8 = create_ir_push(r8);
	push_r9 = create_ir_push(r9);
	push_r10 = create_ir_push(r10);
	push_r11 = create_ir_push(r11);

	push_rsp = create_ir_push(rsp);
	push_rbp = create_ir_push(rbp);
	push_rax = create_ir_push(rax);

	// pop instructions
	pop_rbx = create_ir_pop(rbx);
	pop_r12 = create_ir_pop(r12);
	pop_r13 = create_ir_pop(r13);
	pop_r14 = create_ir_pop(r14);
	pop_r15 = create_ir_pop(r15);

	pop_rcx = create_ir_pop(rcx);
	pop_rdx = create_ir_pop(rdx);
	pop_rsi = create_ir_pop(rsi);
	pop_rdi = create_ir_pop(rdi);
	pop_r8 = create_ir_pop(r8);
	pop_r9 = create_ir_pop(r9);
	pop_r10 = create_ir_pop(r10);
	pop_r11 = create_ir_pop(r11);

	pop_rsp = create_ir_pop(rsp);
	pop_rbp = create_ir_pop(rbp);
	pop_rax = create_ir_pop(rax);
}

void init_constants()
{
	init_registers();
	one = create_constant_args(1);
	zero = create_constant_args(0);

	heap_base = create_label_args("$heap");
	heap_free = create_label_args("heap_next");
	print_int = create_label_args("$num");
	print_null = create_label_args("$null");
	print_true = create_label_args("$true");
	print_false = create_label_args("$false");
}

LINKEDLIST* build_ir_tree(BODY* body, int unused)
{
	fprintf(stderr, "[ir_tree] began intermediate code generation\n");
	function_stack = init_stack();
	irlist = link_initialize();
	datalist = link_initialize();
	init_constants();

	// create print forms
	link_push(irlist, create_ir_directive("f.num: \n\t.string \"%d\\n\""));
	link_push(irlist, create_ir_directive("f.true: \n\t.string \"TRUE\\n\""));
	link_push(irlist, create_ir_directive("f.false: \n\t.string \"FALSE\\n\""));
	link_push(irlist, create_ir_directive("f.null: \n\t.string \"NULL\\n\""));

	link_push(irlist, create_ir_directive(".text"));
	LINKEDLIST* first_element = irlist;

	ir_decl_list(body->decl_list);

	//init heap here
	int data_length = link_length(datalist);
	if (data_length > 0)
		link_push(datalist, create_ir_mov(heap_base, heap_free));

	link_push(irlist, create_ir_directive(".globl main"));
	link_push(irlist, create_ir_label("main"));

	link_push(irlist, push_rbp); // push base pointer
	link_push(irlist, create_ir_mov(rsp, rbp)); // make base pointer point to stack pointer

	allocate_local_vars(body->table);

	ir_statement_list(body->statement_list);

	function_epilog(); // cleanup
	link_push(irlist, create_ir_mov(zero, rax)); // exit code 0 to signal a-ok
	link_push(irlist, create_ir_ret());

	body->table->local_var_count = 0;

	data_section();

	return irlist;
}
void ir_func(FUNCTION* func)
{
	//fprintf(stderr, "ir_func\n");
	// declarations handled here to avoid nested function generation
	push_stack(function_stack, func);
	ir_decl_list(func->body->decl_list);
	ir_head(func->head);
	ir_body(func->body);
	func->table->local_var_count = 0; // reset local variables in this scope
	pop_stack(function_stack);
}
void ir_head(HEAD* head)
{
	//fprintf(stderr, "ir_head\n");
	SYMBOL* symbol = getSymbol(head->table, head->id);
	char* label = create_label(FUNC, symbol->name, symbol->offset);
	link_push(irlist, create_ir_label(label));
}
void ir_body(BODY* body)
{
	//fprintf(stderr, "ir_body\n");
	function_prolog(body->table);
	ir_statement_list(body->statement_list);
}
void ir_var_decl_list(VAR_DECL_LIST* var_decl_list)
{
	switch (var_decl_list->kind)
	{
	case VDECL_LIST:
		ir_var_decl_list(var_decl_list->var_decl_list);
		ir_var_type(var_decl_list->var_type);
		break;
	case VDECL_TYPE:
		ir_var_type(var_decl_list->var_type);
		break;
	}
}
void ir_var_type(VAR_TYPE* var_type)
{
	SYMBOL* symbol = getSymbol(var_type->table, var_type->id);
	symbol->var_offset = var_offset + 8;
	fprintf(stderr, "got symbol %s :: offset %d\n", symbol->name, symbol->var_offset);
	switch (var_type->type->kind) // allocate space on the stack for local integers & bools
	{
	case INT_T:
		if (var_type->symbol->symbol_kind == SYMBOL_LOCAL_VARIABLE)
		{
			var_type->table->local_var_count += OFFSET_SIZE;
		}
		break;
	case BOOL_T:
		if (var_type->symbol->symbol_kind == SYMBOL_LOCAL_VARIABLE)
		{
			var_type->table->local_var_count += OFFSET_SIZE;
		}
		break;
	default: // heap the rest..
		link_push(datalist, var_type);
		break;
	}
}
void ir_decl_list(DECL_LIST* decl_list)
{
	//fprintf(stderr, "ir_decl_list\n");
	switch (decl_list->kind)
	{
	case DECL_LIST_POPULATED:
		ir_declaration(decl_list->declaration);
		ir_decl_list(decl_list->decl_list);
	case DECL_LIST_EMPTY:
		break;
	}
}
void ir_declaration(DECLARATION* decl)
{
	//fprintf(stderr, "ir_declaration\n");
	switch (decl->kind)
	{
	case DECLARATION_ID:
		if(decl->val.identifier.type->kind == RECORD_T)
		{
			fprintf(stderr, "found a record\n");
		}
		else
		{
			SYMBOL* var = getSymbol(decl->table, decl->name);
			var->var_offset = var_offset + 8;
			fprintf(stderr, "ir_decl->%s %d\n", decl->name, var->var_offset);
		}
		
		break;
	case DECLARATION_FUNC:
		ir_func(decl->val.function);
		break;
	case DECLARATION_VAR:
		ir_var_decl_list(decl->val.var_decl_list);
		var_offset = 8;
		break;
	}
}
void ir_statement_list(STATEMENT_LIST* statement_list)
{
	switch (statement_list->kind)
	{
	case STATEMENT_LIST_LIST:
		ir_statement(statement_list->statement);
		ir_statement_list(statement_list->statement_list);
		break;
	case STATEMENT_LIST_ELEMENT:
		ir_statement(statement_list->statement);
		break;
	}
}
void ir_statement(STATEMENT* statement)
{
	int write_args_count = 0;
	int label_id = 0;
	SYMBOL_VALUE* symbol_val = NULL;
	switch (statement->kind)
	{
	case RETURN:
		ir_exp(statement->val.stat_return.exp);
		link_push(irlist, pop_rax); // pop top of stack into rax
		function_epilog();
		link_push(irlist, create_ir_ret()); // by convention rax stores the return result
		break;
	case WRITE:
		should_print = 1;
		link_push(irlist, push_rax); // backup rax
		symbol_val = statement->val.exp->symbol_value;
		switch (symbol_val->kind)
		{
		case SYMBOL_INT:
			ir_exp(statement->val.exp);
			link_push(irlist, pop_rax);
			link_push(irlist, create_ir_mov(print_int, rdi)); // move print form into rdi
			link_push(irlist, create_ir_mov(rax, rsi));
			link_push(irlist, create_ir_mov(zero, rax));
			write_args_count++;
			break;
		case SYMBOL_BOOL:
			ir_exp(statement->val.exp);
			link_push(irlist, pop_rax);
			int bool_id = label_count++; 
			char* flow_bool = create_label(FLOW, "pBool", bool_id);
			char* true_bool = create_label(FLOW, "pTrue", bool_id);

			link_push(irlist, create_ir_cmp(one, rax));
			link_push(irlist, create_ir_je(true_bool)); // skip false case if rax is equal to 1

			link_push(irlist, create_ir_mov(print_false, rdi)); // if false
			link_push(irlist, create_ir_mov(print_false, rsi));
			link_push(irlist, create_ir_mov(zero, rax));
			link_push(irlist, create_ir_jmp(flow_bool));

			link_push(irlist, create_ir_label(true_bool)); 
			link_push(irlist, create_ir_mov(print_true, rdi)); // if false
			link_push(irlist, create_ir_mov(print_true, rsi));
			link_push(irlist, create_ir_mov(zero, rax));

			link_push(irlist, create_ir_label(flow_bool)); // finally

			break;
		case SYMBOL_NULL:
			link_push(irlist, create_ir_mov(print_null, rdi));
			link_push(irlist, create_ir_mov(print_null, rsi));
			link_push(irlist, create_ir_mov(zero, rax));
			break;
		default:
			break;
		}
		link_push(irlist, create_ir_call(create_label_args("printf"))); // print what's been put into rdi, rsi & rax
		link_push(irlist, pop_rax); // restore rax
		break;
	case ALLOCATE:
		link_push(irlist, push_rax); // save rax
		symbol_val = statement->val.stat_allocate.var->symbol_value;
		ARGS* alloc_var = ir_var(statement->val.stat_allocate.var);
		switch (symbol_val->kind)
		{
		case SYMBOL_ARRAY:
			link_push(irlist, create_ir_mov(heap_free, rax));
			link_push(irlist, create_ir_mov(rax, alloc_var));
			link_push(irlist, create_ir_xor(rbx, rbx));

			ir_exp(statement->val.stat_allocate.length);
			link_push(irlist, pop_rcx);

			link_push(irlist, create_ir_mov(rcx, create_index_args(NULL, rax, rbx)));
			link_push(irlist, create_ir_inc(rcx));
			link_push(irlist, create_ir_mul(create_constant_args(OFFSET_SIZE), rcx));
			link_push(irlist, create_ir_add(rcx, heap_free));
			break;
		case SYMBOL_RECORD:
			link_push(irlist, create_ir_mov(heap_free, rax));
			link_push(irlist, create_ir_mov(rax, alloc_var));

			int record_member_count = statement->val.stat_allocate.var->symbol_value->length;

			link_push(irlist, create_ir_mov(create_constant_args(record_member_count), rcx));
			link_push(irlist, create_ir_mul(create_constant_args(OFFSET_SIZE), rcx));
			link_push(irlist, create_ir_add(rcx, heap_free));
			break;
		default:break;
		}
		link_push(irlist, pop_rax); // restore rax
		break;
	case ASSIGN:
		link_push(irlist, push_rbx); // backup rbx
		ir_exp(statement->val.stat_assign.exp);
		ARGS* var = ir_var(statement->val.stat_assign.var);
		link_push(irlist, pop_rbx);
		link_push(irlist, create_ir_mov(rbx, var));
		link_push(irlist, pop_rbx); // restore rbx
		break;
	case IF:
		link_push(irlist, push_rax); // save rax
		ir_exp(statement->val.stat_if.condition);
		link_push(irlist, pop_rax);
		link_push(irlist, create_ir_cmp(one, rax));

		int if_id = label_count++;
		char* else_label = create_label(FLOW, "else", if_id);
		char* end_label = create_label(FLOW, "end", if_id);

		if (statement->val.stat_if.optional_else->kind != ELSE_INACTIVE)
			link_push(irlist, create_ir_jne(else_label));
		else
			link_push(irlist, create_ir_jne(end_label));

		ir_statement(statement->val.stat_if.stat); // if condition holds true

		if (statement->val.stat_if.optional_else->kind != ELSE_INACTIVE)
		{
			link_push(irlist, create_ir_jmp(end_label));
			link_push(irlist, create_ir_label(else_label));
			ir_statement(statement->val.stat_if.optional_else->statement);
		}
		link_push(irlist, create_ir_label(end_label));
		link_push(irlist, pop_rax); // restore rax
		break;
	case WHILE:
		label_id = label_count++;
		char* while_start = create_label(FLOW, "wStart", label_id);
		char* while_end = create_label(FLOW, "wEnd", label_id);
		link_push(irlist, create_ir_label(while_start));
		ir_exp(statement->val.stat_while.condition);
		link_push(irlist, pop_rax);
		link_push(irlist, create_ir_cmp(one, rax));
		link_push(irlist, create_ir_jne(while_end));
		ir_statement(statement->val.stat_while.stat);
		link_push(irlist, create_ir_jmp(while_start));
		link_push(irlist, create_ir_label(while_end));
		break;
	case WHILE_LIST:
		ir_statement_list(statement->val.statement_list);
		break;
	default:
		break;
	}
}
void ir_act_list(ACT_LIST* act_list)
{
	switch (act_list->kind)
	{
	case ACT_LIST_POPULATED:
		ir_exp_list(act_list->exp_list);
		break;
	case ACT_LIST_EMPTY:
		break;
	}
}
void ir_exp_list(EXP_LIST* exp_list)
{
	switch (exp_list->kind)
	{
	case EXPRESSION_LIST:
		ir_exp(exp_list->exp);
		ir_exp_list(exp_list->exp_list);
		break;
	case EXPRESSION:
		ir_exp(exp_list->exp);
		break;
	}
}
void ir_exp(EXP* exp)
{
	int and_id, or_id;
	switch (exp->kind)
	{
	case EXP_TIMES:
	case EXP_PLUS:
	case EXP_MINUS:
		ir_exp(exp->val.branches.left);
		ir_exp(exp->val.branches.right);
		link_push(irlist, pop_rbx);
		link_push(irlist, pop_rax);

		if (exp->kind == EXP_TIMES)
			link_push(irlist, create_ir_mul(rbx, rax));
		else if (exp->kind == EXP_MINUS)
			link_push(irlist, create_ir_sub(rbx, rax));
		else if (exp->kind == EXP_PLUS)
			link_push(irlist, create_ir_add(rbx, rax));

		link_push(irlist, push_rax);
		break;
	case EXP_DIV:
		ir_exp(exp->val.branches.left);
		ir_exp(exp->val.branches.right);
		link_push(irlist, pop_rbx);
		link_push(irlist, pop_rax);

		link_push(irlist, create_ir_xor(rdx, rdx));
		link_push(irlist, create_ir_div(rbx));
		link_push(irlist, push_rax);
		break;
	case EXP_LESS:
	case EXP_LESS_EQUALS:
	case EXP_NOT_EQUALS:
	case EXP_GREATER:
	case EXP_GREATER_EQUALS:
	case EXP_EQUALS:
		ir_exp(exp->val.branches.left);
		ir_exp(exp->val.branches.right);

		int equality_id = label_count++;
		char* true_label = create_label(FLOW, "bTrue", equality_id);
		char* false_label = create_label(FLOW, "bFalse", equality_id);

		link_push(irlist, pop_rbx);
		link_push(irlist, pop_rax);
		link_push(irlist, create_ir_cmp(rbx, rax));

		INSTRUCTION* jump;
		switch (exp->kind)
		{
		case EXP_LESS:
			jump = create_ir_jl(true_label);
			break;
		case EXP_LESS_EQUALS:
			jump = create_ir_jle(true_label);
			break;
		case EXP_NOT_EQUALS:
			jump = create_ir_jne(true_label);
			break;
		case EXP_GREATER:
			jump = create_ir_jg(true_label);
			break;
		case EXP_GREATER_EQUALS:
			jump = create_ir_jge(true_label);
			break;
		case EXP_EQUALS:
			jump = create_ir_je(true_label);
			break;
		}

		link_push(irlist, jump);
		link_push(irlist, create_ir_mov(zero, rbx));
		link_push(irlist, create_ir_jmp(false_label));
		link_push(irlist, create_ir_label(true_label));
		link_push(irlist, create_ir_mov(one, rbx));
		link_push(irlist, create_ir_label(false_label));
		link_push(irlist, push_rbx);
		break;
	case EXP_AND:
		and_id = label_count++;
		char* false_and = create_label(FLOW, "aFalse", and_id);
		char* true_and = create_label(FLOW, "aTrue", and_id);

		ARGS* and = one;
		INSTRUCTION* jump_false = create_ir_jne(false_and);
		// rhs
		ir_exp(exp->val.branches.right);
		link_push(irlist, pop_rbx);
		link_push(irlist, create_ir_cmp(and, rbx));
		link_push(irlist, jump_false);

		// lhs
		ir_exp(exp->val.branches.left);
		link_push(irlist, pop_rbx);
		link_push(irlist, create_ir_cmp(and, rbx));
		link_push(irlist, jump_false);
		
		// evaluates to true
		link_push(irlist, create_ir_mov(and, rbx));
		link_push(irlist, create_ir_jmp(true_and));

		link_push(irlist, create_ir_label(false_and));
		link_push(irlist, create_ir_mov(zero, rbx));

		link_push(irlist, create_ir_label(true_and));
		link_push(irlist, push_rbx);
		break;
	case EXP_OR:
		or_id = label_count++;
		char* or_true = create_label(FLOW, "oTrue", or_id);
		char* or_false = create_label(FLOW, "oFalse", or_id);

		ARGS* or = one;
		INSTRUCTION* jump_true = create_ir_je(or_true);

		// evaluate left hand side
		ir_exp(exp->val.branches.left);
		link_push(irlist, pop_rbx);
		link_push(irlist, create_ir_cmp(or, rbx));
		link_push(irlist, jump_true); // first val is true, jump

		// evaluate right hand side
		ir_exp(exp->val.branches.right);
		link_push(irlist, pop_rbx);
		link_push(irlist, create_ir_cmp(or , rbx));
		link_push(irlist, jump_true); // second val is true, jump

		link_push(irlist, create_ir_mov(zero, rbx));
		link_push(irlist, create_ir_jmp(or_false)); // neither value is true, jump false
		link_push(irlist, create_ir_label(or_true));
		link_push(irlist, create_ir_mov(or, rbx));

		link_push(irlist, create_ir_label(or_false));
		link_push(irlist, push_rbx);
		break;
	case EXP_TERM:
		ir_term(exp->val.term);
		break;
	default:
		break;
	}
}
void ir_term(TERM* term)
{
	ARGS* arg = NULL;
	SYMBOL* symbol = NULL;
	switch (term->kind)
	{
	case TERM_VAR:
		arg = ir_var(term->val.var);
		link_push(irlist, create_ir_push(arg)); // push variable onto stack so we can pop it into a register later
		break;
	case TERM_ACT_LIST:
		symbol = getSymbol(term->table, term->val.term_act_list.id);
		char* act_list_label = create_label(FUNC, symbol->name, symbol->offset);
		int caller_scope_id = term->table->table_id;
		int callee_scope_id = symbol->table_id;
		offset_depth = 0;

		ir_act_list(term->val.term_act_list.act_list);

		link_push(irlist, create_ir_call(create_label_args(act_list_label)));

		link_push(irlist, create_ir_add(create_constant_args((symbol->parameters) * OFFSET_SIZE), rsp)); // add to stack pointer
																										 // to account for allocated vars on stack
		link_push(irlist, push_rax);
		break;
	case TERM_PARENTHESES:
		ir_exp(term->val.exp);
		break;
	case TERM_NOT:
		ir_term(term->val.term); 
		link_push(irlist, pop_rbx);
		link_push(irlist, create_ir_xor(one, rbx)); // xor with 1 to get negated val
		link_push(irlist, push_rbx);
		break;
	case TERM_ABSOLUTE:
		ir_exp(term->val.exp);

		if (term->val.exp->symbol_value->kind == SYMBOL_INT)
		{
			link_push(irlist, pop_rbx);
			int abs_num_label_id = label_count++;
			char* abs_num_label = create_label(FLOW, "aNum", label_count++);

			link_push(irlist, create_ir_cmp(zero, rbx));
			link_push(irlist, create_ir_jge(abs_num_label)); // jump to end if it's positive

			link_push(irlist, create_ir_neg(rbx)); // negate if false
			link_push(irlist, create_ir_label(abs_num_label));

			link_push(irlist, push_rbx);
		}
		else if (term->val.exp->symbol_value->kind == SYMBOL_ARRAY)
		{
			link_push(irlist, pop_rax); // might be var
			link_push(irlist, create_ir_xor(rcx, rcx));
			link_push(irlist, create_ir_push(create_index_args(NULL, rax, rcx))); // get first element storing size
		}
		break;
	case TERM_NUM:
		link_push(irlist, create_ir_push(create_constant_args(term->val.num)));
		break;
	case TERM_TRUE:
		link_push(irlist, create_ir_push(one));
		break;
	case TERM_FALSE:
	case TERM_NULL:
		link_push(irlist, create_ir_push(zero));
		break;
	default:
		break;
	}
}
ARGS* ir_var(VAR* var)
{
	ARGS* base = NULL;
	ARGS* offset_arg = NULL;
	ARGS* result = NULL;
	SYMBOL* symbol;
	int offset = 0;
	switch (var->kind)
	{
	case VAR_ID:
		symbol = getSymbol(var->table, var->id);

		if (symbol)
		{
			offset = symbol->offset * OFFSET_SIZE;
			if ((symbol->symbol_value->kind == SYMBOL_ARRAY || symbol->symbol_value->kind == SYMBOL_RECORD) && symbol->symbol_value->kind != SYMBOL_PARAMETER)
				result = create_ir_label(var->id); // var is on the heap
			else if (symbol->table_id < var->table->table_id) // allocate space on the stack for variable
			{
				int call_scope = var->table->table_id;
				int curr_scope = symbol->table_id;

				link_push(irlist, create_ir_mov(create_address_args(OFFSET_SIZE * 2, rbp), rcx));
				call_scope--;
				while (curr_scope != call_scope)
				{
					link_push(irlist, create_ir_mov(create_address_args(OFFSET_SIZE * 2, rcx), rcx));
					call_scope--;
				}

				if (symbol->symbol_kind == SYMBOL_LOCAL_VARIABLE)
				{
					offset *= -1;
					result = create_address_args(offset, rcx);
				}
				else
				{
					offset += OFFSET_SIZE;
					result = create_address_args(offset, rcx);
				}
			}
			else
			{
				if (symbol->symbol_kind == SYMBOL_LOCAL_VARIABLE)
				{
					offset *= -1;
					result = create_address_args(offset, rbp);
				}
				else
				{
					offset += OFFSET_SIZE;
					result = create_address_args(offset, rbp);
				}
			}
		}
		fprintf(stderr, var->id);
			fprintf(stderr, "VAR_ID::symbol->offset %d :: offset %d\n", symbol->offset, offset);
			offset_depth += OFFSET_SIZE;
			fprintf(stderr, "current offset depth: %d\n", offset_depth);
		return result;

	case VAR_ARRAY:
		base = ir_var(var->val.var_array.var);
		link_push(irlist, create_ir_mov(base, rsi));

		ir_exp(var->val.var_array.exp);
		link_push(irlist, create_ir_inc(rdi));

		return create_index_args(NULL, rsi, rdi);

	case VAR_RECORD:
		base = ir_var(var->val.var_record.var);
		SYMBOL_TABLE* child_scope = var->val.var_record.var->symbol_value->child_scope;
		SYMBOL* record = getSymbol(child_scope, var->val.var_record.id);
		if (record)
			offset_arg = create_constant_args(symbol->offset - 1);

		link_push(irlist, create_ir_mov(base, rsi));

		link_push(irlist, create_ir_mov(offset_arg, rdi));
		return create_index_args(NULL, rsi, rdi);
	}
}

void function_prolog(SYMBOL_TABLE* scope)
{
	// CALLEE
	link_push(irlist, push_rbp); // save calling functions base pointer
	link_push(irlist, create_ir_mov(rsp, rbp)); // move stack pointer into base pointer

	link_push(irlist, push_rbx);
	link_push(irlist, push_rsi);
	link_push(irlist, push_rdi);
													// allocate x*8 amount of bytes for this funcs local variables
	allocate_local_vars(scope);						// so that we can refer to them on the stack

	// CALLER
	link_push(irlist, push_rcx);
	link_push(irlist, push_rdx);
}

void function_epilog()
{
	link_push(irlist, pop_rdi);
	link_push(irlist, pop_rsi);
	link_push(irlist, pop_rbx);
	link_push(irlist, pop_rdx);
	link_push(irlist, pop_rcx);

	link_push(irlist, create_ir_mov(rbp, rsp)); // restore stack pointer
	link_push(irlist, pop_rbp); // restore base pointer
}

void allocate_local_vars(SYMBOL_TABLE* scope)
{
	if (scope->local_var_count > 0)
	{
		ARGS* count = create_constant_args(scope->local_var_count);
		INSTRUCTION* inst = create_ir_sub(count, rsp);
		link_push(irlist, inst);
	}
}

char* create_label(LABEL_KIND kind, char* content, int offset)
{
	char* label = malloc(33 * sizeof(char));
	switch (kind)
	{
	case FUNC:
		sprintf(label, "f_%s.%d", content, offset);
		break;
	case FLOW:
		sprintf(label, "c_%s.%d", content, offset);
		break;
	case UNKNOWN:
		break;
	default:
		break;
	}
	return label;
}

int is_already_defined(LINKEDLIST *definedList, char *labelName) {

	LINKEDLIST *iterator = definedList->next;

	while (iterator != definedList) {

		if (strcmp(labelName, (char*)iterator->data) == 0) {
			return 1;
		}
		iterator = iterator->next;
	}
	return 0;
}

void data_section()
{
	int heap_size = link_length(datalist);

	if (heap_size <= 0)
		return;

	link_push(irlist, create_ir_directive(".data"));

	link_push(irlist, create_ir_space(create_label_args("heap."), create_simple_const_args(OFFSET_SIZE * 8192))); // initialize heap max size
	link_push(irlist, create_ir_space(heap_free, create_simple_const_args(OFFSET_SIZE)));

	LINKEDLIST* iterator = datalist;
	LINKEDLIST* definitions = link_initialize();

	while (iterator != NULL)
	{
		VAR_TYPE* vtype = (VAR_TYPE*)iterator->data;
		SYMBOL* symbol = getSymbol(vtype->table, vtype->id);

		if (symbol && (symbol->symbol_kind == SYMBOL_ARRAY || symbol->symbol_kind == SYMBOL_RECORD))
		{
			if (!is_already_defined(definitions, vtype->id)) // did we define it already?
			{
				link_push(irlist, create_ir_space(create_ir_label(vtype->id), create_simple_const_args(OFFSET_SIZE)));
				link_push(definitions, vtype->id);
			}
		}
		iterator = iterator->next;
	}
}