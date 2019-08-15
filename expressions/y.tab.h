/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT_TOKEN = 258,
    ID_TOKEN = 259,
    BOOL_TOKEN = 260,
    ARRAY_OF_TOKEN = 261,
    RECORD_OF_TOKEN = 262,
    BOOL_FALSE = 263,
    BOOL_TRUE = 264,
    BOOL_EQUALS = 265,
    BOOL_NOT_EQUALS = 266,
    ADD_EQUAL = 267,
    SUB_EQUAL = 268,
    MUL_EQUAL = 269,
    DIV_EQUAL = 270,
    LESS_OR_EQUAL = 271,
    GREATER_OR_EQUAL = 272,
    AND = 273,
    OR = 274,
    NULL_TOKEN = 275,
    FOR_TOKEN = 276,
    FUNCTION_START = 277,
    FUNCTION_END = 278,
    TYPE_TOKEN = 279,
    VAR_TOKEN = 280,
    RETURN_TOKEN = 281,
    ALLOCATE_TOKEN = 282,
    IF_TOKEN = 283,
    THEN_TOKEN = 284,
    ELSE_TOKEN = 285,
    WHILE_TOKEN = 286,
    DO_TOKEN = 287,
    WRITE_TOKEN = 288,
    OF_LENGTH_TOKEN = 289
  };
#endif
/* Tokens.  */
#define INT_TOKEN 258
#define ID_TOKEN 259
#define BOOL_TOKEN 260
#define ARRAY_OF_TOKEN 261
#define RECORD_OF_TOKEN 262
#define BOOL_FALSE 263
#define BOOL_TRUE 264
#define BOOL_EQUALS 265
#define BOOL_NOT_EQUALS 266
#define ADD_EQUAL 267
#define SUB_EQUAL 268
#define MUL_EQUAL 269
#define DIV_EQUAL 270
#define LESS_OR_EQUAL 271
#define GREATER_OR_EQUAL 272
#define AND 273
#define OR 274
#define NULL_TOKEN 275
#define FOR_TOKEN 276
#define FUNCTION_START 277
#define FUNCTION_END 278
#define TYPE_TOKEN 279
#define VAR_TOKEN 280
#define RETURN_TOKEN 281
#define ALLOCATE_TOKEN 282
#define IF_TOKEN 283
#define THEN_TOKEN 284
#define ELSE_TOKEN 285
#define WHILE_TOKEN 286
#define DO_TOKEN 287
#define WRITE_TOKEN 288
#define OF_LENGTH_TOKEN 289

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 19 "exp.y" /* yacc.c:1909  */

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

#line 145 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
