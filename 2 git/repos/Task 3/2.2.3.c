#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    char c = '*';
    double sum2=0, tmp10=10, sum1=0, An, x, Answ=0, Derivative=0, n, integral_tmp=0;
    int sign = 1;

        printf("Input degree of polinom (natural):\n");
        printf("n = ");
        scanf("%lf", &n);

        printf("Input value of argument:\n");
        printf("X = ");
        scanf("%lf", &x);
        if ((c = getchar()) != EOF)
        {
            printf("Input coefficient:\n");
            printf("An = ");
            rewind(stdin);//Ó˜Ë˘‡ÂÏ ·ÛÙÂ
            while((n >= 0) && ((c = getchar()) != EOF) && (n >= 0))
            {
                sign = 1;
                if (c == '-')
                {
                    sign = -1;
                    if ((c = getchar()) == EOF)
                    {
                        goto extraend;
                    }
                }
                sum2=0;
                tmp10=10;
                sum1=0;
                while (c != '.'  && c != '\n' && c != ' ' && c != EOF)//—˜ËÚ‡ÂÏ Ò‡ÏÓ
                {
                    sum1 = sum1 * 10;
                    sum1 = sum1 + c - '0';
                    scanf("%c", &c);
                }
                if (c == '.')
                {
                    scanf("%c", &c);
                    while (c != '\n' && c != EOF && c != ' ')
                    {
                        sum2 = sum2 + (c-'0')/tmp10;
                        tmp10 = tmp10*10;
                        scanf("%c", &c);
                    }
                }
                sum1 = sum1 + sum2;
                An = sum1;//¬ An ı‡ÌËÚÒˇ ÔÓÎÛ˜ÂÌÌ‡ˇ ÒÛÏÏ‡, ‡‚Ì‡ˇ ËÒÍÓÏÓÏÛ ˜ËÒÎÛ
                An *= sign;
                Derivative = Derivative * x + Answ;
                Answ = (Answ + An)*x;
                integral_tmp += ((pow(x, n+1))*An)/(n+1);
                n--;
                if (n >= 0)
                {
                    printf("\n");
                    printf("Input coefficient:\n");
                    printf("An = ");
                    rewind(stdin);//Ó˜Ë˘‡ÂÏ ·ÛÙÂ
                }
            }
        }
extraend:
        Answ = Answ/x;
        Derivative = Derivative/x;
    
        printf("Value of polinom: %f\n", Answ);
        printf("Value of Derivative: %f\n", Derivative);
        printf("Value of Integral: %f\n", integral_tmp);

    return 0;
}
