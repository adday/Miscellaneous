
#include <stdio.h>

//Summation i=k to n
void sum(){
   int n,k;
   printf("summation| k -> n\nk: ");
   scanf("%d", &k);
   printf("n: ");
   scanf("%d", &n);
   printf("sum: %d\n", (n*(n+1))/2 - (k*(k-1))/2);
   return;
}

int main(int argc, char *argv[])
{
  sum();
  return 0;
}

 
