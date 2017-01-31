
#include <stdio.h>

char shift(int amt, char *oldChar);

int main(int argc, char *argv[])
{ 
  int i,j;
  char startChar = 'A';
  for(i=0;i<26;i++){
 	printf("\n|SHIFT BY %d|\n",i);
  	for(j=0;j<26;j++) 	   
		startChar = shift(i, &startChar);
		}
  printf("\n");
  return 0;
}

char shift(int amt, char *oldChar){
     char newChar = *oldChar + amt;
     if(newChar > 'Z')
        newChar -= 26;
     printf(" %c ", newChar);
     return newChar;
	}
