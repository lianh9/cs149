/**
 * Description: This module compute the name counts of one or more input files in a parallel fashion using multiple processes.
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date:3/1/2023
 * Creation date: 3/1/2023
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_NAMES 100
#define MAX_C 30

/**
 * This main function read one or more file from command line and compute the number of occurrences of each name inside the file using multiple processes
 * Assumption: unique names are not exceed 100 in the file, and the length of each name are within 30 character
 * Input parameters: argc, argv
 * Returns: an integer(0 - program normal exit, non 0 - program error)
**/
int main(int argc, char *argv[])
{
    // check if any file was given from command line
    if(argc < 2)
    {
        printf("NO input file given\n");
        exit(1);
    }

    int fd[2]; // pipes for writing data from the child process and parent process read data send from child processes
    char name[MAX_NAMES][MAX_C]; // name array placeholder for all the unique names
    int count[MAX_NAMES] = {0}; // count array placeholder for the occurrences for each name
    int index = 0; // array index for both name and count array

    // if pipe failed, print error message
    if(pipe(fd) == -1)
    {
        fprintf(stderr, "Pipe failed");
        return 1;
    }

    // this for loop go through every file given from the command line and assign ith file to ith child process to perform name count
   for(int i = 1; i < argc; i++)
   {

        int childid = fork();

        // child process
        if(childid == 0){

            char name[MAX_NAMES][MAX_C]; // name array to hold unique name in child process
            int count[MAX_NAMES] = {0}; // count array to hold occurrences of each name in child process
            char str[MAX_C]; // str array to hold single name in child process
            int line = 0; // for tracking the current line in the file while reading
            int n = 0; // for tracking how many unique names in file
            int index = 0; // name and count array index

            // open file from command line
	        FILE *f = fopen(argv[i],"r");
        // if file is empty or no argument is passing, print error message
        if (f == NULL)
        {
            fprintf(stderr, "range: cannot open file %s\n",argv[i]);
            return(1);
        }


        // this while loop read file line by line until reach the end of file
        while (fgets(str, MAX_C, f))
        {
            line++;

            // if the current line is empty, print warning message
            if(strcmp(str,"\n") == 0)
            {
                fprintf(stderr,"Warning - %s Line %d is empty.\n", argv[i], line);
                continue;
            }

            int newName = 1;
            // check if the name already exit in the array, if so increment the number of occurrences
            for(int i = 0; i < index; i++)
            {
                if(strcmp(name[i],str) == 0)
                {
                    newName = 0;
                    count[i]++;
                    break;
                }
            }
            // if it is a new name, store in name array and increment the occurrence
            // then, increment index for name and count for storing next value
            if(newName)
            {
                strcpy(name[index],str);
                n++;
                count[index]++;
                index++;
            }
        }
            // close file
            fclose(f);

            close(fd[0]); // close the read end of pipe

            // write the number of unique name to parent process
            if(write(fd[1], &n, sizeof(int)) < 0)
            {
                fprintf(stderr, "failed to write\n");
            }
            // write the name array from read file to parent process
            if(write(fd[1], name, 3000) < 0)
            {
                fprintf(stderr, "failed to write\n");
            }
            // write the number of each name(count array) to parent process
            if(write(fd[1], count, 100*sizeof(int)) < 0)
            {
                fprintf(stderr, "failed to write\n");
            }

            exit(0);

        }
   }
            close(fd[1]); // close write end of pipe


    // the parent waits for each child to finish
    while((wait(NULL)) > 0)
    {

        int n;
        char str[100][30];
        int counts[100];

        close(fd[1]); // close write end of pipe

        // read data from the read end of pipe
        read(fd[0], &n, sizeof(int)); // number of unique name of a certain file from child process
        read(fd[0], str, 3000); // unique name array from child process
        read(fd[0], counts, 100*sizeof(int)); // name count array from child process
        int newName = 1;

        // this for loop for go through the date send from child process
        for(int j = 0; j < n; j++)
        {
            // this loop is to check if the name send from child process already in the final result name array
            for(int i = 0; i < index; i++)
            {
                // if the name already exist in the array, increment the count occurrences
                if(strcmp(name[i],str[j]) == 0)
                {
                    newName = 0;
                    count[i] += counts[j];
                    break;
                }
            }
                // if the name is not exist in the array, append the name and increment the count occurrences
                // then increment array counter to store the next value
                if(newName)
                {
                    strcpy(name[index],str[j]);
                    count[index] += counts[j];
                    index++;
                }
        }
    }
    close(fd[0]); // close the read end of pipe

    // this loop print the final uique name and their occurrences from all the file
    for(int i = 0; i < index; i++)
    {
       char temp[strlen(name[i])];
		strcpy(temp,name[i]);
		// remove newline character in the string
		if(temp[strlen(temp) -1] == '\n')
        {
			temp[strlen(temp) - 1] = '\0';
			strcpy(name[i],temp);
        }
		printf("%-20s %c %d\n",name[i],':',count[i]);
        }
     return 0;

}
