#ifndef __regalloc_h
#define __regalloc_h

#include "memory.h"
#include "tree.h"
#include "symbol.h"
#include "codegen.h"

LINKED_LIST *registerAllocation(LINKED_LIST *l);

REGISTER *createREGISTER(int i, char *id);

void setREGISTER(REGISTER *reg);

void processINSTRUCTION();

#endif
