#include <stdio.h>

int main(){ 
  printf("modinv(a,p)\na: ");
  int a,p;
  scanf("%d",&a);
  printf("p: ");
  scanf("%d",&p);
  printf("%d inverse mod %d = %d\n", a, p, modinv(a,p));
  return 0;
}

//calculate a inverse mod p
int modinv(int a,int pr){
   //using Euclidean algorithm calculate sequence of multipliers k
   int di = a, d = pr, q, r;
   int k[50];
   int i = -1;//use to kill off first 0
   while(1){
	q = di / d;
        r = di % d;
        if(r == 0)
           break;//multipliers all initialized at this point
        di = d;
        d = r;
	if(i != -1)
	   k[i] = q;	
        i++;
	}
   //calculate a inverse 
   int j, p[50];
   p[0] = 0;
   p[1] = 1;
   for(j=2;j<i+2;j++){
	p[j] = (p[j-2] - (p[j-1] *  k[j-2])) % pr;
	if(p[j]<0)
		p[j] = p[j] + pr;
	}
   int ainv = p[i+1];
   return ainv;	
} 


