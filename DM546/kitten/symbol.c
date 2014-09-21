#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol.h"

int Hash(char *str) {
  int length = strlen(str);
  int sum = 0;
  int i;
  for (i = 0; i < length; i++) {
    sum = sum + str[i];
  }
  return sum % HashSize;
}

SymbolTable *initSymbolTable() {
  struct SymbolTable *s = NEW(SymbolTable);
  s->next = NULL;
  int i;
  for (i = 0; i < HashSize; i++) {
    s->table[i] = NULL;
  }
  return s;
}

SymbolTable *scopeSymbolTable(SymbolTable *t) {
  struct SymbolTable *s = initSymbolTable();
  s->next = t;
  return s;
}

SYMBOL *placeSymbol(SymbolTable *t, SYMBOL *s, char *name, int hash) {
  SYMBOL *symbol = getSymbol(t, name);
  if (symbol == NULL) {
    if (t->table[hash] == NULL) {
      t->table[hash] = s;
      return s;
    }
    if (strcmp(t->table[hash]->name, name) == 0) {
      return NULL;
    } else {
      SYMBOL *nextNode = t->table[hash]->next;
      SYMBOL *prevNode = t->table[hash];
      while (nextNode != NULL) {
        if (strcmp(nextNode->name, name) == 0) {
          return NULL;
        }
        prevNode = nextNode;
        nextNode = nextNode->next;
      }
      prevNode->next = s;
      return s;
    }
  }
  return NULL;
}

SYMBOL *putSymbolVar(SymbolTable *t, char *name, VARIABLE *variable) {
  int hash = Hash(name);
  SYMBOL *s = NEW(SYMBOL);
  s->name = malloc(strlen(name));
  strcpy(s->name, name);
  s->kind = svarK;
  s->val.variable = variable;
  s->next = NULL;
  return placeSymbol(t, s, name, hash);
}

SYMBOL *putSymbolPar(SymbolTable *t, char *name, PAR *par) {
  int hash = Hash(name);
  SYMBOL *s = NEW(SYMBOL);
  s->name = malloc(strlen(name));
  strcpy(s->name, name);
  s->kind = sparK;
  s->val.parameter = par;
  s->next = NULL;
  return placeSymbol(t, s, name, hash);
}

SYMBOL *putSymbolFunction(SymbolTable *t, char *name, FUNCTION *function) {
  int hash = Hash(name);
  SYMBOL *s = NEW(SYMBOL);
  s->name = malloc(strlen(name));
  strcpy(s->name, name);
  s->kind = sfunctionK;
  s->val.function = function;
  s->next = NULL;
  return placeSymbol(t, s, name, hash);
}

SYMBOL *getSymbol(SymbolTable *t, char *name) {
  int temp = Hash(name);
  SYMBOL *s = t->table[temp];
  if (s != NULL) {
    if (strcmp(s->name, name) == 0) {
      return s;
    } else {
      SYMBOL *sNext = t->table[temp]->next;
      while (sNext != NULL) {
        if (strcmp(sNext->name, name) == 0) {
          return sNext;
        }
        sNext = sNext->next;
      }
    }
  }
  if (t->next != NULL) {
    return getSymbol(t->next, name);
  } else {
    return NULL;
  }
}
