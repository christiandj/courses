#include <stdio.h>
#include <stdbool.h>
#include "pretty.h"

int indentationLevel = 0;
bool isFirstLine = true;

void newline() {
  if (!isFirstLine) {
    fprintf(stderr, "\n");
  }
  isFirstLine = false;
  int i = indentationLevel * 4;
  while (i-- > 0) {
    fprintf(stderr, " ");
  }
}

void prettyFUNCTION(FUNCTION *function) {
  prettyHEAD(function->head);
  indentationLevel++;
  prettySTATEMENT(function->statement_list);
  indentationLevel--;
  prettyTAIL(function->tail);
}

void prettyHEAD(HEAD *head) {
  fprintf(stderr, "function %s(", head->idH);
  prettyPARDECLLIST(head->par_decl_list);
  fprintf(stderr, ")");
}

void prettyTAIL(TAIL *tail) {
  if (tail->i == 1) {
    newline();
    fprintf(stderr, "end");
  }
}

void prettyPARDECLLIST(PAR_DECL_LIST *par_decl_list) {
  if (par_decl_list != NULL) {
    if (par_decl_list->next != NULL) {
      prettyPARDECLLIST(par_decl_list->next);
      fprintf(stderr, ", ");
    }
    prettyPAR(par_decl_list->par);
  }
}

void prettyPAR(PAR *par) {
  fprintf(stderr, "%s", par->id);
}

void prettyMAIN(MAIN *main) {
  prettyDECLLIST(main->decl_list);
  prettySTATEMENT(main->statement_list);
  newline();
}

void prettyDECLLIST(DECL_LIST *decl_list) {
  if (decl_list != 0) {
    prettyDECLLIST(decl_list->decl_list);
    prettyDECLARATION(decl_list->declaration);
  }
}

void prettyDECLARATION(DECLARATION *declaration) {
  newline();
  prettyFUNCTION(declaration->function);
}

void prettySTATEMENT(STATEMENT *statement) {
  if (statement != NULL) {
    switch (statement->kind) {
      case returnK:
        if (statement->val.returnS.exp != NULL) {
          newline();
          fprintf(stderr, "return ");
          prettyEXP(statement->val.returnS.exp);
          fprintf(stderr, ";");
        }
        break;
      case writeK:
        if (statement->val.writeS.exp != NULL) {
          newline();
          fprintf(stderr, "write ");
          prettyEXP(statement->val.writeS.exp);
          fprintf(stderr, ";");
        }
        break;
      case assignK:
        newline();
        prettyVARIABLE(statement->val.assignS.variable);
        fprintf(stderr, " := ");
        prettyEXP(statement->val.assignS.exp);
        fprintf(stderr, ";");
        break;
      case ifK:
        newline();
        fprintf(stderr, "if ");
        prettyEXP(statement->val.ifS.exp);
        fprintf(stderr," then ");
        indentationLevel++;
        prettySTATEMENT(statement->val.ifS.statement);
        indentationLevel--;
        break;
      case loopK:
        newline();
        fprintf(stderr, "loop ");
        indentationLevel++;
        prettySTATEMENT(statement->val.loopS.statement);
        indentationLevel--;
        break;
      case continueK:
        if (statement->val.continueS.i == 1) {
          newline();
          fprintf(stderr, "continue;");
        }
        break;
      case breakK:
        if (statement->val.breakS.i == 1) {
          newline();
          fprintf(stderr, "break;");
        }
        break;
      case curly_bracketK:
        fprintf(stderr, "{");
        prettySTATEMENT(statement->val.curly_bracketS.statement);
        indentationLevel--;
        newline();
        fprintf(stderr, "}");
        indentationLevel++;
        break;
      case statement_listK:
        prettySTATEMENT(statement->val.statement_listS.statement);
        while (statement->kind == statement_listK) {
          if (statement->val.statement_listS.next != NULL) {
            prettySTATEMENT(statement->val.statement_listS.next);
          }
          statement = statement->val.statement_listS.next;
        }
        break;
    }
  }
}

void prettyVARIABLE(VARIABLE *variable) {
  fprintf(stderr, "%s", variable->idV);
}

void prettyEXP(EXP *e) {
  switch (e->kind) {
    case intconstK:
      fprintf(stderr, "%i", e->val.intconstE);
      break;
    case timesK:
      fprintf(stderr, "(");
      prettyEXP(e->val.timesE.left);
      fprintf(stderr, "*");
      prettyEXP(e->val.timesE.right);
      fprintf(stderr, ")");
      break;
    case divK:
      fprintf(stderr, "(");
      prettyEXP(e->val.divE.left);
      fprintf(stderr, "/");
      prettyEXP(e->val.divE.right);
      fprintf(stderr, ")");
      break;
    case plusK:
      fprintf(stderr, "(");
      prettyEXP(e->val.plusE.left);
      fprintf(stderr, "+");
      prettyEXP(e->val.plusE.right);
      fprintf(stderr, ")");
      break;
    case minusK:
      fprintf(stderr, "(");
      prettyEXP(e->val.minusE.left);
      fprintf(stderr, "-");
      prettyEXP(e->val.minusE.right);
      fprintf(stderr, ")");
      break;
    case eqK:
      fprintf(stderr, "(");
      prettyEXP(e->val.eqE.left);
      fprintf(stderr, "=");
      prettyEXP(e->val.eqE.right);
      fprintf(stderr, ")");
      break;
    case neqK:
      fprintf(stderr, "(");
      prettyEXP(e->val.neqE.left);
      fprintf(stderr, "!=");
      prettyEXP(e->val.neqE.right);
      fprintf(stderr, ")");
      break;
    case gtK:
      fprintf(stderr, "(");
      prettyEXP(e->val.gtE.left);
      fprintf(stderr, ">");
      prettyEXP(e->val.gtE.right);
      fprintf(stderr, ")");
      break;
    case ltK:
      fprintf(stderr, "(");
      prettyEXP(e->val.ltE.left);
      fprintf(stderr, "<");
      prettyEXP(e->val.ltE.right);
      fprintf(stderr, ")");
      break;
    case geqK:
      fprintf(stderr, "(");
      prettyEXP(e->val.geqE.left);
      fprintf(stderr, ">=");
      prettyEXP(e->val.geqE.right);
      fprintf(stderr, ")");
      break;
    case leqK:
      fprintf(stderr, "(");
      prettyEXP(e->val.leqE.left);
      fprintf(stderr, "<=");
      prettyEXP(e->val.leqE.right);
      fprintf(stderr, ")");
      break;
    case andK:
      fprintf(stderr, "(");
      prettyEXP(e->val.andE.left);
      fprintf(stderr, "and");
      prettyEXP(e->val.andE.right);
      fprintf(stderr, ")");
      break;
    case orK:
      fprintf(stderr, "(");
      prettyEXP(e->val.orE.left);
      fprintf(stderr, "or");
      prettyEXP(e->val.orE.right);
      fprintf(stderr, ")");
      break;
    case notK:
      fprintf(stderr, "(not");
      prettyEXP(e->val.notE.note);
      fprintf(stderr, ")");
      break;
    case func_callK:
      fprintf(stderr, "%s(", e->val.func_callE.id);
      if (e->val.func_callE.act_list != NULL) {
        EXP_LIST *explist = e->val.func_callE.act_list;
        prettyEXPLIST(explist);
      }
      fprintf(stderr, ")");
      break;
    case varK:
      prettyVARIABLE(e->val.var);
      break;
  }
}

void prettyEXPLIST(EXP_LIST *exp_list) {
  if (exp_list != NULL) {
    if (exp_list->next != NULL) {
      prettyEXPLIST(exp_list->next);
      fprintf(stderr, ", ");
    }
    prettyEXP(exp_list->exp);
  }
}
