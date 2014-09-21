#include <stdio.h>
#include <stdbool.h>
#include "tree.h"
#include "traversal.h"

bool isVar = false;

int traversalerr = 0;
int countPar = 0;
int countVar = 0;

int traversal(MAIN *main, SymbolTable *t) {
  if (main->statement_list != NULL) {
    traversal_statement_list(main->statement_list, t);
  }
  if (main->decl_list != NULL) {
    traversal_decllist(main->decl_list, t);
  }
  return traversalerr;
}

void traversal_decllist(DECL_LIST *decl_list, SymbolTable *t) {
  if (decl_list != NULL) {
    if (decl_list->decl_list != NULL) {
      traversal_decllist(decl_list->decl_list, t);
    }
    traversal_declaration(decl_list->declaration, t);
  }
}

void traversal_declaration(DECLARATION *decl, SymbolTable *t) {
  FUNCTION *function = decl->function;
  HEAD *head = function->head;
  STATEMENT *statement_list = function->statement_list;
  SYMBOL *symbol = putSymbolFunction(t, head->idH, function);
  if (symbol == NULL) {
    traversalerr++;
    SYMBOL *s = getSymbol(t, head->idH);
    int i;
    switch (s->kind) {
      case svarK:
        i = s->val.variable->lineno;
        fprintf(stderr, "Fejl i linje %i: En variabel med navnet %s er allerede deklareret i linje %i.\n", head->lineno, head->idH, i);
        break;
      case sparK:
        i = s->val.parameter->lineno;
        fprintf(stderr, "Fejl i linje %i: En parameter med navnet %s er allerede deklareret i linje %i.\n", head->lineno, head->idH, i);
        break;
      case sfunctionK:
        i = s->val.function->head->lineno;
        fprintf(stderr, "Fejl i linje %i: En funktion med navnet %s er allerede deklareret i linje %i.\n", head->lineno, head->idH, i);
        break;
    }
  } else {
    PAR_DECL_LIST *par_decl_list = head->par_decl_list;
    function->table = scopeSymbolTable(t);
    if (par_decl_list != NULL) {
      traversal_pardecllist(par_decl_list, function->table);
    }
    traversal_statement_list(statement_list, function->table);
  }
}

void traversal_pardecllist(PAR_DECL_LIST *par_decl_list, SymbolTable *t) {
  if (par_decl_list->next != NULL) {
    traversal_pardecllist(par_decl_list->next, t);
  }
  traversal_par(par_decl_list->par, t);
}

void traversal_par(PAR *par, SymbolTable *t) {
  SYMBOL *symbol = putSymbolPar(t, par->id, par);
  if (symbol == NULL) {
    traversalerr++;
    SYMBOL *s = getSymbol(t, par->id);
    int i;
    switch (s->kind) {
      case svarK:
        i = s->val.variable->lineno;
        fprintf(stderr, "Fejl i linje %i: En variabel med navnet %s er allerede deklareret i linje %i.\n", par->lineno, par->id, i);
        break;
      case sparK:
        i = s->val.parameter->lineno;
        fprintf(stderr, "Fejl i linje %i: En parameter med navnet %s er allerede deklareret i linje %i.\n", par->lineno, par->id, i);
        break;
      case sfunctionK:
        i = s->val.function->head->lineno;
        fprintf(stderr, "Fejl i linje %i: En funktion med navnet %s er allerede deklareret i linje %i.\n", par->lineno, par->id, i);
        break;
     }
  }
}

void traversal_statement_list(STATEMENT *statement_list, SymbolTable *t) {
  if (statement_list->kind == statement_listK) {
    if (statement_list->val.statement_listS.statement != NULL) {
      traversal_statement(statement_list->val.statement_listS.statement, t);
    }
    if (statement_list->val.statement_listS.next != NULL) {
      traversal_statement_list(statement_list->val.statement_listS.next, t);
    }
  } else {
    traversal_statement(statement_list, t);
  }
}

void traversal_statement(STATEMENT *statement, SymbolTable *t) {
  if (statement->kind == 2) {
    traversal_assign(statement, t);
  }
  if (statement->kind == 8) {
    traversal_statement_list(statement, t);
  }
}

void traversal_assign(STATEMENT *statement, SymbolTable *t) {
  VARIABLE *v = statement->val.assignS.variable;
  SYMBOL *symbol = putSymbolVar(t, v->idV, v);
  if (symbol == NULL) {
    SYMBOL *s = getSymbol(t, v->idV);
    if (s->kind == sfunctionK) {
      traversalerr++;
      int i = s->val.function->head->lineno;
      fprintf(stderr, "Fejl i linje %i: En funktion med navnet %s er allerede deklareret i linje %i.\n", v->lineno, v->idV, i);
    }
  }
}

/*
int setValueTraversal(MAIN *main, SymbolTable *t) {
  if (main->statement_list != NULL) {
    setValueTraversal_statement_list(main->statement_list, t);
  }
  if (main->decl_list != NULL) {
    setValueTraversal_decllist(main->decl_list, t);
  }
  return traversalerr;
}

void setValueTraversal_decllist(DECL_LIST *decl_list, SymbolTable *t) {
  if (decl_list != NULL) {
    if (decl_list->decl_list != NULL) {
      setValueTraversal_decllist(decl_list->decl_list, t);
    }
    setValueTraversal_declaration(decl_list->declaration, t);
  }
}

void setValueTraversal_declaration(DECLARATION *decl, SymbolTable *t) {
  FUNCTION *function = decl->function;
  STATEMENT *statement_list = function->statement_list;
  setValueTraversal_statement_list(statement_list, function->table);
}

void setValueTraversal_statement_list(STATEMENT *statement_list, SymbolTable *t) {
  if (statement_list->kind == statement_listK) {
    if (statement_list->val.statement_listS.statement != NULL) {
      setValueTraversal_statement(statement_list->val.statement_listS.statement, t);
    }
    if (statement_list->val.statement_listS.next != NULL) {
      setValueTraversal_statement_list(statement_list->val.statement_listS.next, t);
    }
  } else {
    setValueTraversal_statement(statement_list, t);
  }
}

void setValueTraversal_statement(STATEMENT *statement, SymbolTable *t) {
  if (statement->kind == 2 && statement->val.assignS.exp->kind == 0) {
    setValueTraversal_assign(statement, t);
  }
  if (statement->kind == 2) {
    calcAndSetValue(statement, t);
  }
  if (statement->kind == 8) {
    setValueTraversal_statement_list(statement, t);
  }
}

void setValueTraversal_assign(STATEMENT *statement, SymbolTable *t) {
  VARIABLE *var = statement->val.assignS.variable;
  SYMBOL *s = getSymbol(t, var->idV);
  EXP *exp = statement->val.assignS.exp;
  int value = exp->val.intconstE;
  s->value = value;
  s->pos = 0;
  s->isNum = true;
}

void calcAndSetValue(STATEMENT *statement, SymbolTable *t) {
  EXP *exp = statement->val.assignS.exp;
  VARIABLE *var = statement->val.assignS.variable;
  SYMBOL *s = getSymbol(t, var->idV);
  int i = calcValue(exp, s);
  s->value = i;
  s->pos = 0;
}

int calcValue(EXP *exp, SYMBOL *s) {
  int i = 0;
  int j = 0;
  int res = 0;
  switch (exp->kind) {
    case timesK:
      i = calcValue(exp->val.timesE.left, s);
      j = calcValue(exp->val.timesE.right, s);
      res = i * j;
      break;
    case divK:
      i = calcValue(exp->val.divE.left, s);
      j = calcValue(exp->val.divE.right, s);
      res = i / j;
      break;
    case plusK:
      i = calcValue(exp->val.plusE.left, s);
      j = calcValue(exp->val.plusE.right, s);
      res = i + j;
      break;
    case minusK:
      i = calcValue(exp->val.minusE.left, s);
      j = calcValue(exp->val.minusE.right, s);
      res = i - j;
      break;
    default:
      break;
  }
  if (exp->kind == varK) {
    isVar = true;
  }
  if (exp->kind == 0) {
    return exp->val.intconstE;
  }
  if (!isVar) {
    s->isNum = true;
    return res;
  } else {
    s->isNum = false;
    isVar = false;
    return 0;
  }
}

void setPositionTraversal_statement_list(STATEMENT *statement_list, SymbolTable *t) {
  if (statement_list->kind == statement_listK) {
    if (statement_list->val.statement_listS.statement != NULL) {
      setPositionTraversal_statement(statement_list->val.statement_listS.statement, t);
    }
    if (statement_list->val.statement_listS.next != NULL) {
      setPositionTraversal_statement_list(statement_list->val.statement_listS.next, t);
    }
  } else {
    setPositionTraversal_statement(statement_list, t);
  }
}

void setPositionTraversal_statement(STATEMENT *statement, SymbolTable *t) {
  if (statement->kind == 2) {
    VARIABLE *var = statement->val.assignS.variable;
    SYMBOL *s = getSymbol(t, var->idV);
    if (s->pos == 0) {
      s->pos = 4 * countVar;
      countVar--;
    }
  }
  if (statement->kind == 8) {
    setPositionTraversal_statement_list(statement, t);
  }
}
*/
