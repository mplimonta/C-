/****************************************************/
/* File: tiny.l                                     */
/* Lex specification for TINY                       */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/
%option noyywrap
%{
#include "globals.h"
#include "util.h"
#include "scan.h"
/* lexeme of identifier or reserved word */
char tokenString[MAXTOKENLEN+1];
extern int yylex(void);
%}

digito      [0-9]
numero      {digito}+
letra      [a-zA-Z]
identificador  {letra}+
novalinha     \n
espaco  [ \t]+

%%

"else"          {return ELSE;}
"if"            {return IF;}
"int"           {return INT;}
"return"        {return RETURN;}
"void"          {return VOID;}
"while"         {return WHILE;}
"+"             {return SOM;}
"-"             {return SUB;}
"*"             {return MULT;}
"/"             {return DIV;}
"<"             {return LT;}
"<="            {return LET;}
">"             {return GT;}
">="            {return GET;}
"=="            {return COMP;}
"!="            {return NEQ;}
"="             {return EQ;}
";"             {return PV;}
","             {return VIRG;}
"("             {return APAREN;}
")"             {return FPAREN;}
"["             {return ACOLCH;}
"]"             {return FCOLCH;}
"{"             {return ACHAVE;}
"}"             {return FCHAVE;}
"/*"            {
                  char c;
                  int linhaAux = lineno;
                  while(1){
                    c = input();
                    if (c == EOF){
                      printf("Erro Léxico na linha %d. Comentário aberto na linha %d não foi fechado!\n", lineno, linhaAux);
                      break;
                    }
                    if (c == '\n') lineno++;
                    if (c == '*'){
                      c = input();
                      if(c == '/') break;
                    }
                  }
                }
{numero}        {return NUM;}
{identificador} {return ID;}
{novalinha}     {lineno++;}
{espaco}        {}
.               {return ERRO;}

%%

TokenType getToken(void){
  static int firstTime = TRUE;
  TokenType currentToken;
  if (firstTime)
  { firstTime = FALSE;
    lineno++;
    yyin = source;
    yyout = listing;
  }
  currentToken = yylex();
  if(currentToken == ERRO){
    printf("Erro léxico na linha %d. Lexema '%s' é inválido.\n", lineno, yytext);
    return -1;
  }
  strncpy(tokenString,yytext,MAXTOKENLEN);
  if (TraceScan) {
    fprintf(listing,"\t%d: ",lineno);
    printToken(currentToken,tokenString);
  }
  return currentToken;
}

