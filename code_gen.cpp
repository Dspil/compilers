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
		// case locals (if any) and block of statements
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
		// case 'goto <stmt>'
    p = lookupEntry(t->str, LOOKUP_CURRENT_SCOPE, false);
    if (p->u.eVariable.block) {
			// if label is already defined create branch to that BasicBlock
      Builder.CreateBr(p->u.eVariable.block);
      return NULL;
    } else {
			// if label not already defined, save goto for when label is defined
      p->u.eVariable.goto_stack.push_back(
          &cur_func->getBasicBlockList().back());
      lBB = BasicBlock::Create(TheContext, "help", cur_func);
      Builder.SetInsertPoint(lBB);
      return NULL;
    }
    return NULL;
  }

  case IF: {
		// case 'if then (else)'
    l = code_gen(t->left, cur_func);
    lBB = BasicBlock::Create(TheContext, "then", cur_func);
    mBB = BasicBlock::Create(TheContext, "else");
    rBB = BasicBlock::Create(TheContext, "merge");

    Builder.CreateCondBr(l, lBB, mBB);
    Builder.SetInsertPoint(lBB);
    code_gen(t->mid, cur_func);
    Builder.CreateBr(rBB);
    cur_func->getBasicBlockList().push_back(mBB);
    Builder.SetInsertPoint(mBB);

    if (t->right) {
			//if else exists
      code_gen(t->right, cur_func);
    }

    Builder.CreateBr(rBB);
    cur_func->getBasicBlockList().push_back(rBB);
    Builder.SetInsertPoint(rBB);
    return NULL;
  }

  case INT_CONST: {
		// case constant int
    return c_int(t->integer);
  }

  case NEW: {
    // case 'new'
    p = lookupEntry("cMalloc", LOOKUP_ALL_SCOPES, false);
    r = lvalue_pointer(t->right, cur_func);
    if (t->left) {
			// case 'new [size] l'
      l = code_gen(t->left, cur_func);
      m = Builder.CreateIntToPtr(
          c_int(0),
          find_llvm_type(t->right->type->refType->refType)->getPointerTo());
			// trick with CreateGEP instruction to get size of that to which l is pointing
      m = Builder.CreateGEP(m, c_int(1));
      m = Builder.CreatePtrToInt(m, i32);

			// size * number of elements
      m = Builder.CreateMul(l, m);
      m = Builder.CreateZExt(m, i64);

			// call declared cMalloc
      m = Builder.CreateCall(p->u.eFunction.llvmFunc, std::vector<Value *>{m});
      m = Builder.CreateIntToPtr(
          m, find_llvm_type(t->right->type->refType)->getPointerTo());

      Builder.CreateStore(m, r);
    }
		else {
			//case 'new l'
      m = Builder.CreateIntToPtr(c_int(0), find_llvm_type(t->right->type));

      m = Builder.CreateGEP(m, c_int(1));
      m = Builder.CreatePtrToInt(m, i64);
      m = Builder.CreateCall(p->u.eFunction.llvmFunc, std::vector<Value *>{m});
      m = Builder.CreateIntToPtr(m, find_llvm_type(t->right->type));
      Builder.CreateStore(m, r);
    }
    return NULL;
  }

  case NOT: {
		// case 'not'
    l = code_gen(t->left, cur_func);
    return Builder.CreateNot(l);
  }

  case FUNCTION:
  case PROCEDURE: {
    prepareFunctionSymbolTable(t);
    p1 = t->sentry->u.eFunction.firstArgument;
    if (t->left) {
			// if function (or procedure) has arguments
      head = t->left; // seq_formal
      while (head) {
        llvm_tp = find_llvm_type(head->left->right->type);
        if (p1->u.eParameter.mode == PASS_BY_REFERENCE) {
					// if pass by reference pass pointer
          llvm_tp = llvm_tp->getPointerTo();
				}
        head1 = head->left->left;
        while (head1) {
					// while loop for all variables in one declaration (e.g var x, y, z : integer)
          params.push_back(llvm_tp);
          head1 = head1->right;
          p1 = p1->u.eParameter.next;
        }
        head = head->right;
      }
    }
    f_tp = FunctionType::get(find_llvm_type(t->type), params, false);
    f = Function::Create(f_tp, Function::InternalLinkage, t->id,
                         TheModule.get());
		// save llvm object of funtion for later use
    t->sentry->u.eFunction.llvmFunc = f;
    return NULL;
  }

  case PROGRAM: {
    // case 'program'
    openScope();
    generate_builtins();
    f_tp = FunctionType::get(i32, std::vector<llvm::Type *>{}, false);
    f = llvm::Function::Create(f_tp, llvm::Function::ExternalLinkage, "main",
                               TheModule.get());
    BasicBlock *BB = BasicBlock::Create(TheContext, "entry", f);
    Builder.SetInsertPoint(BB);
    code_gen(t->left, f);
    Builder.CreateRet(c_int(0));
    closeScope();
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
		//case constant real
    return c_real(t->real);
  }

  case RESULT: {
		// case 'result' as rvalue
    p = lookupEntry("result", LOOKUP_CURRENT_SCOPE, false);
    return Builder.CreateLoad(p->alloca_inst);
  }

  case WHILE: {
		// case 'while'
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
		// case constant string
    return ConstantDataArray::getString(TheContext, t->str, true);
  }

  case NEQ: {
		// case '<>'
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
		// case '='
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
		// case '>='
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
		// case '<='
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
		// case '<'
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
		// case '>'
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
		// case '+'
    l = code_gen(t->left, cur_func);
    if (!t->right) {
			// if unary operator
			return l;
		}
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
		// case '-'
    l = code_gen(t->left, cur_func);
    if (!t->right) {
			// if unary operator
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
		// case '*'
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
		// case '/'
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
		// case 'l^'
    return Builder.CreateLoad(code_gen(t->left, cur_func));
  }

  case REF: {
		// case '@l'
    return lvalue_pointer(t->left, cur_func);
  }

  case SEQ_STMT: {
		// case sequence of statements
    for (head = t; head; head = head->right) {
      if (!head->left)
        break;
      code_gen(head->left, cur_func);
    }
    return NULL;
  }

  case STMT: {
		// case label : statement
    lBB = BasicBlock::Create(TheContext, "labelb", cur_func);
    Builder.CreateBr(lBB);

		// label in t->id
    p = lookupEntry(t->id, LOOKUP_CURRENT_SCOPE, false);

    p->u.eVariable.block = lBB;
    std::vector<BasicBlock *> v_blocks = p->u.eVariable.goto_stack;

    while (!v_blocks.empty()) {
			// make branches for the saved gotos
      Builder.SetInsertPoint(v_blocks.back());
      Builder.CreateBr(lBB);
      v_blocks.pop_back();
    }
    Builder.SetInsertPoint(lBB);
    code_gen(t->left, cur_func);
    return NULL;
  }

  case INDEX: {
    return Builder.CreateLoad(lvalue_pointer(t, cur_func));
  }

  case CALL: {
    // case call of function (or procedure)
    p = lookupEntry(t->id, LOOKUP_ALL_SCOPES, false);
    p1 = p->u.eFunction.firstArgument;
    f = p->u.eFunction.llvmFunc;
    std::vector<Value *> params;

    for (head = t->left; head; head = head->right) {

      if (p1->u.eParameter.mode == PASS_BY_REFERENCE) {
        l = lvalue_pointer(head->left, cur_func);
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
      p1 = p1->u.eParameter.next;
    }
    auto ret = Builder.CreateCall(f, params);
    return ret;
  }

  case SEQ_LOCAL: {
    // case sequence of locals
    for (head = t; head; head = head->right) {
      code_gen(head->left, cur_func);
    }
    return NULL;
  }

  case SEQ_LOCAL_VAR: {
		// case sequence of local vars (e.g. var x, y : integer; z, k : integer)
    for (head = t; head; head = head->right) {
      code_gen(head->left, cur_func);
    }
    return NULL;
  }

  case LOCAL_VAR_INSTANCE: {
    // case of local vars with same type (e.g. var x, y : integer)
    tp = t->right->type;
    llvm_tp = find_llvm_type(tp);

    for (head = t->left; head; head = head->right) {
      p = newVariable(head->id, tp);
      p->alloca_inst = Builder.CreateAlloca(llvm_tp, 0, head->id);
    }
    return NULL;
  }

  case LOCAL_VAR: {
		// case 'var x' in locals
    code_gen(t->left, cur_func);
    return NULL;
  }

  case DEFINITION: {
		// case definition of function (or procedure)

    if (!(p = lookupEntry(t->left->id, LOOKUP_ALL_SCOPES, false))) {
			// if function has no forward declaration
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
			// set name and alloca for every function argument
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
      Builder.CreateStore(&Arg, Alloca);
      p1 = p1->u.eParameter.next;
    }
    if (t->left->k == FUNCTION) {
			// if function then create variable result of type the function's return type for later use
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
    // case 'dispose []'
    l = code_gen(t->left, cur_func);
    auto inst = CallInst::CreateFree(l, Builder.GetInsertBlock());
    Builder.GetInsertBlock()->getInstList().push_back(inst);
    Builder.CreateStore(
        Builder.CreateIntToPtr(c_int(0), find_llvm_type(t->left->type)),
        lvalue_pointer(t->left, cur_func));
    return NULL;
  }

  case DISPOSE: {
		// case 'dispose'
    l = code_gen(t->left, cur_func);
    auto inst = CallInst::CreateFree(l, Builder.GetInsertBlock());
    Builder.GetInsertBlock()->getInstList().push_back(inst);
    Builder.CreateStore(
        Builder.CreateIntToPtr(c_int(0), find_llvm_type(t->left->type)),
        lvalue_pointer(t->left, cur_func));
    return NULL;
  }

  case ID: {
		// case id
    p = lookupEntry(t->id, LOOKUP_ALL_SCOPES, false);
    l = Builder.CreateLoad(p->alloca_inst);
    if (p->entryType == ENTRY_PARAMETER &&
        p->u.eParameter.mode == PASS_BY_REFERENCE)
      l = Builder.CreateLoad(l);
    return l;
  }

  case LABEL: {
    // case declaration of label
    head = t->left;
    while (head) {
      newVariable(head->id, typeLabel);
      head = head->right;
    }
    return NULL;
  }

  case ASSIGN: {
		// case ':='
    l = lvalue_pointer(t->left, cur_func);
		// if rvalue is 'nil'
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
		// case 'return'
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

	case VAR:
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
		// Should not be reached
    error("Unknown error");
    return NULL;
  }
  default: { return NULL; }
  }
}

void generate_code(ast *t) {
	// basic function for generating llvm ir
  TheModule = std::make_unique<Module>("pcl program", TheContext);
  initSymbolTable(256);
  code_gen(t, NULL);
  TheModule->print(outs(), nullptr);
}
