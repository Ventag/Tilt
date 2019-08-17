#ifndef __ir_tree_h
#define __ir_tree_h

#include "../expressions/tree.h"
#include "../symbols/linkedlist.h"
#include "instruction_set.h"

typedef struct IMMEDIATECODE
{
	enum
	{
		NONE,
		PARAM,
		LOCAL,
		RECORD,
		ARRAY
	}kind;

	int onheap;
	int offset;
	int local_var_count;
	int depth;
} IMMEDIATECODE;

LINKEDLIST* build_ir_tree(BODY*, int);
void ir_func(FUNCTION*);
void ir_head(HEAD*);
void ir_body(BODY*);
void ir_par_decl_list(PAR_DECL_LIST* pdecl);
void ir_var_decl_list(VAR_DECL_LIST*);
void ir_var_type(VAR_TYPE*);
void ir_decl_list(DECL_LIST*);
void ir_declaration(DECLARATION*);
void ir_statement_list(STATEMENT_LIST*);
void ir_statement(STATEMENT*);
void ir_act_list(ACT_LIST*);
void ir_exp_list(EXP_LIST*);
void ir_exp(EXP*);
void ir_term(TERM*);
void ir_var(VAR*);

void function_prolog(SYMBOL_TABLE*), function_epilog();

void allocate_local_vars();

void data_section();

typedef enum LABEL_KIND
{
	UNKNOWN,
	FUNC,
	FLOW
} LABEL_KIND;

char* create_label(LABEL_KIND, char*, int);

#endif // !__ir_tree_h
