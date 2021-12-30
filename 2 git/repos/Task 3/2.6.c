//
//  main.c
//  Task 2.6
//
//  Created by Ivan on 10.10.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int number;           // поле данных
    struct Node *left;  // левый потомок
    struct Node *right; // правый потомок
} Node;

typedef struct Node* Tree;

/*
struct tnode * addnode(int x, tnode *tree) {
  if (tree == NULL) { // Если дерева нет, то формируем корень
    tree =new tnode; // память под узел
    tree->number = x;   // поле данных
    tree->left =  NULL;
    tree->right = NULL; // ветви инициализируем пустотой
  }else  if (x < tree->number)   // условие добавление левого потомка
    tree->left = addnode(x,tree->left);
  else    // условие добавление правого потомка
    tree->right = addnode(x,tree->right);
  return(tree);
}
*/

Tree add_bin_node(Tree Ftree, int digit)
{
    //if (Ftree != NULL && Ftree->right != NULL)
        //printf("And? %i %i\n", Ftree->number, Ftree->right->number);
    if (Ftree == NULL)
    {
        //printf("add: %i\n", digit);
        Ftree = (Tree) malloc (sizeof (Node));
        Ftree->number = digit;
        //printf("New: %i\n", Ftree->number);
        Ftree->left = NULL;
        Ftree->right = NULL;
    }
    else
    {
        if (digit == (Ftree->number))//printf("%i %i\n", Ftree->number, digit);
        {
            return Ftree;
        }
        else
        {
            if (digit < (Ftree->number))
            {
                //printf("left\n");
                Ftree->left = add_bin_node(Ftree->left, digit);
            }
            else
            {
               // printf("right\n");
                Ftree->right = add_bin_node(Ftree->right, digit);
            }
        }
    }
        
    
    //printf("Done\n");
    return Ftree;
}

void treeprint(Node *p)
{
  if(p != NULL)
  {
    //printf("Hi\n");
    treeprint(p->left);
    printf("%i ", p->number);
    treeprint(p->right);
  }
}

void delete_hard_case (struct Node** x, struct Node** y)
{
    Tree p;
    if ((*x)->right == NULL)
    {
        (*y)->number = (*x)->number;
        p = (*x);
        (*x) = (*x)->left;
        free(p);
    }
    else delete_hard_case(&((*x)->right), y);
}



void delete_bin_node (struct Node** Ftree, int digit)
{
    Tree p;
    //!!!!
    if (*Ftree != NULL)
    {
        //printf("Number: %i", (*Ftree)->number);
        if ( ((*Ftree)->number) > digit)
        {
            delete_bin_node((&((*Ftree)->left)), digit);
        }
        else
        {
            if((*Ftree)->number < digit)
            {
                delete_bin_node((&(*Ftree)->right), digit);
            }
            else
            {
                if ((*Ftree)->left == NULL)
                {
                    //printf("Del1: %i\n", (*Ftree)->number);
                    p = (*Ftree);
                    (*Ftree) = (*Ftree)->right;
                    //printf("Del1: %i\n", (*Ftree)->number);

                    //free(p);
                }
                else
                {
                    if ((*Ftree)->right == NULL)
                    {
                        //printf("Del2: %i\n", (*Ftree)->number);

                        p = (*Ftree);
                        (*Ftree) = (*Ftree)->left;
                        //printf("Del2: %i\n", (*Ftree)->number);
                        //free(p);
                    }
                    else delete_hard_case((&(*Ftree)->left), Ftree);
                }
            }
        }
    

        }
 
}


/*
Tree delete_bin_node (Tree Ftree, int digit)
{
    //Tree p;
    if (Ftree == NULL)
        return 0;
    else
    {
        //printf("Number: %i", (*Ftree)->number);
        if ( Ftree->number > digit)
        {
            printf("Numberleft: %i", Ftree->number);
            Ftree = delete_bin_node(Ftree->left, digit);
        }
        else
        {
            if(Ftree->number < digit)
            {
                printf("Numberright: %i", Ftree->number);
                Ftree = delete_bin_node(Ftree->right, digit);
            }
            else
            {
                if (Ftree->left == NULL)
                {
                    printf("Del1: %i\n", Ftree->number);
                    //p = (*Ftree);
                    Ftree = Ftree->right;
                    //printf("Del1: %i\n", Ftree->number);
                    return Ftree;
                    //free(p);
                }
                else
                {
                    if (Ftree->right == NULL)
                    {
                        printf("Del2: %i\n", Ftree->number);

                        //p = (*Ftree);
                        Ftree = Ftree->left;
                        printf("Del2: %i\n", Ftree->number);
                        return Ftree;
                        //free(p);
                    }
                }
            }
        }
    }
    return 0;
}
 */
int find_bin_node_tmp (Node* Ftree, int digit)
{
    if (Ftree != NULL)
    {
        if (Ftree->number == digit)
        {
            return 1;
        }
        return (find_bin_node_tmp(Ftree->left, digit) || find_bin_node_tmp(Ftree->right, digit));
    }
    return 0;
}

void find_bin_node(Node* Ftree, int digit)
{
    int a = 0;
    a = find_bin_node_tmp(Ftree, digit);
    //printf("tmp_fnc: %d\n", a);
    
    if (a == 0)
    {
        printf("NO");
    }
    else
        printf("YES");
    /*
    int *git = NULL;
    if (Ftree != NULL)
    {
        if (Ftree->number == digit)
        {
            printf("YES");
            git = (int*)malloc(sizeof(int));
            *git = 0;
        }
        find_bin_node(Ftree->left, digit);
        find_bin_node(Ftree->right, digit);

    }
    if (git == NULL)
        printf("NO");
     */
}

 

int main()
{
    int number;
    char sign = '\0';
    Node *tree = NULL;
   
    
    printf("Hello!\n");
    
    /*
    while (i>0)
    {
        printf("in a: \n");
        scanf("%i", &a);
        tree = add_bin_node(tree, a);
        treeprint(tree);
        printf("\n");
        i--;
        
        //printf("in b: \n");
        //scanf("%i", &b);
        //tree = delete_bin_node(tree, b);
        //treeprint(tree);
        //printf("\n");
    }
    printf("in b: \n");
    scanf("%i", &b);
    delete_bin_node(&tree, b);
    treeprint(tree);
    
    printf("in find: \n");
    scanf("%i", &find);
    find_bin_node(tree, find);
    
    printf("\n");
     */
    printf("Input sequnce: ");
    while( scanf("%c", &sign) == 1)
    {
        //printf("%c", sign);
        if (sign == '+')
        {
            scanf("%i", &number);
            //printf("num: %d\n", number);
            tree = add_bin_node(tree, number);
        }
        if (sign == '-')
        {
            scanf("%i", &number);
            //printf("num: %d\n", number);
            delete_bin_node(&tree, number);

        }
        if (sign == '?')
        {
            scanf("%i", &number);
            //printf("num: %d\n", number);
            find_bin_node(tree, number);
            printf("\n");

        }
        if (sign == 'p')
        {
            printf("\nYour tree: ");
            treeprint(tree);
            printf("\n");
        }

        scanf("%c", &sign);
    }

    return 0;
}
