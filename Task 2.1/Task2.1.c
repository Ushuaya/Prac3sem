#include <stdio.h>
#include <stdlib.h>
int main()
{
    double x, E, xi=1, xij, tmp=E+1;
    char c = '*';
    double sum2=0, tmp10=10, sum1=0;



 
            x = sum1;//В х хранится полученная сумма, равная искомому числу



            printf("Input accuracy:\n");//Задаём точность
            scanf("%lf", &E);
            tmp=E+1;
               
            printf("Input number:\n");
            while (scanf ("%lf", &x) != EOF)
            {
                while (tmp >= E)//Считаем корень
                {
                    xij= 0.5*(xi+(x/xi));

                    if (xij-xi < 0)
                    {
                        tmp = (xij-xi)*(-1);
                    }
                    else
                        tmp = (xij-xi);
                    xi = xij;
                }
                printf("%.10g\n", xij);
                printf("\n");
                printf("Input number:\n");
                tmp=E+1;
            }
    
   // }


    return 0;
}
