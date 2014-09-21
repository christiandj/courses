#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "regalloc.h"

REGISTER *eax; // Accumulator Register
REGISTER *ebx; // Base Register
REGISTER *ecx; // Counter Register
REGISTER *edx; // Data Register
REGISTER *esi; // Source Index
REGISTER *edi; // Destination Index
REGISTER *ebp; // Base Pointer
REGISTER *esp; // Stack Pointer

LINKED_LIST *currentRec = NULL;

int stackId = 0;
int temporaries = 0;
int variables = 0;

LINKED_LIST *registerAllocation(LINKED_LIST *l) {
  eax = createREGISTER(0, "%eax");
  ebx = createREGISTER(1, "%ebx");
  ecx = createREGISTER(2, "%ecx");
  edx = createREGISTER(3, "%edx");
  esi = createREGISTER(4, "%esi");
  edi = createREGISTER(5, "%edi");
  ebp = createREGISTER(6, "%ebp");
  esp = createREGISTER(7, "%esp");
  currentRec = l;
  if (currentRec != NULL) {
    processINSTRUCTION();
  }
  while (currentRec->next != NULL) {
    currentRec = currentRec->next;
    processINSTRUCTION();
  }
  return l;
}

REGISTER *createREGISTER(int i, char *id) {
  REGISTER *r = NEW(REGISTER);
  r->registerid = i;
  r->registername = malloc(strlen(id));
  r->registervalue = 0;
  strcpy(r->registername, id);
  return r;
}

void setREGISTER(REGISTER *reg) {
  if (reg != NULL) {
    char *id;
    switch (reg->registerid) {
      case 0:
        id = "%eax";
        reg->registername = malloc(strlen(id));
        strcpy(reg->registername, id);
        break;
      case 1:
        id = "%ebx";
        reg->registername = malloc(strlen(id));
        strcpy(reg->registername, id);
        break;
      case 2:
        id = "%ecx";
        reg->registername = malloc(strlen(id));
        strcpy(reg->registername, id);
        break;
      case 3:
        id = "%edx";
        reg->registername = malloc(strlen(id));
        strcpy(reg->registername, id);
        break;
      case 4:
        id = "%esi";
        reg->registername = malloc(strlen(id));
        strcpy(reg->registername, id);
        break;
      case 5:
        id = "%edi";
        reg->registername = malloc(strlen(id));
        strcpy(reg->registername, id);
        break;
      case 6:
        id = "%ebp";
        reg->registername = malloc(strlen(id));
        strcpy(reg->registername, id);
        break;
      case 7:
        id = "%esp";
        reg->registername = malloc(strlen(id));
        strcpy(reg->registername, id);
        break;
      default:
        if (reg->registerid > stackId) {
          // if (reg->registername == NULL) {
            temporaries++;
            char *stackCounter = (char *)Malloc(8);
            sprintf(stackCounter, "-%d", ((temporaries + variables) * 4) + 16);
            strcat(stackCounter, "(%ebp)");
            reg->registername = stackCounter;
            stackId = reg->registerid;
          // }
        }
        break;
    }
  }
}

void processINSTRUCTION() {
  INSTRUCTION *ins = currentRec->current;
  LINKED_LIST *l;
  if (ins != NULL) {
    switch (ins->kind) {
      case iintaddK:
        setREGISTER(ins->u.CONST_ARGUMENT.rb);
        break;
      case iaddK:
        setREGISTER(ins->u.ARGUMENT.ra);
        setREGISTER(ins->u.ARGUMENT.rb);
        if (ins->u.ARGUMENT.ra->registerid < 0 || ins->u.ARGUMENT.ra->registerid > 7) {
          if (ins->u.ARGUMENT.rb->registerid < 0 || ins->u.ARGUMENT.rb->registerid > 7) {
            l = NEW(LINKED_LIST);
            l->current = NEW(INSTRUCTION);
            l->current->kind = imovK;
            l->current->u.ARGUMENT.ra = ins->u.ARGUMENT.ra;
            l->current->u.ARGUMENT.rb = ecx;
            ins->u.ARGUMENT.ra = ecx;
            l->next = currentRec;
            l->prev = currentRec->prev;
            currentRec->prev->next = l;
            currentRec->prev = l;
          }
        }
        break;
      case isubK:
        setREGISTER(ins->u.ARGUMENT.ra);
        setREGISTER(ins->u.ARGUMENT.rb);
        if (ins->u.ARGUMENT.ra->registerid < 0 || ins->u.ARGUMENT.ra->registerid > 7) {
          if (ins->u.ARGUMENT.rb->registerid < 0 || ins->u.ARGUMENT.rb->registerid > 7) {
            l = NEW(LINKED_LIST);
            l->current = NEW(INSTRUCTION);
            l->current->kind = imovK;
            l->current->u.ARGUMENT.ra = ins->u.ARGUMENT.ra;
            l->current->u.ARGUMENT.rb = ecx;
            ins->u.ARGUMENT.ra = ecx;
            l->next = currentRec;
            l->prev = currentRec->prev;
            currentRec->prev->next = l;
            currentRec->prev = l;
          }
        }
        break;
      case imulK:
        setREGISTER(ins->u.ARGUMENT.ra);
        setREGISTER(ins->u.ARGUMENT.rb);
        if (ins->u.ARGUMENT.ra->registerid < 0 || ins->u.ARGUMENT.ra->registerid > 7) {
          if (ins->u.ARGUMENT.rb->registerid < 0 || ins->u.ARGUMENT.rb->registerid > 7) {
            l = NEW(LINKED_LIST);
            l->current = NEW(INSTRUCTION);
            l->current->kind = imovK;
            l->current->u.ARGUMENT.ra = ins->u.ARGUMENT.rb;
            l->current->u.ARGUMENT.rb = eax;
            ins->u.ARGUMENT.rb = eax;
            l->next = currentRec;
            l->prev = currentRec->prev;
            currentRec->prev->next = l;
            currentRec->prev = l;
          }
        }
        break;
      case idivK:
        setREGISTER(ins->u.ARGUMENT.ra);
        l = NEW(LINKED_LIST);
        l->current = NEW(INSTRUCTION);
        l->current->kind = imovK;
        l->current->u.ARGUMENT.ra = ins->u.ARGUMENT.ra;
        l->current->u.ARGUMENT.rb = ecx;
        ins->u.ARGUMENT.ra = ecx;
        l->next = currentRec;
        l->prev = currentRec->prev;
        currentRec->prev->next = l;
        currentRec->prev = l;
        break;
      case iandK:
        setREGISTER(ins->u.ARGUMENT.ra);
        setREGISTER(ins->u.ARGUMENT.rb);
        if (ins->u.ARGUMENT.ra->registerid < 0 || ins->u.ARGUMENT.ra->registerid > 7) {
          if (ins->u.ARGUMENT.rb->registerid < 0 || ins->u.ARGUMENT.rb->registerid > 7) {
            l = NEW(LINKED_LIST);
            l->current = NEW(INSTRUCTION);
            l->current->kind = imovK;
            l->current->u.ARGUMENT.ra = ins->u.ARGUMENT.ra;
            l->current->u.ARGUMENT.rb = ecx;
            ins->u.ARGUMENT.ra = ecx;
            l->next = currentRec;
            l->prev = currentRec->prev;
            currentRec->prev->next = l;
            currentRec->prev = l;
          }
        }
        break;
      case iorK:
        setREGISTER(ins->u.ARGUMENT.ra);
        setREGISTER(ins->u.ARGUMENT.rb);
        if (ins->u.ARGUMENT.ra->registerid < 0 || ins->u.ARGUMENT.ra->registerid > 7) {
          if (ins->u.ARGUMENT.rb->registerid < 0 || ins->u.ARGUMENT.rb->registerid > 7) {
            l = NEW(LINKED_LIST);
            l->current = NEW(INSTRUCTION);
            l->current->kind = imovK;
            l->current->u.ARGUMENT.ra = ins->u.ARGUMENT.ra;
            l->current->u.ARGUMENT.rb = ecx;
            ins->u.ARGUMENT.ra = ecx;
            l->next = currentRec;
            l->prev = currentRec->prev;
            currentRec->prev->next = l;
            currentRec->prev = l;
          }
        }
        break;
      case iintcmpK:
        setREGISTER(ins->u.CONST_ARGUMENT.rb);
        break;
      case icmpK:
        setREGISTER(ins->u.ARGUMENT.ra);
        setREGISTER(ins->u.ARGUMENT.rb);
        l = NEW(LINKED_LIST);
        l->current = NEW(INSTRUCTION);
        l->current->kind = imovK;
        l->current->u.ARGUMENT.ra = ins->u.ARGUMENT.rb;
        l->current->u.ARGUMENT.rb = ecx;
        ins->u.ARGUMENT.rb = ecx;
        l->next = currentRec;
        l->prev = currentRec->prev;
        currentRec->prev->next = l;
        currentRec->prev = l;
        break;
      case iintmovK:
        setREGISTER(ins->u.CONST_ARGUMENT.rb);
        break;
      case imovK:
        setREGISTER(ins->u.ARGUMENT.ra);
        setREGISTER(ins->u.ARGUMENT.rb);
        if (ins->u.ARGUMENT.ra->registerid < 0 || ins->u.ARGUMENT.ra->registerid > 7) {
          if (ins->u.ARGUMENT.rb->registerid < 0 || ins->u.ARGUMENT.rb->registerid > 7) {
            l = NEW(LINKED_LIST);
            l->current = NEW(INSTRUCTION);
            l->current->kind = imovK;
            l->current->u.ARGUMENT.ra = ins->u.ARGUMENT.ra;
            l->current->u.ARGUMENT.rb = ecx;
            ins->u.ARGUMENT.ra = ecx;
            l->next = currentRec;
            l->prev = currentRec->prev;
            currentRec->prev->next = l;
            currentRec->prev = l;
          }
        }
        break;
      case ipushK:
        assert(ins->u.ARGUMENT.ra);
        setREGISTER(ins->u.ARGUMENT.ra);
        break;
      case ipopK:
        setREGISTER(ins->u.ARGUMENT.ra);
        break;
      case iposmovK:
        setREGISTER(ins->u.POSMOV.ra);
        setREGISTER(ins->u.POSMOV.rb);
        if (ins->u.POSMOV.ra->registerid > 7) {
          l = NEW(LINKED_LIST);
          l->current = NEW(INSTRUCTION);
          l->current->kind = imovK;
          l->current->u.ARGUMENT.ra = ins->u.ARGUMENT.ra;
          l->current->u.ARGUMENT.rb = eax;
          l->next = currentRec;
          l->prev = currentRec->prev;
          currentRec->prev->next = l;
          currentRec->prev = l;
        }
        break;
      case iallocK:
        variables = ins->u.CONST_ARGUMENT.a;
        break;
      case ideallocK:
        ins->u.CONST_ARGUMENT.a = temporaries + variables;
        LINKED_LIST *l = currentRec;
        while (ins->kind != iallocK) {
          l = l->prev;
          ins = l->current;
        }
        l->current->u.CONST_ARGUMENT.a = temporaries + variables;
        stackId = 0;
        temporaries = 0;
        break;
      default:
        break;
    }
  }
}
