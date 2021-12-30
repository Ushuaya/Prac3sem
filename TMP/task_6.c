#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <unistd.h>
#define N 5 // количество философов
#define THINKING 0 // урод думает
#define HUNGRY 1   // мразь голодный
#define EATING 1   // скотина кушает
#define LEFT (i - 1) % N // номер левого соседа дл€ i-го философа
#define RIGHT (i + 1) % N // номер правого соседа дл€ i-го философа
typedef int semaphore; // определили тип семафор

struct sembuf up = {0, 1, 0}; //V = {номер семафора в векторе, производима€ операци€, флаг операции}
struct sembuf down = {0, -1, 0}; //P = {номер семафора в векторе, производима€ операци€, флаг операции}

int state[N]; // массив состо€ний каждого из философов, заполненный нул€ми
semaphore mutex = 1; // семафор дл€ доступа в критическую секцию
semaphore s[N]; // массив семафоров по одному на каждого из философов
int i = 1;

int Philosopher(int i);
int Think(int i);
int Take_Forks(int i);
int Eat(int i);
int Put_Forks(int i);
int Test(int i);

int Philosopher(int i)
{
    while(i != N)
    {
        Think(i); // мен€ем статус текущего философа на статус урод думает
        Take_Forks(i); // берем обе вилки
        Eat(i); // скотина кушает
        Put_Forks(i);
        i++;
    }
}

int Think(int i)
{
    state[i] = THINKING;
    sleep(5);
}

int Eat(int i)
{
    state[i] = EATING;
    sleep(5);
}

int Take_Forks(int i)
{
    //входим в критическую секцию
    semop(mutex, &down, 1);
        state[i] = HUNGRY;
        Test(i);
    //выходим из критической секции
    semop(mutex, &up, 1);
    if(state[i] != EATING)
    {
        semop(s[i], &up, 1); // поднимаем семафор, чтобы философ вышел из режима ожидани€
    }
    else
    {
        semop(s[i], &down, 1); // опускаем семафор, если философ поел
    }
}

int Put_Forks(int i)
{
    //входим в критическую секцию
    semop(mutex, &down, 1);
        Test(LEFT); //делаем проверку на то свободна€ ли лева€ вилка или нет
        if((state[LEFT] != EATING)) // если он не ел,как вы€снилось после проверки, то семафор нужно подн€ть, так как мы его в функции Test опустили
        {
            semop(s[i], &up, 1);
        }
        Test(RIGHT); ////делаем проверку на то свободна€ ли права€ вилка или нет
        if((state[RIGHT] != EATING))
        {
            semop(s[i], &up, 1);
        }
        if(state[i] != EATING)
        {
            if((state[LEFT] != EATING) && ((state[RIGHT] != EATING))) // если слева и справа сосесди не ели, как вы€снилось после проверики
                                                                     // то снова провер€ем нашего текущего филсофа
            {
                   Test(i);
                   semop(s[i], &down, 1);   // так как мы подн€ли семафор в Test, то его нужно опустить
            }
        }
        state[i] = THINKING; //после того, как отработали с текущем философом,т.е. она поел,нужно поставить ему снова состо€ние THINKING
    //выходим из критической секции
    semop(mutex, &up, 1);
}

int Test(int i) // провер€ем зан€та ли вилка соседом
{
    if((state[i] == HUNGRY) && (state[LEFT] != EATING) && (state[RIGHT] != EATING))
    {
        state[i] = EATING;
        semop(s[i], &up, 1);
    }
    else
    {
        semop(s[i], &down, 1); // если хоть одна чмошна€ вилка зан€та
    }
}

int main()
{
    Philosopher(i);
    return 0;
}
