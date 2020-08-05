#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "ast_symbol.h"

ast* find_ast_type(PclType tp){
	switch(tp->kind) {
		case TYPE_INTEGER: {
			return ast_type(INT, -1, NULL);
		}
		case TYPE_REAL: {
			return ast_type(REAL, -1, NULL);
		}
		case TYPE_BOOLEAN: {
			return ast_type(BOOL, -1, NULL);
		}
		case TYPE_CHAR: {
			return ast_type(CHAR, -1, NULL);
		}
		case TYPE_ARRAY: {
			return ast_type(ARRAY, tp->size, find_ast_type(tp->refType));
		}
		case TYPE_IARRAY: {
			return ast_type(IARRAY, 0, find_ast_type(tp->refType));
		}
		case TYPE_POINTER: {
			return ast_type(ARRAY, -1, find_ast_type(tp->refType));
		}
		default: {
			printf("Unknown error!\n");
			return NULL;
		}
	}
}

int make_params(ast * t, SymbolEntry* cur_func) {
	SymbolEntry *p, *p1;
	PclType tp;
	PassMode pass_type;
	ast * head, * head1;
	int ret, ret2, ret3, flag;

	if (!t) {		//Should not be reached
		printf("Unknown Error\n");
		return 1;
	}
	//printf("%d %s\n", t->k, t->id);


	switch (t->k) {

	case AND:
	case OR:
	case DIV:
	case MOD:
	case NEQ:
	case EQ:
	case GEQ:
	case LEQ:
	case LESS:
	case GREATER:
	case PLUS:
	case MINUS:
	case TIMES:
	case DIVIDE:
	case WHILE:
	case INDEX:
	case DISPOSE:
	case BLOCK:
	case BODY:
	case IF:
	case NEW:
	case NOT:
	case VAR:
	case DEREF:
	case REF:
	case DISPOSE_ARRAY:
	case VARREF:
	case LOCAL_VAR:
	case ASSIGN:
	case STMT:
	{
		ret = (t->left && make_params(t->left, cur_func));
		ret2 = (t->right && make_params(t->right, cur_func));
		ret3 = (t->mid && make_params(t->mid, cur_func));
		return ret || ret2 || ret3;
	}


	case IARRAY:
	case ARRAY:
	case BOOL:
	case BOOL_CONST:
	case CHAR:
	case CHAR_CONST:
	case INT:
	case INT_CONST:
	case REAL:
	case REAL_CONST:
	case RESULT:
	case STR_CONST:
	case LABEL:
	case NIL:
	case GOTO:
	case POINTER:
	{
		return 0;
	}


	case FORWARD:
	if (make_params(t->left, cur_func)) return 1;
	forwardFunction(t->left->sentry);
	t->left->sentry->u.eFunction.forward_decl = t;
	closeScope();
	break;


	case PROCEDURE:
	case FUNCTION: {
		//printf("in1\n");
	t->sentry = newFunction(t->id);
	//printf("in2\n");
	openScope();
	//printf("in3\n");
	if (t->left) { //t->left : seq_formal (parameters)
		//printf("in4\n");
	  head = t->left; //seq_formal
	  //printf("in5\n");
	  while (head) {
		  //printf("in6\n");
	    tp = head->left->right->type;
		//printf("%d %d\n", head->left->k, head->left->right->k);
		//printf("in7\n");
	  	pass_type = head->left->k == VARREF ? PASS_BY_REFERENCE : PASS_BY_VALUE;
		//printf("in8\n");
	  	head1 = head->left->left;
		//printf("in9\n");
	  	while (head1) {
	  	  newParameter(head1->id, tp, pass_type, t->sentry);
		  //printf("in11\n");
	  	  head1 = head1->right;
		  //printf("in12\n");
	  	}
		//printf("in13\n");
	  	head = head->right;
	  }
	}
	//printf("in14\n");
	endFunctionHeader(t->sentry, t->type);
	return 0;
}

	case PROGRAM: {
	openScope();
	define_builtins();
	ret = make_params(t->left, NULL);
	closeScope();
	return ret;
	}


	case SEQ_EXPR:
	case SEQ_FORMAL:
	case SEQ_LOCAL:
	case SEQ_LOCAL_VAR:
	case SEQ_STMT: {
		ret = 0;
	head = t;
	while (head) {
	  if (head->left && make_params(head->left, cur_func)) {
	    ret = 1;
	  }
	  head = head->right;
	}
	return ret;
	}

	case LOCAL_VAR_INSTANCE: {
	tp = t->right->type;
	head = t->left;
	while (head) {
	  newVariable(head->id, tp);
	  head = head->right;
	}
	return 0;
	}

	case ID: {
		ret = 0;
		if (!lookupEntry(t->id, LOOKUP_CURRENT_SCOPE, false)) {
			cur_func->u.eFunction.extra_params->insert(t->id);
			ret = 1;
		}
		return ret;
	}

	case CALL: {
		ret = 0;
		if (t->left) ret = make_params(t->left, cur_func);
		p = lookupEntry(t->id, LOOKUP_ALL_SCOPES, false);
		flag = 1;
		for (p1 = p->u.eFunction.firstArgument; p1; p1 = p1->u.eParameter.next) {
			if (flag) {
				if (!t->left) {
					char * id = (char*)malloc(strlen(p1->id) * sizeof(char));
					strcpy(id, p1->id);
					t->left = ast_seq_expr(ast_id(id), NULL);
					ret = 1;
				}
				head = t->left;
				flag = 0;
			}
			else {
				if (!head->right) {
					char * id = (char*)malloc(strlen(p1->id) * sizeof(char));
					strcpy(id, p1->id);
					head->right = ast_seq_expr(ast_id(id), NULL);
					ret = 1;
				}
				head = head->right;
			}
		}
		if (t->left) {
			for (head = t->left; head->right; head = head->right);
			flag = 0;
		}
		else flag = 1;
		for (auto it = p->u.eFunction.extra_params->begin(); it != p->u.eFunction.extra_params->end(); ++it) {
			if (flag) {
				t->left = ast_seq_expr(ast_id(const_cast<char*> ((*it).c_str())), NULL);
				head = t->left;
				flag = 0;
				ret = 1;
			}
			else {
				head->right = ast_seq_expr(ast_id(const_cast<char*> ((*it).c_str())), NULL);
				head = head->right;
				ret = 1;
			}
			if (!lookupEntry((*it).c_str(), LOOKUP_CURRENT_SCOPE, false)) {
				cur_func->u.eFunction.extra_params->insert(*it);
				ret = 1;
			}
		}
		return ret;
	}

	case DEFINITION: {
	make_params(t->left, cur_func);
	ret = make_params(t->right, t->left->sentry);
	closeScope();
	if (ret) {
		//printf("edo\n");
		head = t->left; // header
		if (head->left) { // arguments already exist
			for (head = head->left; head->right; head = head->right);
			flag = 0;
		}
		else flag = 1;
		for (auto &value: (*t->left->sentry->u.eFunction.extra_params)) {
			//printf("in\n");
			if (!lookupEntry(const_cast<char*> (value.c_str()), LOOKUP_CURRENT_SCOPE, false)) {
				cur_func->u.eFunction.extra_params->insert(value);
			}
			p = lookupEntry(const_cast<char*> (value.c_str()), LOOKUP_ALL_SCOPES, false);
			if (p->entryType == ENTRY_VARIABLE)	tp = p->u.eVariable.type;
			else tp = p->u.eParameter.type;
			if (flag) {
				head->left = ast_seq_formal(ast_formal(VARREF, ast_seq_id(const_cast<char*> (value.c_str()), NULL), find_ast_type(tp)), NULL);
				head->left->left->right->type = tp;
				head = head->left;
				flag = 0;
			}
			else {
				head->right = ast_seq_formal(ast_formal(VARREF, ast_seq_id(const_cast<char*> (value.c_str()), NULL), find_ast_type(tp)), NULL);
				head->right->left->right->type = tp;
				head = head->right;
			}
		}
		if (t->left->sentry->u.eFunction.forward_decl) {
			//printf("mesa\n");
			t->left->sentry->u.eFunction.forward_decl->left = t->left;
		}
	}
	return ret;
	}

	case SEQ_ID:
	case RETURN:
		break;
	default:
		break;
	}
	return 0;
}

int make_parameters(ast* t) {
  initSymbolTable(256);
  int ret = make_params(t, NULL);
  destroySymbolTable();
  return ret;
}
