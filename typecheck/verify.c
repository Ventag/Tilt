#include "process.h"
#include "collect.h"
#include "../symbols/stack.h"

STACK* function_stack;

void verify(BODY* body)
{
	fprintf(stderr, "[verify] type verification started\n");
	function_stack = init_stack();
	verify_body(body);
}

void verify_head(HEAD* head)
{
	verify_par_decl_list(head->par_decl_list);
	verify_type(head->type);
}

void verify_body(BODY* body)
{
	verify_decl_list(body->decl_list);
	verify_statement_list(body->statement_list);
}

void verify_function(FUNCTION* func)
{
	push_stack(function_stack, func);
	verify_head(func->head);
	verify_body(func->body);
	pop_stack(function_stack);
}

void verify_type(TYPE* type)
{
	switch (type->kind)
	{
	case ARRAY_T:
		verify_type(type->val.type);
		break;
	case RECORD_T:
		verify_var_decl_list(type->val.var_decl_list);
		break;
	}
}

void verify_par_decl_list(PAR_DECL_LIST* pdecl_list)
{
	switch (pdecl_list->kind)
	{
	case PAR_DECL_LIST_POPLUATED:
		verify_var_decl_list(pdecl_list->var_decl_list);
		break;
	case PAR_DECL_LIST_EMPTY:
		break;
	}
}

void verify_var_decl_list(VAR_DECL_LIST* vdecl_list)
{
	switch (vdecl_list->kind)
	{
	case VDECL_LIST:
		verify_var_decl_list(vdecl_list->var_decl_list);
		verify_var_type(vdecl_list->var_type);
		break;
	case VDECL_TYPE:
		break;
	}
}

void verify_var_type(VAR_TYPE* vtype)
{
	verify_type(vtype->type);
	if (vtype->symbol->symbol_value->kind == SYMBOL_UNKNOWN)
	{
		fprintf(stderr, "[verify error] can't deduce type @ %d\n", vtype->lineno);
		exit(1);
	}
}

void verify_decl_list(DECL_LIST* decl_list)
{
	switch (decl_list->kind)
	{
	case DECL_LIST_POPULATED:
		verify_decl_list(decl_list->decl_list);
		verify_declaration(decl_list->declaration);
		break;
	case DECL_LIST_EMPTY:
		break;
	}
}

void verify_declaration(DECLARATION* decl)
{
	switch (decl->kind)
	{
	case DECLARATION_ID:
		verify_type(decl->val.identifier.type);
		break;
	case DECLARATION_FUNC:
		verify_function(decl->val.function);
		break;
	case DECLARATION_VAR:
		verify_var_decl_list(decl->val.var_decl_list);
		break;
	}
}

void verify_statement(STATEMENT* statement)
{
	SYMBOL_VALUE *left, *right = NULL;
	FUNCTION* func = NULL;
	switch (statement->kind)
	{
	case RETURN:
		verify_exp(statement->val.stat_return.exp);
		left = statement->val.stat_return.exp->symbol_value;
		if (!is_stack_empty(function_stack))
		{
			func = peek_stack(function_stack);
			right = func->symbol_value->return_type;
			if (left->kind != right->kind)
			{
				fprintf(stderr, "[verify error] function return type mistmatch @ %d\nleft: %d\nright: %d\n", statement->lineno, left->kind, right->kind);
				exit(1);
			}
		}
		break;
	case WRITE:
		verify_exp(statement->val.exp);
		if (statement->val.exp->symbol_value->kind == SYMBOL_ARRAY && statement->val.exp->val.term->kind != TERM_ABSOLUTE
			|| statement->val.exp->symbol_value->kind == SYMBOL_RECORD)
		{
			fprintf(stderr, "[typechecking error] writing type, did you try to write an array or record? @ %d\n", statement->lineno);
			exit(1);
		}
		break;
	case ALLOCATE:
		verify_var(statement->val.stat_allocate.var);
		verify_exp(statement->val.stat_allocate.length);

		left = statement->val.stat_allocate.var->symbol_value;
		if (left->kind != SYMBOL_RECORD && left->kind != SYMBOL_ARRAY)
		{
			fprintf(stderr, "[typechecking error] cannot allocate specific var type @ %d type is %d\n", statement->lineno, left->kind);
			exit(1);
		}

		right = statement->val.stat_allocate.length->symbol_value;
		if(right->kind != SYMBOL_INT)
		{
			fprintf(stderr, "[typechecking error] allocate type differs from INT @ %d type is %d\n", statement->lineno, statement->val.stat_allocate.length->symbol_value->kind);
			exit(1);
		}
		break;
	case ASSIGN:
		verify_var(statement->val.stat_assign.var);
		verify_exp(statement->val.stat_assign.exp);

		left = statement->val.stat_assign.var->symbol_value;
		right = statement->val.stat_assign.exp->symbol_value;

		/*
		TODO: Handle record assignments here
		*/

		if (left->kind != right->kind)
		{
			fprintf(stderr, "[typechecking error] this needs rework @ %d", statement->lineno);
			exit(1);
		}

		break;
	case IF:
		verify_exp(statement->val.stat_if.condition);
		verify_statement(statement->val.stat_if.stat);
		verify_else(statement->val.stat_if.optional_else);

		if (statement->val.stat_if.condition->symbol_value->kind != SYMBOL_BOOL)
		{
			fprintf(stderr, "[type verification error] conditionals can only be boolean @ %d\n", statement->lineno);
			exit(1);
		}
		break;
	case WHILE:
		verify_exp(statement->val.stat_while.condition);
		verify_statement(statement->val.stat_while.stat);

		if (statement->val.stat_while.condition->symbol_value->kind != SYMBOL_BOOL)
		{
			fprintf(stderr, "[type verification error] conditionals can only be boolean @ %d\n", statement->lineno);
			exit(1);
		}
		break;
	case WHILE_LIST:
		verify_statement_list(statement->val.statement_list);
		break;

	default: break;
	}
}

void verify_statement_list(STATEMENT_LIST* statement_list)
{
	switch (statement_list->kind)
	{
	case STATEMENT_LIST_LIST:
		verify_statement_list(statement_list->statement_list);
		verify_statement(statement_list->statement);
		break;
	case STATEMENT_LIST_ELEMENT:
		verify_statement(statement_list->statement);
		break;
	}
}

void verify_else(STATEMENT_ELSE* statement_else)
{
	switch (statement_else->kind)
	{
	case ELSE_INACTIVE:
		break;
	case ELSE_ACTIVE:
		verify_statement(statement_else->statement);
		break;
	}
}

void verify_exp(EXP* exp)
{
	SYMBOL_VALUE *left, *right = NULL;

	switch (exp->kind)
	{
	case EXP_TIMES:
	case EXP_DIV:
	case EXP_PLUS:
	case EXP_MINUS:
		verify_exp(exp->val.branches.left);
		verify_exp(exp->val.branches.right);

		left = exp->val.branches.left->symbol_value;
		right = exp->val.branches.right->symbol_value;

		if (left->kind != SYMBOL_INT || right->kind != SYMBOL_INT)
		{
			fprintf(stderr, "[type verification error] wrong type received, expected int @ %d\n", exp->lineno);
			exit(1);
		}
		else
			exp->symbol_value = create_symbol_value(SYMBOL_INT);
		break;
	case EXP_AND:
	case EXP_OR:
		verify_exp(exp->val.branches.left);
		verify_exp(exp->val.branches.right);

		left = exp->val.branches.left->symbol_value;
		right = exp->val.branches.right->symbol_value;

		if (left->kind != SYMBOL_BOOL || right->kind != SYMBOL_BOOL)
		{
			fprintf(stderr, "[verify] type mismatch, expected boolean expression @ %d\n", exp->lineno);
			exit(1);
		}
		else
		{
			exp->symbol_value = create_symbol_value(SYMBOL_BOOL);
		}
		break;
	case EXP_EQUALS:
	case EXP_NOT_EQUALS:
		verify_exp(exp->val.branches.left);
		verify_exp(exp->val.branches.right);
		left = exp->val.branches.left->symbol_value;
		right = exp->val.branches.right->symbol_value;
		if (left->kind == right->kind)
			exp->symbol_value = create_symbol_value(SYMBOL_BOOL);
		else if (left->kind == SYMBOL_ARRAY && right->kind == SYMBOL_NULL)
			exp->symbol_value = create_symbol_value(SYMBOL_BOOL);
		else if (left->kind == SYMBOL_NULL && right->kind == SYMBOL_ARRAY)
			exp->symbol_value = create_symbol_value(SYMBOL_BOOL);
		else if (left->kind == SYMBOL_RECORD && right->kind == SYMBOL_NULL)
			exp->symbol_value = create_symbol_value(SYMBOL_BOOL);
		else if (left->kind == SYMBOL_NULL && right->kind == SYMBOL_RECORD)
			exp->symbol_value = create_symbol_value(SYMBOL_BOOL);
		else
		{
			fprintf(stderr, "[verify error] type mismatch @ %d\n", exp->lineno);
			exit(1);
		}

		break;
	case EXP_LESS:
	case EXP_LESS_EQUALS:
	case EXP_GREATER:
	case EXP_GREATER_EQUALS:
		verify_exp(exp->val.branches.left);
		verify_exp(exp->val.branches.right);

		left = exp->val.branches.left->symbol_value;
		right = exp->val.branches.right->symbol_value;

		if (left->kind != SYMBOL_INT || right->kind != SYMBOL_INT)
		{
			fprintf(stderr, "[verify error] wrong type received, expected int @ %d\n", exp->lineno);
			exit(1);
		}
		else
			exp->symbol_value = create_symbol_value(SYMBOL_BOOL);
		break;
	case EXP_TERM:
		verify_term(exp->val.term);
		exp->symbol_value = exp->val.term->symbol_value;
		break;
	}
}

void verify_term(TERM* term)
{
	int param_count = 0;
	switch (term->kind)
	{
	case TERM_VAR:
		verify_var(term->val.var);
		term->symbol_value = term->val.var->symbol_value;
		break;
	case TERM_ACT_LIST:
		param_count = verify_act_list(term->val.term_act_list.act_list);
		SYMBOL* symbol = getSymbol(term->table, term->val.term_act_list.id);
		if (!symbol || symbol->symbol_value->kind != SYMBOL_FUNC)
		{
			fprintf(stderr, "[verify error] undefined function %d @ %d\n", symbol->symbol_value->kind, term->lineno);
			exit(1);
		}

		if (param_count < symbol->param_count || param_count > symbol->param_count)
		{
			fprintf(stderr, "[verify error] arguments count mismatch for function %d vs %d @ %d\n", param_count, symbol->parameters, term->lineno);
			exit(1);
		}

		/*
		TODO: Compare call parameters & function parameters
		*/

		term->symbol_value = symbol->symbol_value->return_type;
		break;
	case TERM_PARENTHESES:
		verify_exp(term->val.exp);
		term->symbol_value = term->val.exp->symbol_value;
		break;
	case TERM_NOT:
		if (term->val.term->symbol_value->kind != SYMBOL_BOOL)
		{
			fprintf(stderr, "[verify error] expected boolean @ %d\n", term->lineno);
			exit(1);
		}
		term->symbol_value = term->val.term->symbol_value;
		break;
	case TERM_ABSOLUTE:
		verify_exp(term->val.exp);
		SYMBOL_TYPES kind = term->val.exp->symbol_value->kind;
		//if (kind != SYMBOL_INT || kind != SYMBOL_ARRAY)
		if(kind != SYMBOL_INT && kind != SYMBOL_ARRAY)
		{
			fprintf(stderr, "[verify error] expected int or array @ %d\n", term->lineno);
			fprintf(stderr, "type is %d\n", kind);
			exit(1);
		}

		if (kind == SYMBOL_INT)
			term->symbol_value = create_symbol_value(SYMBOL_INT);
		else
			term->symbol_value = term->val.exp->symbol_value;

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
		break;
	case TERM_UMINUS:
		verify_term(term->val.term);
		if (term->val.term->symbol_value->kind != SYMBOL_INT)
		{
			fprintf(stderr, "[verify error] expected int @ %d\n", term->lineno);
			exit(1);
		}
		term->symbol_value = term->val.term->symbol_value;
		break;
	default:
		break;
	}
}

int verify_var(VAR* var)
{
	SYMBOL* symbol = NULL;
	SYMBOL_TABLE* inner_scope;
	int depth = 1;
	switch (var->kind)
	{
	case VAR_ID:
		//fprintf(stderr, "verify_var_id\n");
		//fprintf(stderr, "name: %s - kind: %d - lineno: %d\n", var->id, var->kind, var->lineno);
		symbol = getSymbol(var->table, var->id);

		if (symbol->symbol_value == NULL)
			fprintf(stderr, "SYMBOL_VALUE is NULL\n");

		if (symbol)
		{
			var->symbol_value = symbol->symbol_value;
			if (symbol->symbol_kind == SYMBOL_TYPE_DEFINITION)
			{
				fprintf(stderr, "[type verification error] symbol is a type @ %d\n", var->lineno);
				exit(1);
			}
		}
		else
		{
			fprintf(stderr, "[type verification error] symbol cannot be found @ %d\n", var->lineno);
			exit(1);
		}
		break;
	case VAR_ARRAY:
		//fprintf(stderr, "verify_var_array\n");
		depth += verify_var(var->val.var_array.var);
		verify_exp(var->val.var_array.exp);

		if (var->val.var_array.exp->symbol_value->kind != SYMBOL_INT)
		{
			fprintf(stderr, "[verify error] expected integer @ %d\n", var->lineno);
			exit(1);
		}

		if (var->val.var_array.var->symbol_value->kind != SYMBOL_ARRAY)
		{
			fprintf(stderr, "[verify error] expected array @ %d\n", var->lineno);
			exit(1);
		}

		/*
		TODO: Compare array base types
		*/

		var->symbol_value = var->val.var_array.var->symbol_value;
		break;
	case VAR_RECORD:
		//fprintf(stderr, "verify_var_record\n");
		verify_var(var->val.var_record.var);

		if (var->val.var_record.var->symbol_value->kind == SYMBOL_RECORD)
		{
			inner_scope = var->val.var_record.var->symbol_value->child_scope;
			symbol = getSymbol(inner_scope, var->val.var_record.id);
			if (symbol)
				var->symbol_value = symbol->symbol_value;
			else
			{
				fprintf(stderr, "[verify error] symbol not found @ %d\n", var->lineno);
				exit(1);
			}
		}
		else
		{
			fprintf(stderr, "[verify error] expected record @ %d\n", var->lineno);
			exit(1);
		}
		break;
	}
	return depth;
}

int verify_act_list(ACT_LIST* act_list)
{
	int param_count = 0;
	switch (act_list->kind)
	{
	case ACT_LIST_EMPTY:
		return 0;
		break;
	case ACT_LIST_POPULATED:
		return verify_exp_list(act_list->exp_list);
		break;
	}
	return param_count;
}

int verify_exp_list(EXP_LIST* exp_list)
{
	int param_count = 1;
	switch (exp_list->kind)
	{
	case EXPRESSION_LIST:
		param_count += verify_exp_list(exp_list->exp_list);
		verify_exp(exp_list->exp);
		break;
	case EXPRESSION:
		verify_exp(exp_list->exp);
		break;
	}
	return param_count;
}

int get_array_length(SYMBOL_VALUE* symbol_value)
{
	int length = 1;
	SYMBOL_VALUE* copy = symbol_value;
	while (copy->array_next_value)
	{
		length++;
		copy = copy->array_next_value;
	}

	return length;
}