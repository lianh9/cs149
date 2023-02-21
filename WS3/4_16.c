/**
 * Description: This module computes max and average.
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date: 2/16/2023
 * Creation date:2/16/2023
 **/
#include <stdio.h>

int main()
{
    int x = 0; // placeholder for user input
    int max = 0; // placehold for the max input
    double sum; // placeholder for sum of all the input
    double average; // placeholder for average
    int count = 0; // placeholder for number of inputs

    // this loop takes user inputs and computes the max and the sum,
    // until user enters a negative integer.
    while(x >= 0){
        scanf("%d", &x);
        if(x < 0){
            break;
        }
        if(x > max){
            max = x;
        }
        count++;
        sum += x;
    }
    average = sum / count;

    printf("%d %0.2lf \n", max, average);

    return 0;
}
