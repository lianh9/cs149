/**
 * Description: This module remove all non-alphabetic characters
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date: 3/2/2023
 * Creation date:3/2/2023
 **/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void RemoveNonAlpha(char userString[], char userStringAlphaOnly[]);

/**
 * This main function reads user input string
   then call RemoveNonAlpha to remove all non alpha character
 * Assumption: The length of string not exceed 50 character
 * Input parameters: n/a
 * Returns: an integer(0 - program normal exit, non 0 - program error)
**/
int main()
{
    char userString[50];
    static char userStringAlphaOnly[50];

    fgets(userString, 50, stdin);

    RemoveNonAlpha(userString, userStringAlphaOnly);

    printf("%s \n", userStringAlphaOnly);

    return 0;
}
/**
 * This function remove non-alphabetic characters in a string
 * Assumption: The length of string not exceed 50 character
 * Input parameters: userString, userStringAlphaOnly
 * Returns: n/a
**/
void RemoveNonAlpha(char userString[], char userStringAlphaOnly[])
{
    int i = 0;
    int index = 0;
    // this loop copies all alpha from userString to userStringAlphaOnly
    while(userString[i] != '\0')
    {
        if(isalpha(userString[i]) != 0){
            userStringAlphaOnly[index] = userString[i];
            index++;
        }
        i++;
    }
}


