#ifndef __AST_H__
#define __AST_H__
#include "symbol.h"

typedef enum {
  AND, IARRAY, ARRAY, BLOCK, BOOL, CHAR, DISPOSE, DIV, BOOL_CONST, FORWARD, FUNCTION, GOTO, IF, INT, MOD, NEW, NIL, NOT, OR, PROCEDURE, PROGRAM, REAL_CONST, REAL, RESULT, RETURN, VAR, WHILE, ID, INT_CONST, STR_CONST, CHAR_CONST, NEQ, GEQ, LEQ, LESS, GREATER, EQ, PLUS, MINUS, TIMES, DIVIDE, DEREF, REF, SEQ_EXPR, SEQ_STMT, SEQ_ID, INDEX, POINTER, CALL, ASSIGN, STMT, DISPOSE_ARRAY, VARREF, SEQ_FORMAL, SEQ_LOCAL, DEFINITION, LOCAL_VAR, LOCAL_VAR_INSTANCE, SEQ_LOCAL_VAR, BODY, LABEL
} kind;

typedef struct node {
  kind k;
  char* id;
  char* str;
  int boolean;
  int integer;
  char character;
  long double real;
  int size;
  Type type;
  SymbolEntry *sentry;
  bool full;
  struct node *left, *mid, *right;
} ast;

ast* make_ast(kind k, char* id, char* str, int boolean, int integer, char character, long double real, int size, ast *left, ast *mid, ast *right);
ast* ast_op(ast *l, kind op, ast *r);
ast* ast_id(char* id);
ast* ast_begin(ast * l);
ast* ast_formal(kind k, ast * l, ast * r);
ast* ast_dispose(ast * l);
ast* ast_dispose_array(ast * l);
ast* ast_const(kind k, int boolean, int integer, char character, long double real, char* str);
ast* ast_forward(ast * l);
ast* ast_seq_expr(ast * l, ast * r);
ast* ast_seq_stmt(ast * l, ast * r);
ast* ast_seq_id(char * id, ast * r);
ast* ast_seq_formal(ast * l, ast * r);
ast* ast_goto(char * label);
ast* ast_if(ast * l, ast * mid, ast * r);
ast* ast_stmt(char * id, ast * l);
ast* ast_new(ast * l, ast * r); //l NULL for just pointer
ast* ast_program(char * id, ast * l);
ast* ast_result();
ast* ast_index(ast * l, ast * r);
ast* ast_return();
ast* ast_while(ast * l, ast * r);
ast* ast_call(char * id, ast * l);
ast* ast_assign(ast * l, ast * r);
ast* ast_type(kind k, int size, ast * l); //size -1 for incomplete
ast* ast_header(kind k, char * id, ast * l, ast * r);
ast* ast_local(kind k, ast * l, ast * r);
ast* ast_seq_local(kind k, ast * l, ast * r);
ast* ast_local_var_instance(ast * l, ast * r);
ast* ast_seq_local_var(ast * l, ast * r);
ast* ast_body(ast * l, ast * r);
void print_ast(ast * t);
#endif
