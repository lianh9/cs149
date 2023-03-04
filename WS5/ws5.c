/**
 * Description: This module uses fork() to print the string "hello world from PID xxx!" 4 times.
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date: 3/2/2023
 * Creation date:3/2/2023
 **/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{

    fork();
    fork();

    printf("hello world from PID %d!\n", (int) getpid());


    return 0;
}

