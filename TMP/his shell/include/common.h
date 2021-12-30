#ifndef _COMMON_H_INCLUDED
#define _COMMON_H_INCLUDED

#include <setjmp.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>
#include <errno.h>
#include <signal.h>

#define true 1
#define false 0
typedef int bool;

jmp_buf repeat_jmp_buf;

void error(const char *mes);

#endif // _COMMON_H_INCLUDED
