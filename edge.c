#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utils.h"
#include "edge.h"

/* Dealloca un elemento Edge */
void edge_freeNode(Edge node) {
    if (node != NULL) {
        node->sourceIndex = 0;
        node->destIndex = 0;
        node->weight = 0;
        node->next = NULL;
    }
}

/* Dealloca una lista di elementi Edge */
void edge_freeList(Edge list) {
    if (list != NULL) {
        edge_freeList(list->next);
        edge_freeNode(list);
    }
}

/* Alloca dinamicamente un elemento Edge e lo passa in output */
Edge edge_newNode(int source, int dest, int weight) {
    Edge E = (Edge) calloc(1, sizeof(edge));
    if (E != NULL) {
        E->sourceIndex = source;
        E->destIndex = dest;
        E->weight = weight;
        E->next = NULL;
    }

    return E;
}

/* Crea un elemento Edge e lo inserisce in coda alla lista */
Edge edge_tailInsert(Edge list, int source, int dest, int weight) {
    if (list == NULL) return edge_newNode(source, dest, weight);
    
    else {
    if (source != list->sourceIndex) 
            list->next = edge_tailInsert(list->next, 
                source, dest, weight);

    else if (list->destIndex != dest) 
        list->next = edge_tailInsert(list->next, 
                source, dest, weight);

    return list;
    }
}

/* Crea un elemento Edge e lo inserisce in testa alla lista */
Edge edge_headInsert(Edge list, int source, int dest, int weight) {
    Edge E = edge_newNode(source, dest, weight);
    if (E != NULL) E->next = list;
    return E;
}

/* Stampa su stdout una lista di elementi di Edge (come caratteri) */
void edge_printPath(Edge list) {
    if (list == NULL) {
        printf("///\n");
        return;
    }

    if (list->next != NULL) {
        printf("%c -> ", intToChar(list->sourceIndex));
        edge_printPath(list->next);
        return;
    }

    printf("%c -> %c\n", intToChar(list->sourceIndex), intToChar(list->destIndex));

}