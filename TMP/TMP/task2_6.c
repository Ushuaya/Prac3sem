#include <stdio.h>
#include <stdlib.h>
#define DEBUG_MODE 0

//TREE DESCRIPTION
typedef struct tree_unit
  {
  int key;
  struct tree_unit * left;
  struct tree_unit * right;
  } Tree_node;
typedef Tree_node * Tree_link;


//FUNCTION PROTOTYPES
Tree_link add_elem (int this_int, Tree_link this_link);
Tree_link del_elem (int this_int, Tree_link this_link);
void search_elem (int this_int, Tree_link this_link); 
void all_print (Tree_link this_link, int level); //debug function

int main(void) 
  {
  Tree_link t_link = NULL;      
      
  // Our aim is to create a search tree
  // For this we need to read the symbols
  // Until we meet + - ?
  
  char tmp_string [1024] = {};
  char tc;//trash_char
  
  int nnin = 0; //non-negative-integer-number
  
  while (!feof(stdin))
    {
    scanf ("%c", &tc);
    while (((tc == ' ') || (tc == '\t') || (tc == '\n'))&&(!feof(stdin)))  
      {
      scanf ("%c", &tc);
      }
      
    if (feof(stdin)) return 0;
    //we finished it, so tc = + - ?
    //we need to read the number (nnin) then switch
    scanf ("%d", &nnin);
    
    if (DEBUG_MODE == 1) printf ("\n BEFORE SWITCH \n");    
    if (DEBUG_MODE == 1) all_print (t_link, 1); 
    if (DEBUG_MODE == 1) printf ("\n"); 
    
    switch (tc)
      {
      case '+': if (DEBUG_MODE == 1) printf ("\n -TIME TO ADD -\n");
                t_link = add_elem (nnin, t_link);
      
                if (DEBUG_MODE == 1) printf ("done");
                break;
      case '-': 
                if (DEBUG_MODE == 1) printf ("\n -TIME TO DELETE -\n");
                t_link = del_elem (nnin, t_link);
                if (DEBUG_MODE == 1) printf ("\n CHECK WHAT WE DELETE %d \n", t_link -> key);
                break;
      case '?': search_elem (nnin, t_link);
                //For debug
                if (DEBUG_MODE == 1)  all_print (t_link, 1);
                break;
      default: printf ("trash char = %c", tc);
               printf ("trash char = %d", (int)tc);
      }
    
    if (DEBUG_MODE == 1) printf ("\n");    
    if (DEBUG_MODE == 1) all_print (t_link, 1); 
    if (DEBUG_MODE == 1) printf ("\n");   
    }
  
  return 0;
  }
  
  
Tree_link add_elem (int this_int, Tree_link this_link)
  {
  Tree_link tmp_link = this_link;
  Tree_link tmp_link2 = this_link;
  
  if (DEBUG_MODE == 1) printf ("pointer %d \n", (int)((void*)(this_link)) );
  
  //IF IT HAS 0 ELEM
  if (tmp_link == NULL)
    {
    tmp_link = malloc (1 * sizeof (Tree_node));
    tmp_link -> left = NULL;
    tmp_link -> right = NULL;
    tmp_link -> key = this_int;
    
    if (DEBUG_MODE == 1) printf (" pointer %d \n", (int)((void*)(this_link)) );    
    return tmp_link;
    }
  
  //1 ELEM
  if (tmp_link -> key == this_int)  
    {
    if (DEBUG_MODE == 1) printf (" pointer %d \n", (int)((void*)(this_link)) );    
    return this_link;
    }
  else if (tmp_link -> key > this_int)  
    {
    tmp_link = tmp_link -> left;
    }
  else 
    {
    tmp_link = tmp_link -> right;   
    }
  
  //>= 2 ELEM
  while (tmp_link != NULL)   
    {
    if (tmp_link -> key == this_int)  
      {
      if (DEBUG_MODE == 1) printf (" pointer %d \n", (int)((void*)(this_link)) );    
      return this_link;
      }
    else if (tmp_link -> key > this_int)  
      {
      tmp_link2 = tmp_link;
      tmp_link = tmp_link -> left;
      }
    else 
      {
      tmp_link2 = tmp_link;
      tmp_link = tmp_link -> right;   
      } 
    }
    
    
  if (DEBUG_MODE == 1) all_print (this_link, 1);
  
  //If we are here, it is needed to add elem as a child of tmp_2
  if (tmp_link2 -> key > this_int)  
      {
      tmp_link2 -> left = malloc (1 * sizeof (Tree_node));
      tmp_link = tmp_link2 -> left;
      tmp_link -> left = NULL;
      tmp_link -> right = NULL;
      tmp_link -> key = this_int;
      
      if (DEBUG_MODE == 1) all_print (this_link, 1);
      
      if (DEBUG_MODE == 1) printf ("pointer %d \n", (int)((void*)(this_link)) );
      return this_link;
      }
    else 
      {
      tmp_link2 -> right = malloc (1 * sizeof (Tree_node));
      tmp_link = tmp_link2 -> right;
      tmp_link -> left = NULL;
      tmp_link -> right = NULL;
      tmp_link -> key = this_int;
      
      //if (DEBUG_MODE == 1) all_print (this_link, 1);
      
      if (DEBUG_MODE == 1) printf ("pointer %d \n", (int)((void*)(this_link)) );
      return this_link;
      }
  }
  
  
  
Tree_link del_elem (int this_int, Tree_link this_link)
  {
  Tree_link tmp_link = this_link;
  Tree_link tmp1 = this_link;      
  Tree_link tmp2 = this_link; 
  Tree_link tmp_link_par = NULL;//parent of this_link 
  int flag = 0;
      
  // IF IT HAS 0 ELEM
  if (this_link == NULL)
    {
    return this_link;
    }    
  
  // IF IT HAS 1 ELEM
  if (tmp_link -> key == this_int)  
    {
    if (DEBUG_MODE == 1) printf ("1st elem deleting");
    // We have to delete tmp_link 
    if (tmp_link -> right == NULL && tmp_link -> left == NULL) 
      { // it is a leaf
      free (tmp_link);
      return NULL;
      }
    else if (tmp_link -> right == NULL)
      { // has only 1 son
      tmp_link = tmp_link -> left;
      free (this_link);
      return tmp_link;
      }
    else if (tmp_link -> left == NULL)
      { // has only 1 son
      tmp_link = tmp_link -> right;
      free (this_link);
      return tmp_link;
      }
    else 
      { // we need to find the folowwing element
      if (DEBUG_MODE == 1) printf ("\n FOLOWING SEARCHING \n");
      
      tmp1 = tmp_link;
      tmp2 = tmp_link -> right;
      //and then we go left until tmp2 left son = 0
      
      flag = 0;
      while (tmp2 -> left != NULL)
        {
        tmp1 = tmp2;    
        tmp2 = tmp2 -> left;    
        
        flag = 1;    
        }
      //So we stopped and tmp2 is the following element
      //tmp1 is the parent of tmp2; we have to delete tmp_link
      if (flag) 
        {
        tmp1 -> left = NULL;
        tmp2 -> left = tmp_link -> left;
        tmp2 -> right = tmp_link -> right;
        free (tmp_link);
        return tmp2;
        }
      else 
        {
        tmp2 -> left = tmp_link -> left;
        tmp2 -> right = tmp_link -> right -> right;
        free (tmp_link);
        return tmp2;  
        }
      }
    }
  else if (tmp_link -> key > this_int)  
    {
    tmp_link_par = tmp_link;
    tmp_link = tmp_link -> left;
    }
  else 
    {
    tmp_link_par = tmp_link;
    tmp_link = tmp_link -> right;    
    }
  
  while (tmp_link != NULL)   
    {
    if (tmp_link -> key = this_int)  
      {
      if (DEBUG_MODE == 1) printf ("TESTCASE"); 	
      break;
      }
    else if (tmp_link -> key > this_int)  
      {
      tmp_link_par = tmp_link;
      tmp_link = tmp_link -> left;
      }
    else 
      {
      tmp_link_par = tmp_link;
      tmp_link = tmp_link -> right;   
      } 
    }
  
  if (tmp_link == NULL) return this_link; 
  //Else we have to delete tmp_link unit
  
  if (tmp_link -> right == NULL && tmp_link -> left == NULL) 
    { // it is a leaf
    if (tmp_link_par -> left = tmp_link) tmp_link_par -> left = NULL;
    else tmp_link_par -> right = NULL;
   
    if (DEBUG_MODE == 1) 
      {
      printf ("\n LEAF DELETED \n");    
      printf ("pointer %d \n", (int)((void*)(this_link)) );
      }

    free (tmp_link);
    return this_link;
    }
  else if (tmp_link -> right == NULL)
    { // has only 1 son
    if (tmp_link_par -> left == tmp_link) tmp_link_par -> left = tmp_link -> left;
    else tmp_link_par -> right = tmp_link -> left;
      
    free (tmp_link);
    return this_link;
    }
  else if (tmp_link -> left == NULL)
    { // has only 1 son
    if (DEBUG_MODE == 1) printf ("123-2 2");
    
    if (tmp_link_par -> left == tmp_link) tmp_link_par -> left = tmp_link -> right;
    else tmp_link_par -> right = tmp_link -> right;
      
    free (tmp_link);
    return this_link;
    }
  else 
    { // we need to find the folowwing element
    tmp1 = tmp_link;
    tmp2 = tmp_link -> right;
    //and then we go left until tmp2 left son = 0
    
    flag = 0;  
    while (tmp2 -> left != NULL)
      {
      tmp1 = tmp2;    
      tmp2 = tmp2 -> left;  
      flag = 1;
      }
    //So we stopped and tmp2 is the following element
    //tmp1 is the parent of tmp2; we have to delete tmp_link
      tmp1 -> left = NULL;
      tmp2 -> left = tmp_link -> left;
      tmp2 -> right = tmp_link -> right;
      
      if (tmp_link_par -> left = tmp_link) tmp_link_par -> left = tmp2;
      else tmp_link_par -> right = tmp2;
      
      free (tmp_link);
      return this_link;
      
      
      if (flag) 
        {
        tmp1 -> left = NULL;
        tmp2 -> left = tmp_link -> left;
        tmp2 -> right = tmp_link -> right;
      
        if (tmp_link_par -> left = tmp_link) tmp_link_par -> left = tmp2;
        else tmp_link_par -> right = tmp2;
      
        free (tmp_link);
        return this_link;
        }
      else 
        {
        if (DEBUG_MODE == 1) printf ("+1+2+3-2?2 case"); 	
        	
        tmp2 -> left = tmp_link -> left;
        tmp2 -> right = tmp_link -> right -> right;
      
        if (tmp_link_par -> left = tmp_link) tmp_link_par -> left = tmp2;
        else tmp_link_par -> right = tmp2;
      
        free (tmp_link);
        return this_link; 
        }
    }
    
  
  }
  
void search_elem (int this_int, Tree_link this_link)  
  {
  Tree_link tmp_link = this_link;
  if (this_link == NULL)
    {
    printf ("\n%d no", this_int);
    return;
    }      
  
  while (tmp_link != NULL)   
    {
    if (tmp_link -> key == this_int)  
      {
      printf ("\n%d yes", this_int);
      return;
      }
    else if (tmp_link -> key > this_int)  
      {
      tmp_link = tmp_link -> left;
      }
    else 
      {
      tmp_link = tmp_link -> right;   
      } 
    } 

  printf ("\n %d no", this_int);
  return;
  }
  
void all_print (Tree_link this_link, int level)  
  {
  if (this_link == NULL)
    {
    return;
    }
  else 
    {
    printf (" %d-%d ", this_link -> key, level);    
    all_print (this_link -> left, level + 1);
    all_print (this_link -> right, level + 1);
    }
  }
