/*
* *
* Author: Alexander Day
*
* Description: This program builds an array and tests it values to see if two distinct
*              elements sum to a user specified value.
*
* Input: Array size, Array values, Value to test sum against
*
* Output: The lines "This program builds an array of a size determind by the user."
*                   "It then checks the array to see if any two distinct elements sum"
*                   "to a user specified value."
*                   "Please enter the size of the array you wish to build: 'size'"
*                   "Please enter the number you want to check the sum against: 'test'"
*                   "Please enter element # 'n'"
*                   Either one of the following.
*                   "The result of the test is TRUE."
*                   "The result of the test is FALSE."
*/
#include <stdio.h>

int main (void)
{
//Local Declarations
int size;
int ary [size];
int test;
int sum;
int i;
int j;

//Statements
printf("This program builds an array of a size determined by the user.");
printf("\nIt then checks the array to see if any two distinct elements sum");
printf("\nto a user specified value.");
printf("\nPlease enter the size of the array you wish to build: ");
scanf("%d", &size);
printf("Please enter the number you want to check the sum against: ");
scanf("%d", &test);

for (i=0; i<size; i++)
{
    printf("Please enter element #%d: ",i+1);
    scanf("%d", &ary[i]);
}//for

for (i=size-1;i>0;i--)
{
 for (j=0;j<i;j++)
  {
   sum = ary[i] + ary[j];
   if (sum == test)
        {
         printf("The result of the test is TRUE.\n");
         return 0;
        }
  }//for
}//for

printf("The result of the test is FALSE.\n");
return 0;
} // main
