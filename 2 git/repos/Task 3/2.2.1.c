#include <stdio.h>
#include <stdlib.h>

int main()
{
    double An, x, Answ=0, Derivative=0;


   /**/
        printf("Input value of argument:\n");
        printf("X = ");
        scanf("%lf", &x);

            printf("Input coefficient:\n");
            printf("An = ");
            while(scanf("%lf", &An) == 1)
            {

                Derivative = Derivative * x + Answ;
                Answ = (Answ + An)*x;


                printf("\n");
                printf("Input coefficient:\n");
            }

        Answ = Answ/x;
        Derivative = Derivative/x;
        printf("Value of polinom: %f\n", Answ);
        printf("Value of Derivative: %f\n", Derivative);

    return 0;
}
