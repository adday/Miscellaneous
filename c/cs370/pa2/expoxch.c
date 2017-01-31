//expoxch.c
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int expoxch(char* X, char* N);
int factorial(int n);

int Usage(){
	printf("Usage: ./expox <x value (float <1)> < Number of terms n (int)>");
	return 1;
}

int main(int argc, char *argv[])
{   
  if(argc != 3)
	return Usage();
  return expoxch(argv[1],argv[2]);
}

int expoxch(char* X, char* N){
  double x = atof(X);
  if(!(x>0) || !(x<1)){
	printf("The value of x is outside of the range (0,1)\n");
	return 1;}
  int n = atoi(N);
  double ex = 1;
  int i;
  //calculate e^x using series expansion up to n terms
  for(i = 1;i < n;i++)
	ex += pow(x,i)/factorial(i);
  //check if approximation is close to actual
  double diff = fabs(exp(x) - ex);	
  if(diff > 1){
	printf("Approximation is not good\n");
	return 1;	
	}
  printf("For x = %g the actual value of e^x is %1.7f\n", x, exp(x));
  printf("Child (PID = %d): For x = %g the first %d terms yield %1.7f\n", (int)getpid(), x, n, ex);
  return 0;
}


//iterative factorial function
//returns n!
int factorial(int n){
   int i, fact = 1;
   for(i = 1; i <= n; i++)
	fact = fact * i;
   return fact;
}
