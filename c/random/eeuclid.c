
#include <stdio.h>

int main(int argc, char *argv[])
{ 
  int i,j;
  for(i=1;i<2000;i++)
	for(j=-1000;j<2000;j++)
		if((423*i + 191*j) == 1){
			printf("i: %d j: %d\n", i, j);
			return;}
  return 0;
}

