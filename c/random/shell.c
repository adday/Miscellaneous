
#include <stdio.h>

int main(int argc, char *argv[])
{ 
  int i = 0, x = 0;
  for(i=0;i<1000;i++){
	x = (71*i)-84;
	if((x % 41) == 0){
	printf("i is:%d ", i);
	return 0;
	}
		
}
  return 0;
}

