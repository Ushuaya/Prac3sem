#include <stdio.h>
#include <stdlib.h>

#define DEBUGMODE 1

//ABOUT FILE 
int fd;
FILE * ptrFile;

//ABOUT BUFFER STRING
#define STR_SIZE 20 // THE STR BUF SIZE

//ABOUT WORDS THAT WE READ
#define WORD_QUANTITY  150 // MAX amount of words
#define WORD_MAX_SIZE 20 


//WORK WITH STR IS VERY USEFUL TO BE ORGANISED AS WITH GLOBAL
int tmp_STR_SIZE = STR_SIZE; // if fread < STR SIZE we have to know we have to stop
char str [STR_SIZE] = {};     
int str_position = -1;   
int read_symbols = STR_SIZE;
int END_FLAG = 0; // =1, if the file ended 



/* Описать программу, которая, пока не получен конец файла, выполняет в цикле
следующие действия:
1) cчитывает из stdin очередную строку,
2) преобразует ее в последовательность (список) слов,
3) выводит в stdout полученную последовательность слов в исходном порядке,
4) выводит слова последовательности в лексикографическом порядке.
При выводе в первой строке напечатать длину списка, в каждой последующей –
очередной элемент списка. */

char getsym(void) //only for reading symbols from str
  {
  str_position++;
  //printf ("%d", str_position);
  
  // IS IT THE END OF THE PART????
  if (str_position == tmp_STR_SIZE) 
    { 
    // we need to load new part of the string if it was not last part
    
    if (tmp_STR_SIZE != STR_SIZE)
      {
      //That s the end of file
      END_FLAG = 1; 
      return '\n';    
      }
    
    read_symbols = fread(str, sizeof (char), STR_SIZE, ptrFile);
    tmp_STR_SIZE = read_symbols;
    
    if (tmp_STR_SIZE == 0) 
      {
      END_FLAG = 1;
      return '\n';
      }
      
    str_position = 0;
    return str [0];  
    }
  
  //IF IT IS NOT THE END WE CAN JUST READ
  int debug_var = str [str_position];
  int debug_var_pos = str_position;
  char debug_str [2 * STR_SIZE] = {};
  for (int i = 0; i < STR_SIZE; i++)
    {
    debug_str [i] = str [i];     
    }
  
  if (debug_var == '>')
   {
   ;
   printf ("231020 case");
   }
  return str [str_position]; 
  }
  

//LIST REALLOCATION FUNCTION
//Reallocate This Word List
void RTWL (char *** Word_List_link, int * Word_list_size_link)
  {
  //DEBUG
  //int TMP_WLSL = *Word_list_size_link;
  //static int RTWL_COUNT = 0;
  //RTWL_COUNT++;
  //char * DAV = NULL; //Debug auxilary varuable
  
      
  static char **tmp_list = NULL; 
      
  tmp_list = malloc ((*Word_list_size_link + WORD_QUANTITY) * sizeof (char*));
  for (int i = 0; i < *Word_list_size_link; i++) 
    {
    //DAV = *(      (*Word_List_link) + i * sizeof (char*));
    //*(tmp_list + ((long) i) ) = DAV;
    *(tmp_list + i) = *(      (*Word_List_link) + i);
    }
  *Word_list_size_link += WORD_QUANTITY;
  free (*Word_List_link);
  *Word_List_link = tmp_list; 
  
  return;  
  }  
  
//FIRST STRING BIGGER LEXICOGRAPHICALLY (B > A) (AB > A)
//1 if yes, 0 if no
//if they are equal returns 0
int FSBL (char * first_string, char * second_string)
  {
  int i = 0;
        
  while ((*(first_string + i) != '\0'))
    {
    //if (*(second_string + i * sizeof(char)) == '\0') return 0; 
    if (*(first_string + i) > *(second_string + i)) return 1;  
    if (*(first_string + i) < *(second_string + i)) return 0;  
    
    i++;
    } 
  
  return 0; 
  }
    //TEST STRINGS FOR FSBL
    char str1[] = "|";
    char str2[] = "||";
    

//Count Chars In String
int CCIS (char * str)
  {
  int i = 0;      
          
  while (*(str + i) != '\0') i++;          
          
  return i;
  }

//Count Words In List
int CWIL (char ** List)
  {
  int i = 0;      
          
  while (*(List + i) != NULL) i++;          
          
  return i;
  }


//DEBUG FUNCTIONS
void debug_list_print(char ** Word_List, int Word_list_position)
  {
  printf ("_");
  for (int i = 0; i < Word_list_position; i++)
    {
    //printf ("0");
    printf ("%s\n", *(Word_List + i));
    //printf ("1");
    } 
  printf ("_");    
  return;    
  }
  
//WRITE from_buf_to_list  
void WFBTL(char ** word_list_unit_link, char * word_buf, int word_buf_position)
  {
  *(word_list_unit_link) = malloc ((word_buf_position + 2) * sizeof (char));  
  
  char * word_list_unit = *(word_list_unit_link);
      
  for (int j = 0; j <= word_buf_position; j++) 
    {
    *(word_list_unit + j) = *(word_buf + j);
    }
  *(word_list_unit + (word_buf_position + 1)  ) = '\0';
   
   
  printf ("%s\n", *(word_list_unit_link)); 
  return;    
  }  

//WLL - WORD_LIST_LINK; WLSL - word list size link; WLP - WORDLISTPOSITION 
/*void ADDLIST (char *** WLL, int *WLSL, int *WLP, 
              char * word_buf, int word_buf_position)
  {
  //IF THE LIST ENDS
  if (*WLP == Word_list_size) RTWL (WLL, WLS);
  
  
  WFBTL ((Word_List + Word_list_position), SS, 1);
  *WLP++;   
      
  }*/


int main()
  {
  BEGIN_POINT:      
      
  //printf ("%d", FSBL (str1, str2) );      
     
  //if (DEBUGMODE == 1) printf ("DEBUG POINT 0");       
  ptrFile = fopen ("test.txt", "r");
  
      
  char *auxilary = NULL;  
  char tmp_sym = 0; 
      
  ///If lack of space for word pointers, we ll realloc word_buf 
  char **Word_List = NULL;
  Word_List = malloc (WORD_QUANTITY * sizeof (char*));
  int Word_list_size = WORD_QUANTITY; //for easy reallocation
  int Word_list_position = 0;
    char **tmp_list = NULL;
  
  //If lack of space for word, we ll realloc word_buf
  char *word_buf = NULL; 
  word_buf = malloc (WORD_MAX_SIZE * sizeof (char*));
  int word_buf_size = WORD_MAX_SIZE; // for easy reallocation
  int word_buf_position = 0; 
    // New buffer for reallocation of word_buf
    char *tmp_buf = NULL; 


  char SS[2] = {};
  int SS_Q = 0;
  
  //int WORD_BEGIN = 0; //temporable var for word dividing
  //char this_sym = 0;

  // BEFORE MAIN WE HAVE TO FILL STR
  read_symbols = fread(str, sizeof (char), STR_SIZE, ptrFile);
  tmp_STR_SIZE = read_symbols;
  str_position = -1;
  
  if (tmp_STR_SIZE == 0) 
    {
    END_FLAG = 1;
    }
  
  //if (DEBUGMODE == 1) printf ("DEBUG POINT 1"); 
  
  // MAIN CYCLE
  // Here we read words to word_buf 
  for (word_buf_position = 0; !END_FLAG; word_buf_position++)
    {
    //debug_list_print (Word_List, Word_list_position);      
        
    if (word_buf_position == word_buf_size) 
      {
      //we can not write and we need to reallocate word_buf 
      tmp_buf = malloc ((word_buf_size + WORD_MAX_SIZE) * sizeof (char*));
      for (int i = 0; i < word_buf_size; i++) *(tmp_buf + i) = *(word_buf + i);
      word_buf_size += WORD_MAX_SIZE;
      free (word_buf);
      word_buf = tmp_buf; 
      }
    
    //If we are here, we can write 
    *(word_buf + word_buf_position) = getsym(); 
    tmp_sym = *(word_buf + word_buf_position);
    
    

    switch (tmp_sym)
      {
      case '|': 
      case '&': 
      case '>':
        if (SS_Q && (SS[0] == tmp_sym))
          { //WE CAN WRITE TWO SYMBOLS (\0 will be added by WFBTL)
          if (Word_list_position == Word_list_size) RTWL (&Word_List, &Word_list_size);
          SS[1] = tmp_sym;
          WFBTL ((Word_List + Word_list_position), SS, 1);
          Word_list_position++;  
          SS_Q = 0;
          
          word_buf_position = -1;
          break;
          }
        else if (SS_Q) 
          { //WE HAVE TO WRITE ONE SS
          if (Word_list_position == Word_list_size) RTWL (&Word_List, &Word_list_size);
          WFBTL ((Word_List + Word_list_position), SS, 0);
          Word_list_position++;  
          
          //AND STORE THAT WAS READED
          SS[0] = tmp_sym;  //SS_Q = 1  
          word_buf_position = -1;
          break;
          }
        else  
          {
          if (word_buf_position > 0)
            { //IF THERE IS ANYTHING TO BE WRITTEN 
            if (Word_list_position == Word_list_size) RTWL (&Word_List, &Word_list_size);
            WFBTL ((Word_List + Word_list_position), word_buf, word_buf_position - 1);
            Word_list_position++;               
            }  
            
          SS[0] = tmp_sym;      
          SS_Q = 1;  
          
          word_buf_position = -1;
          }
        break;
  
  
              
      case ';':
      case '<':
      case '(':
      case ')':
        if (SS_Q)
          { //IF SPECIAL SYMBOL WAS SAVED BEFORE
          if (Word_list_position == Word_list_size) RTWL (&Word_List, &Word_list_size);
          WFBTL ((Word_List + Word_list_position), SS, 0);
          Word_list_position++;  
          SS_Q = 0;
          }
        else
          { //IF ANOTHER WORD WAS SAVED BEFORE
          if (word_buf_position > 0)
            {
            if (Word_list_position == Word_list_size) RTWL (&Word_List, &Word_list_size);
            WFBTL ((Word_List + Word_list_position), word_buf, word_buf_position - 1);
            Word_list_position++; 
            }
          }
      
        //WRITING THE SYMBOL ITSELF (SS EMPTY, SS_Q = 0)
        if (Word_list_position == Word_list_size) RTWL (&Word_List, &Word_list_size);
        SS[0] = tmp_sym;
        WFBTL ((Word_List + Word_list_position), SS, 0);
        Word_list_position++;  
        
        word_buf_position = -1;
        break;


      case '\n':
      case '\0':      
      case  ' ':
        if (SS_Q)
          {
          if (Word_list_position == Word_list_size) RTWL (&Word_List, &Word_list_size);
          WFBTL ((Word_List + Word_list_position), SS, 0);
          Word_list_position++;  
          SS_Q = 0;
          }
        else 
          {
          if (word_buf_position > 0)
            {
            if (Word_list_position == Word_list_size) RTWL (&Word_List, &Word_list_size);
            WFBTL ((Word_List + Word_list_position), word_buf, word_buf_position - 1);
            Word_list_position++; 
            }
          }
        
        word_buf_position = -1;
        break;
        
     
        
      default: 
        //printf ("_DC_");
        if (SS_Q)
          {
          if (Word_list_position == Word_list_size) RTWL (&Word_List, &Word_list_size);
          WFBTL ((Word_List + Word_list_position), SS, 0);
          Word_list_position++;  
          SS_Q = 0;
          }
        
        *(word_buf + word_buf_position) = tmp_sym;
        break;
      }
      
    //printf ("%s\n", word_buf);   
    }
    
    
  *(Word_List + Word_list_position) = NULL;
  
  
  
  
  //And now lets check what we have
  printf ("\n _________________________ \n");
  for (int i = 0; i < Word_list_position; i++)
    {
    printf ("%s\n", *(Word_List + i));
    } 
  
  //printf ("%d", FSBL (str1, str2) );
  
  //SORTING THE MASSIV
  for (int i = 0; i < Word_list_position; i++)
    {
    for (int j = i + 1; j < Word_list_position; j++)
      {
      if (FSBL (*(Word_List + i), *(Word_List + j))) 
        {
        auxilary = *(Word_List + i);
        *(Word_List + i) = *(Word_List + j);
        *(Word_List + j) = auxilary;
        }
        
      //debug_list_print (Word_List, Word_list_position);    
      }
    } 

  //debug_list_print (Word_List, Word_list_position);
  printf ("--------------------------------------------------");
  printf ("%d\n", CWIL(Word_List));
  for (int i = 0; i < Word_list_position; i++)
    {
    printf ("%s\n", *(Word_List + i));
    //printf ("_%d", (int)*(*(Word_List + i * sizeof (char*))));
    } 
  
  
  
  
  // In the end it is needed to free the memory
  for (int i = 0; i < Word_list_position; i++)
    {
    free ( *(Word_List + i ));
    } 
  free (word_buf);
  free (Word_List);
  
  fclose (ptrFile);
  
  //goto BEGIN_POINT;
  return 0;
  }
