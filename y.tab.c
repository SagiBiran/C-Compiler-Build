/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 5 "part3.y"

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lex.yy.c"

typedef enum {false,true} bool;

typedef struct node
{
	struct node *right;
	struct node *left;
	char *token;
	char *var;
	char *label;
	char *SCOPE;
	char *trueLab;
	char *falseLab;
	int cnt;
} node;

typedef struct Func 
{
	char * name;
	struct Args* args;
	char *retType; 
	int argNum;
	int getRet;
} Func;

typedef struct Args
{
	char* name;
	char* length;
	char* type;
}Args;

typedef struct Variables
{	
	char*name;
	char*value;
	char*type;
	char* length;
	int isArg;
}Variable;

typedef struct SCOPE
{	
	char *name;
	Func ** func;
	Variable * var;
	int varCount;
	int funcCount;
	struct SCOPE * nextScope;
	struct SCOPE * preScope;
}SCOPE;

int yylex();
int yyerror(char *e);

int mainFlag = false;
void addFunction(char*, Args* , node*, int, SCOPE*);
static int scope = 0;
SCOPE* makeScope(char *);
SCOPE* findScope(SCOPE * scopes);
SCOPE* globalScope = NULL;
void addVariables(Args*, int, int,SCOPE*);
char *findVariables(node * tree,SCOPE * MYscope);
void syntaxAnalyzer(node *tree,SCOPE * scope);
void putScopes(SCOPE*, char*);
char * getExpressionType(node *,SCOPE*);
char* findFunctionInScope(node * tree,SCOPE * MYscope,int* count);
node* makeNode(char*, node*, node*);
Args * makeArguments(node *,int *);
Args * functionCallOnArguments(SCOPE *,node *tree,int*);

static int line = 0;
static int t = 0;
static int lab = 0;
static node* startNode;
int popParameters(Args * args,int count);
void M3AC(node*);
void addSecondScope(node*, char* ,char*, char*, char*,char*);
char* freshVariables();
void addFirstScope(node*, char*, char*, char*,char*, char*);
char* firstStrCat(char*des,char*src);
char* generator(char*,char*,char*,char*,char*);
char* freshLabel();
char* secondStrCat(char*des,char*src);
char * addSpaces(char*);
char *replaceString(const char*, const char*, const char*);



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 100 "part3.y"
{
    struct node *node;
    char *string;
}
/* Line 193 of yacc.c.  */
#line 298 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 311 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   504

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  95
/* YYNRULES -- Number of states.  */
#define YYNSTATES  199

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   306

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     9,    12,    13,    22,    25,    26,
      36,    45,    47,    48,    51,    56,    61,    64,    65,    72,
      81,    85,    87,    89,    91,    93,    95,    97,    99,   101,
     104,   105,   107,   109,   111,   113,   121,   127,   135,   142,
     146,   150,   155,   157,   161,   166,   168,   170,   172,   174,
     176,   178,   180,   182,   184,   186,   190,   194,   198,   202,
     206,   210,   214,   218,   222,   226,   230,   234,   238,   241,
     243,   245,   248,   250,   252,   254,   256,   258,   260,   262,
     266,   271,   273,   275,   278,   283,   289,   297,   300,   305,
     311,   314,   318,   320,   321,   325
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      53,     0,    -1,    55,    54,    -1,    57,    56,    -1,     3,
      55,    -1,    -1,    14,    36,    40,    41,    55,    44,    61,
      45,    -1,    57,    58,    -1,    -1,    72,    37,    40,    59,
      41,    55,    44,    61,    45,    -1,    14,    37,    40,    59,
      41,    44,    61,    45,    -1,    60,    -1,    -1,    65,    64,
      -1,    60,    38,    55,    60,    -1,    55,    57,    62,    66,
      -1,    62,    63,    -1,    -1,    31,    65,    64,    55,    38,
      55,    -1,     9,    64,    42,    46,    43,    55,    38,    55,
      -1,    37,    39,    64,    -1,    37,    -1,     8,    -1,    11,
      -1,    12,    -1,    50,    -1,    13,    -1,    10,    -1,    51,
      -1,    66,    69,    -1,    -1,    69,    -1,    63,    -1,    58,
      -1,    38,    -1,    44,    57,    55,    62,    66,    45,    55,
      -1,     5,    40,    73,    41,    67,    -1,     5,    40,    73,
      41,    67,     6,    67,    -1,     4,    55,    40,    73,    41,
      67,    -1,    70,    38,    55,    -1,    73,    38,    55,    -1,
       7,    73,    38,    55,    -1,    68,    -1,    71,    18,    73,
      -1,    37,    42,    73,    43,    -1,    37,    -1,    74,    -1,
      75,    -1,     8,    -1,    11,    -1,    12,    -1,    50,    -1,
      13,    -1,    10,    -1,    51,    -1,    40,    73,    41,    -1,
      73,    17,    73,    -1,    73,    25,    73,    -1,    73,    21,
      73,    -1,    73,    22,    73,    -1,    73,    23,    73,    -1,
      73,    24,    73,    -1,    73,    15,    73,    -1,    73,    19,
      73,    -1,    73,    28,    73,    -1,    73,    29,    73,    -1,
      73,    30,    73,    -1,    73,    27,    73,    -1,    26,    73,
      -1,    74,    -1,    75,    -1,    79,    55,    -1,    46,    -1,
      47,    -1,    34,    -1,    33,    -1,    32,    -1,    49,    -1,
      48,    -1,    20,    37,    20,    -1,    37,    42,    73,    43,
      -1,    37,    -1,    35,    -1,    16,    37,    -1,    16,    40,
      37,    41,    -1,    16,    37,    42,    73,    43,    -1,    16,
      40,    37,    42,    73,    43,    41,    -1,    30,    37,    -1,
      30,    40,    76,    41,    -1,    30,    37,    42,    76,    43,
      -1,    37,    46,    -1,    73,    39,    77,    -1,    73,    -1,
      -1,    40,    77,    41,    -1,    37,    78,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   135,   135,   137,   138,   138,   140,   142,   143,   145,
     146,   148,   149,   151,   152,   154,   156,   156,   158,   159,
     161,   162,   164,   165,   166,   167,   168,   169,   170,   173,
     173,   175,   175,   175,   175,   177,   179,   181,   182,   183,
     184,   185,   186,   189,   191,   192,   193,   194,   197,   198,
     199,   200,   201,   202,   203,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   234,   235,   236,   237,   239,   240,   241,
     243,   245,   246,   247,   249,   251
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "COMMENT", "WHILE", "IF", "ELSE",
  "RETURN", "BOOL_TYPE", "STR_TYPE", "CHAR_PTR", "CHAR_TYPE", "INT_TYPE",
  "INT_PTR", "VOID", "AND", "ADDR", "EQ", "ASSIGN", "OR", "LENGTH", "GE",
  "G", "LE", "L", "NOTEQ", "NOT", "DIV", "PLUS", "MINUS", "MUL", "VAR",
  "STRING", "REAL", "CHAR", "NONE", "MAIN", "ID", "SEMICOLON", "COMMA",
  "L_SOGER", "R_SOGER", "L_BRACKET", "R_BRACKET", "L_BLOCK", "R_BLOCK",
  "INT_DEC", "INT_HEX", "BOOL_TRUE", "BOOL_FALSE", "REAL_TYPE", "REAL_PTR",
  "$accept", "project", "program", "comment", "main", "functions",
  "function", "parameters_upward", "parameters_list", "body", "declares",
  "declare", "variables", "regular_type", "statements", "block_statement",
  "new_block", "statement", "assignment_statement", "lhs", "function_type",
  "expression", "address_expression", "dereference_expression",
  "dereference_support", "expression_list", "parent_expression",
  "function_call", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    52,    53,    54,    55,    55,    56,    57,    57,    58,
      58,    59,    59,    60,    60,    61,    62,    62,    63,    63,
      64,    64,    65,    65,    65,    65,    65,    65,    65,    66,
      66,    67,    67,    67,    67,    68,    69,    69,    69,    69,
      69,    69,    69,    70,    71,    71,    71,    71,    72,    72,
      72,    72,    72,    72,    72,    73,    73,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      73,    73,    73,    74,    74,    74,    74,    75,    75,    75,
      76,    77,    77,    77,    78,    79
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     2,     0,     8,     2,     0,     9,
       8,     1,     0,     2,     4,     4,     2,     0,     6,     8,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       0,     1,     1,     1,     1,     7,     5,     7,     6,     3,
       3,     4,     1,     3,     4,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     3,
       4,     1,     1,     2,     4,     5,     7,     2,     4,     5,
       2,     3,     1,     0,     3,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       5,     5,     0,     8,     4,     1,     2,     0,    48,    53,
      49,    50,    52,     0,    51,    54,     3,     7,     0,     0,
       0,     0,     0,    12,    12,     5,    22,    27,    23,    24,
      26,    25,    28,     0,    11,     0,     0,     0,     0,     5,
      21,    13,     5,     5,     5,     0,     0,     0,     8,     0,
       0,    14,    20,     5,    17,     6,    10,     0,     0,    30,
       9,     0,     0,    16,    15,     0,     0,     5,     0,     0,
       0,     0,     0,     0,    76,    75,    74,    82,    81,     0,
       8,    72,    73,    78,    77,    42,    29,     0,     0,     0,
      69,    70,     5,     0,     5,     0,     0,    81,     0,    69,
      70,    83,     0,     0,    68,    87,     0,    93,     0,    95,
       0,     5,     5,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     5,    71,     0,     0,
       0,     0,     0,     5,     0,     0,    79,     0,     0,     0,
      92,     0,     0,    55,    17,    39,    43,    62,    56,    63,
      58,    59,    60,    61,    57,    67,    64,    65,    66,    40,
       5,     5,     0,     0,     0,    41,     0,    84,     0,     0,
      90,    88,    93,    94,    80,    30,     0,    18,     0,    34,
      33,    32,    36,    31,    80,    85,     0,    89,    91,     0,
       5,    38,     0,     0,     5,    19,    37,    86,    35
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     6,    48,    16,     7,    17,    33,    34,    49,
      59,   181,    41,    35,    64,   182,    85,   183,    87,    88,
      18,    89,    99,   100,   139,   141,   109,    92
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -170
static const yytype_int16 yypact[] =
{
      74,    74,    91,  -170,  -170,  -170,  -170,    33,  -170,  -170,
    -170,  -170,  -170,    50,  -170,  -170,  -170,  -170,    56,    55,
      57,    58,    59,   191,   191,    74,  -170,  -170,  -170,  -170,
    -170,  -170,  -170,    62,    61,    67,    64,    52,    63,    74,
      69,  -170,    74,    74,    74,   191,    67,    66,  -170,    70,
      75,  -170,  -170,    74,    68,  -170,  -170,    77,    86,     3,
    -170,    67,   191,  -170,   214,    72,    67,    74,    84,   239,
     -22,    88,   239,   -21,  -170,  -170,  -170,  -170,    -7,   239,
    -170,  -170,  -170,  -170,  -170,  -170,  -170,    94,   116,   424,
     117,   120,    74,    60,    74,   107,   239,    32,   442,  -170,
    -170,   108,   112,   131,  -170,   111,   118,   239,   239,  -170,
     342,    18,    74,   239,   239,   239,   239,   239,   239,   239,
     239,   239,   239,   239,   239,   239,    74,  -170,   113,   119,
     239,   363,   239,    74,   239,    47,  -170,   118,   122,   130,
     405,   133,   274,  -170,  -170,  -170,   460,   474,  -170,   474,
      23,    23,    23,    23,    23,   137,    -3,    -3,   137,  -170,
      74,    74,   384,   132,   291,  -170,   308,  -170,   239,   134,
    -170,  -170,   239,  -170,   141,     3,   135,  -170,   132,  -170,
    -170,  -170,   169,  -170,  -170,  -170,   325,  -170,  -170,   180,
      74,  -170,   132,   145,    74,  -170,  -170,  -170,  -170
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -170,  -170,  -170,     0,  -170,   -42,  -156,   164,   144,   -36,
      48,   -54,    24,   129,    20,  -169,  -170,   -60,  -170,  -170,
    -170,   -59,   -62,   -61,    71,    21,  -170,  -170
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -48
static const yytype_int16 yytable[] =
{
       3,     4,    90,    91,    86,    63,    54,   180,    50,   191,
      98,   -45,    61,   104,   115,   101,   105,    57,   102,   106,
     110,     1,   180,   196,   122,    37,     8,   125,     9,    10,
      11,    12,    58,   107,    62,   108,   180,   131,   111,    45,
     115,     8,    47,     9,    10,    11,    12,    13,   140,   142,
     122,   123,   124,   125,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,    95,    14,    15,
      52,   162,   107,   164,   132,   166,     8,     1,     9,    10,
      11,    12,    58,    14,    15,    65,    19,    20,   167,   168,
      94,     5,   127,    21,   129,    22,    43,    23,    24,    39,
      25,    90,    91,    38,    40,    42,   128,    44,    46,   186,
      53,   144,   145,   140,    93,    55,    90,    91,    14,    15,
      56,    63,    60,    20,    96,   103,   159,    90,    91,    86,
      90,    91,   112,   165,   113,   -46,    67,    68,   -47,    69,
       8,    61,     9,    10,    11,    12,    58,   130,    70,   135,
     134,   136,    71,   137,   115,   138,   160,   161,    72,   -44,
     176,   177,    73,    62,    74,    75,    76,    77,   170,    78,
     179,   171,    79,   190,   173,   192,    80,   187,    81,    82,
      83,    84,    14,    15,    67,    68,   197,    69,    36,    51,
     195,    66,   175,   188,   198,   189,    70,     0,     0,    26,
      71,    27,    28,    29,    30,     0,    72,     0,   169,     0,
      73,     0,    74,    75,    76,    77,     0,    78,    67,    68,
      79,    69,     0,     0,    80,   194,    81,    82,    83,    84,
      70,     0,     0,     0,    71,     0,     0,     0,     0,     0,
      72,    31,    32,     0,    73,     0,    74,    75,    76,    77,
       0,    78,     0,     0,    79,    70,     0,     0,    80,    71,
      81,    82,    83,    84,     0,    72,     0,     0,     0,    73,
       0,    74,    75,    76,    77,     0,    97,     0,     0,    79,
       0,     0,     0,     0,     0,    81,    82,    83,    84,   114,
       0,   115,     0,   116,     0,   117,   118,   119,   120,   121,
       0,   122,   123,   124,   125,     0,   114,     0,   115,     0,
     116,     0,   117,   118,   119,   120,   121,   174,   122,   123,
     124,   125,     0,   114,     0,   115,     0,   116,     0,   117,
     118,   119,   120,   121,   184,   122,   123,   124,   125,     0,
     114,     0,   115,     0,   116,     0,   117,   118,   119,   120,
     121,   185,   122,   123,   124,   125,     0,   114,     0,   115,
       0,   116,     0,   117,   118,   119,   120,   121,   193,   122,
     123,   124,   125,     0,     0,     0,     0,     0,   114,     0,
     115,     0,   116,   143,   117,   118,   119,   120,   121,     0,
     122,   123,   124,   125,     0,     0,     0,     0,     0,   114,
       0,   115,     0,   116,   163,   117,   118,   119,   120,   121,
       0,   122,   123,   124,   125,     0,     0,     0,     0,     0,
     114,     0,   115,     0,   116,   178,   117,   118,   119,   120,
     121,     0,   122,   123,   124,   125,     0,     0,     0,   114,
       0,   115,     0,   116,   172,   117,   118,   119,   120,   121,
       0,   122,   123,   124,   125,     0,     0,   114,     0,   115,
       0,   116,   126,   117,   118,   119,   120,   121,     0,   122,
     123,   124,   125,     0,     0,   114,     0,   115,     0,   116,
     133,   117,   118,   119,   120,   121,     0,   122,   123,   124,
     125,   115,     0,     0,     0,   117,   118,   119,   120,   121,
       0,   122,   123,   124,   125
};

static const yytype_int16 yycheck[] =
{
       0,     1,    64,    64,    64,    59,    48,   163,    44,   178,
      69,    18,     9,    72,    17,    37,    37,    53,    40,    40,
      79,     3,   178,   192,    27,    25,     8,    30,    10,    11,
      12,    13,    14,    40,    31,    42,   192,    96,    80,    39,
      17,     8,    42,    10,    11,    12,    13,    14,   107,   108,
      27,    28,    29,    30,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,    67,    50,    51,
      46,   130,    40,   132,    42,   134,     8,     3,    10,    11,
      12,    13,    14,    50,    51,    61,    36,    37,    41,    42,
      66,     0,    92,    37,    94,    40,    44,    40,    40,    38,
      41,   163,   163,    41,    37,    41,    46,    44,    39,   168,
      44,   111,   112,   172,    42,    45,   178,   178,    50,    51,
      45,   175,    45,    37,    40,    37,   126,   189,   189,   189,
     192,   192,    38,   133,    18,    18,     4,     5,    18,     7,
       8,     9,    10,    11,    12,    13,    14,    40,    16,    37,
      42,    20,    20,    42,    17,    37,    43,    38,    26,    18,
     160,   161,    30,    31,    32,    33,    34,    35,    46,    37,
      38,    41,    40,    38,    41,     6,    44,    43,    46,    47,
      48,    49,    50,    51,     4,     5,    41,     7,    24,    45,
     190,    62,   144,   172,   194,   175,    16,    -1,    -1,     8,
      20,    10,    11,    12,    13,    -1,    26,    -1,   137,    -1,
      30,    -1,    32,    33,    34,    35,    -1,    37,     4,     5,
      40,     7,    -1,    -1,    44,    45,    46,    47,    48,    49,
      16,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,
      26,    50,    51,    -1,    30,    -1,    32,    33,    34,    35,
      -1,    37,    -1,    -1,    40,    16,    -1,    -1,    44,    20,
      46,    47,    48,    49,    -1,    26,    -1,    -1,    -1,    30,
      -1,    32,    33,    34,    35,    -1,    37,    -1,    -1,    40,
      -1,    -1,    -1,    -1,    -1,    46,    47,    48,    49,    15,
      -1,    17,    -1,    19,    -1,    21,    22,    23,    24,    25,
      -1,    27,    28,    29,    30,    -1,    15,    -1,    17,    -1,
      19,    -1,    21,    22,    23,    24,    25,    43,    27,    28,
      29,    30,    -1,    15,    -1,    17,    -1,    19,    -1,    21,
      22,    23,    24,    25,    43,    27,    28,    29,    30,    -1,
      15,    -1,    17,    -1,    19,    -1,    21,    22,    23,    24,
      25,    43,    27,    28,    29,    30,    -1,    15,    -1,    17,
      -1,    19,    -1,    21,    22,    23,    24,    25,    43,    27,
      28,    29,    30,    -1,    -1,    -1,    -1,    -1,    15,    -1,
      17,    -1,    19,    41,    21,    22,    23,    24,    25,    -1,
      27,    28,    29,    30,    -1,    -1,    -1,    -1,    -1,    15,
      -1,    17,    -1,    19,    41,    21,    22,    23,    24,    25,
      -1,    27,    28,    29,    30,    -1,    -1,    -1,    -1,    -1,
      15,    -1,    17,    -1,    19,    41,    21,    22,    23,    24,
      25,    -1,    27,    28,    29,    30,    -1,    -1,    -1,    15,
      -1,    17,    -1,    19,    39,    21,    22,    23,    24,    25,
      -1,    27,    28,    29,    30,    -1,    -1,    15,    -1,    17,
      -1,    19,    38,    21,    22,    23,    24,    25,    -1,    27,
      28,    29,    30,    -1,    -1,    15,    -1,    17,    -1,    19,
      38,    21,    22,    23,    24,    25,    -1,    27,    28,    29,
      30,    17,    -1,    -1,    -1,    21,    22,    23,    24,    25,
      -1,    27,    28,    29,    30
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    53,    55,    55,     0,    54,    57,     8,    10,
      11,    12,    13,    14,    50,    51,    56,    58,    72,    36,
      37,    37,    40,    40,    40,    41,     8,    10,    11,    12,
      13,    50,    51,    59,    60,    65,    59,    55,    41,    38,
      37,    64,    41,    44,    44,    55,    39,    55,    55,    61,
      61,    60,    64,    44,    57,    45,    45,    61,    14,    62,
      45,     9,    31,    63,    66,    64,    65,     4,     5,     7,
      16,    20,    26,    30,    32,    33,    34,    35,    37,    40,
      44,    46,    47,    48,    49,    68,    69,    70,    71,    73,
      74,    75,    79,    42,    64,    55,    40,    37,    73,    74,
      75,    37,    40,    37,    73,    37,    40,    40,    42,    78,
      73,    57,    38,    18,    15,    17,    19,    21,    22,    23,
      24,    25,    27,    28,    29,    30,    38,    55,    46,    55,
      40,    73,    42,    38,    42,    37,    20,    42,    37,    76,
      73,    77,    73,    41,    55,    55,    73,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    55,
      43,    38,    73,    41,    73,    55,    73,    41,    42,    76,
      46,    41,    39,    41,    43,    62,    55,    55,    41,    38,
      58,    63,    67,    69,    43,    43,    73,    43,    77,    66,
      38,    67,     6,    43,    45,    55,    67,    41,    55
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 135 "part3.y"
    { startNode = (yyvsp[(2) - (2)].node); syntaxAnalyzer((yyvsp[(2) - (2)].node),globalScope); M3AC((yyvsp[(2) - (2)].node)); }
    break;

  case 3:
#line 137 "part3.y"
    { (yyval.node) = makeNode("CODE",(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); }
    break;

  case 4:
#line 138 "part3.y"
    { ; }
    break;

  case 6:
#line 140 "part3.y"
    { (yyval.node) = makeNode("Main",makeNode("ARGS",NULL,(yyvsp[(7) - (8)].node)),NULL); t = 0; }
    break;

  case 7:
#line 142 "part3.y"
    { (yyval.node) = makeNode("functions",(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); }
    break;

  case 8:
#line 143 "part3.y"
    { (yyval.node) = NULL; }
    break;

  case 9:
#line 145 "part3.y"
    { (yyval.node) = makeNode("FUNC",makeNode((yyvsp[(2) - (9)].string),makeNode("",NULL,NULL),makeNode("ARGS",(yyvsp[(4) - (9)].node),makeNode("Return",(yyvsp[(1) - (9)].node),NULL))),makeNode("",(yyvsp[(8) - (9)].node),NULL)); t = 0; }
    break;

  case 10:
#line 146 "part3.y"
    { (yyval.node) = makeNode("FUNCTION",makeNode((yyvsp[(2) - (8)].string),makeNode("",NULL,NULL),NULL),makeNode("ARGS",(yyvsp[(4) - (8)].node),(yyvsp[(7) - (8)].node))); t = 0; }
    break;

  case 11:
#line 148 "part3.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 12:
#line 149 "part3.y"
    { (yyval.node) = NULL; }
    break;

  case 13:
#line 151 "part3.y"
    { (yyval.node) = makeNode("(",(yyvsp[(1) - (2)].node),makeNode("",(yyvsp[(2) - (2)].node),makeNode(")",NULL,NULL))); }
    break;

  case 14:
#line 152 "part3.y"
    { (yyval.node) = makeNode("",(yyvsp[(1) - (4)].node),makeNode("",(yyvsp[(4) - (4)].node),NULL)); }
    break;

  case 15:
#line 154 "part3.y"
    { (yyval.node) = makeNode("BODY", makeNode(" ",(yyvsp[(2) - (4)].node),NULL),makeNode(" ",(yyvsp[(3) - (4)].node),makeNode(" ",(yyvsp[(4) - (4)].node),makeNode(" ",NULL,NULL)))); }
    break;

  case 16:
#line 156 "part3.y"
    { (yyval.node) = makeNode("",(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node));}
    break;

  case 17:
#line 156 "part3.y"
    { (yyval.node) = NULL; }
    break;

  case 18:
#line 158 "part3.y"
    { (yyval.node) = makeNode("var", (yyvsp[(2) - (6)].node),(yyvsp[(3) - (6)].node)); }
    break;

  case 19:
#line 159 "part3.y"
    { (yyval.node) = makeNode("var",makeNode("string", makeNode("[",makeNode("$3",NULL,NULL),NULL), NULL) ,(yyvsp[(2) - (8)].node)); }
    break;

  case 20:
#line 161 "part3.y"
    { (yyval.node) = makeNode((yyvsp[(1) - (3)].string), makeNode(" ", (yyvsp[(3) - (3)].node), NULL),NULL); }
    break;

  case 21:
#line 162 "part3.y"
    { (yyval.node) = makeNode((yyvsp[(1) - (1)].string), NULL, NULL); }
    break;

  case 22:
#line 164 "part3.y"
    { (yyval.node) = makeNode("boolean", NULL, NULL); }
    break;

  case 23:
#line 165 "part3.y"
    { (yyval.node) = makeNode("char", NULL, NULL); }
    break;

  case 24:
#line 166 "part3.y"
    { (yyval.node) = makeNode("int", NULL, NULL); }
    break;

  case 25:
#line 167 "part3.y"
    { (yyval.node) = makeNode("real", NULL, NULL); }
    break;

  case 26:
#line 168 "part3.y"
    { (yyval.node) = makeNode("int*", NULL, NULL); }
    break;

  case 27:
#line 169 "part3.y"
    { (yyval.node) = makeNode("char*", NULL, NULL); }
    break;

  case 28:
#line 170 "part3.y"
    { (yyval.node) = makeNode("real*", NULL, NULL); }
    break;

  case 29:
#line 173 "part3.y"
    { (yyval.node) = makeNode("statements",(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); if(strcmp((yyvsp[(2) - (2)].node)->token, "if") == 0 || strcmp((yyvsp[(2) - (2)].node)->token, "if-else") == 0 || strcmp((yyvsp[(2) - (2)].node)->token, "while") == 0){ if((yyval.node)->cnt == 0) { addFirstScope((yyvsp[(2) - (2)].node),NULL,NULL,freshLabel(),NULL,NULL); (yyval.node)->cnt = 1; } } }
    break;

  case 30:
#line 173 "part3.y"
    { (yyval.node) = NULL; }
    break;

  case 31:
#line 175 "part3.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); if(strcmp((yyvsp[(1) - (1)].node)->token, "if") == 0 || strcmp((yyvsp[(1) - (1)].node)->token, "if-else") == 0 || strcmp((yyvsp[(1) - (1)].node)->token, "while") == 0) addFirstScope((yyvsp[(1) - (1)].node),NULL,NULL,freshLabel(),NULL,NULL); }
    break;

  case 32:
#line 175 "part3.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 33:
#line 175 "part3.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 34:
#line 175 "part3.y"
    { (yyval.node) = makeNode("",NULL,NULL); }
    break;

  case 35:
#line 177 "part3.y"
    { (yyval.node) = makeNode("{",(yyvsp[(2) - (7)].node),makeNode("",(yyvsp[(4) - (7)].node),makeNode("", (yyvsp[(5) - (7)].node),("}",NULL,NULL)))); }
    break;

  case 36:
#line 179 "part3.y"
    { (yyval.node) = makeNode("if",makeNode("(", (yyvsp[(3) - (5)].node),makeNode(")",NULL,NULL)),(yyvsp[(5) - (5)].node)); addFirstScope((yyvsp[(3) - (5)].node),NULL,NULL,NULL,freshLabel(),NULL); 
}
    break;

  case 37:
#line 181 "part3.y"
    { (yyval.node) = makeNode("if-else",makeNode("", (yyvsp[(3) - (7)].node),makeNode("",NULL,NULL)),makeNode("",(yyvsp[(5) - (7)].node),makeNode("",(yyvsp[(7) - (7)].node),NULL))); addFirstScope((yyvsp[(3) - (7)].node),NULL,NULL,NULL,freshLabel(),NULL); addFirstScope((yyvsp[(3) - (7)].node),NULL,NULL,NULL,NULL,freshLabel()); }
    break;

  case 38:
#line 182 "part3.y"
    { (yyval.node) = makeNode("while",makeNode("(", (yyvsp[(4) - (6)].node),makeNode(")",NULL,NULL)),(yyvsp[(6) - (6)].node)); addFirstScope((yyval.node),NULL,NULL,NULL,freshLabel(),NULL); addFirstScope((yyval.node),NULL,NULL,NULL,NULL,freshLabel()); }
    break;

  case 39:
#line 183 "part3.y"
    { (yyval.node) = makeNode("assignment_statement",(yyvsp[(1) - (3)].node),NULL); }
    break;

  case 40:
#line 184 "part3.y"
    { (yyval.node) = (yyvsp[(1) - (3)].node); }
    break;

  case 41:
#line 185 "part3.y"
    { (yyval.node) = makeNode("return",(yyvsp[(2) - (4)].node),NULL); }
    break;

  case 42:
#line 186 "part3.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 43:
#line 189 "part3.y"
    { (yyval.node) = makeNode("=",(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); }
    break;

  case 44:
#line 191 "part3.y"
    { (yyval.node) = makeNode((yyvsp[(1) - (4)].string), makeNode("[",(yyvsp[(3) - (4)].node),makeNode("]",NULL,NULL)), NULL); }
    break;

  case 45:
#line 192 "part3.y"
    { (yyval.node) = makeNode((yyvsp[(1) - (1)].string),NULL,NULL); }
    break;

  case 46:
#line 193 "part3.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 47:
#line 194 "part3.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 48:
#line 197 "part3.y"
    { (yyval.node) = makeNode("boolean", NULL, NULL); }
    break;

  case 49:
#line 198 "part3.y"
    { (yyval.node) = makeNode("char", NULL, NULL); }
    break;

  case 50:
#line 199 "part3.y"
    { (yyval.node) = makeNode("int", NULL, NULL); }
    break;

  case 51:
#line 200 "part3.y"
    { (yyval.node) = makeNode("real", NULL, NULL); }
    break;

  case 52:
#line 201 "part3.y"
    { (yyval.node) = makeNode("int*", NULL, NULL); }
    break;

  case 53:
#line 202 "part3.y"
    { (yyval.node) = makeNode("char*", NULL, NULL); }
    break;

  case 54:
#line 203 "part3.y"
    { (yyval.node) = makeNode("real*", NULL, NULL); }
    break;

  case 55:
#line 205 "part3.y"
    { (yyval.node) = makeNode("(",(yyvsp[(2) - (3)].node),makeNode(")",NULL,NULL)); }
    break;

  case 56:
#line 206 "part3.y"
    { (yyval.node) = makeNode("==",(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); }
    break;

  case 57:
#line 207 "part3.y"
    { (yyval.node) = makeNode("!=",(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); }
    break;

  case 58:
#line 208 "part3.y"
    { (yyval.node) = makeNode(">=",(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); }
    break;

  case 59:
#line 209 "part3.y"
    { (yyval.node) = makeNode(">",(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); }
    break;

  case 60:
#line 210 "part3.y"
    { (yyval.node) = makeNode("<=",(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); }
    break;

  case 61:
#line 211 "part3.y"
    { (yyval.node) = makeNode("<",(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); }
    break;

  case 62:
#line 212 "part3.y"
    { (yyval.node) = makeNode("&&",(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); addFirstScope((yyvsp[(1) - (3)].node),NULL,NULL,NULL,freshLabel(),NULL); }
    break;

  case 63:
#line 213 "part3.y"
    { (yyval.node) = makeNode("||",(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); addFirstScope((yyvsp[(1) - (3)].node),NULL,NULL,NULL,NULL,freshLabel()); }
    break;

  case 64:
#line 214 "part3.y"
    { (yyval.node) = makeNode("+",(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); }
    break;

  case 65:
#line 215 "part3.y"
    { (yyval.node) = makeNode("-",(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); }
    break;

  case 66:
#line 216 "part3.y"
    { (yyval.node) = makeNode("*",(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); }
    break;

  case 67:
#line 217 "part3.y"
    { (yyval.node) = makeNode("/",(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); }
    break;

  case 68:
#line 218 "part3.y"
    { (yyval.node) = makeNode("!",(yyvsp[(2) - (2)].node),NULL); }
    break;

  case 69:
#line 219 "part3.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 70:
#line 220 "part3.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 71:
#line 221 "part3.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); }
    break;

  case 72:
#line 222 "part3.y"
    { (yyval.node) = makeNode((yyvsp[(1) - (1)].string),makeNode("INT",NULL,NULL),NULL); }
    break;

  case 73:
#line 223 "part3.y"
    { (yyval.node) = makeNode((yyvsp[(1) - (1)].string),makeNode("HEX", NULL, NULL),NULL); }
    break;

  case 74:
#line 224 "part3.y"
    { (yyval.node) = makeNode((yyvsp[(1) - (1)].string),makeNode("CHAR", NULL, NULL),NULL); }
    break;

  case 75:
#line 225 "part3.y"
    { (yyval.node) = makeNode((yyvsp[(1) - (1)].string),makeNode("REAL", NULL, NULL),NULL); }
    break;

  case 76:
#line 226 "part3.y"
    { (yyval.node) = makeNode((yyvsp[(1) - (1)].string),makeNode("STRING", NULL, NULL),NULL); }
    break;

  case 77:
#line 227 "part3.y"
    { (yyval.node) = makeNode((yyvsp[(1) - (1)].string),makeNode("BOOLEAN", NULL, NULL),NULL); }
    break;

  case 78:
#line 228 "part3.y"
    { (yyval.node) = makeNode((yyvsp[(1) - (1)].string),makeNode("BOOLEAN", NULL, NULL),NULL); }
    break;

  case 79:
#line 229 "part3.y"
    { (yyval.node) = makeNode("|",makeNode((yyvsp[(2) - (3)].string),NULL,NULL),makeNode("|",NULL,NULL)); }
    break;

  case 80:
#line 230 "part3.y"
    { (yyval.node) = makeNode("solver",makeNode((yyvsp[(1) - (4)].string),makeNode("[",(yyvsp[(3) - (4)].node),makeNode("]",NULL,NULL)),NULL),NULL); }
    break;

  case 81:
#line 231 "part3.y"
    { (yyval.node) = makeNode("solver",makeNode((yyvsp[(1) - (1)].string),NULL,NULL),NULL); }
    break;

  case 82:
#line 232 "part3.y"
    { (yyval.node) = makeNode("null",NULL,NULL); }
    break;

  case 83:
#line 234 "part3.y"
    { (yyval.node) = makeNode("&",makeNode((yyvsp[(2) - (2)].string),NULL,NULL),NULL); }
    break;

  case 84:
#line 235 "part3.y"
    { (yyval.node) = makeNode("&",makeNode("(",makeNode((yyvsp[(3) - (4)].string),NULL,NULL),NULL),makeNode(")",NULL,NULL)); }
    break;

  case 85:
#line 236 "part3.y"
    { (yyval.node) = makeNode("&", makeNode((yyvsp[(2) - (5)].string),makeNode("[",(yyvsp[(4) - (5)].node),makeNode("]",NULL,NULL)),NULL),NULL); }
    break;

  case 86:
#line 237 "part3.y"
    { (yyval.node) = makeNode("&",makeNode("(",	makeNode((yyvsp[(3) - (7)].string),makeNode("[",(yyvsp[(5) - (7)].node),makeNode("]",NULL,NULL)),NULL),makeNode(")",NULL,NULL)),NULL); }
    break;

  case 87:
#line 239 "part3.y"
    { (yyval.node) = makeNode("^",makeNode((yyvsp[(2) - (2)].string),NULL,NULL),NULL); addFirstScope((yyval.node),"",firstStrCat("*",(yyvsp[(2) - (2)].string)),NULL,NULL,NULL); }
    break;

  case 88:
#line 240 "part3.y"
    { (yyval.node) = makeNode("^",makeNode("(",(yyvsp[(3) - (4)].node),NULL),makeNode(")",NULL,NULL)); addFirstScope((yyval.node),(yyvsp[(3) - (4)].node)->SCOPE,firstStrCat("*",(yyvsp[(3) - (4)].node)->var),NULL,NULL,NULL); }
    break;

  case 89:
#line 241 "part3.y"
    { (yyval.node) = makeNode((yyvsp[(1) - (5)].string), makeNode((yyvsp[(2) - (5)].string),makeNode("[",(yyvsp[(4) - (5)].node),makeNode("]",NULL,NULL)),NULL), NULL); }
    break;

  case 90:
#line 243 "part3.y"
    { (yyval.node) = makeNode("solver",makeNode((yyvsp[(1) - (2)].string),NULL,NULL),makeNode((yyvsp[(2) - (2)].string),NULL,NULL)); }
    break;

  case 91:
#line 245 "part3.y"
    { (yyval.node) = makeNode("expression_list",(yyvsp[(1) - (3)].node),makeNode(",",(yyvsp[(3) - (3)].node),NULL)); }
    break;

  case 92:
#line 246 "part3.y"
    { (yyval.node) = makeNode("expression_list",(yyvsp[(1) - (1)].node),NULL); }
    break;

  case 93:
#line 247 "part3.y"
    { (yyval.node) = NULL; }
    break;

  case 94:
#line 249 "part3.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); }
    break;

  case 95:
#line 251 "part3.y"
    { (yyval.node) = makeNode("Call func",makeNode((yyvsp[(1) - (2)].string),NULL,NULL),makeNode("ARGS",(yyvsp[(2) - (2)].node),NULL)); }
    break;


/* Line 1267 of yacc.c.  */
#line 2207 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 253 "part3.y"

int main() {
    int ans = yyparse();
    FILE *f = fopen("output.txt", "w+");
    if (ans == 0) {
        printf(" The Syntax and Semantics Are Valid\n\n");
    }
    fprintf(f, "%s", startNode->SCOPE);
    printf("%s", startNode->SCOPE);

    return ans;

}

int yyerror(char *e) {
    int yydebug = 1;
    fflush(stdout);
    fprintf(stderr, "Error %s at line %d\n", e, yylineno);
    fprintf(stderr, "does not accept '%s'\n", yytext);

    return 0;
}

Args *functionCallOnArguments(SCOPE *MYscope, node *tree, int *count) {
    Args *arr1 = NULL, arr2[50];
    char *type, *length;
    while (tree != NULL) {
        arr2[(*count)++].type = getExpressionType(tree->left, MYscope);
        if (tree->right != NULL)
            tree = tree->right->left;
        else
            tree = NULL;

    }
    arr1 = (Args *) malloc(sizeof(Args) * (*count));
    for (int i = 0; i < *count; i++)
        arr1[i].type = arr2[i].type;
    return arr1;
}

char *findFunctionInScope(node *tree, SCOPE *MYscope, int *countParams) {
    SCOPE *tmp = MYscope;
    Args *args;
    int find = false, flag = true;
    while (tmp != NULL) {
        for (int i = 0; i < tmp->funcCount; i++)
            if (strcmp(tree->left->token, tmp->func[i]->name) == 0) {
                find = true;
                flag = true;
                int count = 0;
                args = functionCallOnArguments(MYscope, tree->right->left, &count);
                if (count == tmp->func[i]->argNum) {
                    for (int j = 0, t = count - 1; j < count; j++, t--) {
                        if (strcmp(args[j].type, tmp->func[i]->args[t].type) != 0)
                            flag = false;
                    }
                    if (flag == true) {
                        if (countParams != NULL)
                            *countParams = popParameters(args, count);
                        return tmp->func[i]->retType;
                    }
                }
            }
        tmp = tmp->preScope;
    }
    printf("ERROR, function [%s] cannot find call in scope [%s's] function\n", tree->left->token,
           globalScope->func[globalScope->funcCount - 1]->name);
    if (find == true)
        printf("There is a function with the same name that accepts different arguments\n");
    exit(1);
}

char *findVariables(node *tree, SCOPE *MYscope) {
    SCOPE *tmp = MYscope;
    if (strcmp(tree->token, "solver") == 0)
        tree = tree->left;
    while (tmp != NULL) {
        for (int i = 0; i < tmp->varCount; i++)
            if (strcmp(tree->token, tmp->var[i].name) == 0) {

                if (tree->left != NULL && strcmp(tree->left->token, "[") == 0) {
                    if (strcmp(tmp->var[i].type, "string") == 0)
                        if (strcmp(getExpressionType(tree->left->left, MYscope), "int") == 0) {
                            return "char";
                        } else {
                            printf("ERROR, index in string can be only int (<string>[<int>])in scope %s in function %s\n",
                                   MYscope->name, globalScope->func[globalScope->funcCount - 1]->name);
                            exit(1);
                        }
                    else {
                        printf("ERROR, you can use index only on string type (<string>[<int>]) in scope %s in function %s\n",
                               MYscope->name, globalScope->func[globalScope->funcCount - 1]->name);
                        exit(1);
                    }

                } else
                    return tmp->var[i].type;

            }
        tmp = tmp->preScope;
    }
    printf("ERROR, var %s cannot find in scope %s in function %s\n ", tree->token, MYscope->name,
           globalScope->func[globalScope->funcCount - 1]->name);
    exit(1);

}

char *getExpressionType(node *tree, SCOPE *MYscope) {
    char *message = (char *) malloc(sizeof(char) * 7);
    message = "";
    if (strcmp(tree->token, "null") == 0)
        message = "NULL";
    else if (tree->left != NULL) {
        if (strcmp(tree->left->token, "INT") == 0)
            message = "int";
        if (strcmp(tree->left->token, "HEX") == 0)
            message = "hex";
        if (strcmp(tree->left->token, "CHAR") == 0)
            message = "char";
        if (strcmp(tree->left->token, "REAL") == 0)
            message = "real";
        if (strcmp(tree->left->token, "STRING") == 0)
            message = "string";
        if (strcmp(tree->left->token, "BOOLEAN") == 0)
            message = "boolean";
        if (strcmp(tree->token, "!") == 0)
            if (strcmp(getExpressionType(tree->left, MYscope), "boolean") == 0)
                message = "boolean";
            else {
                printf("ERROR, operator ! is only define on boolean type");
                exit(1);
            }
        if (strcmp(tree->token, "|") == 0)
            if (strcmp(getExpressionType(tree->left, MYscope), "string") == 0)
                message = "int";
            else {
                printf("ERROR, operator | is only define on string type in a function %s",
                       globalScope->func[globalScope->funcCount - 1]->name);
                exit(1);
            }
        if (strcmp(tree->token, "==") == 0 || strcmp(tree->token, "!=") == 0) {
            if (strcmp(getExpressionType(tree->left, MYscope), getExpressionType(tree->right, MYscope)) == 0 &&
                strcmp(getExpressionType(tree->right, MYscope), "string") != 0)
                message = "boolean";
            else {
                printf("ERROR, %s is undefined between %s and %s in a function %s\n", tree->token,
                       getExpressionType(tree->left, MYscope), getExpressionType(tree->right, MYscope),
                       globalScope->func[globalScope->funcCount - 1]->name);
                exit(1);
            }
        }

        if (strcmp(tree->token, ">=") == 0 || strcmp(tree->token, ">") == 0 || strcmp(tree->token, "<=") == 0 ||
            strcmp(tree->token, "<") == 0) {
            if ((strcmp(getExpressionType(tree->left, MYscope), "int") == 0 ||
                 strcmp(getExpressionType(tree->left, MYscope), "real") == 0) &&
                (strcmp(getExpressionType(tree->right, MYscope), "int") == 0 ||
                 strcmp(getExpressionType(tree->right, MYscope), "real") == 0))
                message = "boolean";
            else {
                printf("ERROR, %s is undefined between %s and %s in a function %s\n", tree->token,
                       getExpressionType(tree->left, MYscope), getExpressionType(tree->right, MYscope),
                       globalScope->func[globalScope->funcCount - 1]->name);
                exit(1);
            }
        }

        if (strcmp(tree->token, "&&") == 0 || strcmp(tree->token, "||") == 0) {

            if (strcmp(getExpressionType(tree->left, MYscope), getExpressionType(tree->right, MYscope)) == 0 &&
                strcmp(getExpressionType(tree->right, MYscope), "boolean") == 0)
                message = "boolean";
            else {
                printf("ERROR, %s is undefined between %s and %s in a function %s\n", tree->token,
                       getExpressionType(tree->left, MYscope), getExpressionType(tree->right, MYscope),
                       globalScope->func[globalScope->funcCount - 1]->name);
                exit(1);
            }


        }
        if (strcmp(tree->token, "-") == 0 || strcmp(tree->token, "+") == 0) {
            if ((strcmp(getExpressionType(tree->left, MYscope), "int") == 0 ||
                 strcmp(getExpressionType(tree->left, MYscope), "real") == 0) &&
                (strcmp(getExpressionType(tree->right, MYscope), "int") == 0 ||
                 strcmp(getExpressionType(tree->right, MYscope), "real") == 0)) {
                if (strcmp(getExpressionType(tree->left, MYscope), getExpressionType(tree->right, MYscope)) == 0 &&
                    strcmp(getExpressionType(tree->left, MYscope), "int") == 0)
                    message = "int";
                else
                    message = "real";
            }

            if (strcmp(getExpressionType(tree->right, MYscope), "int") == 0 &&
                (strcmp(getExpressionType(tree->left, MYscope), "char*") == 0 ||
                 strcmp(getExpressionType(tree->right, MYscope), "int*") == 0 ||
                 strcmp(getExpressionType(tree->right, MYscope), "real*") == 0)) {
                message = getExpressionType(tree->left, MYscope);
            } else if (strcmp(message, "") == 0) {
                printf("ERROR, %s is undefined between %s and %s in a function %s\n", tree->token,
                       getExpressionType(tree->left, MYscope), getExpressionType(tree->right, MYscope),
                       globalScope->func[globalScope->funcCount - 1]->name);
                exit(1);
            }

        }
        if (strcmp(tree->token, "*") == 0 || strcmp(tree->token, "/") == 0) {
            if ((strcmp(getExpressionType(tree->left, MYscope), "int") == 0 ||
                 strcmp(getExpressionType(tree->left, MYscope), "real") == 0) &&
                (strcmp(getExpressionType(tree->right, MYscope), "int") == 0 ||
                 strcmp(getExpressionType(tree->right, MYscope), "real") == 0)) {
                if (strcmp(getExpressionType(tree->left, MYscope), getExpressionType(tree->right, MYscope)) == 0 &&
                    strcmp(getExpressionType(tree->left, MYscope), "int") == 0)
                    message = "int";
                else
                    message = "real";
            } else {
                printf("ERROR, %s is undefined between %s and %s in a function %s\n", tree->token,
                       getExpressionType(tree->left, MYscope), getExpressionType(tree->right, MYscope));
                exit(1);
            }
        }
        if (strcmp(tree->token, "&") == 0) {
            if (strcmp(tree->left->token, "(") == 0)
                message = getExpressionType(tree->left->left, MYscope);
            else {
                message = getExpressionType(tree->left, MYscope);

            }
            if (strcmp(message, "char") == 0)
                message = "char*";
            else if (strcmp(message, "int") == 0)
                message = "int*";
            else if (strcmp(message, "real") == 0)
                message = "real*";
            else {
                printf("ERROR, %s is undefined on %s \n", tree->token, message);
                exit(1);
            }
        }
        if (strcmp(tree->token, "^") == 0) {
            if (strcmp(tree->left->token, "(") == 0)
                message = getExpressionType(tree->left->left, MYscope);
            else
                message = getExpressionType(tree->left, MYscope);

            if (strcmp(message, "char*") == 0)
                message = "char";
            else if (strcmp(message, "int*") == 0)
                message = "int";
            else if (strcmp(message, "real*") == 0)
                message = "real";
            else {
                printf("ERROR, %s is undefined on %s \n", tree->token, message);
                exit(1);
            }

        }
        if (strcmp(tree->token, "(") == 0)
            message = getExpressionType(tree->left, MYscope);
        if (strcmp(tree->token, "Call func") == 0)
            message = findFunctionInScope(tree, MYscope, NULL);

    }
    if (strcmp(message, "") == 0)
        message = findVariables(tree, MYscope);


    return message;
}

SCOPE *makeScope(char *name) {
    SCOPE *newScope = (SCOPE *) malloc(sizeof(SCOPE));
    newScope->name = name;
    newScope->var = NULL;
    newScope->varCount = 0;
    newScope->func = NULL;
    newScope->funcCount = 0;
    newScope->nextScope = NULL;
    newScope->preScope = NULL;
    return newScope;
}

void putScopes(SCOPE *from, char *name) {
    SCOPE *point;
    if (globalScope == NULL)
        globalScope = makeScope(name);
    else {
        point = globalScope;
        while (point->nextScope != NULL)
            point = point->nextScope;
        point->nextScope = makeScope(name);
        point->nextScope->preScope = from;
    }
}

void addVariables(Args *args, int variablesCounter, int isArg, SCOPE *MYscope) {
    if (variablesCounter == 0)
        return;
    Variable *tmp;
    SCOPE *scopes = MYscope;

    for (int i = 0; i < variablesCounter; i++)
        for (int j = 0; j < variablesCounter; j++)
            if (i != j && strcmp(args[j].name, args[i].name) == 0) {
                printf("There is already same variable %s in other declare", args[i].name);
                SCOPE *t = scopes->preScope;
                while (t->preScope != NULL && t->preScope->funcCount == 0)
                    t = t->preScope;
                if (t->func != NULL)
                    printf(",in function %s\n", t->func[t->funcCount - 1]->name);
                else
                    printf("\n");
                exit(1);
            }
    if (scopes->var == NULL) {
        scopes->var = (Variable *) malloc(sizeof(Variable) * variablesCounter);
    } else {
        tmp = scopes->var;
        scopes->var = (Variable *) malloc(sizeof(Variable) * (scopes->varCount + variablesCounter));
        for (int i = 0; i < scopes->varCount; i++) {
            for (int j = 0; j < variablesCounter; j++) {
                if (strcmp(tmp[i].name, args[j].name) == 0) {
                    printf("There can't be same variable %s in same scope", tmp[i].name);
                    SCOPE *t = scopes->preScope;
                    while (t->preScope != NULL && t->preScope->funcCount == 0)
                        t = t->preScope;
                    if (t->func != NULL)
                        printf(",in function %s\n", t->func[t->funcCount - 1]->name);
                    else
                        printf("\n");
                    exit(1);
                }
            }
            scopes->var[i] = tmp[i];
        }
    }
    for (int j = 0; j < variablesCounter; j++) {

        scopes->var[scopes->varCount].name = args[j].name;
        scopes->var[scopes->varCount].value = NULL;
        scopes->var[scopes->varCount].isArg = isArg;
        scopes->var[scopes->varCount].length = args[j].length;
        scopes->var[(scopes->varCount)++].type = args[j].type;
    }
}

void addFunction(char *name, Args *args, node *retType, int argNum, SCOPE *MYscope) {
    Func **tmp;
    SCOPE *scopes = MYscope;
    for (int i = 0; i < argNum; i++)
        for (int j = 0; j < argNum; j++)
            if (i != j && strcmp(args[j].name, args[i].name) == 0) {
                printf("ERROR, there are identical arguments %s in function %s\n", args[i].name, name);
                exit(1);
            }
    if (scopes->func == NULL) {
        scopes->func = (Func **) malloc(sizeof(Func * ));
    } else {
        tmp = scopes->func;
        scopes->func = (Func **) malloc(sizeof(Func * ) * (scopes->funcCount + 1));
        for (int i = 0; i < scopes->funcCount; i++) {
            if (strcmp(tmp[i]->name, name) == 0) {
                printf("ERROR, there's already function %s in same scope \n", tmp[i]->name);
                exit(1);
            }
            scopes->func[i] = tmp[i];
        }
    }
    scopes->func[scopes->funcCount] = (Func *) malloc(sizeof(Func));
    scopes->func[scopes->funcCount]->name = name;
    scopes->func[scopes->funcCount]->args = args;
    if (retType == NULL)
        scopes->func[scopes->funcCount]->retType = NULL;
    else {
        if (strcmp(retType->token, "string") == 0) {
            printf("ERROR, return type function %s can't be string\n", name);
            exit(1);
        }
        scopes->func[scopes->funcCount]->retType = retType->token;
    }
    scopes->func[scopes->funcCount]->argNum = argNum;
    scopes->func[scopes->funcCount]->getRet = false;
    ++(scopes->funcCount);
}

Args *makeArguments(node *tree, int *count) {
    Args *arr1 = NULL, arr2[50];
    char *type, *length;
    if (tree != NULL) {
        node *temp1 = tree, *tmp = tree;
        do {
            if (strcmp(temp1->token, "") == 0) {
                tmp = temp1->right->left;
                temp1 = temp1->left;

                if (strcmp(tmp->token, "(") == 0 || strcmp(tmp->token, "var") == 0) {
                    type = tmp->left->token;
                    if (tmp->left->left != NULL)
                        length = tmp->left->left->left->token;
                    node *tmptree;
                    tmptree = tmp->right->left;
                    do {
                        arr2[*count].name = tmptree->token;
                        arr2[*count].type = type;
                        arr2[*count].length = length;
                        (*count)++;
                        if (tmptree->left == NULL)
                            tmptree = NULL;
                        else
                            tmptree = tmptree->left->left;
                    } while (tmptree != NULL);
                }
            }
        } while (strcmp(temp1->token, "(") != 0 && strcmp(tmp->token, "var") != 0);
        tmp = temp1;
        if (strcmp(tmp->token, "(") == 0 || strcmp(tmp->token, "var") == 0) {
            type = tmp->left->token;
            node *tmptree;
            if (strcmp(tmp->token, "var") == 0)
                tmptree = tmp->right;
            else
                tmptree = tmp->right->left;
            if (tmp->left->left != NULL)
                length = tmp->left->left->left->token;
            do {
                arr2[*count].name = tmptree->token;
                arr2[*count].type = type;
                arr2[*count].length = length;
                (*count)++;
                if (tmptree->left == NULL)
                    tmptree = NULL;
                else
                    tmptree = tmptree->left->left;
            } while (tmptree != NULL);
        }
        arr1 = (Args *) malloc(sizeof(Args) * (*count));
        for (int i = 0; i < *count; i++) {
            for (int j = 0; j < *count; j++) {
            }
            arr1[i].name = arr2[i].name;
            arr1[i].type = arr2[i].type;
        }
    }
    return arr1;
}

node *makeNode(char *token, node *left, node *right) {
    node *newnode = (node *) malloc(sizeof(node));
    newnode->left = left;
    newnode->right = right;
    newnode->token = token;
    newnode->SCOPE = NULL;
    newnode->var = NULL;
    newnode->label = NULL;
    newnode->trueLab = NULL;
    newnode->falseLab = NULL;
    newnode->cnt = 0;
    return newnode;
}

SCOPE *findScope(SCOPE *scopes) {
    SCOPE *MYscope = scopes;
    if (MYscope != NULL)
        while (MYscope->nextScope != NULL)
            MYscope = MYscope->nextScope;
    return MYscope;
}

void syntaxAnalyzer(node *tree, SCOPE *MYscope) {

    if (strcmp(tree->token, "=") == 0) {
        if (!(strcmp(getExpressionType(tree->right, MYscope), "NULL") == 0 &&
              (strcmp(getExpressionType(tree->left, MYscope), "real*") == 0 ||
               strcmp(getExpressionType(tree->left, MYscope), "int*") == 0 ||
               strcmp(getExpressionType(tree->left, MYscope), "char*") == 0)))
            if (strcmp(getExpressionType(tree->left, MYscope), getExpressionType(tree->right, MYscope)) != 0) {
                printf("ERROR, applying = between %s and %s in scope %s is undefined in function %s\n",
                       getExpressionType(tree->left, MYscope), getExpressionType(tree->right, MYscope), MYscope->name,
                       globalScope->func[globalScope->funcCount - 1]->name);
                exit(1);
            }

    } else if (strcmp(tree->token, "var") == 0) {
        int varCount = 0;
        Args *var = makeArguments(tree, &varCount);
        addVariables(var, varCount, 0, MYscope);


    } else if (strcmp(tree->token, "if") == 0) {
        if (strcmp(getExpressionType(tree->left->left, MYscope), "boolean") != 0) {
            printf("ERROR, if condition type should be boolean\n");
            exit(1);
        }


        if (strcmp(tree->right->token, "{") != 0) {
            putScopes(MYscope, tree->token);
            if (tree->left)
                syntaxAnalyzer(tree->left, findScope(MYscope->nextScope));

            if (tree->right)
                syntaxAnalyzer(tree->right, findScope(MYscope->nextScope));
            scope--;
            return;
        }

    } else if (strcmp(tree->token, "while") == 0) {
        if (strcmp(getExpressionType(tree->left->left, MYscope), "boolean") != 0) {
            printf("ERROR, while condition type should be boolean\n");
            exit(1);
        }

        if (strcmp(tree->right->token, "{") != 0) {
            putScopes(MYscope, tree->token);
            if (tree->left)
                syntaxAnalyzer(tree->left, findScope(MYscope->nextScope));

            if (tree->right)
                syntaxAnalyzer(tree->right, findScope(MYscope->nextScope));
            scope--;
            return;
        }

    } else if (strcmp(tree->token, "FUNC") == 0) {
        int count = 0;
        Args *arg = makeArguments(tree->left->right->left, &count);
        addFunction(tree->left->token, arg, tree->left->right->right->left, count, MYscope);
        putScopes(MYscope, tree->token);
        addVariables(arg, count, 1, findScope(MYscope));
        if (tree->left)
            syntaxAnalyzer(tree->left, findScope(MYscope->nextScope));

        if (tree->right)
            syntaxAnalyzer(tree->right, findScope(MYscope->nextScope));
        if (MYscope->func[MYscope->funcCount - 1]->getRet == false) {
            printf("ERROR, there is no return statement in function %s\n", tree->left->token);
            exit(1);
        }
        scope--;
        return;
    } else if (strcmp(tree->token, "FUNCTION") == 0) {

        int count = 0;
        Args *arg = makeArguments(tree->right->left, &count);
        addFunction(tree->left->token, arg, NULL, count, MYscope);
        putScopes(MYscope, tree->token);
        addVariables(arg, count, 1, findScope(MYscope));
        if (tree->left)
            syntaxAnalyzer(tree->left, findScope(MYscope->nextScope));

        if (tree->right)
            syntaxAnalyzer(tree->right, findScope(MYscope->nextScope));
        scope--;
        return;
    } else if (strcmp(tree->token, "Call func") == 0) {
        int count = 0;
        findFunctionInScope(tree, MYscope, &count);
        tree->cnt = count;
    } else if (strcmp(tree->token, "CODE") == 0) {
        putScopes(NULL, tree->token);
        if (tree->left)
            syntaxAnalyzer(tree->left, globalScope);

        if (tree->right)
            syntaxAnalyzer(tree->right, globalScope);
        scope--;
        return;
    } else if (strcmp(tree->token, "BODY") == 0) {

    } else if (strcmp(tree->token, "ARGS") == 0) {
    } else if (strcmp(tree->token, "Main") == 0) {
        if (mainFlag == true && strcmp(MYscope->name, "CODE") == 0) {
            printf("ERROR, only one main function is allowed and implemented solely\n");
            exit(1);
        }
        mainFlag = true;
        addFunction(tree->token, NULL, NULL, 0, MYscope);
        putScopes(MYscope, tree->token);

        if (tree->left)
            syntaxAnalyzer(tree->left, findScope(MYscope->nextScope));

        if (tree->right)
            syntaxAnalyzer(tree->right, findScope(MYscope->nextScope));
        scope--;
        return;

    } else if (strcmp(tree->token, "if-else") == 0) {
        if (strcmp(getExpressionType(tree->left->left, MYscope), "boolean") != 0) {
            printf("ERROR, if condition type should be boolean\n");
            exit(1);
        }

        if (strcmp(tree->right->left->token, "{") != 0) {
            putScopes(MYscope, tree->token);
            syntaxAnalyzer(tree->right->left, findScope(MYscope->nextScope));
            scope--;
            putScopes(MYscope, tree->token);
            syntaxAnalyzer(tree->right->right->left, findScope(MYscope->nextScope));
            scope--;
            return;
        }


    } else if (strcmp(tree->token, "return") == 0) {
        SCOPE *tmp = MYscope;
        int flag = true;
        while (strcmp(tmp->name, "FUNC") != 0 && strcmp(tmp->name, "FUNCTION") != 0 && strcmp(tmp->name, "CODE") != 0) {
            tmp = tmp->preScope;
            flag = false;
        }
        if (flag == false) {
            if (strcmp(getExpressionType(tree->left, MYscope), tmp->preScope->func[tmp->preScope->funcCount - 1]->retType)) {
                printf("ERROR, the return type doesn't match the type of function %s \n",
                       tmp->preScope->func[tmp->preScope->funcCount - 1]->name);
                printf("%s ,%s %s\n", getExpressionType(tree->left, MYscope),
                       tmp->preScope->func[tmp->preScope->funcCount - 1]->retType,
                       tmp->preScope->func[tmp->preScope->funcCount - 1]->name);
                exit(1);
            }
        } else {
            if (tmp->preScope->func[tmp->preScope->funcCount - 1]->retType != NULL) {
                if (0 == strcmp(getExpressionType(tree->left, MYscope),
                                tmp->preScope->func[tmp->preScope->funcCount - 1]->retType)) {
                    tmp->preScope->func[tmp->preScope->funcCount - 1]->getRet = true;
                } else {
                    printf("ERROR, the return type doesn't match the type of function %s \n",
                           tmp->preScope->func[tmp->preScope->funcCount - 1]->name);
                    printf("%s ,%s %s\n", getExpressionType(tree->left, MYscope),
                           tmp->preScope->func[tmp->preScope->funcCount - 1]->retType,
                           tmp->preScope->func[tmp->preScope->funcCount - 1]->name);
                    exit(1);
                }
            }
                //TODO: Remove
            else {
                printf("ERROR, there can't be return in FUNCTION %s\n",
                       tmp->preScope->func[tmp->preScope->funcCount - 1]->name);
                exit(1);
            }
        }

    } else if (strcmp(tree->token, "{") == 0) {
        putScopes(MYscope, tree->token);
        if (tree->left)
            syntaxAnalyzer(tree->left, findScope(MYscope->nextScope));

        if (tree->right)
            syntaxAnalyzer(tree->right, findScope(MYscope->nextScope));
        scope--;
        return;
    } else if (strcmp(tree->token, "}") == 0) {

    } else if (strcmp(tree->token, "") == 0);
    else if (strcmp(tree->token, "(") == 0);
    else if (strcmp(tree->token, ")") == 0);
    else if (strcmp(tree->token, ",") == 0);
    else if (strcmp(tree->token, ";") == 0);
    else if (strcmp(tree->token, "&&") == 0 ||
             strcmp(tree->token, "/") == 0 ||
             strcmp(tree->token, "==") == 0 ||
             strcmp(tree->token, ">") == 0 ||
             strcmp(tree->token, ">=") == 0 ||
             strcmp(tree->token, "<") == 0 ||
             strcmp(tree->token, "<=") == 0 ||
             strcmp(tree->token, "-") == 0 ||
             strcmp(tree->token, "!") == 0 ||
             strcmp(tree->token, "!=") == 0 ||
             strcmp(tree->token, "||") == 0 ||
             strcmp(tree->token, "+") == 0 ||
             strcmp(tree->token, "*") == 0 ||
             strcmp(tree->token, "&") == 0 ||
             strcmp(tree->token, "^") == 0 ||
             strcmp(tree->token, ",") == 0) {

    } else if (strcmp(tree->token, "|") == 0);
    else if (strcmp(tree->token, "solver") == 0) {
        findVariables(tree->left, MYscope);
    }
    if (tree->left)
        syntaxAnalyzer(tree->left, MYscope);

    if (tree->right)
        syntaxAnalyzer(tree->right, MYscope);

}

int popParameters(Args *args, int count) {
    int size = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(args[i].type, "int") == 0)
            size += 4;
        else if (strcmp(args[i].type, "char") == 0)
            size += 1;
        else if (strcmp(args[i].type, "real") == 0)
            size += 8;
        else if (strcmp(args[i].type, "string") == 0)
            size += atoi(args[i].length);
        else if (strcmp(args[i].type, "boolean") == 0)
            size += 4;
        else if (strcmp(args[i].type, "int*") == 0)
            size += 4;
        else if (strcmp(args[i].type, "char*") == 0)
            size += 4;
        else if (strcmp(args[i].type, "real*") == 0)
            size += 4;
    }
    return size;
} 

void addFirstScope(node *node, char *SCOPE, char *var, char *label, char *trueLab, char *falseLab) {
    if (SCOPE != NULL) {
        node->SCOPE = (char *) malloc(sizeof(char) * (1 + strlen(SCOPE)));
        strcpy(node->SCOPE, SCOPE);
    } else if (node->SCOPE == NULL) {
        node->SCOPE = (char *) malloc(sizeof(char) * 2);
        strcpy(node->SCOPE, "");
    }

    if (var != NULL) {
        node->var = (char *) malloc(sizeof(char) * (1 + strlen(var)));
        strcpy(node->var, var);
    } else if (node->var == NULL) {
        node->var = (char *) malloc(sizeof(char) * 2);
        strcpy(node->var, "");
    }

    if (label != NULL && node->label == NULL) {
        node->label = (char *) malloc(sizeof(char) * (1 + strlen(label)));
        strcpy(node->label, label);
    }

    if (trueLab != NULL && node->trueLab == NULL) {
        node->trueLab = (char *) malloc(sizeof(char) * (1 + strlen(trueLab)));
        strcpy(node->trueLab, trueLab);
    }

    if (falseLab != NULL && node->falseLab == NULL) {
        node->falseLab = (char *) malloc(sizeof(char) * (1 + strlen(falseLab)));
        strcpy(node->falseLab, falseLab);
    }

}

void addSecondScope(node *node, char *SCOPE, char *var, char *label, char *trueLab, char *falseLab) {
    if (SCOPE != NULL) {
        node->SCOPE = (char *) malloc(sizeof(char) * (1 + strlen(SCOPE)));
        strcpy(node->SCOPE, SCOPE);
    } else if (node->SCOPE == NULL) {
        node->SCOPE = (char *) malloc(sizeof(char) * 2);
        strcpy(node->SCOPE, "");
    }

    if (var != NULL) {
        node->var = (char *) malloc(sizeof(char) * (1 + strlen(var)));
        strcpy(node->var, var);
    } else if (node->var == NULL) {
        node->var = (char *) malloc(sizeof(char) * 2);
        strcpy(node->var, "");
    }

    if (label != NULL) {
        node->label = (char *) malloc(sizeof(char) * (1 + strlen(label)));
        strcpy(node->label, label);
    }

    if (trueLab != NULL) {
        node->trueLab = (char *) malloc(sizeof(char) * (1 + strlen(trueLab)));
        strcpy(node->trueLab, trueLab);
    }

    if (falseLab != NULL && node->falseLab == NULL) {
        node->falseLab = (char *) malloc(sizeof(char) * (1 + strlen(falseLab)));
        strcpy(node->falseLab, falseLab);
    }

}

char *freshVariables() {
    char *x;
    asprintf(&x, "t%d", t++);
    return x;
}

char *freshLabel() {
    char *x;
    asprintf(&x, "L%d", lab++);
    return x;
}

char *generator(char *s1, char *s2, char *s3, char *s4, char *s5) {
    char *x;

    asprintf(&x, "%s %s %s %s %s\n", s1, s2, s3, s4, s5);
    return x;
}

char *replaceString(const char *s, const char *old_word, const char *new_word) {
    char *res;
    int i, c = 0;
    int newTempLen = strlen(new_word);
    int oldTempLen = strlen(old_word);
    for (i = 0; s[i] != '\0'; i++) {
        if (strstr(&s[i], old_word) == &s[i]) {
            c++;

            i += oldTempLen - 1;
        }
    }

    res = (char *) malloc(i + c * (newTempLen - oldTempLen) + 1);

    i = 0;
    while (*s) {
        if (strstr(s, old_word) == s) {
            strcpy(&res[i], new_word);
            i += newTempLen;
            s += oldTempLen;
        } else
            res[i++] = *s++;
    }

    res[i] = '\0';
    return res;
}

char *firstStrCat(char *des, char *src) {
    char *tamp = des;
    char *num;
    asprintf(&num, "%d ", line++);
    if (src != NULL) {
        if (des == NULL) {
            des = (char *) malloc((strlen(src) + 1) * sizeof(char));
            strcpy(des, src);
            return des;
        }
        des = (char *) malloc((strlen(des) + strlen(src) + 1 + strlen(num)) * sizeof(char));
        if (tamp != NULL) {
            strcat(des, tamp);
        }
        if (src != NULL) {
            strcat(des, src);
        }
    }
    return des;
}

char *addSpaces(char *label) {
    char *message;
    char x = ' ';
    int length = strlen(firstStrCat(label, "\0"));
    if (label == NULL || !strcmp(label, ""))
        message = "";
    else {
        asprintf(&message, "%c", x);
        while (length < 5) {
            asprintf(&message, "%c%s", x, message);
            length++;
        }
        asprintf(&label, "%s: ", firstStrCat(label, "\0"));
        message = firstStrCat(message, label);
    }
    return message;
}

void M3AC(node *tree) {

    if (strcmp(tree->token, "=") == 0) {
        if (tree->left != NULL) M3AC(tree->left);
        if (tree->right != NULL) M3AC(tree->right);
        addFirstScope(tree, firstStrCat(tree->right->SCOPE, generator(tree->left->var, "=", tree->right->var, "", "")), NULL,
                      NULL, NULL, NULL);
        return;
    } else if (strcmp(tree->token, "if") == 0) {
        if (tree->left->left)
            addFirstScope(tree->left->left, NULL, NULL, NULL, NULL, tree->label);
        if (tree->right)
            addSecondScope(tree->right, NULL, NULL, tree->label, NULL, NULL);
        if (tree->left != NULL) M3AC(tree->left);
        if (tree->right != NULL) M3AC(tree->right);
        addFirstScope(tree, firstStrCat(tree->left->left->SCOPE, firstStrCat(addSpaces(tree->left->left->label),
                                                                             firstStrCat(addSpaces(
                                                                                                 tree->left->left->trueLab),
                                                                                         firstStrCat(tree->right->SCOPE,
                                                                                                     addSpaces(
                                                                                                             tree->trueLab))))),
                      NULL, NULL, NULL, NULL);
        return;
    } else if (strcmp(tree->token, "if-else") == 0) {
        if (tree->right->left)
            addFirstScope(tree->right->left, NULL, NULL, tree->label, NULL, NULL);
        if (tree->right->right->left)
            addSecondScope(tree->right->right->left, NULL, NULL, tree->label, NULL, tree->label);
        if (tree->right->left)
            addSecondScope(tree->right->left, NULL, NULL, tree->label, NULL, tree->label);

        if (tree->left != NULL) M3AC(tree->left);
        if (tree->right != NULL) M3AC(tree->right);
        addFirstScope(tree, firstStrCat(firstStrCat(tree->left->left->SCOPE,
                                                    firstStrCat(addSpaces(tree->left->left->trueLab),
                                                                tree->right->left->SCOPE)), firstStrCat(
                firstStrCat("goto ", firstStrCat(firstStrCat(tree->label, "\n"),
                                                 firstStrCat(addSpaces(tree->left->left->falseLab),
                                                             tree->right->right->left->SCOPE))),
                addSpaces(tree->label))), NULL, NULL, NULL, NULL);
        return;
    } else if (strcmp(tree->token, "while") == 0) {
        if (tree->left->left)
            addFirstScope(tree->left->left, NULL, NULL, NULL, tree->falseLab, tree->label);
        if (tree->right)
            addSecondScope(tree->right, NULL, NULL, tree->label, NULL, NULL);

        if (tree->left != NULL) M3AC(tree->left);
        if (tree->right != NULL) M3AC(tree->right);

        addFirstScope(tree, firstStrCat(
                firstStrCat(firstStrCat(addSpaces(tree->trueLab), tree->left->left->SCOPE), addSpaces(tree->falseLab)),
                firstStrCat(tree->right->SCOPE, firstStrCat(firstStrCat("\tgoto ", firstStrCat(tree->trueLab, "\n")),
                                                            addSpaces(tree->label)))), NULL, NULL, NULL, NULL);
        return;
    } else if (strcmp(tree->token, "statements") == 0) {

        if (tree->right != NULL)
            if (strcmp(tree->right->token, "if-else") == 0 || strcmp(tree->right->token, "while") == 0)
                addSecondScope(tree->right, NULL, NULL, tree->label, NULL, NULL);
        if (tree->right != NULL && tree->left != NULL)
            if (strcmp(tree->left->right->token, "if") == 0 || strcmp(tree->left->right->token, "if-else") == 0 ||
                strcmp(tree->left->right->token, "while") == 0)
                addSecondScope(tree->right, NULL, NULL, NULL, tree->left->right->label, NULL);
        if (tree->left != NULL) M3AC(tree->left);
        if (tree->right != NULL) M3AC(tree->right);

        if (tree->right != NULL && tree->left != NULL)
            if ((strcmp(tree->right->token, "while") == 0 || strcmp(tree->right->token, "if-else") == 0) &&
                (strcmp(tree->left->right->token, "if") == 0 || strcmp(tree->left->right->token, "if-else") == 0 ||
                 strcmp(tree->left->right->token, "while") == 0))
                addFirstScope(tree, firstStrCat(tree->left->SCOPE, &tree->right->SCOPE[8]), NULL, NULL, NULL, NULL);
            else
                addFirstScope(tree, firstStrCat(tree->left->SCOPE, tree->right->SCOPE), NULL, NULL, NULL, NULL);
        else if (tree->right != NULL) {
            if (strcmp(tree->right->token, "if-else") == 0 || strcmp(tree->right->token, "while") == 0)
                addFirstScope(tree, tree->right->SCOPE, NULL, NULL, NULL, NULL);
            else
                addFirstScope(tree, firstStrCat(tree->right->SCOPE, addSpaces(tree->right->label)), NULL, NULL, NULL,
                              NULL);
        } else
            addFirstScope(tree, "", NULL, NULL, NULL, NULL);

        return;

    } else if (strcmp(tree->token, "FUNCTION") == 0) {
        if (tree->left != NULL) M3AC(tree->left);
        if (tree->right != NULL) M3AC(tree->right);
        char *x;
        asprintf(&x, " %s:\n", tree->left->token);
        addFirstScope(tree, firstStrCat(x, tree->right->right->SCOPE), NULL, NULL, NULL, NULL);
        return;
    } else if (strcmp(tree->token, "FUNC") == 0) {
        if (tree->left != NULL) M3AC(tree->left);
        if (tree->right != NULL) M3AC(tree->right);

        char *x;
        asprintf(&x, " %s:\n", tree->left->token);
        addFirstScope(tree, firstStrCat(x, tree->right->left->SCOPE), NULL, NULL, NULL, NULL);
        return;
    } else if (strcmp(tree->token, "expression_list") == 0) {
        if (tree->left != NULL) M3AC(tree->left);
        if (tree->right != NULL) M3AC(tree->right);
        if (tree->right == NULL)
            addFirstScope(tree,
                          firstStrCat(tree->left->SCOPE, firstStrCat("PushParam ", firstStrCat(tree->left->var, "\n"))),
                          NULL, NULL, NULL, NULL);
        else
            addFirstScope(tree, firstStrCat(
                    firstStrCat(tree->left->SCOPE, firstStrCat("PushParam ", firstStrCat(tree->left->var, "\n"))),
                    tree->right->left->SCOPE), NULL, NULL, NULL, NULL);
    } else if (strcmp(tree->token, "Call func") == 0) {

        if (tree->left != NULL) M3AC(tree->left);
        if (tree->right != NULL) M3AC(tree->right);
        char *x, *parm = (char *) malloc(sizeof(char));
        if (tree->right->left == NULL)
            strcpy(parm, "");
        else
            parm = tree->right->left->SCOPE;
        addFirstScope(tree, NULL, freshVariables(), NULL, NULL, NULL);
        asprintf(&x, "%s%s = LCALL %s\n‪\tpopParameters %d‬‬‬‬\n", parm, tree->var, tree->left->token, tree->cnt);
        addFirstScope(tree, x, NULL, NULL, NULL, NULL);
        return;
    } else if (strcmp(tree->token, "CODE") == 0) {
        if (tree->left != NULL) M3AC(tree->left);
        if (tree->right != NULL) M3AC(tree->right);
        if (tree->left)
            addFirstScope(tree, firstStrCat(tree->left->SCOPE, tree->right->SCOPE), NULL, NULL, NULL, NULL);
        else
            addFirstScope(tree, tree->right->SCOPE, NULL, NULL, NULL, NULL);
        tree->SCOPE = replaceString(tree->SCOPE, "\n\n", "\n");
        char x = 'a', *y, *z;

        while (x <= 'z') {
            asprintf(&y, "\n%c", x);
            asprintf(&z, "\n\t%c", x);
            tree->SCOPE = replaceString(tree->SCOPE, y, z);
            x++;
        }
        x = 'A';
        while (x <= 'Z') {
            asprintf(&y, "\n%c", x);
            asprintf(&z, "\n\t%c", x);
            tree->SCOPE = replaceString(tree->SCOPE, y, z);
            x++;
        }
        return;
    } else if (strcmp(tree->token, "BODY") == 0) {

        if (tree->left != NULL) M3AC(tree->left);
        if (tree->right != NULL) M3AC(tree->right);
        if (tree->right->right->left) {

            if (tree->right->right->left->SCOPE[strlen(firstStrCat(tree->right->right->left->SCOPE, "\0")) - 2] == ':')
                addFirstScope(tree,
                              firstStrCat(firstStrCat("\tBeginFunc‬‬\n", tree->right->right->left->SCOPE), "EndFunc\n"),
                              NULL, NULL, NULL, NULL);
            else
                addFirstScope(tree, firstStrCat(firstStrCat("\tBeginFunc‬‬\n", tree->right->right->left->SCOPE),
                                                "\tEndFunc\n"), NULL, NULL, NULL, NULL);
        } else
            addFirstScope(tree, firstStrCat("\tBeginFunc‬‬\n", "\tEndFunc\n"), NULL, NULL, NULL, NULL);

        return;
    } else if (strcmp(tree->token, "Main") == 0) {

        if (tree->left != NULL) M3AC(tree->left);
        if (tree->right != NULL) M3AC(tree->right);

        addFirstScope(tree, firstStrCat(" Main:\n", tree->left->right->SCOPE), NULL, NULL, NULL, NULL);
        return;
    } else if (strcmp(tree->token, "functions") == 0) {
        if (tree->left != NULL) M3AC(tree->left);
        if (tree->right != NULL) M3AC(tree->right);
        if (tree->left != NULL)
            addFirstScope(tree, firstStrCat(tree->left->SCOPE, tree->right->SCOPE), NULL, NULL, NULL, NULL);
        else addFirstScope(tree, tree->right->SCOPE, NULL, NULL, NULL, NULL);
        return;
    } else if (strcmp(tree->token, "return") == 0) {

        if (tree->left != NULL) M3AC(tree->left);
        if (tree->right != NULL) M3AC(tree->right);

        addFirstScope(tree, firstStrCat(tree->left->SCOPE, generator("return", tree->left->var, "", "", "")), NULL, NULL,
                      NULL, NULL);
        return;
    } else if (strcmp(tree->token, "{") == 0) {
        if (tree->right->right->left)
            addFirstScope(tree, NULL, NULL, tree->right->right->left->label, tree->right->right->left->trueLab,
                          tree->right->right->left->falseLab);
        if (tree->left != NULL) M3AC(tree->left);
        if (tree->right != NULL) M3AC(tree->right);
        if (tree->right->right->left)
            addFirstScope(tree, tree->right->right->left->SCOPE, tree->right->right->left->var, NULL, NULL, NULL);
        return;
    } else if (strcmp(tree->token, "}") == 0) {
        if (tree->left != NULL) M3AC(tree->left);
        if (tree->right != NULL) M3AC(tree->right);


    } else if (strcmp(tree->token, "assignment_statement") == 0) {
        if (tree->left != NULL) M3AC(tree->left);
        if (tree->right != NULL) M3AC(tree->right);
        addFirstScope(tree, tree->left->SCOPE, tree->left->var, tree->left->label, tree->left->trueLab,
                      tree->left->falseLab);
        return;

    } else if (strcmp(tree->token, "+") == 0 ||
               strcmp(tree->token, "*") == 0 ||
               strcmp(tree->token, "-") == 0 ||
               strcmp(tree->token, "/") == 0) {

        if (tree->left != NULL) M3AC(tree->left);
        if (tree->right != NULL) M3AC(tree->right);
        addFirstScope(tree, NULL, freshVariables(), NULL, NULL, NULL);
        addFirstScope(tree, firstStrCat(firstStrCat(tree->left->SCOPE, tree->right->SCOPE),
                                        generator(tree->var, "=", tree->left->var, tree->token, tree->right->var)), NULL,
                      NULL, NULL, NULL);
        return;
    } else if (strcmp(tree->token, "&") == 0) {
        if (tree->left != NULL) M3AC(tree->left);
        if (tree->right != NULL) M3AC(tree->right);
        if ((tree->left->left == NULL))
            addFirstScope(tree, "", firstStrCat("&", (tree->left->token)), NULL, NULL, NULL);
        else if (strcmp(tree->left->left->token, "[") == 0) {
            char *x, *fv1, *fv2;
            asprintf(&fv1, "%s", freshVariables());
            asprintf(&fv2, "%s", freshVariables());
            asprintf(&x, "\t%s = &%s\n\t%s = %s + %s\n", fv1, tree->left->token, fv2, fv1, tree->left->left->left->var);
            addFirstScope(tree, firstStrCat(tree->left->left->left->SCOPE, x), fv2, NULL, NULL, NULL);
        } else if (tree->left->left->left == NULL)
            addFirstScope(tree, "", firstStrCat("&", (tree->left->left->token)), NULL, NULL, NULL);
        else {
            char *x, *fv1, *fv2;
            asprintf(&fv1, "%s", freshVariables());
            asprintf(&fv2, "%s", freshVariables());
            asprintf(&x, "\t%s = &%s\n\t%s = %s + %s\n", fv1, tree->left->left->token, fv2, fv1,
                     tree->left->left->left->left->var);
            addFirstScope(tree, firstStrCat(tree->left->left->left->left->SCOPE, x), fv2, NULL, NULL, NULL);
        }


        return;
    } else if (strcmp(tree->token, "^") == 0) {
        if (tree->left != NULL) M3AC(tree->left);
        if (tree->right != NULL) M3AC(tree->right);
        if ((tree->left->left == NULL))
            addFirstScope(tree, "", firstStrCat("*", (tree->left->token)), NULL, NULL, NULL);
        else {
            addFirstScope(tree, "", firstStrCat("*", (tree->left->left->token)), NULL, NULL, NULL);
        }

        return;
    } else if (strcmp(tree->token, "==") == 0 ||
               strcmp(tree->token, ">") == 0 ||
               strcmp(tree->token, ">=") == 0 ||
               strcmp(tree->token, "<") == 0 ||
               strcmp(tree->token, "<=") == 0 ||
               strcmp(tree->token, "!=") == 0) {

        if (tree->left != NULL) M3AC(tree->left);
        if (tree->right != NULL) M3AC(tree->right);
        addFirstScope(tree, firstStrCat(firstStrCat(tree->left->SCOPE, tree->right->SCOPE), firstStrCat(
                generator("if", tree->left->var, tree->token, tree->right->var,
                    firstStrCat("goto ", firstStrCat(tree->trueLab, "\n"))),
                firstStrCat("\tgoto ", firstStrCat(tree->falseLab, "\n")))), NULL, NULL, NULL, NULL);


        return;
    } else if (strcmp(tree->token, "(") == 0) {
        addFirstScope(tree->left, NULL, NULL, NULL, tree->trueLab, tree->falseLab);
        if (tree->left != NULL) M3AC(tree->left);
        if (tree->right != NULL) M3AC(tree->right);
        addFirstScope(tree, tree->left->SCOPE, tree->left->var, NULL, NULL, NULL);
        return;
    } else if (strcmp(tree->token, "!") == 0) {
        addFirstScope(tree->left, NULL, NULL, NULL, tree->trueLab, tree->falseLab);
        if (tree->left != NULL) M3AC(tree->left);
        if (tree->right != NULL) M3AC(tree->right);

        addFirstScope(tree, tree->left->SCOPE, NULL, NULL, NULL, NULL);

        return;
    } else if (strcmp(tree->token, "||") == 0) {
        addFirstScope(tree->left, NULL, NULL, NULL, tree->trueLab, NULL);
        addFirstScope(tree->right, NULL, NULL, NULL, tree->trueLab, tree->falseLab);
        if (tree->left != NULL) M3AC(tree->left);
        if (tree->right != NULL) M3AC(tree->right);
        addFirstScope(tree,
                      firstStrCat(tree->left->SCOPE, firstStrCat(addSpaces(tree->left->falseLab), tree->right->SCOPE)),
                      NULL, NULL, NULL, NULL);
        return;
    } else if (strcmp(tree->token, "&&") == 0) {

        addFirstScope(tree->left, NULL, NULL, NULL, NULL, tree->falseLab);
        addFirstScope(tree->right, NULL, NULL, NULL, tree->trueLab, tree->falseLab);
        if (tree->left != NULL) M3AC(tree->left);
        if (tree->right != NULL) M3AC(tree->right);
        addFirstScope(tree,
                      firstStrCat(tree->left->SCOPE, firstStrCat(addSpaces(tree->left->trueLab), tree->right->SCOPE)),
                      NULL, NULL, NULL, NULL);
        return;
    } else if (strcmp(tree->token, "null") == 0) {
        if (tree->left != NULL) M3AC(tree->left);
        if (tree->right != NULL) M3AC(tree->right);
        addFirstScope(tree, "", tree->token, NULL, NULL, NULL);
        return;
    } else if (strcmp(tree->token, "solver") == 0) {
        if (tree->left != NULL) M3AC(tree->left);
        if (tree->right != NULL) M3AC(tree->right);
        if (tree->left->left == NULL)
            addFirstScope(tree, "", tree->left->token, NULL, NULL, NULL);
        else {
            char *x, *fv1, *fv2;
            asprintf(&fv1, "%s", freshVariables());
            asprintf(&fv2, "%s", freshVariables());
            asprintf(&x, "\t%s = &%s\n\t%s = %s + %s\n", fv1, tree->left->token, fv2, fv1, tree->left->left->left->var);
            addFirstScope(tree, firstStrCat(tree->left->left->left->SCOPE, x), firstStrCat("*", fv2), NULL, NULL, NULL);
        }

        return;
    } else if ((tree->left != NULL) &&
               (strcmp(tree->left->token, "INT") == 0 ||
                strcmp(tree->left->token, "HEX") == 0 ||
                strcmp(tree->left->token, "CHAR") == 0 ||
                strcmp(tree->left->token, "REAL") == 0 ||
                strcmp(tree->left->token, "STRING") == 0 ||
                strcmp(tree->left->token, "BOOLEAN") == 0)) {

        if (tree->left != NULL) M3AC(tree->left);
        if (tree->right != NULL) M3AC(tree->right);
        if (strcmp(tree->left->token, "STRING") == 0)
            addFirstScope(tree, "", tree->token, NULL, NULL, NULL);
        else if (strcmp(tree->left->token, "BOOLEAN") == 0) {
            if (strcmp(tree->token, "true") == 0 && tree->trueLab != NULL)
                addFirstScope(tree, firstStrCat("goto ", firstStrCat(tree->trueLab, "\n")), tree->token, NULL, NULL,
                              NULL);
            else if (strcmp(tree->token, "false") == 0 && tree->falseLab != NULL)
                addFirstScope(tree, firstStrCat("goto ", firstStrCat(tree->falseLab, "\n")), tree->token, NULL, NULL,
                              NULL);
            else
                addFirstScope(tree, tree->token, tree->token, NULL, NULL, NULL);
        } else
            addFirstScope(tree, "", tree->token, NULL, NULL, NULL);
        return;
    } else if (strcmp(tree->token, "") == 0 || strcmp(tree->token, " ") == 0) {

        if (tree->left)
            addFirstScope(tree->left, NULL, NULL, tree->label, tree->trueLab, tree->falseLab);
        if (tree->right)
            addFirstScope(tree->right, NULL, NULL, tree->label, tree->trueLab, tree->falseLab);
        if (tree->left != NULL) M3AC(tree->left);
        if (tree->right != NULL) M3AC(tree->right);
        if (tree->left && tree->right)
            addFirstScope(tree, firstStrCat(tree->left->SCOPE, tree->right->SCOPE), tree->right->var, NULL, NULL, NULL);
        else if (tree->left)
            addFirstScope(tree, tree->left->SCOPE, tree->left->var, NULL, NULL, NULL);
        else if (tree->right)
            addFirstScope(tree, tree->right->SCOPE, tree->right->var, NULL, NULL, NULL);
        return;
    } else {
        if (tree->left)
            M3AC(tree->left);

        if (tree->right)
            M3AC(tree->right);
        addFirstScope(tree, "", tree->token, NULL, NULL, NULL);
        return;
    }
    if (tree->left)
        M3AC(tree->left);
    if (tree->right)
        M3AC(tree->right);
}


