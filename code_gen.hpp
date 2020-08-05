#ifndef __CODE_GEN_H__
#define __CODE_GEN_H__
#include "ast_symbol.h"
#include <llvm/IR/Value.h>
#include <stdio.h>
#include <stdlib.h>

using namespace llvm;

Type *find_llvm_type(PclType tp);
void generate_builtins();
Value *code_gen(ast *t, Function *cur_func);
Value *lvalue_pointer(ast *t, Function *cur_func);
void generate_code(ast *t);

#endif
