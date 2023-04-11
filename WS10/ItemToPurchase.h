/**
 header file includes libraries, struct definitions and function prototype
 **/
#include <stdio.h>
#include <string.h>
struct Items {
    char  itemName[60];
    int itemPrice;
    int itemQuantity;
};

void MakeItemBlank(struct Items *item);
void PrintItemCost(struct Items *item);
