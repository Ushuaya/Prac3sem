#include <stdio.h>
#include <math.h>
double masf2double(char masf[])
{
    int i = 0;
    int sign = 1;
    double sum2 = 0, tmp10 = 10, sum1 = 0;
    while ((masf[i])&&(masf[i] != ' '))
    {
        
        if ((masf[i]) == '-')
        {
            sign = -1;
            i++;
        }
        
        while ((masf[i])&&(masf[i] != ' ')&&(masf[i] != '.')&&(masf[i] != 'e')&&(masf[i] != 'E'))
        {
            sum1 = sum1 * 10;
            sum1 = sum1 + masf[i] - '0';
            ++i;
        }

        if (masf[i] == '.') {
            
            ++i;
            while ((masf[i])&&(masf[i] != ' ')&&(masf[i] != 'e')&&(masf[i] != 'E'))
            {
                sum2 = sum2 + (masf[i] - '0')/tmp10;
                tmp10 = tmp10*10;
                ++i;
            }
        }
        sum1 = sum1 + sum2;
        sum1 = sum1 * sign;
        
        sum2 = 1;
        sign = 1;
        if ((masf[i] == 'e')||(masf[i] == 'E'))
        {
            i++;
            if (masf[i] == '-')
            {
                sign = -1;
            }
            if ((masf[i] == '+') || (masf[i] == '-'))
                i++;
            sum2 = 0;
            while ((masf[i])&&(masf[i] != ' '))
            {
                sum2 = sum2 * 10;
                sum2 += (masf[i] -'0');
                i++;
            }
            //printf ("%lf TH \n", sum2);
            sum2 = sum2 * sign;
            sum2 = pow(10,sum2);
            //printf ("%lf TH \n", tmp10);
            //printf ("%lf TH \n", sum2);

        }
        
        return (sum1*sum2);
    }
    return 0;
}

int main()
{
    double Ans;
    printf("Intup numbers you want to out \n");
    char mass[10000];
    while (scanf("%s", mass) == 1)
    {
        Ans = masf2double(mass);
        printf("%.10g\n", Ans);
    }
    return 0;
}
