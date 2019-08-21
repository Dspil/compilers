#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

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

  case ARRAY:
    if (t->size > 0) {
      printf("array[%d] of (", t->size);
      print_ast(t->left);
      printf(")");
    }
    else {
      printf("ARRAY_OF(");
      print_ast(t->left);
      printf(")");
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
    while(head != NULL) {
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
    while(head != NULL) {
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
    printf(")BODY(");
    print_ast(t->right);
    printf(")");
    break;
	
  case HEADER:
    switch (t->k) {
    case FUNCTION:
      printf("FUNCTION(");
      break;
    case PROCEDURE:
      printf("PROCEDURE(");
      break;
    default:;
    }
    printf("%s(", t->id);
    if (t->left != NULL)
      print_ast(t->left);
    printf(")");
    if (t->k == FUNCTION) {
      printf(" : ");
      print_ast(t->right);
    }
    printf(")");
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
    printf("ASSIGN(%s,", t->id);
    print_ast(t->right);
    printf(")");
    break;
  default:;
  }     
}
