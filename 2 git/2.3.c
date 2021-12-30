#include <stdio.h>
#include <stdlib.h>


int iter(int index)
{
    int x1 = 0;
    int x2 = 1;
    while (index > 0)
    {
        x2 += x1;
        x1 -= x2;
        x1 *= (-1);
        index --;
    }
return x1;
}

int reer(int index)
{
    if (index == 0) return 0;
    if (index == 1) return 1;
    return (reer(index - 1) + reer(index - 2));
}



int main()
{
    int i;

    printf ("Input number of digit you want to find:\n");
    
    while (scanf("%i", &i) == 1)
    {
        printf ("Answer internationale:\n");
        printf("%i", iter(i));
        printf("\n");
        printf ("Answer ~REternationale:\n");
        printf("%i", reer(i));
        printf("\n");
    }


    return 0;
}
