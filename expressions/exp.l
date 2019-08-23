%{
#include "y.tab.h"
#include <string.h>

int comment = 0;
extern int lineno;
extern int fileno();
%}

%option noyywrap nounput noinput
%x multi_line_comments
DIGITS 0|([1-9][0-9]*)
IDENTIFIERS [a-zA-Z_][a-zA-Z0-9_]*

%%
[ \t]+        /* ignore whitespace */;
[ \r]          
\n              lineno++;

"#".* /*Single comment ignore*/

"(*"    {
        comment++;
        BEGIN(multi_line_comments);
        }
<multi_line_comments>"(*" {comment++;}
<multi_line_comments>\n {lineno++;}
<multi_line_comments>. ;
<multi_line_comments>"*)"   {
                                comment--;
                                if(comment == 0)
                                    BEGIN(INITIAL);
                            }
<multi_line_comments><<EOF>> {yy_fatal_error("comments missing a closing line statement");}

"*"             return '*';
"/"             return '/';
"+"             return '+';
"-"             return '-';
"="             return '=';
">"             return '>';
"<"             return '<';

"("             return '(';
")"             return ')';
"["             return '[';
"]"             return ']';
"{"             return '{';
"}"             return '}';
"|"             return '|';
";"             return ';';
":"             return ':';
","             return ',';
"."             return '.';
"!"             return '!';

"false"         return BOOL_FALSE;
"true"          return BOOL_TRUE;
"=="            return BOOL_EQUALS;
"!="            return BOOL_NOT_EQUALS;
"<="            return LESS_OR_EQUAL;
">="            return GREATER_OR_EQUAL;
"&&"            return AND;
"||"            return OR;

"func"          return FUNCTION_START;
"end"           return FUNCTION_END;
"id"            return ID_TOKEN;
"int"           return INT_TOKEN;
"bool"          return BOOL_TOKEN;
"array of"      return ARRAY_OF_TOKEN;
"record of"     return RECORD_OF_TOKEN;
"type"          return TYPE_TOKEN;
"var"           return VAR_TOKEN;
"return"        return RETURN_TOKEN;
"write"         return WRITE_TOKEN;
"allocate"      return ALLOCATE_TOKEN;
"of length"     return OF_LENGTH_TOKEN;
"if"            return IF_TOKEN;
"then"          return THEN_TOKEN;
"else"          return ELSE_TOKEN;
"while"         return WHILE_TOKEN;
"do"            return DO_TOKEN;
"null"          return NULL_TOKEN;
"for"           return FOR_TOKEN;

{DIGITS}        { yylval.intconst = atoi(yytext);
                       return INT_TOKEN; }
{IDENTIFIERS}	{ yylval.stringconst = (char *)malloc(strlen(yytext)+1);
                         sprintf(yylval.stringconst,"%s",yytext);
                         return ID_TOKEN; }
.               { yy_fatal_error("invalid token parsed");}/* throw error if we see an invalid token */;
%%
