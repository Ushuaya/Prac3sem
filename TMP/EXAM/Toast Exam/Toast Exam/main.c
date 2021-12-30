//
//  main.c
//  Toast Exam
//
//  Created by Ivan on 25.12.2020.
//


#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX_CNT 100
int target_pid, cnt; int fd[2];
int status;
void SigHndlr(int s)
{
     /* в обработчике сигнала происходит и чтение, и запись */
     signal(SIGUSR1, SigHndlr);
    if(cnt < MAX_CNT)
    {
        read(fd[0], &cnt, sizeof(int));
        printf("%d\n", cnt);
        cnt++;
        write(fd[1], &cnt, sizeof(int));
        /* посылаем сигнал второму: пора читать из канала */
        kill(target_pid, SIGUSR1);
    }
    else if(target_pid == getppid())
    {
          /* условие окончания игры проверяется потомком */
          printf("Child is going to be terminated\n");
          //close(fd[1]);
          //close(fd[0]);
          /* завершается потомок */
        exit(0);
    }
    else
        kill(target_pid, SIGUSR1);
}


int main(int argc, char **argv)
{
     /* организация канала */
     pipe(fd);
     /* установка обработчика сигнала для обоих процессов*/
     signal(SIGUSR1, SigHndlr);
    cnt = 0;
        
    if((target_pid = fork()) != 0)
    {
          /* Предку остается только ждать завершения
          потомка */
          wait(&status);
          printf("Parent is going to be terminated\n");
          //close(fd[1]);
          //close(fd[0]);
        return 0;
    }
    else
    {
        target_pid = getppid();
        /* потомок начинает пинг-понг */
        write(fd[1], &cnt, sizeof(int));
        kill(target_pid, SIGUSR1);
        for(;;); /* бесконечный цикл */
    }
}

