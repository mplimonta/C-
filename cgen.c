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
int label = 0;

static void printOp( TokenType token, const char* tokenString )
{ switch (token){
    case SOM: fprintf(code,"SOM"); break;
    case SUB: fprintf(code,"SUB"); break;
    case MULT: fprintf(code,"MULT"); break;
    case DIV: fprintf(code,"DIV"); break;
    case LT: fprintf(code,"LT"); break;
    case LET: fprintf(code,"LET"); break;
    case GT: fprintf(code,"GT"); break;
    case GET: fprintf(code,"GET"); break;
    case COMP: fprintf(code,"COMP"); break;
    case NEQ: fprintf(code,"NEQ"); break;
    case EQ: fprintf(code,"EQ"); break;
    default: /* should never happen */
      fprintf(code,"Unknown token: %d",token);
  }
}

static int indexCounter(){
  count = ++count % 32;
  return count;
}
static int labelCounter(){
  label++;
  return label;
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
  int reg1, reg2, labelfalse, labelend, labelloop;
  switch (tree->kind.stmt) {
      case IfK :
        cGen(tree->child[0], -1);
        labelfalse = label;
        labelend = label + 1;        
        label += 2;
        fprintf(code, "(IFF, $t%d, L%d -)\n", count, labelfalse);
        cGen(tree->child[1], -1); 
        fprintf(code, "(GOTO, L%d, -, -)\n", labelend);
        fprintf(code, "(LAB, L%d, -, -)\n", labelfalse);
        cGen(tree->child[2], -1); 
        fprintf(code, "(GOTO, L%d, -, -)\n", labelend);
        fprintf(code, "(LAB, L%d, -, -)\n", labelend);
        break;
      case WhileK:
        labelloop = label;
        fprintf(code, "(LAB, L%d, -, -)\n", labelloop);
        cGen(tree->child[0], -1);
        labelend = label + 1;        
        label += 2;
        fprintf(code, "(WHILE, $t%d, L%d -)\n", count, labelend);
        cGen(tree->child[1], -1); 
        fprintf(code, "(GOTO, L%d, -, -)\n", labelloop);
        fprintf(code, "(LAB, L%d, -, -)\n", labelend);
        break;
      case ReturnK:
        cGen(tree->child[0], -1);
        fprintf(code, "(RET, $t%d, -, -)\n", count);
        break;

      case FunK:{
        TreeNode *p1 = tree->child[0];
        //fprintf(code, "dxfg %s %s %d %d\n", p1->attr.name, p1->child[0]->attr.name, p1->kind.exp, p1->child[0]->kind.exp);
        fprintf(code, "\n(FUNC, %s, %s, -)\n",tree->child[0]->attr.name, tree->attr.name);
        if(tree->child[0]->child[0] != NULL) cGen(tree->child[0], FunK);
        cGen(tree->child[1], -1);
        fprintf(code, "(END, %s, -, -)\n", tree->attr.name);
        break;
      }

      case CallK:{
        cGen(tree->child[0], CallK);
        fprintf(code, "(CALL, $t%d, %s, %d)\n", indexCounter(), tree->attr.name, paramCounter(tree));
        break;
      }

      case VarK:
        fprintf(code, "(ALLOC, %s, %s -)\n", tree->attr.name, tree->attr.scope);

        break;
      case AssignK:{
        cGen(tree->child[0], -1);
        cGen(tree->child[1], -1);
        reg2 = count;
        fprintf(code, "(STORE, %s, t%d, -)\n", tree->child[0]->attr.name, reg2);
        break;
      }
      default:
        break;
    }
} /* genStmt */

/* Procedure genExp generates code at an expression node */
static void genExp( TreeNode * tree){
  int reg1, reg2;
  char rg1[10], rg2[10];
  switch (tree->kind.exp) {
    case TypeK:

      cGen(tree->child[0], -1);
      break;

    case ConstK :
      fprintf(code, "(LOAD, $t%d, %d, -)\n", indexCounter(), tree->attr.val);
      break; /* ConstK */

    case IdK :
      fprintf(code, "(LOAD, $t%d, %s, -)\n", indexCounter(), tree->attr.name);
      break; /* IdK */
    case VetK :
      fprintf(code, "ARRAY\n");
      fprintf(code, "(LOAD, $t%d, %s, -)\n", indexCounter(), tree->attr.name);
      cGen(tree->child[0], -1);
      reg1 = count;
      fprintf(code, "(MULT, $t%d, $t%d, 4)\n", indexCounter(), reg1);
      reg2 = count;
      //fprintf(code, "(LOAD, $t%d, %s, -)\n", indexCounter(), tree->attr.name);

      fprintf(code, "FIM ARRAY\n");
      //, "(LOAD, $t%d, %s, -)\n", indexCounter(), tree->attr.name);
      break;

    case OpK :
      if(tree->child[0]->kind.exp == ConstK){
        sprintf(rg1, "%d", tree->child[0]->attr.val);
      }else{
        cGen(tree->child[0], -1);
        reg1 = count;
        sprintf(rg1, "$t%d", reg1);
      }
      if(tree->child[1]->kind.exp == ConstK){
        sprintf(rg2, "%d", tree->child[1]->attr.val);
      }else{
        cGen(tree->child[1], -1);
        reg2 = count;
        sprintf(rg2, "$t%d", reg2);
      }
      fprintf(code,"(");
      printOp(tree->attr.op, "");
      fprintf(code, ", $t%d, %s, %s)\n", indexCounter(), rg1, rg2);
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
    if(type == CallK) fprintf(code, "(PARAM, $t%d, -, -)\n", count);
    if(type == FunK){
      fprintf(code, "(ARG, %s, %s, %s)\n", tree->attr.name, tree->child[0]->attr.name, tree->attr.scope);
    }
    cGen(tree->sibling, type);
  }
}

void codeGen(TreeNode * syntaxTree){
    cGen(syntaxTree, -1);
}
