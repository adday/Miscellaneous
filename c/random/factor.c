
#include <stdio.h>

int main(int argc, char *argv[])
{ 
  int i, N = 12191;
  for(i=2;i<100;i++){
	if((N % i ) == 0)
		printf("i is: %d ", i);

		
}
  return 0;
}

