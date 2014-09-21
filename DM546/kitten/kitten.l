%{
#include "y.tab.h"
#include <string.h>
 
extern int lineno;
extern int fileno();
%}

%x comment mcomment

%option noyywrap nounput noinput

%%
<INITIAL>{
[ \t]+                  /* ignore */;
\n                      lineno++;
"#"                     { BEGIN(comment); }
"(*"                    { BEGIN(mcomment); }

"*"                     return '*';
"/"                     return '/';
"+"                     return '+';
"-"                     return '-';
"("                     return '(';
")"                     return ')';
"="                     return tEQ;
"!="                    return tNEQ;
">"                     return tGT;
"<"                     return tLT;
">="                    return tGEQ;
"<="                    return tLEQ;
"and"                   return tAND;
"or"                    return tOR;

"*="                    return tTIMESEQ;
"/="                    return tDIVEQ;
"+="                    return tPLUSEQ;
"-="                    return tMINUSEQ;

"function"              return tFUNCTION;
"end"                   return tEND;
"return"                return tRETURN;
"write"                 return tWRITE;
":="                    return tASSIGN;
"if"                    return tIF;
"then"                  return tTHEN;
"loop"                  return tLOOP;
"continue"              return tCONTINUE;
"break"                 return tBREAK;

"{"                     return '{';
"}"                     return '}';

"not"                   return tNOT;

","                     return ',';
";"                     return ';';

0|([1-9][0-9]*)         { yylval.intconst = atoi(yytext);
                          return tINTCONST; }
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.stringconst = (char *)malloc(strlen(yytext) + 1);
                          sprintf(yylval.stringconst, "%s", yytext); 
                          return tIDENTIFIER; }
.                       { fprintf(stderr, "Ugyldigt leksikalsk element '%s' i linje %d.\n", yytext, lineno); exit(1); };
}

<comment>\n             { lineno++; BEGIN(INITIAL); }
<comment>.              /* ignore */;

<mcomment>[^*\n]*       /* ignore */;
<mcomment>"*"+[^*)\n]*  /* ignore */;
<mcomment>\n            lineno++;
<mcomment>"*"+")"       BEGIN(INITIAL);
%%
