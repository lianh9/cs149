/**
 * Description: This module implements Online shopping cart
 * Author names: Lian Huang
 * Author emails: lian.huang@sjsu.edu
 * Last modified date: 4/10/2023
 * Creation date:4/05/2023
 **/
#include "ItemToPurchase.h"
/**
 * This main function prompt user enter item information
   then store the information into struct
 * Assumption: The string will always contain less than 60 characters
 * Input parameters: n/a
 * Returns: an integer(0 - program normal exit, non 0 - program error)
**/
int main()
{
    char c;
    char str[60];
    struct Items item1;
    struct Items item2;
    MakeItemBlank(&item1);
    MakeItemBlank(&item2);
    // Item 1
    printf("Item 1\n");
    printf("Enter the item name:\n");
    fgets(str,60,stdin);
    str[strlen(str) -1] = '\0';
    strcpy(item1.itemName,str);
    printf("Enter the item price:\n");
    scanf("%d",&item1.itemPrice);
    printf("Enter the item quantity:\n");
    scanf("%d",&item1.itemQuantity);


    c = getchar();
    while(c !='\n' && c != EOF){
        c = getchar();
    }
    // Item 2
    printf("Item 2\n");
    printf("Enter the item name:\n");
    fgets(str,60,stdin);
    str[strlen(str) -1] = '\0';
    strcpy(item2.itemName,str);
    printf("Enter the item price:\n");
    scanf("%d",&item2.itemPrice);
    printf("Enter the item quantity:\n");
    scanf("%d",&item2.itemQuantity);
    // print out total cost
    printf("TOTAL COST\n");
    PrintItemCost(&item1);
    PrintItemCost(&item2);
    printf("Total: $%d",item1.itemPrice*item1.itemQuantity + item2.itemPrice*item2.itemQuantity);
    printf("\n");


    return 0;
}
