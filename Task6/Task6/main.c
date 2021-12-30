////////////////////////////////////////
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
#include <sys/shm.h>

void handler(int sig) {
}
void clrscr(void);


int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("There is no enough arguments for this program\n");
        return 0;
    }

    
    struct sembuf sem;
    int semid, key, Process_quantity = 1, i = 0;
    char* time = argv[1];
    char *weight = argv[2];
    int time_num = 0, weight_num = 0;
    while (weight[i])
    {
        weight_num = weight_num * 10 + weight[i] - '0';
        i++;
    }
    //printf("weight: %d\n", weight_num);
    
    i = 0;
    while (time[i])
    {
        time_num = time_num * 10 + time[i] - '0';
        i++;
    }
    //printf("time: %d\n", time_num);
    clrscr();
    
    key=ftok(argv[0], 0);
    semid=semget(key, 2, IPC_CREAT|0666);
    semctl(semid, 0, SETVAL, (int) 500);
    semctl(semid, 1, SETVAL, (int) 1);
    //signal(SIGINT, handler);
    int *shmaddr;
     
    int shmid;
    shmid = shmget(key, 4, 0666 | IPC_CREAT);
    // создаем разделяемую память на 256 элементов
    shmaddr = shmat(shmid, NULL, 0);
    // подключаемся к разделу памяти, в shaddr – указатель на буфер с разделяемой памятью
    (*shmaddr)=0;
    
    
    
    
    
    
    //if (fork()==0)
    {
       // goto PRINT_ARG;
    }
    
    sem.sem_num = 1;
    sem.sem_flg = 0;
    sem.sem_num = 0;
    sem.sem_flg = 0;
    if (fork() == 0)
    {
        //semafore number
        while (1)
        {
            
            if (fork() == 0)
            {
                sleep(1);
                //sleep(time);
                //printf("Quantity of processes: %d\n", Process_quantity);
                goto new;
            }
            sleep(1);
            sem.sem_num = 1;
            sem.sem_op = -1;
            semop(semid, &sem, 1);
            
            (*shmaddr)++;
            
            sem.sem_op = 1;
            semop(semid, &sem, 1);
            sem.sem_num = 0;
            
            //printf("Quantity of processes: %d\n", (*shmaddr));
        }
         
    new:

        {
            sem.sem_num = 0;
            sem.sem_op=-weight_num;
            semop(semid, &sem, 1/*number of arguments*/);
            //printf("I'm in\n");
           // printf("%d\n", semctl(semid, 0, GETVAL));
            
            sleep(time_num);
            
            sem.sem_op = weight_num;
            semop(semid, &sem, 1);
            //printf("I'm out\n");
            //printf("%d\n", semctl(semid, 0, GETVAL));
            
            sem.sem_num = 1;
            sem.sem_op = -1;
            semop(semid, &sem, 1);
            
            (*shmaddr)--;
            
            sem.sem_op = 1;
            semop(semid, &sem, 1);
            sem.sem_num = 0;
            
            exit(0);
            //clrscr();
        }
        
    }
    
    while(1)
    {
        //printf("\n");
        int tmp = semctl(semid, 0, GETVAL);
        printf("Semafore value: %d\n", tmp);
        printf("Quantity of processes: %d\n", (*shmaddr));
        //printf("Quantity of processes\n");
        //printf("\n");
        //sleep(1);
        clrscr();
    }
    
    pause();
    semctl(semid, 0, IPC_RMID, (int) 0);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
    
PRINT_ARG:
    while(1)
    {
        //printf("\n");
        //int tmp = semctl(semid, 0, GETVAL);
        //printf("Semafore value: %d\n", tmp);
        //printf("Quantity of processes: %d\n", (*shmaddr));
        printf("Quantity of processes\n");
        //printf("\n");
        //sleep(1);
        clrscr();
    }
    
    
}
void clrscr(void)
{ char a[80];
    //printf("\n");
    printf("\033[2J"); /* Clear the entire screen. */
    printf("\033[0;0f"); /* Move cursor to the top left hand corner */
    sleep(1);
    
}
