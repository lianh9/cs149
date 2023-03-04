/**
 * Description: This module counts input length without
   spaces, periods, exclamation points, or comma
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date: 3/2/2023
 * Creation date:3/2/2023
 **/
#include <stdio.h>
#include <string.h>

int main()
{
    char str[50];
    int count = 0;

    fgets(str,sizeof(str),stdin);
    int i = 0; // loop counter
    // this loop iterates the input character array and
    // count input length without spaces, periods, exclamation points, or comma
    while(str[i] != '\n')
    {
        if(str[i] != ' ' && str[i] != '.' && str[i] != ',' && str[i] != '!' )
        {
            count++;
        }

        i++;
    }
    printf("%d\n", count);

    return 0;
}
