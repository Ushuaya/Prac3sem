//
//  cp.c
//  Task4
//
//  Created by Ivan on 31.10.2020.
//

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#define BUFSIZE 1024

//int creat(char *name, int perms);
int main(int argc, char * argv[])
{
    /*       if (argc <= 2)
        {
            printf("There is no enough arguments \n");
            return 0;
        }

    */
    
    if (argc <=2)
    {
        printf("There is no enough arguments \n");
        return 0;
    }
    else
    {
        int  file1, file2, size;
        char buf[BUFSIZE];

        file1 = open(argv[1],  O_RDONLY);
        file2 = open(argv[2],  O_CREAT | O_TRUNC | O_WRONLY);
        //while(!feof())
        {
            while( ( size = read( file1, buf, BUFSIZE ) ) > 0 )
            {

                if( write(file2, buf, size) != size )
                {
                    perror("Write error: \n");
                    return 0;
                }
            }
        }
        close(file1);
        close(file2);
    }
    return 0;
}

