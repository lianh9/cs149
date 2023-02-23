/**
 * Description: This module implements max and min numbers.
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date: 02/23/2023
 * Creation date: 02/23/2023
 **/

#include <stdio.h>

/* function declaration */
int MaxNumber(int num1, int num2, int num3, int num4);
int MinNumber(int num1, int num2, int num3, int num4);


/**
 * Main fuction takes 4 integers as input, calls function MaxNumber()
   and MinNumber() to calculate the max and min, and outputs max and min.
 * Assumption: n/a
 * Input parameters: n/a
 * Returns: 0
**/
int main()
{
    int num1; int num2; int num3; int num4;
    int max; int min;
    scanf("%d %d %d %d", &num1, &num2, &num3, &num4);
    max  = MaxNumber(num1, num2, num3, num4);
    min  = MinNumber(num1, num2, num3, num4);
    printf("Maximum is %d\n", max);
    printf("Minimum is %d\n", min);

    return 0;
}
/**
 * This function calculates the max
 * Assumption: n/a
 * Input parameters: int num1, int num2, int num3, int num4
 * Returns: an integer
**/

int MaxNumber(int num1, int num2, int num3, int num4){
    int max;
    max = (num1 > num2) ? num1 : num2;
    max = (max > num3) ? max : num3;
    max = (max > num4) ? max : num4;

    return max;
}
/**
 * This function calculates the min
 * Assumption: n/a
 * Input parameters: int num1, int num2, int num3, int num4
 * Returns: an integer
**/
int MinNumber(int num1, int num2, int num3, int num4){
    int min;
    min = (num1 < num2) ? num1 : num2;
    min = (min < num3) ? min : num3;
    min = (min < num4) ? min : num4;

    return min;
}
