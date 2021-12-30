#ifndef _BUILTINS_H_INCLUDED
#define _BUILTINS_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "common.h"

typedef struct _builtin_list_node_t
{
    char * name;
    void (*fptr)(int, char **);
    struct _builtin_list_node_t *next;
} builtin_list_node_t;

typedef struct _builtin_list_t
{
    builtin_list_node_t *begin, *end;
    size_t size;
} builtin_list_t;

builtin_list_t builtins;

void init_builtins(void);

int cd(int argc, char **argv);

#endif // _BUILTINS_H_INCLUDED
