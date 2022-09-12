// Part 3
//Author: Sagi Biran
//ID: 205620859

%{
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

%}
%union
{
    struct node *node;
    char *string;
}

%token <string> COMMENT WHILE IF ELSE 
%token <string> RETURN
%token <string> BOOL_TYPE STR_TYPE CHAR_PTR CHAR_TYPE INT_TYPE INT_PTR VOID
%token <string> AND ADDR EQ ASSIGN OR LENGTH GE G LE L NOTEQ NOT
%token <string> DIV PLUS MINUS MUL VAR
%token <string> STRING REAL CHAR NONE
%token <string> MAIN ID SEMICOLON COMMA L_SOGER R_SOGER L_BRACKET R_BRACKET L_BLOCK R_BLOCK
%token <string> INT_DEC INT_HEX BOOL_TRUE BOOL_FALSE  REAL_TYPE REAL_PTR  

%left ID OR AND 
%left  NOTEQ L LE GE G 
%left PLUS MINUS RETURN
%left MUL DIV
%left SEMICOLON EQ
%right NOT R_BLOCK


%nonassoc L_SOGER
%nonassoc IF
%nonassoc ELSE 


%type <node> address_expression statements block_statement dereference_expression expression_list function_call 
%type <node> expression lhs assignment_statement new_block dereference_support
%type <node> statement function_type regular_type variables declare parent_expression 
%type <node> body parameters_list parameters_upward function functions
%type <node> main program project declares 
%%


project: comment program { startNode = $2; syntaxAnalyzer($2,globalScope); M3AC($2); }; 

program: functions main{ $$ = makeNode("CODE",$1,$2); }
 comment: COMMENT comment { ; }| ;

main: VOID MAIN L_SOGER R_SOGER comment L_BLOCK body R_BLOCK { $$ = makeNode("Main",makeNode("ARGS",NULL,$7),NULL); t = 0; };

functions: functions  function { $$ = makeNode("functions",$1,$2); }
	    | { $$ = NULL; };

function: function_type ID L_SOGER parameters_upward R_SOGER comment L_BLOCK body R_BLOCK { $$ = makeNode("FUNC",makeNode($2,makeNode("",NULL,NULL),makeNode("ARGS",$4,makeNode("Return",$1,NULL))),makeNode("",$8,NULL)); t = 0; }
	   | VOID ID L_SOGER parameters_upward R_SOGER L_BLOCK  body R_BLOCK { $$ = makeNode("FUNCTION",makeNode($2,makeNode("",NULL,NULL),NULL),makeNode("ARGS",$4,$7)); t = 0; };

parameters_upward: parameters_list { $$ = $1; }
	  | { $$ = NULL; };

parameters_list: regular_type variables  { $$ = makeNode("(",$1,makeNode("",$2,makeNode(")",NULL,NULL))); }
	   | parameters_list SEMICOLON comment  parameters_list { $$ = makeNode("",$1,makeNode("",$4,NULL)); }	;

body: comment functions declares statements { $$ = makeNode("BODY", makeNode(" ",$2,NULL),makeNode(" ",$3,makeNode(" ",$4,makeNode(" ",NULL,NULL)))); };

declares: declares declare { $$ = makeNode("",$1,$2);} | { $$ = NULL; };

declare: VAR regular_type variables comment SEMICOLON comment { $$ = makeNode("var", $2,$3); };
		| STR_TYPE variables L_BRACKET INT_DEC R_BRACKET comment SEMICOLON comment { $$ = makeNode("var",makeNode("string", makeNode("[",makeNode("$3",NULL,NULL),NULL), NULL) ,$2); };

variables: ID COMMA variables { $$ = makeNode($1, makeNode(" ", $3, NULL),NULL); }
	| ID { $$ = makeNode($1, NULL, NULL); };

regular_type: BOOL_TYPE { $$ = makeNode("boolean", NULL, NULL); }
	 | CHAR_TYPE { $$ = makeNode("char", NULL, NULL); }
	 | INT_TYPE { $$ = makeNode("int", NULL, NULL); }
	 | REAL_TYPE { $$ = makeNode("real", NULL, NULL); }
	 | INT_PTR { $$ = makeNode("int*", NULL, NULL); }
	 | CHAR_PTR { $$ = makeNode("char*", NULL, NULL); }
	 | REAL_PTR { $$ = makeNode("real*", NULL, NULL); };

	
statements: statements statement { $$ = makeNode("statements",$1,$2); if(strcmp($2->token, "if") == 0 || strcmp($2->token, "if-else") == 0 || strcmp($2->token, "while") == 0){ if($$->cnt == 0) { addFirstScope($2,NULL,NULL,freshLabel(),NULL,NULL); $$->cnt = 1; } } } | { $$ = NULL; };

block_statement: statement { $$ = $1; if(strcmp($1->token, "if") == 0 || strcmp($1->token, "if-else") == 0 || strcmp($1->token, "while") == 0) addFirstScope($1,NULL,NULL,freshLabel(),NULL,NULL); } | declare { $$ = $1; } | function { $$ = $1; } | SEMICOLON { $$ = makeNode("",NULL,NULL); };

new_block: L_BLOCK functions comment declares statements R_BLOCK comment { $$ = makeNode("{",$2,makeNode("",$4,makeNode("", $5,("}",NULL,NULL)))); };

statement: IF L_SOGER expression R_SOGER block_statement { $$ = makeNode("if",makeNode("(", $3,makeNode(")",NULL,NULL)),$5); addFirstScope($3,NULL,NULL,NULL,freshLabel(),NULL); 
}%prec IF
| IF L_SOGER expression R_SOGER block_statement ELSE block_statement { $$ = makeNode("if-else",makeNode("", $3,makeNode("",NULL,NULL)),makeNode("",$5,makeNode("",$7,NULL))); addFirstScope($3,NULL,NULL,NULL,freshLabel(),NULL); addFirstScope($3,NULL,NULL,NULL,NULL,freshLabel()); }
| WHILE comment L_SOGER expression R_SOGER  block_statement { $$ = makeNode("while",makeNode("(", $4,makeNode(")",NULL,NULL)),$6); addFirstScope($$,NULL,NULL,NULL,freshLabel(),NULL); addFirstScope($$,NULL,NULL,NULL,NULL,freshLabel()); }
| assignment_statement SEMICOLON comment { $$ = makeNode("assignment_statement",$1,NULL); }
| expression SEMICOLON comment { $$ = $1; }
| RETURN expression SEMICOLON comment { $$ = makeNode("return",$2,NULL); }
| new_block { $$ = $1; };


assignment_statement: lhs ASSIGN expression { $$ = makeNode("=",$1,$3); };

lhs: ID L_BRACKET expression R_BRACKET { $$ = makeNode($1, makeNode("[",$3,makeNode("]",NULL,NULL)), NULL); } 
| ID { $$ = makeNode($1,NULL,NULL); }
| address_expression { $$ = $1; }
| dereference_expression{ $$ = $1; };


function_type: BOOL_TYPE { $$ = makeNode("boolean", NULL, NULL); }
	  | CHAR_TYPE { $$ = makeNode("char", NULL, NULL); }
	  | INT_TYPE { $$ = makeNode("int", NULL, NULL); }
	  | REAL_TYPE { $$ = makeNode("real", NULL, NULL); }
	  | INT_PTR { $$ = makeNode("int*", NULL, NULL); }
	  | CHAR_PTR { $$ = makeNode("char*", NULL, NULL); }
	  | REAL_PTR { $$ = makeNode("real*", NULL, NULL); };

expression: L_SOGER expression R_SOGER { $$ = makeNode("(",$2,makeNode(")",NULL,NULL)); }
      | expression EQ expression { $$ = makeNode("==",$1,$3); }
      | expression NOTEQ expression { $$ = makeNode("!=",$1,$3); }
      | expression GE expression { $$ = makeNode(">=",$1,$3); }
      | expression G expression { $$ = makeNode(">",$1,$3); }
      | expression LE expression { $$ = makeNode("<=",$1,$3); }
      | expression L expression { $$ = makeNode("<",$1,$3); }
      | expression AND expression { $$ = makeNode("&&",$1,$3); addFirstScope($1,NULL,NULL,NULL,freshLabel(),NULL); }
      | expression OR expression { $$ = makeNode("||",$1,$3); addFirstScope($1,NULL,NULL,NULL,NULL,freshLabel()); }
      | expression PLUS expression { $$ = makeNode("+",$1,$3); }
      | expression MINUS expression { $$ = makeNode("-",$1,$3); }
      | expression MUL expression { $$ = makeNode("*",$1,$3); }
      | expression DIV expression { $$ = makeNode("/",$1,$3); }
      | NOT expression { $$ = makeNode("!",$2,NULL); }
      | address_expression { $$ = $1; }
      | dereference_expression { $$ = $1; }
      | function_call comment { $$ = $1; }
      | INT_DEC { $$ = makeNode($1,makeNode("INT",NULL,NULL),NULL); }
      | INT_HEX { $$ = makeNode($1,makeNode("HEX", NULL, NULL),NULL); }
      | CHAR { $$ = makeNode($1,makeNode("CHAR", NULL, NULL),NULL); }
      | REAL { $$ = makeNode($1,makeNode("REAL", NULL, NULL),NULL); }
      | STRING { $$ = makeNode($1,makeNode("STRING", NULL, NULL),NULL); }
      | BOOL_FALSE { $$ = makeNode($1,makeNode("BOOLEAN", NULL, NULL),NULL); }
      | BOOL_TRUE { $$ = makeNode($1,makeNode("BOOLEAN", NULL, NULL),NULL); }
      | LENGTH ID LENGTH { $$ = makeNode("|",makeNode($2,NULL,NULL),makeNode("|",NULL,NULL)); }
      | ID L_BRACKET expression R_BRACKET { $$ = makeNode("solver",makeNode($1,makeNode("[",$3,makeNode("]",NULL,NULL)),NULL),NULL); }
      | ID { $$ = makeNode("solver",makeNode($1,NULL,NULL),NULL); }
      | NONE { $$ = makeNode("null",NULL,NULL); };

address_expression: ADDR ID { $$ = makeNode("&",makeNode($2,NULL,NULL),NULL); }
	      | ADDR L_SOGER ID R_SOGER { $$ = makeNode("&",makeNode("(",makeNode($3,NULL,NULL),NULL),makeNode(")",NULL,NULL)); }
	      | ADDR ID L_BRACKET expression R_BRACKET { $$ = makeNode("&", makeNode($2,makeNode("[",$4,makeNode("]",NULL,NULL)),NULL),NULL); }
	      | ADDR L_SOGER ID L_BRACKET expression R_BRACKET R_SOGER { $$ = makeNode("&",makeNode("(",	makeNode($3,makeNode("[",$5,makeNode("]",NULL,NULL)),NULL),makeNode(")",NULL,NULL)),NULL); };

dereference_expression: MUL ID { $$ = makeNode("^",makeNode($2,NULL,NULL),NULL); addFirstScope($$,"",firstStrCat("*",$2),NULL,NULL,NULL); }
		 | MUL L_SOGER dereference_support R_SOGER { $$ = makeNode("^",makeNode("(",$3,NULL),makeNode(")",NULL,NULL)); addFirstScope($$,$3->SCOPE,firstStrCat("*",$3->var),NULL,NULL,NULL); }
		 | MUL ID L_BRACKET dereference_support R_BRACKET { $$ = makeNode($1, makeNode($2,makeNode("[",$4,makeNode("]",NULL,NULL)),NULL), NULL); };

dereference_support: ID INT_DEC { $$ = makeNode("solver",makeNode($1,NULL,NULL),makeNode($2,NULL,NULL)); };

expression_list: expression COMMA expression_list { $$ = makeNode("expression_list",$1,makeNode(",",$3,NULL)); } 
	   | expression { $$ = makeNode("expression_list",$1,NULL); }
	   | { $$ = NULL; };

parent_expression: L_SOGER expression_list R_SOGER { $$ = $2; };

function_call: ID parent_expression { $$ = makeNode("Call func",makeNode($1,NULL,NULL),makeNode("ARGS",$2,NULL)); };

%%
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

