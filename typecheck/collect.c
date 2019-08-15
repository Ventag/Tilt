#include "collect.h"
#include "../expressions/tree.h"
#include "../symbols/linkedlist.h"

int unknown_user_types = 0;
int function_count = 0;
int current_offset = 1;
int args_count = 0;

void increment_args_count()
{
	args_count++;
}

void reset_args_count()
{
	args_count = 0;
}

#define INCREMENT_OFFSET (current_offset++)
#define RESET_OFFSET (current_offset = 1)
#define MAX_FUNCTION_NAME_LENGTH 128

LINKEDLIST* function_names;

SYMBOL_TABLE* parent_table;

void collect(BODY* body)
{
	function_names = link_initialize();
	fprintf(stderr, "[collect] type collection started\n");
	parent_table = initSymbolTable(0);
	collect_body(body, parent_table);
	dumpSymbolTable(parent_table);
}

void collect_func(FUNCTION* func, SYMBOL_TABLE* _st)
{
	func->table = scopeSymbolTable(_st);

	collect_head(func->head, func->table);
	collect_body(func->body, func->table);
	func->symbol_value = func->head->symbol_value;
}

void collect_head(HEAD* head, SYMBOL_TABLE* _st)
{
	if(sizeof(head->id) > MAX_FUNCTION_NAME_LENGTH)
	{
		fprintf(stderr, "function name is too long @ %s\n", head->lineno);
		exit(1);
	}
	head->table = _st;
	head->symbol_value = create_symbol_value(SYMBOL_FUNC);

	SYMBOL* symbol = putSymbol(_st->next, head->id, head->symbol_value);
	collect_par_decl_list(head->par_decl_list, _st);
	symbol->param_count = collect_par_decl_list(head->par_decl_list, _st);
	RESET_OFFSET;
	reset_args_count();

	char* data = link_seek(function_names, (char*)head->id);
	if(data != NULL)
	{
		fprintf(stderr, "function redifinition @ %d\n", head->lineno);
		exit(1);
	}
	link_push(function_names, head->id);
	
	SYMBOL_VALUE *type = collect_type(head->type, _st);
	head->symbol_value->return_type = type;
}

void collect_body(BODY* body, SYMBOL_TABLE* _st)
{
	body->table = _st;
	collect_decl_list(body->decl_list, _st);
	collect_statement_list(body->statement_list, _st);
}

SYMBOL_VALUE* collect_type(TYPE* type, SYMBOL_TABLE* _st)
{
	type->table = _st;
	SYMBOL* symbol = NULL;

	switch (type->kind)
	{
	case ID_T: // TODO
		fprintf(stderr, "[collect_type::ID_T] %s\n", type->val.id);
		symbol = getSymbol(_st, type->val.id);
		if (symbol != NULL && symbol->symbol_type != SYMBOL_UNKNOWN)
		{
			type->symbol_value = symbol->symbol_value;
			fprintf(stderr, "found symbol current\n");
			return symbol->symbol_value;
		}
		else if (symbol == NULL && _st->parent != NULL)
		{
			symbol = getSymbol(_st->parent, type->val.id);
			if (symbol != NULL && symbol->symbol_type != SYMBOL_UNKNOWN)
			{
				type->symbol_value = symbol->symbol_value;
				fprintf(stderr, "found symbol parent\n");
				return symbol->symbol_value;
			}
		}

		type->symbol_value = create_symbol_value(SYMBOL_UNKNOWN);
		break;
	case INT_T:
		//fprintf(stderr, "collect_type::INT_T\n");
		type->symbol_value = create_symbol_value(SYMBOL_INT);
		break;
	case BOOL_T:
		//fprintf(stderr, "collect_type::BOOL_T\n");
		type->symbol_value = create_symbol_value(SYMBOL_BOOL);
		break;
	case ARRAY_T:
		//fprintf(stderr, "collect_type::ARRAY_T\n");
		type->symbol_value = create_symbol_value(SYMBOL_ARRAY);
		type->symbol_value->array_next_value = collect_type(type->val.type, _st);
		break;
	case RECORD_T: // create a symbol table for each record
		//fprintf(stderr, "collect_type::RECORD_T\n");
		type->symbol_value = create_symbol_value(SYMBOL_RECORD);
		type->symbol_value->child_scope = scopeSymbolTable(_st);
		type->symbol_value->child_scope->parent = _st;
		type->symbol_value->length = collect_var_decl_list(type->val.var_decl_list, type->symbol_value->child_scope, SYMBOL_RECORD_MEMBER);
		RESET_OFFSET;
		type->symbol_value->records = type->val.var_decl_list;
		break;
	default:
		//fprintf(stderr, "error: collect_type [unknown type]\n");
		exit(1);
		break;
	}

	return type->symbol_value;
}

SYMBOL_VALUE* create_symbol_value(SYMBOL_TYPES kind)
{
	SYMBOL_VALUE* symbol = NEW(SYMBOL_VALUE);
	symbol->array_next_value = NULL;
	symbol->child_scope = NULL;
	symbol->records = NULL;
	symbol->return_type = NULL;
	symbol->kind = kind;

	return symbol;
}

int collect_par_decl_list(PAR_DECL_LIST* pdecl, SYMBOL_TABLE* _st)
{
	pdecl->table = _st;
	int count = 0;
	switch (pdecl->kind)
	{
	case PAR_DECL_LIST_POPLUATED:
		count += collect_var_decl_list(pdecl->var_decl_list, _st, SYMBOL_PARAMETER);
		increment_args_count();
		break;
	case PAR_DECL_LIST_EMPTY:
		return 0;
	}

	return count;
}

int collect_var_decl_list(VAR_DECL_LIST* vdecl, SYMBOL_TABLE* _st, SYMBOL_KINDS kind)
{
	vdecl->table = _st;
	int count = 1;
	switch (vdecl->kind)
	{
	case VDECL_LIST:
		collect_var_type(vdecl->var_type, _st, kind);
		count += collect_var_decl_list(vdecl->var_decl_list, _st, kind);
		increment_args_count();
		break;
	case VDECL_TYPE:
		collect_var_type(vdecl->var_type, _st, kind);
		break;
	}

	return count;
}

void collect_var_type(VAR_TYPE* vtype, SYMBOL_TABLE* _st, SYMBOL_KINDS kind)
{
	vtype->table = _st;

	// Acquire the type of the variable
	SYMBOL_VALUE* symbol_type = collect_type(vtype->type, _st);

	if (symbol_type->kind == SYMBOL_UNKNOWN) // Only happens if vtype->type is ID and it cant be found in local/outer scope
		unknown_user_types++;

	vtype->symbol = putSymbol(_st, vtype->id, symbol_type);
}

void collect_decl_list(DECL_LIST* declist, SYMBOL_TABLE* _st)
{
	declist->table = _st;

	switch (declist->kind)
	{
	case DECL_LIST_POPULATED:
		collect_declaration(declist->declaration, _st);
		collect_decl_list(declist->decl_list, _st);
		break;
	case DECL_LIST_EMPTY:
		break;
	}
}

void collect_declaration(DECLARATION* decl, SYMBOL_TABLE* _st)
{
	decl->table = _st;
	SYMBOL_VALUE* symbol_value = NULL;
	SYMBOL* symbol = NULL;

	switch (decl->kind)
	{
	case DECLARATION_ID:
		fprintf(stderr, "collect_declaration::DECLARATION_ID %s\n", decl->val.identifier.id);
		symbol_value = collect_type(decl->val.identifier.type, _st);

		if (symbol_value->kind == SYMBOL_UNKNOWN)
		{
			unknown_user_types++;
			fprintf(stderr, "collect_declaration::DECLARATION_ID found unknown type\n");
		}

		symbol = putSymbol(_st, decl->val.identifier.id, symbol_value);
		if(!symbol)
			exit(1);

		symbol->symbol_kind = SYMBOL_TYPE_DEFINITION;
		fprintf(stderr, "collect_declaration::DECLARATION_ID end\n");
		break;
	case DECLARATION_FUNC:
		fprintf(stderr, "collect_declaration::DECLARATION_FUNC\n");
		collect_func(decl->val.function, _st);
		break;
	case DECLARATION_VAR:
		fprintf(stderr, "collect_declaration::DECLARATION_VAR\n");
		collect_var_decl_list(decl->val.var_decl_list, _st, SYMBOL_LOCAL_VARIABLE);
		decl->symbol = decl->val.var_decl_list->var_type->symbol;
		break;
	}
}

void collect_statement_list(STATEMENT_LIST* list, SYMBOL_TABLE* _st)
{
	list->table = _st;
	switch (list->kind)
	{
	case STATEMENT_LIST_LIST:
		collect_statement_list(list->statement_list, _st);
		collect_statement(list->statement, _st);
		break;
	case STATEMENT_LIST_ELEMENT:
		collect_statement(list->statement, _st);
		break;
	}
}

void collect_statement(STATEMENT* stat, SYMBOL_TABLE* _st)
{
	stat->table = _st;
	switch (stat->kind)
	{
	case RETURN:
		collect_expression(stat->val.stat_return.exp, _st);
		break;
	case WRITE:
		collect_expression(stat->val.exp, _st);
		break;
	case ALLOCATE:
		collect_variable(stat->val.stat_allocate.var, _st);
		collect_expression(stat->val.stat_allocate.length, _st);
		break;
	case ASSIGN:
		collect_variable(stat->val.stat_assign.var, _st);
		collect_expression(stat->val.stat_assign.exp, _st);
		break;
	case IF:
		collect_expression(stat->val.stat_if.condition, _st);
		collect_statement(stat->val.stat_if.stat, _st);
		collect_else(stat->val.stat_if.optional_else, _st);
		break;
	case WHILE:
		collect_expression(stat->val.stat_while.condition, _st);
		collect_statement(stat->val.stat_while.stat, _st);
		break;
	case WHILE_LIST:
		collect_statement_list(stat->val.statement_list, _st);
		break;

	default: break;
	}
}

void collect_else(STATEMENT_ELSE* stat_else, SYMBOL_TABLE* _st)
{
	stat_else->table = _st;

	switch (stat_else->kind)
	{
	case ELSE_ACTIVE:
		collect_statement(stat_else->statement, _st);
		break;
	case ELSE_INACTIVE:
		break;
	}
}

void collect_variable(VAR* var, SYMBOL_TABLE* _st)
{
	var->table = _st;
	switch (var->kind)
	{
	case VAR_ID:
		break;
	case VAR_ARRAY:
		collect_variable(var->val.var_array.var, _st);
		collect_expression(var->val.var_array.exp, _st);
		break;
	case VAR_RECORD:
		collect_variable(var->val.var_record.var, _st);
		break;
	}
}

void collect_expression(EXP* exp, SYMBOL_TABLE* _st)
{
	exp->table = _st;

	switch (exp->kind)
	{
	case EXP_TERM:
		collect_term(exp->val.term, _st);
		break;	
	default:
		collect_expression(exp->val.branches.left, _st);
		collect_expression(exp->val.branches.right, _st);
		break;
	}
}

void collect_term(TERM* term, SYMBOL_TABLE* _st)
{
	term->table = _st;
	switch (term->kind)
	{
	case TERM_VAR:
		collect_variable(term->val.var, _st);
		break;
	case TERM_ACT_LIST:
		collect_act_list(term->val.term_act_list.act_list, _st);
		break;
	case TERM_PARENTHESES:
		collect_expression(term->val.exp, _st);
		break;
	case TERM_NOT:
		collect_term(term->val.term, _st);
		break;
	case TERM_ABSOLUTE:
		collect_expression(term->val.exp, _st);
		break;
	case TERM_NUM:
		term->symbol_value = create_symbol_value(SYMBOL_INT);
		break;
	case TERM_TRUE:
		term->symbol_value = create_symbol_value(SYMBOL_BOOL);
		break;
	case TERM_FALSE:
		term->symbol_value = create_symbol_value(SYMBOL_BOOL);
		break;
	case TERM_NULL:
		term->symbol_value = create_symbol_value(SYMBOL_NULL);
	case TERM_UMINUS:
		collect_term(term->val.term, _st);
		break;

	default: break;
	}
}

void collect_act_list(ACT_LIST* act_list, SYMBOL_TABLE* _st)
{
	act_list->table = _st;
	switch (act_list->kind)
	{
	case ACT_LIST_POPULATED:
		collect_exp_list(act_list->exp_list, _st);
		break;
	case ACT_LIST_EMPTY:
		break;
	}
}

void collect_exp_list(EXP_LIST* exp_list, SYMBOL_TABLE* _st)
{
	exp_list->table = _st;
	switch (exp_list->kind)
	{
	case EXPRESSION_LIST:
		collect_exp_list(exp_list->exp_list, _st);
		collect_expression(exp_list->exp, _st);
		break;
	case EXPRESSION:
		collect_expression(exp_list->exp, _st);
		break;
	default: break;
	}
}