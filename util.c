/****************************************************/
/* File: util.c                                     */
/* Utility function implementation                  */
/* for the C- compiler                              */
/****************************************************/

#include "globals.h"
#include "util.h"

/* Procedure printToken prints a token 
 * and its lexeme to the listing file
 */
void printToken( TokenType token, const char* tokenString )
{ switch (token)
  { case ELSE:
    case IF:
    case INT:
    case RETURN:
    case VOID:
    case WHILE:
      fprintf(listing,
         "Palavra reservada: %s\n",tokenString);
      break;
    case SOM: fprintf(listing,"+\n"); break;
    case SUB: fprintf(listing,"-\n"); break;
    case MULT: fprintf(listing,"*\n"); break;
    case DIV: fprintf(listing,"/\n"); break;
    case LT: fprintf(listing,"<\n"); break;
    case LET: fprintf(listing,"<=\n"); break;
    case GT: fprintf(listing,">\n"); break;
    case GET: fprintf(listing,">=\n"); break;
    case COMP: fprintf(listing,"==\n"); break;
    case NEQ: fprintf(listing,"!=\n"); break;
    case EQ: fprintf(listing,"=\n"); break;
    case PV: fprintf(listing,";\n"); break;
    case VIRG: fprintf(listing,",\n"); break;
    case APAREN: fprintf(listing,"(\n"); break;
    case FPAREN: fprintf(listing,")\n"); break;
    case ACOLCH: fprintf(listing,"[\n"); break;
    case FCOLCH: fprintf(listing,"]\n"); break;
    case ACHAVE: fprintf(listing,"{\n"); break;
    case FCHAVE: fprintf(listing,"}\n"); break;

    case NUM: fprintf(listing,"Num = %s\n",tokenString); break;
    case ID: fprintf(listing,"ID = %s\n",tokenString); break;
    case ERRO: fprintf(listing,"ERRO = %s\n",tokenString); break;
    case ENDFILE: fprintf(listing,"FIM = %s\n",tokenString); break;

    default: /* should never happen */
      fprintf(listing,"Unknown token: %d\n",token);
  }
}

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode * newStmtNode(StmtKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = StmtK;
    t->kind.stmt = kind;
    t->lineno = lineno;
  }
  return t;
}

/* Function newExpNode creates a new expression 
 * node for syntax tree construction
 */
TreeNode * newExpNode(ExpKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = ExpK;
    t->kind.exp = kind;
    t->lineno = lineno;
    t->type = VOID;
    t->attr.scope = "global";
    t->attr.name = "semnome";
  }
  return t;
}

/* Function copyString allocates and makes a new
 * copy of an existing string
 */
char * copyString(char * s)
{ int n;
  char * t;
  if (s==NULL) return NULL;
  n = strlen(s)+1;
  t = malloc(n);
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else strcpy(t,s);
  return t;
}

/* Variable indentno is used by printTree to
 * store current number of spaces to indent
 */
static int indentno = 0;

/* macros to increase/decrease indentation */
#define INDENT indentno+=2
#define UNINDENT indentno-=2

/* printSpaces indents by printing spaces */
static void printSpaces(void)
{ int i;
  for (i=0;i<indentno;i++)
    fprintf(listing," ");
}

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
void printTree( TreeNode * tree ){
  int i;
  INDENT;
  while (tree != NULL) {
    printSpaces();
    if (tree->nodekind==StmtK)
    { switch (tree->kind.stmt)
            {
            case IfK:
                fprintf(listing, "If\n");
                break;
            case AssignK:
                fprintf(listing, "Atribuicao\n");
                break;
            case WhileK:
                fprintf(listing, "While\n");
                break;
            case VarK:
                fprintf(listing, "Variavel %s\n", tree->attr.name);
                break;
            case FunK:
                fprintf(listing, "Funcao %s\n", tree->attr.name);
                break;
            case CallK:
                fprintf(listing, "Chamada de Funcao %s \n", tree->attr.name);
                break;
            case ReturnK:
                fprintf(listing, "Return\n");
                break;
            default:
                fprintf(listing, "No de Declaracao desconhecido\n");
                break;
            }
    }
    else if (tree->nodekind==ExpK)
    { switch (tree->kind.exp) {
        case OpK:
          fprintf(listing,"Op: ");
          printToken(tree->attr.op,"\0");
          break;
        case ConstK:
          fprintf(listing,"Const: %d\n",tree->attr.val);
          break;
        case IdK:
          fprintf(listing,"Id: %s\n",tree->attr.name);
          break;
        case VetK:
                fprintf(listing, "Vetor: %s\n", tree->attr.name);
                break;
        //case VetidK:
        //    fprintf(listing, "Indice [%d]\n", tree->attr.val);
        //    break;
        case TypeK:
            fprintf(listing, "Tipo %s\n", tree->attr.name);
            break;
        default:
          fprintf(listing,"No de expressao desconhecido.\n");
          break;
      }
    }
    else fprintf(listing,"No desconhcido.\n");
    for (i=0;i<MAXCHILDREN;i++)
         printTree(tree->child[i]);
    tree = tree->sibling;
  }
  UNINDENT;
}
