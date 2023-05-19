/****************************************************/
/* File: cgen.c                                     */
/* The code generator implementation                */
/* for the TINY compiler                            */
/* (generates code for the TM machine)              */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "symtab.h"
#include "code.h"
#include "cgen.h"

/* tmpOffset is the memory offset for temps
  It is decremented each time a temp is
  stored, and incremeted when loaded again
*/
static int tmpOffset = 0;

/* prototype for internal recursive code generator */
static void cGen (TreeNode * tree, StmtKind type);

int count = -1;

static int indexCounter(){
  count = ++count % 32;
  return count;
}

static int paramCounter(TreeNode * tree){
  TreeNode *t = tree->child[0];
  int counter = 0;
  while(t != NULL){
    t = t->sibling;
    counter++;
  }
  return counter;
}

/* Procedure genStmt generates code at a statement node */
static void genStmt(TreeNode * tree){
  switch (tree->kind.stmt) {
      case IfK :
         
        break;

      case FunK:{
        TreeNode *p1 = tree->child[0];
        //fprintf(code, "dxfg %s %s %d %d\n", p1->attr.name, p1->child[0]->attr.name, p1->kind.exp, p1->child[0]->kind.exp);
        fprintf(code, "\nFUNC, %s, %s -\n",tree->child[0]->attr.name, tree->attr.name);
        if(tree->child[0]->child[0] != NULL) cGen(tree->child[0], FunK);
        cGen(tree->child[1], -1);
        break;
      }
        

      case CallK:{
        cGen(tree->child[0], CallK);
        fprintf(code, "CALL, $t%d, %s, %d\n", indexCounter(), tree->attr.name, paramCounter(tree));

        break;

      }

      case VarK:
        fprintf(code, "ALLOC, %s, %s -\n", tree->attr.name, tree->attr.scope);

        break;
      case AssignK:{
        cGen(tree->child[1], -1);
        fprintf(code, "STORE, %s, $t%d -\n", tree->child[0]->attr.name, count);
        break;
      }
      default:
        break;
    }
} /* genStmt */

/* Procedure genExp generates code at an expression node */
static void genExp( TreeNode * tree){
  switch (tree->kind.exp) {
    case TypeK:

      cGen(tree->child[0], -1);
      break;

    case ConstK :

      break; /* ConstK */

    case IdK :
      fprintf(code, "LOAD, $t%d, %s -\n", indexCounter(), tree->attr.name);
      break; /* IdK */

    case OpK :

      break; /* OpK */
    case VetK :

      break;
    default:
      break;
  }
}
static void cGen(TreeNode * tree, StmtKind type){
   if (tree != NULL){
      switch (tree->nodekind) {
      case StmtK:
        genStmt(tree);
        break;
      case ExpK:
        if(type != FunK)genExp(tree);
        break;
      default:
        break;
    }
    if(type == CallK) fprintf(code, "PARAM, $t, -, -%d\n", count);
    if(type == FunK)
      fprintf(code, "ARG, %s, %s, %s\n", tree->attr.name, tree->child[0]->attr.name, tree->attr.scope);
    cGen(tree->sibling, type);
  }
}

void codeGen(TreeNode * syntaxTree){
    cGen(syntaxTree, -1);
}

/**********************************************/
/* the primary function of the code generator */
/**********************************************/
/* Procedure codeGen generates code to a code
 * file by traversal of the syntax tree. The
 * second parameter (codefile) is the file name
 * of the code file, and is used to print the
 * file name as a comment in the code file
 */