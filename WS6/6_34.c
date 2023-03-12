/**
 * Description: This module implements Multiples of ten in an array
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date: 3/11/2023
 * Creation date:3/11/2023
 **/
#include <stdio.h>
#include <stdbool.h>

//function declaration
bool IsArrayMult10(int inputVals[], int numVals);
bool IsArrayNoMult10(int inputVals[], int numVals);
/**
 * This main function reads user inputs
   then pass user inputs to function IsArrayMult10() and IsArrayNoMult10
   to determine if the input integers are Multiples of 10 or not or mixed
 * Assumption: The number of Inputs not exceed 20 integers
 * Input parameters: n/a
 * Returns: an integer(0 - program normal exit, non 0 - program error)
**/

int main()
{
    int inputVals[20];
    int numVals;
    printf("Enter the number of values : \n");
    scanf("%d", &numVals);
    printf("Enter %d integers separate by space : \n", numVals);
    int i = 0;

    while(i < numVals)
    {
        int temp;
        scanf("%d", &temp);
        inputVals[i] = temp;
        i++;
    }

    if(IsArrayMult10(inputVals, numVals))
    {
        printf("all mutiples of 10\n");
    }
    else if(IsArrayNoMult10(inputVals, numVals))
    {
        printf("no mutiples of 10\n");
    }
    else
    {
        printf("mixed values\n");
    }

    return 0;
}
/**
 * This function determine if the inputVals are mutiples of 10
 * Assumption: The size of inputVals not exceed 20 integers
 * Input parameters: inputVals, numVals
 * Returns: true or false
**/
bool IsArrayMult10(int inputVals[], int numVals)
{
    for(int i = 0; i < numVals; i++)
    {
        if(inputVals[i] % 10 != 0)
        {
            return false;
        }
    }
    return true;

}
/**
 * This function determine if the inputVals are not mutiples of 10
 * Assumption: The size of inputVals not exceed 20 integers
 * Input parameters: inputVals, numVals
 * Returns: true or false
**/
bool IsArrayNoMult10(int inputVals[], int numVals)
{
    for(int i = 0; i < numVals; i++)
    {
        if(inputVals[i] % 10 == 0)
        {
            return false;
        }
    }
    return true;

}




