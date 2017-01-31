#include <stdio.h>

int main(){ 
  printf("gcd(a,b)\na: ");
  int a,b;
  scanf("%d",&a);
  printf("b: ");
  scanf("%d",&b);
  printf("gcd(%d,%d)=%d\n", a, b, gcd(a,b));
  return 0;
}

int gcd(int a,int b){//using Euclidean algorithm
   int dividend = a, divisor = b, quotient, remainder;
   while(1){
	quotient = dividend / divisor;
        remainder = dividend % divisor;
        if(remainder == 0)
           return divisor;
        dividend = divisor;
        divisor = remainder;	
	}
   //return -1;//error
} 



