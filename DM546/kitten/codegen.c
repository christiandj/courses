#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "codegen.h"
#include "memory.h"
#include "tree.h"

// Labels
char *div_zero;
char *end_func;

// Counters
int comparisons;
int rno, parno, varno, mainvarno;
int countDiv, countAnd, countOr, countIf, countLoop;

// Main scope
SymbolTable *mscope;

REGISTER *eax; // Accumulator Register
REGISTER *ebx; // Base Register
REGISTER *ecx; // Counter Register
REGISTER *edx; // Data Register
REGISTER *esi; // Source Index
REGISTER *edi; // Destination Index
REGISTER *ebp; // Base Pointer
REGISTER *esp; // Stack Pointer

LINKED_LIST *head; // The first element in the list
LINKED_LIST *tail; // The last element in the list

LINKED_LIST *generateCode(MAIN *main, SymbolTable *t) {
  // Initialize the counters
  comparisons = 0;
  rno = 0;
  parno = 0;
  varno = 0;
  mainvarno = 0;
  countDiv = 0;
  countAnd = 0;
  countOr = 0;
  countIf = 0;
  countLoop = 0;
  // Initialize the symbol table
  mscope = initSymbolTable();
  // Initialize the linked list
  tail = NEW(LINKED_LIST);
  tail->next = NULL;
  tail->prev = NULL;
  tail->current = NEW(INSTRUCTION);
  tail->current->kind = ilabelK;
  // The directive .globl tells assembler that main is accessible outside the file
  tail->current->u.id = malloc(strlen(".globl main") + 1);
  strcpy(tail->current->u.id, ".globl main");
  head = tail;
  div_zero = malloc(strlen("divbyzero"));
  sprintf(div_zero, "divbyzero");
  putSymbolPar(mscope, "_intPrint", NULL);
  makeLABEL("_intPrint:");
  makeLABEL("    .string \"%d\\n\"");
  // The directive .data tells assembler that we are in the data segment
  makeLABEL(".data");
  makeLABEL("    .align 4");
  makeLABEL("_myspace:");
  makeLABEL("    .space 8");
  makeLABEL("_divbyzero_error:");
  makeLABEL("    .ascii \"Der opstod en fejl på kørselstidspunktet: Division med 0.\\n\"");
  // The directive .text tells assembler that we are in the text segment
  makeLABEL(".text");
  // General purpose registers for temporary data storage
  eax = makeREGISTER();
  ebx = makeREGISTER();
  ecx = makeREGISTER();
  edx = makeREGISTER();
  esi = makeREGISTER();
  edi = makeREGISTER();
  ebp = makeREGISTER();
  esp = makeREGISTER();
  // Global variables
  countParVar(t);
  mainvarno = varno;
  varno = 0;
  // Functions
  makeDECLLISTcg(main->decl_list);
  // MAIN START
  makeLABEL("main:");
  varno = mainvarno;
  // Save
  push(ebp);
  mov(esp, edx);
  mov(edx, ebp);
  push(ebx);
  push(esi);
  push(edi);
  makeLABEL("    movl   %esp, _myspace");
  intpush(0);
  allocVar();
  makeSTATEMENTLISTcg(main->statement_list, t);
  // Restore
  deallocVar();
  intadd(4, esp);
  pop(edi);
  pop(esi);
  pop(ebx);
  mov(ebp, edx);
  mov(edx, esp);
  pop(ebp);
  intmov(0, eax);
  returnCall();
  // MAIN END
  // DIVBYZERO START
  char *div_zeroL = malloc(strlen("divbyzero") + 4);
  sprintf(div_zeroL, "divbyzero:");
  makeLABEL(div_zeroL);
  makeLABEL("    pushl  $_divbyzero_error");
  call("printf");
  makeLABEL("    movl   _myspace, %esp");
  pop(edi);
  pop(esi);
  pop(ebx);
  pop(ebp);
  // The return value is 2
  intmov(2, eax);
  makeLABEL("    ret");
  // DIVBYZERO END
  makeLABEL("    .ident \"Kitten\"");
  return head;
}

REGISTER *makeREGISTERint(int i) {
  REGISTER *r = NEW(REGISTER);
  r->registerid = rno;
  r->registername = NULL;
  r->registervalue = i;
  rno++;
  intmov(i, r);
  return r;
}

REGISTER *makeREGISTER() {
  REGISTER *r = NEW(REGISTER);
  r->registerid = rno;
  r->registername = NULL;
  r->registervalue = 0;
  rno++;
  return r;
}

void makeFUNCTIONcg(FUNCTION *function) {
  parno = 0;
  varno = 0;
  STATEMENT *statement_list = function->statement_list;
  HEAD *head = function->head;
  SymbolTable *t = function->table;
  countParVar(t);
  if (parno != 0) {
    setPosPar(head->par_decl_list, t, parno);
  }
  size_t function_start = strlen(head->idH);
  char *a, *label, *function_count;
  a = malloc(function_start + 8);
  label = malloc(function_start + 8);
  sprintf(a, "%s", head->idH);
  strcpy(label, a);
  function_count = malloc(4);
  int counter = 0;
  SYMBOL *symbol = getSymbol(mscope, a);
  while (symbol != NULL) {
    strcpy(a, label);
    sprintf(function_count, "%d", counter);
    strcat(a, function_count);
    symbol = getSymbol(mscope, a);
    counter++;
  }
  strcat(label, function_count);
  putSymbolPar(mscope, label, NULL);
  strcpy(head->idH, label);
  function_start = strlen(head->idH);
  end_func = malloc(strlen("end") + function_start + 4);
  sprintf(end_func, "end_%s", label);
  char *function_end = malloc(strlen("end") + function_start + 4);
  sprintf(function_end, "end_%s:", label);
  strcat(label, ":");
  makeFUNCTIONLABEL(label);
  // Save
  push(ebp);
  mov(esp, edx);
  mov(edx, ebp);
  push(ebx);
  push(esi);
  push(edi);
  allocVar();
  makeSTATEMENTLISTcg(statement_list, function->table);
  makeLABEL(function_end);
  // Restore
  deallocVar();
  intadd(4, esp);
  pop(edi);
  pop(esi);
  pop(ebx);
  mov(ebp, edx);
  mov(edx, esp);
  pop(ebp);
  parno = 0;
  varno = 0;
  returnCall();
}

void makeDECLLISTcg(DECL_LIST *decl_list) {
  int updaterno = rno;
  if (decl_list != NULL) {
    if (decl_list->declaration != NULL) {
      makeFUNCTIONcg(decl_list->declaration->function);
      rno = updaterno;
    }
    if (decl_list->decl_list != NULL) {
      makeDECLLISTcg(decl_list->decl_list);
    }
  }
}

void makeSTATEMENTcg(STATEMENT *statement, SymbolTable *t) {
  char *label, *labelEnd, *label1;
  REGISTER *ra, *rb, *rc;
  switch (statement->kind) {
    case returnK:
      ra = makeEXPcg(statement->val.returnS.exp, t);
      if (ra != NULL) {
        mov(ra, eax);
      } else {
        rb = makeREGISTERint(0);
        mov(rb, eax);
      }
      jmp(end_func);
      break;
    case writeK:
      push(ecx);
      push(edx);
      ra = makeEXPcg(statement->val.writeS.exp, t);
      assert(ra);
      push(ra);
      makeLABEL("    pushl  $_intPrint");
      call("printf");
      intadd(8, esp);
      pop(edx);
      pop(ecx);
      break;
    case assignK:
      ra = makeEXPcg(statement->val.assignS.exp, t);
      if (ra != NULL) {
        rb = makeREGISTER();
        mov(ra, rb);
        rc = makeVARcg(statement->val.assignS.variable, t);
        mov(rb, rc);
      } else {
        rb = makeVARcg(statement->val.assignS.variable, t);
        intmov(0, rb);
      }
      break;
    case ifK:
      ra = makeEXPcg(statement->val.ifS.exp, t);
      assert(ra);
      labelEnd = malloc(strlen("end_if:") + 4);
      sprintf(labelEnd, "end_if%d", countIf);
      countIf++;
      intcmp(1, ra);
      jne(labelEnd);
      makeSTATEMENTcg(statement->val.ifS.statement, t);
      strcat(labelEnd, ":");
      makeLABEL(labelEnd);
      break;
    case loopK:
      label1 = malloc(strlen("loop") + 4);
      sprintf(label1, "loop%d", countLoop);
      label = malloc(strlen("loop:") + 4);
      sprintf(label, "loop%d:", countLoop);
      makeLABEL(label);
      labelEnd = malloc(strlen("end_loop:") + 4);
      sprintf(labelEnd, "end_loop%d", countLoop);
      countLoop++;
      makeSTATEMENTcg(statement->val.loopS.statement, t);
      jmp(label1);
      strcat(labelEnd, ":");
      makeLABEL(labelEnd);
      break;
    case continueK:
      label = malloc(strlen("loop") + 4);
      sprintf(label, "loop%d", countLoop - 1);
      jmp(label);
      break;
    case breakK:
      label = malloc(strlen("end_loop") + 4);
      sprintf(label, "end_loop%d", countLoop - 1);
      jmp(label);
      break;
    case curly_bracketK:
      makeSTATEMENTcg(statement->val.curly_bracketS.statement, t);
      break;
    case statement_listK:
      makeSTATEMENTLISTcg(statement, t);
      break;
    default:
      break;
  }
}

void makeSTATEMENTLISTcg(STATEMENT *statement_list, SymbolTable *t) {
  if (statement_list->kind == statement_listK) {
    if (statement_list->val.statement_listS.statement != NULL) {
      makeSTATEMENTcg(statement_list->val.statement_listS.statement, t);
    }
    if (statement_list->val.statement_listS.next != NULL) {
      makeSTATEMENTLISTcg(statement_list->val.statement_listS.next, t);
    }
  } else {
    makeSTATEMENTcg(statement_list, t);
  }
}

int getVARposition(char *id, int pos, SymbolTable *t) {
  SYMBOL *s;
  int hashValue = Hash(id);
  if (t->table[hashValue] != NULL) {
    s = t->table[hashValue];
    int cmpname = strcmp(s->name, id);
    while (cmpname != 0 && s->next != NULL) {
      s = s->next;
      cmpname = strcmp(s->name, id);
    }
    if (cmpname == 0) {
      return pos;
    }
  }
  if (t->next != NULL) {
    pos++;
    pos = getVARposition(id, pos, t->next);
    return pos;
  }
  return pos;
}

REGISTER *makeVARcg(VARIABLE *var, SymbolTable *t) {
  REGISTER *r = NEW(REGISTER);
  // We need to enter the default case in setREGISTER in regalloc.c
  r->registerid = -1;
  SYMBOL *s = getSymbol(t, var->idV);
  int pos = getVARposition(var->idV, 0, t);
  char *label;
  if (pos == 1) {
    // Function scope
    posMov(ebp, edx, 8, 0);
    label = malloc(strlen("(%edx)") + 4);
    sprintf(label, "%d", s->pos);
    strcat(label, "(%edx)");
  } else {
    // Main scope
    label = malloc(strlen("(%ebp)") + 4);
    sprintf(label, "%d", s->pos);
    strcat(label, "(%ebp)");
  }
  r->registername = label;
  return r;
}

REGISTER *makeEXPcg(EXP *exp, SymbolTable *t) {
  char *label, *labelEnd;
  SYMBOL *symbol;
  REGISTER *r;
  REGISTER *ra, *rb, *rc, *rd;
  switch (exp->kind) {
    case intconstK:
      r = makeREGISTERint(exp->val.intconstE);
      break;
    case timesK:
      ra = makeEXPcg(exp->val.timesE.left, t);
      assert(ra);
      rb = makeREGISTER();
      mov(ra, rb);
      rc = makeEXPcg(exp->val.timesE.right, t);
      assert(rc);
      rd = makeREGISTER();
      mul(rb, rc);
      mov(eax, rd);
      r = rd;
      break;
    case divK:
      ra = makeEXPcg(exp->val.divE.left, t);
      assert(ra);
      rb = makeREGISTER();
      mov(ra, rb);
      rc = makeEXPcg(exp->val.divE.right, t);
      assert(rc);
      intcmp(0, rc);
      je(div_zero);
      rd = makeREGISTER();
      mov(rb, eax);
      makeLABEL("    cltd");
      mydiv(rc);
      mov(eax, rd);
      r = rd;
      break;
    case plusK:
      ra = makeEXPcg(exp->val.plusE.left, t);
      assert(ra);
      rb = makeREGISTER();
      mov(ra, rb);
      rc = makeEXPcg(exp->val.plusE.right, t);
      assert(rc);
      add(rc, rb);
      r = rb;
      break;
    case minusK:
      ra = makeEXPcg(exp->val.minusE.left, t);
      assert(ra);
      rb = makeREGISTER();
      mov(ra, rb);
      rc = makeEXPcg(exp->val.minusE.right, t);
      assert(rc);
      sub(rc, rb);
      r = rb;
      break;
    case eqK:
      ra = makeEXPcg(exp->val.eqE.left, t);
      if (ra == NULL) {
        rb = makeREGISTERint(0);
      } else {
        rb = makeREGISTER();
        mov(ra, rb);
      }
      rc = makeEXPcg(exp->val.eqE.right, t);
      if (rc == NULL) {
        cmp(makeREGISTERint(0), rb);
      } else {
        cmp(rc, rb);
      }
      label = malloc(strlen("false:") + 4);
      sprintf(label, "false%d", comparisons);
      labelEnd = malloc(strlen("end_comparison:") + 4);
      sprintf(labelEnd, "end_comparison%d", comparisons);
      jne(label);
      tail->next = NEW(LINKED_LIST);
      r = NEW(REGISTER);
      r->registerid = rno;
      r->registername = NULL;
      rno++;
      intmov(1, r);
      jmp(labelEnd);
      strcat(label, ":");
      makeLABEL(label);
      intmov(0, r);
      strcat(labelEnd, ":");
      makeLABEL(labelEnd);
      comparisons++;
      break;
    case neqK:
      ra = makeEXPcg(exp->val.neqE.left, t);
      if (ra == NULL) {
        rb = makeREGISTERint(0);
      } else {
        rb = makeREGISTER();
        mov(ra, rb);
      }
      rc = makeEXPcg(exp->val.neqE.right, t);
      if (rc == NULL) {
        cmp(makeREGISTERint(0), rb);
      } else {
        cmp(rc, rb);
      }
      label = malloc(strlen("true:") + 4);
      sprintf(label, "true%d", comparisons);
      labelEnd = malloc(strlen("end_comparison:") + 4);
      sprintf(label, "end_comparison%d", comparisons);
      je(label);
      tail->next = NEW(LINKED_LIST);
      r = NEW(REGISTER);
      r->registerid = rno;
      r->registername = NULL;
      rno++;
      intmov(1, r);
      jmp(labelEnd);
      strcat(label, ":");
      makeLABEL(label);
      intmov(0, r);
      strcat(labelEnd, ":");
      makeLABEL(labelEnd);
      comparisons++;
      break;
    case gtK:
      ra = makeEXPcg(exp->val.gtE.left, t);
      assert(ra);
      rb = makeREGISTER();
      mov(ra, rb);
      rc = makeEXPcg(exp->val.gtE.right, t);
      assert(rc);
      tail->next = NEW(LINKED_LIST);
      r = NEW(REGISTER);
      r->registerid = rno;
      r->registername = NULL;
      rno++;
      label = malloc(strlen("false:") + 4);
      sprintf(label, "false%d", comparisons);
      labelEnd = malloc(strlen("end_comparison:") + 4);
      sprintf(labelEnd, "end_comparison%d", comparisons);
      cmp(rc, rb);
      jle(label);
      intmov(1, r);
      jmp(labelEnd);
      strcat(label, ":");
      makeLABEL(label);
      intmov(0, r);
      strcat(labelEnd, ":");
      makeLABEL(labelEnd);
      comparisons++;
      break;
    case ltK:
      ra = makeEXPcg(exp->val.ltE.left, t);
      assert(ra);
      rb = makeREGISTER();
      mov(ra, rb);
      rc = makeEXPcg(exp->val.ltE.right, t);
      assert(rc);
      tail->next = NEW(LINKED_LIST);
      r = NEW(REGISTER);
      r->registerid = rno;
      r->registername = NULL;
      rno++;
      label = malloc(strlen("false:") + 4);
      sprintf(label, "false%d", comparisons);
      labelEnd = malloc(strlen("end_comparison:") + 4);
      sprintf(labelEnd, "end_comparison%d", comparisons);
      cmp(rc, rb);
      jge(label);
      intmov(1, r);
      jmp(labelEnd);
      strcat(label, ":");
      makeLABEL(label);
      intmov(0, r);
      strcat(labelEnd, ":");
      makeLABEL(labelEnd);
      comparisons++;
      break;
    case geqK:
      ra = makeEXPcg(exp->val.geqE.left, t);
      assert(ra);
      rb = makeREGISTER();
      mov(ra, rb);
      rc = makeEXPcg(exp->val.geqE.right, t);
      assert(rc);
      tail->next = NEW(LINKED_LIST);
      r = NEW(REGISTER);
      r->registerid = rno;
      r->registername = NULL;
      rno++;
      label = malloc(strlen("false:") + 4);
      sprintf(label, "false%d", comparisons);
      labelEnd = malloc(strlen("end_comparison:") + 4);
      sprintf(labelEnd, "end_comparison%d", comparisons);
      cmp(rc, rb);
      jl(label);
      intmov(1, r);
      jmp(labelEnd);
      strcat(label, ":");
      makeLABEL(label);
      intmov(0, r);
      strcat(labelEnd, ":");
      makeLABEL(labelEnd);
      comparisons++;
      break;
    case leqK:
      ra = makeEXPcg(exp->val.leqE.left, t);
      assert(ra);
      rb = makeREGISTER();
      mov(ra, rb);
      rc = makeEXPcg(exp->val.leqE.right, t);
      assert(rc);
      tail->next = NEW(LINKED_LIST);
      r = NEW(REGISTER);
      r->registerid = rno;
      r->registername = NULL;
      rno++;
      label = malloc(strlen("false:") + 4);
      sprintf(label, "false%d", comparisons);
      labelEnd = malloc(strlen("end_comparison:") + 4);
      sprintf(labelEnd, "end_comparison%d", comparisons);
      cmp(rc, rb);
      jg(label);
      intmov(1, r);
      jmp(labelEnd);
      strcat(label, ":");
      makeLABEL(label);
      intmov(0, r);
      strcat(labelEnd, ":");
      makeLABEL(labelEnd);
      comparisons++;
      break;
    case andK:
      ra = makeEXPcg(exp->val.andE.left, t);
      assert(ra);
      rb = makeREGISTER();
      mov(ra, rb);
      label = malloc(strlen("land:") + 4);
      sprintf(label, "land%d", countAnd);
      countAnd++;
      rc = rb;
      intcmp(1, rb);
      jne(label);
      rc = makeEXPcg(exp->val.andE.right, t);
      assert(rc);
      strcat(label, ":");
      makeLABEL(label);
      and(rc, rb);
      r = rb;
      break;
    case orK:
      ra = makeEXPcg(exp->val.orE.left, t);
      assert(ra);
      rb = makeREGISTER();
      mov(ra, rb);
      label = malloc(strlen("lor:") + 4);
      sprintf(label, "lor%d", countOr);
      countOr++;
      rc = rb;
      intcmp(1, rb);
      je(label);
      rc = makeEXPcg(exp->val.orE.right, t);
      assert(rc);
      strcat(label, ":");
      makeLABEL(label);
      or(rc, rb);
      r = rb;
      break;
    case notK:
      ra = makeEXPcg(exp->val.notE.note, t);
      assert(ra);
      label = malloc(strlen("false:") + 4);
      sprintf(label, "false%d", comparisons);
      labelEnd = malloc(strlen("end_comparison:") + 4);
      sprintf(labelEnd, "end_comparison%d", comparisons);
      intcmp(1, ra);
      jne(label);
      intmov(0, ra);
      jmp(labelEnd);
      strcat(label, ":");
      makeLABEL(label);
      intmov(1, ra);
      strcat(labelEnd, ":");
      makeLABEL(labelEnd);
      comparisons++;
      r = ra;
      break;
    case func_callK:
      varno = 0;
      parno = 0;
      int i = getVARposition(exp->val.func_callE.id, 0, t);
      symbol = getSymbol(t, exp->val.func_callE.id);
      countParVar(symbol->val.function->table);
      if (parno > 0) {
        makeEXPLISTcg(exp->val.func_callE.act_list, t);
      }
      if (i == 0) {
        push(ebp);
      } else {
        posMov(ebp, edx, 8, 0);
        push(edx);
      }
      call(symbol->val.function->head->idH);
      if (i > 0) {
        pop(edx);
      } else {
        pop(ebp);
      }
      if (parno > 0) {
        intadd(parno * 4, esp);
      }
      parno = 0;
      varno = 0;
      r = eax;
      break;
    case varK:
      r = makeVARcg(exp->val.var, t);
      break;
  }
  return r;
}

void makeEXPLISTcg(EXP_LIST *explist, SymbolTable *t) {
  REGISTER *ra = makeEXPcg(explist->exp, t);
  assert(ra);
  push(ra);
  if (explist->next != NULL) {
    makeEXPLISTcg(explist->next, t);
  }
}

void makeFUNCTIONLABEL(char *label) {
  LINKED_LIST *l = NEW(LINKED_LIST);
  l->current = NEW(INSTRUCTION);
  l->current->kind = iflabelK;
  l->current->u.id = malloc(strlen(label) + 1);
  strcpy(l->current->u.id, label);
  l->next = NULL;
  l->prev = tail;
  tail->next = l;
  tail = l;
}

void makeLABEL(char *label) {
  LINKED_LIST *l = NEW(LINKED_LIST);
  l->current = NEW(INSTRUCTION);
  l->current->kind = ilabelK;
  l->current->u.id = malloc(strlen(label) + 1);
  strcpy(l->current->u.id, label);
  l->next = NULL;
  l->prev = tail;
  tail->next = l;
  tail = l;
}

void intadd(int a, REGISTER *ra) {
  LINKED_LIST *l = NEW(LINKED_LIST);
  l->current = NEW(INSTRUCTION);
  l->current->kind = iintaddK;
  l->current->u.CONST_ARGUMENT.a = a;
  l->current->u.CONST_ARGUMENT.rb = ra;
  tail->next = l;
  l->prev = tail;
  tail = l;
}

void add(REGISTER *ra, REGISTER *rb) {
  LINKED_LIST *l = NEW(LINKED_LIST);
  l->current = NEW(INSTRUCTION);
  l->current->kind = iaddK;
  l->current->u.ARGUMENT.ra = ra;
  l->current->u.ARGUMENT.rb = rb;
  tail->next = l;
  l->prev = tail;
  tail = l;
}

void sub(REGISTER *ra, REGISTER *rb) {
  LINKED_LIST *l = NEW(LINKED_LIST);
  l->current = NEW(INSTRUCTION);
  l->current->kind = isubK;
  l->current->u.ARGUMENT.ra = ra;
  l->current->u.ARGUMENT.rb = rb;
  tail->next = l;
  l->prev = tail;
  tail = l;
}

void mul(REGISTER *ra, REGISTER *rb) {
  LINKED_LIST *l = NEW(LINKED_LIST);
  l->current = NEW(INSTRUCTION);
  l->current->kind = imulK;
  l->current->u.ARGUMENT.ra = ra;
  l->current->u.ARGUMENT.rb = rb;
  tail->next = l;
  l->prev = tail;
  tail = l;
}

void mydiv(REGISTER *ra) {
  LINKED_LIST *l = NEW(LINKED_LIST);
  l->current = NEW(INSTRUCTION);
  l->current->kind = idivK;
  l->current->u.ARGUMENT.ra = ra;
  tail->next = l;
  l->prev = tail;
  tail = l;
}

void and(REGISTER *ra, REGISTER *rb) {
  LINKED_LIST *l = NEW(LINKED_LIST);
  l->current = NEW(INSTRUCTION);
  l->current->kind = iandK;
  l->current->u.ARGUMENT.ra = ra;
  l->current->u.ARGUMENT.rb = rb;
  tail->next = l;
  l->prev = tail;
  tail = l;
}

void or(REGISTER *ra, REGISTER *rb) {
  LINKED_LIST *l = NEW(LINKED_LIST);
  l->current = NEW(INSTRUCTION);
  l->current->kind = iorK;
  l->current->u.ARGUMENT.ra = ra;
  l->current->u.ARGUMENT.rb = rb;
  tail->next = l;
  l->prev = tail;
  tail = l;
}

void intcmp(int a, REGISTER *ra) {
  LINKED_LIST *l = NEW(LINKED_LIST);
  l->current = NEW(INSTRUCTION);
  l->current->kind = iintcmpK;
  l->current->u.CONST_ARGUMENT.a = a;
  l->current->u.CONST_ARGUMENT.rb = ra;
  tail->next = l;
  l->prev = tail;
  tail = l;
}

void cmp(REGISTER *ra, REGISTER *rb) {
  LINKED_LIST *l = NEW(LINKED_LIST);
  l->current = NEW(INSTRUCTION);
  l->current->kind = icmpK;
  l->current->u.ARGUMENT.ra = ra;
  l->current->u.ARGUMENT.rb = rb;
  tail->next = l;
  l->prev = tail;
  tail = l;
}

void intmov(int a, REGISTER *ra) {
  LINKED_LIST *l = NEW(LINKED_LIST);
  l->current = NEW(INSTRUCTION);
  l->current->kind = iintmovK;
  l->current->u.CONST_ARGUMENT.a = a;
  l->current->u.CONST_ARGUMENT.rb = ra;
  tail->next = l;
  l->prev = tail;
  tail = l;
}

void mov(REGISTER *ra, REGISTER *rb) {
  LINKED_LIST *l = NEW(LINKED_LIST);
  l->current = NEW(INSTRUCTION);
  l->current->kind = imovK;
  l->current->u.ARGUMENT.ra = ra;
  l->current->u.ARGUMENT.rb = rb;
  tail->next = l;
  l->prev = tail;
  tail = l;
}

// Always jumps
void jmp(char *label) {
  LINKED_LIST *l = NEW(LINKED_LIST);
  l->current = NEW(INSTRUCTION);
  l->current->kind = ijmpK;
  l->current->u.id = malloc(strlen(label) + 1);
  strcpy(l->current->u.id, label);
  tail->next = l;
  l->prev = tail;
  tail = l;
}

// Jumps if equal
void je(char *label) {
  LINKED_LIST *l = NEW(LINKED_LIST);
  l->current = NEW(INSTRUCTION);
  l->current->kind = ijeK;
  l->current->u.id = malloc(strlen(label) + 1);
  strcpy(l->current->u.id, label);
  tail->next = l;
  l->prev = tail;
  tail = l;
}

// Jumps if not equal
void jne(char *label) {
  LINKED_LIST *l = NEW(LINKED_LIST);
  l->current = NEW(INSTRUCTION);
  l->current->kind = ijneK;
  l->current->u.id = malloc(strlen(label) + 1);
  strcpy(l->current->u.id, label);
  tail->next = l;
  l->prev = tail;
  tail = l;
}

// Jumps if less than
void jl(char *label) {
  LINKED_LIST *l = NEW(LINKED_LIST);
  l->current = NEW(INSTRUCTION);
  l->current->kind = ijlK;
  l->current->u.id = malloc(strlen(label) + 1);
  strcpy(l->current->u.id, label);
  tail->next = l;
  l->prev = tail;
  tail = l;
}

// Jumps if less than or equal to
void jle(char *label) {
  LINKED_LIST *l = NEW(LINKED_LIST);
  l->current = NEW(INSTRUCTION);
  l->current->kind = ijleK;
  l->current->u.id = malloc(strlen(label) + 1);
  strcpy(l->current->u.id, label);
  tail->next = l;
  l->prev = tail;
  tail = l;
}

// Jumps if greater than
void jg(char *label) {
  LINKED_LIST *l = NEW(LINKED_LIST);
  l->current = NEW(INSTRUCTION);
  l->current->kind = ijgK;
  l->current->u.id = malloc(strlen(label) + 1);
  strcpy(l->current->u.id, label);
  tail->next = l;
  l->prev = tail;
  tail = l;
}

// Jumps if greater than or equal to
void jge(char *label) {
  LINKED_LIST *l = NEW(LINKED_LIST);
  l->current = NEW(INSTRUCTION);
  l->current->kind = ijgeK;
  l->current->u.id = malloc(strlen(label) + 1);
  strcpy(l->current->u.id, label);
  tail->next = l;
  l->prev = tail;
  tail = l;
}

void intpush(int a) {
  LINKED_LIST *l = NEW(LINKED_LIST);
  l->current = NEW(INSTRUCTION);
  l->current->kind = iintpushK;
  l->current->u.CONST_ARGUMENT.a = a;
  tail->next = l;
  l->prev = tail;
  tail = l;
}

void push(REGISTER *ra) {
  LINKED_LIST *l = NEW(LINKED_LIST);
  l->current = NEW(INSTRUCTION);
  l->current->kind = ipushK;
  l->current->u.ARGUMENT.ra = ra;
  l->current->u.ARGUMENT.rb = NULL;
  tail->next = l;
  l->prev = tail;
  tail = l;
}

void pop(REGISTER *ra) {
  LINKED_LIST *l = NEW(LINKED_LIST);
  l->current = NEW(INSTRUCTION);
  l->current->kind = ipopK;
  l->current->u.ARGUMENT.ra = ra;
  l->current->u.ARGUMENT.rb = NULL;
  tail->next = l;
  l->prev = tail;
  tail = l;
}

void call(char *label) {
  LINKED_LIST *l = NEW(LINKED_LIST);
  l->current = NEW(INSTRUCTION);
  l->current->kind = icallK;
  l->current->u.id = malloc(strlen(label) + 1);
  strcpy(l->current->u.id, label);
  tail->next = l;
  l->prev = tail;
  tail = l;
}

void returnCall() {
  LINKED_LIST *l = NEW(LINKED_LIST);
  l->current = NEW(INSTRUCTION);
  l->current->kind = ireturnK;
  l->current->u.id = malloc(strlen("    ret") + 1);
  strcpy(l->current->u.id, "    ret");
  l->next = NULL;
  l->prev = tail;
  tail->next = l;
  tail = l;
}

void posMov(REGISTER *ra, REGISTER *rb, int posa, int posb) {
  LINKED_LIST *l = NEW(LINKED_LIST);
  l->current = NEW(INSTRUCTION);
  l->current->kind = iposmovK;
  l->current->u.POSMOV.ra = ra;
  l->current->u.POSMOV.rb = rb;
  l->current->u.POSMOV.posa = posa;
  l->current->u.POSMOV.posb = posb;
  tail->next = l;
  l->prev = tail;
  tail = l;
}

void setPosPar(PAR_DECL_LIST *par_decl_list, SymbolTable *t, int i) {
  SYMBOL *symbol = getSymbol(t, par_decl_list->par->id);
  symbol->pos = (8 + (4 * i));
  i--;
  if (i > 0) {
    setPosPar(par_decl_list->next, t, i);
  }
}

void countParVar(SymbolTable *t) {
  int i;
  for (i = 0; i < HashSize; i++) {
    if (t->table[i] != NULL) {
      if (t->table[i]->kind == sparK) {
        parno++;
      }
      if (t->table[i]->kind == svarK) {
        varno++;
        t->table[i]->pos = (-1) * (16 + varno * 4);
      }
      SYMBOL *sNext = t->table[i]->next;
      while (sNext != NULL) {
        if (t->table[i]->kind == sparK) {
          parno++;
        }
        if (t->table[i]->kind == svarK) {
          varno++;
          t->table[i]->pos = (-1) * (16 + varno * 4);
        }
        sNext = sNext->next;
      }
    }
  }
}

void allocVar() {
  LINKED_LIST *l = NEW(LINKED_LIST);
  l->current = NEW(INSTRUCTION);
  l->current->kind = iallocK;
  l->current->u.CONST_ARGUMENT.a = varno;
  l->current->u.CONST_ARGUMENT.rb = NULL;
  tail->next = l;
  l->prev = tail;
  tail = l;
}

void deallocVar() {
  LINKED_LIST *l = NEW(LINKED_LIST);
  l->current = NEW(INSTRUCTION);
  l->current->kind = ideallocK;
  l->current->u.CONST_ARGUMENT.a = 0;
  l->current->u.CONST_ARGUMENT.rb = NULL;
  tail->next = l;
  l->prev = tail;
  tail = l;
}

// For debugging purposes only
const char* getInstrKind(INSTRUCTION *instruction) {
  switch (instruction->kind) {
    case ilabelK:
      return "";
    case iflabelK:
      return "";
    case iintaddK:
      return "    # DEBUG: iintaddK\n";
    case iaddK:
      return "    # DEBUG: iaddK\n";
    case isubK:
      return "    # DEBUG: isubK\n";
    case imulK:
      return "    # DEBUG: imulK\n";
    case idivK:
      return "    # DEBUG: idivK\n";
    case iandK:
      return "    # DEBUG: iandK\n";
    case iorK:
      return "    # DEBUG: iorK\n";
    case iintcmpK:
      return "    # DEBUG: iintcmpK\n";
    case icmpK:
      return "    # DEBUG: icmpK\n";
    case iintmovK:
      return "    # DEBUG: iintmovK\n";
    case imovK:
      return "    # DEBUG: imovK\n";
    case ijmpK:
      return "    # DEBUG: ijmpK\n";
    case ijeK:
      return "    # DEBUG: ijeK\n";
    case ijneK:
      return "    # DEBUG: ijneK\n";
    case ijlK:
      return "    # DEBUG: ijlK\n";
    case ijleK:
      return "    # DEBUG: ijleK\n";
    case ijgK:
      return "    # DEBUG: ijgK\n";
    case ijgeK:
      return "    # DEBUG: ijgeK\n";
    case iintpushK:
      return "    # DEBUG: iintpushK\n";
    case ipushK:
      return "    # DEBUG: ipushK\n";
    case ipopK:
      return "    # DEBUG: ipopK\n";
    case icallK:
      return "    # DEBUG: icallK\n";
    case ireturnK:
      return "    # DEBUG: ireturnK\n";
    case iposmovK:
      return "    # DEBUG: iposmovK\n";
    case iallocK:
      return "    # DEBUG: iallocK\n";
    case ideallocK:
      return "    # DEBUG: ideallocK\n";
    default:
      return "    # DEBUG: unknown\n";
  }
}

void printInstruction(INSTRUCTION *instruction) {
  char *stack = malloc(strlen("%esp"));
  strcpy(stack, "%esp");
  switch (instruction->kind) {
    case ilabelK:
      fprintf(stdout, "%s\n", instruction->u.id);
      break;
    case iflabelK:
      fprintf(stdout, "%s\n", instruction->u.id);
      break;
    case iintaddK:
      fprintf(stdout, "    addl   $%d, %s\n", instruction->u.CONST_ARGUMENT.a, instruction->u.CONST_ARGUMENT.rb->registername);
      break;
    case iaddK:
      fprintf(stdout, "    addl   %s, %s\n", instruction->u.ARGUMENT.ra->registername, instruction->u.ARGUMENT.rb->registername);
      break;
    case isubK:
      fprintf(stdout, "    subl   %s, %s\n", instruction->u.ARGUMENT.ra->registername, instruction->u.ARGUMENT.rb->registername);
      break;
    case imulK:
      fprintf(stdout, "    imul   %s, %s\n", instruction->u.ARGUMENT.ra->registername, instruction->u.ARGUMENT.rb->registername);
      break;
    case idivK:
      fprintf(stdout, "    idiv   %s\n", instruction->u.ARGUMENT.ra->registername);
      break;
    case iandK:
      fprintf(stdout, "    and    %s, %s\n", instruction->u.ARGUMENT.ra->registername, instruction->u.ARGUMENT.rb->registername);
      break;
    case iorK:
      fprintf(stdout, "    or     %s, %s\n", instruction->u.ARGUMENT.ra->registername, instruction->u.ARGUMENT.rb->registername);
      break;
    case iintcmpK:
      fprintf(stdout, "    cmp    $%d, %s\n", instruction->u.CONST_ARGUMENT.a, instruction->u.CONST_ARGUMENT.rb->registername);
      break;
    case icmpK:
      fprintf(stdout, "    cmp    %s, %s\n", instruction->u.ARGUMENT.ra->registername, instruction->u.ARGUMENT.rb->registername);
      break;
    case iintmovK:
      fprintf(stdout, "    movl   $%d, %s\n", instruction->u.CONST_ARGUMENT.a, instruction->u.CONST_ARGUMENT.rb->registername);
      break;
    case imovK:
      fprintf(stdout, "    movl   %s, %s\n", instruction->u.ARGUMENT.ra->registername, instruction->u.ARGUMENT.rb->registername);
      break;
    case ijmpK:
      fprintf(stdout, "    jmp    %s\n", instruction->u.id);
      break;
    case ijeK:
      fprintf(stdout, "    je     %s\n", instruction->u.id);
      break;
    case ijneK:
      fprintf(stdout, "    jne    %s\n", instruction->u.id);
      break;
    case ijlK:
      fprintf(stdout, "    jl     %s\n", instruction->u.id);
      break;
    case ijleK:
      fprintf(stdout, "    jle    %s\n", instruction->u.id);
      break;
    case ijgK:
      fprintf(stdout, "    jg     %s\n", instruction->u.id);
      break;
    case ijgeK:
      fprintf(stdout, "    jge    %s\n", instruction->u.id);
      break;
    case iintpushK:
      fprintf(stdout, "    pushl  $%d\n", instruction->u.CONST_ARGUMENT.a);
      break;
    case ipushK:
      fprintf(stdout, "    pushl  %s\n", instruction->u.ARGUMENT.ra->registername);
      break;
    case ipopK:
      fprintf(stdout, "    popl   %s\n", instruction->u.ARGUMENT.ra->registername);
      break;
    case icallK:
      fprintf(stdout, "    call   %s\n", instruction->u.id);
      break;
    case ireturnK:
      fprintf(stdout, "%s\n", instruction->u.id);
      break;
    case iposmovK:
      if (instruction->u.POSMOV.posa > 0) {
        fprintf(stdout, "    movl   %d(%s),", instruction->u.POSMOV.posa, instruction->u.POSMOV.ra->registername);
      } else {
        fprintf(stdout, "    movl   %s,", instruction->u.POSMOV.ra->registername);
      }
      if (instruction->u.POSMOV.posb > 0) {
        fprintf(stdout, "%d(%s)\n", instruction->u.POSMOV.posb, instruction->u.POSMOV.rb->registername);
      } else {
        fprintf(stdout, "%s\n", instruction->u.POSMOV.rb->registername);
      }
      break;
    case iallocK:
      if (instruction->u.CONST_ARGUMENT.a > 0) {
        fprintf(stdout, "    addl   $-%d, %s\n", instruction->u.CONST_ARGUMENT.a * 4, stack);
      }
      break;
    case ideallocK:
      if (instruction->u.CONST_ARGUMENT.a > 0) {
        fprintf(stdout, "    addl   $%d, %s\n", instruction->u.CONST_ARGUMENT.a * 4, stack);
      }
      break;
    default:
      break;
  }
}

void emission(LINKED_LIST *l) {
  if (l->current != NULL) {
    // fprintf(stdout, "%s", getInstrKind(l->current));
    printInstruction(l->current);
  }
  if (l->next != NULL) {
    emission(l->next);
  }
}
