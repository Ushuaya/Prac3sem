#include <stdio.h>
#include <stdlib.h>

typedef struct TElem
{
     char word;
     struct TElem *Next;
}TElem;

char mass = 'a';
struct TElem *list, *save;

int main()
{
    printf("Hello!\n");
    /*
     list = (struct TElem*) malloc(sizeof(struct TElem) + 1);
    list->word = mass;
    list->Next = NULL;
     */

    
    if (scanf("%c", &mass) == 1)
    {
        list = (struct TElem*) malloc(sizeof(struct TElem));
        save = list;
        list->word = mass;
        list -> Next = NULL;
    
        while (scanf("%c", &mass) == 1)
        {
            if ((mass != ' ') && (mass != '\n'))
            {
                list->Next = (struct TElem*) malloc(sizeof(struct TElem));
                list = list->Next;
                list->word = mass;
                list -> Next = NULL;
            //printf ("%c\n", list->word);
            }
        }
        
    }
    //list = NULL;
    
    list = save;
    //list = list->Next;
    //printf ("%c\n", list->word);

    printf ("\n");
    
    while (list != NULL)
    {
        printf ("priiint %c\n", list->word);
        list = list->Next;
    }
    
    return 0;
}
