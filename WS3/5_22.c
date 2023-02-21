/**
 * Description: This module prints elements in a range
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date: 2/19/2023
 * Creation date:2/19/2023
 **/
#include <stdio.h>
#include <limits.h>

int main()
{
    int list[20];
    int n = 0;
    int index = 0;
    int low;
    int high;
    printf("Please enter the number of item will be in the array: \n");
    scanf("%d", &n);

    printf("please enter %d integer separate by space: \n", n);
    // this loop gets the number of inputs and store them in an array
    while(index < n){
        int temp;
        scanf("%d", &temp);
        list[index] = temp;
        index++;
    }
    printf("please enter a range separate by space:\n");
    scanf("%d %d", &low, &high);
    // this loop find all the values between the range
    for(int i = 0; i < index; i++){
        if(list[i] >= low && list[i] <= high){
            printf("%d,", list[i]);
        }

    }
    printf("\n");

    return 0;
}
