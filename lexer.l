%option noyywrap

%{
#include "parser.h"
#include "yyfunc.h"
void ERROR(char * s);
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

{L}({L}|{D}|_)* {return t_id;}

{D}+ {return t_int_const;}

{D}+\.{D}+([Ee][+-]?{D}+)? {return t_real_const;}

('[^\'\"\n]')|'(\\\\|\\n|\\t|\\r|\\0|\\'|\\\")' {return t_char_const;}

\"(([^\'\"])|\\\\|\\n|\\t|\\r|\\0|\\'|\\\")*\" {return t_string_const;} 

\(\*(((\*[^)])*)|([^*]*))*\*\) {return 10000;}

{W}+ {/* nothing */}

. {ERROR("illegal token");}

%%

void ERROR(char * s) {
  printf("%s\n", s);
}

void yyerror(const char *msg) {
    printf("%s\n", msg);
}
/*
int main () {
  int token;
  do {
    token = yylex();
    printf("token=%d, lexeme=\"%s\"\n", token, yytext);
  } while (token != 0);
}
*/
