/*
* Program Name: HW6
*
* Author: Alexander Day
* 
* Description: This program reads an integer and prints its digits in reversed order.
* 
* Input: 1 integer value.
*
* Output: The lines "This program reads an integer and then prints it in reverse."
*                   "Please enter an integer: "
*                   "The original number is :'num'"
*                   "The reversed number is :'reversedNum'"
*/

#include <stdio.h>

int main (void)

{
int num;

printf("This program reads an integer and prints it in reverse\n");
printf("Please enter an integer: ");

scanf("%d", &num);

printf("The original number is: %d\n", num);
printf("The reversed number is: ");

while (num != 0)
 {
  printf("%d", num%10);
  num/=10;
 }//while

printf("\n");

return 0;

} // main