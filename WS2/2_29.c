/**
 * Description: This module using math functions.
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date:2/11/2023
 * Creation date:2/11/2023 
 **/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int main(void){

	double x;
	double y;
	double z;

	scanf("%lf %lf %lf", &x, &y, &z);
        
	printf("%0.2lf  %0.2lf %0.2lf %0.2lf\n", pow(x,z), pow(x,pow(y,2)), fabs(y),sqrt(pow(x*y,z)));
	
	return 0;
}
