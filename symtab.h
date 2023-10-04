/****************************************************/
/* File: symtab.h                                   */
/* Symbol table interface for the C- compiler       */
/****************************************************/

#ifndef _SYMTAB_H_
#define _SYMTAB_H_

int hash(char* name, char * scope);

void st_insert( char * name, int lineno, int loc, ExpType type, char* scope, char* scope_search, int len);


int st_lookup ( char * name, char* scope, char* scope_search);

ExpType st_lookup_type(char * name);

BucketList* ret_hashtable();

int ret_Mloc(char* name, char* scope);

//char* ret_scope(char* name, char* scope);

void printSymTab(FILE * listing);

#endif
