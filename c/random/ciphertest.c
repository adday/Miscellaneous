
#include <stdio.h>

int main(int argc, char *argv[])
{ 
  printf("Enter #: ");
  int num, i, shift, count = 0;
  scanf("%d", &num);
  shift = num;
  for(i = 0; i < 100;i++){
     num+=shift;
     if(num >  25)
        num = num - 26;
     printf("%d\n", num);
     count++;
     if(num == shift){
       printf("%d",count);
       break;
	}
} 
  return 0;
}

