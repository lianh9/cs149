/**
 * Description: This module counts the number of times each name appears in a file.
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date:2/16/2023
 * Creation date: 2/9/2023
 **/

#include <stdio.h>
#include <string.h>

#define MAX_NAME 100 
#define MAX_C 30
/**
 * This main function read file from command line and compute the number of occurrences of each name inside the file
 * Assumption: unique names are not exceed 100 in the file, and the length of each name are within 30 character
 * Input parameters: argc, argv
 * Returns: an integer(0 - program normal exit, non 0 - program error)
**/
int main(int argc, char *argv[]) {
	// declare character array to store up to 100 names
	char name[MAX_NAME][MAX_C];
	// declare and initialize integer array to 0 for storing the number of occurrences of name
	int count[MAX_NAME] = {0};
	// placeholder for string in one line  while reading file
	char str[MAX_C];
	// array counter
	int index = 0;
	// use for checking if a name is new name
	int newName = 0;
	// use for tracking lines while reading file
	int line = 0;

	// open file from command line
	FILE *f = fopen(argv[1],"r");
	// if file is empty or no argument is passing, print error message
	if (f == NULL) {
		perror("error: cannot open file\n");
		return(1);
	}
	// this while loop read file line by line until reach the end of file
	while (fgets(str, MAX_C, f)) {
		line++;
		// if the current line is empty, print warning message
		if(strcmp(str,"\n") == 0){
			fprintf(stderr,"Warning - Line %d is empty.\n",line);
			continue;
		}

		newName = 1;
		// check if the name already exit in the array, if so increment the number of occurrences
		for(int i = 0; i < index; i++){
			if(strcmp(name[i],str) == 0){
				newName = 0;
				count[i]++;
				break;
			}
		}
		// if it is a new name, store in name array and increment the occurrence
		// then, increment index for name and count for storing next value
		if(newName){
			strcpy(name[index],str);
			count[index]++;
			index++;
		}
	}
	// close file
	fclose(f);


	// print out results from name array with the number of occurrences
	for(int i = 0; i < MAX_NAME; i++){
		if(count[i] == 0){
			break;
                }

		char temp[strlen(name[i])];
		strcpy(temp,name[i]);
		// remove newline character in the string 
		if(temp[strlen(temp) -1] == '\n'){
			temp[strlen(temp) - 1] = '\0';
			strcpy(name[i],temp);
					}
		printf("%s %c %d\n",name[i],':',count[i]);
	}



	return 0;
}
