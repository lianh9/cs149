/**
 * Description: This module implements q5 - create size 100 int array using malloc()
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date: 4/20/2023
 * Creation date:4/20/2023
 **/


 /* Answer for the question:
  * This program runs without error with normall runs
  * This program has memory leak and indicated with Invalid write of size 4 if run with valgind(--leak-check=yas flag)
  * HEAP SUMMARY:
        Invalid write of size 4
        ==4521==    at 0x10916D: main (in /home/lian/Desktop/cs149/WS12/q5)
        ==4521==  Address 0x4a971d0 is 0 bytes after a block of size 400 alloc'd
        ==4521==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
        ==4521==    by 0x10915E: main (in /home/lian/Desktop/cs149/WS12/q5)
        ==4521==
        ==4521==
        ==4521== HEAP SUMMARY:
        ==4521==     in use at exit: 400 bytes in 1 blocks
        ==4521==   total heap usage: 1 allocs, 0 frees, 400 bytes allocated
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//buggy program allocates memory using malloc() without free before exiting and invalid write problem
#define SIZE 100
int main()
{
    int *data;
    data = (int*)malloc(SIZE *sizeof(int));
    data[100] = 0;


    return 0;

}
