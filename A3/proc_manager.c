/**
 * Description: This module reads commands for each execution from stdin line by line, then execute commands in a parallel fashion using multiple processes.
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date:3/21/2023
 * Creation date: 3/16/2023
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

/**
 * This main function read one or more commands line from stdin and parse the commands, then execute them use execvp() in parallel using multiple processes
 * Assumption: commands not exceed 100, the length of command is within 30 character
 * Input parameters: void
 * Returns: an integer(0 - program normal exit, non 0 - program error)
**/
#define MAX_NUM_COMMAND 100
#define MAX_LEN 30

int main(void)
{

    char * line = NULL; // for tracking line when reading from stdin
    size_t len = 0;
    ssize_t read;

    char commands[MAX_NUM_COMMAND][MAX_LEN]; // for storing parsed command
    char *run_command[MAX_LEN]; // command buffer for execvp() function
    int i,j,ctr; // loop counter
    pid_t pid[MAX_NUM_COMMAND];// child pid
    int num_commands = 0; // tracking number of commands


    // get commands from stdin until ctrl d, then parse each command
    while ((read = getline(&line, &len, stdin)) != -1)
    {
        for (int i=0; i<MAX_LEN; i++)
            for (int j=0; j<MAX_LEN; j++)
                commands[i][j]=0;

        j=0; ctr=0;
        for(i=0;i<=(strlen(line));i++)
        {
        // if space or NULL found, assign NULL into newString[ctr]
            if(line[i]==' '||line[i]=='\0' || line[i] == '\n')
            {
                commands[ctr][j]='\0';
                ctr++; //for next word
                j=0; //for next word, init index to 0
            }
            else
            {
                commands[ctr][j]=line[i];
                j++;
            }
        }

        run_command[0] = (char *)&commands[0][0];
        run_command[1] = (char *)&commands[1][0];
        run_command[2] = (char *)0;
        num_commands++;

        pid[num_commands] = fork();
        /* child */
        if (pid[num_commands] < 0)
        {
            printf("fork error");
        }
        // each command/child process will write its own stdout and stderr to log files
        else if (pid[num_commands] == 0)
        {

            char outFile[MAX_LEN];
            char errFile[MAX_LEN];
            sprintf(outFile, "%d.out", getpid());
            sprintf(errFile, "%d.err", getpid());
            // open pid.out file
            int pid_out = open(outFile, O_RDWR | O_CREAT | O_APPEND, 0777 );
            // open pid.err file
            int pid_err = open(errFile, O_RDWR | O_CREAT | O_APPEND, 0777 );
            // move stdout to pid.out
            dup2(pid_out, 1);
            // move stderr to pid.err
            dup2(pid_err,2);
            dprintf(pid_out,"Starting command %d: child %d pid of parent %d\n", num_commands, getpid(), getppid());
            close(pid_out);
            close(pid_err);
            execvp(run_command[0], run_command);
            // wouldn't reach here unless execvp() failed
            fprintf(stderr,"couldn't execute command: %s %s\n", run_command[0], run_command[1]);
            exit(1);
        }
    }

    /* parent wait for each child process to finish */
    // get the exit code and status or if the child is killed by any signals from child, then write them to log files

    for(int i = 1; i <= num_commands; i++)
    {
        int status;
        //get child pid
        pid_t cpid = waitpid(pid[i], &status, 0);
        // write finished message to child out file
        char pathname_out[MAX_LEN];
        sprintf(pathname_out, "%d.out", cpid);
        int fd1 = open(pathname_out, O_RDWR | O_APPEND, 0777 );
        dprintf(fd1,"Finished child %d pid of parent %d\n",cpid,getpid());
        close(fd1);
        // open err file
        char pathname_err[MAX_LEN];
        sprintf(pathname_err, "%d.err", cpid);
        int fd2 = open(pathname_err, O_RDWR | O_APPEND, 0777 );
        // get exit status
        if(WIFEXITED(status))
        {
            int code = WEXITSTATUS(status);
            // write exitcode to child out file
            dprintf(fd2,"Exited with exitcode = %d\n", code);

        }
        // if child is killed by signal
        else if (WIFSIGNALED(status))
        {
            dprintf(fd2, "Killed with signal %d\n",WTERMSIG(status));
        }
        close(fd2);


    }

    exit(0);
}

