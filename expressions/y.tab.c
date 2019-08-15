/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "exp.y" /* yacc.c:339  */

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


#line 83 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
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
#line 19 "exp.y" /* yacc.c:355  */

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

#line 214 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 231 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   417

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  64
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  141

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    53,     2,     2,     2,     2,     2,     2,
      40,    41,    37,    35,    49,    36,    52,    38,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    42,    46,
      43,    45,    44,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    50,     2,    51,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    47,    54,    48,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      39
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   106,   106,   109,   115,   118,   121,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   140,   141,   142,   143,   144,   148,   149,   152,   153,
     156,   157,   158,   161,   162,   165,   166,   167,   168,   169,
     170,   171,   172,   175,   176,   179,   180,   183,   186,   187,
     188,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   203,   204,   207,   208
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT_TOKEN", "ID_TOKEN", "BOOL_TOKEN",
  "ARRAY_OF_TOKEN", "RECORD_OF_TOKEN", "BOOL_FALSE", "BOOL_TRUE",
  "BOOL_EQUALS", "BOOL_NOT_EQUALS", "ADD_EQUAL", "SUB_EQUAL", "MUL_EQUAL",
  "DIV_EQUAL", "LESS_OR_EQUAL", "GREATER_OR_EQUAL", "AND", "OR",
  "NULL_TOKEN", "FOR_TOKEN", "FUNCTION_START", "FUNCTION_END",
  "TYPE_TOKEN", "VAR_TOKEN", "RETURN_TOKEN", "ALLOCATE_TOKEN", "IF_TOKEN",
  "THEN_TOKEN", "ELSE_TOKEN", "WHILE_TOKEN", "DO_TOKEN", "WRITE_TOKEN",
  "OF_LENGTH_TOKEN", "'+'", "'-'", "'*'", "'/'", "\"U_Minus\"", "'('",
  "')'", "':'", "'<'", "'>'", "'='", "';'", "'{'", "'}'", "','", "'['",
  "']'", "'.'", "'!'", "'|'", "$accept", "program", "function", "head",
  "body", "tail", "exp", "type", "decl_list", "par_decl_list",
  "declaration", "statement_list", "statement", "statement_else",
  "var_decl_list", "var_type", "var", "term", "act_list", "exp_list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,    43,    45,    42,    47,   290,
      40,    41,    58,    60,    62,    61,    59,   123,   125,    44,
      91,    93,    46,    33,   124
};
# endif

#define YYPACT_NINF -36

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-36)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -19,     0,     9,    13,     8,   -36,   -19,   -36,   121,   -19,
     -13,   -10,     7,    16,     1,   -36,    53,   -36,    37,    84,
      76,    84,    84,    84,   121,   -36,   121,   -26,   -36,    13,
     390,   390,   -36,    13,    77,   -36,   121,   -36,    46,   -36,
     -36,   -36,   103,    84,   103,    84,   194,   -20,   -36,    81,
     292,   321,   206,    49,   -36,    84,    84,    90,    57,   -36,
     -36,   -36,   -36,   390,    13,    54,   -36,   -36,   -36,    84,
      84,    84,   -36,   331,   -36,     4,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,   -36,   237,
     121,   121,   -36,   -36,   249,   148,   -36,    60,   -36,   -36,
     -36,   280,   159,    58,   -36,   344,   -36,   -36,   373,   373,
     373,   373,   373,   373,   163,   163,    35,    35,   373,   373,
     -36,    75,   -36,   -36,   -36,   390,   121,    84,   -36,   -36,
     121,   -36,   -36,    67,   -36,   -36,    78,    62,   121,    65,
     -36
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      27,     0,     0,     0,     0,    31,    27,     2,     0,    27,
       0,     0,     0,     0,    46,     1,     0,    48,     0,     0,
       0,     0,     0,     0,     0,     5,    33,     0,    26,    29,
       0,     0,    32,     0,     0,     3,     0,    57,    48,    59,
      58,    60,     0,     0,     0,     0,     0,    51,    20,     0,
       0,     0,     0,     0,    34,     0,     0,     0,     0,    28,
      22,    21,    23,     0,     0,     0,    47,    45,     6,     0,
      62,     0,    56,     0,    54,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    35,     0,
       0,     0,    36,    41,     0,     0,    50,     0,    24,    25,
      30,     0,    63,     0,    61,     0,    19,    55,    15,    16,
      12,    14,    17,    18,     9,    10,     7,     8,    11,    13,
      37,    44,    40,    38,    49,     0,     0,     0,    52,    53,
       0,    39,     4,     0,    64,    43,     0,     0,     0,     0,
      42
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -36,   -36,   -36,   -36,   108,   -36,   -12,   -29,   106,   -36,
     -36,    12,   -35,   -36,    -4,   -36,    -8,    19,   -36,   -11
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,     7,    35,   102,    65,     8,    58,
       9,    25,    26,   131,    13,    14,    47,    48,   103,   104
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      27,    69,    66,     1,    10,     2,     3,    46,    15,    50,
      51,    52,    49,    11,    76,    77,    27,    12,    27,    55,
      78,    79,    80,    81,    56,    59,    57,    29,    27,    67,
      56,    73,    57,    75,    98,    30,    53,    89,    54,    82,
      83,    84,    85,    94,    95,    76,    77,    86,    87,    31,
      33,    78,    79,    80,    81,   121,   122,   101,   107,   105,
      99,    72,    32,    74,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,    34,    36,    86,    87,
      17,    68,    27,    27,    37,    38,    70,    37,    38,    39,
      40,   133,    39,    40,    96,   135,   132,    93,    97,   128,
     100,    41,   125,   139,    41,   130,    37,    38,   136,   138,
     137,    39,    40,   140,    16,    28,   134,    42,    27,     0,
      42,    43,    27,    41,    43,    17,     0,     0,     0,     0,
      27,    56,     0,    57,    44,    45,     0,    44,    45,    42,
       0,     0,    18,    71,     0,     0,     0,    19,    20,    21,
       0,     0,    22,     0,    23,     0,    44,    45,    76,    77,
       0,     0,     0,     0,    78,    79,    80,    81,    24,    76,
      77,     0,     0,    76,    77,    78,    79,    80,    81,    78,
      79,    80,    81,    82,    83,    84,    85,     0,     0,     0,
       0,    86,    87,     0,    82,    83,    84,    85,     0,   124,
      84,    85,    86,    87,    76,    77,    86,    87,   127,     0,
      78,    79,    80,    81,     0,     0,    76,    77,     0,     0,
       0,     0,    78,    79,    80,    81,     0,     0,     0,    82,
      83,    84,    85,     0,     0,     0,     0,    86,    87,     0,
      88,    82,    83,    84,    85,     0,     0,    76,    77,    86,
      87,     0,    92,    78,    79,    80,    81,     0,     0,    76,
      77,     0,     0,     0,     0,    78,    79,    80,    81,     0,
       0,     0,    82,    83,    84,    85,     0,     0,     0,     0,
      86,    87,     0,   120,    82,    83,    84,    85,     0,     0,
      76,    77,    86,    87,     0,   123,    78,    79,    80,    81,
       0,     0,    76,    77,     0,     0,     0,     0,    78,    79,
      80,    81,     0,     0,     0,    82,    83,    84,    85,     0,
       0,    90,     0,    86,    87,     0,   126,    82,    83,    84,
      85,    76,    77,     0,     0,    86,    87,    78,    79,    80,
      81,    76,    77,     0,     0,     0,     0,    78,    79,    80,
      81,     0,     0,    91,    76,    77,    82,    83,    84,    85,
      78,    79,    80,    81,    86,    87,    82,    83,    84,    85,
       0,     0,   106,     0,    86,    87,     0,     0,     0,    82,
      83,    84,    85,    76,    77,   129,     0,    86,    87,    78,
      79,    80,    81,    60,    61,    62,    63,    64,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    82,    83,
      84,    85,     0,     0,     0,     0,    86,    87
};

static const yytype_int16 yycheck[] =
{
       8,    36,    31,    22,     4,    24,    25,    19,     0,    21,
      22,    23,    20,     4,    10,    11,    24,     4,    26,    45,
      16,    17,    18,    19,    50,    29,    52,    40,    36,    33,
      50,    43,    52,    45,    63,    45,    24,    49,    26,    35,
      36,    37,    38,    55,    56,    10,    11,    43,    44,    42,
      49,    16,    17,    18,    19,    90,    91,    69,    54,    71,
      64,    42,    46,    44,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    23,    40,    43,    44,
       4,     4,    90,    91,     3,     4,    40,     3,     4,     8,
       9,   126,     8,     9,     4,   130,   125,    48,    41,    41,
      46,    20,    42,   138,    20,    30,     3,     4,    41,    47,
      32,     8,     9,    48,     6,     9,   127,    36,   126,    -1,
      36,    40,   130,    20,    40,     4,    -1,    -1,    -1,    -1,
     138,    50,    -1,    52,    53,    54,    -1,    53,    54,    36,
      -1,    -1,    21,    40,    -1,    -1,    -1,    26,    27,    28,
      -1,    -1,    31,    -1,    33,    -1,    53,    54,    10,    11,
      -1,    -1,    -1,    -1,    16,    17,    18,    19,    47,    10,
      11,    -1,    -1,    10,    11,    16,    17,    18,    19,    16,
      17,    18,    19,    35,    36,    37,    38,    -1,    -1,    -1,
      -1,    43,    44,    -1,    35,    36,    37,    38,    -1,    51,
      37,    38,    43,    44,    10,    11,    43,    44,    49,    -1,
      16,    17,    18,    19,    -1,    -1,    10,    11,    -1,    -1,
      -1,    -1,    16,    17,    18,    19,    -1,    -1,    -1,    35,
      36,    37,    38,    -1,    -1,    -1,    -1,    43,    44,    -1,
      46,    35,    36,    37,    38,    -1,    -1,    10,    11,    43,
      44,    -1,    46,    16,    17,    18,    19,    -1,    -1,    10,
      11,    -1,    -1,    -1,    -1,    16,    17,    18,    19,    -1,
      -1,    -1,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      43,    44,    -1,    46,    35,    36,    37,    38,    -1,    -1,
      10,    11,    43,    44,    -1,    46,    16,    17,    18,    19,
      -1,    -1,    10,    11,    -1,    -1,    -1,    -1,    16,    17,
      18,    19,    -1,    -1,    -1,    35,    36,    37,    38,    -1,
      -1,    29,    -1,    43,    44,    -1,    46,    35,    36,    37,
      38,    10,    11,    -1,    -1,    43,    44,    16,    17,    18,
      19,    10,    11,    -1,    -1,    -1,    -1,    16,    17,    18,
      19,    -1,    -1,    32,    10,    11,    35,    36,    37,    38,
      16,    17,    18,    19,    43,    44,    35,    36,    37,    38,
      -1,    -1,    41,    -1,    43,    44,    -1,    -1,    -1,    35,
      36,    37,    38,    10,    11,    41,    -1,    43,    44,    16,
      17,    18,    19,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    36,
      37,    38,    -1,    -1,    -1,    -1,    43,    44
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    22,    24,    25,    56,    57,    58,    59,    63,    65,
       4,     4,     4,    69,    70,     0,    59,     4,    21,    26,
      27,    28,    31,    33,    47,    66,    67,    71,    63,    40,
      45,    42,    46,    49,    23,    60,    40,     3,     4,     8,
       9,    20,    36,    40,    53,    54,    61,    71,    72,    71,
      61,    61,    61,    66,    66,    45,    50,    52,    64,    69,
       3,     4,     5,     6,     7,    62,    62,    69,     4,    67,
      40,    40,    72,    61,    72,    61,    10,    11,    16,    17,
      18,    19,    35,    36,    37,    38,    43,    44,    46,    61,
      29,    32,    46,    48,    61,    61,     4,    41,    62,    69,
      46,    61,    61,    73,    74,    61,    41,    54,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      46,    67,    67,    46,    51,    42,    46,    49,    41,    41,
      30,    68,    62,    67,    74,    67,    41,    32,    47,    67,
      48
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    55,    56,    57,    58,    59,    60,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    62,    62,    62,    62,    62,    63,    63,    64,    64,
      65,    65,    65,    66,    66,    67,    67,    67,    67,    67,
      67,    67,    67,    68,    68,    69,    69,    70,    71,    71,
      71,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    73,    73,    74,    74
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     3,     7,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     1,     1,     1,     2,     2,     2,     0,     1,     0,
       5,     1,     3,     1,     2,     3,     3,     4,     4,     5,
       4,     3,    11,     2,     0,     3,     1,     3,     1,     4,
       3,     1,     4,     3,     2,     3,     2,     1,     1,     1,
       1,     1,     0,     1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 106 "exp.y" /* yacc.c:1646  */
    { __main__ = (yyvsp[0].body);}
#line 1460 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 110 "exp.y" /* yacc.c:1646  */
    {
                  (yyval.function) = make_function((yyvsp[-2].head), (yyvsp[-1].body), (yyvsp[0].tail));
                }
#line 1468 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 115 "exp.y" /* yacc.c:1646  */
    { (yyval.head) = make_head((yyvsp[-5].stringconst), (yyvsp[-3].par_decl_list), (yyvsp[0].type)); }
#line 1474 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 118 "exp.y" /* yacc.c:1646  */
    { (yyval.body) = make_body((yyvsp[-1].decl_list), (yyvsp[0].statement_list)); }
#line 1480 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 121 "exp.y" /* yacc.c:1646  */
    { (yyval.tail) = make_tail((yyvsp[0].stringconst)); }
#line 1486 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 124 "exp.y" /* yacc.c:1646  */
    {(yyval.exp) = make_exp_times((yyvsp[-2].exp),(yyvsp[0].exp));}
#line 1492 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 125 "exp.y" /* yacc.c:1646  */
    {(yyval.exp) = make_exp_div((yyvsp[-2].exp),(yyvsp[0].exp));}
#line 1498 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 126 "exp.y" /* yacc.c:1646  */
    {(yyval.exp) = make_exp_plus((yyvsp[-2].exp),(yyvsp[0].exp));}
#line 1504 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 127 "exp.y" /* yacc.c:1646  */
    {(yyval.exp) = make_exp_minus((yyvsp[-2].exp),(yyvsp[0].exp));}
#line 1510 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 128 "exp.y" /* yacc.c:1646  */
    {(yyval.exp) = make_exp_less((yyvsp[-2].exp),(yyvsp[0].exp));}
#line 1516 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 129 "exp.y" /* yacc.c:1646  */
    {(yyval.exp) = make_exp_less_equals((yyvsp[-2].exp),(yyvsp[0].exp));}
#line 1522 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 130 "exp.y" /* yacc.c:1646  */
    {(yyval.exp) = make_exp_greater((yyvsp[-2].exp),(yyvsp[0].exp));}
#line 1528 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 131 "exp.y" /* yacc.c:1646  */
    {(yyval.exp) = make_exp_greater_equals((yyvsp[-2].exp),(yyvsp[0].exp));}
#line 1534 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 132 "exp.y" /* yacc.c:1646  */
    {(yyval.exp) = make_exp_equals((yyvsp[-2].exp),(yyvsp[0].exp));}
#line 1540 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 133 "exp.y" /* yacc.c:1646  */
    {(yyval.exp) = make_exp_not_equals((yyvsp[-2].exp),(yyvsp[0].exp));}
#line 1546 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 134 "exp.y" /* yacc.c:1646  */
    {(yyval.exp) = make_exp_and((yyvsp[-2].exp),(yyvsp[0].exp));}
#line 1552 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 135 "exp.y" /* yacc.c:1646  */
    {(yyval.exp) = make_exp_or((yyvsp[-2].exp),(yyvsp[0].exp));}
#line 1558 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 136 "exp.y" /* yacc.c:1646  */
    {(yyval.exp) = (yyvsp[-1].exp);}
#line 1564 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 137 "exp.y" /* yacc.c:1646  */
    { (yyval.exp) = make_exp_term((yyvsp[0].term)); }
#line 1570 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 140 "exp.y" /* yacc.c:1646  */
    { (yyval.type) = make_id_type((yyvsp[0].stringconst)); }
#line 1576 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 141 "exp.y" /* yacc.c:1646  */
    { (yyval.type) = make_int_type(); }
#line 1582 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 142 "exp.y" /* yacc.c:1646  */
    { (yyval.type) = make_bool_type(); }
#line 1588 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 143 "exp.y" /* yacc.c:1646  */
    { (yyval.type) = make_array_of_type((yyvsp[0].type)); }
#line 1594 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 144 "exp.y" /* yacc.c:1646  */
    { (yyval.type) = make_record_of_type((yyvsp[0].var_decl_list)); }
#line 1600 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 148 "exp.y" /* yacc.c:1646  */
    { (yyval.decl_list) = make_decl_list((yyvsp[-1].declaration), (yyvsp[0].decl_list));}
#line 1606 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 149 "exp.y" /* yacc.c:1646  */
    { (yyval.decl_list) = make_decl_list_empty(); }
#line 1612 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 152 "exp.y" /* yacc.c:1646  */
    { (yyval.par_decl_list) = make_par_decl_list((yyvsp[0].var_decl_list)); }
#line 1618 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 153 "exp.y" /* yacc.c:1646  */
    { (yyval.par_decl_list) =  make_par_decl_list_empty(); }
#line 1624 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 156 "exp.y" /* yacc.c:1646  */
    { (yyval.declaration) = make_declaration_id((yyvsp[-3].stringconst), (yyvsp[-1].type)); }
#line 1630 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 157 "exp.y" /* yacc.c:1646  */
    { (yyval.declaration) = make_declaration_function((yyvsp[0].function)); }
#line 1636 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 158 "exp.y" /* yacc.c:1646  */
    { (yyval.declaration) = make_declaration_var((yyvsp[-1].var_decl_list)); }
#line 1642 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 161 "exp.y" /* yacc.c:1646  */
    { (yyval.statement_list) = make_statement_empty_list((yyvsp[0].statement)); }
#line 1648 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 162 "exp.y" /* yacc.c:1646  */
    { (yyval.statement_list) = make_statement_list((yyvsp[-1].statement), (yyvsp[0].statement_list)); }
#line 1654 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 165 "exp.y" /* yacc.c:1646  */
    { (yyval.statement) = make_statement_return((yyvsp[-1].exp)); }
#line 1660 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 166 "exp.y" /* yacc.c:1646  */
    { (yyval.statement) = make_statement_write((yyvsp[-1].exp)); }
#line 1666 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 167 "exp.y" /* yacc.c:1646  */
    { (yyval.statement) = make_statement_allocate((yyvsp[-2].var), (yyvsp[-1].exp)); }
#line 1672 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 168 "exp.y" /* yacc.c:1646  */
    { (yyval.statement) = make_statement_assign((yyvsp[-3].var), (yyvsp[-1].exp)); }
#line 1678 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 169 "exp.y" /* yacc.c:1646  */
    { (yyval.statement) = make_statement_if((yyvsp[-3].exp), (yyvsp[-1].statement), (yyvsp[0].statement_else)); }
#line 1684 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 170 "exp.y" /* yacc.c:1646  */
    { (yyval.statement) = make_statement_while((yyvsp[-2].exp), (yyvsp[0].statement)); }
#line 1690 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 171 "exp.y" /* yacc.c:1646  */
    { (yyval.statement) = make_statement_while_list((yyvsp[-1].statement_list)); }
#line 1696 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 172 "exp.y" /* yacc.c:1646  */
    {(yyval.statement) = make_statement_for((yyvsp[-8].statement), (yyvsp[-7].exp), (yyvsp[-5].statement), (yyvsp[-1].statement));}
#line 1702 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 175 "exp.y" /* yacc.c:1646  */
    { (yyval.statement_else) = make_statement_else((yyvsp[0].statement)); }
#line 1708 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 176 "exp.y" /* yacc.c:1646  */
    { (yyval.statement_else) = make_statement_else_empty(); }
#line 1714 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 179 "exp.y" /* yacc.c:1646  */
    { (yyval.var_decl_list) = make_var_decl_list((yyvsp[-2].var_type), (yyvsp[0].var_decl_list)); }
#line 1720 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 180 "exp.y" /* yacc.c:1646  */
    { (yyval.var_decl_list) = make_var_decl_list_empty((yyvsp[0].var_type)); }
#line 1726 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 183 "exp.y" /* yacc.c:1646  */
    { (yyval.var_type) = make_var_type((yyvsp[-2].stringconst), (yyvsp[0].type)); }
#line 1732 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 186 "exp.y" /* yacc.c:1646  */
    { (yyval.var) = make_var_id((yyvsp[0].stringconst)); }
#line 1738 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 187 "exp.y" /* yacc.c:1646  */
    { (yyval.var) = make_var_array((yyvsp[-3].var), (yyvsp[-1].exp)); }
#line 1744 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 188 "exp.y" /* yacc.c:1646  */
    { (yyval.var) = make_var_record((yyvsp[-2].var), (yyvsp[0].stringconst)); }
#line 1750 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 191 "exp.y" /* yacc.c:1646  */
    { (yyval.term) = make_term_var((yyvsp[0].var)); }
#line 1756 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 192 "exp.y" /* yacc.c:1646  */
    { (yyval.term) = make_term_act_list((yyvsp[-3].stringconst), (yyvsp[-1].act_list)); }
#line 1762 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 193 "exp.y" /* yacc.c:1646  */
    { (yyval.term) = make_term_parentheses((yyvsp[-1].exp)); }
#line 1768 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 194 "exp.y" /* yacc.c:1646  */
    { (yyval.term) = make_term_not((yyvsp[0].term)); }
#line 1774 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 195 "exp.y" /* yacc.c:1646  */
    { (yyval.term) = make_term_absolute((yyvsp[-1].exp)); }
#line 1780 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 196 "exp.y" /* yacc.c:1646  */
    {(yyval.term) = make_term_uminus((yyvsp[0].term)); }
#line 1786 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 197 "exp.y" /* yacc.c:1646  */
    { (yyval.term) = make_term_num((yyvsp[0].intconst)); }
#line 1792 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 198 "exp.y" /* yacc.c:1646  */
    { (yyval.term) = make_term_true(); }
#line 1798 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 199 "exp.y" /* yacc.c:1646  */
    { (yyval.term) = make_term_false(); }
#line 1804 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 200 "exp.y" /* yacc.c:1646  */
    { (yyval.term) = make_term_null(); }
#line 1810 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 203 "exp.y" /* yacc.c:1646  */
    { (yyval.act_list) = make_act_list((yyvsp[0].exp_list)); }
#line 1816 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 204 "exp.y" /* yacc.c:1646  */
    { (yyval.act_list) = make_act_list_empty(); }
#line 1822 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 207 "exp.y" /* yacc.c:1646  */
    { (yyval.exp_list) = make_exp_list_expression((yyvsp[0].exp)); }
#line 1828 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 208 "exp.y" /* yacc.c:1646  */
    { (yyval.exp_list) = make_exp_list((yyvsp[-2].exp), (yyvsp[0].exp_list)); }
#line 1834 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1838 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 211 "exp.y" /* yacc.c:1906  */

