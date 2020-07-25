#ifndef __CODE_GEN_H__
#define __CODE_GEN_H__
#include "ast.h"

void generate_builtins();
int code_gen(ast * t);

#endif
