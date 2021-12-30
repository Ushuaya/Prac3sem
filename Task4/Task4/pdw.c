//
//  pdw.c
//  Task4
//
//  Created by Ivan on 30.10.2020.
//

#include <stdio.h>
#include <limits.h>
#include <unistd.h>

int main(int argc, char * argv[])
{

       char directory[PATH_MAX];
    
       char * link;

       
        link = getwd (directory);
       

       if (link == NULL)
           printf ("Error");
       else
           printf ("%s\n", directory);
 
    return 0;
}
