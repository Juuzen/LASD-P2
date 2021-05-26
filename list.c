#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

/* Dealloca un elemento List */
void list_freeNode(List node) {
    if (node != NULL) {
        node->value = 0;
        node->next = NULL;
        free(node);
    }
}

/* Dealloca una lista di elementi List */
void list_freeList(List L) {
    if (L != NULL) {
        list_freeList(L->next);
        list_freeNode(L);
    }
}

/* Alloca dinamicamente un elemento List */
List list_newNode(int value) {
    List node = (List) calloc(1, (sizeof(list)));
    if (node != NULL) {
        node->value = value;
        node->next = NULL;
    }
    return node;
}

/* Inserisce un elemento List in fondo alla lista */
List list_enqueue(List queue, int value) {
    if (queue == NULL) return list_newNode(value);
    queue->next = list_enqueue(queue->next, value);
    return queue;
}

/* Estrae, se possibile, un elemento List dalla lista (trattata come coda) restituendo il suo campo value */
/* Altrimenti, ritorna -1 */
int list_dequeue(List* queue) {
    if ((*queue) != NULL) {
        List tmp = (*queue);
        (*queue) = (*queue)->next;
        int value = tmp->value;
        list_freeNode(tmp);
        return value;
    }

    else return -1;
}

/* Restituisce true se trova l'elemento key nella lista */
/* Altrimenti false */
bool list_findValue(List L, int key) {
    if (L == NULL) return false;
    if (L->value == key) return true;
    return list_findValue(L->next, key);
}

