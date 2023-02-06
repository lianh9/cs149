/**
 * Description: This module performs arithmetic operations for two variables.
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date:2/6/2023
 * Creation date:2/1/2023 
 **/


#include <stdio.h>

int main(void){
	int userNum;

	printf("Enter integer:\n");
	scanf("%d", &userNum);
        printf("You entered: %d\n", userNum);
        printf("%d squared is %d\n", userNum, userNum*userNum);
	printf("And %d cubed is %d!!\n", userNum, userNum*userNum*userNum);
	printf("Enter another integer:\n");
	int userNum2;
	scanf("%d", &userNum2);
	printf("%d + %d is %d\n", userNum, userNum2, userNum+userNum2);
	printf("%d * %d is %d\n", userNum, userNum2, userNum*userNum2);



        return 0;
}

