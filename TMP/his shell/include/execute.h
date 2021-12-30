#ifndef _EXECUTE_H_INCLUDED
#define _EXECUTE_H_INCLUDED

#include <string.h>

#include "common.h"
#include "builtins.h"
#include "exec_tree.h"
#include "shell.h"

typedef struct _zombie_t
{
	pid_t pid;
	struct _zombie_t *next;
} zombie_t;

zombie_t *zhead;
size_t zombiecount;

void execute(cmdinf_t *exec_tree);

void kill_zombie(void);

#endif // _EXECUTE_H_INCLUDED
