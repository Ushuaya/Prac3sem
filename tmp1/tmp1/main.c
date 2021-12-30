#include <stdio.h>
#include <stdlib.h>
int main()
{
    double x, E, xi=1, xij, tmp=E+1;
    char c = '*';
    double sum2=0, tmp10=10, sum1=0;



 
            x = sum1;//¬ ı ı‡ÌËÚÒˇ ÔÓÎÛ˜ÂÌÌ‡ˇ ÒÛÏÏ‡, ‡‚Ì‡ˇ ËÒÍÓÏÓÏÛ ˜ËÒÎÛ



            printf("Input accuracy:\n");//«‡‰‡∏Ï ÚÓ˜ÌÓÒÚ¸
            scanf("%lf", &E);
            tmp=E+1;
               
            printf("Input number:\n");
            while (scanf ("%lf", &x) != EOF)
            {
                while (tmp >= E)//—˜ËÚ‡ÂÏ ÍÓÂÌ¸
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
