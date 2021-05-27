#ifndef LASD_P2_ORDER_H
#define LASD_P2_ORDER_H
#include <stdbool.h>
#include "item.h"

typedef struct order {
    Item item;
    int quantity;
    struct order *next;
} order;

typedef struct order* Order;

void order_freeNode (Order node);
void order_freeList (Order list);
bool order_findItem (Order list, int itemCode);
Order order_removeItem (Order list, int itemCode);
Order order_new (Item item, int orderQuantity);
Order order_mergeLists (Order primaryList, Order secondaryList);
Order order_mergeInsert (Order list, Order order);
int order_getTotalWeight (Order list);
void order_print(Order list);

#endif //LASD_P2_ORDERMANAGEMENT_H
