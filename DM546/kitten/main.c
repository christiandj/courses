#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include "tree.h"
#include "pretty.h"
#include "symbol.h"
#include "dumpsymbol.h"
#include "traversal.h"
#include "codegen.h"
#include "regalloc.h"

int lineno;

int yyparse();

MAIN *theprogram;

int main(int argc, char **argv) {
  int c;
  bool debug_mode = false;
  bool verbose_mode = false;
  while ((c = getopt(argc, argv, "dv")) != -1) {
    switch (c) {
      case 'd':
        debug_mode = true;
        break;
      case 'v':
        verbose_mode = true;
        break;
      default: /* '?' */
        fprintf(stderr, "Anvendelse: %s [-d] [-v]\n", argv[0]);
        exit(1);
    }
  }
  lineno = 1;
  if (verbose_mode) {
    fprintf(stderr, "Leksikalsk og syntaktisk analyse udføres ...\n");
  }
  int parse = yyparse();
  if (parse != 0) {
    fprintf(stderr, "Der opstod en fejl under den leksikalske eller syntaktiske analyse.\n");
    return 1;
  }
  if (verbose_mode) {
    fprintf(stderr, "Leksikalsk og syntaktisk analyse blev udført.\n");
  }
  if (debug_mode) {
    fprintf(stderr, "Pæn udskrift efter leksikalsk og syntaktisk analyse:\n");
    prettyMAIN(theprogram);
  }
  if (verbose_mode) {
    fprintf(stderr, "Semantisk analyse udføres ...\n");
  }
  SymbolTable *mscope = initSymbolTable();
  int traversalerr = traversal(theprogram, mscope);
  if (traversalerr != 0) {
    fprintf(stderr, "Der opstod i alt %d fejl under den semantiske analyse.\n", traversalerr);
    return 1;
  }
  if (verbose_mode) {
    fprintf(stderr, "Semantisk analyse blev udført.\n");
  }
  if (debug_mode) {
    dumpsymbol(theprogram, mscope);
  }
  if (verbose_mode) {
    fprintf(stderr, "Kodegenerering udføres ...\n");
  }
  LINKED_LIST *l = generateCode(theprogram, mscope);
  l = registerAllocation(l);
  if (verbose_mode) {
    fprintf(stderr, "Kodegenerering blev udført.\n");
  }
  emission(l);
  return 0;
}
