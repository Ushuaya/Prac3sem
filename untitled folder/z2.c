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

int pid1, pid2, pid3, pid4, fpid;

struct
{
    long mtype;
    int Data;
} Message;



void kill_proc(int val)
    {
        //printf("frfr\n");
        //printf ("%d %d\n", fpid, getpid());
        if (getpid() == fpid)
        {
            //printf ("HELLO\n");
            kill (pid1, SIGKILL);

            kill (pid2, SIGKILL);

            kill (pid3, SIGKILL);
 
            kill (pid4, SIGKILL);
            //printf("Eleminated\n");

        }

    }

int main(int argc, char *argv[])
{
    
    int key = ftok(argv[0], 0);
    int msgid = msgget (key, 0666| IPC_CREAT | IPC_EXCL );
    printf("%d\n", msgid);
    
    fpid = getpid();
    //printf ("%d\n", fpid);
    
    signal(SIGINT, kill_proc);
    
    
    if ((pid1 = fork()) == 0)
    {
        Message.mtype = 'a';
        Message.Data = 0;
        msgsnd (msgid, (struct msgbuf* ) (&Message), sizeof(int), 0);
        goto _1;
    }
    
    if ((pid2 = fork()) == 0)
    {
        goto _1;
    }
    
    
    if ((pid3 = fork()) == 0)
    {
        goto _2;
    }
    
    if ((pid4 = fork()) == 0)
    {
        goto _2;
    }
    
    goto FATHER;
    
    
    _1:
    for(;;)
    {
        msgrcv(msgid, (struct msgbuf* )(&Message),sizeof(int) , 'b', 0);// == sizeof(int))
        
            printf ("%d: %d\n", getpid(), Message.Data);
        
        Message.mtype = 'a';
        Message.Data++;

        msgsnd (msgid, (struct msgbuf* )(&Message), sizeof(int), 0);        sleep(1);
    }
    
    
    _2:
    for(;;)
    {
        msgrcv(msgid, (struct msgbuf* )(&Message), sizeof(int), 'a', 0);// == sizeof(int))
        
            printf ("%d: %d\n", getpid(), Message.Data);
        
        Message.mtype = 'b';
        Message.Data++;

        msgsnd (msgid, (struct msgbuf* )(&Message), sizeof(int), 0);        sleep(1);
    }
    
FATHER:
    pause();
    
    //printf ("IMHERE\n");
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
    
    
}
