#ifndef __dumpsymbol_h
#define __dumpsymbol_h

#include "tree.h"
#include "symbol.h"

void dumpsymbol(MAIN *main, SymbolTable *t);

void dumpsymbol_decllist(DECL_LIST *decl_list, SymbolTable *t);

// Moved from symbol.h
void dumpSymbolTable(SymbolTable *t);

#endif
