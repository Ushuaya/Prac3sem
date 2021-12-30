//
//  od.c
//  Task4
//
//  Created by Ivan on 31.10.2020.
//

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>


#define BUFSIZE 1024

//int creat(char *name, int perms);
int main(int argc, char * argv[])
{

    
        if (argc <= 1)
        {
            printf("There is no enough arguments \n");
            return 0;
        }
    if(strcmp(argv[1], "-b"))
    {
        char buf[BUFSIZE];
        FILE *file1;
        int sym;
         
        if (!(file1 = fopen(argv[1],"r")))
        {
            printf("Error opening file \n");
            return 0;
        }
        
        int length = 10;
        int coordinate = 1;
        int i;
        
        sym = fgetc(file1);
        while (!feof(file1))
        {
            printf("%2.6d   ", coordinate);
            i = 0;
            while (i++ < length && !feof(file1))
            {
                if (sym == '\n')
                {
                    printf("\\");
                    printf("n  ");
                }
                else
                    printf("%c   ", sym );
                sym = fgetc(file1);
            }
            coordinate += length;
            printf("\n");
            
        }
        fclose(file1);
    }
    else
    {
        FILE *file1;
        int sym;
         
        if (!(file1 = fopen(argv[2],"r")))
        {
            printf("Error opening file \n");
            return 0;
        }
        
        int length = 10;
        int coordinate = 1;
        int i;
        
        sym = fgetc(file1);
        while (!feof(file1))
        {
            printf("%2.6d   ", coordinate);
            i = 0;
            while (i++ < length && !feof(file1))
            {
                int d = sym;
                    printf("%2.6o   ", d);
                sym = fgetc(file1);
            }
            coordinate += length;
            printf("\n");
            
        }
        fclose(file1);
    }
}

