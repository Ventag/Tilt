#ifndef __weeder_h
#define __weeder_h

#include "../expressions/tree.h"


BODY* weeder(BODY* body);
FUNCTION* weed_func(FUNCTION*);
BODY* weed_body(BODY*);
HEAD* weed_head(HEAD* head);
TYPE*  weed_type(TYPE* type);
PAR_DECL_LIST* weed_par_decl_list(PAR_DECL_LIST* par_decl_list);
VAR_DECL_LIST* weed_var_decl_list(VAR_DECL_LIST* var_decl_list);
VAR_TYPE* weed_var_type(VAR_TYPE* var_type);
DECL_LIST* weed_decl_list(DECL_LIST*);
DECLARATION* weed_declaration(DECLARATION*);
STATEMENT_LIST* weed_stmt_list(STATEMENT_LIST*);
STATEMENT* weed_stmt(STATEMENT*);
STATEMENT_ELSE* weed_stmt_else(STATEMENT_ELSE*);
EXP* weed_exp(EXP* expression);



#endif