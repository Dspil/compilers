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

// Useful LLVM types.
static Type * i8 = IntegerType::get(TheContext, 8);
static Type * i32 = IntegerType::get(TheContext, 32);
static Type * f64 = Type::getDoubleTy(TheContext);
static Type * proc = Type::getVoidTy(TheContext);

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
inline ConstantFP* c_real(double n) {
  return ConstantFP::get(TheContext, APFloat(n));
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
	tp = FunctionType::get(proc, std::vector<Type *>{i8}, false);
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
	tp = FunctionType::get(proc, std::vector<Type *>{i8->getPointerTo()}, false);
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
	f = Function::Create(tp, Function::ExternalLinkage, "trunc", TheModule.get());
	p->u.eFunction.llvmFunc = f;
	closeScope();

	p = newFunction("round");
	openScope();
	newParameter("r", typeReal, PASS_BY_VALUE, p);
	endFunctionHeader(p, typeInteger);
	tp = FunctionType::get(i32, std::vector<Type *>{f64}, false);
	f = Function::Create(tp, Function::ExternalLinkage, "round", TheModule.get());
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
	tp = FunctionType::get(i8, std::vector<Type *>{}, false);
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
	tp = FunctionType::get(proc, std::vector<Type *>{i32, i8->getPointerTo()}, false);
	f = Function::Create(tp, Function::ExternalLinkage, "readString", TheModule.get());
	p->u.eFunction.llvmFunc = f;
	closeScope();
}

Value* code_gen(ast * t, PclType ftype) {
	SymbolEntry *p, *p1;
    ast *head, *head1;
    PclType tp;
    PassMode pass_type;
	Function * f;
	FunctionType * f_tp;

    if (!t) {
      return NULL;
    }
    switch (t->k) {

    case AND:
    case OR:
      break;

    case IARRAY:
      break;

    case ARRAY:
      break;

    case BLOCK:{
		//printf("in block\n");
		code_gen(t->left, ftype);
		return NULL;
	}

    case BODY:{
		//printf("in body\n");
		if(t->left) code_gen(t->left, ftype);
		code_gen(t->right, ftype);
		return NULL;
	}

    case BOOL:
		break;
    case BOOL_CONST:
	  	return c_bool(t->boolean);

    case CHAR:
		break;
    case CHAR_CONST:{
		//printf("char: %c\n", t->character);
		return c_char(t->character);
	}

    case DISPOSE:
      break;

    case DIV:
    case MOD:
      break;

    case FORWARD:
      break;

    case GOTO:
      break;

    case IF:
      break;

    case INT:
		break;
    case INT_CONST:{
		//printf("in int_const\n");
		return c_int(t->integer);
	}

    case NEW:
      break;

    case NIL:
      break;

    case NOT:
      break;

    case PROCEDURE:
      break;

    case FUNCTION:
      break;

    case PROGRAM:{
		//printf("in program\n");
		openScope();
		generate_builtins();
		f_tp = FunctionType::get(i32, std::vector<llvm::Type *>{}, false);
	 	f = llvm::Function::Create(f_tp, llvm::Function::ExternalLinkage, "main", TheModule.get());
		BasicBlock *BB = BasicBlock::Create(TheContext, "entry", f);
		Builder.SetInsertPoint(BB);
		code_gen(t->left, ftype);
		Builder.CreateRet(c_int(0));
		closeScope();
		TheFPM = std::make_unique<legacy::FunctionPassManager>(TheModule.get());
	    TheFPM->add(createPromoteMemoryToRegisterPass());
	    TheFPM->add(createInstructionCombiningPass());
	    TheFPM->add(createReassociatePass());
	    TheFPM->add(createGVNPass());
	    TheFPM->add(createCFGSimplificationPass());
	    TheFPM->doInitialization();
		TheFPM->run(*f);
		return NULL;
	}

    case REAL:{
		break;
	}
    case REAL_CONST:{

      	return c_real(t->real);
	}

    case RESULT:
      break;

    case VAR:
      break;

    case WHILE:
      break;

    case STR_CONST:
      break;

    case NEQ:
    case EQ:
      break;

    case GEQ:
    case LEQ:
    case LESS:
    case GREATER:
      break;

    case PLUS:
    case MINUS:
    case TIMES:
      break;

    case DIVIDE:
      break;

    case DEREF:
      break;

    case REF:
      break;

    case SEQ_EXPR:
		break;

    case SEQ_STMT:{
		//printf("in seq_stmt\n");
		for(head = t; head; head = head->right){
			code_gen(head->left, ftype);
			//printf("done with stmt\n");
		}
		return NULL;
	}

    case STMT:
      break;

    case INDEX:
      break;

    case CALL:{
		//printf("in call\n");
		p = lookupEntry(t->id, LOOKUP_ALL_SCOPES, true);
		f = p->u.eFunction.llvmFunc;
		std::vector<Value *> params;
  		for(head = t->left; head; head = head->right) {
			params.push_back(code_gen(head->left, ftype));
			//printf("pushed back param\n");
		}
		auto ret = Builder.CreateCall(f, params);
		//printf("made call\n");
  		return ret;
	}

    case SEQ_LOCAL:
      break;

    case SEQ_LOCAL_VAR:
      break;

    case LOCAL_VAR_INSTANCE:
      break;

    case LOCAL_VAR:
      break;

    case DEFINITION:
      break;

    case SEQ_FORMAL:
      break;

    case VARREF:
      break;

    case DISPOSE_ARRAY:
      break;

    case ID:
      break;

    case LABEL:
      break;

    case ASSIGN:
      break;

    case POINTER:
      break;

    case SEQ_ID:
      break;

    case RETURN:
      break;
    }
    return NULL;
}

void generate_code(ast *t) {
	TheModule = std::make_unique<Module>("pcl program", TheContext);
	initSymbolTable(256);
	Value *ret = code_gen(t, NULL);
    TheModule->print(outs(), nullptr);
}
