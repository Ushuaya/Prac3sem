//
//  Semof.c
//  
//
//  Created by Ivan on 12.11.2020.
//


#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <sys/shm.h>

typedef int semaphore;

int key;
struct sembuf sem;

int main(int argc, char *argv[])
{
    //PART 1
    key=ftok("/Users/ivan/Desktop/C 3 semestr/Semaphore/Create", 0);
    printf("%d\n", key);
    
    
    if (fork() == 0)
    {
        execl("/Users/ivan/Desktop/C 3 semestr/Semaphore/Create", "Create", "key", NULL);
    }
    
    sleep(1);//This operatin made in order to wait while another programm will put value of key into common memory. Truly saying its illegal -- we must create a semaphore, but im too lazy...
    //creating a memory with the same key value as in the other programm
    int shmid = shmget(key, 4, 0666 | IPC_CREAT);
    //creating a pointer with the same key
    int *shmaddr = shmat(shmid, NULL, 0);
    
    //Here we equate the adress of semaphore we trasmitted from another programm
    int semid = *shmaddr;
    printf("2 %d\n", *shmaddr);
    //SEMAPHRE IS DONE!! KACHOW!!!
    
    
    
    //PART2
    int i = argv[1];//quantity of processes we what to create
    i = 10;
    
    
    semctl(semid, 0, SETVAL, (int) 1);
    while (i--)
    {
        if (fork() == 0)
            goto IMNEW;
    }
    goto IMFATHER;
IMNEW:
    
    
    sem.sem_num = 0;
    sem.sem_op = -1;
    sem.sem_flg = 0;
    semop(semid, &sem, 1);
    
    FILE *file1;
    if((file1 = fopen("SMTHNG.txt", "a+t")) == NULL)
    {
        printf ("Cannot open file.\n");
        exit(1);
    }
    int index = getpid();
    printf("pri: %d\n", index);
    //fwrite(&index, sizeof(int), 1, file1);
    fprintf(file1, "%4d", index);
    char c = ' ';
    //fseek (file1,0,SEEK_END);
    fwrite(&c, sizeof(char), 1, file1);
    fclose (file1);
    
    
    sem.sem_op = 1;
    semop(semid, &sem, 1);
    exit(0);
    
    
    
IMFATHER:
    /*
    i = 5;
    
    c = 'f';
    while (i--)
    {
        file1 = fopen("SMTHNG.txt", "a+t");
        //fseek (file1,0,SEEK_END);
        fwrite(&c, sizeof(char), 1, file1);
        fclose (file1);
    }
     */
    pause();

    
    return 0;

}


