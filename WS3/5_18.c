/**
 * Description: This module outputs all items of a list that less than the last item.
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date: 2/19/2023
 * Creation date:2/19/2023
 **/
#include <stdio.h>

int main()
{
    int input[20];
    int index = 0;
    int n = 0;
    // this loop get the following inputs that the first input indicates
    while(index <= input[0] + 1 ){
        scanf("%d", &n);
        input[index] = n;
        index++;
    }
    // this loop print out all the inputs from array that less than the last value
    for(int i = 1; i <= index - 2; i++){
        if(input[i] <= input[index - 1]){
            printf("%d,", input[i]);
        }

    }
    printf("\n");


    return 0;
}
