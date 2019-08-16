%{
#include <stdio.h>
#include <string.h>
#include "tree.h"

extern char *yytext;
extern BODY* __main__;

void yyerror()
{
   printf("syntax error before %s\n",yytext);
}

int yylex();

%}

%union
{
   int intconst;
   char *stringconst;
   struct EXP *exp;
   struct FUNCTION* function;
   struct HEAD* head;
   struct TAIL* tail;
   struct BODY* body;
   struct TYPE* type;
   struct PAR_DECL_LIST* par_decl_list;
   struct VAR_DECL_LIST* var_decl_list;
   struct VAR_TYPE* var_type;
   struct DECL_LIST* decl_list;
   struct DECLARATION* declaration;
   struct STATEMENT_LIST* statement_list;
   struct STATEMENT* statement;
   struct VAR* var;
   struct STATEMENT_ELSE* statement_else;
   struct TERM* term;
   struct ACT_LIST* act_list;
   struct EXP_LIST* exp_list;
}

%token <intconst> INT_TOKEN
%token <stringconst> ID_TOKEN
%token BOOL_TOKEN
%token ARRAY_OF_TOKEN
%token RECORD_OF_TOKEN
%token BOOL_FALSE
%token BOOL_TRUE
%token BOOL_EQUALS
%token BOOL_NOT_EQUALS
%token ADD_EQUAL;
%token SUB_EQUAL;
%token MUL_EQUAL;
%token DIV_EQUAL;
%token LESS_OR_EQUAL;
%token GREATER_OR_EQUAL;
%token AND;
%token OR;
%token NULL_TOKEN;
%token FOR_TOKEN

%token FUNCTION_START;
%token FUNCTION_END;

%token TYPE_TOKEN
%token VAR_TOKEN
%token RETURN_TOKEN
%token ALLOCATE_TOKEN
%token IF_TOKEN
%token THEN_TOKEN
%token ELSE_TOKEN
%token WHILE_TOKEN
%token DO_TOKEN
%token WRITE_TOKEN
%token OF_LENGTH_TOKEN

%type <head> head
%type <body> program body
%type <tail> tail
%type <type> type;
%type <exp> exp
%type <function> function
%type <statement_list> statement_list
%type <statement> statement
%type <decl_list> decl_list
%type <par_decl_list> par_decl_list
%type <declaration> declaration;
%type <var_decl_list> var_decl_list
%type <var_type> var_type
%type <var> var
%type <statement_else> statement_else
%type <term> term
%type <act_list> act_list
%type <exp_list> exp_list

%start program

%left '+' '-'
%left '*' '/'

%nonassoc ELSE_TOKEN
%nonassoc "U_Minus"

%%

program         : body { __main__ = $1;}
                ;

function        : head body tail
                {
                  $$ = make_function($1, $2, $3);
                }
                ;

head            : FUNCTION_START ID_TOKEN '(' par_decl_list ')' ':' type { $$ = make_head($2, $4, $7); }
                ;
				
body            : decl_list statement_list { $$ = make_body($1, $2); }
                ;

tail            : FUNCTION_END ID_TOKEN { $$ = make_tail($2); }
                ;

exp             : exp '*' exp {$$ = make_exp_times($1,$3);}
                | exp '/' exp {$$ = make_exp_div($1,$3);}
                | exp '+' exp {$$ = make_exp_plus($1,$3);}
                | exp '-' exp {$$ = make_exp_minus($1,$3);}
                | exp '<' exp {$$ = make_exp_less($1,$3);}
                | exp LESS_OR_EQUAL exp {$$ = make_exp_less_equals($1,$3);}
                | exp '>' exp {$$ = make_exp_greater($1,$3);}
                | exp GREATER_OR_EQUAL exp {$$ = make_exp_greater_equals($1,$3);}
                | exp BOOL_EQUALS exp {$$ = make_exp_equals($1,$3);}
                | exp BOOL_NOT_EQUALS exp {$$ = make_exp_not_equals($1,$3);}
                | exp AND exp {$$ = make_exp_and($1,$3);}
                | exp OR exp {$$ = make_exp_or($1,$3);}
                | '(' exp ')' {$$ = $2;}
                | term { $$ = make_exp_term($1); }
                ;

type            : ID_TOKEN { $$ = make_id_type($1); }
                | INT_TOKEN { $$ = make_int_type(); }
                | BOOL_TOKEN { $$ = make_bool_type(); }
                | ARRAY_OF_TOKEN type { $$ = make_array_of_type($2); }
                | RECORD_OF_TOKEN var_decl_list { $$ = make_record_of_type($2); }
                ;


decl_list       : declaration decl_list { $$ = make_decl_list($1, $2);}
                | { $$ = make_decl_list_empty(); }
                ;

par_decl_list   : var_decl_list { $$ = make_par_decl_list($1); }
                | { $$ =  make_par_decl_list_empty(); }
                ;

declaration     : TYPE_TOKEN ID_TOKEN '=' type ';' { $$ = make_declaration_id($2, $4); }
                | function { $$ = make_declaration_function($1); }
                | VAR_TOKEN var_decl_list ';' { $$ = make_declaration_var($2); }
                ;

statement_list  : statement { $$ = make_statement_empty_list($1); }
                | statement statement_list { $$ = make_statement_list($1, $2); }
                ;

statement       : RETURN_TOKEN exp ';' { $$ = make_statement_return($2); }
				| WRITE_TOKEN exp ';' { $$ = make_statement_write($2); }
                | ALLOCATE_TOKEN var OF_LENGTH_TOKEN exp ';' { $$ = make_statement_allocate($2, $4); }
				| var '=' exp ';' { $$ = make_statement_assign($1, $3); }
                | IF_TOKEN exp THEN_TOKEN statement statement_else { $$ = make_statement_if($2, $4, $5); }
                | WHILE_TOKEN exp DO_TOKEN statement { $$ = make_statement_while($2, $4); }
				| '{' statement_list '}' { $$ = make_statement_while_list($2); }
				| FOR_TOKEN '('statement exp ';' statement ')'  DO_TOKEN '{' statement '}' {$$ = make_statement_for($3, $4, $6, $10);}
                ;

statement_else  : ELSE_TOKEN statement { $$ = make_statement_else($2); }
				| { $$ = make_statement_else_empty(); }
                ;

var_decl_list   : var_type ',' var_decl_list { $$ = make_var_decl_list($1, $3); }
                | var_type { $$ = make_var_decl_list_empty($1); }
                ;

var_type        : ID_TOKEN ':' type { $$ = make_var_type($1, $3); }
                ;

var             : ID_TOKEN { $$ = make_var_id($1); }
                | var '[' exp ']' { $$ = make_var_array($1, $3); }
                | var '.' ID_TOKEN { $$ = make_var_record($1, $3); }
                ;

term            : var { $$ = make_term_var($1); }
                | ID_TOKEN '(' act_list ')' { $$ = make_term_act_list($1, $3); }
                | '(' exp ')' { $$ = make_term_parentheses($2); }
                | '!' term { $$ = make_term_not($2); }
                | '|' exp '|' { $$ = make_term_absolute($2); }
				| '-' term %prec "U_Minus" {$$ = make_term_uminus($2); }
                | INT_TOKEN { $$ = make_term_num($1); }
                | BOOL_TRUE { $$ = make_term_true(); }
                | BOOL_FALSE { $$ = make_term_false(); }
                | NULL_TOKEN { $$ = make_term_null(); }
                ;

act_list        : exp_list { $$ = make_act_list($1); }
                | { $$ = make_act_list_empty(); }
                ;

exp_list        : exp { $$ = make_exp_list_expression($1); }
                | exp ',' exp_list { $$ = make_exp_list($1, $3); }
                ;

%%
