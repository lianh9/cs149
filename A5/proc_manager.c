/**
 * Description: This module reads commands for each execution from stdin line by line, then execute commands in a parallel fashion using multiple processes.And store command
 info, pid info, start and finish time to Linked list.
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date:4/23/2023
 * Creation date: 4/13/2023
 **/
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>



// struct definition
struct node {
    int index; // store line number
    char* command; // store command
    int pid; //store child pid
    double starttime;
    double finishtime;
    struct node* link;  // ptr to next node
};
typedef struct node node_c;
static char commands[3][100];
/**
 * This linkedList() function create a node for linkedList
 * Assumption: N/A
 * Input parameters: char* string, int line, int pid, int starttime
 * Returns: node_c *ptr
**/
node_c* linkedList(char* string, int line,int pid, int starttime)
{
    node_c* ptr;
    ptr = (node_c*) malloc(sizeof(node_c));
    if (ptr == NULL) {
        printf("linkedList: memory allocation error\n");
        exit(1);
  }

    ptr->index = line;
    ptr->pid = pid;
    ptr->starttime = starttime;
    ptr->command = strdup(string);
    ptr->link=NULL;

    return ptr;

}

/**
 * This FindCommand() function find a command based on the pid
 * Assumption: N/A
 * Input parameters: node_c* cmd, int pid
 * Returns: node_c *tmpNext/Null(if not found)
**/
node_c* FindCommand(node_c* cmd, int pid) {
    node_c* tmpNext = cmd;
    while (tmpNext != NULL) {
        if (tmpNext->pid == pid) {
            return tmpNext;
        }
    tmpNext = tmpNext->link;
    }
    return NULL;
}
/**
 * This FreeNode() function deallocate memory to avoid memory leak
 * Assumption: N/A
 * Input parameters: node_c *ptr
 * Returns: void
**/
void FreeNode(node_c* ptr)
{
    if(ptr->link != NULL){
        FreeNode(ptr->link);
    }
    free(ptr->command);
    if(ptr->link != NULL){
        free(ptr->link);
    }
}

/**
 * This parseCommand() function parse command from stdin for execvp()
 * Assumption: N/A
 * Input parameters: char *line
 * Returns: void
**/
void parseCommand(char *line){
    int i,j,ctr; // loop counter
    for (int i=0; i<20; i++)
        for (int j=0; j<100; j++)
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
}


/**
 * This main function read commands from stdin and store each command into LinkedList
 * Assumption: N/A
 * Input parameters: N/A
 * Returns: an integer(0 - program normal exit, non 0 - program error)
**/
int main()
{
    char * line = NULL; // for tracking line when reading from stdin
    size_t len = 0;
    ssize_t read;
    int line_number = 0;
    int pid;
    int status;
    struct timespec start, finish;
    double elapsed;
    double finishtime;
    char *run_command[3];
    node_c* head;
    node_c *curr;

    // get commands from stdin until ctrl d, then store each command into LinkedList
    while ((read = getline(&line, &len, stdin)) != -1)
    {
        line_number++;
        parseCommand(line);

        // assign parsed command to run_command buffer
        run_command[0] = (char *)&commands[0][0];
        run_command[1] = (char *)&commands[1][0];
        run_command[2] = (char *)0;

        //fork the commands and record the start times
        //save the startime!
        pid = fork();
        clock_gettime(CLOCK_MONOTONIC, &start);

        if (pid < 0) {
            fprintf(stderr, "error forking");
            exit(2);
        }
        //child
        else if (pid == 0) {
            char outFile[30];
            char errFile[30];
            sprintf(outFile, "%d.out", getpid());
            sprintf(errFile, "%d.err", getpid());
            // open pid.out file
            int fdout = open(outFile, O_RDWR | O_CREAT | O_APPEND, 0777 );
            // open pid.err file
            int fderr = open(errFile, O_RDWR | O_CREAT | O_APPEND, 0777 );
            dup2(fdout,1);
            dup2(fderr,2);
            dprintf(fdout, "Starting command INDEX %d: child PID %d of parent PPID %d.\n", line_number, getpid(), getppid() );
            close(fdout);
            close(fderr);
            execvp(run_command[0],run_command);
            exit(2);
        }
        // parent
        else if (pid > 0) {

            //insert the new pid into the LinkedList
            //record the new starttime!
            if(line_number == 1){
                head = linkedList(line,line_number,pid,start.tv_sec);
                curr = head;
            }
            else{
                curr->link = linkedList(line,line_number,pid,start.tv_sec);
                curr = curr->link;
            }
        }
    } //end of while loop


    while((pid = wait(&status)) >= 0) {
        //record finish time
        clock_gettime(CLOCK_MONOTONIC, &finish);
        finishtime = finish.tv_sec;

        node_c *entry;
        // find command base on pid and store finish time
        if((entry = FindCommand(head,pid)) != NULL){

            entry->finishtime = finishtime;
        }
        else {
            printf("look up error, pid %d\n",pid);
            exit(2);
        }
        // parent
        if(pid > 0) {
            char outFile[30];
            char errFile[30];
            sprintf(outFile, "%d.out", pid);
            sprintf(errFile, "%d.err", pid);
            int fdout = open(outFile,O_RDWR | O_APPEND, 0777 );
            int fderr = open(errFile,O_RDWR | O_APPEND, 0777 );

            dprintf(fdout,"Finished child %d pid of parent %d \n",pid,getpid());

            // get exitcode
            if (WIFEXITED(status)) {
                dprintf(fderr,"Exited with exitcode = %d\n",WEXITSTATUS(status));
            }
            //signal handling
            else if (WIFSIGNALED(status)) {
                dprintf(fderr, "Killed with signal number: %d\n",WTERMSIG(status));
            }

            //to compute the elapsed time
            elapsed = finishtime - entry->starttime;
            dprintf(fdout,"Finished at %0.2lf, runtime duration %0.lf\n",finishtime,elapsed);

            // restart if elapsed time > 2 sec
            if(elapsed > 2){

                pid = fork();
                clock_gettime(CLOCK_MONOTONIC, &start);

                if(pid < 0){
                    fprintf(stderr, "error forking");
                    exit(2);

                }
                else if (pid == 0) { //child
                    char outFile[30];
                    char errFile[30];
                    sprintf(outFile, "%d.out", getpid());
                    sprintf(errFile, "%d.err", getpid());
                    // open pid.out file
                    int fdout = open(outFile, O_RDWR | O_CREAT | O_APPEND, 0777 );
                    // open pid.err file
                    int fderr = open(errFile, O_RDWR | O_CREAT | O_APPEND, 0777 );
                    dup2(fdout,1);
                    dup2(fderr,2);

                    dprintf(fdout,"RESTARTING\n");
                    dprintf(fderr,"RESTARTING\n");
                    dprintf(fdout, "Starting command INDEX %d: child PID %d of parent PPID %d.\n", entry->index, getpid(), getppid() );
                    parseCommand(entry->command);
                    close(fdout);
                    close(fderr);
                    run_command[0] = (char *)&commands[0][0];
                    run_command[1] = (char *)&commands[1][0];
                    run_command[2] = (char *)0;
                    execvp(run_command[0],run_command);
                    exit(2);
                }
                else if (pid > 0) {
                curr->link = linkedList(entry->command,entry->index,pid,start.tv_sec);
                curr = curr->link;

                }
            }
            else{

                dprintf(fderr,"spawning too fast\n");
                close(fdout);
                close(fderr);
            }

        }
    }
    FreeNode(head);
    if(line) free(line);
    free(head);


    return(0);
}





