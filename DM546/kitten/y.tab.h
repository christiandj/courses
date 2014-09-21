/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     tINTCONST = 258,
     tIDENTIFIER = 259,
     tCONTINUE = 260,
     tBREAK = 261,
     tEND = 262,
     tEQ = 263,
     tNEQ = 264,
     tGT = 265,
     tLT = 266,
     tGEQ = 267,
     tLEQ = 268,
     tAND = 269,
     tOR = 270,
     tFUNCTION = 271,
     tRETURN = 272,
     tWRITE = 273,
     tASSIGN = 274,
     tIF = 275,
     tTHEN = 276,
     tLOOP = 277,
     tNOT = 278,
     tTIMESEQ = 279,
     tDIVEQ = 280,
     tPLUSEQ = 281,
     tMINUSEQ = 282,
     UMINUS = 283
   };
#endif
/* Tokens.  */
#define tINTCONST 258
#define tIDENTIFIER 259
#define tCONTINUE 260
#define tBREAK 261
#define tEND 262
#define tEQ 263
#define tNEQ 264
#define tGT 265
#define tLT 266
#define tGEQ 267
#define tLEQ 268
#define tAND 269
#define tOR 270
#define tFUNCTION 271
#define tRETURN 272
#define tWRITE 273
#define tASSIGN 274
#define tIF 275
#define tTHEN 276
#define tLOOP 277
#define tNOT 278
#define tTIMESEQ 279
#define tDIVEQ 280
#define tPLUSEQ 281
#define tMINUSEQ 282
#define UMINUS 283




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 16 "kitten.y"

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



/* Line 2068 of yacc.c  */
#line 125 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


