/* Power function that can work for float x and negative y*/
#include<stdio.h>
 
float power(float x, int y)
{
    float temp;
    if(y == 0)
       return 1;
    temp = power(x, y/2);       
    if (y%2 == 0)
        return temp*temp;
    else
    {
        if(y > 0)
            return x*temp*temp;
        else
            return (temp*temp)/x;
    }
}  
 
/* Program to test function power */
int main()
{
    float a;
    printf("Power function a^b");
    printf("\nEnter a: ");
    scanf("%f", &a);
    int b;
    printf("Enter b: ");
    scanf("%d", &b);
    printf("Result: %f \n", power(a, b));
    return 0;
}