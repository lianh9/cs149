/**
 * Description: This module prints 2 smallest integer value from the list.
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
    int smallest = INT_MAX;
    int secondS = INT_MAX;
    printf("Please enter the number of item will be in the array: \n");
    scanf("%d", &n);

    printf("please enter %d integers separate by space: \n",n);
    // this loop gets the number of inputs and store them in an array
    while(index < n){
        int temp;
        scanf("%d", &temp);
        list[index] = temp;
        index++;
    }
    // this loop finds the 2 smallest values in the list
    for(int i = 0; i < index; i++){
        if(smallest > list[i]){
            secondS = smallest;
            smallest = list[i];
        }
        else if(secondS > list[i] && list[i] != smallest){
            secondS = list[i];
        }
    }

    printf("%d and %d\n", smallest, secondS);
    return 0;
}
