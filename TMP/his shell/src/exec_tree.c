#include "../include/exec_tree.h"

#include <string.h>

cmdinf_list_t *cmd_list;

bool is_ordinar_lexeme(wlist_node_t *lexeme)
{
	return (lexeme != NULL && strstr("| || & && ; ( ) < > >>", lexeme->elem) == NULL);
}

// ---------- cmdinf functions ----------

void free_cmdinf(cmdinf_t **cm)
{
    if (*cm == NULL)
        return;
    free_cmdinf(&((*cm)->next));
    free_cmdinf(&((*cm)->pipe));
    free_cmdinf(&((*cm)->psubcmd));
    free((*cm)->infile);
    free((*cm)->outfile);
    while ((*cm)->argc--)
        free((*cm)->argv[(*cm)->argc]);
    free((*cm)->argv);
    free(*cm);
    *cm = NULL;
}

void empty_cmdinf(cmdinf_t *cm)
{
    cm->argv = NULL;
    cm->argc = 0;
    cm->infile = NULL;
    cm->outfile = NULL;
}

// -------- cmdinf list functions -------

void push_cmdinf(cmdinf_t *ptr)
{
    if (cmd_list->begin == NULL)
    {
        cmd_list->begin = cmd_list->end = malloc(sizeof(cmdinf_list_node_t));
        cmd_list->begin->prev = NULL;
    }
    else
    {
        cmd_list->end->next = malloc(sizeof(cmdinf_list_node_t));
        cmd_list->end->next->prev = cmd_list->end;
        cmd_list->end = cmd_list->end->next;
    }
    cmd_list->end->cmd = ptr;
    cmd_list->end->next = NULL;
}

void pop_cmdinf()
{
    if (cmd_list->end == NULL)
    {
        fprintf(stderr, "cmdinf_list error: pop from empty stack\n");
        return;
    }
    if (cmd_list->end->prev != NULL)
    {
        cmd_list->end = cmd_list->end->prev;
        free(cmd_list->end->next);
        cmd_list->end->next = NULL;
    }
    else
    {
        free(cmd_list->begin);
        cmd_list->begin = cmd_list->end = NULL;
    }
}

void free_cmdinf_list()
{
    cmdinf_list_node_t *it = cmd_list->begin;
    free(cmd_list);
    while (it != NULL)
    {
        free_cmdinf(&(it->cmd));
        cmdinf_list_node_t *temp = it;
        it = it->next;
        free(temp);
    }
}

// --------------------------------------

void syntax_error(void)
{
    free_cmdinf_list();
    error("invalid syntax");
}

cmdinf_t *simple_command(wlist_node_t **cur_lexeme)     // really simple
{
    wlist_node_t *lexeme = *cur_lexeme;
	cmdinf_t *cm = malloc(sizeof(cmdinf_t));            // final command
	push_cmdinf(cm);
	empty_cmdinf(cm);
	cm->argc = 1;
	cm->argv = malloc(sizeof(char*));
	cm->argv[0] = malloc((strlen(lexeme->elem) + 1) * sizeof(char));
	cm->psubcmd = cm->next = cm->pipe = NULL;
	strcpy(cm->argv[0], lexeme->elem);
	lexeme = lexeme->next;
	while (lexeme != NULL && strstr("| || ; & && ( )", lexeme->elem) == NULL)
	{
	    if (!is_ordinar_lexeme(lexeme) && (!is_ordinar_lexeme(lexeme->next) || lexeme->next == NULL))
            syntax_error();
		if (!strcmp(lexeme->elem, ">"))             // output redirection
		{
			lexeme = lexeme->next;
            if (cm->outfile != NULL)
                free(cm->outfile);
            cm->outfile = malloc((strlen(lexeme->elem) + 1) * sizeof(char));
            strcpy(cm->outfile, lexeme->elem);
            cm->append = 0;
		}
		else if (!strcmp(lexeme->elem, ">>"))       // output redirection in appending mode
		{
			lexeme = lexeme->next;
            if (cm->outfile != NULL)
                free(cm->outfile);
            cm->outfile = malloc((strlen(lexeme->elem) + 1) * sizeof(char));
            strcpy(cm->outfile, lexeme->elem);
            cm->append = 1;
		}
		else if (!strcmp(lexeme->elem, "<"))        // input redirection
		{
			lexeme = lexeme->next;
            if (cm->infile != NULL)
                free(cm->infile);
            cm->infile = malloc((strlen(lexeme->elem) + 1) * sizeof(char));
            strcpy(cm->infile, lexeme->elem);
		}
		else                                        //flag or argument
		{
			cm->argc++;
			cm->argv = realloc(cm->argv, cm->argc * (sizeof(char *)));
			cm->argv[cm->argc - 1] = malloc((strlen(lexeme->elem) + 1) * sizeof(char));
			strcpy(cm->argv[cm->argc - 1], lexeme->elem);
		}
		lexeme = lexeme->next;
	}
	cm->argv = realloc(cm->argv, (cm->argc + 1) * sizeof(char *));
	cm->argv[cm->argc] = NULL;
	*cur_lexeme = lexeme;
	pop_cmdinf();
	return cm;
}

cmdinf_t *set_of_commands(wlist_node_t **cur_lexeme);

cmdinf_t *command(wlist_node_t **cur_lexeme)    // we threat (...) as a command, but the ... part may be complex
{
    wlist_node_t *lexeme = *cur_lexeme;
	cmdinf_t *temp = NULL;
	if (!strcmp(lexeme->elem, "("))
	{
		lexeme = lexeme->next;
		temp = malloc(sizeof(cmdinf_t));
		push_cmdinf(temp);
		empty_cmdinf(temp);
		*cur_lexeme = lexeme;
		temp->psubcmd = set_of_commands(cur_lexeme);    // processing the ... part in the set_of_commands()
		lexeme = *cur_lexeme;
		if (lexeme == NULL || strcmp(lexeme->elem, ")"))    // no closing parenthesis
            syntax_error();
		lexeme = lexeme->next;
		while (lexeme != NULL && strstr("| || ; & && ( )", lexeme->elem) == NULL)
		{
			if (!strcmp(lexeme->elem, ">"))             // output redirection
            {
                lexeme = lexeme->next;
                if (temp->outfile != NULL)
                    free(temp->outfile);
                temp->outfile = malloc(sizeof(*(lexeme->elem)));
                strcpy(temp->outfile, lexeme->elem);
                temp->append = 0;
            }
            else if (!strcmp(lexeme->elem, ">>"))       // output redirection in appending mode
            {
                lexeme = lexeme->next;
                if (temp->outfile != NULL)
                    free(temp->outfile);
                temp->outfile = malloc(sizeof(*(lexeme->elem)));
                strcpy(temp->outfile, lexeme->elem);
                temp->append = 1;
            }
            else if (!strcmp(lexeme->elem, "<"))        // input redirection
            {
                lexeme = lexeme->next;
                if (temp->infile != NULL)
                    free(temp->infile);
                temp->infile = malloc(sizeof(*(lexeme->elem)));
                strcpy(temp->infile, lexeme->elem);
            }
			else
                syntax_error();
		}
		*cur_lexeme = lexeme;
        pop_cmdinf();
	}
	else if (is_ordinar_lexeme(*cur_lexeme))
        temp = simple_command(cur_lexeme);
	else
        syntax_error();
	return temp;
}

cmdinf_t *_pipe(wlist_node_t **cur_lexeme)
{
	cmdinf_t *first;
	cmdinf_t *last;
	first = last = command(cur_lexeme);
	push_cmdinf(first);
	while(*cur_lexeme != NULL && !strcmp((*cur_lexeme)->elem, "|"))
	{
		*cur_lexeme = (*cur_lexeme)->next;
		if (*cur_lexeme != NULL)
		{
			last->pipe = command(cur_lexeme);
			last = last->pipe;
		}
		else    // no command after |
            syntax_error();
	}
	last->pipe = NULL;
	if (*cur_lexeme != NULL && !(strcmp((*cur_lexeme)->elem, "&")))
        first->background = 1;//background mode
	else
        first->background = 0;
    pop_cmdinf();
	return first;
}

cmdinf_t *set_of_commands(wlist_node_t **cur_lexeme)
{
	cmdinf_t *first;
	cmdinf_t *last;
	first = last = _pipe(cur_lexeme);
	push_cmdinf(first);
	first->stat = 0;
	while (*cur_lexeme != NULL && strstr("; & || &&", (*cur_lexeme)->elem) != NULL)
	{
		int stat;
		if (!strcmp((*cur_lexeme)->elem, "||"))
		{
			if ((*cur_lexeme)->next == NULL)
                syntax_error();
			else
                stat = 1;
		}
		else if (!strcmp((*cur_lexeme)->elem, "&&"))
		{
			if ((*cur_lexeme)->next == NULL)
                syntax_error();
			else
                stat = 2;
		}
		else
            stat = 0;
		*cur_lexeme = (*cur_lexeme)->next;
		if (*cur_lexeme != NULL && strcmp((*cur_lexeme)->elem, ")"))
		{
			last->next = _pipe(cur_lexeme);
			last = last->next;
			last->stat = stat;
		}
	}
	last->next = NULL;
	pop_cmdinf();
	return first;
}

cmdinf_t *build_exec_tree(wlist_t *lexemes)
{
    if (lexemes == NULL)
        return NULL;
    cmd_list = malloc(sizeof(cmdinf_list_t));
    cmd_list->begin = cmd_list->end = NULL;
    wlist_node_t *cur_lexeme = lexemes->begin;
	if (lexemes->size == 0)
        longjmp(repeat_jmp_buf, 1);
	cmdinf_t *cmd = set_of_commands(&cur_lexeme);
	push_cmdinf(cmd);
	if (cur_lexeme != NULL)
        syntax_error();
    pop_cmdinf();
    free_cmdinf_list();
    return cmd;
}

void print_cmdinf(cmdinf_t *inf)
{
    if (inf == NULL)
        return;
	printf("=====\n");
	while (inf != NULL)
	{
		cmdinf_t *t = inf;
		while (t != NULL)
		{
            int i;
			if (t->argv != NULL)
                for (i = 0; i < t->argc; ++i)
                    printf("%s ", t->argv[i]);
			else
			{
				cmdinf_t *b = t->psubcmd;
				print_cmdinf(b);
			}
			t = t->pipe;
			if (t)
                printf("\n--- pipe ---\n");
		}
		printf("\n");
		inf = inf->next;
	}
	printf("===== ");
}
