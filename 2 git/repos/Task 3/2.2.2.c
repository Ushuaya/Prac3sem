#include <stdio.h>
#include <stdlib.h>

int main()
{
    char c = '*';
    double An, x, Answ=0;


    printf("Input value of argument:\n");
    printf("X = ");
    scanf("%lf", &x);
    printf("Input coefficient:\n");
    printf("An = ");
    while(scanf("%lf", &An) == 1)//������ ������ ����� � ��������� �� ����� �����
    {
        Answ = (Answ + An) * x;
        printf("\nAn = ");
    }
    Answ = Answ/x;
    printf("Answer: %lf\n", Answ);

    return 0;
}
