/**
 * Description: This module computes positive integer to binary form.
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date: 2/16/2023
 * Creation date:2/16/2023
 **/
#include <stdio.h>
#include <string.h>

int main()
{
    int x;
    int binary[32];
    int index = 0;

    scanf("%d", &x);
    // this loop computes x to binary form
    while(x > 0){
        binary[index] = x % 2;
        index++;
        x = x / 2;

    }
    // print the binary form of the input number
    for(int i = 0; i < index; i++){
        printf("%d",binary[i]);
    }
    printf("\n");

    return 0;
}
