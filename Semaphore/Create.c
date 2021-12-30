//
//  Create.c
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

//typedef int semaphore;

int i, tmp_num;

int main(int argc, char *argv[])
{
    
    //printf("%s\n", argv[1]);
    int key=ftok("/Users/ivan/Desktop/C 3 semestr/Semaphore/Create", 0);
    printf("%d\n", key);
    
    //Creating of common memory
    //Here we are creating an addres of this memory
    int shmid = shmget(key, 4, 0666 | IPC_CREAT);
    //Here we are creating a pointer on this memory, that can be equal to smthg we want
    int *shmaddr = shmat(shmid, NULL, 0);
    //Here we input the value of key into this pointer in order to transmit it to the initial process
    
    //Creating of semaphore:
    int semid=semget(key, 1/*quantity of semaphores in a array*/, IPC_CREAT|0666);
    semctl(semid, 0, SETVAL, (int) 1);//initail value is 1
    printf("1 %d\n", semid);
    (*shmaddr) = semid;
    
    
    
    printf("Created\n");
    
    
    return 0;



}
