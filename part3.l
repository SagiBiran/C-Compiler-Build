%x C_COMMENT

%{
#include<stdio.h>
#include<string.h>
#include "y.tab.h"
%}

%%
bool return BOOL_TYPE;
char return CHAR_TYPE;
int return INT_TYPE;
real return REAL_TYPE;
string return STR_TYPE;
int\* return INT_PTR;
char\* return CHAR_PTR;
real\* return REAL_PTR;
if return IF;
else return ELSE;
while return WHILE;
var return VAR;
void return VOID;
null return NONE;
main { yylval.string = strdup(yytext); return MAIN; }
"&&" return AND;
"/" return DIV;
"=" return ASSIGN;
"==" return EQ;
">" return G;
">=" return GE;
"<" return L;
"<=" return LE;
"-" return MINUS;
"!" return NOT;
"!=" return NOTEQ;
"||" return OR;
"+" return PLUS;
"*" return MUL;
"&" return ADDR;
"|" return LENGTH;
";" return SEMICOLON;
"," return COMMA;
"{" return L_BLOCK;
"}" return R_BLOCK;
"(" return L_SOGER;
")" return R_SOGER;
"[" return L_BRACKET;
"]" return R_BRACKET;
"/*"            { BEGIN(C_COMMENT); }
<C_COMMENT>"*/" { BEGIN(INITIAL); }
<C_COMMENT>\n   yylineno++;
<C_COMMENT>.   ;
return return RETURN;
true return BOOL_TRUE;
false return BOOL_FALSE;
[a-zA-Z][a-zA-Z0-9_]* { yylval.string = strdup(yytext); return ID; }
"\""[^"]*"\"" { yylval.string= strdup(yytext); return STRING; }
\'.\' { yylval.string = strdup(yytext); return CHAR; }
[+-]?[1-9][0-9]*|[0-9] { yylval.string = strdup(yytext); return INT_DEC; }
0(x|X)[0-9A-F]+ { yylval.string = strdup(yytext); return INT_HEX; }
[-+]?[0-9]*[\.]?[0-9]*[eE]?[-+]?[0-9]+ { yylval.string = strdup(yytext); return REAL; }
[\n] { yylineno++; } //For each line (enter=\n), do yylineo+=1
[ \t]+ ;
. return yytext[0];
%%


