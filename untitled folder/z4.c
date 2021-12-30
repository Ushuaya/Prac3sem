//
//  z4.c
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


int key;
struct sembuf sem;

void Down(struct sembuf fsem)
{
    int fsemid=semget(key, 1, IPC_CREAT|0666);
    fsem.sem_num = 0;
    fsem.sem_op = -1;
    fsem.sem_flg = 0;
    semop(fsemid, &fsem, 1);
}

void Up(struct sembuf fsem)
{
    int ffsemid=semget(key, 1, IPC_CREAT|0666);
    fsem.sem_op = 1;
    semop(ffsemid, &fsem, 1);
    
}

int main(int argc, char *argv[])
{
    key=ftok(argv[0], 0);
    //printf("%d\n", key);
    
    int pid1;
    if ((pid1 = fork()) == 0)
    {
        execl("/Users/ivan/Desktop/C 3 semestr/untitled folder/z4a", "z4a", NULL);
    }
    
    int status;
    waitpid(pid1, &status, 0);
    
    
    int semid=semget(key, 1, IPC_CREAT|0666);
    
    //int i = argv[1];  //!!!!
    int i = 10;
    
    
    semctl(semid, 0, SETVAL, (int) 1);
    while (i--)
    {
        if (fork() == 0)
            goto IMNEW;
    }
    
    
    
    
    goto IMFATHER;
IMNEW:
    
    /*
    sem.sem_num = 0;
    sem.sem_op = -1;
    sem.sem_flg = 0;
    semop(semid, &sem, 1);
    */
    Down(sem);
    
    
    FILE *file1;
    if((file1 = fopen("Proc_ID.txt", "a+t")) == NULL)
    {
        printf ("Cannot open file.\n");
        exit(1);
    }
    int index = getpid();
    printf("proc: %d\n", index);
    fprintf(file1, "%4d", index);
    char c = ' ';
    fwrite(&c, sizeof(char), 1, file1);
    fclose (file1);
    
    /*
    sem.sem_op = 1;
    semop(semid, &sem, 1);
     */
    
    Up(sem);
    
    
    
    exit(0);
    
    
    
IMFATHER:
    for (int j = 0; j < 10; j ++)
        wait(NULL);
    int pidd;
    
    if ((pidd = fork()) == 0)
    {
        execl("/Users/ivan/Desktop/C 3 semestr/untitled folder/z4b", "z4b", NULL);
    }
    
    int statuss;
    waitpid(pid1, &statuss, 0);


    
    return 0;

}
