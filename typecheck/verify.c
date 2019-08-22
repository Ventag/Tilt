#include "process.h"
#include "collect.h"

TYPEINFO* return_type;

int depth_count = 0;

void increment_depth_count()
{
	depth_count++;
}

void reset_depth_count()
{
	depth_count = 0;
}

void verify(BODY* body)
{
	fprintf(stderr, "[verify] type verification started\n");
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
	TYPEINFO* old = return_type;
	verify_head(func->head);
	return_type = func->head->typeinfo->return_type;
	verify_body(func->body);
	return_type = old;
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
	if (vtype->symbol->typeinfo->type == TYPE_UNKNOWN)
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
	TYPEINFO *left, *right = NULL;
	FUNCTION* func = NULL;
	switch (statement->kind)
	{
	case RETURN:
		verify_exp(statement->val.stat_return.exp);
		left = statement->val.stat_return.exp->typeinfo;
		if (return_type == NULL || left->type != return_type->type)
		{
			if(return_type == NULL)
				fprintf(stderr, "[verify error] couldn't return, are you trying to return outside a function? @ %d\n", statement->lineno);
			else
				fprintf(stderr, "[verify error] function return type mistmatch @ %d\nleft: %d\nright: %d\n", statement->lineno, left->type, return_type->type);
			exit(1);
		}
		break;
	case WRITE:
		verify_exp(statement->val.exp);
		if ((statement->val.exp->typeinfo->type == TYPE_ARRAY && statement->val.exp->val.term->kind != TERM_ABSOLUTE)
			|| statement->val.exp->typeinfo->type == TYPE_RECORD)
		{
			fprintf(stderr, "[typechecking error] writing type, did you try to write an array or record? @ %d\n", statement->lineno);
			exit(1);
		}
		break;
	case ALLOCATE:
		verify_var(statement->val.stat_allocate.var);
		verify_exp(statement->val.stat_allocate.length);

		left = statement->val.stat_allocate.var->typeinfo;
		if (left->type != TYPE_RECORD && left->type != TYPE_ARRAY)
		{
			fprintf(stderr, "[typechecking error] cannot allocate specific var type @ %d type is %d\n", statement->lineno, left->type);
			exit(1);
		}

		right = statement->val.stat_allocate.length->typeinfo;
		if(right->type != TYPE_INT)
		{
			fprintf(stderr, "[typechecking error] allocate type differs from INT @ %d type is %d\n", statement->lineno, statement->val.stat_allocate.length->typeinfo->type);
			exit(1);
		}
		break;
	case ASSIGN:
		verify_var(statement->val.stat_assign.var);
		verify_exp(statement->val.stat_assign.exp);

		left = statement->val.stat_assign.var->typeinfo;
		right = statement->val.stat_assign.exp->typeinfo;

		SYMBOL* symbol = getSymbol(statement->val.stat_assign.var->table, statement->val.stat_assign.var->id);
		if (symbol)
		{
			if (symbol->kind == TYPEDEF)
			{
				fprintf(stderr, "tried assigning a typedef directly\n");
				printf("error\n");
				exit(1);
			}
		}

		/*
		TODO: Handle record & array assignments here
		*/

		if (left->type == TYPE_ARRAY)
		{
			left = left->array_next_value;

			if (left->type != right->type && right->type != TYPE_NULL)
			{
				fprintf(stderr, "[typechecking error] array type mismatch @ %d\n", statement->lineno);
				exit(1);
			}
		}
		else if (left->type != right->type)
		{
			fprintf(stderr, "[typechecking error] this needs rework @ %d\n", statement->lineno);
			fprintf(stderr, "left: %d right %d\n", left->type, right->type);
			exit(1);
		}

		break;
	case IF:
		verify_exp(statement->val.stat_if.condition);
		verify_statement(statement->val.stat_if.stat);
		verify_else(statement->val.stat_if.optional_else);

		if (statement->val.stat_if.condition->typeinfo->type != TYPE_BOOL)
		{
			fprintf(stderr, "[type verification error] conditionals can only be boolean @ %d\n", statement->lineno);
			exit(1);
		}
		break;
	case WHILE:
		verify_exp(statement->val.stat_while.condition);
		verify_statement(statement->val.stat_while.stat);

		if (statement->val.stat_while.condition->typeinfo->type != TYPE_BOOL)
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
	TYPEINFO *left, *right = NULL;

	switch (exp->kind)
	{
	case EXP_TIMES:
	case EXP_DIV:
	case EXP_PLUS:
	case EXP_MINUS:
		verify_exp(exp->val.branches.left);
		verify_exp(exp->val.branches.right);

		left = exp->val.branches.left->typeinfo;
		right = exp->val.branches.right->typeinfo;

		if (left->type != TYPE_INT || right->type != TYPE_INT)
		{
			fprintf(stderr, "[type verification error] wrong type received, expected int @ %d\n", exp->lineno);
			exit(1);
		}
		else
			exp->typeinfo = create_type(TYPE_INT);
		break;
	case EXP_AND:
	case EXP_OR:
		verify_exp(exp->val.branches.left);
		verify_exp(exp->val.branches.right);

		left = exp->val.branches.left->typeinfo;
		right = exp->val.branches.right->typeinfo;

		if (left->type != TYPE_BOOL || right->type != TYPE_BOOL)
		{
			fprintf(stderr, "[verify] type mismatch, expected boolean expression @ %d\n", exp->lineno);
			exit(1);
		}
		else
		{
			exp->typeinfo = create_type(TYPE_BOOL);
		}
		break;
	case EXP_EQUALS:
	case EXP_NOT_EQUALS:
		verify_exp(exp->val.branches.left);
		verify_exp(exp->val.branches.right);
		left = exp->val.branches.left->typeinfo;
		right = exp->val.branches.right->typeinfo;
		if (left->type == right->type)
			exp->typeinfo = create_type(TYPE_BOOL);
		else if (left->type == TYPE_ARRAY && right->type == TYPE_NULL)
			exp->typeinfo = create_type(TYPE_BOOL);
		else if (left->type == TYPE_NULL && right->type == TYPE_ARRAY)
			exp->typeinfo = create_type(TYPE_BOOL);
		else if (left->type == TYPE_RECORD && right->type == TYPE_NULL)
			exp->typeinfo = create_type(TYPE_BOOL);
		else if (left->type == TYPE_NULL && right->type == TYPE_RECORD)
			exp->typeinfo = create_type(TYPE_BOOL);
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

		left = exp->val.branches.left->typeinfo;
		right = exp->val.branches.right->typeinfo;

		if (left->type != TYPE_INT || right->type != TYPE_INT)
		{
			fprintf(stderr, "[verify error] wrong type received, expected int @ %d\n", exp->lineno);
			exit(1);
		}
		else
			exp->typeinfo = create_type(TYPE_BOOL);
		break;
	case EXP_TERM:
		verify_term(exp->val.term);
		exp->typeinfo = exp->val.term->typeinfo;
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
		term->typeinfo = term->val.var->typeinfo;
		break;
	case TERM_ACT_LIST:
		verify_act_list(term->val.term_act_list.act_list);
		int param_count = depth_count;
		reset_depth_count();
		SYMBOL* symbol = getSymbol(term->table, term->val.term_act_list.id);
		if (!symbol || symbol->typeinfo->type != TYPE_FUNC)
		{
			fprintf(stderr, "[verify error] undefined function %d @ %d\n", symbol->typeinfo->type, term->lineno);
			exit(1);
		}

		if (param_count < symbol->param_count || param_count > symbol->param_count)
		{
			fprintf(stderr, "[verify error] arguments count mismatch for function %d vs %d @ %d\n", param_count, symbol->param_count, term->lineno);
			exit(1);
		}

		/*
		TODO: Compare call parameters & function parameters
		*/

		term->typeinfo = symbol->typeinfo->return_type;
		break;
	case TERM_PARENTHESES:
		verify_exp(term->val.exp);
		term->typeinfo = term->val.exp->typeinfo;
		break;
	case TERM_NOT:
		if (term->val.term->typeinfo->type != TYPE_BOOL)
		{
			fprintf(stderr, "[verify error] expected boolean @ %d\n", term->lineno);
			exit(1);
		}
		term->typeinfo = term->val.term->typeinfo;
		break;
	case TERM_ABSOLUTE:
		verify_exp(term->val.exp);
		TYPES kind = term->val.exp->typeinfo->type;
		if(kind != TYPE_INT && kind != TYPE_ARRAY)
		{
			fprintf(stderr, "[verify error] expected int or array @ %d\n", term->lineno);
			fprintf(stderr, "type is %d\n", kind);
			exit(1);
		}

		if (kind == TYPE_ARRAY)
			term->typeinfo = create_type(TYPE_INT);
		else
			term->typeinfo = term->val.exp->typeinfo;

		break;
	case TERM_NUM:
		term->typeinfo = create_type(TYPE_INT);
		break;
	case TERM_TRUE:
		term->typeinfo = create_type(TYPE_BOOL);
		break;
	case TERM_FALSE:
		term->typeinfo = create_type(TYPE_BOOL);
		break;
	case TERM_NULL:
		term->typeinfo = create_type(TYPE_NULL);
		break;
	case TERM_UMINUS:
		verify_term(term->val.term);
		if (term->val.term->typeinfo->type != TYPE_INT)
		{
			fprintf(stderr, "[verify error] expected int @ %d\n", term->lineno);
			exit(1);
		}
		term->typeinfo = term->val.term->typeinfo;
		break;
	default:
		break;
	}
}

void verify_var(VAR* var)
{
	SYMBOL* symbol = NULL;
	SYMBOL_TABLE* inner_scope;
	switch (var->kind)
	{
	case VAR_ID:
		symbol = getSymbol(var->table, var->id);

		if (symbol == NULL || symbol->typeinfo == NULL)
		{
			fprintf(stderr, "[type verification error]\n");
			exit(1);
		}

		var->typeinfo = symbol->typeinfo;
		if (var->typeinfo == TYPE_UNKNOWN)
		{
			fprintf(stderr, "[type verification error] symbol is a typedef @ %d\n", var->lineno);
			exit(1);
		}

		break;
	case VAR_ARRAY:
		verify_var(var->val.var_array.var);
		verify_exp(var->val.var_array.exp);

		if (var->val.var_array.exp->typeinfo->type != TYPE_INT)
		{
			fprintf(stderr, "[verify error] expected integer @ %d\n", var->lineno);
			exit(1);
		}

		if (var->val.var_array.var->typeinfo->type != TYPE_ARRAY)
		{
			fprintf(stderr, "[verify error] expected array @ %d\n", var->lineno);
			exit(1);
		}

		TYPEINFO* type = var->val.var_array.var->typeinfo;
		type = type->array_next_value;

		var->typeinfo = type;
		break;
	case VAR_RECORD:
		verify_var(var->val.var_record.var);

		if (var->val.var_record.var->typeinfo->type == TYPE_RECORD)
		{
			inner_scope = var->val.var_record.var->typeinfo->child_scope;
			symbol = getSymbol(inner_scope, var->val.var_record.id);
			if (symbol)
				var->typeinfo = symbol->typeinfo;
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
}

void verify_act_list(ACT_LIST* act_list)
{
	switch (act_list->kind)
	{
	case ACT_LIST_EMPTY:
		break;
	case ACT_LIST_POPULATED:
		verify_exp_list(act_list->exp_list);
		break;
	}
	//increment_depth_count();
}

void verify_exp_list(EXP_LIST* exp_list)
{
	switch (exp_list->kind)
	{
	case EXPRESSION_LIST:
		verify_exp_list(exp_list->exp_list);
		verify_exp(exp_list->exp);
		break;
	case EXPRESSION:
		verify_exp(exp_list->exp);
		break;
	}
	increment_depth_count();
}