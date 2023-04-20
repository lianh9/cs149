/**
 * Description: This module implements q4 - detect memory leak
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date: 4/20/2023
 * Creation date:4/20/2023
 **/


 /* Answer for the question:
  * This program runs without error with normal runs
  * This program has memory leak if run with valgind(--leak-check=yes flag)
  * HEAP SUMMARY:
        ==4159==     in use at exit: 8 bytes in 1 blocks
        ==4159==   total heap usage: 1 allocs, 0 frees, 8 bytes allocated
        ==4159==
        ==4159== 8 bytes in 1 blocks are definitely lost in loss record 1 of 1
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//buggy program allocates memory using malloc() without free before exiting
int main()
{
    int *ptr;
    ptr = (int*)malloc(sizeof(int*));

    return 0;

}
