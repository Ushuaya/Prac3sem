//
//  bingostar.c
//  
//
//  Created by Ivan on 28.11.2020.
//

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>

int main()
{
    char* p = "akjnkjnknjj";

    int * d;
    //printf("%d\n", strcmp(p, "asdsa"));
    printf("%d :: %d\n", sizeof(p), sizeof(*p) );

    *d = 6;
    printf("%d\n", sizeof(d));

}
