/**
 * Description: This module implements Parsing strings
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date: 3/29/2023
 * Creation date:3/29/2023
 **/
#include <string.h>
#include <stdio.h>
#include<stdbool.h>
// function declaration
bool containsComma(char input[]);
/**
 * This main function reads a string/two word separate by comma from user
   then parse the string into two word by comma, repeat until user enter q to quit
 * Assumption: The string will always contain less than 60 characters
 * Input parameters: n/a
 * Returns: an integer(0 - program normal exit, non 0 - program error)
**/
int main()
{
    char first_word[30];
    char second_word[30];
    char input[60];
    char newString[20][30];
    int i,j,ctr;

    while (true)
    {
        printf("Enter input string:\n");
        fgets(input, 60, stdin);
        if(strcmp(input, "q\n") == 0)
        {
            printf("Program ended!\n");
            break;
        }

        if(containsComma(input))
        {

            for (int i=0; i<20; i++)
                for (int j=0; j<20; j++)
                    newString[i][j]=0;

            j=0; ctr=0;
            for(i=0;i<=(strlen(input));i++)
            {
                // if space or NULL found, assign NULL into newString[ctr]
                if(input[i]==' '||input[i]=='\0' || input[i]==',')
                {
                    newString[ctr][j]='\0';
                    if(input[i] == ',')
                    {
                        ctr++; //for next word
                        j=0; //for next word, init index to 0
                    }
                }
                else
                {
                    newString[ctr][j]=input[i];
                    j++;
                }
            }

            strcpy(first_word, newString[0]);
            strcpy(second_word, newString[1]);
            printf("First Word: %s\n",first_word);
            printf("Second Word: %s\n",second_word);
        }
        else
        {
            printf("Error: No comma in string\n");
        }
    }

    return 0;
}
/**
 * This boolean function check if a string contains comma
 * Assumption: The string will always contain less than 60 characters
 * Input parameters: char input[]
 * Returns: true/false
**/
bool containsComma(char input[])
{
    bool comma = false;
    for(int i = 0; i < strlen(input); i++)
        {
            if(input[i] == ',')
            {
                comma = true;
            }
        }
    return comma;

}



