#ifndef __traversal_h
#define __traversal_h

#include "tree.h"
#include "symbol.h"

int traversal(MAIN *main, SymbolTable *t);

void traversal_decllist(DECL_LIST *decl_list, SymbolTable *t);

void traversal_declaration(DECLARATION *decl, SymbolTable *t);

void traversal_pardecllist(PAR_DECL_LIST *par_decl_list, SymbolTable *t);

void traversal_par(PAR *par, SymbolTable *t);

void traversal_statement_list(STATEMENT *statement_list, SymbolTable *t);

void traversal_statement(STATEMENT *statement, SymbolTable *t);

void traversal_assign(STATEMENT *statement, SymbolTable *t);

/*
int setValueTraversal(MAIN *main, SymbolTable *t);

void setValueTraversal_decllist(DECL_LIST *decl_list, SymbolTable *t);

void setValueTraversal_declaration(DECLARATION *decl, SymbolTable *t);

void setValueTraversal_statement_list(STATEMENT *statement_list, SymbolTable *t);

void setValueTraversal_statement(STATEMENT *statement, SymbolTable *t);

void setValueTraversal_assign(STATEMENT *statement, SymbolTable *t);

void calcAndSetValue(STATEMENT *statement, SymbolTable *t);

int calcValue(EXP *exp, SYMBOL *s);

void setPositionTraversal_statement_list(STATEMENT *statement_list, SymbolTable *t);

void setPositionTraversal_statement(STATEMENT *statement, SymbolTable *t);
*/

#endif
