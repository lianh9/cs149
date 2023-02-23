/**
 * Description: This module implements track laps to miles.
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date: 02/23/2023
 * Creation date: 02/23/2023
 **/

#include <stdio.h>

/* function declaration */
double LapsToMiles(double laps);

/**
 * Main fuction takes a number of laps as input, calls function LapsToMiles()
   to calculate the number of miles, and outputs the number of miles.
 * Assumption: n/a
 * Input parameters: n/a
 * Returns: 0
**/
int main()
{
    double numOfLaps;
    double miles;
    scanf("%lf", &numOfLaps );
    miles  = LapsToMiles(numOfLaps);
    printf("%0.2lf\n", miles);

    return 0;
}
/**
 * This function calculates the number of miles
 * Assumption: n/a
 * Input parameters: double laps
 * Returns: a double
**/

double LapsToMiles(double laps){
    return laps * 0.25;
}
