/**
 * Description: This module implements divide by x.
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date:2/11/2023
 * Creation date:2/11/2023 
 **/
#include <stdio.h>

int main(void){

	int userNum;
	int x;

	scanf("%d", &userNum);
        scanf("%d", &x);
	printf("%d %d %d\n", userNum/x, userNum/x/x, userNum/x/x/x);
	
	return 0;
}
