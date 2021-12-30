#include "../include/common.h"

void error(const char *mes)
{
	printf("%s\n", mes);
	longjmp(repeat_jmp_buf, 1);
}
