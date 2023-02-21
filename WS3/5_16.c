/**
 * Description: This module output input numbers in reverse.
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
    // this loop get the following inputs that the first input indicates
    while(index <= input[0]){
        scanf("%d", &n);
        input[index] = n;
        index++;
    }
    // this loop print out all the inputs from array in reverse order except the first value
    for(int i = index - 1; i > 0; i--){
        printf("%d,", input[i]);
    }
    printf("\n");

    return 0;
}
