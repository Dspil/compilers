#ifndef __CODE_GEN_H__
#define __CODE_GEN_H__
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "symbol.h"
#include <llvm/IR/Value.h>

using namespace llvm;

void generate_builtins();
Value* code_gen(ast *t, PclType ftype);
void generate_code(ast *t);

#endif
