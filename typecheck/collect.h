#ifndef __collect_h
#define __collect_h

#include <stdlib.h>
#include <stdio.h>
#include "../symbols/symbol.h"
#include "../symbols/memory.h"
#include "../expressions/tree.h"

void collect(BODY*);
void collect_func(FUNCTION*, SYMBOL_TABLE*);
void collect_head(HEAD*, SYMBOL_TABLE*);
void collect_body(BODY*, SYMBOL_TABLE*);

int collect_par_decl_list(PAR_DECL_LIST*, SYMBOL_TABLE*);
int collect_var_decl_list(VAR_DECL_LIST*, SYMBOL_TABLE*, SYMBOL_KINDS);

SYMBOL_VALUE* collect_type(TYPE*, SYMBOL_TABLE*);
SYMBOL_VALUE* create_symbol_value(SYMBOL_TYPES);

void collect_var_type(VAR_TYPE*, SYMBOL_TABLE*, SYMBOL_KINDS);
void collect_decl_list(DECL_LIST*, SYMBOL_TABLE*);
void collect_declaration(DECLARATION*, SYMBOL_TABLE*);
void collect_statement_list(STATEMENT_LIST*, SYMBOL_TABLE*);
void collect_statement(STATEMENT*, SYMBOL_TABLE*);
void collect_else(STATEMENT_ELSE*, SYMBOL_TABLE*);
void collect_variable(VAR*, SYMBOL_TABLE*);
void collect_expression(EXP*, SYMBOL_TABLE*);
void collect_term(TERM*, SYMBOL_TABLE*);
void collect_act_list(ACT_LIST*, SYMBOL_TABLE*);
void collect_exp_list(EXP_LIST*, SYMBOL_TABLE*);

extern int unknown_user_types;

#endif