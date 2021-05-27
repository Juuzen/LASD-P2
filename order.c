#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "order.h"

/*  Dealloca un elemento Order. */
void order_freeNode (Order node) {
    if (node != NULL) {
        node->next = NULL;
        node->quantity = 0;
        node->item.code = 0;
        node->item.weight = 0;
        memset(node->item.label, '\0', sizeof(node->item.label));
        free(node);
    }
}

/*  Dealloca una lista di elementi Order. */
void order_freeList (Order list) {
    if (list != NULL) {
        order_freeList (list->next);
        order_freeNode (list);
    }
}

/*  Controlla se un elemento Order è presente nella lista, controllando il relativo Item. 
 *  Output:
 *  FALSE: l'elemento non è presente
 *  TRUE: l'elemento è stato trovato con successo
 */
bool order_findItem (Order list, int itemCode) {
    if (list == NULL) return false;
    if (list->item.code == itemCode) return true;
    else return order_findItem(list->next, itemCode);
}

/*  Rimuove da una lista di elementi Order, quello il cui item corrisponde al codice passato in input. 
 *  Output:
 *  Order list: la lista correttamente modificata.
 */
Order order_removeItem (Order list, int itemCode) {
    if (list == NULL) return NULL;
    if (list->item.code == itemCode) {
        Order tmp = list->next;
        order_freeNode(list);
        return tmp;
    }
    list->next = order_removeItem(list->next, itemCode);
    return list;
} 

/*  Alloca dinamicamente un elemento Order.
 *  Output:
 *  NULL: ERRORE in allocazione della memoria
 *  Order order: elemento Order correttamente allocato
 */
Order order_new (Item item, int quantity) {
    Order order;
    order = (Order)calloc(1, sizeof (order));
    if(order!=NULL) {
        order->item = item;
        order->quantity = quantity;
        order->next = NULL;
    }
    return order;
}

/*  Unisce la lista secondaryList all'interno della lista primaryList.
 *  Output:
 *  Order primaryList: la lista correttamente processata.
 */
Order order_mergeLists (Order primaryList, Order secondaryList) {
    Order tmpOrder = NULL;

    /* Fintanto che secondaryList non è vuota */
    while (secondaryList != NULL) {
        /* Creo un duplicato del nodo corrente di secondaryList */
        tmpOrder = order_new(secondaryList->item, secondaryList->quantity);

        /* Inserisco tale duplicato in primaryList */
        primaryList = order_mergeInsert(primaryList, tmpOrder);

        /* Procedo col prossimo elemento di secondaryList */
        secondaryList = secondaryList->next;
    }

    return primaryList;
}

/*  Inserisce un elemento Order in coda alla lista. Se è già presente un elemento con lo stesso
 *  Item, ne incrementa la quantità invece. 
 *  Output:
 *  Order list: la lista correttamente processata.
 */
Order order_mergeInsert (Order list, Order order) {
    if (list == NULL) return order;
    if (list->item.code == order->item.code) {
        list->quantity += order->quantity;
        /* Questo elemento può essere eliminato dal momento il suo contenuto viene incluso nella lista */
        order_freeNode(order);
        return list;
    }
    list->next = order_mergeInsert (list->next, order);
    return list;
}

/*  Restituisce il peso totale di tutta la lista di elementi Order.
 *  Output:
 *  int totalWeight: il peso di tutti gli elementi Order, correttamente calcolato.
 */
int order_getTotalWeight (Order list) {
    if (list == NULL) return 0;
    else return (list->item.weight * list->quantity) + order_getTotalWeight(list->next);
}

/* Stampa su stdout una lista di elementi Order. */
void order_print(Order list) {
    if (list != NULL) {
        item_print(list->item);
        printf("Peso complessivo: %d kg\n\n", list->quantity * list->item.weight);
        order_print(list->next);
    }
}

