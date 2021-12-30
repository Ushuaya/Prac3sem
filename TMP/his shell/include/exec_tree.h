#ifndef _EXEC_TREE_H_INCLUDED
#define _EXEC_TREE_H_INCLUDED

#include "list.h"

typedef struct _cmdinf_t
{
	int argc;
	char **argv;
	char *infile, *outfile;
	int append, background, stat;
	struct _cmdinf_t *psubcmd, *pipe, *next;
} cmdinf_t;

typedef struct _cmdinf_list_node_t
{
    struct _cmdinf_list_node_t *next, *prev;
    cmdinf_t *cmd;
} cmdinf_list_node_t;

typedef struct _cmdinf_list_t
{
    cmdinf_list_node_t *begin, *end;
} cmdinf_list_t;

cmdinf_t *build_exec_tree(wlist_t *lexemes);

void print_cmdinf(cmdinf_t *inf);

void free_cmdinf(cmdinf_t **cm);

#endif // _EXEC_TREE_H_INCLUDED
