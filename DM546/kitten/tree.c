#include <stdlib.h>
#include "memory.h"
#include "tree.h"

extern int lineno;

FUNCTION *makeFUNCTION(HEAD *head, STATEMENT *statement_list, TAIL *tail) {
  FUNCTION *f;
  f = NEW(FUNCTION);
  f->lineno = lineno;
  f->head = head;
  f->statement_list = statement_list;
  f->tail = tail;
  f->table = NULL;
  return f;
}

HEAD *makeHEAD(char *idH, PAR_DECL_LIST *par_decl_list) {
  HEAD *h;
  h = NEW(HEAD);
  h->lineno = lineno;
  h->idH = idH;
  h->par_decl_list = par_decl_list;
  return h;
}

TAIL *makeTAIL() {
  TAIL *t;
  t = NEW(TAIL);
  t->lineno = lineno;
  t->i = 1;
  return t;
}

PAR_DECL_LIST *makePARDECLLIST(PAR *par, PAR_DECL_LIST *next) {
  PAR_DECL_LIST *p;
  p = NEW(PAR_DECL_LIST);
  p->par = par;
  p->next = next;
  return p;
}

PAR *makePAR(char *id) {
  PAR *p;
  p = NEW(PAR);
  p->lineno = lineno;
  p->id = id;
  return p;
}

MAIN *makeMAIN(DECL_LIST *decl_list, STATEMENT *statement_list) {
  MAIN *m;
  m = NEW(MAIN);
  m->lineno = lineno;
  m->decl_list = decl_list;
  m->statement_list = statement_list;
  return m;
}

DECL_LIST *makeDECLLIST(DECL_LIST *decl_list, DECLARATION *declaration) {
  DECL_LIST *d;
  d = NEW(DECL_LIST);
  d->lineno = lineno;
  d->decl_list = decl_list;
  d->declaration = declaration;
  return d;
}

DECLARATION *makeDECLARATION(FUNCTION *function) {
  DECLARATION *d;
  d = NEW(DECLARATION);
  d->lineno = lineno;
  d->function = function;
  return d;
}

STATEMENT *makeSTATEMENTreturn(EXP *exp) {
  STATEMENT *s;
  s = NEW(STATEMENT);
  s->lineno = lineno;
  s->kind = returnK;
  s->val.returnS.exp = exp;
  return s;
}

STATEMENT *makeSTATEMENTwrite(EXP *exp) {
  STATEMENT *s;
  s = NEW(STATEMENT);
  s->lineno = lineno;
  s->kind = writeK;
  s->val.writeS.exp = exp;
  return s;
}

STATEMENT *makeSTATEMENTassign(VARIABLE *variable, EXP *exp) {
  STATEMENT *s;
  s = NEW(STATEMENT);
  s->lineno = lineno;
  s->kind = assignK;
  s->val.assignS.variable = variable;
  s->val.assignS.exp = exp;
  return s;
}

STATEMENT *makeSTATEMENTif(EXP *exp, STATEMENT *statement) {
  STATEMENT *s;
  s = NEW(STATEMENT);
  s->lineno = lineno;
  s->kind = ifK;
  s->val.ifS.exp = exp;
  s->val.ifS.statement = statement;
  return s;
}

STATEMENT *makeSTATEMENTloop(STATEMENT *statement) {
  STATEMENT *s;
  s = NEW(STATEMENT);
  s->lineno = lineno;
  s->kind = loopK;
  s->val.loopS.statement = statement;
  return s;
}

STATEMENT *makeSTATEMENTcontinue() {
  STATEMENT *s;
  s = NEW(STATEMENT);
  s->lineno = lineno;
  s->kind = continueK;
  s->val.continueS.i = 1;
  return s;
}

STATEMENT *makeSTATEMENTbreak() {
  STATEMENT *s;
  s = NEW(STATEMENT);
  s->lineno = lineno;
  s->kind = breakK;
  s->val.breakS.i = 1;
  return s;
}

STATEMENT *makeSTATEMENTcurly(STATEMENT *statement) {
  STATEMENT *s;
  s = NEW(STATEMENT);
  s->lineno = lineno;
  s->kind = curly_bracketK;
  s->val.curly_bracketS.statement = statement;
  return s;
}

STATEMENT *makeSTATEMENTstmtlist(STATEMENT *statement, STATEMENT *next) {
  STATEMENT *s;
  s = NEW(STATEMENT);
  s->lineno = lineno;
  s->kind = statement_listK;
  s->val.statement_listS.statement = statement;
  s->val.statement_listS.next = next;
  return s;
}

STATEMENT *makeSTATEMENTtimeseq(VARIABLE *variable, EXP *exp) {
  STATEMENT *s;
  s = NEW(STATEMENT);
  s->lineno = lineno;
  s->kind = assignK;
  s->val.assignS.variable = makeVARIABLE(variable->idV);
  s->val.assignS.exp = makeEXPtimes(makeEXPvar(s->val.assignS.variable), exp);
  return s;
}

STATEMENT *makeSTATEMENTdiveq(VARIABLE *variable, EXP *exp) {
  STATEMENT *s;
  s = NEW(STATEMENT);
  s->lineno = lineno;
  s->kind = assignK;
  s->val.assignS.variable = makeVARIABLE(variable->idV);
  s->val.assignS.exp = makeEXPdiv(makeEXPvar(s->val.assignS.variable), exp);
  return s;
}

STATEMENT *makeSTATEMENTpluseq(VARIABLE *variable, EXP *exp) {
  STATEMENT *s;
  s = NEW(STATEMENT);
  s->lineno = lineno;
  s->kind = assignK;
  s->val.assignS.variable = makeVARIABLE(variable->idV);
  s->val.assignS.exp = makeEXPplus(makeEXPvar(s->val.assignS.variable), exp);
  return s;
}

STATEMENT *makeSTATEMENTminuseq(VARIABLE *variable, EXP *exp) {
  STATEMENT *s;
  s = NEW(STATEMENT);
  s->lineno = lineno;
  s->kind = assignK;
  s->val.assignS.variable = makeVARIABLE(variable->idV);
  s->val.assignS.exp = makeEXPminus(makeEXPvar(s->val.assignS.variable), exp);
  return s;
}

VARIABLE *makeVARIABLE(char *id) {
  VARIABLE *v;
  v = NEW(VARIABLE);
  v->lineno = lineno;
  v->idV = id;
  return v;
}

EXP *makeEXPintconst(int intconst) {
  EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->kind = intconstK;
  e->val.intconstE = intconst;
  return e;
}

EXP *makeEXPtimes(EXP *left, EXP *right) {
  EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->kind = timesK;
  e->val.timesE.left = left;
  e->val.timesE.right = right;
  return e;
}

EXP *makeEXPdiv(EXP *left, EXP *right) {
  EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->kind = divK;
  e->val.divE.left = left;
  e->val.divE.right = right;
  return e;
}

EXP *makeEXPplus(EXP *left, EXP *right) {
  EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->kind = plusK;
  e->val.plusE.left = left;
  e->val.plusE.right = right;
  return e;
}

EXP *makeEXPminus(EXP *left, EXP *right) {
  EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->kind = minusK;
  e->val.minusE.left = left;
  e->val.minusE.right = right;
  return e;
}

EXP *makeEXPeq(EXP *left, EXP *right) {
  EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->kind = eqK;
  e->val.eqE.left = left;
  e->val.eqE.right = right;
  return e;
}

EXP *makeEXPneq(EXP *left, EXP *right) {
  EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->kind = neqK;
  e->val.neqE.left = left;
  e->val.neqE.right = right;
  return e;
}

EXP *makeEXPgt(EXP *left, EXP *right) {
  EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->kind = gtK;
  e->val.gtE.left = left;
  e->val.gtE.right = right;
  return e;
}

EXP *makeEXPlt(EXP *left, EXP *right) {
  EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->kind = ltK;
  e->val.ltE.left = left;
  e->val.ltE.right = right;
  return e;
}

EXP *makeEXPgeq(EXP *left, EXP *right) {
  EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->kind = geqK;
  e->val.geqE.left = left;
  e->val.geqE.right = right;
  return e;
}

EXP *makeEXPleq(EXP *left, EXP *right) {
  EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->kind = leqK;
  e->val.leqE.left = left;
  e->val.leqE.right = right;
  return e;
}

EXP *makeEXPand(EXP *left, EXP *right) {
  EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->kind = andK;
  e->val.andE.left = left;
  e->val.andE.right = right;
  return e;
}

EXP *makeEXPor(EXP *left, EXP *right) {
  EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->kind = orK;
  e->val.orE.left = left;
  e->val.orE.right = right;
  return e;
}

EXP *makeEXPuminus(EXP *exp) {
  EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->kind = minusK;
  e->val.minusE.left = makeEXPintconst(0);
  e->val.minusE.right = exp;
  return e;
}

EXP *makeEXPnot(EXP *note) {
  EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->kind = notK;
  e->val.notE.note = note;
  return e;
}

EXP *makeEXPfunccall(char *id, EXP_LIST *act_list) {
  EXP *e;
  e = NEW(EXP);
  e->kind = func_callK;
  e->val.func_callE.id = id;
  e->val.func_callE.act_list = act_list;
  return e;
}

EXP *makeEXPvar(VARIABLE *var) {
  EXP *e;
  e = NEW(EXP);
  e->kind = varK;
  e->val.var = var;
  return e;
}

EXP_LIST *makeEXPLIST(EXP *exp, EXP_LIST *next) {
  EXP_LIST *e;
  e = NEW(EXP_LIST);
  e->exp = exp;
  e->next = next;
  return e;
}
