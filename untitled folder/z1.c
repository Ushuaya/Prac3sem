//
//  z1.c
//  
//
//  Created by Ivan on 17.11.2020.
//

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int pid1 = fork();
    if(pid1 == 0)
    {
        int fd = open(argv[2], O_WRONLY);
        dup2(fd, 1);
        close(fd);
        execlp(argv[1], argv[1], NULL);
        exit(1);
    }
    
    
    int status;
    waitpid(pid1, &status, 0);

    if(!(WIFEXITED(status) && !WEXITSTATUS(status)) )
    {
        return 0;
    }

    
    int pfd[2];
    pipe(pfd);

    if(fork() == 0)
    {
        dup2(pfd[1], 1);
        close(pfd[0]);
        close(pfd[1]);
        execlp(argv[3], argv[3], NULL);
        exit(0);
    }

    if( fork() == 0 )
    {
        dup2(pfd[0], 0);
        close(pfd[0]);
        close(pfd[1]);
        execlp(argv[4], argv[4], NULL);
        exit(0);
    }
    close(pfd[0]);
    close(pfd[1]);

    int status_2, status_3;

    wait(&status_2);
    wait(&status_3);

    if(!(WIFEXITED(status_2) && !WEXITSTATUS(status_2)))
    {
        return 0;
    }

    if(!( WIFEXITED(status_3) && !WEXITSTATUS(status_3)))
    {
        return 0;
    }

    return 0;
}

