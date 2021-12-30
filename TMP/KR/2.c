#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>
//#include <sys/wait.h>

// pr1 -> задержка pr1 | (pr3 | pr4) -> задержка(pr3 или pr4) (pr1 | pr2)

int main()
{
    char buf[2];
    int a[2], b[2];
    pipe(a); // подача
    pipe(b); // отражение удара
    int pid1, pid2, pid3, pid4;
    printf("FATHER: pipes created...\n");
    pid1 = fork();
    if(pid1 == 0) // подача
    {

        sleep(1);
        write(a[1], "p", 2);
        read(b[0], buf, 2);
        printf("%s\n", buf);
    }
    if(((pid3 = fork()) == 0) && ((pid4 == fork()) == 0))
    {
        for(;;)
        {
            sleep(1);
            read(a[0], buf, 2);
            printf("%s\n", buf);
            write(b[1], "b", 2);
        }
    }
    if(((pid1 = fork()) == 0) && ((pid2 == fork()) == 0))
    {
        for(;;)
        {
            sleep(1);
            write(a[1], "a", 2);
            read(b[0], buf, 2);
            printf("%s\n", buf);
        }
    }
    printf("\n FATHER DIED ...\n");
    return 0;
}

