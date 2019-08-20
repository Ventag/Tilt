#include <stdio.h>

#include "ir_tree.h"
#include "../symbols/linkedlist.h"
#include "../symbols/memory.h"

#define OFFSET_SIZE 8

LINKEDLIST* irlist;
LINKEDLIST* datalist;

int label_count = 0;
int should_print = 0;
int offset_depth = 0;
int var_offset = 8;
int func_count = 0;

IMMEDIATECODE* imc;

LINKEDLIST* build_ir_tree(BODY* body, int unused)
{
	fprintf(stderr, "[ir_tree] began intermediate code generation\n");
	irlist = link_initialize();
	datalist = link_initialize();

	link_push(irlist, _dir(".text"));
	LINKEDLIST* first_element = irlist;
	imc = calloc(1, sizeof(IMMEDIATECODE));

	ir_decl_list(body->decl_list);

	link_push(irlist, _dir(".globl main"));
	link_push(irlist, _lbl("main"));
	link_push(irlist, _push(rbp, 0, 0, NULL));
	link_push(irlist, _mov(rsp, rbp, 0, NULL, 0)); // initialize frame pointer

	allocate_local_vars(); // allocate local vars in main scope

	ir_statement_list(body->statement_list);

	function_epilog(); // cleanup or SEG fault!
	link_push(irlist, _mov(unknown, rax, 0, NULL, 0)); // exit code 0 to signal a-ok
	link_push(irlist, _ret()); // ret returns what ever is in RAX

	imc->local_var_count = 0;

	//init heap here
	data_section();

	return irlist;
}
void ir_func(FUNCTION* func)
{
	imc->depth++; // we're going down
	ir_head(func->head);
	ir_body(func->body);
	imc->depth--;
}
void ir_head(HEAD* head)
{
	SYMBOL* symbol = getSymbol(head->table, head->id);
	char* label = create_label(FUNC, symbol->name, 0);
	link_push(irlist, _lbl(label));
	ir_par_decl_list(head->par_decl_list);
}

void ir_body(BODY* body)
{
	var_offset = 8;
	ir_decl_list(body->decl_list); 	
	function_prolog(body->table);
	ir_statement_list(body->statement_list);
}

void ir_par_decl_list(PAR_DECL_LIST* pdecl)
{
	switch (pdecl->kind)
	{
	case PAR_DECL_LIST_POPLUATED:
		imc->kind = PARAM;
		ir_var_decl_list(pdecl->var_decl_list);
		break;
	case PAR_DECL_LIST_EMPTY:
		break;
	}
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
	switch(imc->kind)
	{
		case PARAM:
			var_offset += 8; // increment first
			symbol->var_offset = var_offset;
		break;
		case LOCAL:
			symbol->var_offset = -var_offset; // negate offset, we're looking inside the function, not outside
			imc->local_var_count += OFFSET_SIZE; // count amount of local vars so we can allocate room on the stack for assignments later
			var_offset += OFFSET_SIZE; // increment here because rbp is at 0, first args must be at -8 and second -16 etc..
		break;
		default: // records & arrays aren't classified as params or local vars as they reside on the heap
			link_push(datalist, var_type);
		break;
	}
}

void ir_decl_list(DECL_LIST* decl_list)
{
	switch (decl_list->kind)
	{
	case DECL_LIST_POPULATED:
		if(imc->kind != RECORD)
			imc->kind = LOCAL;

		ir_declaration(decl_list->declaration);
		ir_decl_list(decl_list->decl_list);
		var_offset = 8;
	case DECL_LIST_EMPTY:
		break;
	}
}

void ir_declaration(DECLARATION* decl)
{
	SYMBOL* symbol = NULL;
	switch (decl->kind)
	{
	case DECLARATION_ID:
		symbol = getSymbol(decl->table, decl->val.identifier.id);
		if(symbol->kind == RECORD_MEMBER || decl->val.identifier.type->kind == RECORD_T)
		{
			// TODO
			imc->kind = RECORD;
		}
		else
		{
			symbol->var_offset = var_offset;
			link_push(irlist, _push(unknown, 0, 0, NULL));
			var_offset += 8;
		}
		
		break;
	case DECLARATION_FUNC:
		ir_func(decl->val.function);
		break;
	case DECLARATION_VAR:
		var_offset = 8; // reset offset
		//fprintf(stderr, "DECLARATION_VAR\n");
		if (decl->symbol->kind == RECORD_MEMBER)
		{
			imc->kind = RECORD;
		}

		if (decl->val.var_decl_list->var_type->type->typeinfo->type == TYPE_ARRAY)
		{
			imc->kind = ARRAY;
		}

		ir_var_decl_list(decl->val.var_decl_list);
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
	int ilbl = label_count++;
	switch (statement->kind)
	{
	case RETURN:
		ir_exp(statement->val.stat_return.exp);
		link_push(irlist, _pop(rax)); // pop return val into rax, should be ontop of stack
		function_epilog();
		link_push(irlist, _ret()); // return after cleaning up registers
		break;
	case WRITE:
		link_push(irlist, _push(rax, 0, 0, NULL)); // backup whatever is in rax
		TYPEINFO* typeinfo = statement->val.exp->typeinfo;
		switch (typeinfo->type)
		{
		case TYPE_INT:
			ir_exp(statement->val.exp);
			link_push(irlist, _pop(rsi));
			link_push(irlist, _mov(unknown, rdi, 0, "$pnum", 0));
			link_push(irlist, _mov(unknown, rax, 0, NULL,0 ));
			break;
		case TYPE_BOOL:
			ir_exp(statement->val.exp);
			link_push(irlist, _pop(rax));
			int labelid = label_count++;
			char* bend = create_label(FLOW, "pbool", labelid);
			char* btrue = create_label(FLOW, "ptrue", labelid);

			link_push(irlist, _push(r10, 0, 0, NULL)); // backup r10
			link_push(irlist, _mov(unknown, r10, 1, NULL, 0));
			link_push(irlist, _cmp(r10, rax));
			link_push(irlist, _pop(r10)); // restore r10
			link_push(irlist, _je(btrue)); // if rax is equal 1, e.g. it is true, jmp to true case

			link_push(irlist, _mov(unknown, rdi, 0, "$pfalse", 0)); // false case
			link_push(irlist, _mov(unknown, rsi, 0, "$pfalse", 0));
			link_push(irlist, _mov(unknown, rax, 0, NULL, 0));
			link_push(irlist, _jmp(bend));

			link_push(irlist, _lbl(btrue)); // true case
			link_push(irlist, _mov(unknown, rdi, 0, "$ptrue", 0));
			link_push(irlist, _mov(unknown, rsi, 0, "$ptrue", 0));
			link_push(irlist, _mov(unknown, rax, 0, NULL, 0));

			link_push(irlist, _lbl(bend));
			break;
		case TYPE_NULL:
			link_push(irlist, _mov(unknown, rdi, 0, "$pnull", 0));
			link_push(irlist, _mov(unknown, rsi, 0, "$pnull", 0));
			link_push(irlist, _mov(unknown, rax, 0, NULL, 0));
			break;
		default:
			break;
		}
		link_push(irlist, _call("printf"));
		link_push(irlist, _pop(rax)); // finally restore rax
		break;
	case ALLOCATE:
		if (statement->val.stat_allocate.var->typeinfo->type == TYPE_ARRAY)
		{
			link_push(irlist, _push(rax, 0, 0, NULL)); // save rax
			link_push(irlist, _push(rcx, 0, 0, NULL)); // save rcx
			link_push(irlist, _push(rdx, 0, 0, NULL)); // save rdx
			link_push(irlist, _push(rbx, 0, 0, NULL)); // save rbx

			ir_var(statement->val.stat_allocate.var);
			link_push(irlist, _pop(rcx)); // pop var into rcx
			link_push(irlist, _mov(unknown, rax, 0, "heap_next", 0));
			link_push(irlist, _mov(rax, rcx, 0, NULL, 0));

			ir_exp(statement->val.stat_allocate.length); // pop length into rdx
			link_push(irlist, _pop(rdx));
			link_push(irlist, _xor(rbx, rbx));
			link_push(irlist, _raw("mov rdx, (rax,rbx,8)")); // move array size to 1st index
			link_push(irlist, _inc(rdx));
			link_push(irlist, _raw("imul $8, rdx"));  // get size of array in bytes
			link_push(irlist, _raw("add %rdx, heap_next"));

			link_push(irlist, _pop(rbx)); // restore rbx
			link_push(irlist, _pop(rdx)); // restore rdx
			link_push(irlist, _pop(rcx)); // restore rcx
			link_push(irlist, _pop(rax)); // restore rax
		}
		else if (statement->val.stat_allocate.var->typeinfo->type == TYPE_RECORD)
		{
			// TODO
		}
		else
		{
			fprintf(stderr, "error\n"); // can't allocate space for anything but records & arrays
			exit(1);
		}
		break;
	case ASSIGN: // array assignment crashes here
		link_push(irlist, _push(rbx, 0, 0, NULL)); // backup rbx
		ir_exp(statement->val.stat_assign.exp);
		link_push(irlist, _pop(rbx)); // store exp in rbx
		ir_var(statement->val.stat_assign.var);
		link_push(irlist, _pop(rcx)); // store var in rcx
		if (statement->val.stat_assign.var->kind == VAR_ARRAY)
		{
			//link_push(irlist, _mov(rbx, rcx, 0, NULL, 0)); // address is pushed to the stack, we just pop it into rcx
			link_push(irlist, _raw("mov rbx, (rcx)")); // raw because no time to widen _mov function to deref pointers...
		}
		if (statement->val.stat_assign.var->kind == VAR_ID)
		{
			SYMBOL* symbol = getSymbol(statement->table, statement->val.stat_assign.var->id);
			link_push(irlist, _mov(rbx, rbp, symbol->var_offset, NULL, 0));
		}
		link_push(irlist, _pop(rbx));
		break;
	case IF: // TODO
		link_push(irlist, _push(rax, 0, 0, NULL)); // backup rax
		char* lbl_else = create_label(FLOW, "else", ilbl);
		char* lbl_end = create_label(FLOW, "end", ilbl);
		ir_exp(statement->val.stat_if.condition); // will push new value to stack, we pop into rax
		link_push(irlist, _pop(rax));
		link_push(irlist, _push(r10, 0, 0, NULL)); // backup r10
		link_push(irlist, _mov(unknown, r10, 1, NULL, 0)); // move 1 into r10
		link_push(irlist, _cmp(r10, rax)); // cmp 1 to rax, is condition true?

		if (statement->val.stat_if.optional_else->kind == ELSE_INACTIVE)
			link_push(irlist, _jne(lbl_end));
		else
			link_push(irlist, _jne(lbl_else));

		ir_statement(statement->val.stat_if.stat); // generate w/e code has to be executed if it holds true
		link_push(irlist, _jmp(lbl_end));

		if (statement->val.stat_if.optional_else->kind != ELSE_INACTIVE) // if we have an else statement
		{
			link_push(irlist, _lbl(lbl_else)); // create the else statement label
			ir_statement(statement->val.stat_if.optional_else->statement); // generate the code for the else case
		}
		link_push(irlist, _lbl(lbl_end));
		link_push(irlist, _pop(rax));
		break;
	case WHILE:
		link_push(irlist, _push(rax, 0, 0, NULL)); // backup rax
		char* lbl_start = create_label(FLOW, "start", ilbl);
		char* lbl_wend = create_label(FLOW, "end", ilbl);

		link_push(irlist, _lbl(lbl_start));

		ir_exp(statement->val.stat_while.condition);
		link_push(irlist, _pop(rax));
		link_push(irlist, _push(r10, 0, 0, NULL)); // backup r10
		link_push(irlist, _mov(unknown, r10, 1, NULL, 0));
		link_push(irlist, _cmp(r10, rax));
		link_push(irlist, _pop(r10)); // restore r10
		link_push(irlist, _jne(lbl_wend));

		ir_statement(statement->val.stat_while.stat);

		link_push(irlist, _jmp(lbl_start));
		link_push(irlist, _lbl(lbl_wend));
		link_push(irlist, _pop(rax)); // restore rax
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

void ir_exp(EXP* exp) // term values will be on the stack, so pop them into registers at your leisure
{
	int ilabel = label_count++;
	char* sztrue = create_label(FLOW, "btrue", ilabel);
	char* szfalse = create_label(FLOW, "bfalse", ilabel);
	switch (exp->kind)
	{
	case EXP_TIMES:
	case EXP_PLUS:
	case EXP_MINUS:
		ir_exp(exp->val.branches.left);
		ir_exp(exp->val.branches.right);
		link_push(irlist, _pop(rbx));
		link_push(irlist, _pop(rcx));

		switch (exp->kind)
		{
		case EXP_TIMES:
			link_push(irlist, _mul(rbx, rcx));
			break;
		case EXP_MINUS:
			link_push(irlist, _sub(rbx, rcx));
			break;
		case EXP_PLUS:
			link_push(irlist, _add(rbx, rcx, 0));
			break;
		}

		link_push(irlist, _push(rcx, 0, 0, NULL));
		break;
	case EXP_DIV:
		ir_exp(exp->val.branches.left);
		ir_exp(exp->val.branches.right);
		link_push(irlist, _pop(rbx));
		link_push(irlist, _pop(rax));

		link_push(irlist, _xor(rdx, rdx));
		link_push(irlist, _div(rbx));
		link_push(irlist, _push(rax, 0, 0, NULL));
		break;
	case EXP_LESS:
	case EXP_LESS_EQUALS:
	case EXP_NOT_EQUALS:
	case EXP_GREATER:
	case EXP_GREATER_EQUALS:
	case EXP_EQUALS:
		ir_exp(exp->val.branches.left);
		ir_exp(exp->val.branches.right);


		link_push(irlist, _pop(rbx));
		link_push(irlist, _pop(rax));
		link_push(irlist, _cmp(rbx, rax));

		INSTRUCTION* jmp;
		switch (exp->kind)
		{
		case EXP_LESS:
			jmp = _jl(sztrue);
			break;
		case EXP_LESS_EQUALS:
			jmp = _jle(sztrue);
			break;
		case EXP_NOT_EQUALS:
			jmp = _jne(sztrue);
			break;
		case EXP_GREATER:
			jmp = _jg(sztrue);
			break;
		case EXP_GREATER_EQUALS:
			jmp = _jge(sztrue);
			break;
		case EXP_EQUALS:
			jmp = _je(sztrue);
			break;
		}

		link_push(irlist, jmp);
		link_push(irlist, _push(unknown, 0, 0, NULL)); // push 0 to stack
		link_push(irlist, _pop(rbx)); // pop 0 from stack into rbx
		link_push(irlist, _jmp(szfalse));
		link_push(irlist, _lbl(sztrue)); // create true case
		link_push(irlist, _push(unknown, 1, 0, NULL)); // push 1 to stack
		link_push(irlist, _pop(rbx)); // pop 1 from stack into rbx
		link_push(irlist, _lbl(szfalse)); // create false case
		link_push(irlist, _push(rbx, 0, 0, NULL));
		break;
	case EXP_AND:
		ir_exp(exp->val.branches.right);

		link_push(irlist, _pop(rbx));
		link_push(irlist, _mov(unknown, r9, 1, NULL, 0));
		link_push(irlist, _cmp(rbx, r9));
		link_push(irlist, _jne(szfalse));

		ir_exp(exp->val.branches.left);
		link_push(irlist, _pop(rbx));
		link_push(irlist, _cmp(rbx, r9));
		link_push(irlist, _jne(szfalse));

		link_push(irlist, _mov(unknown, rbx, 1, NULL, 0));
		link_push(irlist, _jmp(sztrue));

		link_push(irlist, _lbl(szfalse));
		link_push(irlist, _mov(unknown, rbx, 0, NULL, 0));
		link_push(irlist, _lbl(sztrue));
		link_push(irlist, _push(rbx, 0, 0, NULL));
		break;
	case EXP_OR:
		ir_exp(exp->val.branches.left);
		link_push(irlist, _pop(rbx));
		link_push(irlist, _mov(unknown, r9, 1, NULL, 0));
		link_push(irlist, _cmp(r9, rbx));
		link_push(irlist, _je(sztrue));

		ir_exp(exp->val.branches.right);
		link_push(irlist, _pop(rbx));
		link_push(irlist, _cmp(r9, rbx)); // 1 already resides in r9
		link_push(irlist, _je(sztrue));

		link_push(irlist, _mov(unknown, rbx, 0, NULL, 0));
		link_push(irlist, _jmp(szfalse));

		link_push(irlist, _lbl(sztrue));
		link_push(irlist, _mov(r9, rbx, 0, NULL, 0));

		link_push(irlist, _lbl(szfalse));
		link_push(irlist, _push(rbx, 0, 0, NULL));
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
	SYMBOL* symbol = NULL;
	int depth = 0;
	switch (term->kind)
	{
	case TERM_VAR:
		ir_var(term->val.var);
		
		break;
	case TERM_ACT_LIST:
		// refer to old implementation
		symbol = getSymbolDepth(term->table, term->val.term_act_list.id, &depth);
		char* func_name = create_label(FUNC, symbol->name, 0);

		ir_act_list(term->val.term_act_list.act_list);

		/*if (depth == 0)
			link_push(irlist, _push(rbp, 16, 1, NULL)); // same scope
		else if (depth > 0)
		{
			link_push(irlist, _mov(rbp, r15, 16, NULL, 1)); // reverse the order
			for (int i = 0; i < (depth - 1); i++)
			{
				link_push(irlist, _mov(r15, r15, 16, NULL, 1));
			}
			link_push(irlist, _push(r15, symbol->var_offset, 1, NULL));
		}*/

		link_push(irlist, _call(func_name));
		link_push(irlist, _add(unknown, rsp, symbol->param_count * 8)); // add to stack counter to 'deallocate' local variables
		link_push(irlist, _push(rax, 0, 0, NULL));
		break;
	case TERM_PARENTHESES:
		ir_exp(term->val.exp);
		break;
	case TERM_NOT:
		ir_term(term->val.term);		
		link_push(irlist, _pop(rbx)); // pop term into rbx
		link_push(irlist, _push(rcx, 0, 0, NULL)); // backup rcx
		link_push(irlist, _push(unknown, 1, 0, NULL)); // push 1 to stack
		link_push(irlist, _pop(rcx)); // pop 1 into rcx
		link_push(irlist, _xor(rcx, rbx)); // xor 1 with rbx to negate value
		link_push(irlist, _pop(rcx)); // restore rcx
		link_push(irlist, _push(rbx, 0, 0, NULL)); // push rbx onto stack
		break;
	case TERM_ABSOLUTE:
		ir_exp(term->val.exp);

		if (term->val.exp->typeinfo->type == TYPE_INT)
		{
			link_push(irlist, _pop(rbx));
			int ilabel = label_count++;
			char* szlabel = create_label(FLOW, "abs", ilabel);

			link_push(irlist, _push(rcx, 0, 0, NULL)); // backup rcx
			link_push(irlist, _push(unknown, 0, 0, NULL)); // push 0 to stack
			link_push(irlist, _pop(rcx)); // pop 0 into rcx
			link_push(irlist, _cmp(rcx, rbx)); // compare
			link_push(irlist, _jge(szlabel));
			
			link_push(irlist, _neg(rbx)); // if the value is negative, neg will multiply the value by -1, thus we will get a positive integer
			link_push(irlist, _lbl(szlabel));

			link_push(irlist, _push(rbx, 0, 0, NULL));
			link_push(irlist, _pop(rcx)); // restore rcx
		}
		else if (term->val.exp->typeinfo->type == TYPE_ARRAY) // Array indexing doesn't work, so this implementation won't eiter
		{
			link_push(irlist, _pop(rax));
			link_push(irlist, _xor(rcx, rcx));
			//link_push(irlist, _push()); 
		}

		break;
	case TERM_NUM:
		link_push(irlist, _push(unknown, term->val.num, 0, NULL));
		break;
	case TERM_TRUE:
		link_push(irlist, _push(unknown, 1, 0, NULL));
		break;
	case TERM_FALSE:
	case TERM_NULL:
		link_push(irlist, _push(unknown, 0, 0, NULL));
		break;
	default:
		break;
	}
}

void ir_var(VAR* var) // revisit this
{
	SYMBOL* symbol = NULL;
	int depth = 0;
	switch (var->kind)
	{
	case VAR_ID:
		// Static link lookup
		symbol = getSymbolDepth(var->table, var->id, &depth); // get the offset from base scope to current scopes 
		if (!symbol)
		{
			fprintf(stderr, "[codegen error] can't retrieve symbol for %s @ %d\n", var->id, var->lineno);
			exit(1);
		}

		if ((symbol->typeinfo->type == TYPE_ARRAY || symbol->typeinfo->type == TYPE_RECORD) && symbol->kind != PARAMETER)
		{
			link_push(irlist, _push(unknown, 0, 0, var->id));
		}
		else
		{
			if (depth == 0)
			{
				link_push(irlist, _push(rbp, symbol->var_offset, 1, NULL)); // same scope
			}
			else if (depth > offset_depth - depth) // get the difference in scopes
			{
				link_push(irlist, _mov(rbp, r15, 16, NULL, 1)); // REVERSE IT
				for (int i = 0; i < ((offset_depth - depth) - 1); i++) 	// iterator over the scope difference and get the value from previous
				{														// frame/base pointer
					link_push(irlist, _mov(r15, r15, 16, NULL, 1));
				}
				link_push(irlist, _push(r15, symbol->var_offset, 1, NULL)); // finally the push the value to stack so we can pop it later
			}
		}

		break;
	case VAR_ARRAY:
		ir_var(var->val.var_array.var); // Doesn't work...
		link_push(irlist, _pop(rsi));
		ir_exp(var->val.var_array.exp);
		link_push(irlist, _pop(rdi));
		link_push(irlist, _inc(rdi)); // increment, first element is storing size
		link_push(irlist, _raw("push (%rsi,rdi,8)")); // store the rdi'th element on the stack so we can pop it into a register later
		break;
	case VAR_RECORD:
		fprintf(stderr, "VAR_RECORD\n"); // TODO
		break;
	}
}

void function_prolog(SYMBOL_TABLE* scope)
{
	link_push(irlist, _push(rbp, 0, 0, NULL)); 		// save calling functions base pointer
	link_push(irlist, _mov(rsp, rbp, 0, NULL, 0)); 	// move stack pointer into base pointer
	allocate_local_vars();
	imc->local_var_count = 0;

	// CALLEE
	link_push(irlist, _push(rbx, 0, 0, NULL));
	link_push(irlist, _push(rsi, 0, 0, NULL));
	link_push(irlist, _push(rdi, 0, 0, NULL));

	// CALLER
	link_push(irlist, _push(rcx, 0, 0, NULL));
	link_push(irlist, _push(rdx, 0, 0, NULL));
	offset_depth++;
}

void function_epilog() // do we really need more registers when we're not doing any register allocation?
{
	// CALLER
	link_push(irlist, _pop(rdx));
	link_push(irlist, _pop(rcx));

	// CALLEE
	link_push(irlist, _pop(rdi));
	link_push(irlist, _pop(rsi));
	link_push(irlist, _pop(rbx));

	link_push(irlist, _mov(rbp, rsp, 0, NULL, 0));
	link_push(irlist, _pop(rbp));
	offset_depth--;
}

void allocate_local_vars()
{
	int varcount = imc->local_var_count / OFFSET_SIZE;
	for (int i = 0; i < varcount; i++)
		link_push(irlist, _push(unknown, 0, 0, NULL)); // push x amount of 0 values onto the stack so we can put values into their place later
}

char* create_label(LABEL_KIND kind, char* content, int offset)
{
	char* label = malloc(30 * sizeof(char));
	switch (kind)
	{
	case FUNC:
		sprintf(label, "f_%s", content);
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

int is_already_defined(LINKEDLIST *definedList, char *labelName) 
{
	LINKEDLIST *iterator = definedList;

	while (iterator->data != NULL)
	{
		if (strcmp(labelName, iterator->data) == 0)
			return 1;

		iterator = iterator->next;
	}
	return 0;
}

void data_section() // revisit / rewrite
{
	link_push(irlist, _dir(".data"));

	link_push(irlist, _dir("pnum: \n\t.string \"%d\\n\""));
	link_push(irlist, _dir("ptrue: \n\t.string \"true\\n\""));
	link_push(irlist, _dir("pfalse: \n\t.string \"false\\n\""));
	link_push(irlist, _dir("pnull: \n\t.string \"null\\n\""));

	link_push(irlist, _spc("heap_pointer", OFFSET_SIZE * 1024)); // initialize heap max size
	link_push(irlist, _spc("heap_next", OFFSET_SIZE));

	if (link_length(datalist) < 1)
		return;

	LINKEDLIST* iterator = datalist;
	LINKEDLIST* definitions = link_initialize();

	while (iterator != NULL)
	{
		VAR_TYPE* vtype = (VAR_TYPE*)iterator->data;
		SYMBOL* symbol = getSymbol(vtype->table, vtype->id);

		if (symbol && (symbol->typeinfo->type == TYPE_ARRAY || symbol->typeinfo->type == TYPE_RECORD))
		{
			if (is_already_defined(definitions, vtype->id) == 0) // did we define it already?
			{
				link_push(irlist, _spc(vtype->id, OFFSET_SIZE));
				link_push(definitions, vtype->id);
			}
		}
		iterator = iterator->next;
	}
}