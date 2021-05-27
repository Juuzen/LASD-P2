#ifndef LASD_P2_ITEM_H
#define LASD_P2_ITEM_H
#include "const.h"

typedef struct Item {
    char label[MAX_ITEM_LABEL_SIZE];    //takes in account already the + 1
    int code;
    int weight;
} Item;

Item item_new(char *label, int specificWeight, int codProduct);
void item_print(Item item);

#endif