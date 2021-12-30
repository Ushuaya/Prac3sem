#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>
#include "sys/wait.h"
//��������:
// 1) pr1 > f2 � ���� �� ���������� �������, ����� �� ��������� � 2)
// 2) pr3 | pr4
int main(int argc, char *argv[])
{
    int pid = fork();
//1) pr1 > f2
    int Status;

    if(pid == 0)
    {
        int f2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC);
        dup2(f2, 1);
        close(f2);
        execlp(argv[1], argv[1], NULL);
        exit(1);
    }

    wait(&Status);
    if(WIFEXITED(Status) && WEXITSTATUS(Status) == 0) // ������ �������� �� �� ������� �� ���������� 1)
    {
        exit(0);
    }
// 2) ���� 1) ����������� �������, ����� �� �������� ������ pr3 | pr4, � ������ �������� 1) => 2) ���������� �� �����
// pr3 | pr4
    int fd[2], in, out, next_in;
    pipe(fd); // ������� ����� � ��������� ��� �������������
    out = fd[1];
    next_in = fd[0];
    if(fork == 0)
    {
        dup2(out, 1);
        close(out); //������� ��������������� � ������������� �� ������ ����
        close(next_in); // //������� ��������������� � ������������� �� ������ ����
        execlp(argv[3], argv[3], NULL);
    }
    close(out); // ���� ���� �� ������ � if, �� ��� ����� ���������
    in = next_in;
    if(fork() == 0)
    {
        dup2(in, 0);
        close(in);
        execlp(argv[4], argv[4], NULL);
    }
    close(in);
    wait(NULL);
    wait(NULL);
    return 0;
}
