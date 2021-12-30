//
//  main.c
//  SEM
//
//  Created by Ivan on 23.10.2020.
//

#include <stdio.h>

#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int count = 1;


void SigHndlr (int s) /* обработчик сигнала */
{

    signal (SIGINT, SIG_DFL);

}

void termina ()
{
    printf ("alarm");
}

void my_sleep (int s)
{
    
    signal(SIGALRM, termina);
    alarm (s);
    
}


int main(int argc, char **argv)
{
    int d = 5;
    signal (SIGINT, SigHndlr); /* установка реакции на сигнал */
    signal(SIGALRM, termina);
    
    my_sleep(d);
    
    alarm (5);
    while (1)
    {
        printf("Hello\n");
        sleep(1);
    };
return 0;
}
