#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define masiver char[40];

typedef struct TElem
{
    char *word;
     struct TElem *Next;
} TElem;
struct TElem *list;

//int spr_cmp (char*str1, char*str2);

struct TElem *create_list(char *Ftext)
{
    struct TElem *save = NULL;
    char *mass;
    //int i;

    mass = strtok(Ftext, " '\v''\t'");
    //printf("%lu\n", sizeof(mass));
    if (mass == NULL)
    {
        printf("BAD\n");
        return save;
    }
    if (mass != NULL)
    {
        list = (struct TElem*) malloc(sizeof(struct TElem));
        save = list;
        list->word = mass;
        list -> Next = NULL;
    
        while (mass != NULL)
        {
                
            mass = strtok(NULL, " ");
            if (mass != NULL)
            {
                list->Next = (struct TElem*) malloc(sizeof(struct TElem));
                list = list->Next;
                list->word = mass;
                list -> Next = NULL;
                //printf ("%c\n", list->word);
            }
        }
    }
    list = save;
    
    return save;
}



void pirnt_list (struct TElem * Flist)
{
    printf("\n");
    printf ("Your new list is: \n");
    while (Flist != NULL)
    {
        printf ("%s ", Flist->word);
        //printf("%lu\n", sizeof(list->word));
        Flist = Flist->Next;
    }
    //printf ("\n");
}

int str_cmp (char *str1, char *str2)
{
    while ((*str1 != '\0') && (*str1 != '\0'))
    {
        if (*str1 != *str2)
            return 0;
        str1 += sizeof(char);
        str2 += sizeof(char);
    }
    // ВОПРОС!!!!!
    if ( ((*str1 == '\0') && (*str2 == '\0')) || ((*str1 == '\0') && (*str2 == '\n')) )
        return 1;
    else
        return 0;
}


struct TElem *delete_list_elem(struct TElem * Flist)
{
    if (Flist == NULL)
    {
        printf("BAD\n");
        goto extraend;
    }
    struct TElem *elem1 = Flist;
    struct TElem *elem2 = Flist;
    char *cmpr2 = NULL;
    elem1 = Flist;
    
    while (Flist != NULL)
    {
        cmpr2 = Flist->word;
        Flist = Flist->Next;
    }
    //printf("Cmpr: %s\n", cmpr2);
    Flist = elem1;
    if (elem2->Next != NULL)
    {
        while (elem2->Next->Next != NULL)
        {
            elem2 = elem2->Next;

            //ВОПРОС!!!
            //printf(" cmpr: %s|", cmpr2);
            //printf(" elem2: %s|", elem2->word);
            if ( str_cmp(elem2->word, cmpr2))
            {
                elem1->Next = elem2->Next;
                free(elem2);
                elem2 = elem1;
            }
            else
                elem1 = elem1->Next;
        }
    }
    
    if ((str_cmp(Flist->word, cmpr2)) && (Flist->Next != NULL))
    {
        Flist = Flist->Next;
        free (Flist);
    }
extraend:
    return Flist;
}


int main()
{
    char text[200];
    printf("Hello!\n");
    
    printf("Input text: \n");
    fgets(text, 200, stdin);
    
    list = create_list(text);
    list = delete_list_elem(list);
    pirnt_list(list);

    return 0;
}
