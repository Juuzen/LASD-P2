//
// Created by backs on 20/05/2021.
//

#ifndef LASD_P2_ORDERMANAGEMENT_H
#define LASD_P2_ORDERMANAGEMENT_H

#include "productCatalogue.h"

typedef struct Order {
    Item item;
    int quantity;
    struct Order *next;
} Order;

typedef struct Order* PtrOrder;

void freeOrderNode(PtrOrder node);
void freeOrderList(PtrOrder list);
PtrOrder createNewOrder(Item item, int quantity);
PtrOrder mergeLists(PtrOrder mainList, PtrOrder addList);
PtrOrder insertOrderMergeOrEnd(PtrOrder list, PtrOrder order);
PtrOrder insertOrderOnEnd(PtrOrder head, PtrOrder order);
int calculateOrderWeight(PtrOrder orderList);
void printOrderList(PtrOrder orderList);
PtrCatalogue findElement(PtrCatalogue catalogue,int code);

#endif //LASD_P2_ORDERMANAGEMENT_H
