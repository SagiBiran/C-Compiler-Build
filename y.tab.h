/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
     COMMENT = 258,
     WHILE = 259,
     IF = 260,
     ELSE = 261,
     RETURN = 262,
     BOOL_TYPE = 263,
     STR_TYPE = 264,
     CHAR_PTR = 265,
     CHAR_TYPE = 266,
     INT_TYPE = 267,
     INT_PTR = 268,
     VOID = 269,
     AND = 270,
     ADDR = 271,
     EQ = 272,
     ASSIGN = 273,
     OR = 274,
     LENGTH = 275,
     GE = 276,
     G = 277,
     LE = 278,
     L = 279,
     NOTEQ = 280,
     NOT = 281,
     DIV = 282,
     PLUS = 283,
     MINUS = 284,
     MUL = 285,
     VAR = 286,
     STRING = 287,
     REAL = 288,
     CHAR = 289,
     NONE = 290,
     MAIN = 291,
     ID = 292,
     SEMICOLON = 293,
     COMMA = 294,
     L_SOGER = 295,
     R_SOGER = 296,
     L_BRACKET = 297,
     R_BRACKET = 298,
     L_BLOCK = 299,
     R_BLOCK = 300,
     INT_DEC = 301,
     INT_HEX = 302,
     BOOL_TRUE = 303,
     BOOL_FALSE = 304,
     REAL_TYPE = 305,
     REAL_PTR = 306
   };
#endif
/* Tokens.  */
#define COMMENT 258
#define WHILE 259
#define IF 260
#define ELSE 261
#define RETURN 262
#define BOOL_TYPE 263
#define STR_TYPE 264
#define CHAR_PTR 265
#define CHAR_TYPE 266
#define INT_TYPE 267
#define INT_PTR 268
#define VOID 269
#define AND 270
#define ADDR 271
#define EQ 272
#define ASSIGN 273
#define OR 274
#define LENGTH 275
#define GE 276
#define G 277
#define LE 278
#define L 279
#define NOTEQ 280
#define NOT 281
#define DIV 282
#define PLUS 283
#define MINUS 284
#define MUL 285
#define VAR 286
#define STRING 287
#define REAL 288
#define CHAR 289
#define NONE 290
#define MAIN 291
#define ID 292
#define SEMICOLON 293
#define COMMA 294
#define L_SOGER 295
#define R_SOGER 296
#define L_BRACKET 297
#define R_BRACKET 298
#define L_BLOCK 299
#define R_BLOCK 300
#define INT_DEC 301
#define INT_HEX 302
#define BOOL_TRUE 303
#define BOOL_FALSE 304
#define REAL_TYPE 305
#define REAL_PTR 306




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 100 "part3.y"
{
    struct node *node;
    char *string;
}
/* Line 1529 of yacc.c.  */
#line 156 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

