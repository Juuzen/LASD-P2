//
// Created by backs on 20/05/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "orderManagement.h"
#include "stdlib.h"

void freeOrderNode(PtrOrder node) {
    if (node != NULL) {
        node->next = NULL;
        node->quantity = 0;
        node->item.codProduct = 0;
        node->item.specificWeight = 0;
        memset(node->item.itemLabel, '\0', sizeof(node->item.itemLabel));
        free(node);
    }
}

void freeOrderList(PtrOrder list) {
    if (list != NULL) {
        freeOrderList(list->next);
        freeOrderNode(list);
    }
}

bool findOrder(PtrOrder list, int productCode) {
    if (list == NULL) return false;
    if (list->item.codProduct == productCode) return true;
    else return findOrder(list->next, productCode);
}

PtrOrder removeOrder(PtrOrder list, int productCode) {
    if (list == NULL) return NULL;
    if (list->item.codProduct == productCode) {
        PtrOrder tmp = list->next;
        freeOrderNode(list);
        return tmp;
    }
    list->next = removeOrder(list->next, productCode);
    return list;
} 

PtrOrder createNewOrder(Item item, int quantity) {
    PtrOrder order;
    order = (PtrOrder)calloc(1, sizeof (Order));
    if(order!=NULL) {
        order->item = item;
        order->quantity = quantity;
        order->next = NULL;
    }
    return order;
}

PtrOrder mergeLists (PtrOrder driverList, PtrOrder cartList) {
    PtrOrder tmpOrder = NULL;
    while (cartList != NULL) {
        tmpOrder = createNewOrder(cartList->item, cartList->quantity);
        driverList = insertOrderMergeOrEnd(driverList, tmpOrder);
        cartList = cartList->next;
    }

    return driverList;
}

PtrOrder insertOrderMergeOrEnd(PtrOrder list, PtrOrder order) {
    if (list == NULL) return order;
    if (list->item.codProduct == order->item.codProduct) {
        list->quantity += order->quantity;
        /* Questo elemento può essere eliminato dal momento il suo contenuto viene incluso nella lista */
        freeOrderNode(order);
        return list;
    }
    list->next = insertOrderMergeOrEnd(list->next, order);
    return list;
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
        return head->quantity * head->item.specificWeight + calculateOrderWeight(head->next);
    }
}

void printOrderList2(PtrOrder list) {
        if (list != NULL) {
            printf("%s: x%d (%d kg)\n", list->item.itemLabel, list->quantity, list->item.specificWeight * list->quantity);
            printOrderList(list->next);
    }
}

void printOrderList(PtrOrder head) {

    if (head == NULL) {
        return;
    }

    int i = 1;
    while(head) {
        printf("%d)\n",i);
        printf("Codice: %d\n", head->item.codProduct);  //Issue #21
        printf("Nome: %s\n", head->item.itemLabel);
        printf("Peso specifico (per cassa): %d kg\n", head->item.specificWeight);
        printf("Quantita': %d\n\n", head->quantity);
        head = head->next;
        i++;
    }
}

PtrCatalogue findElement(PtrCatalogue catalogueItem, int productCode)
{
    if (catalogueItem == NULL) return NULL;
    if (catalogueItem->item.codProduct == productCode) return catalogueItem;
    return findElement(catalogueItem->next, productCode);

}