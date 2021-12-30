/* Task 2.3 */

#include <stdio.h>

int Fibonacci_iterative (int fib_index)
  {
  //f0 = 0, f1 = 1, f2 = 1
  int i = fib_index;
  int fi = 0;
  int fi_1 = 1;
  int tmp = 0;
  
  while (i > 0)
    {
    tmp = fi + fi_1;
    
    fi = fi_1;
    fi_1 = tmp;
    
    i--;
    }
    
  return fi;    
  }

int Fibonacci_recursive (int fib_index)
  {
  //f0 = 0, f1 = 1, f2 = 1
  if (fib_index == 0) return 0;
  if (fib_index == 1) return 1;
  return (Fibonacci_recursive (fib_index - 1) 
        + Fibonacci_recursive (fib_index - 2));
  }


int main()
  {
  //printf ("%d", Fibonacci_iterative(3));
  //printf ("%d", Fibonacci_recursive(3));
  
  int tmp = 0;
  
  while (!feof(stdin))
    {
    if (scanf ("%d", &tmp) == 1)
      {
      printf ("%d \n", Fibonacci_iterative(tmp));
      printf ("%d \n", Fibonacci_recursive(tmp));
      }
    }
  
  return 0;
  }
