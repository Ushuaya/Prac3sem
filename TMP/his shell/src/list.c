#include "../include/list.h"

void add_word(wlist_t *list, char *word)
{
	if (list->size == 0)     // empty list
		list->begin = list->end = malloc(sizeof(wlist_t));
	else
	{
		list->end->next = malloc(sizeof(wlist_t));
		list->end = list->end->next;
	}
	list->end->elem = word;
	list->end->next = NULL;
	list->size++;
}

void delete_list(wlist_t **list)
{
    if (*list == NULL)
        return;
	wlist_node_t *now = (*list)->begin, *next;
	while (now != NULL)
	{
		next = now->next;
		free(now->elem);
		free(now);
		now = next;
	}
	free(*list);
	*list = NULL;
}

void print_list(wlist_t *list)
{
	if (list->size == 0)
        printf("empty list\n");
	else
	{
		printf("list contains %zu elements\n", list->size);
	    wlist_node_t *ptr = list->begin;
		while (ptr != NULL)
		{
			printf("%s\n", ptr->elem);
			ptr = ptr->next;
		}
	}
	return;
}

void build_empty_list(wlist_t *list)
{
    list->begin = list->end = NULL;
    list->size = 0;
}
