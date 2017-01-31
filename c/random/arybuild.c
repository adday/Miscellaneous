/*
* Author: Alexander Day
*
* Description: This program builds an array. It then sorts it and displays it to the user. 
*              Then, it accepts a new value to place into the array. Then it displays the 
*              new array sorted to the user.
*
* Input: Array size, Initial array values, New value to place into array
*
* Output: The lines "This program builds an array of integers and displays it to the user."
*                   "Then, it accepts another integer to be placed into the array."
*                   "The array is then displayed with the new integer inserted."
*                   "Please enter the size of the array to build: 'size'"
*                   "Ok, let's build an array with 'size' integers."
*                   "Please enter the integers in nondecreasing order."
*                   "Please enter # 'n': "
*                   "This is the array you entered: 'ary'"
*                   "Please enter a new integer to be inserted in the array: 'x'"
*                   "This is the array with the 'x' inserted: 'array'"
*/

#include <stdio.h>

int main (void)
{
//Local Declarations
int size;
int ary[size+1];
int i;
int j;
int x;//New value to be input into array

//Statements
printf("This program builds an array of integers and displays it to the user.");
printf("\nThen, it accepts another integer to be placed into the array.");
printf("\nThen, the array is displayed with the new integer inserted.");
printf("\nPlease enter the size of the array to build: ");

scanf("%d", &size);

printf("Ok, let's build an array with %d integers.\n", size);
printf("Please enter the integers in nondecreasing order.\n");

for (i=0; i<size; i++)
{
  printf("Please enter #%d: ",i+1);
  scanf("%d", &ary[i]);
}//for

printf("This is the array you entered: ");

for (i=0;i<size;i++)
  printf("%d ", ary[i]);

printf("\nPlease enter a new integer to be inserted into the array: ");

scanf("%d", &x);

i=0;

while (x > ary[i] && i < size)//Locates place to input x
  i++;

j=size;

while (j >= i)//Shifts array to make room for x
{
  ary[j]=ary[j-1];
  j--;
}  

ary[i]=x;//Inserts x

printf("This is the array with %d inserted: ", x);

for(i=0;i<size+1;i++)
  printf("%d ", ary[i]);

return 0;
}// main
