//
// Created by backs on 20/05/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include "orderManagement.h"

PtrOrder createNewOrder(Item item, int quantity) {
    PtrOrder order = (PtrOrder) calloc(1, sizeof(Order));
    if (order != NULL) {
        order->item = item;
        order->quantity = quantity;
        order->next = NULL;
    }

    return order;
}

PtrOrder insertOrderOnEnd(PtrOrder head, PtrOrder order) {
    if (head == NULL) {
        return order;
    }

    head->next = insertOrderOnEnd(head->next, order);
    return head;
}

int calculateOrderWeight(PtrOrder head) {
    if (head == NULL) {
        return 0;
    } else {
        return head->quantity + calculateOrderWeight(head->next);
    }
}

void printOrderList(PtrOrder head) {
    if (head == NULL) {
        return;
    }

    printf("%s\t%d\t%d\n", head->item.itemLabel, head->item.specificWeight, head->quantity);
    printOrderList(head->next);
}