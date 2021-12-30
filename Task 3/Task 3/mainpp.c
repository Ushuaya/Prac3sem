//
//  mainpp.c
//  
//
//  Created by Ivan on 26.11.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "syn.h"
void asd(int dd)
{
    return;
}
int main()
{
    signal(SIGINT, asd);
    syn();
}
