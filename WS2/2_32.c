/**
 * Description: This module output the price change for a house since last month and the estimated monthly mortgage.
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date:2/11/2023
 * Creation date:2/11/2023 
 **/
#include <stdio.h>

int main(void){

	int currentPrice;
	int lastMonthPrice;

	scanf("%d", &currentPrice);
        scanf("%d", &lastMonthPrice);
	printf("This house is $%d. The change is $%d since last month.\n", currentPrice, currentPrice - lastMonthPrice);
	printf("The estimated monthly mortgage is $%0.6lf.\n", (currentPrice*0.051)/12);
	
	return 0;
}
