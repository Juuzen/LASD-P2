//
// Created by backs on 20/05/2021.
//

#include "stdio.h"
#include "orderManagement.h"
#include "stdlib.h"


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

void printOrderList(PtrOrder head) {

    if (head == NULL) {
        return;
    }

    int i = 1;
    while(head) {
        printf("%d)\n",i);
        printf("Nome: %s\n", head->item.itemLabel);
        printf("Peso specifico (per cassa): %d kg\n", head->item.specificWeight);
        printf("Quantita': %d\n\n", head->quantity);
        head = head->next;
        i++;
    }
}

PtrCatalogue findElement(PtrCatalogue catalogue,int code)
{
    PtrCatalogue find = catalogue;
    if(find == NULL){
        return NULL;
    }

    if (catalogue !=NULL && code!=catalogue->item.codProduct)
        find = findElement(catalogue->next,code);

    return find;

}

PtrOrder addToCart(PtrCatalogue catalogue){

    int productCode;
    int quantity;

    printf("\nInserisci il codice del prodotto desiderato:\n");
    scanf("%d",&productCode);


    while(productCode<111 || productCode>121){
        printf("\nProdotto non disponibile\n");
        printf("\nInserisci il codice del prodotto desiderato:\n");
        scanf("%d",&productCode);
    }

    printf("\nIn che quantita'?\n");
    scanf("%d",&quantity);

    PtrCatalogue find = NULL;
    find = findElement(catalogue,productCode);

    PtrOrder singleElement = NULL;
    singleElement = createNewOrder(find->item,quantity);

    return singleElement;

}


