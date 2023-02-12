/**
 * Description: This module outputs the smallest of three values.
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date:2/11/2023
 * Creation date:2/11/2023 
 **/
#include <stdio.h>

int main(void){

	int x, y, z;
	int smallest;

	scanf("%d%d%d", &x, &y, &z);
	if(x < y){
		smallest = x;
	}
	else{smallest = y;}

	if(smallest > z){
		smallest = z;
	}
        
	printf("%d\n", smallest);
	
	return 0;
}
