#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <zconf.h>

int main(int argc, char *argv[]) {
    int f1, f2, f3, N;
    char * buf, *strF, * strS;
    N = atoi(argv[4]); // преобразуем строчку с числом в число, это послежний аргумент,который передается при вызове программе,
                       //т.е. то сколько байт будем считывать из файла
    buf = (char*)malloc(6); // 6 - это размер строки 'ready' + '/0',
                            // это ready нужно, чтобы синхронизировать процессы, чтобы в канал сначала отправлять ready, а потом получать от туда ready
                            // таким образом налаживается синхронизация
    strF = (char*)malloc(N);
    strS = (char*)malloc(N);
    f1 = open(argv[1], O_RDONLY);
    f2 = open(argv[2], O_WRONLY|O_TRUNC|O_CREAT, 0777);
    f3 = open(argv[3], O_WRONLY|O_TRUNC|O_CREAT, 0777);
    int f[2], s[2];
    pipe(f);
    pipe(s);
    //два параллельных процесса
    
    if (fork() == 0){ // процесс сын
        while(1)
        {
            read(f[0], buf, 6);
            if (read(f1, strS, N) < N)
            {
                write(s[1], "ready", 6);
                break;
            }
            write(f3, strS, N);
            write(s[1], "ready", 6);
        }
    }
    
    else
    {
        while (1)
        {
            if (read(f1, strF, N) < N)
            {
                break;
            }
            write(f2, strF, N);
            write(f[1], "ready", 6);
            read(s[0], buf, 6); 
        }
        close(f1);
        close(f2);
        close(f3);
    }
    return 0;
}
