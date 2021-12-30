//
//  main.c
//  Task6
//
//  Created by Ivan on 03.11.2020.
//

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>

void handler(int sig) {
}

int main(int argc, char **argv) {
    struct sembuf sem;
    int semid, key;
    key=ftok(argv[0], 0);
    semid=semget(key, 2, IPC_CREAT|0666);
    semctl(semid, 0, SETVAL, (int) 1);
    semctl(semid, 1, SETVAL, (int) 0);
    signal(SIGINT, handler);
    sem.sem_flg=0;
    if (fork()==0) {
        signal(SIGINT, SIG_DFL);
        for (;;) {
            sem.sem_num=0;
            sem.sem_op=-1;
            semop(semid, &sem, 1);
            printf("Ping\n");
            sleep(1);
            sem.sem_num=1;
            sem.sem_op=1;
            semop(semid, &sem, 1);
        }
        exit(0);
    }
    if (fork()==0) {
        signal(SIGINT, SIG_DFL);
        for (;;) {
            sem.sem_num=1;
            sem.sem_op=-1;
            semop(semid, &sem, 1);
            printf("%d\n", semctl(semid, 0, GETVAL));
            printf("Pong\n");
            sleep(1);
            sem.sem_num=0;
            sem.sem_op=1;
            semop(semid, &sem, 1);
            printf("%d\n", semctl(semid, 0, GETVAL));
        }
        exit(0);
    }
    pause();
    semctl(semid, 0, IPC_RMID, (int) 0);
    return 0;
}
