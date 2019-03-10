%option noyywrap

%{
#define t_and 1000
#define t_array 1001
#define t_begin 1002
#define t_boolean 1003
#define t_char 1004
#define t_dispose 1005
#define t_div 1006
#define t_do 1007
#define t_else 1008
#define t_end 1009
#define t_false 1010
#define t_forward 1011
#define t_function 1012
#define t_goto 1013
#define t_if 1014
#define t_integer 1015
#define t_label 1016
#define t_mod 1017
#define t_new 1018
#define t_nil 1019
#define t_not 1020
#define t_of 1021
#define t_or 1022
#define t_procedure 1023
#define t_program 1024
#define t_real 1025
#define t_result 1026
#define t_return 1027
#define t_then 1028
#define t_true 1029
#define t_var 1030
#define t_while 1031
#define t_id 1032
#define t_real_const 1033
#define t_int_const 1034
#define t_char_const 1035
#define t_string_const 1036
#define t_neq 1037
#define t_geq 1038
#define t_leq 1039
#define t_assign 1040
#define t_eof 0

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

int main () {
  int token;
  do {
    token = yylex();
    printf("token=%d, lexeme=\"%s\"\n", token, yytext);
  } while (token != t_eof);
  return 0;
}
