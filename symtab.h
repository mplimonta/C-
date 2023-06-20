/****************************************************/
/* File: symtab.h                                   */
/* Symbol table interface for the C- compiler       */
/****************************************************/

#ifndef _SYMTAB_H_
#define _SYMTAB_H_

void st_insert( char * name, int lineno, int loc, ExpType type, char* scope, char* scope_search, int len);


int st_lookup ( char * name, char* scope, char* scope_search);

ExpType st_lookup_type(char * name);


void printSymTab(FILE * listing);

#endif
