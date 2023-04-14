/**
 * Description: This module implements Contacts
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date: 4/14/2023
 * Creation date:4/14/2023
 **/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//ContractNode struct definition
typedef struct ContactNode_struct{
    char contactName[60];
    char contactPhoneNumber[60];
    struct ContactNode_struct* nextNodePtr;
} ContactNode;


/**
 * This function initialize node to NULL
 * Assumption: n/a
 * Input parameters: ContactNode *p
 * Returns: void
**/
void InitializeContactNode(ContactNode *p){
    p = NULL;
}

/**
 * This function get a contact name for a specific node
 * Assumption: The string will always contain less than 60 characters
 * Input parameters: ContactNode *n
 * Returns: name
**/
char* GetName(ContactNode *n){
    char *name;
    name = malloc(sizeof(char)*60);
    if(n != NULL){
        strcpy(name,n->contactName);
    }
    return name;
}
/**
 * This function get a contact phone number for a specific node
 * Assumption: The string will always contain less than 60 characters
 * Input parameters: ContactNode *phone
 * Returns: phoneNumber
**/
char* GetPhoneNumber(ContactNode *phone){
    char *phoneNumber;
    phoneNumber = malloc(sizeof(char)*60);
    if(phone != NULL){
        strcpy(phoneNumber,phone->contactPhoneNumber);
    }
    return phoneNumber;

}
/**
 * This function create linkedlist
 * Assumption: n/a
 * Input parameters: ContactNode *thisNode, ContactNode *newNode
 * Returns: void
**/
void insertAfter(ContactNode *thisNode, ContactNode *newNode){
    ContactNode* tmpNext = NULL;
    tmpNext = thisNode->nextNodePtr;
    thisNode->nextNodePtr = newNode;
    newNode->nextNodePtr = tmpNext;
    return;

}
/**
 * This function gets nextNode
 * Assumption: n/a
 * Input parameters: ContactNode *node
 * Returns: nextNode
**/
ContactNode* GetNext(ContactNode *node){
    ContactNode *nextNode;
    if(node->nextNodePtr != NULL){
        nextNode =node->nextNodePtr;

    }
    return nextNode;

}
/**
 * This function print all the contact information in linkedlist
 * Assumption: n/a
 * Input parameters: ContactNode *ptr
 * Returns: void
**/

void PrintContactNode(ContactNode *ptr){
    while(ptr != NULL){
    printf("Name: %s\n", ptr->contactName);
    printf("Phone number: %s\n\n", ptr->contactPhoneNumber);
    ptr = ptr->nextNodePtr;

    }

}

/**
 * This main function prompt user enter contact information
   then store the information into linkedlist and print out all the contact information
 * Assumption: The string will always contain less than 60 characters
 * Input parameters: n/a
 * Returns: an integer(0 - program normal exit, non 0 - program error)
**/
int main()
{
    // create three ContactNode
    ContactNode *first = NULL;
    ContactNode *second = NULL;
    ContactNode *third = NULL;
    //allocate memory
    first = malloc(sizeof(ContactNode));
    second = malloc(sizeof(ContactNode));
    third = malloc(sizeof(ContactNode));
    // Initialize each ContactNode
    InitializeContactNode(first);
    InitializeContactNode(second);
    InitializeContactNode(third);
    /* read user input for contact information, then store it to node*/
    char temp[60];
    // person 1
    printf("Please enter 3 contact information, name follow with phone number:\n");
    fgets(temp,60,stdin);
    if(temp[strlen(temp)-1] == '\n') temp[strlen(temp)-1] = '\0';
    strcpy(first->contactName,temp);
    fgets(temp,60,stdin);
    if(temp[strlen(temp)-1] == '\n') temp[strlen(temp)-1] = '\0';
    strcpy(first->contactPhoneNumber,temp);
    // person 2
    fgets(temp,60,stdin);
    if(temp[strlen(temp)-1] == '\n') temp[strlen(temp)-1] = '\0';
    strcpy(second->contactName,temp);
    fgets(temp,60,stdin);
    if(temp[strlen(temp)-1] == '\n') temp[strlen(temp)-1] = '\0';
    strcpy(second->contactPhoneNumber,temp);
    // person 3
    fgets(temp,60,stdin);
    if(temp[strlen(temp)-1] == '\n') temp[strlen(temp)-1] = '\0';
    strcpy(third->contactName,temp);
    fgets(temp,60,stdin);
    if(temp[strlen(temp)-1] == '\n') temp[strlen(temp)-1] = '\0';
    strcpy(third->contactPhoneNumber,temp);

    // print out three contact information
    printf("Person 1 : %s, %s\n",GetName(first), GetPhoneNumber(first));
    printf("Person 2 : %s, %s\n",GetName(second), GetPhoneNumber(second));
    printf("Person 3 : %s, %s\n\n",GetName(third), GetPhoneNumber(third));
    // build linkedlist use function insertAfter()
    insertAfter(first,second);
    insertAfter(second,third);

    // print out all the contact information in the linkedlist
    printf("CONTACT LIST\n");
    PrintContactNode(first);

    // de-allocate memory
    free(first);
    free(second);
    free(third);

    return 0;
}

