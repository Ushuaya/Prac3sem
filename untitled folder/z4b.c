//
//  z4b.c
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

//typedef int semaphore;

int i, tmp_num;

int main(int argc, char *argv[])
{
    
    //printf("%s\n", argv[1]);
    int key=ftok("/Users/ivan/Desktop/C 3 semestr/untitled folder/z4", 0);
    //printf("%d\n", key);


    int semid=semget(key, 1, IPC_CREAT|0666);
    semctl(semid, 0, IPC_RMID, (int) 0);
    //printf("1 %d\n", semid);
    
    printf("Deleted\n");
    
    
    return 0;



}
