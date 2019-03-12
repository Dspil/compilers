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
%token t_id
%token t_real_const 
%token t_int_const
%token t_char_const
%token t_string_const
%token t_neq "<>"
%token t_geq ">="
%token t_leq "<="
%token t_assign ":="


%nonassoc "<=" ">=" '<' '>' '=' "<>"
%left '+' '-' "or"
%left '*' '/' "div" "mod" "and"
%nonassoc '@' '^'
%left unary


%%

program:
  "program" t_id ";" body "."
;


body:
  block
| local body
;


moreid:
  t_id
| t_id "," moreid
;


localvar:
  moreid ":" type ";"
| moreid ":" type ";" localvar
;

  
local: 
  "var" localvar
| "label" moreid ";"
| header ";" body ";"
| "forward" header ";"
;


header:
  "procedure" t_id "(" ")"
| "procedure" t_id "(" moreformal ")"
| "function" t_id "(" ")" ":" type
| "function" t_id "(" moreformal ")" ":" type
;


moreformal:
  formal
| formal ";" moreformal
;


formal:
  "var" moreid ":" type
| moreid ":" type
;


type:
  "integer"
| "real"
| "boolean"
| "char"
| "array" "of" type
| "array" "[" t_int_const "]" "of" type
| '^' type
;


block:
  "begin" morestmt "end"
;


morestmt:
  stmt
| stmt ";" morestmt
;


stmt:
| lvalue ":=" expr
| block
| call
| "if" expr "then" stmt
| "if" expr "then" stmt "else" stmt
| "while" expr "do" stmt
| t_id ":" stmt
| "goto" t_id
| "return"
| "new" lvalue
| "new" "[" expr "]" lvalue
| "dispose" lvalue
| "dispose" "[" "]" lvalue
;


moreexpr:
  expr
| expr "," moreexpr
;


expr:
  lvalue
| rvalue
;


lvalue:
  lvalue "[" expr "]"
| lvalue '^' 
|  t_string_const
| "(" lvalue ")"
| t_id
| "result"
;


rvalue:
  t_int_const
| "true"
| "false"
| t_real_const
| t_char_const
| "(" rvalue ")"
| "nil"
| call
| '@' lvalue
| unop expr %prec unary
| expr binop expr
;


call:
  t_id "(" ")"
| t_id "(" moreexpr ")"
;


unop:
  "not"
| '+'
| '-'
;


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

%%

int main() {
  int result = yyparse();
  if (result == 0) printf("Success.\n");
  return result;
}
