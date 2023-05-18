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
static void cGen (TreeNode * tree);

/* Procedure genStmt generates code at a statement node */
static void genStmt(TreeNode * tree){ 
  switch (tree->kind.stmt) {
      case IfK :
         
        break; /* if_k */

      case FunK:
        printf("%s ", tree->attr.name);
        break; /* repeat */

      case CallK:
         
        break; /* assign_k */

      case VarK:

        break;
      case AssignK:

        break;
      default:
        break;
    }
} /* genStmt */

/* Procedure genExp generates code at an expression node */
static void genExp( TreeNode * tree){
  fprintf(code,"%d ", tree->child[0]->kind.stmt);
  //fprintf(code,"%s ", tree->child[1]->attr.name);
  //fprintf(code,"%s ", tree->child[2]->attr.name);
  switch (tree->kind.exp) {

    case TypeK:
      if(tree->child[0]->kind.stmt == FunK) fprintf(code, "FUNC");
      cGen(tree->child[0]);
      break;

    case ConstK :
      
      break; /* ConstK */
    
    case IdK :

      break; /* IdK */

    case OpK :

      break; /* OpK */
    case VetK :

      break;
    default:
      break;
  }
}
static void cGen(TreeNode * tree){
   if (tree != NULL){
      switch (tree->nodekind) {
      case StmtK:
        genStmt(tree);
        break;
      case ExpK:
        genExp(tree);
        break;
      default:
        break;
    }
    cGen(tree->sibling);
  }
}
void codeGen(TreeNode * syntaxTree){
    cGen(syntaxTree);
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