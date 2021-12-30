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
    key=ftok("/Users/German/AppData/Local/Packages/CanonicalGroupLimited.UbuntuonWindows_79rhkp1fndgsc/LocalState/rootfs/home/german/TASKS/KW/4_Create", 0);
    printf("%d\n", key);


    if (fork() == 0)
    {
        execl("/Users/German/AppData/Local/Packages/CanonicalGroupLimited.UbuntuonWindows_79rhkp1fndgsc/LocalState/rootfs/home/german/TASKS/KW/4_Create", "Create", NULL);
        // 1-ый аргумент это путь к исполняемому файлу, в котором находится реализованная программа Creat
    }
    sleep(1);// Эта операция выполняется для ожидания, пока другая программа поместит значение ключа в общую память
    int shmid = shmget(key, sizeof(int), 0666 | IPC_CREAT);
    int *shmaddr = shmat(shmid, NULL, 0);

    //Здесь мы приравниваем адрес семафора, который мы передали из другой программы
    int semid = *shmaddr;
    printf("%d\n", *shmaddr);

    //PART2
    int i = 10; // кол-во процессов, которое мы создали

    semctl(semid, 0, SETVAL, (int) 1);
    while (i--)
    {
        if (fork() == 0)
            goto IMNEW;
    }
    goto IMFATHER;
IMNEW:
    //входим в критеческую секцию
    sem.sem_num = 0;// номер семафора в векторе
    sem.sem_op = -1;// производимая операция
    sem.sem_flg = 0;// флаг операции
    semop(semid, &sem, 1);

    FILE* file1;
    if(((file1 = fopen("SMTHNG.txt", "a+t")) == NULL))
    {
        printf ("Cannot open file.\n");
        exit(1);
    }
    int index = getpid();
    printf("pri: %d\n", index); // просто выводим pid
    fprintf(file1, "%4d", index); // записываем pid
    char c = ' ';
    fwrite(&c, sizeof(char), 1, file1); // записываем пробел
    fclose (file1);

    sem.sem_op = 1;
    semop(semid, &sem, 1);
    //выходим из критеческой секции
    exit(0);

IMFATHER:
    pause(); // приостанавливаем отцовский процесс

    key=ftok("/Users/German/AppData/Local/Packages/CanonicalGroupLimited.UbuntuonWindows_79rhkp1fndgsc/LocalState/rootfs/home/german/TASKS/KW/4_Delete", 0);
    printf("%d\n", key);


    if (fork() == 0)
    {
        execl("/Users/German/AppData/Local/Packages/CanonicalGroupLimited.UbuntuonWindows_79rhkp1fndgsc/LocalState/rootfs/home/german/TASKS/KW/4_Delete", "Delete", NULL);
        // 1-ый аргумент это путь к исполняемому файлу, в котором находится реализованная программа Creat
    }
    return 0;

}


