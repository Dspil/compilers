#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "symbol.h"
#include "code_gen.hpp"

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Transforms/Scalar.h>
#if defined(LLVM_VERSION_MAJOR) && LLVM_VERSION_MAJOR >= 4
#include <llvm/Transforms/Scalar/GVN.h>
#include "llvm/Transforms/Utils.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"

#endif

using namespace llvm;

static LLVMContext TheContext;
static IRBuilder<> Builder(TheContext);
static std::unique_ptr<Module> TheModule;
static std::unique_ptr<legacy::FunctionPassManager> TheFPM;

// Global LLVM variables related to the generated code.
static GlobalVariable *TheVars;
static GlobalVariable *TheNL;
static Function *TheWriteInteger;
static Function *TheWriteString;

// Useful LLVM types.
static Type * i8 = IntegerType::get(TheContext, 8);
static Type * i32 = IntegerType::get(TheContext, 32);
static Type * i64 = IntegerType::get(TheContext, 64);

// Useful LLVM helper functions.
inline ConstantInt* c_bool(bool b) {
  return ConstantInt::get(TheContext, APInt(8, b, true));
}
inline ConstantInt* c_char(char c) {
  return ConstantInt::get(TheContext, APInt(8, c, true));
}
inline ConstantInt* c_int(int n) {
  return ConstantInt::get(TheContext, APInt(32, n, true));
}
inline ConstantFP* c_real(long double n) {
  return ConstantFP::get(TheContext, APFloat(n));
}

void generate_builtins() {
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

Value* code_gen(ast * t, PclType ftype) {
	SymbolEntry *p, *p1;
    ast *head, *head1;
    PclType tp;
    PassMode pass_type;
    if (!t) {
      return 1;
    }
    switch (t->k) {

    case AND:
    case OR:
      if (code_gen(t->left, ftype) || code_gen(t->right, ftype)) return 1;
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
      if (code_gen(t->left, ftype)) return 1;
      t->type = typeIArray(t->left->type);
      t->full = false;
      break;

    case ARRAY:
      if (code_gen(t->left, ftype)) return 1;
      if (t->size > 0) t->type = typeArray(t->size, t->left->type);
      else {
        printf("Type error: size of array must be positive!\n");
        return 1;
      }
      t->full = t->left->full;
      break;

    case BLOCK:
      if (code_gen(t->left, ftype)) {
        return 1;
      }
      t->type = NULL;
      break;

    case BODY:
      if (t->left && code_gen(t->left, ftype)) return 1;
      if (code_gen(t->right, ftype)){
        return 1;
      }
      break;

    case BOOL:
		break;
    case BOOL_CONST:
	  	return c_bool(t->boolean);

    case CHAR:
		break;
    case CHAR_CONST:
		return c_char(t->character);

    case DISPOSE:
      if (code_gen(t->left, ftype)) return 1;
      if (t->left->type->kind != TYPE_POINTER) {
        printf("Type error: \"dispose\" argument must be pointer!\n");
        return 1;
      }
      break;

    case DIV:
    case MOD:
      if (code_gen(t->left, ftype) || code_gen(t->right, ftype)) return 1;
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
      if (code_gen(t->left, ftype)) return 1;
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
      if (code_gen(t->left, ftype) || code_gen(t->mid, ftype) || (t->right && code_gen(t->right, ftype))) return 1;
      if (!(t->left->type->kind == TYPE_BOOLEAN)){
        printf("Type Error: if condition must be boolean!\n");
        return 1;
      }
      break;

    case INT:
		break;
    case INT_CONST:
		return c_int(t->integer);
      	break;

    case NEW:
      if (!t->left) {
        if (code_gen(t->right, ftype)) return 1;
        if (t->right->type->kind != TYPE_POINTER || (!t->right->full)){
          printf("Type Error: \"new\" argument must be full type and pointer!\n");
          return 1;
        }
      }
      else {
        if (code_gen(t->left, ftype) || code_gen(t->right, ftype)) return 1;
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
      if (code_gen(t->left, ftype)) return 1;
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
        if (code_gen(t->left, ftype)) return 1;
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
        if (code_gen(t->left, ftype)) return 1;
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
      if (code_gen(t->right, ftype)) {
        return 1;
      }
      t->type = t->right->type;
      endFunctionHeader(t->sentry, t->type);
      break;

    case PROGRAM:
      openScope();
      generate_builtins();
      if (code_gen(t->left, ftype)) {
        return 1;
      }
      closeScope();
      break;

    case REAL:
		break;
    case REAL_CONST:
      	return c_real(t->real);
		

    case RESULT:
      if (!ftype || ftype->kind == TYPE_VOID){
        printf("Error (result): \"result\" variable can only exist in function body!\n");
        return 1;
      }
      if(lookupEntry("result", LOOKUP_CURRENT_SCOPE, false)) t->type = ftype;
      else t->type = typeVoid;
      break;

    case VAR:
      if (code_gen(t->right, ftype)) return 1;
      break;

    case WHILE:
      if (code_gen(t->left, ftype) || code_gen(t->right, ftype)) return 1;
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
      if (code_gen(t->left, ftype) || code_gen(t->right, ftype)) return 1;
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
      if (code_gen(t->left, ftype) || code_gen(t->right, ftype)) return 1;
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
      if (code_gen(t->left, ftype) || code_gen(t->right, ftype)) return 1;
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
      if (code_gen(t->left, ftype) || code_gen(t->right, ftype)) return 1;
      if ((t->left->type->kind == TYPE_INTEGER || t->left->type->kind == TYPE_REAL) && (t->right->type->kind == TYPE_INTEGER || t->right->type->kind == TYPE_REAL)) t->type = typeReal;
      else {
        printf("Type Error: \"/\" arguments must be arithmetic!\n");
        return 1;
      }
      break;

    case DEREF:
      if (code_gen(t->left, ftype)) return 1;
      if (t->left->type) t->type = typePointer(t->left->type);
      else {
        printf("Type Error: \"@\" argument must pointer!\n");
        return 1;
      }
      break;

    case REF:
      if (code_gen(t->left, ftype)) return 1;
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
        if (head->left && code_gen(head->left, ftype)) {
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
      if (code_gen(t->right, ftype)) {
        return 1;
      }
      break;

    case INDEX:
      if (code_gen(t->left, ftype) || code_gen(t->right, ftype)) return 1;
      if ((t->left->type->kind == TYPE_ARRAY || t->left->type->kind == TYPE_IARRAY) && t->right->type->kind == TYPE_INTEGER) t->type = t->left->type->refType;
      else {
        printf("Type Error: Can only index an array and index must be integer!\n");
        return 1;
      }
      break;

    case CALL:
      if (t->left && code_gen(t->left, ftype)) return 1;
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
        if (code_gen(head->left, ftype)) return 1;
        head = head->right;
      }
      break;

    case SEQ_LOCAL_VAR:
      head = t;
      while (head) {
        if (code_gen(head->left, ftype)) return 1;
        head = head->right;
      }
      break;

    case LOCAL_VAR_INSTANCE:
      if (code_gen(t->right, ftype)) return 1;
      tp = t->right->type;
      head = t->left;
      while (head) {
        newVariable(head->id, tp);
        head = head->right;
      }
      break;

    case LOCAL_VAR:
      if (code_gen(t->left, ftype)) return 1;
      break;

    case DEFINITION:
      if (code_gen(t->left, ftype) || code_gen(t->right, t->left->type)) return 1;
      if (t->left->k == FUNCTION && !lookupEntry("result", LOOKUP_CURRENT_SCOPE, false)) {
        printf("Error (function %s): Functions must assign to result!\n", t->left->id);
      }
      closeScope();
      break;

    case SEQ_FORMAL:
      head = t;
      while(head != NULL) {
        if (code_gen(head->left, ftype)) return 1;
        head = head->right;
      }
      break;

    case VARREF:
      if (code_gen(t->right, ftype)) return 1;
      break;

    case DISPOSE_ARRAY:
      if (code_gen(t->left, ftype)) return 1;
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
      if (code_gen(t->left, ftype) || code_gen(t->right, ftype)) {
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
      if (code_gen(t->left, ftype)) return 1;
      t->type = typePointer(t->left->type);
      break;

    case SEQ_ID:
      break;

    case RETURN:
      break;
    }
    return 0;
}

void generate_code() {
	TheModule = std::make_unique<Module>("minibasic program", TheContext);

}
