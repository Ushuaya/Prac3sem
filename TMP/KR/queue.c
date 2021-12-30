//
//  message.c
//  
//
//  Created by Ivan on 14.11.2020.
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

int pid, pid1, pid2, pid3, pid4;
struct
{
    long mtype;
    int data;
} message;

struct sembuf sem;

void killing(int val)
    {
        if (getpid() == pid)
        {
            //printf("dfdf\n");
            //printf("%d\n", pid1);
            //if(pid1 == getpid())
            kill (pid1, SIGKILL);
            printf("%d\n", pid2);
            //if(pid2 == getpid())
            kill (pid2, SIGKILL);
            //printf("%d\n", pid3);
            //if(pid3 == getpid())
            kill (pid3, SIGKILL);
            //printf("%d\n", pid4);
            //if(pid4 == getpid())
            kill (pid4, SIGKILL);
            printf("Deleted\n");
            //printf("dfdfd\n");
        }

    }

int main(int argc, char *argv[])
{
    signal(SIGINT, killing);
    printf("%d\n", getpid());
    int FATHERPID = getpid();
    
    
    int key;
    key = ftok(argv[0], 0);
    int msgid = msgget (key, 0666 | IPC_CREAT | IPC_EXCL );//!!!!!
    
    printf("%d\n", msgid);
    int semid = semget (key, 2, 0666 | IPC_CREAT | IPC_EXCL);
    semctl(semid, 0, SETVAL, (int) 1);
    semctl(semid, 1, SETVAL, (int) 1);
    
    pid = getpid();
    
    
    if ((pid1 = fork()) == 0)
    {

        message.mtype = 'a';
        message.data = 0;
        msgsnd (msgid, (struct msgbuf* ) (&message), sizeof(int), 0);
        goto team1;
    }
    //printf("%d1\n", pid1);
    
    if ((pid2 = fork()) == 0)
    {
        goto team1;
    }
    //printf("%d2\n", pid2);
    
    if ((pid3 = fork()) == 0)
    {
        goto team2;
    }
    //printf("%d3\n", pid3);
    
    if ((pid4 = fork()) == 0)
    {
        goto team2;
    }
    //printf("%d4\n", pid4);
    goto IMFATHER;
    
    
    
team1:
    sem.sem_num = 0;
    for( ; ; )
    {
        sem.sem_op = -1;
        semop(semid, &sem, 1);
        msgrcv(msgid, (struct msgbuf* )(&message),sizeof(int) , 'b', 0);// == sizeof(int))
        
            printf ("%d: %d\n", getpid(), message.data);
        
        message.mtype = 'a';
        message.data++;

        msgsnd (msgid, (struct msgbuf* )(&message), sizeof(int), 0);        sleep(1);
        sem.sem_op = 1;
        semop(semid, &sem, 1);
    }

    
    
team2:
    sem.sem_num = 1;
    for( ;  ; )
    {
        sem.sem_op = -1;
        semop(semid, &sem, 1);
        message.mtype = 2;
        msgrcv(msgid, (struct msgbuf* )(&message), sizeof(int), 'a', 0);// == sizeof(int))
        
            printf ("%d: %d\n", getpid(), message.data);
        
        message.mtype = 'b';
        message.data++;

        msgsnd (msgid, (struct msgbuf* )(&message), sizeof(int), 0);        sleep(1);
        sem.sem_op = 1;
        semop(semid, &sem, 1);
    }

   
    
    
IMFATHER:

    pause();

    printf("IMHERE\n");
    msgctl(msgid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID, (int) 0);
    
    return 0;

}

