//
//  cmp.c
//  Task4
//
//  Created by Ivan on 30.10.2020.
//

#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <assert.h>


int main(int argc, char * argv[])
{

    int sym1 = 0, sym2 = 0, sym_check = 0;
    int line = 1;

    if (argc > 2)
    {
        FILE* file1 = fopen(argv[1], "r");
        FILE* file2 = fopen(argv[2], "r");
            
        if (file1 != NULL && file2 != NULL)
        {
            while (!feof(file1) && !feof(file2) && (sym1 == sym2))
            {
                sym1 = fgetc(file1);
                sym2 = fgetc(file2);
                sym_check++;

                if ((sym1 == '\n') && (sym2 == '\n'))
                {
                    line++;
                    sym_check = 0;
                }
            }

            if (sym1 == sym2)
            {
            printf("files are the same");
            }
            else
            {
                printf("File1 differs from File2: line %d char %d\n", line, sym_check);
            }

            fclose(file2);
            fclose(file1);
        }
        else
            printf("One or two file is not exist\n");
    }
    else
    {
        printf("There are not enough arguments!\n");
    }


    return 0;
}
