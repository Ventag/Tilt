#include <stdio.h>
#include "pretty.h"

void print_begin(BODY* body)
{
	fprintf(stderr, "\n[tilt pretty print]\n");

	print_body(body);
}

void print_body(BODY* body)
{
	print_decl_list(body->decl_list);
	print_statement_list(body->statement_list);
}

void print_head(HEAD* head)
{
	fprintf(stderr, "%s(", head->id);
	print_par_decl_list(head->par_decl_list);
	fprintf(stderr, ") :");
	print_type(head->type);
}

void print_tail(TAIL* tail)
{
	fprintf(stderr, "end %s", tail->id);
}

void print_function(FUNCTION* function)
{
	fprintf(stderr, "func ");
	print_head(function->head);
	fprintf(stderr, "\n");
	print_body(function->body);
	fprintf(stderr, "\n");
	print_tail(function->tail);
	fprintf(stderr, "\n");
}

void print_par_decl_list(PAR_DECL_LIST* par_decl_list)
{
	switch (par_decl_list->kind)
	{
	case PAR_DECL_LIST_EMPTY:
		break;
	case PAR_DECL_LIST_POPLUATED:
		print_var_decl_list(par_decl_list->var_decl_list);
	}
}

void print_decl_list(DECL_LIST* decl_list)
{
	switch (decl_list->kind)
	{
		case DECL_LIST_EMPTY:
			break;
		case DECL_LIST_POPULATED:
			print_decl(decl_list->declaration);
			print_decl_list(decl_list->decl_list);
			printf("\n");
			break;
	}
}

void print_decl(DECLARATION* decl)
{
	if(decl == NULL)
		fprintf(stderr, "houston we have a problem\n");

	fprintf(stderr, "decl kind: %i\n", decl->kind);
	switch (decl->kind)
	{
		case DECLARATION_ID:
			fprintf(stderr, "type %s = ", decl->val.identifier.id);
			print_type(decl->val.identifier.type);
			break;
		case DECLARATION_FUNC:
			print_function(decl->val.function);
			break;
		case DECLARATION_VAR:
			fprintf(stderr, "var ");
			print_var_decl_list(decl->val.var_decl_list);
			break;
		default:
			fprintf(stderr, "this should never hit\n");
			break;
	}
}

void print_type(TYPE* type)
{
	switch (type->kind)
	{
		case ID_T:
			fprintf(stderr, " %s ", type->val.id);
			break;
		case INT_T:
			fprintf(stderr, " int ");
			break;
		case BOOL_T:
			fprintf(stderr, " bool ");
			break;
		case ARRAY_T:
			print_type(type->val.type);
			fprintf(stderr, " array ");
			break;
		case RECORD_T:
			fprintf(stderr, " record ");
			break;
	}
}

void print_var_decl_list(VAR_DECL_LIST* var_decl_list)
{
	//printf("print_var_decl_list\n");
	switch (var_decl_list->kind)
	{
		case VDECL_LIST:
			print_var_decl_list(var_decl_list->var_decl_list);
			fprintf(stderr, ", ");
			print_var_type(var_decl_list->var_type);
			break;
		case VDECL_TYPE:
			print_var_type(var_decl_list->var_type);
			break;
	}
}

void print_var_type(VAR_TYPE* var_type)
{
	fprintf(stderr, "%s :", var_type->id);
	print_type(var_type->type);
}

void print_var(VAR* var)
{
	//printf("print_var\n");
	switch (var->kind)
	{
	case VAR_ID:
		fprintf(stderr, "%s", var->id);
		break;
	case VAR_ARRAY:
		print_var(var->val.var_array.var);
		fprintf(stderr, "[");
		print_exp(var->val.var_array.exp);
		fprintf(stderr, "]");
		break;
	case VAR_RECORD:
		print_var(var->val.var_record.var);
		fprintf(stderr, ".%s", var->val.var_record.id);
		break;
	}
}

void print_statement_list(STATEMENT_LIST* statement_list)
{
	switch (statement_list->kind)
	{
	case STATEMENT_LIST_LIST:
		print_statement_list(statement_list->statement_list);
		print_statement_element(statement_list->statement);
		break;
	case STATEMENT_LIST_ELEMENT:
		print_statement_element(statement_list->statement);
		break;
	}
}

void print_statement_element(STATEMENT* statement)
{
	switch (statement->kind)
	{
	case RETURN:
		fprintf(stderr, "return ");
		print_exp(statement->val.exp);
		fprintf(stderr, ";");
		break;
	case WRITE:
		fprintf(stderr, "write ");
		print_exp(statement->val.exp);
		fprintf(stderr, ";\n");
		break;
	case ALLOCATE:
		fprintf(stderr, "allocate ");
		print_var(statement->val.stat_allocate.var);
		print_exp(statement->val.stat_allocate.length);
		fprintf(stderr, ";\n");
		break;
	case ASSIGN:
		print_var(statement->val.stat_assign.var);
		fprintf(stderr, " = ");
		print_exp(statement->val.stat_assign.exp);
		fprintf(stderr, ";\n");
		break;
	case IF:
		fprintf(stderr, "if ");
		print_exp(statement->val.stat_if.condition);
		fprintf(stderr, " then ");
		print_statement_element(statement->val.stat_if.stat);
		if (statement->val.stat_if.optional_else->kind == ELSE_ACTIVE)
		{
			fprintf(stderr, " else ");
			print_statement_element(statement->val.stat_if.optional_else->statement);
		}
		break;
	case WHILE:
		fprintf(stderr, "while ");
		print_exp(statement->val.stat_while.condition);
		fprintf(stderr, " ");
		print_statement_element(statement->val.stat_while.stat);
		break;
	case WHILE_LIST:
		fprintf(stderr, "\n{\n");
		print_statement_list(statement->val.statement_list);
		fprintf(stderr, "\n}\n");
		break;
	}
}

void print_exp(EXP *e)
{ 
	switch (e->kind) 
	{
    case EXP_ID:
		 fprintf(stderr, "%s",e->val.id);
         break;
    case EXP_INT:
		 fprintf(stderr, "%i",e->val.int_const);
         break;
    case EXP_TIMES:
		 fprintf(stderr, "(");
		 print_exp(e->val.branches.left);
		 fprintf(stderr, "*");
		 print_exp(e->val.branches.right);
		 fprintf(stderr, ")");
         break;
    case EXP_DIV:
         fprintf(stderr,"(");
		 print_exp(e->val.branches.left);
		 fprintf(stderr, "/");
		 print_exp(e->val.branches.right);
		 fprintf(stderr, ")");
         break;
    case EXP_PLUS:
         fprintf(stderr,"(");
		 print_exp(e->val.branches.left);
		 fprintf(stderr, "+");
		 print_exp(e->val.branches.right);
		 fprintf(stderr, ")");
         break;
    case EXP_MINUS:
		 fprintf(stderr, "(");
		 print_exp(e->val.branches.left);
		 fprintf(stderr, "-");
		 print_exp(e->val.branches.right);
		 fprintf(stderr, ")");
         break;
   case EXP_LESS:
         fprintf(stderr,"(");
		 print_exp(e->val.branches.left);
		 fprintf(stderr, "<");
		 print_exp(e->val.branches.right);
		 fprintf(stderr, ")");
         break;
   case EXP_LESS_EQUALS:
	     fprintf(stderr, "(");
		 print_exp(e->val.branches.left);
		 fprintf(stderr, "<=");
		 print_exp(e->val.branches.right);
		 fprintf(stderr, ")");
         break;
   case EXP_GREATER:
         fprintf(stderr,"(");
		 print_exp(e->val.branches.left);
		 fprintf(stderr, ">");
		 print_exp(e->val.branches.right);
		 fprintf(stderr, ")");
         break;
   case EXP_GREATER_EQUALS:
         fprintf(stderr,"(");
		 print_exp(e->val.branches.left);
		 fprintf(stderr, ">=");
		 print_exp(e->val.branches.right);
		 fprintf(stderr, ")");
         break;
   case EXP_EQUALS:
         fprintf(stderr,"(");
		 print_exp(e->val.branches.left);
		 fprintf(stderr, "==");
		 print_exp(e->val.branches.right);
		 fprintf(stderr, ")");
         break;
   case EXP_AND:
         fprintf(stderr,"(");
		 print_exp(e->val.branches.left);
		 fprintf(stderr, "&&");
		 print_exp(e->val.branches.right);
		 fprintf(stderr, ")");
         break;
   case EXP_OR:
         fprintf(stderr,"(");
		 print_exp(e->val.branches.left);
		 fprintf(stderr, "||");
		 print_exp(e->val.branches.right);
		 fprintf(stderr, ")");
         break;
   case EXP_NOT_EQUALS:
         fprintf(stderr,"(");
         print_exp(e->val.branches.left);
		 fprintf(stderr, "!=");
         print_exp(e->val.branches.right);
		 fprintf(stderr, ")");
         break;
   case EXP_TERM:
	     fprintf(stderr, "(");
	     print_term(e->val.term);
	     fprintf(stderr, ")");
  }
}

void print_term(TERM* term)
{
	switch (term->kind)
	{
	case TERM_TRUE:
		fprintf(stderr, "true");
		break;
	case TERM_FALSE:
		fprintf(stderr, "false");
		break;
	case TERM_VAR:
		print_var(term->val.var);
		break;
	case TERM_NUM:
		fprintf(stderr, "%i", term->val.num);
		break;
	case TERM_NULL:
		fprintf(stderr, "NULL");
		break;
	case TERM_NOT:
		fprintf(stderr, "!");
		print_term(term->val.term);
		break;
	case TERM_PARENTHESES:
		fprintf(stderr, "(");
		print_exp(term->val.exp);
		fprintf(stderr, ")");
		break;
	case TERM_ACT_LIST:
		print_act_list(term->val.term_act_list.act_list);
		break;
	case TERM_ABSOLUTE:
		fprintf(stderr, "|");
		print_exp(term->val.exp);
		fprintf(stderr, "|");
		break;
	}
}

void print_act_list(ACT_LIST* act_list)
{
	switch (act_list->kind)
	{
	case ACT_LIST_EMPTY:
		break;
	case ACT_LIST_POPULATED:
		print_exp_list(act_list->exp_list);
		break;
	}
}

void print_exp_list(EXP_LIST* exp_list)
{
	switch (exp_list->kind)
	{
	case EXPRESSION:
		print_exp(exp_list->exp);
		break;
	case EXPRESSION_LIST:
		print_exp_list(exp_list->exp_list);
		print_exp(exp_list->exp);
		break;
	}
}