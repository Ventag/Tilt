#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../symbols/memory.h"
#include "tree.h"

extern int lineno;

EXP *make_exp_id(char *id)
{
	EXP *e;
	e = NEW(EXP);
	e->lineno = lineno;
	e->kind = EXP_ID;
	e->val.id = id;
	return e;
}

EXP *make_exp_int_const(int intconst)
{
	EXP *e;
	e = NEW(EXP);
	e->lineno = lineno;
	e->kind = EXP_INT;
	e->val.int_const = intconst;
	return e;
}

EXP *make_exp_times(EXP *left, EXP *right)
{
	EXP *e;
	e = NEW(EXP);
	e->lineno = lineno;
	e->kind = EXP_TIMES;
	e->val.branches.left = left;
	e->val.branches.right = right;
	return e;
}

EXP *make_exp_div(EXP *left, EXP *right)
{
	EXP *e;
	e = NEW(EXP);
	e->lineno = lineno;
	e->kind = EXP_DIV;
	e->val.branches.left = left;
	e->val.branches.right = right;
	return e;
}

EXP *make_exp_plus(EXP *left, EXP *right)
{
	EXP *e;
	e = NEW(EXP);
	e->lineno = lineno;
	e->kind = EXP_PLUS;
	e->val.branches.left = left;
	e->val.branches.right = right;
	return e;
}

EXP *make_exp_minus(EXP *left, EXP *right)
{
	EXP *e;
	e = NEW(EXP);
	e->lineno = lineno;
	e->kind = EXP_MINUS;
	e->val.branches.left = left;
	e->val.branches.right = right;
	return e;
}

EXP *make_exp_less(EXP *left, EXP *right)
{
	EXP *e;
	e = NEW(EXP);
	e->lineno = lineno;
	e->kind = EXP_LESS;
	e->val.branches.left = left;
	e->val.branches.right = right;
	return e;
}

EXP *make_exp_less_equals(EXP *left, EXP *right)
{
	EXP *e;
	e = NEW(EXP);
	e->lineno = lineno;
	e->kind = EXP_LESS_EQUALS;
	e->val.branches.left = left;
	e->val.branches.right = right;
	return e;
}

EXP *make_exp_greater(EXP* left, EXP* right)
{
	EXP *e;
	e = NEW(EXP);
	e->lineno = lineno;
	e->kind = EXP_GREATER;
	e->val.branches.left = left;
	e->val.branches.right = right;
	return e;
}

EXP *make_exp_greater_equals(EXP *left, EXP *right)
{
	EXP *e;
	e = NEW(EXP);
	e->lineno = lineno;
	e->kind = EXP_GREATER_EQUALS;
	e->val.branches.left = left;
	e->val.branches.right = right;
	return e;
}

EXP *make_exp_equals(EXP *left, EXP *right)
{
	EXP *e;
	e = NEW(EXP);
	e->lineno = lineno;
	e->kind = EXP_EQUALS;
	e->val.branches.left = left;
	e->val.branches.right = right;
	return e;
}

EXP *make_exp_not_equals(EXP *left, EXP *right)
{
	EXP *e;
	e = NEW(EXP);
	e->lineno = lineno;
	e->kind = EXP_NOT_EQUALS;
	e->val.branches.left = left;
	e->val.branches.right = right;
	return e;
}

EXP *make_exp_and(EXP *left, EXP *right)
{
	EXP *e;
	e = NEW(EXP);
	e->lineno = lineno;
	e->kind = EXP_AND;
	e->val.branches.left = left;
	e->val.branches.right = right;
	return e;
}

EXP *make_exp_or(EXP *left, EXP *right)
{
	EXP *e;
	e = NEW(EXP);
	e->lineno = lineno;
	e->kind = EXP_OR;
	e->val.branches.left = left;
	e->val.branches.right = right;
	return e;
}

EXP* make_exp_term(TERM* term)
{
	EXP* e = NEW(EXP);
	e->lineno = lineno;
	e->kind = EXP_TERM;
	e->val.term = term;

	return e;
}

TYPE* make_id_type(char* id)
{
	TYPE* t = NEW(TYPE);
	t->lineno = lineno;
	t->kind = ID_T;
	t->val.id = id;

	return t;
}

TYPE* make_int_type()
{
	TYPE* t = NEW(TYPE);
	t->lineno = lineno;
	t->kind = INT_T;

	return t;
}

TYPE* make_bool_type()
{
	TYPE* t = NEW(TYPE);
	t->lineno = lineno;
	t->kind = BOOL_T;

	return t;
}

TYPE* make_array_of_type(TYPE* type)
{
	TYPE* t = NEW(TYPE);
	t->lineno = lineno;
	t->kind = ARRAY_T;
	t->val.type = type;

	return t;
}

TYPE* make_record_of_type(VAR_DECL_LIST* lst)
{
	TYPE* t = NEW(TYPE);
	t->lineno = lineno;
	t->kind = RECORD_T;
	t->val.var_decl_list = lst;
	return t;
}

FUNCTION* make_function(HEAD* head, BODY* body, TAIL* tail)
{
	FUNCTION* function = NEW(FUNCTION);
	function->lineno = lineno;
	function->head = head;
	function->body = body;
	function->tail = tail;

	return function;
}

HEAD* make_head(char* id, PAR_DECL_LIST* par_decl_list, TYPE* type)
{
	HEAD* head = NEW(HEAD);
	head->id = id;
	head->par_decl_list = par_decl_list;
	head->type = type;

	return head;
}

BODY* make_body(DECL_LIST* decl_list, STATEMENT_LIST* stm_list)
{
	BODY* body = NEW(BODY);
	body->lineno = lineno;
	body->decl_list = decl_list;
	body->statement_list = stm_list;

	return body;
}

TAIL* make_tail(char* id)
{
	TAIL* tail = NEW(TAIL);
	tail->lineno = lineno;
	tail->id = id;

	return tail;
}

DECLARATION* make_declaration_id(char* name, TYPE* type)
{
	DECLARATION* decl = NEW(DECLARATION);
	decl->lineno = lineno;
	//decl->val.id = calloc(strlen(name) + 1, sizeof(char));
	//decl->val.type = type;
	decl->val.identifier.type = type;
	decl->val.identifier.id = name;
	decl->kind = DECLARATION_ID;

	fprintf(stderr, "%s / %s [] %s\n", decl->val.identifier.id, decl->name, name);
	return decl;
}

DECLARATION* make_declaration_function(FUNCTION* func)
{
	DECLARATION* decl = NEW(DECLARATION);
	decl->lineno = lineno;
	decl->val.function = func;
	decl->kind = DECLARATION_FUNC;

	return decl;
}

DECLARATION* make_declaration_var(VAR_DECL_LIST* var_decl_list)
{
	DECLARATION* decl = NEW(DECLARATION);
	decl->lineno = lineno;
	decl->val.var_decl_list = var_decl_list;
	decl->kind = DECLARATION_VAR;

	return decl;
}

DECL_LIST* make_decl_list(DECLARATION* decl, DECL_LIST* decl_list)
{
	DECL_LIST* list = NEW(DECL_LIST);
	list->lineno = lineno;
	list->declaration = decl;
	list->decl_list = decl_list;
	list->kind = DECL_LIST_POPULATED;

	return list;
}

DECL_LIST* make_decl_list_empty()
{
	DECL_LIST* list = NEW(DECL_LIST);
	list->lineno = lineno;
	list->declaration = NULL;
	list->decl_list = NULL;
	list->kind = DECL_LIST_EMPTY;

	return list;
}

PAR_DECL_LIST* make_par_decl_list(VAR_DECL_LIST* var_decl_list)
{
	PAR_DECL_LIST* list = NEW(PAR_DECL_LIST);
	list->lineno = lineno;
	list->var_decl_list = var_decl_list;
	list->kind = PAR_DECL_LIST_POPLUATED;

	return list;
}

PAR_DECL_LIST* make_par_decl_list_empty()
{
	PAR_DECL_LIST* list = NEW(PAR_DECL_LIST);
	list->lineno = lineno;
	list->kind = PAR_DECL_LIST_EMPTY;

	return list;
}

STATEMENT_LIST* make_statement_empty_list(STATEMENT* statement)
{
	STATEMENT_LIST* stat_list = NEW(STATEMENT_LIST);
	stat_list->lineno = lineno;
	stat_list->statement = statement;
	stat_list->statement_list = NULL;
	stat_list->kind = STATEMENT_LIST_ELEMENT;

	return stat_list;
}

STATEMENT_LIST* make_statement_list(STATEMENT* statement, STATEMENT_LIST* list)
{
	STATEMENT_LIST* stat_list = NEW(STATEMENT_LIST);
	stat_list->lineno = lineno;
	stat_list->statement = statement;
	stat_list->statement_list = list;
	stat_list->kind = STATEMENT_LIST_LIST;

	return stat_list;
}

STATEMENT* make_statement_return(EXP* exp)
{
	STATEMENT* ret = NEW(STATEMENT);
	ret->lineno = lineno;
	ret->val.stat_return.exp = exp;
	ret->kind = RETURN;

	return ret;
}

STATEMENT* make_statement_write(EXP* exp)
{
	STATEMENT* ret = NEW(STATEMENT);
	ret->lineno = lineno;
	ret->val.exp = exp;
	ret->kind = WRITE;

	return ret;
}

STATEMENT* make_statement_allocate(VAR* variable, EXP* length)
{
	STATEMENT* ret = NEW(STATEMENT);
	ret->lineno = lineno;
	ret->val.stat_allocate.length = length;
	ret->val.stat_allocate.var = variable;
	ret->kind = ALLOCATE;

	return ret;
}

STATEMENT* make_statement_assign(VAR* variable, EXP* expression)
{
	STATEMENT* ret = NEW(STATEMENT);
	ret->lineno = lineno;
	ret->val.stat_assign.exp = expression;
	ret->val.stat_assign.var = variable;
	ret->kind = ASSIGN;

	return ret;
}

STATEMENT* make_statement_if(EXP* expression, STATEMENT* stat, STATEMENT_ELSE* stat_else)
{
	STATEMENT* ret = NEW(STATEMENT);
	ret->lineno = lineno;
	ret->val.stat_if.condition = expression;
	ret->val.stat_if.stat = stat;
	ret->val.stat_if.optional_else = stat_else;
	ret->kind = IF;

	return ret;
}

STATEMENT* make_statement_while(EXP* expression, STATEMENT* stat)
{
	STATEMENT* ret = NEW(STATEMENT);
	ret->lineno = lineno;
	ret->val.stat_while.condition = expression;
	ret->val.stat_while.stat = stat;
	ret->kind = WHILE;

	return ret;
}

STATEMENT* make_statement_while_list(STATEMENT_LIST* statement_list)
{
	STATEMENT* ret = NEW(STATEMENT);
	ret->lineno = lineno;
	ret->kind = WHILE_LIST;
	ret->val.statement_list = statement_list;

	return ret;
}

STATEMENT* make_statement_for(STATEMENT* assign, EXP* condition, STATEMENT* update, STATEMENT* stat)
{
	STATEMENT* new_stat_for = NEW(STATEMENT);
	new_stat_for->lineno = lineno;
	new_stat_for->kind = FOR;
	new_stat_for->val.stat_for.assign = assign;
	new_stat_for->val.stat_for.condition = condition;
	new_stat_for->val.stat_for.update = update;
	new_stat_for->val.stat_for.stat = stat;

	return new_stat_for;
}

STATEMENT_ELSE* make_statement_else(STATEMENT* stat)
{
	STATEMENT_ELSE* e = NEW(STATEMENT_ELSE);
	e->lineno = lineno;
	e->kind = ELSE_ACTIVE;
	e->statement = stat;

	return e;
}

STATEMENT_ELSE* make_statement_else_empty()
{
	STATEMENT_ELSE* e = NEW(STATEMENT_ELSE);
	e->lineno = lineno;
	e->kind = ELSE_INACTIVE;
	e->statement = NULL;

	return e;
}

VAR_DECL_LIST* make_var_decl_list(VAR_TYPE* vt, VAR_DECL_LIST* vdl)
{
	VAR_DECL_LIST* var_decl_list = NEW(VAR_DECL_LIST);
	var_decl_list->lineno = lineno;
	var_decl_list->var_decl_list = vdl;
	var_decl_list->var_type = vt;
	var_decl_list->kind = VDECL_LIST;

	return var_decl_list;
}

VAR_DECL_LIST* make_var_decl_list_empty(VAR_TYPE* vt)
{
	VAR_DECL_LIST* var_decl_list = NEW(VAR_DECL_LIST);
	var_decl_list->lineno = lineno;
	var_decl_list->var_decl_list = NULL;
	var_decl_list->var_type = vt;
	var_decl_list->kind = VDECL_TYPE;

	return var_decl_list;
}

VAR_TYPE* make_var_type_empty(char* id)
{
	VAR_TYPE* vt = NEW(VAR_TYPE);
	vt->lineno = lineno;
	vt->id = id;
	vt->type = NULL;

	return vt;
}

VAR_TYPE* make_var_type(char* id, TYPE* t)
{
	VAR_TYPE* vt = NEW(VAR_TYPE);
	vt->lineno = lineno;
	vt->id = calloc( strlen(id) + 1, sizeof(char));//id;
	strcpy(vt->id, id);
	vt->type = t;

	return vt;
}

VAR* make_var_id(char* id)
{
	VAR* v = NEW(VAR);
	v->lineno = lineno;
	v->kind = VAR_ID;
	v->id = calloc(strlen(id)+1, sizeof(char));
	strcpy(v->id, id);

	return v;
}

VAR* make_var_array(VAR* var, EXP* exp)
{
	VAR* v = NEW(VAR);
	v->lineno = lineno;
	v->kind = VAR_ARRAY;
	v->val.var_array.exp = exp;
	v->val.var_array.var = var;

	return v;
}

VAR* make_var_record(VAR* var, char* id)
{
	VAR* v = NEW(VAR);
	v->lineno = lineno;
	v->kind = VAR_RECORD;
	v->val.var_record.var = var;
	v->val.var_record.id = id;

	return v;
}

TERM* make_term_var(VAR* var)
{
	TERM* t = NEW(TERM);
	t->lineno = lineno;
	t->kind = TERM_VAR;
	t->val.var = var;

	return t;
}

TERM* make_term_act_list(char* id, ACT_LIST* act_list)
{
	TERM* t = NEW(TERM);
	t->lineno = lineno;
	t->kind = TERM_ACT_LIST;
	t->val.term_act_list.act_list = act_list;
	t->val.term_act_list.id = id;

	return t;
}

TERM* make_term_parentheses(EXP* exp)
{
	TERM* t = NEW(TERM);
	t->lineno = lineno;
	t->kind = TERM_PARENTHESES;
	t->val.exp = exp;

	return t;
}

TERM* make_term_not(TERM* term)
{
	TERM* t = NEW(TERM);
	t->lineno = lineno;
	t->kind = TERM_NOT;
	t->val.term = term;

	return t;
}

TERM* make_term_absolute(EXP* exp)
{
	TERM* t = NEW(TERM);
	t->lineno = lineno;
	t->kind = TERM_ABSOLUTE;
	t->val.exp = exp;

	return t;
}

TERM* make_term_num(int num)
{
	TERM* t = NEW(TERM);
	t->lineno = lineno;
	t->kind = TERM_NUM;
	t->val.num = num;

	return t;
}

TERM* make_term_true()
{
	TERM* t = NEW(TERM);
	t->lineno = lineno;
	t->kind = TERM_TRUE;

	return t;
}

TERM* make_term_false()
{
	TERM* t = NEW(TERM);
	t->lineno = lineno;
	t->kind = TERM_FALSE;

	return t;
}

TERM* make_term_null()
{
	TERM* t = NEW(TERM);
	t->lineno = lineno;
	t->kind = TERM_NULL;

	return t;
}

TERM* make_term_uminus(TERM* term)
{
	TERM* t = NEW(TERM);
	t->lineno = lineno;
	t->kind = TERM_UMINUS;
	t->val.term = term;

	return t;
}

ACT_LIST* make_act_list_empty()
{
	ACT_LIST* a = NEW(ACT_LIST);
	a->lineno = lineno;
	a->kind = ACT_LIST_EMPTY;

	return a;
}

ACT_LIST* make_act_list(EXP_LIST* list)
{
	ACT_LIST* a = NEW(ACT_LIST);
	a->lineno = lineno;
	a->kind = ACT_LIST_POPULATED;
	a->exp_list = list;

	return a;
}

EXP_LIST* make_exp_list_expression(EXP* expression)
{
	EXP_LIST* lst = NEW(EXP_LIST);
	lst->lineno = lineno;
	lst->exp = expression;
	lst->kind = EXPRESSION;

	return lst;
}

EXP_LIST* make_exp_list(EXP* expression, EXP_LIST* list)
{
	EXP_LIST* lst = NEW(EXP_LIST);
	lst->lineno = lineno;
	lst->exp = expression;
	lst->exp_list = list;
	lst->kind = EXPRESSION_LIST;

	return lst;
}
