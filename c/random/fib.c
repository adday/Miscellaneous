
#include <stdio.h>

int main(int argc, char *argv[])
{
   int n;
   printf("Returns nth Fibonacci number. \nEnter n: ");
   scanf("%d", &n);
   printf("Fibonacci number %d is %d \n",n, fib(n));
   return 0;
}
    
int fib(int n){
   if(n==0)
     return 0;
   else if(n == 1)
     return 1; 
   else
     return (fib(n-1) + fib(n-2));
}
