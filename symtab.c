/****************************************************/
/* File: symtab.c                                   */
/* Symbol table implementation for the C- compiler  */
/****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "symtab.h"


#define SIZE 211

#define SHIFT 4

int hash(char* name, char * scope)
{
  int temp = 0;
  int i = 0;
  while (scope[i] != '\0')
  { temp = ((temp << SHIFT) + scope[i]) % SIZE;
    ++i;
  }
  while (name[i] != '\0')
  { temp = ((temp << SHIFT) + name[i]) % SIZE;
    ++i;
  }
  return temp;
}
static BucketList hashTable[SIZE];


void st_insert( char * name, int lineno, int loc, ExpType type, char* scope, char* scope_search, int len){
  int h = hash(name, scope);
  BucketList l =  hashTable[h];

  while ((l != NULL) && (strcmp(name,l->name) != 0 ))
    l = l->next;
  if (l == NULL && strcmp(scope_search, "global") == 0){
    int h2 = hash(name, "global");
    BucketList l2 =  hashTable[h2];
    while ((l2 != NULL) && (strcmp(name,l2->name) != 0))
      l2 = l2->next;
    l = l2;
  }
  if (l == NULL) /* variable not yet in table */
  { BucketList new = (BucketList) malloc(sizeof(struct BucketListRec));
    new->name = name;
    new->lines = (LineList) malloc(sizeof(struct LineListRec));
    new->lines->lineno = lineno;
    new->memloc = loc;
    new->scope = scope;
    new->len = len;
    new->lines->next = NULL;
    new->type = type;
    new->next = hashTable[h];
    hashTable[h] = new; }
  else /* found in table, so just add line number */
  { LineList t = l->lines;
    while (t->next != NULL) t = t->next;
    t->next = (LineList) malloc(sizeof(struct LineListRec));
    t->next->lineno = lineno;
    t->next->next = NULL;
  }
} 

int st_lookup ( char * name, char* scope, char* scope_search){ 
  int h = hash(name, scope);
  BucketList l =  hashTable[h];
  while ((l != NULL) && (strcmp(name,l->name) != 0))
    l = l->next;
  if (l == NULL && strcmp(scope_search, "global") == 0){
    int h2 = hash(name, "global");
    BucketList l2 =  hashTable[h2];
    while ((l2 != NULL) && (strcmp(name,l2->name) != 0))
      l2 = l2->next;
    if(l2 == NULL) return 0;
  }else if(l == NULL && strcmp(scope_search, "global") != 0){
    return 0;
  }else return 1;
  return 1;
}
ExpType st_lookup_type(char * name){
  int h = hash(name, "global");
  BucketList l =  hashTable[h];
  while ((l != NULL) && (strcmp(name,l->name) != 0))
    l = l->next;
  return l->type;
}
BucketList* ret_hashtable(){
  return hashTable;
}

int ret_Mloc(char* name, char* scope){
  int h = hash(name, scope);
  BucketList l =  hashTable[h];
  while ((l != NULL) && (strcmp(name,l->name) != 0))
    l = l->next;
  return l->memloc;
}

// char* ret_scope(char* name, char* scope){
//   int h = hash(name, "global");
//   BucketList l =  hashTable[h];
//   while ((l != NULL) && (strcmp(name,l->name) != 0))
//     l = l->next;
//   return l->scope;
// }

void printSymTab(FILE * listing){
  int i;
  fprintf(table,"MLo|Type|Lenght|Name|Scope|LineNumbers\n");
  //fprintf(table,"---- ---- ------  ------       --------    ------------\n");
  for (i=0;i<SIZE;++i){
    if (hashTable[i] != NULL){
      BucketList l = hashTable[i];
      while (l != NULL){
        LineList t = l->lines;
        fprintf(table, "%d|", l->memloc);
        if(l->type == IntegerK) fprintf(table, "%s|", "int");
        if(l->type == VoidK) fprintf(table, "%s|", "void");
        fprintf(table,"%d|",l->len);
        fprintf(table,"%s|",l->name);
        fprintf(table,"%s|",l->scope);
        while (t != NULL){
          fprintf(table,"%d ",t->lineno);
          t = t->next;
        }
        fprintf(table,"\n");
        l = l->next;
      }
    }
  }
}