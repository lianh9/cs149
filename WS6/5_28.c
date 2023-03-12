/**
 * Description: This module implements Palindrome - determine if a word or phase is a Palindrome or not
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date: 3/11/2023
 * Creation date:3/11/2023
 **/
#include <stdio.h>
#include <string.h>
#define MAX_C 50
#define SPACE ' '
/**
 * This main function reads user input string
   then use two pointer method to determine if the string is palindrome or not
 * Assumption: The length of string not exceed 50 character
 * Input parameters: n/a
 * Returns: an integer(0 - program normal exit, non 0 - program error)
**/
int main()
{
    char userInput[MAX_C];
    printf("Enter a word or phase:\n");
    fgets(userInput, MAX_C, stdin);
    int left = 0;
    int right = strlen(userInput) - 2;

    while(left < right)
    {
        if(userInput[left] == SPACE)
        {
            left++;
        }
        if(userInput[right] == SPACE)
        {
            right--;
        }

        if(userInput[left] == userInput[right])
        {
            left++;
            right--;
        }
        else
        {
            printf("not a palindrome: %s\n", userInput);
            return 0;
        }
    }
    printf("palindrome: %s\n", userInput);

    return 0;
}
