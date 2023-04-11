#include "ItemToPurchase.h"

 /**
 * This function initialize struct object passed by
 * Assumption: N/A
 * Input parameters: struct Items *item
 * Returns: void
**/
void MakeItemBlank(struct Items *item){
    strcpy(item->itemName,"none");
    item->itemPrice = 0;
    item->itemQuantity = 0;

}
/**
 * This function prints out content in the struct object passed by
 * Assumption: N/A
 * Input parameters: struct Items *item
 * Returns: void
**/
void PrintItemCost(struct Items *item){

    printf("%s %d @ $%d = $%d\n",item->itemName, item->itemQuantity, item->itemPrice, item->itemQuantity*item->itemPrice);

}
