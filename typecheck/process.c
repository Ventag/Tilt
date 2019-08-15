#include "process.h"

void process(BODY* body)
{
	if (unknown_user_types > 0) // do we have any unknown user types?
	{
		fprintf(stderr, "[process] processing user defined types\n");
		for(int i = 0; i < 2; i++)
			process_body(body);
	}
}

void process_body(BODY* body)
{
	process_decl_list(body->decl_list);
}

void process_head(HEAD* head)
{
	process_type(head->type);
	process_par_decl_list(head->par_decl_list);
}

void process_function(FUNCTION* function)
{
	process_head(function->head);
	process_body(function->body);
}

void process_type(TYPE* type)
{
	SYMBOL* symbol = NULL;
	switch (type->kind)
	{
	case ID_T:
		if (type->table->parent) // is this in a record?
			symbol = getSymbol(type->table->parent, type->val.id);
		else
			symbol = getSymbol(type->table, type->val.id);

		if (symbol && symbol->symbol_value->kind != SYMBOL_UNKNOWN && type->symbol_value->kind == SYMBOL_UNKNOWN)
		{
			type->symbol_value = symbol->symbol_value;
			fprintf(stderr, "[typechecker] identified unknown user type\n");
		}

		break;
	case ARRAY_T:
		process_type(type->val.type);
		break;
	case RECORD_T:
		process_var_decl_list(type->val.var_decl_list);
		break;
	}
}

void process_par_decl_list(PAR_DECL_LIST* pdcl_list)
{
	switch (pdcl_list->kind)
	{
	case PAR_DECL_LIST_EMPTY:
		break;
	case PAR_DECL_LIST_POPLUATED:
		process_var_decl_list(pdcl_list->var_decl_list);
		break;
	}
}

void process_var_decl_list(VAR_DECL_LIST* vdcl_list)
{
	switch (vdcl_list->kind)
	{
	case VDECL_LIST:
		process_var_decl_list(vdcl_list->var_decl_list);
		process_var_type(vdcl_list->var_type);
		break;
	case VDECL_TYPE:
		process_var_type(vdcl_list->var_type);
		break;
	}
}

void process_var_type(VAR_TYPE* var_type)
{
	SYMBOL_VALUE* symbol_val = var_type->type->symbol_value;
	SYMBOL* symbol = getSymbol(var_type->table, var_type->id);
	if (symbol && symbol->symbol_type == SYMBOL_UNKNOWN && symbol_val->kind != SYMBOL_UNKNOWN)
	{
		unknown_user_types -= 1;
		symbol->symbol_type = symbol_val->kind;
		fprintf(stderr, "[typechecker] identified unknown user type\n");
	}
}

void process_decl_list(DECL_LIST* decl_list)
{
	switch (decl_list->kind)
	{
	case DECL_LIST_EMPTY:
		break;
	case DECL_LIST_POPULATED:
		process_decl_list(decl_list->decl_list);
		process_declaration(decl_list->declaration);
		break;
	}
}

void process_declaration(DECLARATION* declaration)
{
	switch (declaration->kind)
	{
	case DECLARATION_ID:
		process_type(declaration->val.identifier.type);
		SYMBOL_VALUE* symbol_val = declaration->val.identifier.type->symbol_value;
		SYMBOL* symbol = getSymbol(declaration->table, declaration->val.identifier.id);
		if ( symbol && symbol->symbol_type == SYMBOL_UNKNOWN && symbol_val->kind == SYMBOL_UNKNOWN )
		{
			unknown_user_types -= 1;
			symbol->symbol_type = symbol_val->kind;
			fprintf(stderr, "[typechecker] identified unknown user type\n");
		}
		break;
	case DECLARATION_FUNC:
		process_function(declaration->val.function);
		break;
	case DECLARATION_VAR:
		process_var_decl_list(declaration->val.var_decl_list);
		break;
	}
}