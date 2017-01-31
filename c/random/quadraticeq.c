/*
* Author: Alexander Day
* 
* Description: This program makes use of the quadratic equation to find the roots of x
*              when given the coefficients from the standard quadratic form. It finds the
*              noncomplex roots and returns a single statement when roots are complex.
*	      
* Input: The user is required to analyze the standard quadratic form in order to extract 
*        the appropriate coefficients a, b, and c. (An example is shown in program as an aid)
*
* Output: The lines "This program finds the roots of x from the standard form, ax^2+bx+c."
*                   "It utilizes the quadratic equation and only returns noncomplex roots."
*                   "When the roots are complex, it returns 'x has two complex roots'."
*                   "Please enter the following coefficients:"
*                   "a:"
*                   "b:"
*                   "c:"
*         Then, based on the value of the discriminant, the program prints on of the following.
*                   "For this equation, x has two real roots: x1, x2."
*                   "For this equation, x has one real root: x."
*                   "For this equation, x has two complex roots."
*                   
*/
#include <stdio.h>
#include <math.h>

//Function Declarations
void two_roots (float coeffB, float sqr_discr, float divisor);
void one_root (float coeffB, float divisor);
void complex_roots (void);

int main (void)
{

//Local Declarations
   float a;//coefficient a
   float b;//coefficient b
   float c;//coefficient c
   float discr;//discriminant
   float d;//divisor
   float e;//sqrt discriminant
    
//Prompt user and enter coefficients.
   printf("\nThis program finds the roots of x from the standard form, ax^2+bx+c.");
   printf("\nIt utilizes the quadratic equation and only returns noncomplex roots.");
   printf("\nWhen the roots are complex, it returns 'x has two complex roots'.");
   printf("\nPlease enter the following coefficients:");
   printf("\na: ");
   scanf("%f", &a);
   printf("b: ");
   scanf("%f", &b);
   printf("c: ");
   scanf("%f", &c);

//Coefficients are now in a, b, c. Calculate variables for optimization.
   discr = b*b-4*a*c;//discriminant
   d = 2 * a;//divisor
   e = sqrtf (discr);//sqrt divisor

//Calculations to perform are determined
   if (discr >= 0)
      {
       if (discr == 0)
         {
          one_root (b, d);
         }//if 
       
       else
         { 
          two_roots (b, e, d);
         }//else
      }//if

   else
       complex_roots ( );

   return 0;
} // main

//Function Definitions
/************************ two_roots ***************************************
This function finds and prints the roots for x when the discriminant is
greater than zero.
***************************************************************************/
void two_roots (float coeffB, float sqr_discr, float divisor)
{
 float x1;
 float x2;
 x1 = ((-coeffB) + sqr_discr) / divisor;
 x2 = ((-coeffB) - sqr_discr) / divisor;
 printf("For this equation, x has two real roots: %.2f,%.2f\n", x1, x2);
 return;
}//two_roots

/************************ one_root ****************************************
This function finds and prints the root of x when the discriminant is equal
to zero.
***************************************************************************/
void one_root (float coeffB, float divisor)
{
 float x;
 x = -coeffB / divisor;
 printf("For this equation, x has one real root: %.2f\n", x);
 return;
}//one_root

/************************ complex_roots ***********************************
This function prints that "x has complex roots."
***************************************************************************/
void complex_roots (void)
{
 printf("For this equation, x has two complex roots.\n");
 return;
}
//complex_roots
