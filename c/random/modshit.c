
#include <stdio.h>

int main(int argc, char *argv[])
{ 
  int i;
  for(i=1;i<2000;i++){
		if( ((78467*i-1) % 104801) == 0){
			printf("x is: %d", i);
			return 0;
			}
	}//end for
  return 0;
}

