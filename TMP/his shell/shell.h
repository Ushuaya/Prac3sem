#ifndef _SHELL_H_INCLUDED
#define _SHELL_H_INCLUDED

#include "list.h"
#include "exec_tree.h"
#include "lexemes.h"
#include "execute.h"
#include "builtins.h"

typedef struct _intermediate_results
{
    wlist_t *lexemes;
    cmdinf_t *exec_tree;
} intermediate_results;

intermediate_results buffers;

void shell(void);

#endif // _SHELL_H_INCLUDED
