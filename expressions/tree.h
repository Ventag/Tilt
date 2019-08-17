#ifndef __tree_h
#define __tree_h

#include "../symbols/symbol.h"

typedef struct EXP
{
	SYMBOL_TABLE* table;
	TYPEINFO* typeinfo;
  int lineno;
  enum
  {
    EXP_ID,
    EXP_INT,
    EXP_TIMES,
    EXP_DIV,
    EXP_PLUS,
    EXP_MINUS,
    EXP_LESS,
    EXP_LESS_EQUALS,
    EXP_GREATER,
    EXP_GREATER_EQUALS,
    EXP_EQUALS,
    EXP_AND,
    EXP_OR,
    EXP_NOT_EQUALS,
    EXP_TERM
  } kind;
  union
  {
    char *id;
    int int_const;
  	struct { struct EXP *left; struct EXP* right; } branches;
    struct TERM* term;
  } val;
} EXP;

typedef struct FUNCTION
{
	SYMBOL_TABLE* table;
	TYPEINFO* typeinfo;
	TYPEINFO* symbol_return_value;
	int lineno;
	int found_return_statement;

	struct HEAD* head;
	struct BODY* body;
	struct TAIL* tail;
} FUNCTION;

typedef struct HEAD
{
	SYMBOL_TABLE* table;
	TYPEINFO* typeinfo;
	int lineno;
	char* id;
	struct PAR_DECL_LIST* par_decl_list;
	struct TYPE* type;
} HEAD;

typedef struct TAIL
{
	int lineno;
	char* id;
} TAIL;

typedef struct BODY
{
	SYMBOL_TABLE* table;
	int lineno;
	struct DECL_LIST* decl_list;
	struct STATEMENT_LIST* statement_list;
} BODY;

typedef struct TYPE
{
	SYMBOL_TABLE* table;
	TYPEINFO* typeinfo;
	int lineno;
	enum
	{
		ID_T,
		INT_T,
		BOOL_T,
		ARRAY_T,
		RECORD_T
	} kind;

	union
	{
		char* id;
		struct TYPE* type;
		struct VAR_DECL_LIST* var_decl_list;
	} val;

} TYPE;

typedef struct PAR_DECL_LIST
{
	SYMBOL_TABLE* table;
	int lineno;

	struct VAR_DECL_LIST* var_decl_list;

	enum
	{
		PAR_DECL_LIST_EMPTY,
		PAR_DECL_LIST_POPLUATED
	} kind;
} PAR_DECL_LIST;

typedef struct VAR_DECL_LIST
{
	SYMBOL_TABLE* table;
	int lineno;

	struct VAR_DECL_LIST* var_decl_list;
	struct VAR_TYPE* var_type;

	enum
	{
		VDECL_LIST,
		VDECL_TYPE
	} kind;
} VAR_DECL_LIST;

typedef struct VAR_TYPE
{
	SYMBOL_TABLE* table;
	SYMBOL* symbol;
	int lineno;

	char *id;
	struct TYPE* type;
} VAR_TYPE;

typedef struct DECL_LIST
{
	SYMBOL_TABLE* table;
	int lineno;
	struct DECLARATION* declaration;
	struct DECL_LIST* decl_list;

	enum
	{
		DECL_LIST_EMPTY,
		DECL_LIST_POPULATED
	} kind;
} DECL_LIST;

typedef struct DECLARATION
{
	SYMBOL_TABLE* table;
	SYMBOL* symbol;
	int lineno;

	char* name;
	union
	{
		struct 
		{
			char* id;
			struct TYPE* type;
		} identifier;

		struct FUNCTION* function;
		struct VAR_DECL_LIST* var_decl_list;
	} val;

	enum
	{
		DECLARATION_ID,
		DECLARATION_FUNC,
		DECLARATION_VAR
	} kind;

} DECLARATION;

typedef struct STATEMENT_LIST
{
	SYMBOL_TABLE* table;
	int lineno;

	struct STATEMENT* statement;
	struct STATEMENT_LIST* statement_list;

	enum
	{
		STATEMENT_LIST_LIST,
		STATEMENT_LIST_ELEMENT
	} kind;
} STATEMENT_LIST;

typedef struct STATEMENT
{
	SYMBOL_TABLE* table;
	int lineno;
	int retval;

	union
	{
		struct EXP* exp;
		struct STATEMENT_LIST* statement_list;
		struct
		{
			struct EXP* exp;
		} stat_return; // creates a return statement that returns an expression/func

		struct
		{
			struct VAR* var;
			struct EXP* length;
		} stat_allocate; // needs additional datatype

		struct
		{
			struct VAR* var;
			struct EXP* exp;
		} stat_assign; // assigns a variable to an expression

		struct
		{
			struct STATEMENT* stat;
			struct STATEMENT_ELSE* optional_else; // optional else case to match an if
			struct EXP* condition;
		} stat_if;

		struct
		{
			struct STATEMENT* stat;
			struct EXP* condition;
		} stat_while;

		struct
		{
			struct STATEMENT* assign;
			struct EXP* condition;
			struct STATEMENT* update;
			struct STATEMENT* stat;
		} stat_for;

	} val;

	enum
	{
		RETURN,
		WRITE,
		ALLOCATE,
		ASSIGN,
		IF,
		WHILE,
		WHILE_LIST,
		FOR
	} kind;
} STATEMENT;

typedef struct STATEMENT_ELSE
{
	SYMBOL_TABLE* table;
	int lineno;

	enum
	{
		ELSE_INACTIVE,
		ELSE_ACTIVE
	} kind;

	STATEMENT* statement;
} STATEMENT_ELSE;

typedef struct VAR
{
	SYMBOL_TABLE* table;
	TYPEINFO* typeinfo;
	int lineno;
	char* id;

	enum
	{
		VAR_ID,
		VAR_ARRAY,
		VAR_RECORD
	} kind;

	union
	{
		struct
		{
			struct VAR* var;
			struct EXP* exp;
		} var_array;

		struct
		{
			char* id;
			struct VAR* var;
		} var_record;
	} val;
} VAR;

typedef struct TERM
{
	SYMBOL_TABLE* table;
	TYPEINFO* typeinfo;
	int lineno;

	union
	{
		int num;
		struct VAR* var;
		struct
		{
			char* id;
			struct ACT_LIST* act_list;
		} term_act_list;
		struct EXP* exp;
		struct TERM* term;
	} val;

	enum
	{
		TERM_VAR,
		TERM_ACT_LIST,
		TERM_PARENTHESES,
		TERM_NOT,
		TERM_ABSOLUTE,
		TERM_NUM,
		TERM_TRUE,
		TERM_FALSE,
		TERM_NULL,
		TERM_UMINUS
	} kind;
} TERM;

typedef struct ACT_LIST
{
	SYMBOL_TABLE* table;
	int lineno;

	enum
	{
		ACT_LIST_EMPTY,
		ACT_LIST_POPULATED
	} kind;

	struct EXP_LIST* exp_list;
} ACT_LIST;

typedef struct EXP_LIST
{
	SYMBOL_TABLE* table;
	int lineno;

	enum
	{
		EXPRESSION_LIST,
		EXPRESSION
	} kind;

	struct EXP* exp;
	struct EXP_LIST* exp_list;
} EXP_LIST;

EXP *make_exp_id(char *id);
EXP *make_exp_int_const(int intconst);
EXP *make_exp_times(EXP *left, EXP *right);
EXP *make_exp_div(EXP *left, EXP *right);
EXP *make_exp_plus(EXP *left, EXP *right);
EXP *make_exp_minus(EXP *left, EXP *right);
EXP *make_exp_less(EXP *left, EXP *right);
EXP *make_exp_less_equals(EXP *left, EXP *right);
EXP *make_exp_greater(EXP *left, EXP *right);
EXP *make_exp_greater_equals(EXP *left, EXP *right);
EXP *make_exp_equals(EXP *left, EXP *right);
EXP *make_exp_not_equals(EXP *left, EXP *right);
EXP *make_exp_and(EXP *left, EXP *right);
EXP *make_exp_or(EXP *left, EXP *right);
EXP* make_exp_term(TERM* exp);

FUNCTION* make_function(HEAD* head, BODY* body, TAIL* tail);
HEAD* make_head(char* id, PAR_DECL_LIST* par_decl_list, TYPE* type);
BODY* make_body(DECL_LIST* decl_list, STATEMENT_LIST* list);
TAIL* make_tail(char* id);

TYPE* make_id_type(char* id);
TYPE* make_int_type();
TYPE* make_bool_type();
TYPE* make_array_of_type(TYPE* t);
TYPE* make_record_of_type(VAR_DECL_LIST* lst);

DECLARATION* make_declaration_id(char* name, TYPE* type);
DECLARATION* make_declaration_function(FUNCTION* func);
DECLARATION* make_declaration_var(VAR_DECL_LIST* var_decl_list);

DECL_LIST* make_decl_list(DECLARATION* decl, DECL_LIST* decl_list);
DECL_LIST* make_decl_list_empty();

PAR_DECL_LIST* make_par_decl_list(VAR_DECL_LIST* var_decl_list);
PAR_DECL_LIST* make_par_decl_list_empty();

STATEMENT_LIST* make_statement_empty_list(STATEMENT* statement);
STATEMENT_LIST* make_statement_list(STATEMENT* statement, STATEMENT_LIST* list);

STATEMENT* make_statement_return(EXP* exp);
STATEMENT* make_statement_write(EXP* exp);
STATEMENT* make_statement_allocate(VAR* variable, EXP* length);
STATEMENT* make_statement_assign(VAR* variable, EXP* expression);
STATEMENT* make_statement_if(EXP* expression, STATEMENT* stat, STATEMENT_ELSE* stat_else);
STATEMENT* make_statement_while(EXP* expression, STATEMENT* stat);
STATEMENT* make_statement_while_list(STATEMENT_LIST* statement_list);
STATEMENT* make_statement_for(STATEMENT*, EXP*, STATEMENT*, STATEMENT*);

STATEMENT_ELSE* make_statement_else(STATEMENT* stat);
STATEMENT_ELSE* make_statement_else_empty();

VAR_DECL_LIST* make_var_decl_list(VAR_TYPE* vt, VAR_DECL_LIST* vdl);
VAR_DECL_LIST* make_var_decl_list_empty(VAR_TYPE* vt);

VAR_TYPE* make_var_type_empty(char* id);
VAR_TYPE* make_var_type(char* id, TYPE* t);

VAR* make_var_id(char* id);
VAR* make_var_array(VAR* var, EXP* exp);
VAR* make_var_record(VAR* var, char* id);

TERM* make_term_var(VAR* var);
TERM* make_term_act_list(char* id, ACT_LIST* act_list);
TERM* make_term_parentheses(EXP* exp);
TERM* make_term_not(TERM* term);
TERM* make_term_absolute(EXP* exp);
TERM* make_term_num(int num);
TERM* make_term_true();
TERM* make_term_false();
TERM* make_term_null();
TERM* make_term_uminus(TERM*);

ACT_LIST* make_act_list_empty();
ACT_LIST* make_act_list(EXP_LIST* list);

EXP_LIST* make_exp_list_expression(EXP* expression);
EXP_LIST* make_exp_list(EXP* expression, EXP_LIST* list);
#endif
