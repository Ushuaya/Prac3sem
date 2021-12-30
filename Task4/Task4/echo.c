//
//  main.c
//  Task4
//
//  Created by Ivan on 30.10.2020.
//

#include <stdio.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    char tmp[] = "-n";

    if (argc == 1)
    {
        return 0;
    }
    
    if (!strcmp(tmp, argv[1]))
    {
        for (int i = 2; i < argc; i ++ )
        {
            printf("%s ", argv[i]);
        }
    }
    else
    {
        for (int i = 1; i < argc; i ++ )
        {
            printf("%s ", argv[i]);
        }
        printf ("\n");
    }


    return 0;
}
