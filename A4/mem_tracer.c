/**
 * Description: This module reads commands from stdin line by line into a dynamically allocated array and linkedList
 * then trace the memory usage
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date:4/10/2023
 * Creation date: 4/05/2023
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

/**
 *CS149 assignment#4 helper code.
 * See the TODO's in the comments below! You need to implement those.
**/

/**
 *TRACE_NODE_STRUCT is a linked list of
 *pointers to function identifiers
 *TRACE_TOP is the head of the list is the top of the stack
**/
struct TRACE_NODE_STRUCT {
  char* functionid;                // ptr to function identifier (a function name)
  struct TRACE_NODE_STRUCT* next;  // ptr to next frama
};
typedef struct TRACE_NODE_STRUCT TRACE_NODE;
static TRACE_NODE* TRACE_TOP = NULL;       // ptr to the top of the stack


/* --------------------------------*/
/* function PUSH_TRACE */
/*
 * The purpose of this stack is to trace the sequence of function calls,
 * just like the stack in your computer would do.
 * The "global" string denotes the start of the function call trace.
 * The char *p parameter is the name of the new function that is added to the call trace.
 * See the examples of calling PUSH_TRACE and POP_TRACE below
 * in the main, make_extend_array, add_column functions.
**/
void PUSH_TRACE(char* p)          // push p on the stack
{
  TRACE_NODE* tnode;
  static char glob[]="global";

  if (TRACE_TOP==NULL) {

    // initialize the stack with "global" identifier
    TRACE_TOP=(TRACE_NODE*) malloc(sizeof(TRACE_NODE));

    // no recovery needed if allocation failed, this is only
    // used in debugging, not in production
    if (TRACE_TOP==NULL) {
      printf("PUSH_TRACE: memory allocation error\n");
      exit(1);
    }

    TRACE_TOP->functionid = glob;
    TRACE_TOP->next=NULL;
  }//if

  // create the node for p
  tnode = (TRACE_NODE*) malloc(sizeof(TRACE_NODE));

  // no recovery needed if allocation failed, this is only
  // used in debugging, not in production
  if (tnode==NULL) {
    printf("PUSH_TRACE: memory allocation error\n");
    exit(1);
  }//if

  tnode->functionid=p;
  tnode->next = TRACE_TOP;  // insert tnode as the first in the list
  TRACE_TOP=tnode;          // point TRACE_TOP to the first node

}/*end PUSH_TRACE*/

/* --------------------------------*/
/* function POP_TRACE */
/* Pop a function call from the stack */
void POP_TRACE()    // remove the op of the stack
{
  TRACE_NODE* tnode;
  tnode = TRACE_TOP;
  TRACE_TOP = tnode->next;
  free(tnode);

}/*end POP_TRACE*/



/* ---------------------------------------------- */
/* function PRINT_TRACE prints out the sequence of function calls that are on the stack at this instance */
/* For example, it returns a string that looks like: global:funcA:funcB:funcC. */
/* Printing the function call sequence the other way around is also ok: funcC:funcB:funcA:global */
char* PRINT_TRACE()
{
  int depth = 50; //A max of 50 levels in the stack will be combined in a string for printing out.
  int i, length, j;
  TRACE_NODE* tnode;
  static char buf[100];

  if (TRACE_TOP==NULL) {     // stack not initialized yet, so we are
    strcpy(buf,"global");   // still in the `global' area
    return buf;
  }

  /* peek at the depth(50) top entries on the stack, but do not
     go over 100 chars and do not go over the bottom of the
     stack */

  sprintf(buf,"%s",TRACE_TOP->functionid);
  length = strlen(buf);                  // length of the string so far
  for(i=1, tnode=TRACE_TOP->next;
                        tnode!=NULL && i < depth;
                                  i++,tnode=tnode->next) {
    j = strlen(tnode->functionid);             // length of what we want to add
    if (length+j+1 < 100) {              // total length is ok
      sprintf(buf+length,":%s",tnode->functionid);
      length += j+1;
    }else                                // it would be too long
      break;
  }
  return buf;
} /*end PRINT_TRACE*/

// -----------------------------------------
// function REALLOC calls realloc
// TODO REALLOC should also print info about memory usage.
// TODO For this purpose, you need to add a few lines to this function.
// For instance, example of print out:
// "File tracemem.c, line X, function F reallocated the memory segment at address A to a new size S"
// Information about the function F should be printed by printing the stack (use PRINT_TRACE)
void* REALLOC(void* p,int t,char* file,int line)
{
	p = realloc(p,t);
    printf("File %s, line %i, function %s reallocated the memory segment at address %p to a new size %i\n", file, line, PRINT_TRACE(), p, t);
	return p;
}

// -------------------------------------------
// function MALLOC calls malloc
// TODO MALLOC should also print info about memory usage.
// TODO For this purpose, you need to add a few lines to this function.
// For instance, example of print out:
// "File tracemem.c, line X, function F allocated new memory segment at address A to size S"
// Information about the function F should be printed by printing the stack (use PRINT_TRACE)
void* MALLOC(int t,char* file,int line)
{
	void* p;
	p = malloc(t);
    printf("File %s, line %i, function %s allocated new memory segment at address %p to size %i\n", file, line, PRINT_TRACE(), p, t);

	return p;
}

// ----------------------------------------------
// function FREE calls free
// TODO FREE should also print info about memory usage.
// TODO For this purpose, you need to add a few lines to this function.
// For instance, example of print out:
// "File tracemem.c, line X, function F deallocated the memory segment at address A"
// Information about the function F should be printed by printing the stack (use PRINT_TRACE)
void FREE(void* p,char* file,int line)
{
	free(p);
    printf("File %s, line %i, function %s deallocated the memory segment at address %p\n", file, line, PRINT_TRACE(), p);

}

#define realloc(a,b) REALLOC(a,b,__FILE__,__LINE__)
#define malloc(a) MALLOC(a,__FILE__,__LINE__)
#define free(a) FREE(a,__FILE__,__LINE__)


// -----------------------------------------
// function add_column will add an extra column to a 2d array of ints.
// This function is intended to demonstrate how memory usage tracing of realloc is done
// Returns the number of new columns (updated)
/*int add_column(int** array,int rows,int columns)
{
	PUSH_TRACE("add_column");
	int i;

	for(i=0; i<rows; i++) {
	 array[i]=(int*) realloc(array[i],sizeof(int)*(columns+1));
	 array[i][columns]=10*i+columns;
	}//for
	POP_TRACE();
        return (columns+1);
}// end add_column
*/

struct node {
    int n; // store line number
    char* str; // store command
    struct node* link;  // ptr to next node
};
typedef struct node node_c;

/**
 * This linkedList() function create a node for linkedList
 * Assumption: N/A
 * Input parameters: char* string, int line
 * Returns: ptr
**/
node_c* linkedList(char* string, int line)
{
    PUSH_TRACE("linkedList");

    node_c* ptr;
    ptr = (node_c*) malloc(sizeof(node_c));
    if (ptr == NULL) {
    printf("linkedList: memory allocation error\n");
    exit(1);
  }

    ptr->n = line;
    ptr->str = strdup(string);
    ptr->link=NULL;

    POP_TRACE();
    return ptr;

}
/**
 * This PrintNode() function prints content stored in LinkedList then deallocate memory to avoid memory leak
 * Assumption: N/A
 * Input parameters: node_c ptr
 * Returns: void
**/
void PrintNode(node_c* ptr)
{
    PUSH_TRACE("PrintNode");
    printf("LinkedList = Line %d  with command: %s\n",ptr->n,ptr->str);
    if(ptr->link != NULL){
        PrintNode(ptr->link);
    }
    free(ptr->str);
    if(ptr->link != NULL){
        free(ptr->link);
    }

    POP_TRACE();
}

/**
 * This read_command() function read commands from stdin and store each command into dynamic array and LinkedList
 * Assumption: N/A
 * Input parameters: N/A
 * Returns: void
**/
void read_command()
{
    PUSH_TRACE("read_command");
    char * line = NULL; // for tracking line when reading from stdin
    size_t len = 0;
    ssize_t read;
    int line_number = 0;
    int size = 10;
    char **command = (char**) malloc(size * sizeof(char*));
    node_c* head;
    node_c *curr;

    // get commands from stdin until ctrl d, then store each command into dynamic array and LinkedList
    while ((read = getline(&line, &len, stdin)) != -1)
    {
        // if not enough space, realloc double the original size
        if (line_number == size) {
            size *= 2;
            command = realloc(command, size * sizeof(char*));
        }
        command[line_number] = (char*) malloc((read+1) * sizeof(char));
        for(int i=0;i<=(strlen(line));i++)
        {
        // if newline found, assign NULL into line[i]
            if(line[i] == '\n'){
                line[i]='\0';
            }
        }
        strcpy(command[line_number], line);
        // store command and line number to LinkedList
        if(line_number == 0){
            head = linkedList(line,line_number+1);
            curr = head;
        }
        else{
            curr->link = linkedList(line,line_number+1);
            curr = curr->link;
        }

        line_number++;

    }
    // print content from linkedList
    PrintNode(head);
    // print content from dynamically allocated array
    for(int i = 0; i < line_number; i++)
    {
	    printf("Dynamical array = command[%d] = %s\n",i,command[i]);
    }

	 //now deallocate it
	for(int i= 0; i < line_number; i++)
	    free((void*)command[i]);

	free((void*)command);
    free(head);
    if(line) free(line);

	POP_TRACE();
    return;
}

/**
 * This writeFile() function redirect std_out to memtrace log file
 * Assumption: N/A
 * Input parameters: N/A
 * Returns: an integer(0 - program normal exit, non 0 - program error)
**/
int writeFile()
{
    PUSH_TRACE("writeFile");
    char* pathname = "memtrace.out";
    int f = open(pathname, O_RDWR | O_CREAT | O_APPEND, 0777 );
    dup2(f,1);
    close(f);
    POP_TRACE();
    return 0;
}

/**
 * This driver function calls function writeFile() and read_command()
 * Assumption: N/A
 * Input parameters: N/A
 * Returns: an integer(0 - program normal exit, non 0 - program error)
**/
int main()
{
    PUSH_TRACE("main");

    if(writeFile() != 0) printf("error create memtrace log file\n");

	read_command();

    POP_TRACE();
    #undef free
    free(TRACE_TOP);

    return(0);
}






