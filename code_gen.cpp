#include "code_gen.hpp"
#include "ast_symbol.h"
#include <stdio.h>
#include <stdlib.h>

#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/Function.h"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Transforms/Scalar.h>
#if defined(LLVM_VERSION_MAJOR) && LLVM_VERSION_MAJOR >= 4
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Utils.h"
#include <llvm/Transforms/Scalar/GVN.h>
#endif

using namespace llvm;

static LLVMContext TheContext;
static IRBuilder<> Builder(TheContext);
static std::unique_ptr<Module> TheModule;
static std::unique_ptr<legacy::FunctionPassManager> TheFPM;

// Useful LLVM types.
static Type *i1 = IntegerType::get(TheContext, 1);
static Type *i8 = IntegerType::get(TheContext, 8);
static Type *i32 = IntegerType::get(TheContext, 32);
static Type *i64 = IntegerType::get(TheContext, 64);
static Type *f64 = Type::getDoubleTy(TheContext);
static Type *proc = Type::getVoidTy(TheContext);

// Useful LLVM helper functions.
inline ConstantInt *c_bool(bool b) {
  return ConstantInt::get(TheContext, APInt(1, b, true));
}
inline ConstantInt *c_char(char c) {
  return ConstantInt::get(TheContext, APInt(8, c, true));
}
inline ConstantInt *c_int(int n) {
  return ConstantInt::get(TheContext, APInt(32, n, true));
}
inline ConstantFP *c_real(double n) {
  return ConstantFP::get(TheContext, APFloat(n));
}

Type *find_llvm_type(PclType tp) {
	/* function that converts symbol table type to llvm type */
  switch (tp->kind) {
  case TYPE_INTEGER: {
    return i32;
  }
  case TYPE_CHAR: {
    return i8;
  }
  case TYPE_BOOLEAN: {
    return i1;
  }
  case TYPE_REAL: {
    return f64;
  }
  case TYPE_VOID: {
    return proc;
  }
  case TYPE_ARRAY:
  case TYPE_IARRAY: {
    return ArrayType::get(find_llvm_type(tp->refType), tp->size);
  }
  case TYPE_POINTER: {
    return find_llvm_type(tp->refType)->getPointerTo();
  }
  default: { // Should not be reached
    printf("Unknown error\n");
    return NULL;
  }
  }
}

void generate_builtins() {
	/* procedure for declaring builtin functions, which will be later defined by linking externally bultins.so (made from builtins.ll)*/
  SymbolEntry *p;
  Function *f;
  FunctionType *tp;

	//types used: int (4 bytes), char (1 byte), bool (1 byte), string (array of char), real (8 bytes - floating point)

	/* writeInteger: takes int n as argument and prints n */
  p = newFunction("writeInteger");
  openScope();
  newParameter("n", typeInteger, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeVoid);
  tp = FunctionType::get(proc, std::vector<Type *>{i32}, false);
  f = Function::Create(tp, Function::ExternalLinkage, "writeInteger",
                       TheModule.get());
  p->u.eFunction.llvmFunc = f;
  closeScope();

	/* writeBoolean: takes bool b as argument and prints true (if b == 1) or false (if b == 0) */
  p = newFunction("writeBoolean");
  openScope();
  newParameter("b", typeBoolean, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeVoid);
  tp = FunctionType::get(proc, std::vector<Type *>{i1}, false);
  f = Function::Create(tp, Function::ExternalLinkage, "writeBoolean",
                       TheModule.get());
  p->u.eFunction.llvmFunc = f;
  closeScope();

	/* writeChar: takes char c as argument and prints c */
  p = newFunction("writeChar");
  openScope();
  newParameter("c", typeChar, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeVoid);
  tp = FunctionType::get(proc, std::vector<Type *>{i8}, false);
  f = Function::Create(tp, Function::ExternalLinkage, "writeChar",
                       TheModule.get());
  p->u.eFunction.llvmFunc = f;
  closeScope();

	/* writeReal: takes real r as argument and prints r */
  p = newFunction("writeReal");
  openScope();
  newParameter("r", typeReal, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeVoid);
  tp = FunctionType::get(proc, std::vector<Type *>{f64}, false);
  f = Function::Create(tp, Function::ExternalLinkage, "writeReal",
                       TheModule.get());
  p->u.eFunction.llvmFunc = f;
  closeScope();

	/* writeString: takes constant string s as argument and prints s */
  p = newFunction("writeString");
  openScope();
  newParameter("s", typeIArray(typeChar), PASS_BY_REFERENCE, p);
  endFunctionHeader(p, typeVoid);
  tp = FunctionType::get(
      proc, std::vector<Type *>{ArrayType::get(i8, 0)->getPointerTo()}, false);
  f = Function::Create(tp, Function::ExternalLinkage, "writeString",
                       TheModule.get());
  p->u.eFunction.llvmFunc = f;
  closeScope();

	/* abs: takes int n as argument and returns absolute value of n */
  p = newFunction("abs");
  openScope();
  newParameter("n", typeInteger, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeInteger);
  tp = FunctionType::get(i32, std::vector<Type *>{i32}, false);
  f = Function::Create(tp, Function::ExternalLinkage, "abs", TheModule.get());
  p->u.eFunction.llvmFunc = f;
  closeScope();

	/* fabs: takes real r as argument and returns absolute value of r as real */
  p = newFunction("fabs");
  openScope();
  newParameter("r", typeReal, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeReal);
  tp = FunctionType::get(f64, std::vector<Type *>{f64}, false);
  f = Function::Create(tp, Function::ExternalLinkage, "fabs", TheModule.get());
  p->u.eFunction.llvmFunc = f;
  closeScope();

	/* sqrt: takes real r as argument and returns square root of r */
  p = newFunction("sqrt");
  openScope();
  newParameter("r", typeReal, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeReal);
  tp = FunctionType::get(f64, std::vector<Type *>{f64}, false);
  f = Function::Create(tp, Function::ExternalLinkage, "sqrt", TheModule.get());
  p->u.eFunction.llvmFunc = f;
  closeScope();

	/* sin: takes real r as argument and returns sine of r */
  p = newFunction("sin");
  openScope();
  newParameter("r", typeReal, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeReal);
  tp = FunctionType::get(f64, std::vector<Type *>{f64}, false);
  f = Function::Create(tp, Function::ExternalLinkage, "sin", TheModule.get());
  p->u.eFunction.llvmFunc = f;
  closeScope();

	/* cos: takes real r as argument and returns cosine of r */
  p = newFunction("cos");
  openScope();
  newParameter("r", typeReal, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeReal);
  tp = FunctionType::get(f64, std::vector<Type *>{f64}, false);
  f = Function::Create(tp, Function::ExternalLinkage, "cos", TheModule.get());
  p->u.eFunction.llvmFunc = f;
  closeScope();

	/* tan: takes real r as argument and returns tangent of r */
  p = newFunction("tan");
  openScope();
  newParameter("r", typeReal, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeReal);
  tp = FunctionType::get(f64, std::vector<Type *>{f64}, false);
  f = Function::Create(tp, Function::ExternalLinkage, "tan", TheModule.get());
  p->u.eFunction.llvmFunc = f;
  closeScope();

	/* arctan: takes real r as argument and returns arctangent of r */
  p = newFunction("arctan");
  openScope();
  newParameter("r", typeReal, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeReal);
  tp = FunctionType::get(f64, std::vector<Type *>{f64}, false);
  f = Function::Create(tp, Function::ExternalLinkage, "arctan",
                       TheModule.get());
  p->u.eFunction.llvmFunc = f;
  closeScope();

	/* exp: takes real r as argument and returns e^r */
  p = newFunction("exp");
  openScope();
  newParameter("r", typeReal, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeReal);
  tp = FunctionType::get(f64, std::vector<Type *>{f64}, false);
  f = Function::Create(tp, Function::ExternalLinkage, "exp", TheModule.get());
  p->u.eFunction.llvmFunc = f;
  closeScope();

	/* ln: takes real r as argument and returns logarithm base e of r */
  p = newFunction("ln");
  openScope();
  newParameter("r", typeReal, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeReal);
  tp = FunctionType::get(f64, std::vector<Type *>{f64}, false);
  f = Function::Create(tp, Function::ExternalLinkage, "ln", TheModule.get());
  p->u.eFunction.llvmFunc = f;
  closeScope();

	/* pi: returns pi */
  p = newFunction("pi");
  openScope();
  endFunctionHeader(p, typeReal);
  tp = FunctionType::get(f64, std::vector<Type *>{}, false);
  f = Function::Create(tp, Function::ExternalLinkage, "pi", TheModule.get());
  p->u.eFunction.llvmFunc = f;
  closeScope();

	/* trunc: takes real r as argument, truncates the decimal portion of r and returns the rest as int */
  p = newFunction("trunc");
  openScope();
  newParameter("r", typeReal, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeInteger);
  tp = FunctionType::get(i32, std::vector<Type *>{f64}, false);
  f = Function::Create(tp, Function::ExternalLinkage, "trunc2",
                       TheModule.get());
  p->u.eFunction.llvmFunc = f;
  closeScope();

	/* round: takes real r as argument returns rounded r as int */
  p = newFunction("round");
  openScope();
  newParameter("r", typeReal, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeInteger);
  tp = FunctionType::get(i32, std::vector<Type *>{f64}, false);
  f = Function::Create(tp, Function::ExternalLinkage, "round2",
                       TheModule.get());
  p->u.eFunction.llvmFunc = f;
  closeScope();

	/* ord: takes char c as argument and returns its ascii code */
  p = newFunction("ord");
  openScope();
  newParameter("c", typeChar, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeInteger);
  tp = FunctionType::get(i32, std::vector<Type *>{i8}, false);
  f = Function::Create(tp, Function::ExternalLinkage, "ord", TheModule.get());
  p->u.eFunction.llvmFunc = f;
  closeScope();

	/* chr: takes ascii code (int) of c as argument and returns char c */
  p = newFunction("chr");
  openScope();
  newParameter("n", typeInteger, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeChar);
  tp = FunctionType::get(i8, std::vector<Type *>{i32}, false);
  f = Function::Create(tp, Function::ExternalLinkage, "chr", TheModule.get());
  p->u.eFunction.llvmFunc = f;
  closeScope();

	/* readInteger: returns int read from standard input */
  p = newFunction("readInteger");
  openScope();
  endFunctionHeader(p, typeInteger);
  tp = FunctionType::get(i32, std::vector<Type *>{}, false);
  f = Function::Create(tp, Function::ExternalLinkage, "readInteger",
                       TheModule.get());
  p->u.eFunction.llvmFunc = f;
  closeScope();

	/* readBoolean: returns bool read from standard input */
  p = newFunction("readBoolean");
  openScope();
  endFunctionHeader(p, typeBoolean);
  tp = FunctionType::get(i1, std::vector<Type *>{}, false);
  f = Function::Create(tp, Function::ExternalLinkage, "readBoolean",
                       TheModule.get());
  p->u.eFunction.llvmFunc = f;
  closeScope();

	/* readChar: returns char read from standard input */
  p = newFunction("readChar");
  openScope();
  endFunctionHeader(p, typeChar);
  tp = FunctionType::get(i8, std::vector<Type *>{}, false);
  f = Function::Create(tp, Function::ExternalLinkage, "readChar",
                       TheModule.get());
  p->u.eFunction.llvmFunc = f;
  closeScope();

	/* readReal: returns real read from standard input */
  p = newFunction("readReal");
  openScope();
  endFunctionHeader(p, typeReal);
  tp = FunctionType::get(f64, std::vector<Type *>{}, false);
  f = Function::Create(tp, Function::ExternalLinkage, "readReal",
                       TheModule.get());
  p->u.eFunction.llvmFunc = f;
  closeScope();

	/* readString: takes int size and array of char s as input and saves a string
	 	 of specfic size read from standard input as null terminated in s */
  p = newFunction("readString");
  openScope();
  newParameter("size", typeInteger, PASS_BY_VALUE, p);
  newParameter("s", typeIArray(typeChar), PASS_BY_REFERENCE, p);
  endFunctionHeader(p, typeVoid);
  tp = FunctionType::get(
      proc, std::vector<Type *>{i32, ArrayType::get(i8, 0)->getPointerTo()},
      false);
  f = Function::Create(tp, Function::ExternalLinkage, "readString",
                       TheModule.get());
  p->u.eFunction.llvmFunc = f;
  closeScope();

	/* Helping function, not required
		 cMalloc: takes int size, allocates heap memory of specific size and returns
		 its first position in memory */
  p = newFunction("cMalloc");
  openScope();
  newParameter("s", typeInteger, PASS_BY_VALUE, p);
  endFunctionHeader(p, typeInteger);
  tp = FunctionType::get(i32, std::vector<Type *>{i64}, false);
  f = Function::Create(tp, Function::ExternalLinkage, "cMalloc",
                       TheModule.get());
  p->u.eFunction.llvmFunc = f;
  closeScope();
}

Value *lvalue_pointer(ast *t, Function *cur_func) {
	/* function that takes an ast t and returns its llvm stack memory position */
  SymbolEntry *p;
  Value *l, *r;
  switch (t->k) {
  case ID: {
    p = lookupEntry(t->id, LOOKUP_ALL_SCOPES, false);
    if (p->entryType == ENTRY_PARAMETER &&
        p->u.eParameter.mode == PASS_BY_REFERENCE)
      return Builder.CreateLoad(p->alloca_inst);
    return p->alloca_inst;
  }
  case RESULT: {
    p = lookupEntry("result", LOOKUP_ALL_SCOPES, false);
    return p->alloca_inst;
  }
  case INDEX: {
    if (t->left->k)
      l = lvalue_pointer(t->left, cur_func);
    r = code_gen(t->right, cur_func);
    return Builder.CreateGEP(l, std::vector<Value *>{c_int(0), r});
  }
  case DEREF: {
    l = code_gen(t->left, cur_func);
    return l;
  }
  case STR_CONST: {
    return Builder.CreateGlobalStringPtr(t->str);
  }
  default: { return NULL; }
  }
}

void prepareFunctionSymbolTable(ast *t) {
	/* function for declaring a function in the symbol table */
  PassMode pass_type;
  ast *head, *head1;
  PclType tp;
  t->sentry = newFunction(t->id);

  openScope();
  if (t->left) {    // t->left : seq_formal (parameters)
    head = t->left; // seq_formal
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
  endFunctionHeader(t->sentry, t->type);
}

Value *code_gen(ast *t, Function *cur_func) {
	/* main recursive function for generating llvm code */
  SymbolEntry *p, *p1;
  ast *head, *head1;
  PclType tp;
  Type *llvm_tp;
  Function *f;
  FunctionType *f_tp;
  Value *l, *m, *r;
  BasicBlock *lBB, *mBB, *rBB;
  std::vector<Type *> params = std::vector<Type *>();
  AllocaInst *Alloca;

  if (!t) {
		// Should not be reached
    return NULL;
  }

  switch (t->k) {

  case AND: {
		// case '+'
    l = code_gen(t->left, cur_func);
    r = code_gen(t->right, cur_func);
    return Builder.CreateAnd(l, r);
  }

  case OR: {
		// case '||'
    l = code_gen(t->left, cur_func);
    r = code_gen(t->right, cur_func);
    return Builder.CreateOr(l, r);
  }

  case BLOCK: {
		// case block of statements
    code_gen(t->left, cur_func);
    return NULL;
  }

  case BODY:
		// case local headers (if any) and block of statements
    if (t->left)
      code_gen(t->left, cur_func);
    code_gen(t->right, cur_func);
    return NULL;
  }

  case BOOL_CONST: {
		// case constant bool (e.g. true or false)
    return c_bool(t->boolean);
  }

  case CHAR_CONST: {
		// case constant char
    l = c_char(t->character);
    return l;
  }

  case DIV: {
		// case 'div'
    l = code_gen(t->left, cur_func);
    r = code_gen(t->right, cur_func);
    return Builder.CreateSDiv(l, r);
  }

  case MOD: {
		// case 'mod'
    l = code_gen(t->left, cur_func);
    r = code_gen(t->right, cur_func);
    return Builder.CreateSRem(l, r);
  }

  case FORWARD: {
		// case forward <header>
    code_gen(t->left, cur_func);
    forwardFunction(t->left->sentry);
    closeScope();
    return NULL;
  }

  case GOTO: {
		// case goto <stmt>
    p = lookupEntry(t->str, LOOKUP_CURRENT_SCOPE, false);
    if (p->u.eVariable.block) {
			// if label is already defined
      Builder.CreateBr(p->u.eVariable.block);
      return NULL;
    } else {
      p->u.eVariable.goto_stack.push_back(
          &cur_func->getBasicBlockList().back());
      lBB = BasicBlock::Create(TheContext, "help", cur_func);
      Builder.SetInsertPoint(lBB);
      return NULL;
    }
    return NULL;
  }

  case IF: {
    l = code_gen(t->left, cur_func);
    lBB = BasicBlock::Create(TheContext, "then", cur_func);
    mBB = BasicBlock::Create(TheContext, "else");
    rBB = BasicBlock::Create(TheContext, "merge");
    // printf("made basic blocks\n");
    Builder.CreateCondBr(l, lBB, mBB);
    // printf("made first branch\n");

    Builder.SetInsertPoint(lBB);
    // printf("made insert point\n");
    code_gen(t->mid, cur_func);
    // printf("code gen mid\n");
    Builder.CreateBr(rBB);
    // printf("made break\n");

    cur_func->getBasicBlockList().push_back(mBB);
    // printf("first push back\n");
    Builder.SetInsertPoint(mBB);
    // printf("made 2 insert point\n");
    if (t->right) {
      code_gen(t->right, cur_func);
      // printf("code gen else\n");
    }
    Builder.CreateBr(rBB);
    // printf("second branch\n");
    cur_func->getBasicBlockList().push_back(rBB);
    Builder.SetInsertPoint(rBB);
    return NULL;
  }

  case INT_CONST: {
    // printf("in int_const %d\n", t->integer);
    return c_int(t->integer);
  }

  case NEW: {
    // printf("in new\n");
    p = lookupEntry("cMalloc", LOOKUP_ALL_SCOPES, false);
    r = lvalue_pointer(t->right, cur_func);
    if (t->left) {
      // printf("in new1\n");
      l = code_gen(t->left, cur_func);
      // printf("in new2\n");
      // printf("prin\n");
      m = Builder.CreateIntToPtr(
          c_int(0),
          find_llvm_type(t->right->type->refType->refType)->getPointerTo());
      // printf("meta\n");
      m = Builder.CreateGEP(m, c_int(1));
      m = Builder.CreatePtrToInt(m, i32);
      m = Builder.CreateMul(l, m);
      m = Builder.CreateZExt(m, i64);
      m = Builder.CreateCall(p->u.eFunction.llvmFunc, std::vector<Value *>{m});
      m = Builder.CreateIntToPtr(
          m, find_llvm_type(t->right->type->refType)->getPointerTo());
      // printf("shit\n");
      Builder.CreateStore(m, r);
      // Builder.CreateStore(Builder.CreateAlloca(find_llvm_type(t->right->type->refType),
      // l), r); printf("in new3\n");
    } else {
      m = Builder.CreateIntToPtr(c_int(0), find_llvm_type(t->right->type));
      // printf("meta\n");
      m = Builder.CreateGEP(m, c_int(1));
      m = Builder.CreatePtrToInt(m, i64);
      m = Builder.CreateCall(p->u.eFunction.llvmFunc, std::vector<Value *>{m});
      m = Builder.CreateIntToPtr(m, find_llvm_type(t->right->type));
      // printf("shit\n");
      Builder.CreateStore(m, r);
      // printf("in new4\n");
      // Builder.CreateMalloc(cur_func->getBasicBlockList().back(), NULL,
      // find_llvm_type(t->right->type->refType), NULL, l, NULL, cur_func);
      // Builder.CreateStore(Builder.CreateAlloca(find_llvm_type(t->right->type->refType),
      // 0, "newtmp"), r); printf("in new5\n");
    }
    // printf("out new\n");
    return NULL;
  }

  case NOT: {
    l = code_gen(t->left, cur_func);
    return Builder.CreateNot(l);
  }

  case FUNCTION:
  case PROCEDURE: {
    // printf("in proc\n");
    prepareFunctionSymbolTable(t);
    // printf("mesa\n");
    p1 = t->sentry->u.eFunction.firstArgument;
    // printf("mesa1\n");
    if (t->left) {    // t->left : seq_formal (parameters)
      head = t->left; // seq_formal
      while (head) {
        // printf("in while\n");
        llvm_tp = find_llvm_type(head->left->right->type);
        if (p1->u.eParameter.mode == PASS_BY_REFERENCE)
          llvm_tp = llvm_tp->getPointerTo();
        head1 = head->left->left;
        while (head1) {
          // printf("in while2\n");
          params.push_back(llvm_tp);
          head1 = head1->right;
          p1 = p1->u.eParameter.next;
          // printf("out while2\n");
        }
        // printf("out while\n");
        head = head->right;
      }
      // printf("outproc\n");
    }
    // printf("found type\n");
    // printf("made header\n");
    f_tp = FunctionType::get(find_llvm_type(t->type), params, false);
    // printf("found llvmtype\n");
    f = Function::Create(f_tp, Function::InternalLinkage, t->id,
                         TheModule.get());
    // printf("made func\n");
    t->sentry->u.eFunction.llvmFunc = f;
    // printf("wtf?\n");
    return NULL;
  }

  case PROGRAM: {
    // printf("in program\n");
    openScope();
    generate_builtins();
    f_tp = FunctionType::get(i32, std::vector<llvm::Type *>{}, false);
    f = llvm::Function::Create(f_tp, llvm::Function::ExternalLinkage, "main",
                               TheModule.get());
    BasicBlock *BB = BasicBlock::Create(TheContext, "entry", f);
    Builder.SetInsertPoint(BB);
    // printf("before run tleft\n");
    code_gen(t->left, f);
    // printf("ran tleft\n");
    Builder.CreateRet(c_int(0));
    // printSymbolTable();
    // printf("out createret\n");
    closeScope();
    // printf("closed scope\n");
		if (optimize_code) {
    	TheFPM = std::make_unique<legacy::FunctionPassManager>(TheModule.get());
    	TheFPM->add(createPromoteMemoryToRegisterPass());
    	TheFPM->add(createInstructionCombiningPass());
    	TheFPM->add(createReassociatePass());
    	TheFPM->add(createGVNPass());
    	TheFPM->add(createCFGSimplificationPass());
    	TheFPM->doInitialization();
    	TheFPM->run(*f);
		}
    return NULL;
  }

  case REAL_CONST: {
    return c_real(t->real);
  }

  case RESULT: {
    p = lookupEntry("result", LOOKUP_CURRENT_SCOPE, false);
    return Builder.CreateLoad(p->alloca_inst);
  }

  case VAR: {
    return NULL;
  }

  case WHILE: {
    l = code_gen(t->left, cur_func);
    lBB = BasicBlock::Create(TheContext, "loop", cur_func);
    rBB = BasicBlock::Create(TheContext, "after");

    Builder.CreateCondBr(l, lBB, rBB);

    Builder.SetInsertPoint(lBB);
    code_gen(t->right, cur_func);

    l = code_gen(t->left, cur_func);
    Builder.CreateCondBr(l, lBB, rBB);

    cur_func->getBasicBlockList().push_back(rBB);
    Builder.SetInsertPoint(rBB);
    return NULL;
  }

  case STR_CONST: {
    return ConstantDataArray::getString(TheContext, t->str, true);
  }

  case NEQ: {
    l = code_gen(t->left, cur_func);
    r = code_gen(t->right, cur_func);
    if (t->left->type->kind == TYPE_INTEGER &&
        t->right->type->kind == TYPE_REAL) {
      l = Builder.CreateCast(Instruction::SIToFP, l, f64);
      return Builder.CreateFCmpONE(l, r);
    } else if (t->right->type->kind == TYPE_INTEGER &&
               t->left->type->kind == TYPE_REAL) {
      r = Builder.CreateCast(Instruction::SIToFP, r, f64);
      return Builder.CreateFCmpONE(l, r);
    } else if (t->right->type->kind == TYPE_REAL &&
               t->left->type->kind == TYPE_REAL) {
      return Builder.CreateFCmpONE(l, r);
    }
    return Builder.CreateICmpNE(l, r);
  }

  case EQ: {
    l = code_gen(t->left, cur_func);
    r = code_gen(t->right, cur_func);
    if (t->left->type->kind == TYPE_INTEGER &&
        t->right->type->kind == TYPE_REAL) {
      l = Builder.CreateCast(Instruction::SIToFP, l, f64);
      return Builder.CreateFCmpOEQ(l, r);
    } else if (t->right->type->kind == TYPE_INTEGER &&
               t->left->type->kind == TYPE_REAL) {
      r = Builder.CreateCast(Instruction::SIToFP, r, f64);
      return Builder.CreateFCmpOEQ(l, r);
    } else if (t->right->type->kind == TYPE_REAL &&
               t->left->type->kind == TYPE_REAL) {
      return Builder.CreateFCmpOEQ(l, r);
    }
    return Builder.CreateICmpEQ(l, r);
  }

  case GEQ: {
    l = code_gen(t->left, cur_func);
    r = code_gen(t->right, cur_func);
    if (t->left->type->kind == TYPE_INTEGER &&
        t->right->type->kind == TYPE_REAL) {
      l = Builder.CreateCast(Instruction::SIToFP, l, f64);
      return Builder.CreateFCmpOGE(l, r);
    } else if (t->right->type->kind == TYPE_INTEGER &&
               t->left->type->kind == TYPE_REAL) {
      r = Builder.CreateCast(Instruction::SIToFP, r, f64);
      return Builder.CreateFCmpOGE(l, r);
    } else if (t->right->type->kind == TYPE_REAL &&
               t->left->type->kind == TYPE_REAL) {
      return Builder.CreateFCmpOGE(l, r);
    }
    return Builder.CreateICmpSGE(l, r);
  }

  case LEQ: {
    l = code_gen(t->left, cur_func);
    r = code_gen(t->right, cur_func);
    if (t->left->type->kind == TYPE_INTEGER &&
        t->right->type->kind == TYPE_REAL) {
      l = Builder.CreateCast(Instruction::SIToFP, l, f64);
      return Builder.CreateFCmpOLE(l, r);
    } else if (t->right->type->kind == TYPE_INTEGER &&
               t->left->type->kind == TYPE_REAL) {
      r = Builder.CreateCast(Instruction::SIToFP, r, f64);
      return Builder.CreateFCmpOLE(l, r);
    } else if (t->right->type->kind == TYPE_REAL &&
               t->left->type->kind == TYPE_REAL) {
      return Builder.CreateFCmpOLE(l, r);
    }
    return Builder.CreateICmpSLE(l, r);
  }

  case LESS: {
    l = code_gen(t->left, cur_func);
    r = code_gen(t->right, cur_func);
    if (t->left->type->kind == TYPE_INTEGER &&
        t->right->type->kind == TYPE_REAL) {
      l = Builder.CreateCast(Instruction::SIToFP, l, f64);
      return Builder.CreateFCmpOLT(l, r);
    } else if (t->right->type->kind == TYPE_INTEGER &&
               t->left->type->kind == TYPE_REAL) {
      r = Builder.CreateCast(Instruction::SIToFP, r, f64);
      return Builder.CreateFCmpOLT(l, r);
    } else if (t->right->type->kind == TYPE_REAL &&
               t->left->type->kind == TYPE_REAL) {
      return Builder.CreateFCmpOLT(l, r);
    }
    return Builder.CreateICmpSLT(l, r);
  }

  case GREATER: {
    l = code_gen(t->left, cur_func);
    r = code_gen(t->right, cur_func);
    if (t->left->type->kind == TYPE_INTEGER &&
        t->right->type->kind == TYPE_REAL) {
      l = Builder.CreateCast(Instruction::SIToFP, l, f64);
      return Builder.CreateFCmpOGT(l, r);
    } else if (t->right->type->kind == TYPE_INTEGER &&
               t->left->type->kind == TYPE_REAL) {
      r = Builder.CreateCast(Instruction::SIToFP, r, f64);
      return Builder.CreateFCmpOGT(l, r);
    } else if (t->right->type->kind == TYPE_REAL &&
               t->left->type->kind == TYPE_REAL) {
      return Builder.CreateFCmpOGT(l, r);
    }
    return Builder.CreateICmpSGT(l, r);
  }

  case PLUS: {
    l = code_gen(t->left, cur_func);
    if (!t->right)
      return l;
    r = code_gen(t->right, cur_func);
    if (t->left->type->kind == TYPE_INTEGER &&
        t->right->type->kind == TYPE_REAL) {
      l = Builder.CreateCast(Instruction::SIToFP, l, f64);
      return Builder.CreateFAdd(l, r);
    } else if (t->right->type->kind == TYPE_INTEGER &&
               t->left->type->kind == TYPE_REAL) {
      r = Builder.CreateCast(Instruction::SIToFP, r, f64);
      return Builder.CreateFAdd(l, r);
    } else if (t->right->type->kind == TYPE_REAL &&
               t->left->type->kind == TYPE_REAL) {
      return Builder.CreateFAdd(l, r);
    }
    return Builder.CreateAdd(l, r);
  }

  case MINUS: {
    l = code_gen(t->left, cur_func);
    if (!t->right) {
      if (t->left->type->kind == TYPE_REAL)
        return Builder.CreateFSub(c_real(0.0), l);
      else
        return Builder.CreateSub(c_int(0), l);
    }
    r = code_gen(t->right, cur_func);
    if (t->left->type->kind == TYPE_INTEGER &&
        t->right->type->kind == TYPE_REAL) {
      l = Builder.CreateCast(Instruction::SIToFP, l, f64);
      return Builder.CreateFSub(l, r);
    } else if (t->right->type->kind == TYPE_INTEGER &&
               t->left->type->kind == TYPE_REAL) {
      r = Builder.CreateCast(Instruction::SIToFP, r, f64);
      return Builder.CreateFSub(l, r);
    } else if (t->right->type->kind == TYPE_REAL &&
               t->left->type->kind == TYPE_REAL) {
      return Builder.CreateFSub(l, r);
    }
    return Builder.CreateSub(l, r);
  }

  case TIMES: {
    l = code_gen(t->left, cur_func);
    r = code_gen(t->right, cur_func);
    if (t->left->type->kind == TYPE_INTEGER &&
        t->right->type->kind == TYPE_REAL) {
      l = Builder.CreateCast(Instruction::SIToFP, l, f64);
      return Builder.CreateFMul(l, r);
    } else if (t->right->type->kind == TYPE_INTEGER &&
               t->left->type->kind == TYPE_REAL) {
      r = Builder.CreateCast(Instruction::SIToFP, r, f64);
      return Builder.CreateFMul(l, r);
    } else if (t->right->type->kind == TYPE_REAL &&
               t->left->type->kind == TYPE_REAL) {
      return Builder.CreateFMul(l, r);
    }
    return Builder.CreateMul(l, r);
  }

  case DIVIDE: {
    l = code_gen(t->left, cur_func);
    r = code_gen(t->right, cur_func);
    if (t->left->type->kind == TYPE_INTEGER) {
      l = Builder.CreateCast(Instruction::SIToFP, l, f64);
    }
    if (t->right->type->kind == TYPE_INTEGER) {
      r = Builder.CreateCast(Instruction::SIToFP, r, f64);
    }
    return Builder.CreateFDiv(l, r);
  }

  case DEREF: {
    return Builder.CreateLoad(code_gen(t->left, cur_func));
  }

  case REF: {
    return lvalue_pointer(t->left, cur_func);
  }

  case SEQ_STMT: {
    // printf("in seq_stmt\n");
    for (head = t; head; head = head->right) {
      if (!head->left)
        break;
      code_gen(head->left, cur_func);
      // printf("done with stmt\n");
    }
    // printf("done with everything\n");
    return NULL;
  }

  case STMT: {
    // printf("in stmt\n");
    lBB = BasicBlock::Create(TheContext, "labelb", cur_func);
    Builder.CreateBr(lBB);
    // printf("create block\n");
    p = lookupEntry(t->id, LOOKUP_CURRENT_SCOPE, false);
    // printf("lookedup\n");
    p->u.eVariable.block = lBB;
    std::vector<BasicBlock *> v_blocks = p->u.eVariable.goto_stack;
    while (!v_blocks.empty()) {
      Builder.SetInsertPoint(v_blocks.back());
      Builder.CreateBr(lBB);
      v_blocks.pop_back();
    }
    // printf("found block\n");
    Builder.SetInsertPoint(lBB);
    // printf("went there\n");
    code_gen(t->left, cur_func);
    // printf("generate rest\n");
    return NULL;
  }

  case INDEX: {
    return Builder.CreateLoad(lvalue_pointer(t, cur_func));
  }

  case CALL: {
    // printf("in call\n");
    p = lookupEntry(t->id, LOOKUP_ALL_SCOPES, true);
    p1 = p->u.eFunction.firstArgument;
    f = p->u.eFunction.llvmFunc;
    // printf("before call %s\n", t->id);
    // printf("%s\n", p->id);
    std::vector<Value *> params;
    for (head = t->left; head; head = head->right) {

      if (p1->u.eParameter.mode == PASS_BY_REFERENCE) {
        l = lvalue_pointer(head->left, cur_func);
        // printf("megethos2 %d\n", p1->u.eParameter.type->size);
        if (l->getType() !=
            find_llvm_type(p1->u.eParameter.type)->getPointerTo()) {
          l = Builder.CreateBitCast(
              l, find_llvm_type(p1->u.eParameter.type)->getPointerTo());
        }
      } else {
        l = code_gen(head->left, cur_func);
        if (head->left->type->kind == TYPE_INTEGER &&
            p1->u.eParameter.type->kind == TYPE_REAL) {
          l = Builder.CreateCast(Instruction::SIToFP, l, f64);
        }
      }

      params.push_back(l);
      // printf("pushed back param\n");
      p1 = p1->u.eParameter.next;
    }
    auto ret = Builder.CreateCall(f, params);
    // printf("made call\n");
    return ret;
  }

  case SEQ_LOCAL: {
    // printf("in seq local\n");
    for (head = t; head; head = head->right) {
      // printf("in seq_local %d\n", head->left->k);
      code_gen(head->left, cur_func);
      // printf("out seq_local %d\n", head->left->k);
    }
    // printf("out seq local\n");
    return NULL;
  }

  case SEQ_LOCAL_VAR: {
    for (head = t; head; head = head->right) {
      // printf("in seq local var %d\n", head->left->k);
      code_gen(head->left, cur_func);
      // printf("out seq local var %d\n", head->left->k);
    }
    return NULL;
  }

  case LOCAL_VAR_INSTANCE: {
    // printf("in local_var_instance %d\n", t->left->k);
    tp = t->right->type;
    llvm_tp = find_llvm_type(tp);
    // printf("found type\n");
    for (head = t->left; head; head = head->right) {
      p = newVariable(head->id, tp);
      // printf("made variable\n");
      p->alloca_inst = Builder.CreateAlloca(llvm_tp, 0, head->id);
      // printf("alloca\n");
    }
    // printf("out local_var_instance %d\n", t->left->k);
    return NULL;
  }

  case LOCAL_VAR: {
    // printf("in local var %d\n", t->left->k);
    code_gen(t->left, cur_func);
    // printf("out local var\n");
    return NULL;
  }

  case DEFINITION: {
    if (!(p = lookupEntry(t->left->id, LOOKUP_ALL_SCOPES, false))) {
      code_gen(t->left, cur_func);
      p = t->left->sentry;
    } else
      prepareFunctionSymbolTable(t->left);
    rBB = &cur_func->getBasicBlockList().back();
    cur_func = p->u.eFunction.llvmFunc;
    lBB = BasicBlock::Create(TheContext, t->left->id, cur_func);
    Builder.SetInsertPoint(lBB);
    p1 = p->u.eFunction.firstArgument;
    for (auto &Arg : cur_func->args()) {
      Arg.setName(p1->id);
      if (p1->u.eParameter.mode == PASS_BY_REFERENCE) {
        Alloca = Builder.CreateAlloca(
            find_llvm_type(p1->u.eParameter.type)->getPointerTo(), 0,
            Arg.getName());
      } else {
        Alloca = Builder.CreateAlloca(find_llvm_type(p1->u.eParameter.type), 0,
                                      Arg.getName());
      }
      p1->alloca_inst = Alloca;
      // if(Arg.getType() == ArrayType::get(i8,
      // 0)->getPointerTo()->getPointerTo()) printf("ola sosta\n");
      Builder.CreateStore(&Arg, Alloca);
      p1 = p1->u.eParameter.next;
    }
    if (t->left->k == FUNCTION) {
      p = newVariable("result", t->left->type);
      p->alloca_inst =
          Builder.CreateAlloca(find_llvm_type(t->left->type), 0, "result");
    }
    code_gen(t->right, cur_func);
    llvm_tp = cur_func->getReturnType();

    if (llvm_tp->isVoidTy())
      Builder.CreateRetVoid();
    else
      Builder.CreateRet(Builder.CreateLoad(
          lookupEntry("result", LOOKUP_CURRENT_SCOPE, false)->alloca_inst));
    Builder.SetInsertPoint(rBB);
    closeScope();
    return NULL;
  }

  case DISPOSE_ARRAY: {
    // printf("in\n");
    l = code_gen(t->left, cur_func);
    auto inst = CallInst::CreateFree(l, Builder.GetInsertBlock());
    Builder.GetInsertBlock()->getInstList().push_back(inst);
    Builder.CreateStore(
        Builder.CreateIntToPtr(c_int(0), find_llvm_type(t->left->type)),
        lvalue_pointer(t->left, cur_func));
    return NULL;
  }

  case DISPOSE: {
    l = code_gen(t->left, cur_func);
    auto inst = CallInst::CreateFree(l, Builder.GetInsertBlock());
    Builder.GetInsertBlock()->getInstList().push_back(inst);
    Builder.CreateStore(
        Builder.CreateIntToPtr(c_int(0), find_llvm_type(t->left->type)),
        lvalue_pointer(t->left, cur_func));
    return NULL;
  }

  case ID: {
    p = lookupEntry(t->id, LOOKUP_ALL_SCOPES, false);
    l = Builder.CreateLoad(p->alloca_inst);
    if (p->entryType == ENTRY_PARAMETER &&
        p->u.eParameter.mode == PASS_BY_REFERENCE)
      l = Builder.CreateLoad(l);
    return l;
  }

  case LABEL: {
    // printf("inlabel\n");
    head = t->left;
    while (head) {
      newVariable(head->id, typeLabel);
      head = head->right;
    }
    // printf("outlabel\n");
    return NULL;
  }

  case ASSIGN: {
    l = lvalue_pointer(t->left, cur_func);
    if (t->right->k == NIL) {
      Builder.CreateStore(
          Builder.CreateIntToPtr(c_int(0), find_llvm_type(t->left->type)), l);
      return NULL;
    }
    r = code_gen(t->right, cur_func);
    if (t->left->type->kind == TYPE_REAL &&
        t->right->type->kind == TYPE_INTEGER)
      r = Builder.CreateCast(Instruction::SIToFP, r, f64);
    Builder.CreateStore(r, l);
    return NULL;
  }

  case RETURN: {
    llvm_tp = cur_func->getReturnType();
    if (llvm_tp->isVoidTy())
      Builder.CreateRetVoid();
    else
      Builder.CreateRet(Builder.CreateLoad(
          lookupEntry("result", LOOKUP_CURRENT_SCOPE, false)->alloca_inst));
    lBB = BasicBlock::Create(TheContext, "afterret", cur_func);
    Builder.SetInsertPoint(lBB);
    return NULL;
  }

  case VARREF:
  case SEQ_FORMAL:
  case IARRAY:
  case ARRAY:
  case INT:
  case CHAR:
  case BOOL:
  case POINTER:
  case REAL:
  case SEQ_EXPR:
  case SEQ_ID:
  case NIL: {
    printf("oups %d\n", t->k);
    return NULL;
  }
  default: { return NULL; }
  }
  return NULL;
}

void generate_code(ast *t) {
  TheModule = std::make_unique<Module>("pcl program", TheContext);
  initSymbolTable(256);
  code_gen(t, NULL);
  TheModule->print(outs(), nullptr);
}
