
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// char2int
// Converts from a character to an integer digit
// if character '0'..'9' convert to 0..9
// else if character 'A'..'F' convert to 10..15
// else converts to -1
int char2int(char digit){
  int num;
  if(digit == '0')
    num = 0;
  else if(digit == '1')
    num = 1;
  else if(digit == '2')
    num = 2;
  else if(digit == '3')
    num = 3;
  else if(digit == '4')
    num = 4;
  else if(digit == '5')
    num = 5;
  else if(digit == '6')
    num = 6;
  else if(digit == '7')
    num = 7;
  else if(digit == '8')
    num = 8;
  else if(digit == '9')
    num = 9;
  else if(digit == 'A')
    num = 10;
  else if(digit == 'B')
    num = 11;
  else if(digit == 'C')
    num = 12;
  else if(digit == 'D')
    num = 13;
  else if(digit == 'E')
    num = 14;
  else if(digit == 'F')
    num = 15;
  else 
    num = -1;
  return num;
}//end char2int

// int2char
// Converts from an integer digit to a character
// if integer 0..9 convert to '0'..'9'
// else if integer 10..15 convert to 'A'..'F'
// else convert to 'X'
char int2char(int num){
  char digit;
  if(num == 0)
    digit = '0';
  else if(num == 1)
    digit = '1';
  else if(num == 2)
    digit = '2';
  else if(num == 3)
    digit = '3';
  else if(num == 4)
    digit = '4';
  else if(num == 5)
    digit = '5';
  else if(num == 6)
    digit = '6';
  else if(num == 7)
    digit = '7';
  else if(num == 8)
    digit = '8';
  else if(num == 9)
    digit = '9';
  else if(num == 10)
    digit = 'A';
  else if(num == 11)
    digit = 'B';
  else if(num == 12)
    digit = 'C';
  else if(num == 13)
    digit = 'D';
  else if(num == 14)
    digit = 'E';
  else if(num == 15)
    digit = 'F';
  else 
    digit = 'X';
  return digit;
}//end int2char

//int2ascii
// Convert integer to string in specified base and print
// 2 <= base <= 16
void int2ascii(int value, int base){ 
  if(value < base)
    printf("%c", int2char(value));
  else{
    int2ascii(value/base, base);
    printf("%c", int2char(value % base));}
}//end int2ascii

//ascii2int
// Convert string in specified base to integer and print
// 2 <= base <= 16
void ascii2int(char *ascii, int base){
  int i;
  int j;
  int num = 0;
  int templen;
  int mult;
  int length = (int)strlen(ascii);
  templen = length;
  for(j = 0;j < templen-1;j++){
    mult = 1;
    for(i = length-1; i > 0; i--)//Multiplies base to get position multiplier
       mult*=base;
    length--;
    num+= char2int(ascii[j]) * mult;}
  num+= char2int(ascii[j]);
  printf("%d", num); 
}//end ascii2int


