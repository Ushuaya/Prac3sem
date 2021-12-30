#include "../include/shell.h"

void child_wait(int code)
{
    wait(NULL);
}

void shell(void)
{
    setpgid(0, 0);
    signal(SIGINT, SIG_IGN);
    signal(SIGCHLD, child_wait);
    buffers.lexemes = NULL;
    buffers.exec_tree = NULL;
    zhead = NULL;
    zombiecount = 0;
    init_builtins();
	while (true)
	{
		setjmp(repeat_jmp_buf);
		delete_list(&buffers.lexemes);
		free_cmdinf(&buffers.exec_tree);
		printf("> ");
		buffers.lexemes = get_lexemes_list();
		buffers.exec_tree = build_exec_tree(buffers.lexemes);
		execute(buffers.exec_tree);
		kill_zombie();
	}
}
