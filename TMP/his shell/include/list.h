#ifndef _LIST_H_INCLUDED
#define _LIST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "common.h"

typedef struct _wlist_node_t
{
    char *elem;
    struct _wlist_node_t *next;
} wlist_node_t;

typedef struct _wlist_t
{
    wlist_node_t *begin, *end;
    size_t size;
} wlist_t;

void add_word(wlist_t *list, char *word);

void delete_list(wlist_t **list);

void print_list(wlist_t *list);

void build_empty_list(wlist_t *list);

#endif // _LIST_H_INCLUDED
