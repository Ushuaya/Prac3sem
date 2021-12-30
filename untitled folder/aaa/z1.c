//
//  z1.c
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

int f(int x) {
    printf("DEB%d\n",x );
   if (x < 0 || x > 400) {
       return x;
   }
   else {
       return x - f(x/2 - 2);
   }
}
int main()
{
    f(251);
    return 0;
}
