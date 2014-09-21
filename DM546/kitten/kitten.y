%{
#include <stdio.h>
#include "tree.h"

extern char *yytext;
extern MAIN *theprogram;
extern int lineno;

int yylex();

void yyerror() {
  fprintf(stderr, "Syntaksfejl før '%s' i linje %d.\n", yytext, lineno);
}
%}

%union {
  int intconst;
  char *stringconst;
  struct FUNCTION *function;
  struct HEAD *head;
  struct TAIL *tail;
  struct PAR_DECL_LIST *pardecllist;
  struct PAR *par;
  struct MAIN *main;
  struct DECL_LIST *decllist;
  struct DECLARATION *declaration;
  struct STATEMENT *statement;
  struct VARIABLE *variable;
  struct EXP *expression;
  struct EXP_LIST *explist;
}

%token <intconst> tINTCONST
%token <stringconst> tIDENTIFIER tCONTINUE tBREAK tEND
%token tEQ tNEQ tGT tLT tGEQ tLEQ tAND tOR tFUNCTION tRETURN tWRITE
%token tASSIGN tIF tTHEN tLOOP tNOT tTIMESEQ tDIVEQ tPLUSEQ tMINUSEQ

%type <function> function
%type <head> head
%type <tail> tail
%type <pardecllist> par_decl_list
%type <par> par
%type <main> program main
%type <decllist> decl_list
%type <declaration> declaration
%type <statement> statement_list statement
%type <variable> variable
%type <expression> expression term
%type <explist> act_list exp_list

%start program

%right tASSIGN tTIMESEQ tDIVEQ tPLUSEQ tMINUSEQ
%left tOR
%left tAND
%left tEQ tNEQ
%left tGT tLT tGEQ tLEQ
%left '+' '-'
%left '*' '/'
%right tNOT UMINUS

%%
program         : main
                   { theprogram = $1; }
;

function        : head statement_list tail
                   { $$ = makeFUNCTION($1, $2, $3); }
;

head            : tFUNCTION tIDENTIFIER '(' par_decl_list ')'
                   { $$ = makeHEAD($2, $4); }
;

tail            : tEND
                   { $$ = makeTAIL(); }
;

par_decl_list   : par_decl_list ',' par
                   { $$ = makePARDECLLIST($3, $1); }
                | par /* not in the grammar from the project description */
                   { $$ = makePARDECLLIST($1, NULL); }
                | /* epsilon */
                   { $$ = NULL; }
;

par             : tIDENTIFIER
                   { $$ = makePAR($1); }
;

main            : decl_list statement_list
                   { $$ = makeMAIN($1, $2); }
;

decl_list       : decl_list declaration
                   { $$ = makeDECLLIST($1, $2); }
                | /* epsilon */
                   { $$ = NULL; }
;

declaration     : function
                   { $$ = makeDECLARATION($1); }
;

statement_list  : statement
                   { $$ = $1; }
                | statement_list statement
                   { $$ = makeSTATEMENTstmtlist($1, $2); }
;

statement       : tRETURN expression ';'
                   { $$ = makeSTATEMENTreturn($2); }
                | tWRITE expression ';'
                   { $$ =  makeSTATEMENTwrite($2); }
                | variable tASSIGN expression ';'
                   { $$ = makeSTATEMENTassign($1, $3); }
                | tIF expression tTHEN statement
                   { $$ = makeSTATEMENTif($2, $4); }
                | tLOOP statement
                   { $$ = makeSTATEMENTloop($2); }
                | tCONTINUE ';'
                   { $$ = makeSTATEMENTcontinue(); }
                | tBREAK ';'
                   { $$ = makeSTATEMENTbreak(); }
                | '{' statement_list '}'
                   { $$ = makeSTATEMENTcurly($2); }
                | variable tTIMESEQ expression ';' /* syntactic sugar */
                   { $$ = makeSTATEMENTtimeseq($1, $3); }
                | variable tDIVEQ expression ';'   /* syntactic sugar */
                   { $$ = makeSTATEMENTdiveq($1, $3); }
                | variable tPLUSEQ expression ';'  /* syntactic sugar */
                   { $$ = makeSTATEMENTpluseq($1, $3); }
                | variable tMINUSEQ expression ';' /* syntactic sugar */
                   { $$ = makeSTATEMENTminuseq($1, $3); }
;

variable        : tIDENTIFIER
                   { $$ = makeVARIABLE($1); }
;

expression      : expression '*' expression
                   { $$ = makeEXPtimes($1, $3); }
                | expression '/' expression
                   { $$ = makeEXPdiv($1, $3); }
                | expression '+' expression
                   { $$ = makeEXPplus($1, $3); }
                | expression '-' expression
                   { $$ = makeEXPminus($1, $3); }
                | expression tEQ expression
                   { $$ = makeEXPeq($1, $3); }
                | expression tNEQ expression
                   { $$ = makeEXPneq($1, $3); }
                | expression tGT expression
                   { $$ = makeEXPgt($1, $3); }
                | expression tLT expression
                   { $$ = makeEXPlt($1, $3); }
                | expression tGEQ expression
                   { $$ = makeEXPgeq($1, $3); }
                | expression tLEQ expression
                   { $$ = makeEXPleq($1, $3); }
                | expression tAND expression
                   { $$ = makeEXPand($1, $3); }
                | expression tOR expression
                   { $$ = makeEXPor($1, $3); }
                | '-' expression %prec UMINUS /* syntactic sugar */
                   { $$ = makeEXPuminus($2); }
                | term
                   { $$ = $1; }
;

term            : variable
                   { $$ = makeEXPvar($1); }
                | tIDENTIFIER '(' act_list ')'
                   { $$ = makeEXPfunccall($1, $3); }
                | '(' expression ')'
                   { $$ = $2; }
                | tNOT term
                   { $$ = makeEXPnot($2); }
                | tINTCONST
                   { $$ = makeEXPintconst($1); }
;

act_list        : exp_list
                   { $$ = $1; }
                | /* epsilon */
                   { $$ = NULL; }
;

exp_list        : expression
                   { $$ = makeEXPLIST($1, NULL); }
                | exp_list ',' expression
                   { $$ = makeEXPLIST($3, $1); }
;
%%
