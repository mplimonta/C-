/****************************************************/
/* File: analyze.c                                  */
/* Semantic analyzer implementation                 */
/* for the C- compiler                              */
/****************************************************/

#include "globals.h"
#include "symtab.h"
#include "analyze.h"

/* counter for variable memory locations */
static int location = 0;
int main_presence = 0;

/* Procedure traverse is a generic recursive 
 * syntax tree traversal routine:
 * it applies preProc in preorder and postProc 
 * in postorder to tree pointed to by t
 */

static void typeError(TreeNode * t, char * message)
{ fprintf(listing,"Type error at line %d: %s\n",t->lineno,message);
  Error = TRUE;
}



/* Procedure insertNode inserts 
 * identifiers stored in t into 
 * the symbol table 
 */
static void insertNode( TreeNode * t, char ** scope )
{ switch (t->nodekind)
  { case StmtK:
      switch (t->kind.stmt)
      { case VarK:
          if(t->type == VoidK){
            typeError(t,"Erro semantico. Variaveis do tipo void nao sao permitidas.");
          }
          if (st_lookup(t->attr.name, *scope, *scope) == 0){
            /* not yet in table, so treat as new definition */
            t->attr.scope = *scope;
            st_insert(t->attr.name,t->lineno,location++, t->type, *scope, *scope);
          }
          else
          /* already in table, so ignore location, 
             add line number of use only */ 
             typeError(t,"Erro semantico. Variavel ou funcao ja foi declarada.");
          break;
        case FunK:
          {
            if (st_lookup(t->attr.name, *scope, *scope) == 0){
              st_insert(t->attr.name,t->lineno,location++, t->type, *scope, *scope);
              if(strcmp(t->attr.name,"main") == 0){
                main_presence = 1;
              }
            }else{
             typeError(t,"Erro semantico. Nome ja foi declarada.");
            }

            //DEFINIE ESCOPO
            *scope = t->attr.name;
          }
          break;
        case CallK:
                if(!strcmp(t->attr.name, "output") || !strcmp(t->attr.name, "input")){
                  ExpType type = (!strcmp(t->attr.name, "output"))? VoidK:IntegerK;
                  st_insert(t->attr.name, t->lineno, location++, type, "global", "global");
                }else if(st_lookup(t->attr.name, *scope, "global") == 1){
                  st_insert(t->attr.name,t->lineno,location++, t->type, *scope, "global");
                }else{
                  typeError(t,"Erro semantico. Funcao nao foi declarada.");
                }
          break;
        default:
          break;
      }
      break;
    case ExpK:
      switch (t->kind.exp)
      { case IdK:
          if(st_lookup(t->attr.name, *scope, "global") == 1){
            st_insert(t->attr.name, t->lineno, location++, t->type, *scope, "global");
          }else{
            typeError(t,"Erro semantico TIPO 1. Variavel nao foi declarada.");
          }
          break;
        case VetK:
          st_insert(t->attr.name, t->lineno, location++, t->type, *scope, "global");
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}




/* Procedure checkNode performs
 * type checking at a single tree node
 */
static void checkNode(TreeNode * t)
{ switch (t->nodekind)
  { case ExpK:
      switch (t->kind.exp)
      { case OpK:
          if ((t->child[0]->type != IntegerK) ||
              (t->child[1]->type != IntegerK))
            typeError(t,"Op applied to non-integer");
          if ((t->attr.op == LET) || (t->attr.op == LT)
           || (t->attr.op == GT) || (t->attr.op == GET) 
           || (t->attr.op == COMP) || (t->attr.op == NEQ))
            t->type = BooleanK;
          else
            t->type = IntegerK;
          break;
        case ConstK:
        case IdK:
          t->type = IntegerK;
          break;
        default:
          break;
      }
      break;
    case StmtK:
      switch (t->kind.stmt)
      { case IfK:
          if (t->child[0]->type == IntegerK)
            typeError(t->child[0],"if test is not Boolean");
          break;
        case AssignK:
          if(t->child[1]->attr.name == "input" || t->child[1]->attr.name == "output"){
            break;
          }
          if((st_lookup(t->child[1]->attr.name, "global", "global")) && (st_lookup_type(t->child[1]->attr.name) == VoidK)){
            typeError(t->child[1],"Erro semantico. ASSIGN INVALIDO, funcao eh do tipo void");
          }
        default:
          break;
      }
      break;
    default:
      break;
  }
}

static void traverse_insert( TreeNode * t, char *scope){
  if (t != NULL){
    insertNode(t, &scope);
    { 
      int i;
      for (i=0; i < MAXCHILDREN; i++) traverse_insert(t->child[i], scope);
    }
    traverse_insert(t->sibling,scope);
  }
}

static void traverse_check( TreeNode * t){
  if(main_presence == 0){
    typeError(t,"Erro semantico, funcao main nao existe");
    return;
  }
  if (t != NULL){
    { 
      int i;
      for (i=0; i < MAXCHILDREN; i++) traverse_check(t->child[i]);
    }
    checkNode(t);
    traverse_check(t->sibling);
  }
}

/* Procedure typeCheck performs type checking 
 * by a postorder syntax tree traversal
 */
void typeCheck(TreeNode * syntaxTree){
  traverse_check(syntaxTree);
}

/* Function buildSymtab constructs the symbol 
 * table by preorder traversal of the syntax tree
 */
void buildSymtab(TreeNode * syntaxTree)
{ traverse_insert(syntaxTree, "global");
  if (TraceAnalyze)
  { fprintf(listing,"\nSymbol table:\n\n");
    printSymTab(listing);
  }
}

