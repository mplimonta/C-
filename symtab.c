/****************************************************/
/* File: symtab.c                                   */
/* Symbol table implementation for the TINY compiler*/
/* (allows only one symbol table)                   */
/* Symbol table is implemented as a chained         */
/* hash table                                       */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

/* SIZE is the size of the hash table */
#define SIZE 211

/* SHIFT is the power of two used as multiplier
   in hash function  */
#define SHIFT 4

/* the hash function */
static int hash (char* name, char * scope)
{ int temp = 0;
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

/* the list of line numbers of the source 
 * code in which a variable is referenced
 */
typedef struct LineListRec
   { int lineno;
     struct LineListRec * next;
   } * LineList;

/* The record in the bucket lists for
 * each variable, including name, 
 * assigned memory location, and
 * the list of line numbers in which
 * it appears in the source code
 */
typedef struct BucketListRec
   { char * name;
     LineList lines;
     int memloc ; /* memory location for variable */
     struct BucketListRec * next;
     char* scope;

   } * BucketList;

/* the hash table */
static BucketList hashTable[SIZE];

/* Procedure st_insert inserts line numbers and
 * memory locations into the symbol table
 * loc = memory location is inserted only the
 * first time, otherwise ignored
 */
void st_insert( char * name, int lineno, int loc, char* scope, char* scope_search){
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
    new->lines->next = NULL;
    new->next = hashTable[h];
    hashTable[h] = new; }
  else /* found in table, so just add line number */
  { LineList t = l->lines;
    while (t->next != NULL) t = t->next;
    t->next = (LineList) malloc(sizeof(struct LineListRec));
    t->next->lineno = lineno;
    t->next->next = NULL;
  }
} /* st_insert */

/* Function st_lookup returns the memory 
 * location of a variable or -1 if not found
 */
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

/* Procedure printSymTab prints a formatted 
 * listing of the symbol table contents 
 * to the listing file
 */
void printSymTab(FILE * listing)
{ int i;
  fprintf(listing,"Variable Name   Scope     Line Numbers\n");
  fprintf(listing,"-------------  --------   ------------\n");
  for (i=0;i<SIZE;++i)
  { if (hashTable[i] != NULL)
    { BucketList l = hashTable[i];
      while (l != NULL)
      { LineList t = l->lines;
        fprintf(listing,"%-14s ",l->name);
        fprintf(listing,"%-8s  ",l->scope);
        while (t != NULL)
        { fprintf(listing,"%4d ",t->lineno);
          t = t->next;
        }
        fprintf(listing,"\n");
        l = l->next;
      }
    }
  }
} /* printSymTab */
