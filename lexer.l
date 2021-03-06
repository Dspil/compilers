%option noyywrap
%option nounput

%{
#include "ast_symbol.h"
#include "parser.hpp"
#include "yyfunc.h"
#include "error.h"
%}

L [a-zA-Z]
D [0-9]
W [ \t\r\n]

%%

"and" {return t_and;}
"array" {return t_array;}
"begin" {return t_begin;}
"boolean" {return t_boolean;}
"char" {return t_char;}
"dispose" {return t_dispose;}
"div" {return t_div;}
"do" {return t_do;}
"else" {return t_else;}
"end" {return t_end;}
"false" {return t_false;}
"forward" {return t_forward;}
"function" {return t_function;}
"goto" {return t_goto;}
"if" {return t_if;}
"integer" {return t_integer;}
"label" {return t_label;}
"mod" {return t_mod;}
"new" {return t_new;}
"nil" {return t_nil;}
"not" {return t_not;}
"of" {return t_of;}
"or" {return t_or;}
"procedure" {return t_procedure;}
"program" {return t_program;}
"real" {return t_real;}
"result" {return t_result;}
"return" {return t_return;}
"then" {return t_then;}
"true" {return t_true;}
"var" {return t_var;}
"while" {return t_while;}
">=" {return t_geq;}
"<=" {return t_leq;}
"<>" {return t_neq;}
":=" {return t_assign;}

[()=+\-*/%<>\[\];.:,^@]   {return yytext[0];}

{L}({L}|{D}|_)* {yylval.s = (char*)malloc(strlen(yytext)*sizeof(char)) ;strcpy(yylval.s, yytext); return t_id;}

{D}+ {yylval.n = atoi(yytext); return t_int_const;}

{D}+\.{D}+([Ee][+-]?{D}+)? {yylval.r = strtold(yytext, NULL); return t_real_const;}

('[^\'\"\n]')|'(\\\\|\\n|\\t|\\r|\\0|\\'|\\\")' {yylval.c = make_char(yytext); return t_char_const;}

\"(([^\'\"])|\\\\|\\n|\\t|\\r|\\0|\\'|\\\")*\" {yylval.s = (char*)malloc((strlen(yytext) - 2)*sizeof(char)); memcpy(yylval.s, yytext + 1, strlen(yytext) - 2); return t_string_const;}

\(\*(((\*[^)])*)|([^*]*))*\*\) {/* nothing */}

{W}+ {/* nothing */}

. {error("illegal token \"%s\"", yytext); return 1;}

%%

void yyerror(const char *msg) {
    error("%s", msg);
}
