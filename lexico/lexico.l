/****************************************************/
/* File: lexico.l                                   */
/* Lex specification for C-                         */
/* Matheus Presotto Limonta RA: 140740              */
/****************************************************/
/* 
else if int return void while

+ - * / < <= > >= == != = ; , () [] {} /* 

*/

%{

#include <stdlib.h>
#include <stdio.h>

#define ELSE 300
#define IF 301
#define INT 302
#define RETURN 303
#define VOID 304
#define WHILE 305
#define SOM 306
#define SUB 307
#define MULT 308
#define DIV 309
#define LT 310
#define LET 311
#define MT 312
#define MET 313
#define COMP 314
#define NEQ 315
#define EQ 316
#define PV 317
#define VIRG 318
#define APAREN 319
#define FPAREN 320
#define ACOLCH 321
#define FCOLCH 322
#define ACHAVE 323
#define FCHAVE 324
#define ACOMEN 325
#define FCOMEN 326
#define FIM 327
#define NUM 328
#define ID 329
#define NEWLINE 330
#define ERRO 331


%}

digito       [0-9]
numero      {digito}+
letra      [a-zA-Z]
identificador  {letra}+
espaco  [ \t]+

%option noyywrap

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
">"             {return MT;}
">="            {return MET;}
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
"/*"            {return ACOMEN;}
"*/"            {return FCOMEN;}
<<EOF>>         {return FIM;}
{numero}        {return NUM;}
{identificador} {return ID;}
[\n]            {return NEWLINE;}
{espaco}        {}
.               {return ERRO;}


%%

int main(int argc, char *argv[]){

  /*
  "posserr" eh o possivel erro que pode ser encontrado em um comentario
  (Ele eh relevante pois caso o comentario nao seja fechado, o analisador lexico devera apontar o erro)
  
  posserrLine eh a linha em que pode ter ocorrido um erro lexico caso o comentario nao seja fechado

  tokencom eh o token dentro de um comentario

  detected eh uma variavel auxiliar para sabermos se ocorreu um erro em um comentario
  */

  int token, linha = 1, tokencom, posserrLine = 1, detected = 0;
  
  char posserr = 'a';
  FILE *entrada;
  FILE *saida = fopen("saida.txt","w");
 
  if (entrada = fopen("entrada.txt","r")){
    yyin = entrada;
  }
  else{
    printf("Arquivo nao encontrado!!!\n");
    return 0;
    }
  
  
  while ((token=yylex())!=FIM){
    switch(token){
      case ELSE:      fprintf(saida, "ELSE "); break;
      case IF:        fprintf(saida, "IF "); break;
      case INT:       fprintf(saida, "INT "); break;
      case RETURN:    fprintf(saida, "RETURN "); break;
      case VOID:      fprintf(saida, "VOID "); break;
      case WHILE:     fprintf(saida, "WHILE "); break;
      case SOM:       fprintf(saida, "SOM "); break;
      case SUB:       fprintf(saida, "SUB "); break;
      case MULT:      fprintf(saida, "MULT "); break;
      case DIV:       fprintf(saida, "DIV "); break;
      case LT:        fprintf(saida, "LT "); break;
      case LET:       fprintf(saida, "LET "); break;
      case MT:        fprintf(saida, "MT "); break;
      case MET:       fprintf(saida, "MET "); break;
      case COMP:      fprintf(saida, "COMP "); break;
      case NEQ:       fprintf(saida, "NEQ "); break;
      case EQ:        fprintf(saida, "EQ "); break;
      case PV:        fprintf(saida, "PV "); break;
      case VIRG:      fprintf(saida, "VIRG "); break;
      case APAREN:      fprintf(saida, "APAREN "); break;
      case FPAREN:      fprintf(saida, "FPAREN "); break;
      case ACOLCH:      fprintf(saida, "ACOLCH "); break;
      case FCOLCH:      fprintf(saida, "FCOLCH "); break;
      case ACHAVE:      fprintf(saida, "ACHAVE "); break;
      case FCHAVE:      fprintf(saida, "FCHAVE "); break;
      case FIM:         fprintf(saida, "FIM "); break;
      case NUM:         fprintf(saida, "NUM "); break;
      case ID:          fprintf(saida, "ID "); break;
      case NEWLINE:     linha++; break;
      case ERRO:       {
                        printf("Erro léxico na linha %d, lexema: %s\n", linha, yytext);
                        return 0;
                        }  break;
      case ACOMEN:      { while((tokencom = yylex()) != FCOMEN)
                          {
                            switch(tokencom){
                              case NEWLINE: linha++; break;
                              case FIM: {
                                          if(posserr != 'a'){
                                            printf("Erro léxico na linha %d, lexema: %c\n", posserrLine, posserr);
                                          }
                                          return 0;
                                        } break;
                              case ERRO:  {if(!detected){
                                              posserr = yytext[0];
                                              posserrLine = linha;
                                              detected = 1;
                                            }
                                          }  break;
                              default: break;
                              }
                            if (tokencom == FIM) return 0;
                          }
                        }; break;
      case FCOMEN:      fprintf(saida, "FCOMEN "); break;
    }
  }

  fclose(saida);
  fclose(entrada);
  return(0);
}