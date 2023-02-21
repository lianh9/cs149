/**
 * Description: This module searches if a character is in any words user entered.
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date: 2/19/2023
 * Creation date:2/19/2023
 **/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char words[20][10]; // array stores all the words
    char str[10]; // placeholder for each words
    int index = 0; // array index
    int n = 0; // placeholder for number of words user input
    char searchCharacter; // placeholder for character need to be seach
    printf("Please enter the number of words: \n");
    scanf("%d",&n);
    printf("Please enter %d words separate by space:\n", n);

    // this loop get any words user entered untill reaches the number user indicated previouly
    while(index < n){
        scanf("%s",str);
        strcpy(words[index],str);
        index++;

    }

    printf("Please enter a character to search:\n");
    scanf(" %c", &searchCharacter);
    // this loop search if any word in the array contains the character user entered
    // then print out the word contains the character
    for(int i = 0; i < index; i++){
        for(int j = 0; j < strlen(words[i]); j++ ){
            char tem = words[i][j];
            if(tem == searchCharacter){
                printf("%s, ", words[i]);
                break;
            }
        }
    }
    printf("\n");


    return 0;
}
