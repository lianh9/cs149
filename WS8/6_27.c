/**
 * Description: This module implements Count characters
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date: 3/26/2023
 * Creation date:3/26/2023
 **/
#include <stdio.h>
#include <string.h>
#define MAX_C 50
/**
 * This main function reads a single character and a string from user
   then computes the number of times the character appearing in that string
 * Assumption: The string doesn't contain spaces and will always contain less than 50 characters
 * Input parameters: n/a
 * Returns: an integer(0 - program normal exit, non 0 - program error)
**/
int main()
{
    char character;
    char sentence[MAX_C];
    int count = 0;
    printf("Enter a character: ");
    scanf("%c", &character);
    // for preventing fgets reads the newline leftover from scanf
    while ((getchar()) != '\n');

    printf("Enter a string without space and less than 50 characters: ");
    fgets(sentence, MAX_C, stdin);
    // loop through every character in the string to check if the string
    // contains the character
    for(int i = 0; i < strlen(sentence); i++)
    {
        if(sentence[i] == character)
        {
            count ++;
        }
    }

    if(count == 0 || count > 1) printf("%d %c's\n", count, character);

    if(count == 1) printf("%d %c\n", count, character);

    return 0;
}
