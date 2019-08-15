#ifndef __process_h
#define __process_h

#include <stdlib.h>
#include <stdio.h>
#include "../symbols/symbol.h"
#include "../expressions/tree.h"
#include "collect.h"

void process( BODY* );
void process_body( BODY* );
void process_head( HEAD* );
void process_function( FUNCTION* );
void process_type( TYPE* );
void process_par_decl_list( PAR_DECL_LIST* );
void process_var_decl_list( VAR_DECL_LIST* );
void process_var_type( VAR_TYPE* );
void process_decl_list( DECL_LIST* );
void process_declaration( DECLARATION* );
#endif