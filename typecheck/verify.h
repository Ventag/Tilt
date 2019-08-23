#ifndef __process_h
#define __process_h

#include <stdlib.h>
#include <stdio.h>
#include "../symbols/symbol.h"
#include "../expressions/tree.h"
#include "collect.h"

void verify(BODY*);

void verify_body(BODY*);
void verify_head(HEAD*);
void verify_function(FUNCTION*);
void verify_type(TYPE*);
void verify_par_decl_list(PAR_DECL_LIST*);
void verify_var_decl_list(VAR_DECL_LIST*);
void verify_var_type(VAR_TYPE*);
void verify_decl_list(DECL_LIST*);
void verify_declaration( DECLARATION* );
void verify_statement(STATEMENT*);
void verify_statement_list(STATEMENT_LIST*);
void verify_else(STATEMENT_ELSE*);
void verify_exp(EXP*);
void verify_term(TERM*);
void verify_var(VAR*);
void verify_act_list(ACT_LIST*, int*);
void verify_exp_list(EXP_LIST*, int*);

#endif