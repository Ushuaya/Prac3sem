#include <stdio.h>
#include <stdlib.h>

int frog, frog1, frog2;

int main()
{
    int a = 1, tmp, tmp1, tmp2;
    char b = 'a';
    double c = 123.432;
    signed short small = -5, small_tmp;
    signed int big, big2;


    printf("%i", frog);
    printf("\n");
    printf("%i", frog1);
    printf("\n");
    printf("%i", frog2);
    printf("\n");
    printf("6. Проконтролировать, допускается ли инициализация переменных при описании, происходит ли инициализация по умолчанию.");
    printf("\n");
    printf("%i", a);
    printf("\n");
    printf("%c",  b);
    printf("\n");
    printf("%lf",  c);
    printf("\n");

    printf("%i", tmp);
    printf("\n");
    printf("%i", tmp1);
    printf("\n");
    printf("%i", tmp2);
    printf("\n");
    printf("\n");
    printf("\n");


    printf ("1. Выяснить, сколько байт отведено для хранения данных типа short, int, long, float, double и long double.");
    printf("\n");
    printf("%lu", sizeof (short));
    printf("\n");
    printf("%lu", sizeof (int));
    printf("\n");
    printf("%lu", sizeof (long));
    printf("\n");
    printf("%lu", sizeof (float));
    printf("\n");
    printf("%lu", sizeof (double));
    printf("\n");
    printf("%lu", sizeof (long double));
    printf("\n");
    printf("\n");
    printf("\n");


    printf("4. Выяснить, как упорядочены коды символов '0'-'9', 'a'-'z', 'A'- 'Z', пробел междсобой и относительно друг друга  ");
    printf("\n 0-9");
    printf("\n");
    printf("%i", '0');
    printf("\n");
    printf("%i", '9');
    printf("\n");
    printf("\n a-z");
    printf("\n");
    printf("%i", 'a');
    printf("\n");
    printf("%i", 'z');
    printf("\n");
    printf("\n A-Z");
    printf("\n");
    printf("%i", 'A');
    printf("\n");
    printf("%i", 'Z');
    printf("\n");
    printf("\n Space");
    printf("\n");
    printf("%i", ' ');
    printf("\n");

    int i, d;
    char h[4]={'a', '0', 'A', ' '};
    char R;
    for (i = 0; i < 3; i ++)
    {
        for( d=0  ; d < 3; ++d)
        {
            if (h[d] > h[d+1])
            {
                R = h[d];
                h[d] = h[d+1];
                h[d+1] = R;
            }
        }
    }
                printf("\n");

    printf ("Poryadokk:\n");

    for ( i = 0; i < 4; i++)
    {
        if (h[i] == 'a' || h[i] == 'A' )
        {
            printf("%c", h[i]);
	    printf("-");
	    printf("%c", h[i]+'z'-'a');
            printf("\n");
        }
        if (h[i] == '0')
            printf("0-9\n");
        if (h[i] == ' ')
            printf("SPACEX\n");
    }
    printf ("\n");
    printf ("\n");



    printf ("12. Определите, каким образом малое целое расширяется до int старшиеразряды int заполняются нулями или знаковым разрядом малого целого . ");
    printf("\n");

    small_tmp = small;
    for (int i=0; i<sizeof(short)*8; ++i)
    {
        printf("%u", (unsigned int) small_tmp % 2);

        small_tmp = small_tmp >> 1;
    }
    printf ("\n");
    big = small;
    big2 = small;
    for (int i=0; i<sizeof(int)*8; ++i)
    {
        printf("%u", (unsigned int) big % 2);

        big = big >> 1;
    }

    big2 = (unsigned int)big2 >> sizeof(short);
    if (big2 == 0)
    {
        printf("\n");
        printf ("NULL");
    }
    else
        printf("\n");
        printf ("NE NULL");
        printf("\n");

    return 0;
}
