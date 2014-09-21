#include <stdio.h>
#include <stdbool.h>
#include "tree.h"
#include "dumpsymbol.h"

bool dumpedMainScope = false;

void dumpsymbol(MAIN *main, SymbolTable *t) {
  if (main->decl_list != NULL) {
    dumpsymbol_decllist(main->decl_list, t);
  } else {
    dumpSymbolTable(t);
  }
}

void dumpsymbol_decllist(DECL_LIST *decl_list, SymbolTable *t) {
  if (decl_list != NULL) {
    if (decl_list->decl_list != NULL) {
      dumpsymbol_decllist(decl_list->decl_list, t);
    }
    FUNCTION *function = decl_list->declaration->function;
    fprintf(stderr, "Virkefelt for funktionen %s:\n", function->head->idH);
    dumpSymbolTable(function->table);
  }
}

// Moved from symbol.c
void dumpSymbolTable(SymbolTable *t) {
  int i;
  for (i = 0; i < HashSize; i++) {
    if (t->table[i] != NULL) {
      fprintf(stderr, "Spand %d indeholder følgende:\n", i);
      switch (t->table[i]->kind) {
        case svarK:
          fprintf(stderr, "    En variabel med navnet %s.\n", t->table[i]->name);
          break;
        case sparK:
          fprintf(stderr, "    En parameter med navnet %s.\n", t->table[i]->name);
          break;
        case sfunctionK:
          fprintf(stderr, "    En funktion med navnet %s.\n", t->table[i]->name);
          break;
      }
      struct SYMBOL *sNext = t->table[i]->next;
      while (sNext != NULL) {
        switch (sNext->kind) {
          case svarK:
            fprintf(stderr, "    En variabel med navnet %s.\n", t->table[i]->name);
            break;
          case sparK:
            fprintf(stderr, "    En parameter med navnet %s.\n", t->table[i]->name);
            break;
          case sfunctionK:
            fprintf(stderr, "    En funktion med navnet %s.\n", t->table[i]->name);
            break;
        }
        sNext = sNext->next;
      }
    }
  }
  if (t->next != NULL) {
    if (!dumpedMainScope) {
      fprintf(stderr, "Globalt virkefelt:\n");
      dumpSymbolTable(t->next);
    }
    dumpedMainScope = true;
  }
}
