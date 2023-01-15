/****************************************************/
/* File: tiny.y                                     */
/* The TINY Yacc/Bison specification file           */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/
%{
#define YYPARSER /* distinguishes Yacc output from other code files */

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

#define YYSTYPE TreeNode *
static TreeNode * savedTree; /* stores syntax tree for later return */
static int yylex(void);
int yyerror(char* msg);
static char * savedName; /* for use in assignments */
static int savedLineNo;  /* ditto */




%}

%token ELSE IF INT RETURN VOID WHILE SOM SUB MULT DIV
%token LT LET GT GET COMP NEQ EQ PV VIRG APAREN FPAREN
%token ACOLCH FCOLCH ACHAVE FCHAVE NUM ID ERRO

%% /* Grammar for Cminus */
programa : declaracao_lista     //raiz da arvore
          {savedTree = $1;}
         ;
declaracao_lista : declaracao_lista declaracao
                  {
                    YYSTYPE t = $1;
                    if(t != NULL){
                      while(t->sibling != NULL)
                      t = t->sibling;
                      t->sibling = $2;
                      $$ = $1;
                    }
                    else $$ = $2;
                  }
                 | declaracao {$$ = $1;}
                 ;
declaracao : var_declaracao {$$ = $1;}

           | fun_declaracao {$$ = $1;}

           ;
var_declaracao : INT ident PV 
              {
                $$ = newExpNode(TypeK);
                $$->type = IntegerK;
                $$->attr.name = "inteiro";
                $$->child[0] = $2;
                $2->nodekind = StmtK;
                $2->kind.stmt = VarK;
                $2->type = IntegerK;
						  }
               | INT ident ACOLCH num FCOLCH PV
                {
                  $$ = newExpNode(TypeK);
                  $$->type = IntegerK;
                  $$->attr.name = "inteiro";
                  $$->child[0] = $2;
                  $2->nodekind = StmtK;
                  $2->kind.stmt = VarK;
                  $2->type = IntegerK; 
                  $2->attr.len = $4->attr.val;
                }
                ;
fun_declaracao : INT ident APAREN params FPAREN composto_decl
                {
                  $$ = newExpNode(TypeK);
                  $$->type = IntegerK;
                  $$->attr.name = "inteiro";
                  $$->child[0] = $2;
                  $2->child[0] = $4;
                  $2->child[1] = $6;
                  $2->nodekind = StmtK;
                  $2->kind.stmt = FunK;
                  $2->type = IntegerK;
                  $4->type = IntegerK;
                }
                | VOID ident APAREN params FPAREN composto_decl
                {
                  $$ = newExpNode(TypeK);
                  $$->type = VoidK;
                  $$->attr.name = "void";
                  $$->child[0] = $2;
                  $2->child[0] = $4;
                  $2->child[1] = $6;
                  $2->nodekind = StmtK;
                  $2->kind.stmt = FunK;
                }
               ;
params : param_lista {$$ = $1;}
       | VOID
        {
				  $$ = newExpNode(TypeK);
          $$->attr.name = "void";
          $$->child[0] = NULL;
				}
       ;
param_lista : param_lista VIRG param 
            {
              YYSTYPE t = $1;
              if(t != NULL){
                while(t->sibling != NULL)
                t = t->sibling;
                t->sibling = $3;
                $$ = $1;
              }else $$ = $3;
            }
            | param {$$ = $1;}
            ;
tipo_especificador : INT
                  {
                    $$ = newExpNode(TypeK);
                    $$->attr.name = "inteiro";
                    $$->type = IntegerK;
                  }
                  | VOID
                  {
                    $$ = newExpNode(TypeK);
                    $$->attr.name = "void";
                    $$->type = VoidK;
                  }
                  ;
param : tipo_especificador ident
      {
        $$ = $1;
        $$->child[0]= $2;
      }
      | tipo_especificador ident ACOLCH FCOLCH
      {
        $$= $1;
        $$->child[0]= $2;
      }
      ;
composto_decl : ACHAVE local_declaracoes statement_lista FCHAVE
              {
                YYSTYPE t = $2;
                if(t != NULL){
                  while(t->sibling != NULL)
                  t = t->sibling;
                  t->sibling = $3;
                  $$ = $2;
                } 
                else $$ = $3;
              }
              | ACHAVE local_declaracoes FCHAVE //pois podem ser vazio
              {
                $$ = $2;
              }
              | ACHAVE statement_lista FCHAVE //pois podem ser vazio
              {
                $$ = $2;
              }
              | ACHAVE FCHAVE {}            //pois podem ser vazio
              ;
local_declaracoes : local_declaracoes var_declaracao 
                  {
                    YYSTYPE t = $1;
                    if(t != NULL){
                      while(t->sibling != NULL) t = t->sibling;
                      t->sibling = $2;
                      $$ = $1;
                    }else $$ = $2;
                  }
                  | var_declaracao
                  {
                    $$ = $1;
                  }
                   /* vazio, apaguei pois estava dando erro :/ */
                  ;
statement_lista : statement_lista statement 
                {
                    YYSTYPE t = $1;
                    if(t != NULL){
                      while(t->sibling != NULL)
                      t = t->sibling;
                      t->sibling = $2;
                      $$ = $1;
                    }else $$ = $2;
                  }
                  | statement
                  {
                    $$ = $1;
                  }
                /* vazio, apaguei pois estava dando erro :/ */
                ;
statement : expressao_decl
          {
            $$ = $1;
          }
          | composto_decl 
          {
            $$ = $1;
          }
          | selecao_decl 
          {
            $$ = $1;
          }
          | iteracao_decl 
          {
            $$ = $1;
          }
          | retorno_decl
          {
            $$ = $1;
          }
          ;
expressao_decl : expressao PV 
                {
                  $$ = $1;
                }
               | PV
               ;
selecao_decl : IF APAREN expressao FPAREN statement 
              {
                $$ = newStmtNode(IfK);
                $$->child[0] = $3;
                $$->child[1] = $5;
              }
             | IF APAREN expressao FPAREN statement ELSE statement
             {
                $$ = newStmtNode(IfK);
                $$->child[0] = $3;
                $$->child[1] = $5;
                $$->child[2] = $7;
             }
             ;
iteracao_decl : WHILE APAREN expressao FPAREN statement
              {
                $$ = newStmtNode(WhileK);
                $$->child[0] = $3;
                $$->child[1] = $5;
              }
              ;
retorno_decl : RETURN PV 
              {
                $$ = newStmtNode(ReturnK);
              }
             | RETURN expressao PV
              {
                $$ = newStmtNode(ReturnK);
                $$->child[0] = $2;
              }
             ;
expressao : var EQ expressao 
          {
            $$ = newStmtNode(AssignK);
            $$->attr.name = $1->attr.name;
            $$->child[0] = $1;
            $$->child[1] = $3;
          }
          | simples_expressao
          {
            $$ = $1;
          }
          ;
var : ident 
    {
      $$ = $1;
    }
    | ident ACOLCH expressao FCOLCH
    {
      $$ = $1;
      $$->child[0] = $3;
      $$->kind.exp = VetK;
      $$->type = IntegerK;
    }
    ;
simples_expressao : soma_expressao relacional soma_expressao 
                  {
                      $$ = $2;
                      $$->child[0] = $1;
                      $$->child[1] = $3;
                  }
                  | soma_expressao
                  {
                    $$ = $1;
                  }
                  ;
relacional : LET 
            {
              $$ = newExpNode(OpK);
              $$->attr.op = LET;                            
              $$->type = BooleanK;
            }
           | LT 
           {
            $$ = newExpNode(OpK);
            $$->attr.op = LT;                            
						$$->type = BooleanK;
           }
           | GT 
           {
            $$ = newExpNode(OpK);
            $$->attr.op = GT;                            
						$$->type = BooleanK;
           }
           | GET 
           {
            $$ = newExpNode(OpK);
            $$->attr.op = GET;                            
						$$->type = BooleanK;
           }
           | COMP 
           {
            $$ = newExpNode(OpK);
            $$->attr.op = COMP;                            
						$$->type = BooleanK;
           }
           | NEQ
           {
            $$ = newExpNode(OpK);
            $$->attr.op = NEQ;                            
						$$->type = BooleanK;
           }
           ;
soma_expressao : soma_expressao soma termo 
              {
                $$ = $2;
                $$->child[0] = $1;
                $$->child[1] = $3;
              }
               | termo
               {
                $$ = $1;
               }
               ;
soma : SOM 
      {
        $$ = newExpNode(OpK);
        $$->attr.op = SOM;  
      }
     | SUB
     {
      $$ = newExpNode(OpK);
      $$->attr.op = SUB;  
     }
     ;
termo : termo mult fator
      {
        $$ = $2;
        $$->child[0] = $1;
        $$->child[1] = $3;
      }
      | fator
      {
        $$ = $1;
      }
      ;
mult : MULT 
      {
        $$ = newExpNode(OpK);
        $$->attr.op = MULT; 
      }
      | DIV
      {
        $$ = newExpNode(OpK);
        $$->attr.op = DIV; 
      }
     ;
fator : APAREN expressao FPAREN 
      {
        $$ = $2;
      }
      | var 
      {
        $$ = $1;
      }
      | ativacao 
      {
        $$ = $1;
      }
      | num
      {
        $$ = $1;
      }
      ;
ativacao : ident APAREN arg_lista FPAREN
          {
            $$ = $1;
            $$->child[0] = $3;
            $$->nodekind = StmtK;
            $$->kind.stmt = CallK;
          }
          | ident APAREN FPAREN
          {
            $$ = $1;
            $$->nodekind = StmtK;
            $$->kind.stmt = CallK;
          }
          ;
arg_lista : arg_lista VIRG expressao 
          {
            YYSTYPE t = $1;
            if(t != NULL){
              while(t->sibling != NULL)
              t = t->sibling;
              t->sibling = $3;
              $$ = $1;
            } else $$ = $3;
          }
          | expressao
          {
            $$ = $1;
          }
          ;
ident : ID
      {
      $$ = newExpNode(IdK);
      $$->attr.name = copyString(tokenString);
      }
;
num : NUM
      {
        $$ = newExpNode(ConstK);
        $$->attr.val = atoi(tokenString);
        $$->type = IntegerK;
      }
;

%%


/* yylex calls getToken to make Yacc/Bison output
 * compatible with ealier versions of the TINY scanner
 */
static int yylex(void)
{ return getToken(); }

int yyerror(char * message)
{ fprintf(listing,"Syntax error at line %d: %s\n",lineno,message);
  fprintf(listing,"Current token: ");
  printToken(yychar,tokenString);
  Error = TRUE;
  return 0;
}

TreeNode * parse(void){
  yyparse();
  return savedTree;
}

