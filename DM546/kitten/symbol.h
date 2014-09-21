#ifndef __symbol_h
#define __symbol_h

#include <stdbool.h>
#include "tree.h"
#include "memory.h"

#define HashSize 317

void *malloc(unsigned n);

typedef struct SYMBOL {
  char *name;
  struct SYMBOL *next;
  enum { svarK, sparK, sfunctionK } kind;
  union {
    struct VARIABLE *variable;
    struct PAR *parameter;
    struct FUNCTION *function;
  } val;
  int pos;
} SYMBOL;

typedef struct SymbolTable {
  SYMBOL *table[HashSize];
  struct SymbolTable *next;
} SymbolTable;

int Hash(char *str);

SymbolTable *initSymbolTable();

SymbolTable *scopeSymbolTable(SymbolTable *t);

SYMBOL *placeSymbol(SymbolTable *t, SYMBOL *s, char *name, int hash);

SYMBOL *putSymbolVar(SymbolTable *t, char *name, VARIABLE *variable);

SYMBOL *putSymbolPar(SymbolTable *t, char *name, PAR *par);

SYMBOL *putSymbolFunction(SymbolTable *t, char *name, FUNCTION *function);

SYMBOL *getSymbol(SymbolTable *t, char *name);

#endif
