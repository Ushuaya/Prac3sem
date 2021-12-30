//
//  main.c
//  TMP
//
//  Created by Ivan on 16.10.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
/*
int palindrom (char * text)
{
    char * end;
    char * begin;
    end = text;
    begin = text;
    
    while (*(end+1) != '\0')
    {
        end++;
    }
    printf("\nEND: %c\n", *end);
    printf("\nEND: %c\n", *begin);
    
    while ((begin < end) && ( *begin == *end ))
    {
        printf("\n%c %c\n", *begin, *end);
        end --;
        begin ++;
    }
    if (begin < end)
    {
        printf("NO");
        return 0;
    }
    else
    {
        printf("YES");
        return 1;
    }
               
}


 int main()
 {
     char str[50] = "This is si sihT";
     int i;
     //char *s;
     //printf("%d\n", sizeof(int));
     palindrom(str);
     
     
        
}
*/
int main()
{
    char str[50] = "This is si sihT";
    unsigned int a = 1;
    int b = -3;
    
    printf("%d\n", a+b);
    printf("%d\n", sizeof(long int));
    printf("%d\n", sizeof(short int));
    printf("%d\n", sizeof(int));
    printf("%d\n", sizeof(float));
    printf("%lu\n", sizeof(double));




    
    
    return 0;
}
