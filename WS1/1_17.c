/**
 * Description: This module outputs formatted Rigt-facing arrow from user inputs.
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date:2/6/2023
 * Creation date:2/1/2023 
 **/

#include <stdio.h>

int main(void){
	int baseInt;
	int headInt;

	scanf("%d",&baseInt);
	scanf("%d",&headInt);
	printf("%d\n",headInt);
	printf("%d%d\n",headInt,headInt);
	printf("%d%d%d%d%d%d%d\n",baseInt,baseInt,baseInt,baseInt,headInt,headInt,headInt);
	printf("%d%d%d%d%d%d%d%d\n",baseInt,baseInt,baseInt,baseInt,headInt,headInt,headInt,headInt);
	printf("%d%d%d%d%d%d%d\n",baseInt,baseInt,baseInt,baseInt,headInt,headInt,headInt);
	printf("%d%d\n",headInt,headInt);
	printf("%d\n",headInt);

	return 0;
}
