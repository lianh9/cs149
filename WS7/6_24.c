/**
 * Description: This module implements Swapping variables.
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date: 03/12/2023
 * Creation date: 03/12/2023
 **/
#include <stdio.h>

/* function declaration */
void SwapValues(int* userVal1, int* userVal2, int* userVal3, int* userVal4);

/**
 * Main function takes 4 integers as input, pass the 4 integers by pointer
   to function SwapValues() to performing swap procedure
 * Assumption: n/a
 * Input parameters: n/a
 * Returns: 0
**/
int main()
{
    int userVal1;
    int userVal2;
    int userVal3;
    int userVal4;

    printf("Enter 4 integers separate by space:\n");
    scanf("%d %d %d %d", &userVal1, &userVal2, &userVal3, &userVal4);

    SwapValues(&userVal1, &userVal2, &userVal3, &userVal4);
    printf("%d %d %d %d\n", userVal1, userVal2, userVal3, userVal4);

    return 0;
}

/**
 * This function swap the 1st value with second and 3rd with fourth
 * Assumption: n/a
 * Input parameters: int* userVal1, int* userVal2, int* userVal3, int* userVal4
 * Returns: n/a
**/
void SwapValues(int* userVal1, int* userVal2, int* userVal3, int* userVal4)
{
    int temp;

    temp = *userVal1;
    *userVal1 = *userVal2;
    *userVal2 = temp;

    temp = *userVal3;
    *userVal3 = *userVal4;
    *userVal4 = temp;
}

