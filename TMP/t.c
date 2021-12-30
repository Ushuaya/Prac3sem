#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
//#include "list.h"
//#include "tree.h"
//#include "exec.h"
#include <string.h>
#define SIZE 16
//;;;;;;;;;;;;;;;;;;;; ЭТО ДЛЯ ПЕРВОГО ЭТАПА
char pred;

int c; /*текущий символ */
char **lst; /* список слов (в виде массива)*/
char *buf; /* буфер для накопления текущего слова*/
char *buf_ss; // буфер для слэшей
int sizebuf; /* размер буфера текущего слова*/
int sizelist; /* размер списка слов*/
int curbuf; /* индекс текущего символа в буфере*/
int curlist; /* индекс текущего слова в списке*/

int kol_words(char **lst);
char **reverse(char **lst, int count);
void null_list();
void termlist();
void change_lst(char **lst, int sizelist);
void printlist(char **lst);
void clearlist(char **lst);
void nullbuf();
void addsym();
void addword();
int symset(int c);
int number;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ЭТО ДЛЯ 2 ЭТАПА(ДЛЯ ДЕРЕВА)

int count(char **lst, int *k)
{
    int i;
    i=0;
    while((*k)>=0)
    {
        printf("1\n");
        if (strcmp(lst[(*k)],"|")==0)
        {
            break;
        }
        printf("%s\n",lst[(*k)]);
        (*k)--;
        i++;
    }
    return i;
}

struct List
{
    char *Word;
    struct List *Next;
};

struct tree
{
    char **argv;
    char *infile;
    char *outfile;
    int count_r; // ?????»-???? N„?°???»???? ???° N‡N‚?µ?????µ
    int count_w; // ?????»-???? N„?°???»???? ???° ?·?°????N?N?
    int flag; // N„?»?°?? ???»N? ??N€?????µN€???? ??N‚?? ???· "> < >>" ?±N‹?» ???µN€??N‹??
    int background; // ?????»-???? &
    struct tree *pipe;
    struct tree *next;
    int count; // ?????»-???? ?°N€??N????µ??N‚????
};

struct tree *inf;
char **New_list; // структура списков во всем списке
char *str; // текущее слово
int k; // номер текущего слова

struct tree *Create_inf();
void add_arg(struct tree *inf, char *str, int k);
int kol_amp(char **lst);
void kol_rediraction(char **lst,int *k_in_1, int *k_out_1, int *k_out_2);
void make_tree(char **lst, struct tree *inf);
struct tree *Analys_List(char **lst);
struct tree *semicolon(char **lst,int k);
struct tree *paralell(char **lst,int k);
int kol_sticks(char **lst);
int kol_semicolon(char **lst);
void Clear(struct tree *inf);
void Clear_next(struct tree *inf);
void make_shift(int n);
void Print_tree(struct tree *inf, int shift);

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

// ПЕРВЫЙ ЭТАП

char str_EUID[] = "ID";

void clearlist(char **lst)
{
    int i;
    sizelist = 0;
    curlist = 0;
    if (lst == NULL)
        return;
    for (i = 0; lst[i] != NULL; i++)
        lst[i] = malloc(0);
    lst = NULL;

}

void null_list()
{
    sizelist = 0;
    curlist = 0;
    lst = NULL;
    buf_ss = NULL;
}

int count_lst(char **lst)
{
    int x=0;
    while(lst[x]!=NULL)
    {
        x++;
    }
    return x;
}

/* Функция termlist() завершает список, добавляя NULL в позицию curlist и обрезает память,
 занимаемую списком, до точного размера. */
void termlist()
{
    if (curlist > sizelist-1)
        lst = realloc(lst,(sizelist+1)*sizeof(char*));
    if (lst == NULL)
    {
        printf ("ERROR!");
        clearlist(lst);
        lst = NULL;
        exit(0);
    }
    lst[curlist] = NULL;
    /*выравниваем используемую под список память точно по размеру списка*/
    lst = realloc(lst,(sizelist=curlist+1)*sizeof(char*));
    if (lst == NULL)
    {
        printf ("ERROR@");
        clearlist(lst);
        lst = NULL;
        exit(0);
    }
}

/* Функция nullbuf() присваивает переменной buf значение NULL,
 переменной sizebuf (размер буфера) присваивает значение 0,
 переменной curbuf, указывающей очередную свободную позицию в буфере,
 присваивает значение 0.*/
void nullbuf()
{
    buf = NULL;
    sizebuf = 0;
    curbuf = 0;
}

/* Функция addsym()добавляет очередной символ в буфер в позицию curbuf ,
после чего переменная curbuf увеличивается на 1. Если буфер был пуст,
то он создается. Если размер буфера превышен, то он увеличивается на константу SIZE,
 заданную директивой define. */
void addsym()
{
    if (curbuf > sizebuf - 1)
        buf = realloc(buf, sizebuf+=SIZE); /* увеличиваем буфер при необходимости */
    if (buf == NULL)
    {
        printf("ERROR#");
        clearlist(lst);
        lst = NULL;
        exit(0);
    }
    buf[curbuf++] = c;
}

/* Функция addword() завершает текущее слово в буфере, добавляя ’\0’ в позицию curbuf
(увеличив, если нужно, буфер), и обрезает память, занимаемую словом, до точного размера;
затем добавляет слово в список в позицию curlist, после чего значение curlist увеличивается на 1.
Если список был пуст, то он создается. Если размер списка превышен, то он увеличивается на константу SIZE. */
void addword()
{
    if (curbuf > sizebuf-1)
        buf = realloc(buf, sizebuf+=1); /* для записи ’\0’ увеличиваем буфер при необходимости */
    if (buf == NULL)
    {
        printf("ERROR*");
        clearlist(lst);
        lst = NULL;
        exit(0);
    }
    buf[curbuf++] = '\0';
    /*выравниваем используемую память точно по размеру слова*/
    buf = realloc(buf, sizebuf = curbuf);
    if (buf == NULL)
    {
        printf("ERROR^");
        clearlist(lst);
        lst = NULL;
        exit(0);
    }
    if (curlist > sizelist-1)
        lst = realloc(lst, (sizelist+=SIZE)*sizeof(*lst)); /* увеличиваем массив под список при необходимости */
    if (buf == NULL)
    {
        printf("ERROR&");
        clearlist(lst);
        lst = NULL;
        exit(0);
    }
    lst[curlist++] = buf;
}

void printlist(char **lst)
{
    int k, i;
    if (strncmp(lst[0],"$",1)==0)
    {
        i=1;
        printf("Length of list = %d\n",sizelist - 2 );
    }
    else
    {
        i=0;
        printf("Length of list = %d\n", sizelist - 1);
    }

    if ((strcmp(lst[0],"$")==0) && (strcmp(lst[1],getenv("HOME")) != 0) && (strcmp(lst[1],getenv("SHELL")) != 0) && (strcmp(lst[1], str_EUID) != 0) && (strcmp(lst[1],getenv("USER")) != 0))
    {
        printf("$\n");
    }
    for (k = i; k < sizelist - 1; k++)
    {
        if(strcmp(lst[k],"\\")==0 && k < sizelist - 2)
        {
            printf("%s\n", lst[k+1]);
            k++;
        }
        else if (strcmp(lst[k],str_EUID)==0)
        {
            printf("%d\n",number);
        }
        else
        {
            printf("%s\n",lst[k]);
        }
    }

}

/* Обозначение symset означает любой символ, кроме пробела, табуляции,
перевода строки и специальных символов (>, >>), и не конец файла (EOF). */
int symset(int c)
{
    return c != '\n' && c != ' ' && c != '"' && c != '\t' && c != '>' && c !='\\' && c != EOF && c != '<' && c != '&' && c != '|' && c != ';' && c != '(' && c != ')' && c != '/' && c != '.' && c != '"' && c != '#';
}

void change_lst(char **lst, int sizelist)
{
    int i = 0;
    if (strncmp(lst[i],"$HOME",5) == 0)
    {
        strcpy(lst[i], getenv("HOME"));
        /*printf("%s\n", getenv("HOME"));*/
    }
    if (strncmp(lst[i],"$SHELL",6) == 0)
    {
        strcpy(lst[i], getenv("SHELL"));
        /*printf("%s\n", getenv("SHELL"));*/
    }
    if (strncmp(lst[i],"$EUID",5) == 0)
    {
        strcpy(lst[i],str_EUID);
        number=getuid();
    }
    if (strncmp(lst[i],"$USER",5) == 0)
    {
        strcpy(lst[i], getenv("USER"));
        /*printf("%s\n", getenv("USER"));*/
    }
    i++;
    while(lst[i] != NULL)
    {
        if ((strcmp(lst[i - 1], "\\") != 0))
        {
            if (strncmp(lst[i],"$HOME",5) == 0)
            {
                strcpy(lst[i], getenv("HOME"));
                /*printf("%s\n", getenv("HOME"));*/
            }
            if (strncmp(lst[i],"$SHELL",6) == 0)
            {
                strcpy(lst[i], getenv("SHELL"));
                /*printf("%s\n", getenv("SHELL"));*/
            }
            if (strncmp(lst[i],"$EUID",5) == 0)
            {
                strcpy(lst[i],str_EUID);
                number=getuid();
            }
            if (strncmp(lst[i],"$USER",5) == 0)
            {
                strcpy(lst[i], getenv("USER"));
                /*printf("%s\n", getenv("USER"));*/
            }
        }
        i++;
    }
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;; ВСЕ ФУНКЦИИ ДЛЯ ПЕРВОГО ЭТАПА

typedef enum {Start, Word, Greater, Double_Sslash, Greater2, Lattice, Newline, Underthan, Ampersent, Ampersent2, Or, Or2, Stop, Comma, Lbkt, Rbkt, Sslash, Dot, Quote} vertex;
vertex start(); //
vertex word(); //
vertex double_Sslash();
vertex greater(); //
vertex greater2(); //
vertex newline(); //
vertex underthan();
vertex ampersent();
vertex ampersent2();
vertex or();
vertex or2();
vertex comma();
vertex lbkt();
vertex rbkt();
vertex sslash();
vertex dot();
vertex lattice();
vertex quote(); //
struct tree *New_inf, *inf, *next_inf;
int main()
{
    vertex V=Start;
    null_list();
    c = getchar();
    //printf("00/n");
    while(1)
        switch(V)
        {
        case Start:
            V=start();
            break;
        case Word:
            V=word();
            break;
        case Greater:
            V=greater();
            break;
        case Greater2:
            V=greater2();
            break;
        case Newline:
            V=newline();
            break;
        case Underthan:
            V= underthan();
            break;
        case Ampersent:
            V = ampersent();
            break;
        case Double_Sslash:
            V = double_Sslash();
            break;
        case Ampersent2:
            V = ampersent2();
            break;
        case Or:
            V=or();
            break;
        case Or2:
            V=or2();
            break;
        case Comma:
            V= comma();
            break;
        case Lbkt:
            V=lbkt();
            break;
        case Rbkt:
            V= rbkt();
            break;
        case Lattice:
            V= lattice();
            break;
        case Sslash:
            V=sslash();
            break;
        case Dot:
            V=dot();
            break;
        case Quote:
            V=quote();
            break;
        case Stop:
            exit(0);
            break;
        }
}
vertex start()
{
    int i = 0, k = 0, k1, k2;
    //char **lst_1;
    //lst_1 = NULL;
    int count = 0;
    if(c==' '||c=='\t')
    {
        c=getchar();
        return Start;
    }
    else if (c == EOF)
    {
        return Stop;
    }
    else if (c=='\n')
    {
        if(lst != NULL) //;; ?Y?•?§???????® ???Y?????z?s
        {
            count = count_lst(lst);
            k1 = kol_sticks(lst);
            k2 = kol_semicolon(lst);
            //k3 = kol_amp(lst);
            if(k1 == 0 && k2 == 0)
            {
                change_lst(lst, sizelist);
                printlist(lst);
                //lst = reverse(lst, count);
                inf = Analys_List(lst);
                k = 0;
                Print_tree(inf, k);
                Clear(inf);
                nullbuf();
            }
            else if (k2 == 0)
            {
                k=0;
                lst = reverse(lst, count);
                inf=paralell(lst, k);
                k1=0;
                k=0;
                if(inf != NULL)
                {
                    Print_tree(inf, k);
                    Clear(inf);
                    inf=NULL;
                }
            }
            else if (k1 == 0)
            {
                k=0;
                lst = reverse(lst, count);
                inf = semicolon(lst, k);
                k2=0;
                k=0;
                if(inf != NULL)
                {
                    Print_tree(inf, k);
                    Clear(inf);
                    inf=NULL;
                }
            }
        }
        return Newline;
    }
    else
    {
        if(c == '"')
        {
            return Quote;
        }
        else if(c == '#')
        {
            return Lattice;
        }
        else if(c == '\\')
        {
            return Double_Sslash;
        }
        else
        {

            char cprev=c;
            addsym();
            c=getchar();
            return ((cprev == '>'))? Greater: ((cprev == '|'))? Or: ((cprev == '&'))? Ampersent: ((cprev == ';'))? Comma: ((cprev == '<'))? Underthan: ((cprev == '('))? Lbkt: ((cprev == ')'))? Rbkt: /*((cprev == '$'))? Dollar:*/ ((cprev == '/'))? Sslash: ((cprev == '.'))? Dot: ((cprev == '"'))? Quote: Word;
        }
    }
}

vertex word()
{
    if(symset(c))
    {
        addsym();
        c=getchar();
        return Word;
    }
    else if (c == '\\')
    {
        double_Sslash();
        return Word;
    }
    else
    {
        addword();
        termlist();
        nullbuf();
        return Start;
    }
}



vertex greater()
{
    if(c=='>')
    {
        addsym();
        c=getchar();
        return Greater2;
    }
    else
    {
        addword();
        nullbuf();
        return Start;
    }
}

vertex greater2()
{
    addword();
    nullbuf();
    return Start;
}

vertex newline()
{
    c=getchar();
    return Start;
}

vertex underthan()
{
    if ((c == '<'))
    {
        addsym();
        c = getchar();
        return Underthan;
    }
    else
    {
        addword();
        nullbuf();
        return Start;
    }
}

vertex ampersent()
{
    if (c == '&')
    {
        addsym();
        c = getchar();
        return Ampersent2;
    }
    else
    {
        addword();
        nullbuf();
        return Start;
    }
}

vertex ampersent2()
{
    addword();
    nullbuf();
    return Start;
}

vertex or()
{
    if(c == '|')
    {
        addsym();
        c = getchar();
        return Or2;
    }
    else
    {
        addword();
        nullbuf();
        return Start;
    }

}

vertex or2()
{

    addword();
    nullbuf();
    return Start;

}

vertex comma()
{
    if ((c == ';'))
    {
        addsym();
        c = getchar();
    }
    else
    {
        addword();
        nullbuf();
        return Start;
    }
    return Comma;
}

vertex lbkt()
{
    if ((c == '('))
    {
        addsym();
        c = getchar();
    }
    else
    {
        addword();
        nullbuf();
        return Start;
    }
    return Lbkt;
}

vertex rbkt()
{
    if ((c == ')'))
    {
        addsym();
        c = getchar();
    }
    else
    {
        addword();
        nullbuf();
        return Start;
    }
    return Rbkt;
}

vertex sslash()
{
    if ((c == '/'))
    {
        addsym();
        c = getchar();
    }
    else
    {
        addword();
        nullbuf();
        return Start;
    }
    return Sslash;
}

vertex dot()
{
    if ((c == '.'))
    {
        addsym();
        c = getchar();
    }
    else
    {
        addword();
        nullbuf();
        return Start;
    }
    return Dot;
}

vertex quote()
{
    c = getchar();
    while(c != '"')
    {
        addsym();
        c = getchar();
    }
    addword();
    nullbuf();
    c = getchar();
    return Start;
}

vertex lattice()
{
    while(c != '\n')
    {
        c = getchar();
    }
    return Start;
}

vertex double_Sslash()
{
    if (sizebuf == 0)
    {
        addsym();
        addword();
        nullbuf();
    }
    c = getchar();
    addsym();
    c = getchar();
    if (c == ' ')
    {
        addword();
        nullbuf();
        c = getchar();
    }
    return Start;
}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; 2 ЭТАП
int k_amp = 0, flag = 0, k_in_1 = 0, k_out_1 = 0, k_out_2 = 0;

struct tree *Create_inf() // N????·???°?????µ ???µN€?µ???°
{
    struct tree *New_inf;
    New_inf = malloc(sizeof(struct tree));
    New_inf->argv = NULL;
    New_inf->infile = NULL;
    New_inf->outfile = NULL;
    New_inf->count_r = 0;
    New_inf->count_w = 0;
    New_inf->flag = 0;
    New_inf->count = 0;
    New_inf->pipe = NULL;
    New_inf->next=NULL;
    New_inf->background = 0;
    return New_inf;
}

void add_arg(struct tree *inf, char *str, int k) // функция копирования слова из одного списка в другой
{
    inf->argv = realloc(inf->argv,(k+1) * sizeof(char*));
    inf->argv[k-1] = str;
    inf->argv[k] = NULL;
}

int kol_amp(char **lst) // функция для подсчета кол-ва амперсантов
{
    int x = 0;
    int i = 0;
    while (lst[i] != NULL)
    {
        if (strcmp(lst[i], "&")==0)
        {
            x++;
        }
        i++;
    }
    return x;
}

char **reverse(char **lst, int count)
{
    int i = 0;
    char *b;
    for (i=0; i< count / 2; i++)
    {
        b = lst[i];
        lst[i] = lst[count - i - 1];
        lst[count - i - 1] = b;
    }
    /*for (i=0; i < count; i++) printf("%s ",lst[i]);
    printf("\n");*/
    return lst;
}

void make_shift(int n)
{
    while(n--)
        putc(' ', stderr);
}

void kol_rediraction(char **lst,int *k1,int *k2, int *k3)  // функция для подсчета кол-ва потокового ввода, вывода и добавления информации в конец файла
{
    int x, y, z, i;
    i = x = y = z = 0;
    while (lst[i]!=NULL)
    {
        if (strcmp(lst[i],"<")==0)
        {
            x++;
        }
        if (strcmp(lst[i],">")==0)
        {
            y++;
        }
        if (strcmp(lst[i],">>")==0)
        {
            z++;
        }
        i++;
    }
    (*k1)=x;
    (*k2)=y;
    (*k3)=z;
}

void make_tree(char **lst, struct tree *inf) // построение дерева
{
    int k, i = 0;
    k=1;
    while(lst[i]!=NULL)
    {
        add_arg(inf, lst[i], k);
        i++;
        k++;
    }
    inf->count = k - 1;
}

struct tree *Analys_List(char **lst)
{
    struct tree *inf;
    int k1, k2, k3, k4, k_amp, k, i;
    k1 = k2 = k3 = k_amp = k = k4 = i = 0;
    kol_rediraction(lst, &k1, &k2, &k3);
    k_amp = kol_amp(lst);
    //printf("%d", k_amp);
    inf = Create_inf();
    if(k_amp == 1)
    {
        inf->background = k_amp;
    }
    else if(k_amp > 1)
    {
        printf("ERROR!");
        //inf=NULL;
        return inf;
    }
    inf->count_r = k1;/* < */
    k4= k2 + k3;
    inf->count_w = k4;/* > >> */
    if (k1 > 1 || k4 > 1)
    {
        printf("Problems with files \n");
        Clear(inf);
        return inf;
    }
    if (k1 == 0 && k2 == 0 && k3 == 0)  // если не встретели ни одной стрелки
    {
        if (k_amp == 0)  // и не встретили амперсант(он может быть только один)
        {
            make_tree(lst, inf);
        }
        else if (k_amp==1)
        {
            k = 1;
            i=0;
            while(strcmp(lst[i], "&") != 0)
            {
                if (lst[i]==NULL)
                {
                    break;
                }
                add_arg(inf, lst[i], k);
                k++;
                i++;
            }
        }
        return inf;
    }
    if ((k1 == 1 && k4 == 0))  //если встретили < и не встретили ни > ни >>
    {
        k = 1;
        inf->flag = 1;
        while (strcmp(lst[i], "<" ) != 0)
        {
            add_arg(inf, lst[i], k);
            k++;
            i++;
        }
        //printf("%s\n", lst[i]); отладочный вывод
        inf->count=k - 1;
        if (lst[i + 1] == NULL)
        {
            printf("Problems with files\n");
            Clear(inf);
            return inf;
        }
        i++;
        if (lst[i + 1] != NULL)
        {
            printf("Problems with files \n");
            Clear(inf);
            return inf;
        }
        //printf("%s\n",lst[i]); отладочный вывод
        inf->infile = lst[i];
        return inf;
    }
    if ((k1 == 0 && k4 == 1))
    {
        k=1;
        inf->flag = 2;
        if (k2 == 1)
        {
            while (strcmp(lst[i], ">") != 0)
            {
                add_arg(inf, lst[i], k);
                k++;
                i++;
            }
            inf->count = k - 1;
        }
        else
        {
            while (strcmp(lst[i], ">>") != 0)
            {
                add_arg(inf, lst[i], k);
                k++;
                i++;
            }
            inf->count = k - 1;
        }
        if (lst[i + 1] == NULL)
        {
            printf("Problems with files\n");
            Clear(inf);
            return inf;
        }
        i++;
        if (lst[i + 1] != NULL)
        {
            printf("Problems with files \n");
            Clear(inf);
            return inf;
        }
        inf->outfile = lst[i];
        return inf;
    }
    if (k1 == 1 && k4 == 1)
    {
        k=1;
        while(lst != NULL)
        {
            if ((strcmp(lst[i], ">") == 0) || (strcmp(lst[i], ">>") == 0) || (strcmp(lst[i], "<") == 0))
            {
                inf->count = k - 1;
                break;
            }
            add_arg(inf, lst[i], k);
            k++;
            i++;
        }
        if (strcmp(lst[i], "<")==0) // первый символ
        {
            inf->flag = 1;
            if (lst[i + 1] != NULL)
            {
                inf->infile = lst[i + 1];
            }
            else
            {
                printf("Problems with files \n");
                Clear(inf);
            }
        }
        else
        {
            if (lst[i + 1] != NULL)
            {
                inf->flag = 2;
                inf->outfile = lst[i + 1];
            }
            else
            {
                printf("Problems with files \n");
                Clear(inf);
                return inf;
            }
        }
        i++;
        if ((strcmp(lst[i], ">") == 0) || (strcmp(lst[i], ">>") == 0) || (strcmp(lst[i], "<") == 0))
        {
            printf("Problems with files \n");
            Clear(inf);
            return inf;
        }
        i++;
        if (lst[i + 1] == NULL)
        {
            printf("Problems with files \n");
            Clear(inf);
            return inf;
        }
        if (strcmp(lst[i], "<")==0) // второй символ
        {
            if (lst[i + 1] != NULL)
            {
                inf->infile = lst[i + 1];
                i++;
            }
            else
            {
                printf("Problems with files \n");
                Clear(inf);
            }
        }
        else if((strcmp(lst[i], ">") == 0) || (strcmp(lst[i], ">>") == 0))
        {
            if (lst[i + 1] != NULL)
            {
                inf->outfile = lst[i + 1];
                i++;
            }
            else
            {
                printf("Problems with files tt \n");
                Clear(inf);
            }
        }
        else
        {
            printf("Problems with files \n");
            Clear(inf);
        }
        return inf;
    }
    return inf;
}

int kol_sticks(char **lst)
{
    int k, i;
    i = k = 0;
    while(lst[i] != NULL)
    {
        if (strcmp(lst[i],"|") == 0)
        {
            k++;
        }
        i++;
    }
    return k;
}

int kol_semicolon(char **lst)
{
    int k, i;
    i = k = 0;
    while(lst[i] != NULL)
    {
        if (strcmp(lst[i],";") == 0)
        {
            k++;
        }
        i++;
    }
    return k;
}

struct tree *semicolon(char **lst,int k)
{
    char **lst_1;
    lst_1 = NULL;
    next_inf = NULL;
    inf = NULL;
    int i = 0;
    if (strcmp(lst[k],";")==0)
    {
        printf("Error\n");
        Clear(inf);
        Clear_next(next_inf);
        inf=NULL;
        return inf;
    }
    while(1)
    {
        if (lst[k]==NULL)
        {
            next_inf=NULL;
            break;
        }
        i=0;
        while(lst[k] != NULL)
        {
            if(strcmp(lst[k],";")==0)
            {
                k++;
                break;
            }
            i++;
            lst_1 = realloc(lst_1, SIZE * sizeof(*lst));
            lst_1[i - 1] = lst[k];
            //printf("%s\n",lst_1[i-1]);
            k++;
        }
        lst_1 = reverse(lst_1, i);
        next_inf = Analys_List(lst_1);
        next_inf->next=inf;
        inf=next_inf;
        for(i=0; lst_1[i]!=NULL; i++)
        {
            lst_1[i]=malloc(0);
        }
        lst_1=NULL;
    }
    return inf;
}

struct tree *paralell(char **lst,int k)
{
    char **lst_1;
    lst_1 = NULL;
    next_inf = NULL;
    inf = NULL;
    int i = 0;
    if (strcmp(lst[k],"|")==0)
    {
        printf("Error\n");
        Clear(inf);
        Clear_next(next_inf);
        inf = NULL;
        return inf;
    }
    while(1)
    {
        if (lst[k]==NULL)
        {
            next_inf=NULL;
            break;
        }
        i=0;
        while(lst[k] != NULL)
        {
            if(strcmp(lst[k],"|")==0)
            {
                k++;
                break;
            }
            i++;
            lst_1 = realloc(lst_1, SIZE * sizeof(*lst));
            lst_1[i - 1] = lst[k];
            //printf("%s\n",lst_1[i-1]);
            k++;
        }
        lst_1 = reverse(lst_1, i);
        next_inf = Analys_List(lst_1);
        next_inf->pipe=inf;
        inf=next_inf;
        for(i=0; lst_1[i]!=NULL; i++)
        {
            lst_1[i]=malloc(0);
        }
        lst_1=NULL;
    }
    return inf;
}


void Clear_next(struct tree *inf)
{
    if (inf!=NULL)
    {
        int i=0;
        if (inf->argv!=NULL)
        {
            for (i=0; inf->argv[i]!=NULL; i++)
            {
                inf->argv[i]=malloc(0);
            }
        }
        if (inf->infile!=NULL)
        {
            free(inf->infile);
        }
        if (inf->outfile!=NULL)
        {
            free(inf->outfile);
        }
        inf->argv=NULL;
        inf->infile=NULL;
        inf->outfile=NULL;
        inf->count_r=0;
        inf->count_w=0;
        inf->flag=0;
        inf->pipe=NULL;
        inf->next=NULL;
        inf->count=0;
        inf->background=0;
    }
    inf=NULL;
}

void Clear(struct tree *inf)
{
    int i;
    clearlist(lst);
    lst = NULL;
    i=0;
    if (inf!=NULL)
    {
        while(inf->argv[i]!=NULL)
        {
            free(inf->argv[i]);
            inf->argv[i]=malloc(0);
            i++;
        }
        inf->argv = NULL;
        inf->infile = NULL;
        inf->outfile = NULL;
        inf->count_r = 0;
        inf->count_w = 0;
        inf->flag = 0;
        inf->count = 0;
        inf->background = 0;
        inf->pipe = NULL;
    }
}

void Print_tree(struct tree *inf,int shift)
{
    if (inf == NULL)
    {
        return;
    }
    if(inf != NULL)
    {
        int i;
        if (inf->argv==NULL)
        {
            make_shift(shift);
            printf("inf-> argv = NULL \n");
        }
        else
        {
            i=0;
            while(inf->argv[i]!=NULL)
            {
                make_shift(shift);
                printf("inf -> argv :");
                printf("%s\n",inf->argv[i]);
                i++;
            }
        }
        make_shift(shift);
        if (inf->infile==NULL)
        {
            printf("inf-> infile = NULL \n");
        }
        else
        {
            printf("inf-> infile = %s\n",inf->infile);
        }
        make_shift(shift);
        if (inf->outfile==NULL)
        {
            printf("inf-> outfile = NULL \n");
        }
        else
        {
            printf("inf->outfile = %s\n",inf->outfile);
        }
        make_shift(shift);
        printf("inf->count_reading = %d \n",inf ->count_r);
        make_shift(shift);
        printf("inf->count_writing_begin = %d \n",inf ->count_w);
        make_shift(shift);
        printf("inf->flag = %d \n",inf ->flag);
        make_shift(shift);
        printf("inf->background = %d\n",inf->background);
        make_shift(shift);
        printf("inf->count = %d\n",inf->count);
        make_shift(shift);
        if (inf->pipe==NULL)
        {
            printf("In Pipe : NULL \n");
        }
        else
        {
            printf("In Pipe : \n");
            Print_tree(inf->pipe,shift+5);
        }
        make_shift(shift);
        if (inf->next==NULL)
        {
            printf("In Next : NULL \n");
        }
        else
        {
            printf("In Next: \n");
            Print_tree(inf->next,shift+5);
        }
    }
}
