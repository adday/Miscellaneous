/*

* Author: Alexander Day
* 
* Description: This program converts temperatures from Celsius to Fahrenheit or from 
*              Fahrenheit to Celsius. It prompts the user to pick a conversion to perform 
*              and utilizes a function call to perform the conversion. The input temperature
*              is of type float. The program returns an rounded integer as the type for the
*              converted temperature.	
*	      
* Input: 'C'- To perform Celsius to Fahrenheit conversion
*        'F'- To perform Fahrenheit to Celsius conversion
*         Float type value of temperature to be converted
*
* Output: The lines: "This program converts a Celsius temperature to Fahrenheit degrees
*                     or a Fahrenheit temperature to Celsius degrees."
*                    "If you want to convert Celsius to Fahrenheit, please enter C."
*                    "If you want to convert Fahrenheit to Celsius, please enter F."
*                    "Enter C or F: "
*                    "Please enter the temperature in (Fahrenheit/Celsius) degrees."
*                    "The temperature in (Fahrenheit/Celsius) degrees is (convTemp)."
*/

#include <stdio.h>

//Function Declarations
float cel_to_fah (float c);
float fah_to_cel (float f);
int roundNum (float num);

int main (void)
{
//Local Declarations
   float temp;//temperature value input by user
   int convTemp;//temperature once converted and rounded
   char type;//input for initial temperature value, C-Celsius F-Fahrenheit

//Prompt user to enter the desired conversion to be performed
   printf("\nThis program converts a Celsius temperature to Fahrenheit degrees");
   printf("\nor a Fahrenheit temperature to Celsius degrees.\n");
   printf("\nIf you want to convert Celsius to Farenheit, please enter C.");
   printf("\nIf you want to convert Fahrenheit to Celsius, please enter F.");
   printf("\nEnter C or F: ");
   scanf("%c", &type);//User inputs type of conversion to be performed

//Functions now called based on conversion type
if (type == 'C')//Celsius to Fahrenheit
  {
   printf("\nPlease enter the temperature in Celsius degrees: ");
   scanf("%f", &temp);//User inputs temperature value in Celsius 
   convTemp = cel_to_fah (temp);
   printf("\nThe temperature in Fahrentheit degrees is %d.\n", convTemp);
  }//if (type = C)

if (type == 'F')//Fahrenheit to Celsius
  {
   printf("\nPlease enter the temperature in Fahrenheit degrees: ");
   scanf("%f", &temp);//User inputs temperature value in Fahrenheit
   convTemp = fah_to_cel (temp);
   printf("\nThe temperature in Celsius degrees is %d.\n", convTemp);
  }//if (type = F)
 
return 0;
}// main

//Function Definitions
/* =============================== cel_to_fah ================================
   This function calculates Fahrenheit temperature from given Celsius degrees.
*/
float cel_to_fah (float cel)
{
float fah;//Fahrenheit temperature
int fahRound;//Rounded Fahrenheit temperature
fah = (((1.8) * cel) + 32);
fahRound = roundNum (fah);
return (fah);
}//cel_to_fah


/* =============================== fah_to_cel ================================
   This function calculates Celsius temperature from given Fahrenheit degrees.
*/
float fah_to_cel (float fah)
{
float cel;//Celsius temperature
int celRound;//Rounded Celsius temperature
cel = ((0.5556) * (fah-32));
celRound = roundNum (cel);
return (celRound);
}//fah_to_cel


/* =============================== roundNum ==================================
   This function rounds a float number to an integer. If the float part is <0.5
   then it rounds the number down and if the float part is >0.5 it rounds the 
   number up.
*/
int roundNum (float num)
{
    return num < 0 ? num - 0.5 : num + 0.5;
}//roundNum
 
