#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symbol.h"


char * table[] =  {"AND", "IARRAY", "ARRAY", "BLOCK", "BOOL", "CHAR", "DISPOSE", "DIV", "BOOL_CONST", "FORWARD", "FUNCTION", "GOTO", "IF", "INT", "MOD", "NEW", "NIL", "NOT", "OR", "PROCEDURE", "PROGRAM", "REAL_CONST", "REAL", "RESULT", "RETURN", "VAR", "WHILE", "ID", "INT_CONST", "STR_CONST", "CHAR_CONST", "NEQ", "GEQ", "LEQ", "LESS", "GREATER", "EQ", "PLUS", "MINUS", "TIMES", "DIVIDE", "DEREF", "REF", "SEQ_EXPR", "SEQ_STMT", "SEQ_ID", "INDEX", "POINTER", "CALL", "ASSIGN", "STMT", "DISPOSE_ARRAY", "VARREF", "SEQ_FORMAL", "SEQ_LOCAL", "DEFINITION", "LOCAL_VAR", "LOCAL_VAR_INSTANCE", "SEQ_LOCAL_VAR", "BODY", "LABEL"};

ast* make_ast(kind k, char* id, char* str, int boolean, int integer, char character, long double real, int size, ast *left, ast *mid, ast *right) {
  ast * node;
  if ((node = (ast*)malloc(sizeof(ast))) == NULL) {
    exit(1);
  }
  node->left = left;
  node->k = k;
  node->right = right;
  node->mid = mid;
  node->real = real;
  node->integer = integer;
  node->boolean = boolean;
  node->character = character;
  node->size = size;
  node->id = id;
  node->str = str;
  node->type = NULL;
  node->sentry = NULL;
  node->full = true;
  return node;
}


ast * ast_op(ast * l, kind op, ast * r) {
  return make_ast(op, NULL, NULL, 0, 0, '\0', 0, 0, l, NULL, r);
}


ast * ast_begin(ast * l) {
  return make_ast(BLOCK, NULL, NULL, 0, 0, '\0', 0, 0, l, NULL, NULL);
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


ast * ast_assign(ast * l, ast * r) {
  return make_ast(ASSIGN, NULL, NULL, 0, 0, '\0', 0, 0, l, NULL, r);
}


ast * ast_call(char * id, ast * l) {
  return make_ast(CALL, id, NULL, 0, 0, '\0', 0, 0, l, NULL, NULL);
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

ast* ast_seq_local(kind k, ast * l, ast * r) {
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

ast* ast_id(char* id) {
   return make_ast(ID, id, NULL, 0, 0, '\0', 0, 0, NULL, NULL, NULL);
}


/* PRINT AST */


void print_ast(ast * t) {
  ast * head;
  if (!t) {
    return;
  }
  switch (t->k) {

  case AND:
    printf("AND(");
    print_ast(t->left);
    printf(", ");
    print_ast(t->right);
    printf(")");
    break;

  case IARRAY:
    printf("IARRAY_OF(");
    print_ast(t->left);
    printf(")");
    break;

  case ARRAY:
    if (t->size > 0) {
      printf("array[%d] of (", t->size);
      print_ast(t->left);
      printf(")");
    }
    else {
      return;
    }
    break;

  case BLOCK:
    printf("BLOCK(");
    print_ast(t->left);
    printf(")");
    break;

  case BOOL:
    printf("BOOL");
    break;

  case CHAR:
    printf("CHAR");
    break;

  case DISPOSE:
    printf("DISPOSE(");
    print_ast(t->left);
    break;

  case DIV:
    printf("DIV(");
    print_ast(t->left);
    printf(", ");
    print_ast(t->right);
    printf(")");
    break;

  case BOOL_CONST:
    printf("%s", t->boolean ? "true" : "false");
    break;

  case FORWARD:
    printf("FORWARD(");
    print_ast(t->left);
    printf(")");
    break;

  case GOTO:
    printf("GOTO(%s)", t->id);
    break;

  case IF:
    printf("IF(");
    print_ast(t->left);
    printf(", ");
    print_ast(t->mid);
    printf(",");
    print_ast(t->right);
    printf(")");
    break;

  case INT:
    printf("INT");
    break;

  case MOD:
    printf("MOD(");
    print_ast(t->left);
    printf(", ");
    print_ast(t->right);
    printf(")");
    break;

  case NEW:
    printf("NEW(");
    print_ast(t->right);
    printf(")");
    break;

  case NIL:
    printf("NIL");
    break;

  case NOT:
    printf("NOT(");
    print_ast(t->left);
    printf(")");
    break;

  case OR:
    printf("OR(");
    print_ast(t->left);
    printf(", ");
    print_ast(t->right);
    printf(")");
    break;

  case PROCEDURE:
    printf("PROCEDURE(%s", t->id);
    if (t->left) {
      printf(", ");
      print_ast(t->left);
    }
    printf(")");
    break;

  case PROGRAM:
    printf("PROGRAM(%s, ", t->id);
    print_ast(t->left);
    printf(")\n");
    break;

  case REAL_CONST:
    printf("%Lf",t->real);
    break;

  case REAL:
    printf("REAL");
    break;

  case RESULT:
    printf("RESULT");
    break;

  case RETURN:
    printf("RETURN");
    break;

  case VAR:
    printf("BY_VALUE(");
    print_ast(t->left);
    printf(", ");
    print_ast(t->right);
    printf(")");
    break;

  case WHILE:
    printf("WHILE(");
    print_ast(t->left);
    printf(", ");
    print_ast(t->right);
    printf(")");
    break;

  case INT_CONST:
    printf("%d", t->integer);
    break;

  case STR_CONST:
    printf("%s", t->str);
    break;

  case CHAR_CONST:
    printf("%c", t->character);
    break;

  case NEQ:
    printf("NEQ(");
    print_ast(t->left);
    printf(", ");
    print_ast(t->right);
    printf(")");
    break;

  case GEQ:
    printf("GEQ(");
    print_ast(t->left);
    printf(", ");
    print_ast(t->right);
    printf(")");
    break;

  case LEQ:
    printf("LEQ(");
    print_ast(t->left);
    printf(", ");
    print_ast(t->right);
    printf(")");
    break;

  case LESS:
    printf("LESS(");
    print_ast(t->left);
    printf(", ");
    print_ast(t->right);
    printf(")");
    break;

  case GREATER:
    printf("GREATER(");
    print_ast(t->left);
    printf(", ");
    print_ast(t->right);
    printf(")");
    break;

  case EQ:
    printf("EQ(");
    print_ast(t->left);
    printf(", ");
    print_ast(t->right);
    printf(")");
    break;

  case PLUS:
    if (t->right) {
      printf("PLUS(");
      print_ast(t->left);
      printf(", ");
      print_ast(t->right);
    }
    else {
      printf("PLUS(");
      print_ast(t->left);
    }
    printf(")");
    break;

  case MINUS:
    if (t->right) {
      printf("MINUS(");
      print_ast(t->left);
      printf(", ");
      print_ast(t->right);
    }
    else {
      printf("MINUS(");
      print_ast(t->left);
    }
    printf(")");
    break;

  case TIMES:
    printf("TIMES(");
    print_ast(t->left);
    printf(", ");
    print_ast(t->right);
    printf(")");
    break;

  case DIVIDE:
    printf("DIVIDE(");
    print_ast(t->left);
    printf(", ");
    print_ast(t->right);
    printf(")");
    break;

  case DEREF:
    printf("DEREF(");
    print_ast(t->left);
    printf(")");
    break;

  case REF:
    printf("REF(");
    print_ast(t->left);
    printf(")");
    break;

  case SEQ_EXPR:
    printf("SEQ_EXPR(");
    print_ast(t->left);
    head = t->right;
    while(head && head->left){
      printf(",");
      print_ast(head->left);
      head = head->right;
    }
    printf(")");
    break;

  case SEQ_STMT:
    printf("SEQ_STMT(");
    print_ast(t->left);
    head = t->right;
    while(head && head->left) {
      printf(",");
      print_ast(head->left);
      head = head->right;
    }
    printf(")");
    break;

  case ID:
    printf("ID(%s)", t->id);
    break;

  case SEQ_ID:
    printf("SEQ_ID(");
    printf("%s", t->id);
    head = t->right;
    while(head != NULL) {
      printf(",");
      printf("%s", head->id);
      head = head->right;
    }
    printf(")");
    break;

  case INDEX:
    print_ast(t->left);
    printf("[");
    print_ast(t->right);
    printf("]");
    break;

  case CALL:
    printf("%s(", t->id);
    if (t->left) {
      print_ast(t->left);
    }
    printf(")");
    break;

  case LABEL:
    printf("LABEL(");
    print_ast(t->left);
    printf(")");
    break;

  case BODY:
    printf("BODY(");
    if (t->left) {
      print_ast(t->left);
      printf(",");
    }
    print_ast(t->right);
    printf(")");
    break;

  case SEQ_LOCAL:
    printf("SEQ_LOCAL(");
    print_ast(t->left);
    head = t->right;
    while(head != NULL) {
      printf(",");
      print_ast(head->left);
      head = head->right;
    }
    printf(")");
    break;

  case SEQ_LOCAL_VAR:
    printf("SEQ_LOCAL_VAR(");
    print_ast(t->left);
    head = t->right;
    while(head != NULL) {
      printf(",");
      print_ast(head->left);
      head = head->right;
    }
    printf(")");
    break;

  case LOCAL_VAR_INSTANCE:
    printf("LOCAL_VAR_INSTANCE(");
    print_ast(t->left);
    printf(": ");
    print_ast(t->right);
    printf(")");
    break;

  case LOCAL_VAR:
    printf("VAR(");
    print_ast(t->left);
    head = t->right;
    while(head != NULL) {
      printf(",");
      print_ast(head->left);
      head = head->right;
    }
    printf(")");
    break;

  case DEFINITION:
    printf("DEFINITION(HEADER(");
    print_ast(t->left);
    printf(")(");
    print_ast(t->right);
    printf("))");
    break;

  case SEQ_FORMAL:
    printf("SEQ_FORMAL(");
    print_ast(t->left);
    head = t->right;
    while(head != NULL) {
      printf(",");
      print_ast(head->left);
      head = head->right;
    }
    printf(")");
    break;

  case VARREF:
    printf("VARREF(");
    print_ast(t->left);
    printf(" : ");
    print_ast(t->right);
    printf(")");
    break;

  case STMT:
    printf("STMT_WITH_LABEL(%s, ", t->id);
    print_ast(t->left);
    printf(")");
    break;

  case DISPOSE_ARRAY:
    printf("DISPOSE_ARRAY(");
    print_ast(t->left);
    printf(")");
    break;

  case ASSIGN:
    printf("ASSIGN(%s,", t->left->id);
    print_ast(t->right);
    printf(")");
    break;
  default:;
  }
}

void define_builtins() {
  SymbolEntry * p;

  p = newFunction("writeInteger");
  openScope();
  newParameter("n", typeInteger, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeVoid);
  closeScope();

  p = newFunction("writeBoolean");
  openScope();
  newParameter("b", typeBoolean, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeVoid);
  closeScope();

  p = newFunction("writeChar");
  openScope();
  newParameter("c", typeChar, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeVoid);
  closeScope();

  p = newFunction("writeReal");
  openScope();
  newParameter("r", typeReal, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeVoid);
  closeScope();

  p = newFunction("writeString");
  openScope();
  newParameter("s", typeIArray(typeChar), PASS_BY_REFERENCE, p);
  endFunctionHeader(p, typeVoid);
  closeScope();

  p = newFunction("abs");
  openScope();
  newParameter("n", typeInteger, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeInteger);
  closeScope();

  p = newFunction("fabs");
  openScope();
  newParameter("r", typeReal, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeReal);
  closeScope();

  p = newFunction("sqrt");
  openScope();
  newParameter("r", typeReal, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeReal);
  closeScope();

  p = newFunction("sin");
  openScope();
  newParameter("r", typeReal, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeReal);
  closeScope();

  p = newFunction("cos");
  openScope();
  newParameter("r", typeReal, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeReal);
  closeScope();

  p = newFunction("tan");
  openScope();
  newParameter("r", typeReal, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeReal);
  closeScope();

  p = newFunction("arctan");
  openScope();
  newParameter("r", typeReal, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeReal);
  closeScope();

  p = newFunction("exp");
  openScope();
  newParameter("r", typeReal, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeReal);
  closeScope();

  p = newFunction("ln");
  openScope();
  newParameter("r", typeReal, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeReal);
  closeScope();

  p = newFunction("pi");
  openScope();
  endFunctionHeader(p, typeReal);
  closeScope();

  p = newFunction("trunc");
  openScope();
  newParameter("r", typeReal, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeInteger);
  closeScope();

  p = newFunction("round");
  openScope();
  newParameter("r", typeReal, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeInteger);
  closeScope();

  p = newFunction("ord");
  openScope();
  newParameter("c", typeChar, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeInteger);
  closeScope();

  p = newFunction("chr");
  openScope();
  newParameter("n", typeInteger, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeChar);
  closeScope();

  p = newFunction("readInteger");
  openScope();
  endFunctionHeader(p, typeInteger);
  closeScope();

  p = newFunction("readBoolean");
  openScope();
  endFunctionHeader(p, typeBoolean);
  closeScope();

  p = newFunction("readChar");
  openScope();
  endFunctionHeader(p, typeChar);
  closeScope();

  p = newFunction("readReal");
  openScope();
  endFunctionHeader(p, typeReal);
  closeScope();

  p = newFunction("readString");
  openScope();
  newParameter("size", typeInteger, PASS_BY_VALUE, p);
  newParameter("s", typeIArray(typeChar), PASS_BY_REFERENCE, p);
  endFunctionHeader(p, typeVoid);
  closeScope();
}

int type_check(ast * t, Type ftype) {
  SymbolEntry *p, *p1;
  ast *head, *head1;
  Type tp;
  int pass_type;
  if (!t) {
    return 1;
  }
  switch (t->k) {

  case AND:
  case OR:
    if (type_check(t->left, ftype) || type_check(t->right, ftype)) return 1;
    if (t->left->type->kind == TYPE_BOOLEAN && t->right->type->kind == TYPE_BOOLEAN) t->type = typeBoolean;
    else {
      if (t->k == AND)
        printf("Type error: \"and\" arguments must be boolean!\n");
      else
        printf("Type error: \"or\" arguments must be boolean!\n");
      return 1;
    }
    break;

  case IARRAY:
    if (type_check(t->left, ftype)) return 1;
    t->type = typeIArray(t->left->type);
    t->full = false;
    break;

  case ARRAY:
    if (type_check(t->left, ftype)) return 1;
    if (t->size > 0) t->type = typeArray(t->size, t->left->type);
    else {
      printf("Type error: size of array must be positive!\n");
      return 1;
    }
    t->full = t->left->full;
    break;

  case BLOCK:
    if (type_check(t->left, ftype)) {
      return 1;
    }
    t->type = NULL;
    break;

  case BODY:
    if (t->left && type_check(t->left, ftype)) return 1;
    if (type_check(t->right, ftype)){
      return 1;
    }
    break;

  case BOOL:
  case BOOL_CONST:
    t->type = typeBoolean;
    break;

  case CHAR:
  case CHAR_CONST:
    t->type = typeChar;
    break;

  case DISPOSE:
    if (type_check(t->left, ftype)) return 1;
    if (t->left->type->kind != TYPE_POINTER) {
      printf("Type error: \"dispose\" argument must be pointer!\n");
      return 1;
    }
    break;

  case DIV:
  case MOD:
    if (type_check(t->left, ftype) || type_check(t->right, ftype)) return 1;
    if (t->left->type->kind == TYPE_INTEGER && t->right->type->kind == TYPE_INTEGER) t->type = typeInteger;
    else {
      if (t->k == DIV)
        printf("Type error: \"div\" arguments must be integers!\n");
      else
        printf("Type error: \"mod\" arguments must be integers!\n");
      return 1;
    }
    break;

  case FORWARD:
    if (type_check(t->left, ftype)) return 1;
    forwardFunction(t->left->sentry);
    if (lookupEntry(t->left->sentry->id, LOOKUP_CURRENT_SCOPE, false)) {
      printf("Error (forward): function %s already exists!\n", t->left->sentry->id);
      return 1;
    }
    break;

  case GOTO:
    if (!lookupEntry(t->str, LOOKUP_CURRENT_SCOPE, true)){
      printf("Error (goto): Undefined label %s\n", t->str);
      return 1;
    }
    t->type = NULL;
    break;

  case IF:
    if (type_check(t->left, ftype) || type_check(t->mid, ftype) || (t->right && type_check(t->right, ftype))) return 1;
    if (!(t->left->type->kind == TYPE_BOOLEAN)){
      printf("Type Error: if condition must be boolean!\n");
      return 1;
    }
    break;

  case INT:
  case INT_CONST:
    t->type = typeInteger;
    break;

  case NEW:
    if (!t->left) {
      if (type_check(t->right, ftype)) return 1;
      if (t->right->type->kind != TYPE_POINTER || (!t->right->full)){
        printf("Type Error: \"new\" argument must be full type and pointer!\n");
        return 1;
      }
    }
    else {
      if (type_check(t->left, ftype) || type_check(t->right, ftype)) return 1;
      if (t->left->type->kind != TYPE_INTEGER){
        printf("Type Error: \"new\" size must be integer!\n");
        return 1;
      }
      if (t->right->type->kind != TYPE_POINTER  || (t->right->type->refType->kind != TYPE_ARRAY && t->left->type->refType->kind != TYPE_IARRAY) || (!t->right->full)){
        printf("Type Error: \"new\" argument must be pointer to array of a full type!\n");
        return 1;
      }
    }
    break;

  case NIL:
    t->type = typePointer(NULL);
    break;

  case NOT:
    if (type_check(t->left, ftype)) return 1;
    if (!(t->left->type->kind == TYPE_BOOLEAN)) {
      printf("Type Error: \"not\" argument must be boolean!\n");
      return 1;
    }
    t->type = typeBoolean;
    break;

  case PROCEDURE:
    t->sentry = newFunction(t->id);
    openScope();
    if (t->left) { //t->left : seq_formal (parameters)
      if (type_check(t->left, ftype)) return 1;
      head = t->left; //seq_formal
      while (head) {
        tp = head->left->right->type;
        pass_type = head->left->k == VARREF ? PASS_BY_REFERENCE : PASS_BY_VALUE;
        head1 = head->left->left;
      	while (head1) {
      	  newParameter(head1->id, tp, pass_type, t->sentry);
      	  head1 = head1->right;
      	}
        head = head->right;
      }
    }
    t->type = typeVoid;
    endFunctionHeader(t->sentry, t->type);
    break;

  case FUNCTION:
    t->sentry = newFunction(t->id);
    openScope();
    if (t->left) { //t->left : seq_formal (parameters)
      if (type_check(t->left, ftype)) return 1;
      head = t->left; //seq_formal
      while (head) {
        tp = head->left->right->type;
      	pass_type = head->left->k == VARREF ? PASS_BY_REFERENCE : PASS_BY_VALUE;
      	head1 = head->left->left;
      	while (head1) {
      	  newParameter(head1->id, tp, pass_type, t->sentry);
      	  head1 = head1->right;
      	}
      	head = head->right;
      }
    }
    if (type_check(t->right, ftype)) {
      return 1;
    }
    t->type = t->right->type;
    endFunctionHeader(t->sentry, t->type);
    break;

  case PROGRAM:
    openScope();
    define_builtins();
    if (type_check(t->left, ftype)) {
      return 1;
    }
    closeScope();
    break;

  case REAL:
  case REAL_CONST:
    t->type = typeReal;
    break;

  case RESULT:
    if (!ftype || ftype->kind == TYPE_VOID){
      printf("Error (result): \"result\" variable can only exist in function body!\n");
      return 1;
    }
    if(lookupEntry("result", LOOKUP_CURRENT_SCOPE, false)) t->type = ftype;
    else t->type = typeVoid;
    break;

  case VAR:
    if (type_check(t->right, ftype)) return 1;
    break;

  case WHILE:
    if (type_check(t->left, ftype) || type_check(t->right, ftype)) return 1;
    if (!(t->left->type->kind == TYPE_BOOLEAN)){
      printf("Type Error: \"while\" condition must be boolean!\n");
      return 1;
    }
    break;

  case STR_CONST:
    t->type = typeArray(strlen(t->str), typeChar);
    break;

  case NEQ:
  case EQ:
    if (type_check(t->left, ftype) || type_check(t->right, ftype)) return 1;
    if (!((t->left->type->kind == TYPE_INTEGER || t->left->type->kind == TYPE_REAL) && (t->right->type->kind == TYPE_INTEGER || t->right->type->kind == TYPE_REAL)) && (t->left->type->kind != t->right->type->kind)){
      if (t->k == NEQ)
        printf("Type Error: \"<>\" arguments must be of equal type or arithmetic!\n");
      else
        printf("Type Error: \"=\" arguments must be of equal type or arithmetic!\n");
      return 1;
    }
    t->type = typeBoolean;
    break;

  case GEQ:
  case LEQ:
  case LESS:
  case GREATER:
    if (type_check(t->left, ftype) || type_check(t->right, ftype)) return 1;
    if (!(t->left->type->kind == TYPE_INTEGER || t->left->type->kind == TYPE_REAL) || !(t->right->type->kind == TYPE_INTEGER || t->right->type->kind == TYPE_REAL)) {
      if (t->k == GEQ)
        printf("Type Error: \">=\" arguments must be arithmetic!\n");
      else if (t->k == LEQ)
        printf("Type Error: \"<=\" arguments must be arithmetic!\n");
      else if (t->k == LESS)
        printf("Type Error: \"<\" arguments must be arithmetic!\n");
      else
        printf("Type Error: \">\" arguments must be arithmetic!\n");
      return 1;
    }
    t->type = typeBoolean;
    break;

  case PLUS:
  case MINUS:
  case TIMES:
    if (type_check(t->left, ftype) || type_check(t->right, ftype)) return 1;
    if (t->left->type->kind == TYPE_INTEGER && t->right->type->kind == TYPE_INTEGER) t->type = typeInteger;
    else if (t->left->type->kind == TYPE_INTEGER && t->right->type->kind == TYPE_REAL) t->type = typeReal;
    else if (t->left->type->kind == TYPE_REAL && t->right->type->kind == TYPE_INTEGER) t->type = typeReal;
    else if (t->left->type->kind == TYPE_REAL && t->right->type->kind == TYPE_REAL) t->type = typeReal;
    else {
      if (t->k == PLUS)
        printf("Type Error: \"+\" arguments must be arithmetic!\n");
      else if (t->k == MINUS)
        printf("Type Error: \"-\" arguments must be arithmetic!\n");
      else
        printf("Type Error: \"<\" arguments must be arithmetic!\n");
      return 1;
    }
    break;

  case DIVIDE:
    if (type_check(t->left, ftype) || type_check(t->right, ftype)) return 1;
    if ((t->left->type->kind == TYPE_INTEGER || t->left->type->kind == TYPE_REAL) && (t->right->type->kind == TYPE_INTEGER || t->right->type->kind == TYPE_REAL)) t->type = typeReal;
    else {
      printf("Type Error: \"/\" arguments must be arithmetic!\n");
      return 1;
    }
    break;

  case DEREF:
    if (type_check(t->left, ftype)) return 1;
    if (t->left->type) t->type = typePointer(t->left->type);
    else {
      printf("Type Error: \"@\" argument must pointer!\n");
      return 1;
    }
    break;

  case REF:
    if (type_check(t->left, ftype)) return 1;
    if (t->left->type->kind == TYPE_POINTER) t->type = t->left->type->refType;
    else {
      printf("Type Error: \"^\" argument must be pointer!\n");
      return 1;
    }
    break;

  case SEQ_EXPR:
  case SEQ_STMT:
    head = t;
    while (head) {
      if (head->left && type_check(head->left, ftype)) {
        return 1;
      }
      head = head->right;
    }
    break;

  case STMT:
    if (!(p = lookupEntry(t->id, LOOKUP_CURRENT_SCOPE, true))){
      printf("Error (label): label %s does not exist!\n", t->id);
      return 1;
    }
    if (p->u.eVariable.type->kind != TYPE_LABEL) {
      printf("Error (label): label %s does not exist!\n", t->id);
      return 1;
    }
    if (type_check(t->right, ftype)) {
      return 1;
    }
    break;

  case INDEX:
    if (type_check(t->left, ftype) || type_check(t->right, ftype)) return 1;
    if ((t->left->type->kind == TYPE_ARRAY || t->left->type->kind == TYPE_IARRAY) && t->right->type->kind == TYPE_INTEGER) t->type = t->left->type->refType;
    else {
      printf("Type Error: Can only index an array and index must be integer!\n");
      return 1;
    }
    break;

  case CALL:
    if (t->left && type_check(t->left, ftype)) return 1;
    if (!(p = lookupEntry(t->id, LOOKUP_ALL_SCOPES, true))){
      printf("Error (call function): function %s undeclared!\n", t->id);
      return 1;
    }
    if (p->entryType != ENTRY_FUNCTION){
      printf("Error (call function): function %s undeclared!\n", t->id);
      return 1;
    }
    p1 = p->u.eFunction.firstArgument;
    head = t->left;
    while (head) {
      if (!p1) {
        printf("Error (call function): more arguments given to function %s than needed!\n", t->id);
        return 1;
      }
      if (p1->u.eParameter.type->kind == TYPE_IARRAY &&
	    (head->left->type->kind == TYPE_ARRAY ||
	     head->left->type->kind == TYPE_IARRAY)) {
	        if (!equalType(head->left->type->refType, p1->u.eParameter.type->refType)) {
	           printf("Error (call function): argument type mismatch to function %s!\n", t->id);
	           return 1;
	        }
      }
      else if (!equalType(head->left->type, p1->u.eParameter.type)) {
	       printf("Error (call function): argument type mismatch to function %s!\n", t->id);
	       return 1;
      }
      head = head->right;
      p1 = p1->u.eParameter.next;
    }
    if (p1) {
      printf("Error (call function): less arguments given to function %s than needed!\n", t->id);
      return 1;
    }
    t->type = p->u.eFunction.resultType;
    break;

  case SEQ_LOCAL:
    head = t;
    while (head) {
      if (type_check(head->left, ftype)) return 1;
      head = head->right;
    }
    break;

  case SEQ_LOCAL_VAR:
    head = t;
    while (head) {
      if (type_check(head->left, ftype)) return 1;
      head = head->right;
    }
    break;

  case LOCAL_VAR_INSTANCE:
    if (type_check(t->right, ftype)) return 1;
    tp = t->right->type;
    head = t->left;
    while (head) {
      newVariable(head->id, tp);
      head = head->right;
    }
    break;

  case LOCAL_VAR:
    if (type_check(t->left, ftype)) return 1;
    break;

  case DEFINITION:
    if (type_check(t->left, ftype) || type_check(t->right, t->left->type)) return 1;
    if (t->left->k == FUNCTION && !lookupEntry("result", LOOKUP_CURRENT_SCOPE, false)) {
      printf("Error (function %s): Functions must assign to result!\n", t->left->id);
    }
    closeScope();
    break;

  case SEQ_FORMAL:
    head = t;
    while(head != NULL) {
      if (type_check(head->left, ftype)) return 1;
      head = head->right;
    }
    break;

  case VARREF:
    if (type_check(t->right, ftype)) return 1;
    break;

  case DISPOSE_ARRAY:
    if (type_check(t->left, ftype)) return 1;
    if (t->left->type->kind != TYPE_ARRAY && t->left->type->kind != TYPE_IARRAY) return 1;
    break;

  case ID:
    if (!(p = lookupEntry(t->id, LOOKUP_ALL_SCOPES, true))){
      printf("Error (id): variable %s does not exist!\n", t->id);
      return 1;
    }
    if (p->u.eVariable.type)
      t->type = p->u.eVariable.type;
    else {
      printf("Error (id): variable %s does not exist!\n", t->id);
      return 1;
    }
    break;

  case LABEL:
    head = t->left;
    while (head) {
      if (lookupEntry(head->id, LOOKUP_CURRENT_SCOPE, false)) {
	printf("Error (label): name %s already exists in this scope!\n", head->id);
	return 1;
      }
      newVariable(head->id, typeLabel);
      head = head->right;
    }
    break;

  case ASSIGN:
    if (type_check(t->left, ftype) || type_check(t->right, ftype)) {
      return 1;
    }
    if (t->left->k == RESULT && !(lookupEntry("result", LOOKUP_CURRENT_SCOPE, false))) {
      newVariable("result", ftype);
      t->left->type = ftype;
    }
    if (!equalType(t->left->type, t->right->type)) {
      printf("Type error: \":=\" arguments must be of equal type\n");
      return 1;
    }
    break;

  case POINTER:
    if (type_check(t->left, ftype)) return 1;
    t->type = typePointer(t->left->type);
    break;

  case SEQ_ID:
    break;

  case RETURN:
    break;
  }
  return 0;
}

int type_checking(ast* t) {
  initSymbolTable(256);
  return type_check(t, NULL);
}
