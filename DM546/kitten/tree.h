#ifndef __tree_h
#define __tree_h

typedef struct FUNCTION {
  int lineno;
  struct HEAD *head;
  struct STATEMENT *statement_list;
  struct TAIL *tail;
  struct SymbolTable *table;
} FUNCTION;

typedef struct HEAD {
  int lineno;
  char *idH;
  struct PAR_DECL_LIST *par_decl_list;
} HEAD;

typedef struct TAIL {
  int lineno;
  int i;
} TAIL;

typedef struct PAR_DECL_LIST {
  struct PAR *par;
  struct PAR_DECL_LIST *next;
} PAR_DECL_LIST;

typedef struct PAR {
  int lineno;
  char *id;
} PAR;

typedef struct MAIN {
  int lineno;
  struct DECL_LIST *decl_list;
  struct STATEMENT *statement_list;
} MAIN;

typedef struct DECL_LIST {
  int lineno;
  struct DECL_LIST *decl_list;
  struct DECLARATION *declaration;
} DECL_LIST;

typedef struct DECLARATION {
  int lineno;
  struct FUNCTION *function;
} DECLARATION;

typedef struct STATEMENT {
  int lineno;
  enum { returnK, writeK, assignK, ifK, loopK, continueK, breakK, curly_bracketK, statement_listK } kind;
  union {
    struct { struct EXP *exp; } returnS;
    struct { struct EXP *exp; } writeS;
    struct { struct VARIABLE *variable; struct EXP *exp; } assignS;
    struct { struct EXP *exp; struct STATEMENT *statement; } ifS;
    struct { struct STATEMENT *statement; int i; } loopS;
    struct { int i; } continueS;
    struct { int i; } breakS;
    struct { struct STATEMENT *statement; } curly_bracketS;
    struct { struct STATEMENT *statement; struct STATEMENT *next; } statement_listS;
  } val;
} STATEMENT;

typedef struct VARIABLE {
  int lineno;
  char *idV;
} VARIABLE;

typedef struct EXP {
  int lineno;
  enum { intconstK, timesK, divK, plusK, minusK, eqK, neqK, gtK, ltK, geqK, leqK, andK, orK, notK, func_callK, varK } kind;
  union {
    int intconstE;
    struct { struct EXP *left; struct EXP *right; } timesE;
    struct { struct EXP *left; struct EXP *right; } divE;
    struct { struct EXP *left; struct EXP *right; } plusE;
    struct { struct EXP *left; struct EXP *right; } minusE;
    struct { struct EXP *left; struct EXP *right; } eqE;
    struct { struct EXP *left; struct EXP *right; } neqE;
    struct { struct EXP *left; struct EXP *right; } gtE;
    struct { struct EXP *left; struct EXP *right; } ltE;
    struct { struct EXP *left; struct EXP *right; } geqE;
    struct { struct EXP *left; struct EXP *right; } leqE;
    struct { struct EXP *left; struct EXP *right; } andE;
    struct { struct EXP *left; struct EXP *right; } orE;
    struct { struct EXP *note; } notE;
    struct { char *id; struct EXP_LIST *act_list; } func_callE;
    struct VARIABLE *var;
  } val;
} EXP;

typedef struct EXP_LIST {
  struct EXP *exp;
  struct EXP_LIST *next;
} EXP_LIST;

FUNCTION *makeFUNCTION(HEAD *head, STATEMENT *statement_list, TAIL *tail);

HEAD *makeHEAD(char *idH, PAR_DECL_LIST *par_decl_list);

TAIL *makeTAIL();

PAR_DECL_LIST *makePARDECLLIST(PAR *par, PAR_DECL_LIST *next);

PAR *makePAR(char *id);

MAIN *makeMAIN(DECL_LIST *decl_list, STATEMENT *statement_list);

DECL_LIST *makeDECLLIST(DECL_LIST *decl_list, DECLARATION *declaration);

DECLARATION *makeDECLARATION(FUNCTION *function);

STATEMENT *makeSTATEMENTstmtlist(STATEMENT *statement, STATEMENT *next);

STATEMENT *makeSTATEMENTreturn(EXP *exp);

STATEMENT *makeSTATEMENTwrite(EXP *exp);

STATEMENT *makeSTATEMENTassign(VARIABLE *variable, EXP *exp);

STATEMENT *makeSTATEMENTif(EXP *exp, STATEMENT *statement);

STATEMENT *makeSTATEMENTloop(STATEMENT *statement);

STATEMENT *makeSTATEMENTcontinue();

STATEMENT *makeSTATEMENTbreak();

STATEMENT *makeSTATEMENTcurly(STATEMENT *statement);

STATEMENT *makeSTATEMENTtimeseq(VARIABLE *variable, EXP *exp);

STATEMENT *makeSTATEMENTdiveq(VARIABLE *variable, EXP *exp);

STATEMENT *makeSTATEMENTpluseq(VARIABLE *variable, EXP *exp);

STATEMENT *makeSTATEMENTminuseq(VARIABLE *variable, EXP *exp);

VARIABLE *makeVARIABLE(char *id);

EXP *makeEXPintconst(int intconst);

EXP *makeEXPtimes(EXP *left, EXP *right);

EXP *makeEXPdiv(EXP *left, EXP *right);

EXP *makeEXPplus(EXP *left, EXP *right);

EXP *makeEXPminus(EXP *left, EXP *right);

EXP *makeEXPeq(EXP *left, EXP *right);

EXP *makeEXPneq(EXP *left, EXP *right);

EXP *makeEXPgt(EXP *left, EXP *right);

EXP *makeEXPlt(EXP *left, EXP *right);

EXP *makeEXPgeq(EXP *left, EXP *right);

EXP *makeEXPleq(EXP *left, EXP *right);

EXP *makeEXPand(EXP *left, EXP *right);

EXP *makeEXPor(EXP *left, EXP *right);

EXP *makeEXPuminus(EXP *exp);

EXP *makeEXPnot(EXP *note);

EXP *makeEXPfunccall(char *id, EXP_LIST *act_list);

EXP *makeEXPvar(VARIABLE *var);

EXP_LIST *makeEXPLIST(EXP *exp, EXP_LIST *next);

#endif
