%{
#include "yyfunc.h"
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

ast * t;

%}


%union{
  ast * a;
  char c;
  int n;
  char* s;
  long double r;
  kind k;
  }


%token t_and "and"
%token t_array "array"
%token t_begin "begin"
%token t_boolean "boolean"
%token t_char "char"
%token t_dispose "dispose"
%token t_div "div"
%token t_do "do"
%token t_else "else"
%token t_end "end"
%token t_false "false"
%token t_forward "forward"
%token t_function "function"
%token t_goto "goto"
%token t_if "if"
%token t_integer "integer"
%token t_label "label"
%token t_mod "mod"
%token t_new "new"
%token t_nil "nil"
%token t_not "not"
%token t_of "of"
%token t_or "or"
%token t_procedure "procedure"
%token t_program "program"
%token t_real "real"
%token t_result "result"
%token t_return "return"
%token t_then "then"
%token t_true "true"
%token t_var "var"
%token t_while "while"
%token<s> t_id
%token<r> t_real_const 
%token<n> t_int_const
%token<c> t_char_const
%token<s> t_string_const
%token t_neq "<>"
%token t_geq ">="
%token t_leq "<="
%token t_assign ":="


%left "<=" ">=" '<' '>' '=' "<>"
%left '+' '-' "or"
%left '*' '/' "div" "mod" "and"
%nonassoc '@' '^'
%left unary

%type<a> program
%type<a> body
%type<a> moreid
%type<a> localvar
%type<a> local
%type<a> header
%type<a> moreformal
%type<a> formal
%type<a> type
%type<a> morestmt
%type<a> stmt
%type<a> moreexpr
%type<a> expr
%type<a> lvalue
%type<a> rvalue
%type<a> call
%type<a> block
%type<k> unop
%%

program:
"program" t_id ';' body '.' {t = $$ = ast_program($2, $4);}
;


body:
block {$$ = ast_body(NULL, $1);}
| local body {$$ = ast_body($1, $2);}
;

moreid:
t_id {$$ = ast_seq_id($1, NULL);}
| t_id ',' moreid {$$ = ast_seq_id($1, $3);}
;


localvar:
moreid ':' type ';' {$$ = ast_seq_local_var(ast_local_var_instance($1, $3), NULL);}
| moreid ':' type ';' localvar {$$ = ast_seq_local_var(ast_local_var_instance($1, $3), $5);}
;

  
local: 
"var" localvar {$$ = ast_local(LOCAL_VAR, $2, NULL);}
| "label" moreid ';' {$$ = ast_local(LABEL, $2, NULL);}
| header ';' body ';' {$$ = ast_local(DEFINITION, $1, $3);}
| "forward" header ';' {$$ = ast_local(FORWARD, $2, NULL);}
;


header:
"procedure" t_id '(' ')' {$$ = ast_header(PROCEDURE, $2, NULL, NULL);}
| "procedure" t_id '(' moreformal ')' {$$ = ast_header(PROCEDURE, $2, $4, NULL);}
| "function" t_id '(' ')' ':' type {$$ = ast_header(FUNCTION, $2, NULL, $6);}
| "function" t_id '(' moreformal ')' ':' type {$$ = ast_header(FUNCTION, $2, $4, $7);}  
;


moreformal:
formal {$$ = ast_seq_formal($1, NULL);}
| formal ';' moreformal {$$ = ast_seq_formal($1, $3);}
;


formal:
"var" moreid ':' type {$$ = ast_formal(VARREF, $2, $4);}
| moreid ':' type {$$ = ast_formal(VAR, $1, $3);}
;


type:
"integer" {$$ = ast_type(INT, -1, NULL);}
| "real" {$$ = ast_type(REAL, -1, NULL);}
| "boolean" {$$ = ast_type(BOOL, -1, NULL);}
| "char" {$$ = ast_type(CHAR, -1, NULL);}
| "array" "of" type {$$ = ast_type(ARRAY, -1, $3);}
| "array" '[' t_int_const ']' "of" type {$$ = ast_type(ARRAY, $3, $6);}
| '^' type {$$ = ast_type(POINTER, -1, $2);}
;


block:
"begin" morestmt "end" {$$ = ast_begin($2);}
;


morestmt:
stmt {$$ = ast_seq_stmt($1, NULL);}
| stmt ';' morestmt {$$ = ast_seq_stmt($1, $3);}
;


stmt:
/* nothing */ {$$ = NULL;}
| lvalue ":=" expr {$$ = ast_assign($1, $3);}
| block {$$ = $1;}
| call {$$ = $1;}
| "if" expr "then" stmt {$$ = ast_if($2, $4, NULL);}
| "if" expr "then" stmt "else" stmt {$$ = ast_if($2, $4, $6);}
| "while" expr "do" stmt {$$ = ast_while($2, $4);}
| t_id ':' stmt {$$ = ast_stmt($1, $3);}
| "goto" t_id {$$ = ast_goto($2);}
| "return" {$$ = ast_return();}
| "new" lvalue {$$ = ast_new(NULL, $2);}
| "new" '[' expr ']' lvalue {$$ = ast_new($3, $5);}
| "dispose" lvalue {$$ = ast_dispose($2);}
| "dispose" '[' ']' lvalue {$$ = ast_dispose_array($4);} 
;


moreexpr:
expr {$$ = ast_seq_expr($1, NULL);}
| expr ',' moreexpr {$$ = ast_seq_expr($1, $3);}
;


expr:
lvalue {$$ = $1;}
| rvalue {$$ = $1;}
;


lvalue:
lvalue '[' expr ']' {$$ = ast_index($1, $3);}
| lvalue '^' {$$ = ast_op($1, REF, NULL);}
|  t_string_const {$$ = ast_const(STR_CONST, 0, 0, '\0', 0.0, $1);}
| '(' lvalue ')' {$$ = $2;}
| t_id {$$ = ast_id($1);}
| "result" {$$ = ast_result();}
;


rvalue:
t_int_const {$$ = ast_const(INT_CONST, 0, $1, '\0', 0.0, NULL);}
| "true" {$$ = ast_const(BOOL_CONST, 1, 0, '\0', 0.0, NULL);}
| "false" {$$ = ast_const(BOOL_CONST, 0, 0, '\0', 0.0, NULL);}
| t_real_const {$$ = ast_const(REAL_CONST, 0, 0, '\0', $1, NULL);}
| t_char_const {$$ = ast_const(CHAR_CONST, 0, 0, $1, 0.0, NULL);}
| '(' rvalue ')' {$$ = $2;}
| "nil" {$$ = ast_const(NIL, 0, 0, '\0', 0.0, NULL);}
| call {$$ = $1;}
| '@' lvalue {$$ = ast_op($2, DEREF, NULL);}
| unop expr %prec unary {$$ = ast_op($2, $1, NULL);}
| expr '+' expr {$$ = ast_op($1, PLUS, $3);}
| expr '-' expr {$$ = ast_op($1, MINUS, $3);}
| expr '*' expr {$$ = ast_op($1, TIMES, $3);}
| expr '/' expr {$$ = ast_op($1, DIVIDE, $3);}
| expr "div" expr {$$ = ast_op($1, DIV, $3);}
| expr "mod" expr {$$ = ast_op($1, MOD, $3);}
| expr "or" expr {$$ = ast_op($1, OR, $3);}
| expr "and" expr {$$ = ast_op($1, AND, $3);}
| expr '=' expr {$$ = ast_op($1, EQ, $3);}
| expr "<>" expr {$$ = ast_op($1, NEQ, $3);}
| expr '<' expr {$$ = ast_op($1, LESS, $3);}
| expr "<=" expr {$$ = ast_op($1, LEQ, $3);}
| expr '>' expr {$$ = ast_op($1, GREATER, $3);}
| expr ">=" expr {$$ = ast_op($1, GEQ, $3);} 
;


call:
t_id '(' ')' {$$ = ast_call($1, NULL);}
| t_id '(' moreexpr ')' {$$ = ast_call($1, $3);}
;


unop:
"not" {$$ = NOT;}
| '+' {$$ = PLUS;}
| '-' {$$ = MINUS;}
;

/*
binop:
  '+'
| '-'
| '*'
| '/'
| "div"
| "mod"
| "or"
| "and"
| '='
| "<>"
| '<'
| "<="
| '>'
| ">="
;
*/
%%

int main() {
  //printf("%lu\n", (long)t);
  int result = yyparse();
  //printf("%s\n", (char*)(t+4));
  //printf("etoimo\n");
  //printf("%lu\n", (long)t);
  if (result == 0) print_ast(t);
  return result;
}
