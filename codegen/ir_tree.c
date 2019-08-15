#include <stdio.h>

#include "ir_tree.h"
#include "../symbols/stack.h"
#include "../symbols/linkedlist.h"
#include "../symbols/memory.h"

#define OFFSET_SIZE 8

STACK* function_stack;
LINKEDLIST* irlist;
LINKEDLIST* datalist;

INSTRUCTION* print_num;
INSTRUCTION* print_true;
INSTRUCTION* print_false;
INSTRUCTION* print_null;

int label_count = 0;
int should_print = 0;
int offset_depth = 0;
int var_offset = 8;
int func_count = 0;

IMMEDIATECODE* imc;

LINKEDLIST* build_ir_tree(BODY* body, int unused)
{
	fprintf(stderr, "[ir_tree] began intermediate code generation\n");
	function_stack = init_stack();
	irlist = link_initialize();
	datalist = link_initialize();

	print_num = _lbl("$pnum");
	print_true = _lbl("$ptrue");;
	print_false = _lbl("$pfalse");;
	print_null = _lbl("$pnull");;

	link_push(irlist, _dir(".text"));
	LINKEDLIST* first_element = irlist;
	imc = calloc(1, sizeof(IMMEDIATECODE));

	ir_decl_list(body->decl_list);

	link_push(irlist, _dir(".globl main"));
	link_push(irlist, _lbl("main"));
	link_push(irlist, _push(rbp, 0, 0));
	link_push(irlist, _mov(rsp, rbp, 0, NULL));

	allocate_local_vars();

	ir_statement_list(body->statement_list);

	function_epilog(); // cleanup
	link_push(irlist, _mov(unknown, rax, 0, NULL)); // exit code 0 to signal a-ok
	link_push(irlist, _ret());

	body->table->local_var_count = 0;

	//init heap here
	data_section();
	int data_length = link_length(datalist);
	//if (data_length > 0)
	//	link_push(datalist, _mov(heap_base, heap_free));

	return irlist;
}
void ir_func(FUNCTION* func)
{
	push_stack(function_stack, func);
	ir_head(func->head);
	ir_body(func->body);
	pop_stack(function_stack);
}
void ir_head(HEAD* head)
{
	SYMBOL* symbol = getSymbol(head->table, head->id);
	char* label = create_label(FUNC, symbol->name, func_count++);
	link_push(irlist, _lbl(label));
	imc->kind = PARAM;
	ir_par_decl_list(head->par_decl_list); // allocate room on the stack before the function prolog
}

void ir_body(BODY* body)
{
	ir_decl_list(body->decl_list); 	
	function_prolog(body->table);
	ir_statement_list(body->statement_list);
}

void ir_par_decl_list(PAR_DECL_LIST* pdecl)
{
	switch (pdecl->kind)
	{
	case PAR_DECL_LIST_POPLUATED:
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
	// TODO
	SYMBOL* symbol = getSymbol(var_type->table, var_type->id);
	/*if(var_type->type->kind != RECORD_T) // assume local var
	{
		var_offset += 8;
		link_push(irlist, "pushq $0");
		symbol->var_offset = var_offset * -1;
	}*/

	/*if(det->kind == PARAM)
	{
		var_offset += 8;
		fprintf(stderr, "ir_var_type[PARAM]::var_offset %d - symbol: %d\n", var_offset, symbol->offset);
		symbol->offset = var_offset;
	}*/
	switch(imc->kind)
	{
		case PARAM:
			var_offset += 8; // increment first
			symbol->offset = var_offset;
			fprintf(stderr, "ir_var_type[PARAM]::offset %d\n", var_offset);
		break;
		case LOCAL:
			symbol->offset = -var_offset; // negate offset, we're looking inside the function, not outside
			//link_push(irlist, "pushq $0		#allocate room on the stack for local var");
			//link_push(irlist, _push(unknown, 0, 0));
			fprintf(stderr, "ir_var_type[LOCAL]::offset %d\n", -var_offset);
			imc->local_var_count += OFFSET_SIZE;
			var_offset += OFFSET_SIZE; // increment here because rbp is at 0, first args must be at -8 and second -16 etc..
		break;
		default:
			// Heap it ?
		break;
	}
	// IR_TYPE ???
	// var_type->type <- needs to be handled
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
	fprintf(stderr, "ir_declaration\n");
	SYMBOL* symbol = NULL;
	switch (decl->kind)
	{
	case DECLARATION_ID:
		symbol = getSymbol(decl->table, decl->val.identifier.id);
		fprintf(stderr, "ir_declaration::%s\n", decl->val.identifier.id);
		if(symbol->symbol_kind == SYMBOL_RECORD_MEMBER)
		{
			// not a local var, maybe heap it
			// TODO
			fprintf(stderr, "called SYMBOL_RECORD_MEMBER\n");
			imc->kind = RECORD;
		}
		else
		{
			var_offset += 8;
			symbol->var_offset = var_offset;
			link_push(irlist, _push(unknown, 0, 0));
			fprintf(stderr, "called ir_declaration_id::ELSE\n");
		}
		
		break;
	case DECLARATION_FUNC:
		ir_func(decl->val.function);
		break;
	case DECLARATION_VAR:
		var_offset = 8; // reset offset
		fprintf(stderr, "DECLARATION_VAR\n");
		if (decl->symbol->symbol_kind == SYMBOL_RECORD)
		{
			fprintf(stderr, "declaration_var::SYMBOL_RECORD\n");
			imc->kind = RECORD;
		}
		else
			imc->kind = LOCAL;

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
	switch (statement->kind)
	{
	case RETURN:
		ir_exp(statement->val.stat_return.exp);
		if(statement->val.exp->symbol_value->kind == INT_T || statement->val.exp->symbol_value->kind == BOOL_T)
		{
			// we know the return value is stored at top of stack
			// so we pop it into RAX and return

			link_push(irlist, _pop(rax));
			function_epilog();
			link_push(irlist, _ret());
		}
		else
		{
			// shouldn't happen..
			fprintf(stderr, "invalid return type\n");
			exit(0);
		}
		break;
	case WRITE:
		link_push(irlist, _push(rax, 0, 0)); // backup whatever is in rax
		SYMBOL_VALUE* symbolval = statement->val.exp->symbol_value;
		// refer to backedup files on how to write in asm..		
		switch (symbolval->kind)
		{
		case SYMBOL_INT:
			ir_exp(statement->val.exp);
			link_push(irlist, _pop(rsi));
			link_push(irlist, _mov(unknown, rdi, 0, "pnum"));
			//link_push(irlist, _mov(rax, rsi));
			link_push(irlist, _mov(unknown, rax, 0, NULL));
			break;
		case SYMBOL_BOOL:
			ir_exp(statement->val.exp);
			break;
		case SYMBOL_NULL:
			break;
		default:
			break;
		}
		link_push(irlist, _call("printf"));
		link_push(irlist, _pop(rax));
		break;
	case ALLOCATE:
		ir_exp(statement->val.stat_allocate.length);
		ir_var(statement->val.stat_allocate.var);
		// do some logic here, decide which register to put shit in, maybe use immediate code
		break;
	case ASSIGN:
		link_push(irlist, _push(rbx, 0, 0)); // backup rbx
		ir_exp(statement->val.stat_assign.exp);
		ir_var(statement->val.stat_assign.var);
		link_push(irlist, _pop(rbx)); // restore rbx
		// do some logic here
		SYMBOL* symbol = getSymbol(statement->table, statement->val.stat_assign.var->id);
		link_push(irlist, _mov(rbx, rbp, symbol->offset, NULL));
		fprintf(stderr, "reee offset %d\n", symbol->offset);
		link_push(irlist, _pop(rbx));
		break;
	case IF: // TODO
		ir_exp(statement->val.stat_if.condition);

		// refer to old implementation
		break;
	case WHILE:
		ir_exp(statement->val.stat_while.condition);
		ir_statement(statement->val.stat_while.stat);

		// refer to old implementation
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
			link_push(irlist, _add(rbx, rcx));
			break;
		}

		link_push(irlist, _push(rcx, 0, 0));
		break;
	case EXP_DIV:
		ir_exp(exp->val.branches.left);
		ir_exp(exp->val.branches.right);
		link_push(irlist, _pop(rbx));
		link_push(irlist, _pop(rax));

		link_push(irlist, _xor(rdx, rdx));
		link_push(irlist, _div(rbx));
		link_push(irlist, _push(rax, 0, 0));
		break;
	case EXP_LESS:
	case EXP_LESS_EQUALS:
	case EXP_NOT_EQUALS:
	case EXP_GREATER:
	case EXP_GREATER_EQUALS:
	case EXP_EQUALS:
		ir_exp(exp->val.branches.left);
		ir_exp(exp->val.branches.right);

		int ilabel = label_count++;
		char* sztrue = create_label(FLOW, "btrue", ilabel);
		char* szfalse = create_label(FLOW, "bfalse", ilabel);

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
		link_push(irlist, _push(unknown, 0, 0)); // push 0 to stack
		link_push(irlist, _pop(rbx)); // pop 0 from stack into rbx
		link_push(irlist, _jmp(szfalse));
		link_push(irlist, _lbl(sztrue)); // create true case
		link_push(irlist, _push(unknown, 1, 0)); // push 1 to stack
		link_push(irlist, _pop(rbx)); // pop 1 from stack into rbx
		link_push(irlist, _lbl(szfalse)); // create false case
		link_push(irlist, _push(rbx, 0, 0));
		break;
	case EXP_AND:
		break;
	case EXP_OR:
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
	//ARGS* arg = NULL;
	SYMBOL* symbol = NULL;
	switch (term->kind)
	{
	case TERM_VAR:
		ir_var(term->val.var);
		
		break;
	case TERM_ACT_LIST:
		// refer to old implementation
		symbol = getSymbol(term->table, term->val.term_act_list.id);
		char* func_name = create_label(FUNC, symbol->name, 0);
		int icaller = term->table->table_id;
		int icallee = symbol->table_id;

		ir_act_list(term->val.term_act_list.act_list);

		link_push(irlist, _call(func_name));
		//link_push(irlist, _add(rcx, rbx)); // this needs rework
		//link_push(irlist, _push(rax, 0, 0));
		break;
	case TERM_PARENTHESES:
		ir_exp(term->val.exp);
		break;
	case TERM_NOT:
		ir_term(term->val.term);		
		link_push(irlist, _pop(rbx)); // pop term into rbx
		link_push(irlist, _push(rcx, 0, 0)); // backup rcx
		link_push(irlist, _push(unknown, 1, 0)); // push 1 to stack
		link_push(irlist, _pop(rcx)); // pop 1 into rcx
		link_push(irlist, _xor(rcx, rbx)); // xor 1 with rbx to negate value
		link_push(irlist, _push(rbx, 0, 0)); // push rbx onto stack
		link_push(irlist, _pop(rcx)); // restore rcx
		break;
	case TERM_ABSOLUTE:
		ir_exp(term->val.exp);

		if (term->val.exp->symbol_value->kind == SYMBOL_INT)
		{
			link_push(irlist, _pop(rbx));
			int ilabel = label_count++;
			char* szlabel = create_label(FLOW, "abs", ilabel);

			link_push(irlist, _push(rcx, 0, 0)); // backup rcx
			link_push(irlist, _push(unknown, 0, 0)); // push 0 to stack
			link_push(irlist, _pop(rcx)); // pop 0 into rcx
			link_push(irlist, _cmp(rcx, rbx)); // compare
			link_push(irlist, _jge(szlabel));
			
			link_push(irlist, _neg("")); // needs to take register instead of char
			link_push(irlist, _lbl(szlabel));

			link_push(irlist, _push(rbx, 0, 0));
			link_push(irlist, _pop(rcx)); // restore rcx
		}
		else if (term->val.exp->symbol_value->kind == SYMBOL_ARRAY)
		{
			link_push(irlist, _pop(rax));
			link_push(irlist, _xor(rcx, rcx));
			//link_push(irlist, _push()); //needs to rework this to push 16(%rax) 
		}

		break;
	case TERM_NUM:
		link_push(irlist, _push(unknown, term->val.num, 0));
		break;
	case TERM_TRUE:
		link_push(irlist, _push(unknown, 1, 0));
		break;
	case TERM_FALSE:
	case TERM_NULL:
		link_push(irlist, _push(unknown, 0, 0));
		break;
	default:
		break;
	}
}

void ir_var(VAR* var) // revisit this
{
	switch (var->kind) // TODO
	{
	case VAR_ID:
		fprintf(stderr, "VAR_ID\n");
		SYMBOL* symbol = getSymbol(var->table, var->id);
		int offset = symbol->offset;

		//if (false) // if we are assigning the variables passed as arguments
		//{

		//}
		//elseb
		//{
		//symbol->symbol_type
		fprintf(stderr, "symboltype: %d : symbolkind %d\n", symbol->symbol_type, symbol->symbol_kind);
		if(symbol->symbol_kind == SYMBOL_PARAMETER)
			link_push(irlist, _push(rbp, offset, 1));

		//det->offset = offset;
		//}

		break;
	case VAR_ARRAY:
		fprintf(stderr, "VAR_ARRAY\n");
		break;
	case VAR_RECORD:
		fprintf(stderr, "VAR_RECORD\n");
		break;
	}
}

void function_prolog(SYMBOL_TABLE* scope)
{
	link_push(irlist, _push(rbp, 0, 0)); 		// save calling functions base pointer
	link_push(irlist, _mov(rsp, rbp, 0, NULL)); // move stack pointer into base pointer
												// allocate x*8 amount of bytes for this funcs local variables
	allocate_local_vars();					// so that we can refer to them on the stack
	imc->local_var_count = 0;

	// CALLEE
	link_push(irlist, _push(rbx, 0, 0));
	link_push(irlist, _push(rsi, 0, 0));
	link_push(irlist, _push(rdi, 0, 0));

	// CALLER
	link_push(irlist, _push(rcx, 0, 0));
	link_push(irlist, _push(rdx, 0, 0));
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

	link_push(irlist, _mov(rbp, rsp, 0, NULL));
	link_push(irlist, _pop(rbp));
}

void allocate_local_vars()
{
	int varcount = imc->local_var_count / OFFSET_SIZE;
	for (int i = 0; i < varcount; i++)
	{
		link_push(irlist, _push(unknown, 0, 0));
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

		if (symbol && (symbol->symbol_kind == SYMBOL_ARRAY || symbol->symbol_kind == SYMBOL_RECORD))
		{
			if (!is_already_defined(definitions, vtype->id)) // did we define it already?
			{
				link_push(irlist, _spc(vtype->id, OFFSET_SIZE));
				link_push(definitions, vtype->id);
			}
		}
		iterator = iterator->next;
	}
}