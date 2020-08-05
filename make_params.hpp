#ifndef __MAKE_PARAMS_H__
#define __MAKE_PARAMS_H__
#include "ast_symbol.h"

int make_params(ast *t, PclType ftype);
int make_parameters(ast *t);
ast *find_ast_type(PclType tp);

#endif
