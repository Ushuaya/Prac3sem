#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <unistd.h>
#define N 5 // ���������� ���������
#define THINKING 0 // ���� ������
#define HUNGRY 1   // ����� ��������
#define EATING 1   // ������� ������
#define LEFT (i - 1) % N // ����� ������ ������ ��� i-�� ��������
#define RIGHT (i + 1) % N // ����� ������� ������ ��� i-�� ��������
typedef int semaphore; // ���������� ��� �������

struct sembuf up = {0, 1, 0}; //V = {����� �������� � �������, ������������ ��������, ���� ��������}
struct sembuf down = {0, -1, 0}; //P = {����� �������� � �������, ������������ ��������, ���� ��������}

int state[N]; // ������ ��������� ������� �� ���������, ����������� ������
semaphore mutex = 1; // ������� ��� ������� � ����������� ������
semaphore s[N]; // ������ ��������� �� ������ �� ������� �� ���������
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
        Think(i); // ������ ������ �������� �������� �� ������ ���� ������
        Take_Forks(i); // ����� ��� �����
        Eat(i); // ������� ������
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
    //������ � ����������� ������
    semop(mutex, &down, 1);
        state[i] = HUNGRY;
        Test(i);
    //������� �� ����������� ������
    semop(mutex, &up, 1);
    if(state[i] != EATING)
    {
        semop(s[i], &up, 1); // ��������� �������, ����� ������� ����� �� ������ ��������
    }
    else
    {
        semop(s[i], &down, 1); // �������� �������, ���� ������� ����
    }
}

int Put_Forks(int i)
{
    //������ � ����������� ������
    semop(mutex, &down, 1);
        Test(LEFT); //������ �������� �� �� ��������� �� ����� ����� ��� ���
        if((state[LEFT] != EATING)) // ���� �� �� ��,��� ���������� ����� ��������, �� ������� ����� �������, ��� ��� �� ��� � ������� Test ��������
        {
            semop(s[i], &up, 1);
        }
        Test(RIGHT); ////������ �������� �� �� ��������� �� ������ ����� ��� ���
        if((state[RIGHT] != EATING))
        {
            semop(s[i], &up, 1);
        }
        if(state[i] != EATING)
        {
            if((state[LEFT] != EATING) && ((state[RIGHT] != EATING))) // ���� ����� � ������ ������� �� ���, ��� ���������� ����� ���������
                                                                     // �� ����� ��������� ������ �������� �������
            {
                   Test(i);
                   semop(s[i], &down, 1);   // ��� ��� �� ������� ������� � Test, �� ��� ����� ��������
            }
        }
        state[i] = THINKING; //����� ����, ��� ���������� � ������� ���������,�.�. ��� ����,����� ��������� ��� ����� ��������� THINKING
    //������� �� ����������� ������
    semop(mutex, &up, 1);
}

int Test(int i) // ��������� ������ �� ����� �������
{
    if((state[i] == HUNGRY) && (state[LEFT] != EATING) && (state[RIGHT] != EATING))
    {
        state[i] = EATING;
        semop(s[i], &up, 1);
    }
    else
    {
        semop(s[i], &down, 1); // ���� ���� ���� ������� ����� ������
    }
}

int main()
{
    Philosopher(i);
    return 0;
}
