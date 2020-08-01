#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "symbol.h"
#include "code_gen.hpp"

#include <llvm/IR/IRBuilder.h>
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/Function.h"
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

// Useful LLVM types.
static Type * i1 = IntegerType::get(TheContext, 1);
static Type * i8 = IntegerType::get(TheContext, 8);
static Type * i32 = IntegerType::get(TheContext, 32);
static Type * i64 = IntegerType::get(TheContext, 64);
static Type * f64 = Type::getDoubleTy(TheContext);
static Type * proc = Type::getVoidTy(TheContext);

// Useful LLVM helper functions.
inline ConstantInt* c_bool(bool b) {
  return ConstantInt::get(TheContext, APInt(1, b, true));
}
inline ConstantInt* c_char(char c) {
  return ConstantInt::get(TheContext, APInt(8, c, true));
}
inline ConstantInt* c_int(int n) {
  return ConstantInt::get(TheContext, APInt(32, n, true));
}
inline ConstantFP* c_real(double n) {
  return ConstantFP::get(TheContext, APFloat(n));
}

Type* find_llvm_type(PclType tp) {
	//printf("megethos1 %d\n", tp->size);
	switch(tp->kind) {
		case TYPE_INTEGER:{
			return i32;
		}
		case TYPE_CHAR:{
			return i8;
		}
		case TYPE_BOOLEAN:{
			return i1;
		}
		case TYPE_REAL:{
			return f64;
		}
		case TYPE_VOID:{
			return proc;
		}
		case TYPE_ARRAY:
		case TYPE_IARRAY:{
			return ArrayType::get(find_llvm_type(tp->refType), tp->size);
		}
		case TYPE_POINTER:{
			return find_llvm_type(tp->refType)->getPointerTo();
		}
	}
}

void generate_builtins() {
	SymbolEntry * p;
	Function * f;
	FunctionType * tp;

  	p = newFunction("writeInteger");
  	openScope();
  	newParameter("n", typeInteger, PASS_BY_VALUE, p);
  	endFunctionHeader(p, typeVoid);
  	tp = FunctionType::get(proc, std::vector<Type *>{i32}, false);
	f = Function::Create(tp, Function::ExternalLinkage, "writeInteger", TheModule.get());
	p->u.eFunction.llvmFunc = f;
  	closeScope();

	p = newFunction("writeBoolean");
	openScope();
	newParameter("b", typeBoolean, PASS_BY_VALUE, p);
	endFunctionHeader(p, typeVoid);
	tp = FunctionType::get(proc, std::vector<Type *>{i1}, false);
	f = Function::Create(tp, Function::ExternalLinkage, "writeBoolean", TheModule.get());
	p->u.eFunction.llvmFunc = f;
	closeScope();

	p = newFunction("writeChar");
	openScope();
	newParameter("c", typeChar, PASS_BY_VALUE, p);
	endFunctionHeader(p, typeVoid);
	tp = FunctionType::get(proc, std::vector<Type *>{i8}, false);
	f = Function::Create(tp, Function::ExternalLinkage, "writeChar", TheModule.get());
	p->u.eFunction.llvmFunc = f;
	closeScope();

	p = newFunction("writeReal");
	openScope();
	newParameter("r", typeReal, PASS_BY_VALUE, p);
	endFunctionHeader(p, typeVoid);
	tp = FunctionType::get(proc, std::vector<Type *>{f64}, false);
	f = Function::Create(tp, Function::ExternalLinkage, "writeReal", TheModule.get());
	p->u.eFunction.llvmFunc = f;
	closeScope();

	p = newFunction("writeString");
	openScope();
	newParameter("s", typeIArray(typeChar), PASS_BY_REFERENCE, p);
	endFunctionHeader(p, typeVoid);
	tp = FunctionType::get(proc, std::vector<Type *>{ArrayType::get(i8, 0)->getPointerTo()}, false);
	f = Function::Create(tp, Function::ExternalLinkage, "writeString", TheModule.get());
	p->u.eFunction.llvmFunc = f;
	closeScope();

	p = newFunction("abs");
	openScope();
	newParameter("n", typeInteger, PASS_BY_VALUE, p);
	endFunctionHeader(p, typeInteger);
	tp = FunctionType::get(i32, std::vector<Type *>{i32}, false);
	f = Function::Create(tp, Function::ExternalLinkage, "abs", TheModule.get());
	p->u.eFunction.llvmFunc = f;
	closeScope();

	p = newFunction("fabs");
	openScope();
	newParameter("r", typeReal, PASS_BY_VALUE, p);
	endFunctionHeader(p, typeReal);
	tp = FunctionType::get(f64, std::vector<Type *>{f64}, false);
	f = Function::Create(tp, Function::ExternalLinkage, "fabs", TheModule.get());
	p->u.eFunction.llvmFunc = f;
	closeScope();

	p = newFunction("sqrt");
	openScope();
	newParameter("r", typeReal, PASS_BY_VALUE, p);
	endFunctionHeader(p, typeReal);
	tp = FunctionType::get(f64, std::vector<Type *>{f64}, false);
	f = Function::Create(tp, Function::ExternalLinkage, "sqrt", TheModule.get());
	p->u.eFunction.llvmFunc = f;
	closeScope();

	p = newFunction("sin");
	openScope();
	newParameter("r", typeReal, PASS_BY_VALUE, p);
	endFunctionHeader(p, typeReal);
	tp = FunctionType::get(f64, std::vector<Type *>{f64}, false);
	f = Function::Create(tp, Function::ExternalLinkage, "sin", TheModule.get());
	p->u.eFunction.llvmFunc = f;
	closeScope();

	p = newFunction("cos");
	openScope();
	newParameter("r", typeReal, PASS_BY_VALUE, p);
	endFunctionHeader(p, typeReal);
	tp = FunctionType::get(f64, std::vector<Type *>{f64}, false);
	f = Function::Create(tp, Function::ExternalLinkage, "cos", TheModule.get());
	p->u.eFunction.llvmFunc = f;
	closeScope();

	p = newFunction("tan");
	openScope();
	newParameter("r", typeReal, PASS_BY_VALUE, p);
	endFunctionHeader(p, typeReal);
	tp = FunctionType::get(f64, std::vector<Type *>{f64}, false);
	f = Function::Create(tp, Function::ExternalLinkage, "tan", TheModule.get());
	p->u.eFunction.llvmFunc = f;
	closeScope();

	p = newFunction("arctan");
	openScope();
	newParameter("r", typeReal, PASS_BY_VALUE, p);
	endFunctionHeader(p, typeReal);
	tp = FunctionType::get(f64, std::vector<Type *>{f64}, false);
	f = Function::Create(tp, Function::ExternalLinkage, "arctan", TheModule.get());
	p->u.eFunction.llvmFunc = f;
	closeScope();

	p = newFunction("exp");
	openScope();
	newParameter("r", typeReal, PASS_BY_VALUE, p);
	endFunctionHeader(p, typeReal);
	tp = FunctionType::get(f64, std::vector<Type *>{f64}, false);
	f = Function::Create(tp, Function::ExternalLinkage, "exp", TheModule.get());
	p->u.eFunction.llvmFunc = f;
	closeScope();

	p = newFunction("ln");
	openScope();
	newParameter("r", typeReal, PASS_BY_VALUE, p);
	endFunctionHeader(p, typeReal);
	tp = FunctionType::get(f64, std::vector<Type *>{f64}, false);
	f = Function::Create(tp, Function::ExternalLinkage, "ln", TheModule.get());
	p->u.eFunction.llvmFunc = f;
	closeScope();

	p = newFunction("pi");
	openScope();
	endFunctionHeader(p, typeReal);
	tp = FunctionType::get(f64, std::vector<Type *>{}, false);
	f = Function::Create(tp, Function::ExternalLinkage, "pi", TheModule.get());
	p->u.eFunction.llvmFunc = f;
	closeScope();

	p = newFunction("trunc");
	openScope();
	newParameter("r", typeReal, PASS_BY_VALUE, p);
	endFunctionHeader(p, typeInteger);
	tp = FunctionType::get(i32, std::vector<Type *>{f64}, false);
	f = Function::Create(tp, Function::ExternalLinkage, "trunc2", TheModule.get());
	p->u.eFunction.llvmFunc = f;
	closeScope();

	p = newFunction("round");
	openScope();
	newParameter("r", typeReal, PASS_BY_VALUE, p);
	endFunctionHeader(p, typeInteger);
	tp = FunctionType::get(i32, std::vector<Type *>{f64}, false);
	f = Function::Create(tp, Function::ExternalLinkage, "round2", TheModule.get());
	p->u.eFunction.llvmFunc = f;
	closeScope();

	p = newFunction("ord");
	openScope();
	newParameter("c", typeChar, PASS_BY_VALUE, p);
	endFunctionHeader(p, typeInteger);
	tp = FunctionType::get(i32, std::vector<Type *>{i8}, false);
	f = Function::Create(tp, Function::ExternalLinkage, "ord", TheModule.get());
	p->u.eFunction.llvmFunc = f;
	closeScope();

	p = newFunction("chr");
	openScope();
	newParameter("n", typeInteger, PASS_BY_VALUE, p);
	endFunctionHeader(p, typeChar);
	tp = FunctionType::get(i8, std::vector<Type *>{i32}, false);
	f = Function::Create(tp, Function::ExternalLinkage, "chr", TheModule.get());
	p->u.eFunction.llvmFunc = f;
	closeScope();

	p = newFunction("readInteger");
	openScope();
	endFunctionHeader(p, typeInteger);
	tp = FunctionType::get(i32, std::vector<Type *>{}, false);
	f = Function::Create(tp, Function::ExternalLinkage, "readInteger", TheModule.get());
	p->u.eFunction.llvmFunc = f;
	closeScope();

	p = newFunction("readBoolean");
	openScope();
	endFunctionHeader(p, typeBoolean);
	tp = FunctionType::get(i1, std::vector<Type *>{}, false);
	f = Function::Create(tp, Function::ExternalLinkage, "readBoolean", TheModule.get());
	p->u.eFunction.llvmFunc = f;
	closeScope();

	p = newFunction("readChar");
	openScope();
	endFunctionHeader(p, typeChar);
	tp = FunctionType::get(i8, std::vector<Type *>{}, false);
	f = Function::Create(tp, Function::ExternalLinkage, "readChar", TheModule.get());
	p->u.eFunction.llvmFunc = f;
	closeScope();

	p = newFunction("readReal");
	openScope();
	endFunctionHeader(p, typeReal);
	tp = FunctionType::get(f64, std::vector<Type *>{}, false);
	f = Function::Create(tp, Function::ExternalLinkage, "readReal", TheModule.get());
	p->u.eFunction.llvmFunc = f;
	closeScope();


	p = newFunction("readString");
	openScope();
	newParameter("size", typeInteger, PASS_BY_VALUE, p);
	newParameter("s", typeIArray(typeChar), PASS_BY_REFERENCE, p);
	endFunctionHeader(p, typeVoid);
	tp = FunctionType::get(proc, std::vector<Type *>{i32, ArrayType::get(i8, 0)->getPointerTo()}, false);
	f = Function::Create(tp, Function::ExternalLinkage, "readString", TheModule.get());
	p->u.eFunction.llvmFunc = f;
	closeScope();

	p = newFunction("cMalloc");
	openScope();
	newParameter("s", typeInteger, PASS_BY_VALUE, p);
	endFunctionHeader(p, typeInteger);
	tp = FunctionType::get(i32, std::vector<Type *>{i64}, false);
	f = Function::Create(tp, Function::ExternalLinkage, "cMalloc", TheModule.get());
	p->u.eFunction.llvmFunc = f;
	closeScope();

}

Value* lvalue_pointer(ast * t, Function* cur_func) {
	SymbolEntry * p;
	Value *l, *r;
	AllocaInst *Alloca;
	switch (t->k){
		case ID: {
			p = lookupEntry(t->id, LOOKUP_ALL_SCOPES, false);
			if (p->entryType == ENTRY_PARAMETER && p->u.eParameter.mode == PASS_BY_REFERENCE)
				return Builder.CreateLoad(p->alloca_inst);
			return p->alloca_inst;
		}
		case RESULT: {
			p = lookupEntry("result", LOOKUP_ALL_SCOPES, false);
			return p->alloca_inst;
		}
		case INDEX: {
			if(t->left->k)
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
		default: {
			return NULL;
		}
	}
	/* error */
	return NULL;
}

void prepareFunctionSymbolTable(ast *t){
	//printf("in proc\n");
	PassMode pass_type;
	ast *head, *head1;
	PclType tp;
	t->sentry = newFunction(t->id);

	openScope();
	if (t->left) { //t->left : seq_formal (parameters)
		head = t->left; //seq_formal
		while (head) {
		//printf("in while\n");
			tp = head->left->right->type;
			pass_type = head->left->k == VARREF ? PASS_BY_REFERENCE : PASS_BY_VALUE;
			head1 = head->left->left;
			while (head1) {
				//printf("in while2\n");
				newParameter(head1->id, tp, pass_type, t->sentry);
				head1 = head1->right;
			  //printf("out while2\n");
			}
			//printf("out while\n");
			head = head->right;
		}
		//printf("outproc\n");
	}
	//printf("found type\n");
	endFunctionHeader(t->sentry, t->type);
}

Value* code_gen(ast * t, Function* cur_func) {
	SymbolEntry *p, *p1;
    ast *head, *head1;
    PclType tp;
	Type* llvm_tp;
	Function * f;
	FunctionType * f_tp;
	Value *l, *m, *r;
	BasicBlock *lBB, *mBB, *rBB;
	std::vector<Type *> params = std::vector<Type *>();
	AllocaInst *Alloca;

	//printf("%d %s\n", t->k, t->id);
	//printSymbolTable();
    if (!t) {
      return NULL;
    }

    switch (t->k) {

    case AND: {
		l = code_gen(t->left, cur_func);
		r = code_gen(t->right, cur_func);
		return Builder.CreateAnd(l, r);
	}

    case OR: {
		l = code_gen(t->left, cur_func);
		r = code_gen(t->right, cur_func);
		return Builder.CreateOr(l, r);
	}

    case BLOCK:{
		//printf("in block\n");
		code_gen(t->left, cur_func);
		//printf("out block\n");
		return NULL;
	}

    case BODY:{
		//printf("in body\n");
		if(t->left) code_gen(t->left, cur_func);
		//printf("ran t->left\n");
		code_gen(t->right, cur_func);
		//printf("out body\n");
		return NULL;
	}

    case BOOL_CONST: {
		return c_bool(t->boolean);
	}

    case CHAR_CONST:{
		//printf("char: %c\n", t->character);
		l = c_char(t->character);
		return l;
	}

    case DIV:{
		l = code_gen(t->left, cur_func);
		r = code_gen(t->right, cur_func);
		return Builder.CreateSDiv(l, r);
	}

    case MOD:{
		l = code_gen(t->left, cur_func);
		r = code_gen(t->right, cur_func);
		return Builder.CreateSRem(l, r);
	}

    case FORWARD:{
		code_gen(t->left, cur_func);
		forwardFunction(t->left->sentry);
		closeScope();
	    return NULL;
	}

    case GOTO:{
		//printf("in goto\n");
		p = lookupEntry(t->str, LOOKUP_CURRENT_SCOPE, false);
		if(p->u.eVariable.block) {
			//printf("lookedup in goto\n");
			Builder.CreateBr(p->u.eVariable.block);
			//printf("made break\n");
			return NULL;
		}
		else {
			//printf("edo\n");
			p->u.eVariable.goto_stack.push_back(&cur_func->getBasicBlockList().back());
			lBB = BasicBlock::Create(TheContext, "help", cur_func);
			Builder.SetInsertPoint(lBB);
			return NULL;
		}
		return NULL;
	}

    case IF:{
		l = code_gen(t->left, cur_func);
		lBB = BasicBlock::Create(TheContext, "then", cur_func);
		mBB = BasicBlock::Create(TheContext, "else");
		rBB = BasicBlock::Create(TheContext, "merge");
		//printf("made basic blocks\n");
		Builder.CreateCondBr(l, lBB, mBB);
		//printf("made first branch\n");

		Builder.SetInsertPoint(lBB);
		//printf("made insert point\n");
		code_gen(t->mid, cur_func);
		//printf("code gen mid\n");
		Builder.CreateBr(rBB);
		//printf("made break\n");

		cur_func->getBasicBlockList().push_back(mBB);
		//printf("first push back\n");
		Builder.SetInsertPoint(mBB);
		//printf("made 2 insert point\n");
		if(t->right){
			code_gen(t->right, cur_func);
			//printf("code gen else\n");
		}
		Builder.CreateBr(rBB);
		//printf("second branch\n");
		cur_func->getBasicBlockList().push_back(rBB);
		Builder.SetInsertPoint(rBB);
		return NULL;
	}

    case INT_CONST:{
		//printf("in int_const %d\n", t->integer);
		return c_int(t->integer);
	}

    case NEW: {
		//printf("in new\n");
		p = lookupEntry("cMalloc", LOOKUP_ALL_SCOPES, false);
		if(!p) printf("oups\n");
		r = lvalue_pointer(t->right, cur_func);
		if(t->left) {
			//printf("in new1\n");
			l = code_gen(t->left, cur_func);
			//printf("in new2\n");
			//printf("prin\n");
			m = Builder.CreateIntToPtr(c_int(0), find_llvm_type(t->right->type->refType->refType)->getPointerTo());
			//printf("meta\n");
			m = Builder.CreateGEP(m, c_int(1));
			m = Builder.CreatePtrToInt(m, i32);
			m = Builder.CreateMul(l, m);
			m = Builder.CreateZExt(m, i64);
			m = Builder.CreateCall(p->u.eFunction.llvmFunc, std::vector<Value *>{m});
			m = Builder.CreateIntToPtr(m, find_llvm_type(t->right->type->refType)->getPointerTo());
			//printf("shit\n");
			Builder.CreateStore(m, r);
			//Builder.CreateStore(Builder.CreateAlloca(find_llvm_type(t->right->type->refType), l), r);
			//printf("in new3\n");
		}
		else {
			m = Builder.CreateIntToPtr(c_int(0), find_llvm_type(t->right->type));
			//printf("meta\n");
			m = Builder.CreateGEP(m, c_int(1));
			m = Builder.CreatePtrToInt(m, i64);
			m = Builder.CreateCall(p->u.eFunction.llvmFunc, std::vector<Value *>{m});
			m = Builder.CreateIntToPtr(m, find_llvm_type(t->right->type));
			//printf("shit\n");
			Builder.CreateStore(m, r);
			//printf("in new4\n");
			//Builder.CreateMalloc(cur_func->getBasicBlockList().back(), NULL, find_llvm_type(t->right->type->refType), NULL, l, NULL, cur_func);
			//Builder.CreateStore(Builder.CreateAlloca(find_llvm_type(t->right->type->refType), 0, "newtmp"), r);
			//printf("in new5\n");
		}
		//printf("out new\n");
    	return NULL;
	}

    case NOT:{
		l = code_gen(t->left, cur_func);
		return Builder.CreateNot(l);
	}

	case FUNCTION:
    case PROCEDURE: {
		//printf("in proc\n");
		prepareFunctionSymbolTable(t);
		//printf("mesa\n");
		p1 = t->sentry->u.eFunction.firstArgument;
		//printf("mesa1\n");
		if (t->left) { //t->left : seq_formal (parameters)
			head = t->left; //seq_formal
			while (head) {
			//printf("in while\n");
				llvm_tp = find_llvm_type(head->left->right->type);
				if (p1->u.eParameter.mode == PASS_BY_REFERENCE) llvm_tp = llvm_tp->getPointerTo();
				head1 = head->left->left;
				while (head1) {
					//printf("in while2\n");
					params.push_back(llvm_tp);
					head1 = head1->right;
					p1 = p1->u.eParameter.next;
				  	//printf("out while2\n");
				}
				//printf("out while\n");
				head = head->right;
			}
			//printf("outproc\n");
		}
		//printf("found type\n");
		//printf("made header\n");
		f_tp = FunctionType::get(find_llvm_type(t->type), params, false);
		//printf("found llvmtype\n");
		f = Function::Create(f_tp, Function::InternalLinkage, t->id, TheModule.get());
		//printf("made func\n");
		t->sentry->u.eFunction.llvmFunc = f;
		//printf("wtf?\n");
		return NULL;
	}

    case PROGRAM:{
		//printf("in program\n");
		openScope();
		generate_builtins();
		f_tp = FunctionType::get(i32, std::vector<llvm::Type *>{}, false);
	 	f = llvm::Function::Create(f_tp, llvm::Function::ExternalLinkage, "main", TheModule.get());
		BasicBlock *BB = BasicBlock::Create(TheContext, "entry", f);
		Builder.SetInsertPoint(BB);
		//printf("before run tleft\n");
		code_gen(t->left, f);
		//printf("ran tleft\n");
		Builder.CreateRet(c_int(0));
		//printSymbolTable();
		//printf("out createret\n");
		closeScope();
		//printf("closed scope\n");
		TheFPM = std::make_unique<legacy::FunctionPassManager>(TheModule.get());
	    TheFPM->add(createPromoteMemoryToRegisterPass());
	    TheFPM->add(createInstructionCombiningPass());
	    TheFPM->add(createReassociatePass());
	    TheFPM->add(createGVNPass());
	    TheFPM->add(createCFGSimplificationPass());
	    TheFPM->doInitialization();
		//TheFPM->run(*f);
		//printf("ran\n");
		return NULL;
	}

    case REAL_CONST:{
      	return c_real(t->real);
	}

    case RESULT: {
      return NULL;
  }

    case VAR:{
		return NULL;
	}

    case WHILE:{
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
		if(t->left->type->kind == TYPE_INTEGER && t->right->type->kind == TYPE_REAL) {
			l = Builder.CreateCast(Instruction::SIToFP, l, f64);
			return Builder.CreateFCmpONE(l, r);
		}
		else if(t->right->type->kind == TYPE_INTEGER && t->left->type->kind == TYPE_REAL) {
			r = Builder.CreateCast(Instruction::SIToFP, r, f64);
			return Builder.CreateFCmpONE(l, r);
		}
		else if(t->right->type->kind == TYPE_REAL && t->left->type->kind == TYPE_REAL) {
			return Builder.CreateFCmpONE(l, r);
		}
		return Builder.CreateICmpNE(l, r);
	}

    case EQ:{
		l = code_gen(t->left, cur_func);
		r = code_gen(t->right, cur_func);
		if(t->left->type->kind == TYPE_INTEGER && t->right->type->kind == TYPE_REAL) {
			l = Builder.CreateCast(Instruction::SIToFP, l, f64);
			return Builder.CreateFCmpOEQ(l, r);
		}
		else if(t->right->type->kind == TYPE_INTEGER && t->left->type->kind == TYPE_REAL) {
			r = Builder.CreateCast(Instruction::SIToFP, r, f64);
			return Builder.CreateFCmpOEQ(l, r);
		}
		else if(t->right->type->kind == TYPE_REAL && t->left->type->kind == TYPE_REAL) {
			return Builder.CreateFCmpOEQ(l, r);
		}
		return Builder.CreateICmpEQ(l, r);
	}

    case GEQ:{
		l = code_gen(t->left, cur_func);
		r = code_gen(t->right, cur_func);
		if(t->left->type->kind == TYPE_INTEGER && t->right->type->kind == TYPE_REAL) {
			l = Builder.CreateCast(Instruction::SIToFP, l, f64);
			return Builder.CreateFCmpOGE(l, r);
		}
		else if(t->right->type->kind == TYPE_INTEGER && t->left->type->kind == TYPE_REAL) {
			r = Builder.CreateCast(Instruction::SIToFP, r, f64);
			return Builder.CreateFCmpOGE(l, r);
		}
		else if(t->right->type->kind == TYPE_REAL && t->left->type->kind == TYPE_REAL) {
			return Builder.CreateFCmpOGE(l, r);
		}
		return Builder.CreateICmpSGE(l, r);
	}

    case LEQ:{
		l = code_gen(t->left, cur_func);
		r = code_gen(t->right, cur_func);
		if(t->left->type->kind == TYPE_INTEGER && t->right->type->kind == TYPE_REAL) {
			l = Builder.CreateCast(Instruction::SIToFP, l, f64);
			return Builder.CreateFCmpOLE(l, r);
		}
		else if(t->right->type->kind == TYPE_INTEGER && t->left->type->kind == TYPE_REAL) {
			r = Builder.CreateCast(Instruction::SIToFP, r, f64);
			return Builder.CreateFCmpOLE(l, r);
		}
		else if(t->right->type->kind == TYPE_REAL && t->left->type->kind == TYPE_REAL) {
			return Builder.CreateFCmpOLE(l, r);
		}
		return Builder.CreateICmpSLE(l, r);
	}

    case LESS:{
		l = code_gen(t->left, cur_func);
		r = code_gen(t->right, cur_func);
		if(t->left->type->kind == TYPE_INTEGER && t->right->type->kind == TYPE_REAL) {
			l = Builder.CreateCast(Instruction::SIToFP, l, f64);
			return Builder.CreateFCmpOLT(l, r);
		}
		else if(t->right->type->kind == TYPE_INTEGER && t->left->type->kind == TYPE_REAL) {
			r = Builder.CreateCast(Instruction::SIToFP, r, f64);
			return Builder.CreateFCmpOLT(l, r);
		}
		else if(t->right->type->kind == TYPE_REAL && t->left->type->kind == TYPE_REAL) {
			return Builder.CreateFCmpOLT(l, r);
		}
		return Builder.CreateICmpSLT(l, r);
	}

    case GREATER:{
		l = code_gen(t->left, cur_func);
		r = code_gen(t->right, cur_func);
		if(t->left->type->kind == TYPE_INTEGER && t->right->type->kind == TYPE_REAL) {
			l = Builder.CreateCast(Instruction::SIToFP, l, f64);
			return Builder.CreateFCmpOGT(l, r);
		}
		else if(t->right->type->kind == TYPE_INTEGER && t->left->type->kind == TYPE_REAL) {
			r = Builder.CreateCast(Instruction::SIToFP, r, f64);
			return Builder.CreateFCmpOGT(l, r);
		}
		else if(t->right->type->kind == TYPE_REAL && t->left->type->kind == TYPE_REAL) {
			return Builder.CreateFCmpOGT(l, r);
		}
		return Builder.CreateICmpSGT(l, r);
	}

    case PLUS:{
		l = code_gen(t->left, cur_func);
		if (!t->right)
			return l;
		r = code_gen(t->right, cur_func);
		if(t->left->type->kind == TYPE_INTEGER && t->right->type->kind == TYPE_REAL) {
			l = Builder.CreateCast(Instruction::SIToFP, l, f64);
			return Builder.CreateFAdd(l, r);
		}
		else if(t->right->type->kind == TYPE_INTEGER && t->left->type->kind == TYPE_REAL) {
			r = Builder.CreateCast(Instruction::SIToFP, r, f64);
			return Builder.CreateFAdd(l, r);
		}
		else if(t->right->type->kind == TYPE_REAL && t->left->type->kind == TYPE_REAL) {
			return Builder.CreateFAdd(l, r);
		}
		return Builder.CreateAdd(l, r);
	}

    case MINUS:{
		l = code_gen(t->left, cur_func);
		if (!t->right)
			if (t->left->type->kind == TYPE_REAL)
				return Builder.CreateFSub(c_real(0.0), l);
			else
				return Builder.CreateSub(c_int(0), l);
		r = code_gen(t->right, cur_func);
		if(t->left->type->kind == TYPE_INTEGER && t->right->type->kind == TYPE_REAL) {
			l = Builder.CreateCast(Instruction::SIToFP, l, f64);
			return Builder.CreateFSub(l, r);
		}
		else if(t->right->type->kind == TYPE_INTEGER && t->left->type->kind == TYPE_REAL) {
			r = Builder.CreateCast(Instruction::SIToFP, r, f64);
			return Builder.CreateFSub(l, r);
		}
		else if(t->right->type->kind == TYPE_REAL && t->left->type->kind == TYPE_REAL) {
			return Builder.CreateFSub(l, r);
		}
		return Builder.CreateSub(l, r);
	}

    case TIMES: {
		l = code_gen(t->left, cur_func);
		r = code_gen(t->right, cur_func);
		if(t->left->type->kind == TYPE_INTEGER && t->right->type->kind == TYPE_REAL) {
			l = Builder.CreateCast(Instruction::SIToFP, l, f64);
			return Builder.CreateFMul(l, r);
		}
		else if(t->right->type->kind == TYPE_INTEGER && t->left->type->kind == TYPE_REAL) {
			r = Builder.CreateCast(Instruction::SIToFP, r, f64);
			return Builder.CreateFMul(l, r);
		}
		else if(t->right->type->kind == TYPE_REAL && t->left->type->kind == TYPE_REAL) {
			return Builder.CreateFMul(l, r);
		}
		return Builder.CreateMul(l, r);
	}

    case DIVIDE:{
		l = code_gen(t->left, cur_func);
		r = code_gen(t->right, cur_func);
		if(t->left->type->kind == TYPE_INTEGER) {
			l = Builder.CreateCast(Instruction::SIToFP, l, f64);
		}
		if(t->right->type->kind == TYPE_INTEGER) {
			r = Builder.CreateCast(Instruction::SIToFP, r, f64);
		}
		return Builder.CreateFDiv(l, r);
	}

    case DEREF:{
		return Builder.CreateLoad(code_gen(t->left, cur_func));
	}

    case REF:{
		return lvalue_pointer(t->left, cur_func);
	}

    case SEQ_STMT:{
		//printf("in seq_stmt\n");
		for(head = t; head; head = head->right){
			if(!head->left) break;
			code_gen(head->left, cur_func);
			//printf("done with stmt\n");
		}
		//printf("done with everything\n");
		return NULL;
	}

    case STMT:{
		//printf("in stmt\n");
		lBB = BasicBlock::Create(TheContext, "labelb", cur_func);
		Builder.CreateBr(lBB);
		//printf("create block\n");
		p = lookupEntry(t->id, LOOKUP_CURRENT_SCOPE, false);
		//printf("lookedup\n");
		p->u.eVariable.block = lBB;
		std::vector<BasicBlock*> v_blocks = p->u.eVariable.goto_stack;
		while(!v_blocks.empty()){
			Builder.SetInsertPoint(v_blocks.back());
			Builder.CreateBr(lBB);
			v_blocks.pop_back();
		}
		//printf("found block\n");
		Builder.SetInsertPoint(lBB);
		//printf("went there\n");
		code_gen(t->left, cur_func);
		//printf("generate rest\n");
		return NULL;
	}

    case INDEX:{
		return Builder.CreateLoad(lvalue_pointer(t, cur_func));
	}

    case CALL:{
		//printf("in call\n");
		p = lookupEntry(t->id, LOOKUP_ALL_SCOPES, true);
		p1 = p->u.eFunction.firstArgument;
		f = p->u.eFunction.llvmFunc;
		//printf("before call %s\n", t->id);
		//printf("%s\n", p->id);
		std::vector<Value *> params;
  		for(head = t->left; head; head = head->right) {

			if (p1->u.eParameter.mode == PASS_BY_REFERENCE){
				l = lvalue_pointer(head->left, cur_func);
				//printf("megethos2 %d\n", p1->u.eParameter.type->size);
				if(l->getType() != find_llvm_type(p1->u.eParameter.type)->getPointerTo()){
					//printf("edo skatoules\n");
					l = Builder.CreateBitCast(l, find_llvm_type(p1->u.eParameter.type)->getPointerTo());
					//printf("edo skatoules\n");
				}
			}
			else {
				l = code_gen(head->left, cur_func);
			}

			params.push_back(l);
			//printf("pushed back param\n");
			p1 = p1->u.eParameter.next;
		}
		auto ret = Builder.CreateCall(f, params);
		//printf("made call\n");
  		return ret;
	}

    case SEQ_LOCAL:{
		//printf("in seq local\n");
		for(head = t; head; head = head->right) {
			//printf("in seq_local %d\n", head->left->k);
			code_gen(head->left, cur_func);
			//printf("out seq_local %d\n", head->left->k);
		}
		//printf("out seq local\n");
		return NULL;
	}

    case SEQ_LOCAL_VAR:{
		for(head = t; head; head = head->right) {
			//printf("in seq local var %d\n", head->left->k);
			code_gen(head->left, cur_func);
			//printf("out seq local var %d\n", head->left->k);
		}
		return NULL;
	}

    case LOCAL_VAR_INSTANCE:{
		//printf("in local_var_instance %d\n", t->left->k);
		tp = t->right->type;
	    llvm_tp = find_llvm_type(tp);
		//printf("found type\n");
	    for(head = t->left; head; head = head->right){
			p = newVariable(head->id, tp);
			//printf("made variable\n");
			p->alloca_inst = Builder.CreateAlloca(llvm_tp, 0, head->id);
			//printf("alloca\n");
	    }
		//printf("out local_var_instance %d\n", t->left->k);
		return NULL;
	}

    case LOCAL_VAR:{
		//printf("in local var %d\n", t->left->k);
		code_gen(t->left, cur_func);
		//printf("out local var\n");
		return NULL;
	}

    case DEFINITION:{
		if(!(p = lookupEntry(t->left->id, LOOKUP_ALL_SCOPES, false))) {
			code_gen(t->left, cur_func);
			p = t->left->sentry;
		}
		else prepareFunctionSymbolTable(t->left);
		//printf("edo einai\n");
		rBB = &cur_func->getBasicBlockList().back();
		cur_func = p->u.eFunction.llvmFunc;
		lBB = BasicBlock::Create(TheContext, t->left->id, cur_func);
		Builder.SetInsertPoint(lBB);
		p1 = p->u.eFunction.firstArgument;
		//printf("prin apo loop\n");
		for (auto &Arg : cur_func->args()) {
  			Arg.setName(p1->id);
			if(p1->u.eParameter.mode == PASS_BY_REFERENCE) {
				Alloca = Builder.CreateAlloca(find_llvm_type(p1->u.eParameter.type)->getPointerTo(), 0, Arg.getName());
			}
			else {
				Alloca = Builder.CreateAlloca(find_llvm_type(p1->u.eParameter.type), 0, Arg.getName());
			}
			//printf("gamietai\n");
			p1->alloca_inst = Alloca;
			if(Arg.getType() == ArrayType::get(i8, 0)->getPointerTo()->getPointerTo()) printf("ola sosta\n");
			Builder.CreateStore(&Arg, Alloca);
			//printf("eftase\n");
			p1 = p1->u.eParameter.next;
		}
		if (t->left->k == FUNCTION) {
		  p = newVariable("result", t->left->type);
		  p->alloca_inst = Builder.CreateAlloca(find_llvm_type(t->left->type), 0, "result");
		}
		code_gen(t->right, cur_func);
		llvm_tp = cur_func->getReturnType();

		if(llvm_tp->isVoidTy())
			Builder.CreateRetVoid();
		else
			Builder.CreateRet(Builder.CreateLoad(lookupEntry("result", LOOKUP_CURRENT_SCOPE, false)->alloca_inst));
		Builder.SetInsertPoint(rBB);
		closeScope();
		//printf("ola kala\n");
		return NULL;
	}

    case DISPOSE_ARRAY:{
		//printf("in\n");
		l = code_gen(t->left, cur_func);
		auto inst = CallInst::CreateFree(l, Builder.GetInsertBlock());
		Builder.GetInsertBlock()->getInstList().push_back(inst);
		Builder.CreateStore(Builder.CreateIntToPtr(c_int(0), find_llvm_type(t->left->type)), lvalue_pointer(t->left, cur_func));
    	return NULL;
	}

	case DISPOSE:{
		l = code_gen(t->left, cur_func);
		auto inst = CallInst::CreateFree(l, Builder.GetInsertBlock());
		Builder.GetInsertBlock()->getInstList().push_back(inst);
		Builder.CreateStore(Builder.CreateIntToPtr(c_int(0), find_llvm_type(t->left->type)), lvalue_pointer(t->left, cur_func));
    	return NULL;
	}

    case ID:{
		p = lookupEntry(t->id, LOOKUP_ALL_SCOPES, false);
		l = Builder.CreateLoad(p->alloca_inst);
		if (p->entryType == ENTRY_PARAMETER && p->u.eParameter.mode == PASS_BY_REFERENCE) l = Builder.CreateLoad(l);
		return l;
	}

    case LABEL:{
		//printf("inlabel\n");
		head = t->left;
	    while (head) {
	      newVariable(head->id, typeLabel);
	      head = head->right;
	    }
		//printf("outlabel\n");
	    return NULL;
	}

    case ASSIGN:{
		//printf("in assign\n");
		r = code_gen(t->right, cur_func);
		l = lvalue_pointer(t->left, cur_func);
		if (t->left->type->kind == TYPE_REAL && t->right->type->kind == TYPE_INTEGER) r = Builder.CreateCast(Instruction::SIToFP, r, f64);
		Builder.CreateStore(r, l);
		return NULL;
	}

    case RETURN: {
		llvm_tp = cur_func->getReturnType();
		if(llvm_tp->isVoidTy())
			Builder.CreateRetVoid();
		else
			Builder.CreateRet(Builder.CreateLoad(lookupEntry("result", LOOKUP_CURRENT_SCOPE, false)->alloca_inst));
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
	case NIL:{
		printf("oups %d\n", t->k);
		return NULL;
	}
	default:{
		return NULL;
	}
	}
    return NULL;
}

void generate_code(ast *t) {
	TheModule = std::make_unique<Module>("pcl program", TheContext);
	initSymbolTable(256);
	Value *ret = code_gen(t, NULL);
    TheModule->print(outs(), nullptr);
}
