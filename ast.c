#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

ast make_ast(kind k, char* id, char* str, int boolean, int integer, char character, long double real, int size, ast *left, ast *mid, ast *right) {
  ast * node;
  if ((node = (ast*)malloc(sizeof(ast))) == NULL) {
    return NULL;
  }
  node->left = l;
  node->k = k;
  node->right = r;
  node->mid = mid;
  node->real = real;
  node->integer = integer;
  node->boolean = boolean;
  node->character = character;
  node->size = size;
  if (id) {
    node->id = (char*)malloc(strlen(id)*sizeof(char));
    strcpy(node->id, id);
  }
  if (str) {
    node->str = (char*)malloc(strlen(str)*sizeof(char));
    strcpy(node->str, str);
  }
  return node;
}


ast * ast_op(ast * l, kind op, ast * r) {
  return make_ast(op, NULL, NULL, 0, 0, '\0', 0, 0, l, NULL, r);
}


ast * ast_begin(ast * l) {
  return make_ast(BEGIN, NULL, NULL, 0, 0, '\0', 0, 0, l, NULL, NULL);
}


ast * ast_formal(kind k, ast * l, ast * r) {
  return make_ast(k, NULL, NULL, 0, 0, '\0', 0, 0, l, NULL, r);
}


ast * ast_dispose(ast * l) {
  return make_ast(DISPOSE, NULL, NULL, 0, 0, '\0', 0, 0, l, NULL, NULL);
}


ast * ast_dispose_array(ast * l) {
  return make_ast(DISPOSE_ARRAY, NULL, NULL, 0, 0, '\0', 0, 0, l, NULL, NULL);
}


ast * ast_const(kind k, int boolean, int integer, char character, long double real, char* str) {
  return make_ast(k, NULL, str, boolean, integer, character, real, 0, NULL, NULL, NULL);
}


ast * ast_forward(ast * l) {
  return make_ast(FORWARD, NULL, NULL, 0, 0, '\0', 0, 0, l, NULL, NULL);
}


ast* ast_seq_expr(ast * l, ast * r) {
  return make_ast(SEQ_EXPR, NULL, NULL, 0, 0, '\0', 0, 0, l, NULL, r);
}


ast* ast_seq_stmt(ast * l, ast * r) {
  return make_ast(SEQ_STMT, NULL, NULL, 0, 0, '\0', 0, 0, l, NULL, r);
}


ast* ast_seq_id(char * id, ast * r) {
  return make_ast(SEQ_ID, id, NULL, 0, 0, '\0', 0, 0, NULL, NULL, r);
}


ast* ast_seq_formal(ast * l, ast * r) {
  return make_ast(SEQ_FORMAL, NULL, NULL, 0, 0, '\0', 0, 0, l, NULL, r);
}


ast * ast_goto(char * label) {
  return make_ast(GOTO, NULL, label, 0, 0, '\0', 0, 0, NULL, NULL, NULL);
}


ast * ast_if(ast * l, ast * mid, ast * r) {
  return make_ast(IF, NULL, NULL, 0, 0, '\0', 0, 0, l, mid, r);
}


ast * ast_stmt(char * id, ast * l) {
  return make_ast(STMT, id, NULL, 0, 0, '\0', 0, 0, l, NULL, NULL);
}


ast * ast_new(ast * l, ast * r) { //l NULL for just pointer
  return make_ast(NEW, NULL, NULL, 0, 0, '\0', 0, 0, l, NULL, r);
}


ast * ast_program(char * id, ast * l) {
  return make_ast(PROGRAM, id, NULL, 0, 0, '\0', 0, 0, l, NULL, NULL);
}


ast * ast_result() {
  return make_ast(RESULT, NULL, NULL, 0, 0, '\0', 0, 0, NULL, NULL, NULL);
}


ast * ast_index(ast * l, ast * r) {
  return make_ast(INDEX, NULL, NULL, 0, 0, '\0', 0, 0, l, NULL, r);
}


ast * ast_return() {
  return make_ast(RETURN, NULL, NULL, 0, 0, '\0', 0, 0, NULL, NULL, NULL);
}


ast * ast_while(ast * l, ast * r) {
  return make_ast(WHILE, NULL, NULL, 0, 0, '\0', 0, 0, l, NULL, r);
}


ast * ast_assign(char * id, ast * l) {
  return make_ast(ASSIGN, id, NULL, 0, 0, '\0', 0, 0, l, NULL, NULL);
}


ast * ast_call(ast * l, ast * r) {
  return make_ast(CALL, NULL, NULL, 0, 0, '\0', 0, 0, l, NULL, r);
}


ast * ast_type(kind k, int size, ast * l) {
  return make_ast(k, NULL, NULL, 0, 0, '\0', 0, size, l, NULL, NULL);
}


ast* ast_header(kind k, char * id, ast * l, ast * r) {
  return make_ast(k, id, NULL, 0, 0, '\0', 0, 0, l, NULL, r);
}


ast* ast_local(kind k, ast * l, ast * r) {
  return make_ast(k, NULL, NULL, 0, 0, '\0', 0, 0, l, NULL, r);
}


ast* ast_local_var_instance(ast * l, ast * r) {
  return make_ast(LOCAL_VAR_INSTANCE, NULL, NULL, 0, 0, '\0', 0, 0, l, NULL, r);
}


ast* ast_seq_local_var(ast * l, ast * r) {
  return make_ast(SEQ_LOCAL_VAR, NULL, NULL, 0, 0, '\0', 0, 0, l, NULL, r);
}


ast* ast_body(ast * l, ast * r) {
  return make_ast(BODY, NULL, NULL, 0, 0, '\0', 0, 0, l, NULL, r);
}
