/**
 * Description: This module outputs welcome message.
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date:2/11/2023
 * Creation date:2/11/2023 
 **/
#include <stdio.h>

int main(void){

	char userName[50];

	scanf("%s", userName);
	printf("Hello %s, and welcome to CS online!\n", userName);
	
	return 0;
}
