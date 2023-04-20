/**
 * Description: This module implements q6 - create size 100 int array using malloc(), free then print out one element of the array
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date: 4/20/2023
 * Creation date:4/20/2023
 **/


 /* Answer for the question:
  * This program runs without error with normal runs and prints out 0 for data[20]
  * This program has no memory leak but with Invalid write of size 4 problem if run with valgind(--leak-check=yes flag)
  * HEAP SUMMARY:
        ==4710== Invalid read of size 4
        ==4710==    at 0x1091B7: main (in /home/lian/Desktop/cs149/WS12/q6)
        ==4710==  Address 0x4a97090 is 80 bytes inside a block of size 400 free'd
        ==4710==     in use at exit: 0 bytes in 0 blocks
        ==4710==   total heap usage: 2 allocs, 2 frees, 1,424 bytes allocated
        ==4710==
        ==4710== All heap blocks were freed -- no leaks are possible
  */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//buggy program tries to print out content after free()
#define SIZE 100
int main()
{
    int *data;
    data = (int*)malloc(SIZE *sizeof(int));
    free(data);

    printf("%d\n",data[20]);

    return 0;

}
