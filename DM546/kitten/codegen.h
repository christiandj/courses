#ifndef __codegen_h
#define __codegen_h

#include "memory.h"
#include "tree.h"
#include "symbol.h"

typedef struct REGISTER {
  int registerid;
  int registervalue;
  char *registername;
} REGISTER;

typedef struct INSTRUCTION {
  enum {
    ilabelK, iflabelK, iintaddK, iaddK, isubK, imulK, idivK, iandK, iorK,
    iintcmpK, icmpK, iintmovK, imovK, ijmpK, ijeK, ijneK, ijlK, ijleK, ijgK,
    ijgeK, iintpushK, ipushK, ipopK, icallK, ireturnK, iposmovK, iallocK, ideallocK
  } kind;
  union {
    char *id;
    struct { struct REGISTER *ra; struct REGISTER *rb; } ARGUMENT;
    struct { int a; struct REGISTER *rb; } CONST_ARGUMENT;
    struct { struct REGISTER *ra; struct REGISTER *rb; int posa; int posb; } POSMOV;
  } u;
} INSTRUCTION;

typedef struct LINKED_LIST {
  struct INSTRUCTION *current;
  struct LINKED_LIST *prev;
  struct LINKED_LIST *next;
} LINKED_LIST;

LINKED_LIST *generateCode(MAIN *main, SymbolTable *t);

REGISTER *makeREGISTERint(int i);

REGISTER *makeREGISTER();

void makeFUNCTIONcg(FUNCTION *function);

void makeDECLLISTcg(DECL_LIST *decl_list);

void makeSTATEMENTcg(STATEMENT *statement, SymbolTable *t);

void makeSTATEMENTLISTcg(STATEMENT *statement_list, SymbolTable *t);

int getVARposition(char *id, int pos, SymbolTable *t);

REGISTER *makeVARcg(VARIABLE *var, SymbolTable *t);

REGISTER *makeEXPcg(EXP *exp, SymbolTable *t);

void makeEXPLISTcg(EXP_LIST *explist, SymbolTable *t);

void makeFUNCTIONLABEL(char *label);

void makeLABEL(char *label);

void intadd(int a, REGISTER *ra);

void add(REGISTER *ra, REGISTER *rb);

void sub(REGISTER *ra, REGISTER *rb);

void mul(REGISTER *ra, REGISTER *rb);

void mydiv(REGISTER *ra);

void and(REGISTER *ra, REGISTER *rb);

void or(REGISTER *ra, REGISTER *rb);

void intcmp(int a, REGISTER *ra);

void cmp(REGISTER *ra, REGISTER *rb);

void intmov(int a, REGISTER *ra);

void mov(REGISTER *ra, REGISTER *rb);

void jmp(char *label);

void je(char *label);

void jne(char *label);

void jl(char *label);

void jle(char *label);

void jg(char *label);

void jge(char *label);

void intpush(int a);

void push(REGISTER *ra);

void pop(REGISTER *ra);

void call(char *label);

void returnCall();

void posMov(REGISTER *ra, REGISTER *rb, int posa, int posb);

void setPosPar(PAR_DECL_LIST *par_decl_list, SymbolTable *t, int i);

void countParVar(SymbolTable *t);

void allocVar();

void deallocVar();

void printInstruction(INSTRUCTION *instruction);

void emission(LINKED_LIST *l);

#endif
