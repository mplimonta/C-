static void genExp( TreeNode * tree){
  int reg1, reg2;
  switch (tree->kind.exp) {
    case TypeK:

      cGen(tree->child[0], -1);
      break;

    case ConstK :
      fprintf(code, ", %d", tree->attr.val);
      break; /* ConstK */

    case IdK :
      fprintf(code, "(LOAD, $t%d, %s -)\n", indexCounter(), tree->attr.name);
      break; /* IdK */
    case VetK :

      break;

    case OpK :
      switch(tree->attr.op){
        case LET:
          if(tree->child[0]->kind.exp == IdK && tree->child[1]->kind.exp == IdK){
              cGen(tree->child[0], -1);
              cGen(tree->child[1], -1);
              fprintf(code, "(LET, $t%d, $t%d, $t%d)\n", indexCounter(), count, count-1); 
            }else
            if(tree->child[0]->kind.exp == ConstK && tree->child[1]->kind.exp == IdK){
              cGen(tree->child[1], -1);
              fprintf(code, "(LET, $t%d", indexCounter());
              cGen(tree->child[0], -1);
              fprintf(code, ", $t%d", count-1);
              fprintf(code, ")\n");
            }else
            if(tree->child[0]->kind.exp == IdK && tree->child[1]->kind.exp == ConstK){
              cGen(tree->child[0], -1);
              fprintf(code, "(LET, $t%d", indexCounter());
              fprintf(code, ", $t%d", count-1);
              cGen(tree->child[1], -1);
              fprintf(code, ")\n");
            }else
            if(tree->child[0]->kind.exp == ConstK && tree->child[1]->kind.exp == ConstK){
              fprintf(code, "(LET, $t%d", indexCounter());
              cGen(tree->child[0], -1);
              cGen(tree->child[1], -1);
              fprintf(code, ")\n");
            }
          break;
        case LT:
          if(tree->child[0]->kind.exp == IdK && tree->child[1]->kind.exp == IdK){
              cGen(tree->child[0], -1);
              cGen(tree->child[1], -1);
              fprintf(code, "(LT, $t%d, $t%d, $t%d)\n", indexCounter(), count, count-1); 
            }else
            if(tree->child[0]->kind.exp == ConstK && tree->child[1]->kind.exp == IdK){
              cGen(tree->child[1], -1);
              fprintf(code, "(LT, $t%d", indexCounter());
              cGen(tree->child[0], -1);
              fprintf(code, ", $t%d", count-1);
              fprintf(code, ")\n");
            }else
            if(tree->child[0]->kind.exp == IdK && tree->child[1]->kind.exp == ConstK){
              cGen(tree->child[0], -1);
              fprintf(code, "(LT, $t%d", indexCounter());
              fprintf(code, ", $t%d", count-1);
              cGen(tree->child[1], -1);
              fprintf(code, ")\n");
            }else
            if(tree->child[0]->kind.exp == ConstK && tree->child[1]->kind.exp == ConstK){
              fprintf(code, "(LT, $t%d", indexCounter());
              cGen(tree->child[0], -1);
              cGen(tree->child[1], -1);
              fprintf(code, ")\n");
            }
          break;
        case GT:
          if(tree->child[0]->kind.exp == IdK && tree->child[1]->kind.exp == IdK){
              cGen(tree->child[0], -1);
              cGen(tree->child[1], -1);
              fprintf(code, "(GT, $t%d, $t%d, $t%d)\n", indexCounter(), count, count-1); 
            }else
            if(tree->child[0]->kind.exp == ConstK && tree->child[1]->kind.exp == IdK){
              cGen(tree->child[1], -1);
              fprintf(code, "(GT, $t%d", indexCounter());
              cGen(tree->child[0], -1);
              fprintf(code, ", $t%d", count-1);
              fprintf(code, ")\n");
            }else
            if(tree->child[0]->kind.exp == IdK && tree->child[1]->kind.exp == ConstK){
              cGen(tree->child[0], -1);
              fprintf(code, "(GT, $t%d", indexCounter());
              fprintf(code, ", $t%d", count-1);
              cGen(tree->child[1], -1);
              fprintf(code, ")\n");
            }else
            if(tree->child[0]->kind.exp == ConstK && tree->child[1]->kind.exp == ConstK){
              fprintf(code, "(GT, $t%d", indexCounter());
              cGen(tree->child[0], -1);
              cGen(tree->child[1], -1);
              fprintf(code, ")\n");
            }
          break;
        case GET:
          if(tree->child[0]->kind.exp == IdK && tree->child[1]->kind.exp == IdK){
              cGen(tree->child[0], -1);
              cGen(tree->child[1], -1);
              fprintf(code, "(GET, $t%d, $t%d, $t%d)\n", indexCounter(), count, count-1); 
            }else
            if(tree->child[0]->kind.exp == ConstK && tree->child[1]->kind.exp == IdK){
              cGen(tree->child[1], -1);
              fprintf(code, "(GET, $t%d", indexCounter());
              cGen(tree->child[0], -1);
              fprintf(code, ", $t%d", count-1);
              fprintf(code, ")\n");
            }else
            if(tree->child[0]->kind.exp == IdK && tree->child[1]->kind.exp == ConstK){
              cGen(tree->child[0], -1);
              fprintf(code, "(GET, $t%d", indexCounter());
              fprintf(code, ", $t%d", count-1);
              cGen(tree->child[1], -1);
              fprintf(code, ")\n");
            }else
            if(tree->child[0]->kind.exp == ConstK && tree->child[1]->kind.exp == ConstK){
              fprintf(code, "(GET, $t%d", indexCounter());
              cGen(tree->child[0], -1);
              cGen(tree->child[1], -1);
              fprintf(code, ")\n");
            }
          break;
        case COMP:
            if(tree->child[0]->kind.exp == IdK && tree->child[1]->kind.exp == IdK){
              cGen(tree->child[0], -1);
              cGen(tree->child[1], -1);
              fprintf(code, "(EQUAL, $t%d, $t%d, $t%d)\n", indexCounter(), count, count - 1); 
            }else
            if(tree->child[0]->kind.exp == ConstK && tree->child[1]->kind.exp == IdK){
              cGen(tree->child[1], -1);
              fprintf(code, "(EQUAL, $t%d", indexCounter());
              cGen(tree->child[0], -1);
              fprintf(code, ", $t%d", count-1);
              fprintf(code, ")\n");
            }else
            if(tree->child[0]->kind.exp == IdK && tree->child[1]->kind.exp == ConstK){
              cGen(tree->child[0], -1);
              fprintf(code, "(EQUAL, $t%d", indexCounter());
              fprintf(code, ", $t%d", count-1);
              cGen(tree->child[1], -1);
              fprintf(code, ")\n");
            }else
            if(tree->child[0]->kind.exp == ConstK && tree->child[1]->kind.exp == ConstK){
              fprintf(code, "(EQUAL, $t%d", indexCounter());
              cGen(tree->child[0], -1);
              cGen(tree->child[1], -1);
              fprintf(code, ")\n");
            }
            
            // IdK OpK
            // OpK IdK
            // ConstK OpK
            // OpK ConstK
            // OpK OpK
          break;
        case NEQ:
          if(tree->child[0]->kind.exp == IdK && tree->child[1]->kind.exp == IdK){
              cGen(tree->child[0], -1);
              cGen(tree->child[1], -1);
              fprintf(code, "(NEQ, $t%d, $t%d, $t%d)\n", indexCounter(), count, count-1); 
            }else
            if(tree->child[0]->kind.exp == ConstK && tree->child[1]->kind.exp == IdK){
              cGen(tree->child[1], -1);
              fprintf(code, "(NEQ, $t%d", indexCounter());
              cGen(tree->child[0], -1);
              fprintf(code, ", $t%d", count-1);
              fprintf(code, ")\n");
            }else
            if(tree->child[0]->kind.exp == IdK && tree->child[1]->kind.exp == ConstK){
              cGen(tree->child[0], -1);
              fprintf(code, "(NEQ, $t%d", indexCounter());
              fprintf(code, ", $t%d", count-1);
              cGen(tree->child[1], -1);
              fprintf(code, ")\n");
            }else
            if(tree->child[0]->kind.exp == ConstK && tree->child[1]->kind.exp == ConstK){
              fprintf(code, "(NEQ, $t%d", indexCounter());
              cGen(tree->child[0], -1);
              cGen(tree->child[1], -1);
              fprintf(code, ")\n");
            }
          break;
        case SOM:
          cGen(tree->child[0], -1);
          cGen(tree->child[1], -1);
          break;
        case SUB:
          cGen(tree->child[0], -1);
          cGen(tree->child[1], -1);
          break;
        case MULT:
          cGen(tree->child[0], -1);
          cGen(tree->child[1], -1);
          break;
        case DIV:
          cGen(tree->child[0], -1);
          cGen(tree->child[1], -1);
          break;
      }
      //OpK
      break;
    default:
      break;
  }
}