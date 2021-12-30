//
//  main.c
//  Task 2.7
//
//  Created by Ivan on 18.10.2020.
//

#include<stdio.h>
#include<setjmp.h>
#include<math.h>
jmp_buf begin; /* Просто какой-то тип данных для этой функции */
char curlex;
void getlex(void);
int expr(void);
int add(void);
int mult(void);
int minus(void);
int fpow(void);
int fpow_main(void);
void error(void);

int main()
{
    int result;
    setjmp(begin);
    printf("==>");
    //printf("Curlex: %c\n", curlex);
    getlex();
    //printf("Curlex: %c\n", curlex);
    result=expr();
    if (curlex != '\n') error();
    printf("\n%d\n",result);
    return 0;
}
    
void getlex()
{
    //printf("Curlexget1: %c\n", curlex);
    while ( (curlex = getchar()) == ' ');
    //printf("Curlexget2: %c\n", curlex);
}
   
void error(void)
{
    printf("\nÎØÈÁÊÀ!\n");
    while(getchar()!='\n');
    longjmp(begin,1);
}

int expr()
{
    int u = add();
plus:
    while (curlex == '+')
    {
        getlex();
        u += add();
    }
mins:
    while (curlex == '-')
    {
        getlex();
        u -= add();
    }
    
    if (curlex == '+')
        goto plus;
    if (curlex == '-')
        goto mins;
    //printf("Curlexexpr: %c\n", curlex);
    
    return u;
}

    
int add()
{
    int a=fpow_main();
mulpl:
    while (curlex == '*')
    {
        getlex();
        a *= fpow_main();
        
    }
delpl:
    while (curlex == '/')
    {
        getlex();
        a /= fpow_main();
        
    }
    if (curlex == '*')
        goto mulpl;
    if (curlex == '/')
        goto delpl;
    
    return a;
}


int fpow() // вспомогательная рекурсивная функция для fpow_main
{
    int t = mult();
    if (t < 0)
        error();
    if (curlex == '^')
    {
        getlex();
        return t = pow(t, fpow());
    }
    else
        return t;
}

int fpow_main()
{
    int p = mult();
    if (curlex == '^')
    {
        getlex();
        p = pow(p, fpow());
    }
    
    return p;
}

    
int mult()
{
    int m = 0;
    
    switch(curlex)
    {
    case '0': case '1': case '2': case '3': case '4': case '5':
    case '6': case '7': case '8': case '9': m = curlex-'0'; break;
    
        case '(': getlex();  m=expr(); if (curlex == ')') break;

    default : error();
    }

    getlex();

    return m;
}

