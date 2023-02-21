/**
 * Description: This module output the middle item of a list.
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date: 2/17/2023
 * Creation date:2/17/2023
 **/
#include <stdio.h>

int main()
{
    int input[20];
    int index = 0;
    int n = 0;
    // this loop get and store user input to an array until negtive integer is entered
    while(n >= 0){
        scanf("%d", &n);
        // if negtive integer entered, end the input
        if(n < 0) break;
        input[index] = n;
        index++;
        // if exceeds 9 items
        if(index > 8){
            printf("Too many numbers.");
            return 0;

        }
    }
    //print the middle item
    printf("%d\n", input[index/2]);

    return 0;
}
