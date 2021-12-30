#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>
#include <stdint.h>
#include <time.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

void
kill_all_forks(pid_t *pids, int n)
{
    for(int i = 0;i<n;i++) {
        kill(pids[i], SIGKILL);
    }
}
int 
main(int count_arg, char **arg) 
{
    // int fd[2];
    // int tmp_fd[2];
    // int tmp_counter = 0;
    // pipe(tmp_fd);
    // pipe(fd);
    setbuf(stdout, NULL);
    pid_t *pids = calloc((count_arg - 1), sizeof(pid_t));

    int tmp_fd[2];
    //pipe(tmp_fd);

    int fd[2];
    fd[0] = 0;
    fd[1] = 0;

    int tmp_tmp[2];
    setbuf(stdin, NULL);

    for(int i = 1; i < count_arg;i++) {
        pids[i - 1] = fork();
        if(!pids[i-1]) {
            //setbuf(stdout, NULL);
            printf("SON %d %d\n", getpid(), i);
            fflush(stdout);
            _exit(0);
        } else {
            printf("PARENT %d %d\n", pids[i - 1], i);
        }
        //sleep(5);
        // pids[i - 1] = fork();
        // if(pids[i - 1] < 0) {
        //     kill_all_forks(pids, count_arg - 1);
        //     free(pids);
        //     return 1;
        // }
        

        // if(!pids[i - 1]) {
        //     printf("%d %s\n", i, arg[i]);
        //     if(i != 1) { // в этом случае ввод берем из fd
        //         printf("VVOD FROM FD[0] %s\n", arg[i]);
        //         dup2(fd[0], 0);
        //     }

        //     if(i != count_arg - 1) { // в этом случае вывод пишем в tmp_fd
        //         printf("VuVOD TO TMP_FD[1] %s\n", arg[i]);
        //         dup2(tmp_fd[1], 1);
        //     }
            
        //     close(fd[0]);
        //     close(fd[1]);
        //     close(tmp_fd[0]);
        //     close(tmp_fd[1]);
        //     execlp("/bin/sh", "sh", "-c", arg[i], NULL);
        //     //execlp(arg[i], arg[i], NULL);
        //     _exit(1);
        // }

        // close(fd[0]);
        // close(fd[1]); 

        // fd[0] = tmp_fd[0];
        // fd[1] = tmp_fd[1];
        // close(fd[0]);

        // pipe(tmp_tmp);
        // tmp_fd[0] = tmp_tmp[0];
        // tmp_fd[1] = tmp_tmp[1];
    }

    close(fd[0]);
    close(fd[1]);
    close(tmp_fd[0]);
    close(tmp_fd[1]);

    for(int i = 0;i < count_arg - 1;i++) {
        //waitpid(pids[i], NULL, 0);
        wait(NULL);
    }
    free(pids);

    return 0;
}
