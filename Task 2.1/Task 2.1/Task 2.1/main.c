#include <stdio.h>
#include <stdlib.h>
int main()
{
    double x, E, xi=1, xij, tmp=E+1;
    char c = '*';
    double sum2=0, tmp10=10, sum1=0;

/*
    //¬˚˜ËÒÎÂÌËÂ ÔÂ‚Ó„Ó ˜ËÒÎ‡
    printf("Input nuber:\n");
    if((c = getchar()) != EOF)//œÓ‚ÂÍ‡ Ì‡ ÍÓÌÂˆ Ù‡ÈÎ‡
    {
        while (c != '.' && c != '\n' && c != EOF)
        {
            sum1 = sum1 * 10;
            sum1 = sum1 + c - '0';
            scanf("%c", &c);
        }
        if (c == '.')
        {
            scanf("%c", &c);
            while (c != '\n' && c != EOF)
            {
                sum2 = sum2 + (c-'0')/tmp10;
                tmp10 = tmp10*10;
                scanf("%c", &c);
            }
        }
        sum1 = sum1 + sum2;
        x = sum1;
        //printf("sum = %f\n", sum1);
        printf("Input accuracy:\n");
        scanf("%lf", &E);
        tmp=E+1;


        while (tmp >= E)
        {
            xij= 0.5*(xi+(x/xi));
           // printf("xi = %f\n", xi);
           // printf("xij = %f\n", xij);
            if (xij-xi < 0)
            {
                tmp = (xij-xi)*(-1);
            }
            else
                tmp = (xij-xi);
            xi = xij;
        }
        printf("%.10g\n", xij);
*/


again:
        printf("Input nuberrr:\n");
        rewind(stdin);//Ó˜Ë˘‡ÂÏ ·ÛÙÂ
        while((c = getchar()) != EOF)//¬‚Ó‰ËÏ ÔÂ‚Û˛ ˆËÙÛ Ë ÔÓ‚ÂˇÂÏ Ì‡ ÍÓÌÂˆ Ù‡ÈÎ‡
        {
            if (c == '-')
            {
                printf("Number can't be negative!!\n");
                goto again;
            }

            sum2=0;
            tmp10=10;
            sum1=0;
            while (c != '.' && c != '\n')//—˜ËÚ‡ÂÏ Ò‡ÏÓ ‚Â˘ÂÒÚ‚ÂÌÌÓÂ ˜ËÒÎÓ, ‚‚Ó‰ËÏÓÂ ÔÓÒËÏ‚ÓÎ¸ÌÓ
            {
                sum1 = sum1 * 10;
                sum1 = sum1 + c - '0';
                scanf("%c", &c);
            }
            if (c == '.')
            {
                scanf("%c", &c);
                while (c != '\n' && c != EOF)
                {
                    sum2 = sum2 + (c-'0')/tmp10;
                    tmp10 = tmp10*10;
                    scanf("%c", &c);
                }
            }
            sum1 = sum1 + sum2;
            x = sum1;//¬ ı ı‡ÌËÚÒˇ ÔÓÎÛ˜ÂÌÌ‡ˇ ÒÛÏÏ‡, ‡‚Ì‡ˇ ËÒÍÓÏÓÏÛ ˜ËÒÎÛ
            //  в х хранится вводимое число


            printf("Input accuracy:\n");//«‡‰‡∏Ï ÚÓ˜ÌÓÒÚ¸
            scanf("%lf", &E);
            tmp=E+1;

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
            printf("Input nuber:\n");
            rewind(stdin);//Ó˜Ë˘‡ÂÏ ·ÛÙÂ
    }
   // }


    return 0;
}
