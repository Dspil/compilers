#ifndef __AST_SYMBOL_H__
#define __AST_SYMBOL_H__
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>
#include <set>
#include <stdbool.h>
#include <string>
#include <vector>

typedef enum {
  AND,
  IARRAY,
  ARRAY,
  BLOCK,
  BOOL,
  CHAR,
  DISPOSE,
  DIV,
  BOOL_CONST,
  FORWARD,
  FUNCTION,
  GOTO,
  IF,
  INT,
  MOD,
  NEW,
  NIL,
  NOT,
  OR,
  PROCEDURE,
  PROGRAM,
  REAL_CONST,
  REAL,
  RESULT,
  RETURN,
  VAR,
  WHILE,
  ID,
  INT_CONST,
  STR_CONST,
  CHAR_CONST,
  NEQ,
  GEQ,
  LEQ,
  LESS,
  GREATER,
  EQ,
  PLUS,
  MINUS,
  TIMES,
  DIVIDE,
  DEREF,
  REF,
  SEQ_EXPR,
  SEQ_STMT,
  SEQ_ID,
  INDEX,
  POINTER,
  CALL,
  ASSIGN,
  STMT,
  DISPOSE_ARRAY,
  VARREF,
  SEQ_FORMAL,
  SEQ_LOCAL,
  DEFINITION,
  LOCAL_VAR,
  LOCAL_VAR_INSTANCE,
  SEQ_LOCAL_VAR,
  BODY,
  LABEL
} kind;

extern int optimize_code;

typedef struct Type_tag *PclType;
typedef struct SymbolEntry_tag SymbolEntry;

typedef struct node {
  kind k;
  char *id;
  char *str;
  int boolean;
  int integer;
  char character;
  long double real;
  int size;
  PclType type;
  SymbolEntry *sentry;
  bool full;
  struct node *left, *mid, *right;
} ast;

bool is_lvalue(ast *t);

char make_char(char *s);

char *make_string(char *s);

void define_builtins();

bool check_compatible(PclType def_t, PclType pass_t);
bool check_compatible_array(PclType def_t, PclType pass_t);

ast *make_ast(kind k, char *id, char *str, int boolean, int integer,
              char character, long double real, int size, ast *left, ast *mid,
              ast *right);

ast *ast_op(ast *l, kind op, ast *r);
ast *ast_id(char *id);
ast *ast_begin(ast *l);
ast *ast_formal(kind k, ast *l, ast *r);
ast *ast_dispose(ast *l);
ast *ast_dispose_array(ast *l);
ast *ast_const(kind k, int boolean, int integer, char character,
               long double real, char *str);
ast *ast_forward(ast *l);
ast *ast_seq_expr(ast *l, ast *r);
ast *ast_seq_stmt(ast *l, ast *r);
ast *ast_seq_id(char *id, ast *r);
ast *ast_seq_formal(ast *l, ast *r);
ast *ast_goto(char *label);
ast *ast_if(ast *l, ast *mid, ast *r);
ast *ast_stmt(char *id, ast *l);
ast *ast_new(ast *l, ast *r); // l NULL for just pointer
ast *ast_program(char *id, ast *l);
ast *ast_result();
ast *ast_index(ast *l, ast *r);
ast *ast_return();
ast *ast_while(ast *l, ast *r);
ast *ast_call(char *id, ast *l);
ast *ast_assign(ast *l, ast *r);
ast *ast_type(kind k, int size, ast *l); // size 0 for incomplete
ast *ast_header(kind k, char *id, ast *l, ast *r);
ast *ast_local(kind k, ast *l, ast *r);
ast *ast_seq_local(kind k, ast *l, ast *r);
ast *ast_local_var_instance(ast *l, ast *r);
ast *ast_seq_local_var(ast *l, ast *r);
ast *ast_body(ast *l, ast *r);

void print_ast(ast *t);

int type_check(ast *t, PclType ftype);

int type_checking(ast *t);

/******************************************************************************
 *  CVS version:
 *     $Id: symbol.h,v 1.1 2003/05/13 22:21:01 nickie Exp $
 ******************************************************************************
 *
 *  C header file : symbol.h
 *  Project       : PCL Compiler
 *  Version       : 1.0 alpha
 *  Written by    : Nikolaos S. Papaspyrou (nickie@softlab.ntua.gr)
 *  Date          : May 14, 2003
 *  Description   : Generic symbol table in C
 *
 *  Comments: (in Greek iso-8859-7)
 *  ---------
 *  Εθνικό Μετσόβιο Πολυτεχνείο.
 *  Σχολή Ηλεκτρολόγων Μηχανικών και Μηχανικών Υπολογιστών.
 *  Τομέας Τεχνολογίας Πληροφορικής και Υπολογιστών.
 *  Εργαστήριο Τεχνολογίας Λογισμικού
 */

/* ---------------------------------------------------------------------
   -------------------------- Τύπος bool -------------------------------
   --------------------------------------------------------------------- */

/*
 *  Αν το παραπάνω include δεν υποστηρίζεται από την υλοποίηση
 *  της C που χρησιμοποιείτε, αντικαταστήστε το με το ακόλουθο:
 */

#if 0
typedef enum { false=0, true=1 } bool;
#endif

/* ---------------------------------------------------------------------
   ------------ Ορισμός σταθερών του πίνακα συμβόλων -------------------
   --------------------------------------------------------------------- */

#define START_POSITIVE_OFFSET 8 /* Αρχικό θετικό offset στο Ε.Δ.   */
#define START_NEGATIVE_OFFSET 0 /* Αρχικό αρνητικό offset στο Ε.Δ. */

/* ---------------------------------------------------------------------
   --------------- Ορισμός τύπων του πίνακα συμβόλων -------------------
   --------------------------------------------------------------------- */

/* Τύποι δεδομένων για την υλοποίηση των σταθερών */

typedef int RepInteger;           /* Ακέραιες                  */
typedef unsigned char RepBoolean; /* Λογικές τιμές             */
typedef char RepChar;             /* Χαρακτήρες                */
typedef long double RepReal;      /* Πραγματικές               */
typedef const char *RepString;    /* Συμβολοσειρές             */

/* Τύποι δεδομένων και αποτελέσματος συναρτήσεων */

typedef enum {            /***** Το είδος του τύπου ****/
               TYPE_VOID, /* Κενός τύπος αποτελέσματος */
               TYPE_INTEGER, /* Ακέραιοι                  */
               TYPE_BOOLEAN, /* Λογικές τιμές             */
               TYPE_CHAR,    /* Χαρακτήρες                */
               TYPE_REAL,    /* Πραγματικοί               */
               TYPE_ARRAY, /* Πίνακες γνωστού μεγέθους  */
               TYPE_IARRAY, /* Πίνακες άγνωστου μεγέθους */
               TYPE_POINTER, /* Δείκτες                   */
               TYPE_LABEL    /* Ταμπέλες                  */
} TypeKind;

typedef enum {                  /* Κατάσταση παραμέτρων  */
               PARDEF_COMPLETE, /* Πλήρης ορισμός     */
               PARDEF_DEFINE,   /* Εν μέσω ορισμού    */
               PARDEF_CHECK     /* Εν μέσω ελέγχου    */
} ParDef;

struct Type_tag {
  TypeKind kind;
  PclType refType;       /* Τύπος αναφοράς            */
  RepInteger size;       /* Μέγεθος, αν είναι πίνακας */
  unsigned int refCount; /* Μετρητής αναφορών         */
  bool full;             /* Πλήρης τύπος 			  */
};

/* Τύποι εγγραφών του πίνακα συμβόλων */

typedef enum {
  ENTRY_VARIABLE,  /* Μεταβλητές                 */
  ENTRY_CONSTANT,  /* Σταθερές                   */
  ENTRY_FUNCTION,  /* Συναρτήσεις                */
  ENTRY_PARAMETER, /* Παράμετροι συναρτήσεων     */
  ENTRY_TEMPORARY  /* Προσωρινές μεταβλητές      */
} EntryType;

/* Τύποι περάσματος παραμετρων */

typedef enum {
  PASS_BY_VALUE,    /* Κατ' αξία                  */
  PASS_BY_REFERENCE /* Κατ' αναφορά               */
} PassMode;

/* Τύπος εγγραφής στον πίνακα συμβόλων */

struct SymbolEntry_tag {
  const char *id;      /* Ονομα αναγνωριστικού          */
  EntryType entryType; /* Τύπος της εγγραφής            */
  unsigned int nestingLevel; /* Βάθος φωλιάσματος             */
  unsigned int hashValue; /* Τιμή κατακερματισμού          */
  SymbolEntry *nextHash; /* Επόμενη εγγραφή στον Π.Κ.     */
  SymbolEntry *nextInScope; /* Επόμενη εγγραφή στην εμβέλεια */
  llvm::AllocaInst *alloca_inst; /* Θέση μνήμης στο llvm της μεταβλητής */

  union { /* Ανάλογα με τον τύπο εγγραφής: */

    struct {        /******* Μεταβλητή *******/
      PclType type; /* Τύπος                 */
      int offset;   /* Offset στο Ε.Δ.       */
      llvm::BasicBlock *block; /* Xρήση μόνο στο llvm, σε περίπτωση label */
      std::vector<llvm::BasicBlock *>
          goto_stack; /* Aποθήκευση των goto blocks */
    } eVariable;

    struct {                 /******** Σταθερά ********/
      PclType type;          /* Τύπος                 */
      union {                /* Τιμή                  */
        RepInteger vInteger; /*    ακέραια            */
        RepBoolean vBoolean; /*    λογική             */
        RepChar vChar;       /*    χαρακτήρας         */
        RepReal vReal;       /*    πραγματική         */
        RepString vString;   /*    συμβολοσειρά       */
      } value;
    } eConstant;

    struct {                      /******* Συνάρτηση *******/
      bool isForward;             /* Δήλωση forward        */
      SymbolEntry *firstArgument; /* Λίστα παραμέτρων      */
      SymbolEntry *lastArgument;  /* Τελευταία παράμετρος  */
      PclType resultType;         /* Τύπος αποτελέσματος   */
      ParDef pardef;
      int firstQuad;            /* Αρχική τετράδα        */
      ast *forward_decl;        /*Η θέση του forward στο ast */
      llvm::Function *llvmFunc; /* Πεδίο για χρήση μόνο στο llvm */
      std::set<std::string> *extra_params; /* Εξτρα παράμετροι      */
    } eFunction;

    struct {             /****** Παράμετρος *******/
      PclType type;      /* Τύπος                 */
      int offset;        /* Offset στο Ε.Δ.       */
      PassMode mode;     /* Τρόπος περάσματος     */
      SymbolEntry *next; /* Επόμενη παράμετρος    */
    } eParameter;

    struct {        /** Προσωρινή μεταβλητή **/
      PclType type; /* Τύπος                 */
      int offset;   /* Offset στο Ε.Δ.       */
      int number;
    } eTemporary;

  } u; /* Τέλος του union               */
};

/* Τύπος συνόλου εγγραφών που βρίσκονται στην ίδια εμβέλεια */

typedef struct Scope_tag Scope;

struct Scope_tag {
  unsigned int nestingLevel; /* Βάθος φωλιάσματος      */
  unsigned int negOffset;    /* Τρέχον αρνητικό offset */
  Scope *parent;             /* Περιβάλλουσα εμβέλεια  */
  SymbolEntry *entries;      /* Σύμβολα της εμβέλειας  */
};

/* Τύπος αναζήτησης στον πίνακα συμβόλων */

typedef enum { LOOKUP_CURRENT_SCOPE, LOOKUP_ALL_SCOPES } LookupType;

/* ---------------------------------------------------------------------
   ------------- Καθολικές μεταβλητές του πίνακα συμβόλων --------------
   --------------------------------------------------------------------- */

extern Scope *currentScope; /* Τρέχουσα εμβέλεια         */
extern unsigned int quadNext; /* Αριθμός επόμενης τετράδας */
extern unsigned int tempNumber; /* Αρίθμηση των temporaries  */

extern const PclType typeVoid;
extern const PclType typeInteger;
extern const PclType typeBoolean;
extern const PclType typeChar;
extern const PclType typeReal;
extern const PclType typeLabel;

/* ---------------------------------------------------------------------
   ------ Πρωτότυπα των συναρτήσεων χειρισμού του πίνακα συμβολών ------
   --------------------------------------------------------------------- */

void initSymbolTable(unsigned int size);
void destroySymbolTable(void);

void openScope(void);
void closeScope(void);

SymbolEntry *newVariable(const char *name, PclType type);
SymbolEntry *newConstant(const char *name, PclType type, ...);
SymbolEntry *newFunction(const char *name);
SymbolEntry *newParameter(const char *name, PclType type, PassMode mode,
                          SymbolEntry *f);
SymbolEntry *newTemporary(PclType type);

void forwardFunction(SymbolEntry *f);
void endFunctionHeader(SymbolEntry *f, PclType type);
void destroyEntry(SymbolEntry *e);
SymbolEntry *lookupEntry(const char *name, LookupType type, bool err);

PclType typeArray(RepInteger size, PclType refType);
PclType typeIArray(PclType refType);
PclType typePointer(PclType refType);
void destroyType(PclType type);
unsigned int sizeOfType(PclType type);
bool equalType(PclType type1, PclType type2);
void printType(PclType type);
void printMode(PassMode mode);
void printSymbolTable();

#endif
