//
//  ls.c
//  Task4
//
//  Created by Ivan on 30.10.2020.
//


#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

int IS_IT_EMPTY()
{
    int i = 0;
    DIR * empty_dir;
    struct dirent * what_in_empty_dir;
    if (!(empty_dir = opendir(".")))
    {
        perror("JUST EMPTY");
        return 0;
    }
    while ((what_in_empty_dir = readdir(empty_dir)))
    {
        if (!strcmp(what_in_empty_dir->d_name, ".") || !strcmp(what_in_empty_dir->d_name, "..") || !strcmp(what_in_empty_dir->d_name,".DS_Store"))
        {
            i++;
        }

    }
    if (i == 3)
        return 1;
    else
        return 0;
}

void JUST_PRINT_IT()//Function of printing current directory files
{
    DIR * print_dir;
    //char directory[PATH_MAX];
    //char * link;
    struct dirent * what_in_print_dir;
    //link = getwd (directory);
    
    if (!(print_dir = opendir(".")))
    {
        perror("JUST PRINT");
        return;
    }
    errno = 0;
    while ((what_in_print_dir = readdir(print_dir)))
    {
        if (!strcmp(what_in_print_dir->d_name, ".") || !strcmp(what_in_print_dir->d_name, "..") || !strcmp(what_in_print_dir->d_name,".DS_Store"))
        {
            continue;
        }
        else
        {
            printf ("%s    ", what_in_print_dir->d_name);
        }
            
        errno = 0;
    }

    printf("\n");
    if (errno)
    {
        perror("readdir");
        rewinddir(print_dir);
        return;
    }
    //printf("\n\n");
    //closedir(print_dir);
    //opendir(".");
    rewinddir(print_dir);//Placing poiter to the beginnig of directory
    return;
}

void in_directory(char *name, int FFR)//recursive case of ls -R
{
    struct dirent* findir;
    DIR *fopendir;
    char directory[PATH_MAX];
    
    if (!(fopendir = opendir(name)))
        return;
    
    errno = 0;
    chdir(name);


    printf("./%s:\n", name);
    JUST_PRINT_IT();
    printf("\n");
    
    while ((findir = readdir(fopendir)))
    {
        if (!strcmp(findir->d_name, ".") || !strcmp(findir->d_name, "..") || !strcmp(findir->d_name,".DS_Store"))//skipping of the system files
               continue;

        in_directory(findir->d_name, FFR);
        
        errno = 0;
    }

    if (errno)
    {
        perror("readdir");
        exit(0);
    }
    chdir("..");//Going up
    //getwd (directory);//
    //printf("%s\n", directory);//
     
    return;
}
 

void print_files(int FR)//Case of standart ls
{
    DIR * open_dir;
    char directory[PATH_MAX];
    char * link;
    struct dirent * what_in_dir;
    link = getwd (directory);
    //printf("%s\n", directory);
    JUST_PRINT_IT();
    printf("\n");
    if (link != NULL)
    {
        if (!(open_dir = opendir(".")))
        {
            perror("opendir");
            return;
        }
        errno = 0;
        while ((what_in_dir = readdir(open_dir)))
        {
            if (!strcmp(what_in_dir->d_name, ".") || !strcmp(what_in_dir->d_name, "..") || !strcmp(what_in_dir->d_name,".DS_Store"))//skipping of the system files
                continue;
            
         if (FR)
         {
             in_directory(what_in_dir->d_name, FR);
         }

            
                
            errno = 0;
        }

        printf("\n");
        if (errno)
        {
            perror("readdir");
            return;
        }
        closedir(open_dir);
    }
    else
    {
        exit(0);
    }
}


int main(int argc, char * argv[])
{
    int flag_R = 0;
    
    if (argc > 1)
        if (strcmp(argv[1], "-R") == 0)
            flag_R = 1;

     

        print_files(flag_R);

    return 0;
}
