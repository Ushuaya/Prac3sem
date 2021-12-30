#include <stdio.h>
#include <stdlib.h>
#include "function.h"

#define SIZE 16

void clearlist(){
     int i;
     sizelist=0;
     curlist=0;
     if (lst==NULL) return;
     for (i=0; lst[i]!=NULL; i++)
        free(lst[i]);
     free(lst);
     lst=NULL;
}
void null_list(){
     sizelist=0;
     curlist=0;
     lst=NULL;
}
//////////////
void termlist(){
     if (lst==NULL) return;
     if (curlist>sizelist-1)
        lst=realloc(lst,(sizelist+1)*sizeof(*lst));

     if (lst==NULL){
        printf ("Error");
        clearlist();
        exit(0);
    }



     lst[curlist]=NULL;
     /*выравниваем используемую под список память точно по размеру списка*/
     lst=realloc(lst,(sizelist=curlist+1)*sizeof(*lst));
     if (lst==NULL){
        printf("Error");
        clearlist();
        exit(0);
     }
}
void nullbuf(){
     buf=NULL;
     sizebuf=0;
     curbuf=0;
}
//////////
void addsym(){
     if (curbuf>sizebuf-1)
        buf=realloc(buf, sizebuf+=SIZE); /* увеличиваем буфер при
     необходимости */
     if (buf==NULL){
        printf("Error");
        clearlist();
        exit(0);
     }
     buf[curbuf++]=c;
}
////////
void addword(){
     if (curbuf>sizebuf-1)
        buf=realloc(buf, sizebuf+=1); /* для записи ’\0’ увеличиваем буфер
     при необходимости */
     if (buf==NULL){
        printf("Error");
         clearlist();
        exit(0);
     }

     buf[curbuf++]='\0';
     /*выравниваем используемую память точно по размеру слова*/
     buf=realloc(buf,sizebuf=curbuf);
     if (buf==NULL){
        printf("Error");
         clearlist();
        exit(0);
     }


     if (curlist>sizelist-1)
        lst=realloc(lst, (sizelist+=SIZE)*sizeof(*lst)); /* увеличиваем
     массив под список при необходимости */
     if (buf==NULL){
         printf("Error");
         clearlist();
         exit(0);
     }
     lst[curlist++]=buf;
}
//////////
void printlist(){
     int i;
     if (lst==NULL) return;
    printf("Length list: %d/n", sizelist-1);
     for (i=0; i<sizelist-1; i++)
        printf("%s\n",lst[i]);
     sorting();
     printf("Sorting: \n");
     for (i=0; i<sizelist-1; i++)
        printf("%s\n",lst[i]);
}
//////////
int symset(int c){
     return
     c!='\n' &&
     c!=' ' &&
     c!='\t' &&
     c!='>' &&
    c!= EOF &&
     c!='|' &&
     c!='&' &&
     c!=';' &&
     c!='<' &&
     c!='(' &&
     c!=')' &&
     c!='$' &&
     c!='_' &&
     c!='/' &&
     c!= '.';
}

void sorting(){
  int i,j;
  for(i=0; i<sizelist-2; i++)
       for(j=0; j<sizelist-i-2; j++)
           if(strcmp(lst[j],lst[j+1])>0) {
             char *tmp=lst[j];
             lst[j]=lst[j+1];
             lst[j+1]=tmp;
            }
}

int strcmp (const char *s1, const char *s2){
    for( ; *s1==*s2; ++s1,++s2)
        if (*s2=='\0')
            return 0;
    return *s1 - *s2;
}
/////////////
