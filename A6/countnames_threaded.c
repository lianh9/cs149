#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
/*****************************************
//CS149 Fall 2022
//Template for assignment 6
//San Jose State University
//originally prepared by Bill Andreopoulos
*****************************************/
//thread mutex lock for access to the log index
//TODO you need to use this mutexlock for mutual exclusion
//when you print log messages from each thread
pthread_mutex_t tlock1 = PTHREAD_MUTEX_INITIALIZER;
//thread mutex lock for critical sections of allocating THREADDATA
//TODO you need to use this mutexlock for mutual exclusion
pthread_mutex_t tlock2 = PTHREAD_MUTEX_INITIALIZER;
//thread mutex lock for access to the name counts data structure
//TODO you need to use this mutexlock for mutual exclusion
pthread_mutex_t tlock3 = PTHREAD_MUTEX_INITIALIZER;

void* thread_runner(void*);
pthread_t tid1, tid2;
//struct points to the thread that created the object.
//This is useful for you to know which is thread1. Later thread1 will also
//deallocate.
struct THREADDATA_STRUCT{
    pthread_t creator;
};
typedef struct THREADDATA_STRUCT THREADDATA;
THREADDATA* p=NULL;
//variable for indexing of messages by the logging function.
int logindex=1;
int *logip = &logindex;
//The name counts.
// You can use any data structure you like, here are 2 proposals: a linked list OR
//an array (up to 100 names).
//The linked list will be faster since you only need to lock one node, while for
//the array you need to lock the whole array.
//You can use a linked list template from A5. You should also consider using a hash
//table, like in A5 (even faster).

struct node {
    int count; // store line number
    char name[30]; // store command
    struct node* next;  // ptr to next node
};
typedef struct node countName;
countName* head = NULL;
countName *curr = NULL;

/**
 * This linkedList() function create a node for linkedList
 * Assumption: N/A
 * Input parameters: char* string, int line
 * Returns: ptr
**/
countName* linkedList(char string[30], int n)
{
    countName* ptr;
    ptr = (countName*) malloc(sizeof(countName));
    if (ptr == NULL) {
    printf("linkedList: memory allocation error\n");
    exit(1);
  }
    ptr->count = n;
    strcpy(ptr->name,string);
    ptr->next=NULL;
    return ptr;

}
void PrintNode(countName* ptr)
{
    printf("%s : %d\n",ptr->name,ptr->count);
    if(ptr->next != NULL){
        PrintNode(ptr->next);
    }

    if(ptr->next != NULL){
        free(ptr->next);
    }
}


/*********************************************************
// function main
*********************************************************/
int main(int argc, char *argv[]){
//TODO similar interface as A2: give as command-line arguments three filenames of
     // check if any file was given from command line
    if(argc < 3){
        printf("Not enough input file given\n");
        exit(1);
    }
     // check if more than two file was given from command line numbers
     //(the numbers in the files are newline-separated).
    if(argc > 3){
        printf("Only two files are allowed\n");
        exit(1);
    }

    printf("create first thread\n");
    pthread_create(&tid1,NULL,thread_runner,argv[1]);
    printf("create second thread\n");
    pthread_create(&tid2,NULL,thread_runner,argv[2]);
    //printf("wait for first thread to exit\n");
    pthread_join(tid1,NULL);
    printf("first thread exited\n");
    //printf("wait for second thread to exit\n");
    pthread_join(tid2,NULL);
    printf("second thread exited\n");
    //TODO print out the sum variable with the sum of all the numbers
    printf("==========Name Counts==========\n");
    PrintNode(head);
    free(head);

    exit(0);
}//end main
/**********************************************************************
// function thread_runner runs inside each thread
**********************************************************************/

void* thread_runner(void* x)
{
    char *filename = (char*)x;
    char str[30];
    // variables to store date and time components
    int hours, minutes, seconds, day, month, year;
    // time_t is arithmetic time type
    time_t now;
    // Obtain current time
    // time() returns the current time of the system as a time_t value
    time(&now);
    struct tm *local = localtime(&now);
    hours = local->tm_hour; // get hours since midnight (0-23)
    minutes = local->tm_min; // get minutes passed after the hour (0-59)
    seconds = local->tm_sec; // get seconds passed after minute (0-59)
    day = local->tm_mday; // get day of month (1 to 31)
    month = local->tm_mon + 1; // get month of year (0 to 11)
    year = local->tm_year + 1900; // get year since 1900

    int line = 0;
    pthread_t me;
    me = pthread_self();

    // critical section starts
    pthread_mutex_lock(&tlock2);
    if (p==NULL) {
        p = (THREADDATA*) malloc(sizeof(THREADDATA));
        p->creator=me;
    }
    pthread_mutex_unlock(&tlock2);
    // critical section ends

    if (p!=NULL && p->creator==me) {

        pthread_mutex_lock(&tlock1);
        if (hours < 12){
            printf("Logindex %d, thread %ld, PID %d, %02d/%02d/%d %02d:%02d:%02d am: This is thread %ld and I created THREADDATA %p\n",logindex,me,getpid(), day, month, year,hours, minutes, seconds,me,p);
        }
        else{

            printf("Logindex %d, thread %ld, PID %d, %02d/%02d/%d %02d:%02d:%02d pm: This is thread %ld and I created THREADDATA %p\n",logindex,me,getpid(), day, month, year,hours-12, minutes, seconds,me,p);
        }
        logindex++;


        pthread_mutex_unlock(&tlock1);

    }
    else {

        pthread_mutex_lock(&tlock1);
        if (hours < 12){
            printf("Logindex %d, thread %ld, PID %d, %02d/%02d/%d %02d:%02d:%02d am: This is thread %ld and I can access the THREADDATA %p\n",logindex,me,getpid(), day, month, year,hours, minutes, seconds,me,p);
        }
        else{

            printf("Logindex %d, thread %ld, PID %d, %02d/%02d/%d %02d:%02d:%02d pm: This is thread %ld and I can access the THREADDATA %p\n",logindex,me,getpid(), day, month, year,hours-12, minutes, seconds,me,p);
        }
        logindex++;
        pthread_mutex_unlock(&tlock1);
    }
/**
* //TODO implement any thread name counting functionality you need.
* Assign one file per thread. Hint: you can either pass each argv filename as a
thread_runner argument from main.
* Or use the logindex to index argv, since every thread will increment the
logindex anyway
* when it opens a file to print a log message (e.g. logindex could also index
argv)....
* //Make sure to use any mutex locks appropriately
*/
    sleep(2);
    FILE *f = fopen(filename,"r");
    // if file cannot open, print error message
    if (f == NULL){
            fprintf(stderr, "range: cannot open file %s\n",filename);
            exit(1);
        }
    pthread_mutex_lock(&tlock1);
    if (hours < 12){
        printf("Logindex %d, thread %ld, PID %d, %02d/%02d/%d %02d:%02d:%02d am: opened file %s\n",logindex,me,getpid(), day, month, year,hours, minutes, seconds,filename);
    }
    else{

        printf("Logindex %d, thread %ld, PID %d, %02d/%02d/%d %02d:%02d:%02d pm: opened file %s\n",logindex,me,getpid(), day, month, year,hours-12, minutes, seconds,filename);
    }

    logindex++;
    pthread_mutex_unlock(&tlock1);

    while (fgets(str, 30, f)){

        line++;

        // if the current line is empty, print warning message
        if(strcmp(str,"\n") == 0){
            fprintf(stderr,"Warning - %s Line %d is empty.\n", filename, line);
            continue;
        }
        if(str[strlen(str) -1] == '\n'){
            str[strlen(str) - 1] = '\0';
        }

        pthread_mutex_lock(&tlock3);
        if(head == NULL){
            head = linkedList(str,1);
            curr = head;
        }
        else{
            int newName = 1;
            countName* tmp = head;

            while(tmp != NULL){
                if (strcmp(tmp->name,str) == 0) {
                    tmp->count++;
                    newName = 0;

                }
                tmp = tmp->next;
            }

            if(newName){
                curr->next = linkedList(str,1);
                curr = curr->next;
            }
        }
        pthread_mutex_unlock(&tlock3);

    }
    fclose(f);


// TODO use mutex to make this a start of a critical section

    /**
    * TODO Free the THREADATA object.
    * Freeing should be done by the same thread that created it.
    * See how the THREADDATA was created for an example of how this is done.
    */
    pthread_mutex_lock(&tlock2);
    if (p!=NULL && p->creator==me) {
        free(p);
        p = NULL;
        if (hours < 12){
            printf("Logindex %d, thread %ld, PID %d, %02d/%02d/%d %02d:%02d:%02d am: This is thread %ld and I deleted THREADDATA\n",logindex,me,getpid(), day, month, year,hours, minutes, seconds,me);
        }
        else{

            printf("Logindex %d, thread %ld, PID %d, %02d/%02d/%d %02d:%02d:%02d pm: This is thread %ld and I deleted THREADDATA\n",logindex,me,getpid(), day, month, year,hours-12, minutes, seconds,me);
        }
        logindex++;
    }
    else {
        if (hours < 12){
            printf("Logindex %d, thread %ld, PID %d, %02d/%02d/%d %02d:%02d:%02d am: This is thread %ld and I can access the THREADDATA\n",logindex,me,getpid(), day, month, year,hours, minutes, seconds,me);
        }
        else{

            printf("Logindex %d, thread %ld, PID %d, %02d/%02d/%d %02d:%02d:%02d pm: This is thread %ld and I can access the THREADDATA\n",logindex,me,getpid(), day, month, year,hours-12, minutes, seconds,me);
        }
        logindex++;
    }

    pthread_mutex_unlock(&tlock2);
    // TODO critical section ends
    pthread_exit(NULL);

    return NULL;
}
//end thread_runner

