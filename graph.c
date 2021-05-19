#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

/* FUNZIONI ARCHI */
void edge_freeNode(Edge node) {
    if (node != NULL) {
        node->sourceIndex = 0;
        node->destIndex = 0;
        node->weight = 0;
        node->next = NULL;
    }
}
void edge_freeList(Edge list) {
    if (list != NULL) {
        edge_freeList(list->next);
        edge_freeNode(list);
    }
}
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
Edge edge_removeNode(Edge list, int source, int dest) {
    if (list == NULL) return NULL;
    if ((list->sourceIndex == source) && (list->destIndex == dest)) {
        Edge tmp = list->next;
        edge_freeNode(list);
        tmp = edge_removeNode(tmp, source, dest);
        return tmp;
    }
    list->next = edge_removeNode(list->next, source, dest);
    return list;
}
Edge edge_findNode(Edge list, int source, int dest) {
    if (list == NULL) return NULL;
    if ((list->sourceIndex == source) && (list->destIndex == dest)) 
        return list;
    return edge_findNode(list->next, source, dest);
}

void edge_debugPrintNode(Edge node) {
    if (node != NULL) 
        printf("%d -> %d (W: %d)\n", node->sourceIndex, node->destIndex, node->weight);
    
}
void edge_debugPrintList(Edge list) {
    if (list != NULL) {
        edge_debugPrintNode(list);
        edge_debugPrintList(list->next);
    }
}

/* FUNZIONI GRAFI */
Graph graph_new() {
    Graph graph = (Graph) calloc(1, sizeof(graph));
    if (graph != NULL) {
        graph->nodeCount = 0;
        graph->adjList = (Edge *) calloc(1, NODELIMIT * sizeof(Edge));
        for (int i = 0; i < NODELIMIT; i++) {
            graph->adjList[i] = NULL;
        }
    }
    return graph;
}
void graph_free(Graph G) {
    if (G != NULL) {
        for (int i = 0; i < G->nodeCount; i++) 
            edge_freeList(G->adjList[i]);
        
        G->nodeCount = 0;
        G->adjList = NULL;
        free(G);
    }
}
void graph_addNode(Graph G) {
    if (G != NULL) {
        // Se nodeCount è un multiplo di MAXNODES
        if ((G->nodeCount % NODELIMIT) == 0) {
            // bisogna ampliare la lista di adiacenza
            Edge* newAdjList = (Edge *) realloc(G->adjList, (G->nodeCount + NODELIMIT) * sizeof(Edge));
            if (newAdjList == NULL) {
                // errore nella riallocazione della memoria
                // non si può procedere ulteriormente
                return;
            }
            G->adjList = newAdjList;
        }
        G->nodeCount++;
    }
}
void graph_addEdge(Graph G, bool ordered, int sourceIndex, int destIndex, int weight) {
    if (G == NULL) {
        printf("Il grafo e' nullo.\n");
        return;
    }
    G->adjList[sourceIndex] = edge_tailInsert(G->adjList[sourceIndex], sourceIndex, destIndex, weight);
        // se l'arco non è direzionato, allora aggiungiamo specularmente l'arco di ritorno
    if (!ordered)
        G->adjList[destIndex] = edge_tailInsert(G->adjList[destIndex], destIndex, sourceIndex, weight);
}
void graph_removeEdge(Graph G, bool ordered, int sourceIndex, int destIndex) {
    if (G == NULL) {
        printf("Il grafo e' nullo.\n");
        return;
    }

    if (G->adjList[sourceIndex] != NULL) 
        G->adjList[sourceIndex] = edge_removeNode(G->adjList[sourceIndex], sourceIndex, destIndex);

    if (!ordered) 
        if (G->adjList[destIndex] != NULL)
            G->adjList[destIndex] = edge_removeNode(G->adjList[destIndex], destIndex, sourceIndex);
}

void graph_debugPrint(Graph G) {
    if (G != NULL) {
        for (int i = 0; i < G->nodeCount; i++) {
            if (G->adjList[i] != NULL) edge_debugPrintList(G->adjList[i]);
            else printf("Il nodo %d non ha nodi adiacenti.\n", i);
        }
    }
}