// PA8 Assignment - main.c
// Author: Alexander Day
// Date:   4/7/2015
// Class:  CS270
// Email:  dayalex6@gmail.com

#include <stdio.h>

void reverse(char *s);
char translate(char c);

int main() {
	char buf[80];
	fgets(buf,sizeof(buf),stdin);
	buf[strlen(buf)-1] = '/0'
	reverse(*buf);	
   
	return 0;
}

void reverse(char *s){

}

char translate(char c){
return c;
}
