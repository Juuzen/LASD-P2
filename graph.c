#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "const.h"

/* FUNZIONI LISTE */
void list_freeNode(List node) {
    if (node != NULL) {
        node->value = 0;
        node->next = NULL;
        free(node);
    }
}
void list_freeList(List L) {
    if (L != NULL) {
        list_freeList(L->next);
        list_freeNode(L);
    }
}
List list_newNode(int value) {
    List node = (List) calloc(1, (sizeof(list)));
    if (node != NULL) {
        node->value = value;
        node->next = NULL;
    }
    return node;
}
List list_enqueue(List queue, int value) {
    if (queue == NULL) return list_newNode(value);
    queue->next = list_enqueue(queue->next, value);
    return queue;
}
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
bool list_findValue(List L, int key) {
    if (L == NULL) return false;
    if (L->value == key) return true;
    return list_findValue(L->next, key);
}
void list_debugPrint(List L) {
    if (L == NULL) printf("X\n");
    else {
        printf("%d -> ", L->value);
        list_debugPrint(L->next);
    }
}

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
Edge edge_headInsert(Edge list, int source, int dest, int weight) {
    Edge E = edge_newNode(source, dest, weight);
    if (E != NULL) E->next = list;
    return E;
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
Edge graph_findShortestPath(Graph G, int startIndex, int endIndex, int truckWeight) {
    if (G == NULL) return NULL;

    /* Inizializzazione vettore predecessori */
    int prev[G->nodeCount];
    for (int i = 0; i < G->nodeCount; i++)
        prev[i] = -1;
    
    List visitedNodes = NULL, nodeQueue = NULL;
    bool pathFound = false;
    /* Impostiamo il nodo corrente come il nodo di partenza */
    int currentIndex = startIndex;
    
    /* Per ogni nodo corrente */
    do {
        /* Il nodo corrente viene considerato già visitato */
        visitedNodes = list_enqueue(visitedNodes, currentIndex);

        /* Prendiamo la lista di adiacenza del nodo corrente */
        Edge adjList = G->adjList[currentIndex];

        /* Fino a quando la lista di adiacenza del nodo corrente non è vuota */
        while (!pathFound && adjList != NULL) {
            /* Se l'arco è candidato ad essere messo in coda */
            if (!list_findValue(nodeQueue, adjList->destIndex) && !list_findValue(visitedNodes, adjList->destIndex)) {
                /* Se l'arco può sostenere il peso del camion */
                if (adjList->weight > truckWeight) {
                    /* Se l'arco punta alla destinazione */
                    if (adjList->destIndex == endIndex) {
                        /* Possiamo fermarci, ricostruiamo il percorso minimo */
                        pathFound = true;
                        prev[adjList->destIndex] = currentIndex;
                        /* Usciamo dal while */
                        break;
                    }
                    /* Altrimenti continuiamo a ciclare la lista di adiacenza */
                    nodeQueue = list_enqueue(nodeQueue, adjList->destIndex);
                    prev[adjList->destIndex] = currentIndex;
                }
            }
            adjList = adjList->next;
        }
        
        /* Se il percorso non è stato ancora individuato */
        if (!pathFound) {
            /* Il prossimo nodo corrente viene preso dalla coda */
            currentIndex = list_dequeue(&nodeQueue);
        }
    /* Continua fin quando il percorso non è stato ancora individuato o vi sono ancora nodi nella coda */
    } while(!pathFound && currentIndex != -1);

    /* Libero le strutture ausiliarie */
    list_freeList(visitedNodes);
    list_freeList(nodeQueue);

    /* Se il percorso è stato individuato */
    if (pathFound) {
        Edge path = NULL;
        int source, dest = endIndex;
        do {
            source = prev[dest];
            path = edge_headInsert(path, source, dest, 0);
            dest = source;
        } while (source != startIndex);
        return path;
    }

    /* Altrimenti return NULL */
    return NULL;
}
Graph graph_getSampleGraph() {
    Graph G = graph_new();
    graph_addNode(G); // A - 0
    graph_addNode(G); // B - 1
    graph_addNode(G); // C - 2
    graph_addNode(G); // D - 3
    graph_addNode(G); // E - 4
    graph_addNode(G); // F - 5
    graph_addNode(G); // G - 6
    graph_addNode(G); // H - 7
    graph_addNode(G); // I - 8
    graph_addNode(G); // J - 9
    graph_addNode(G); // K - 10
    graph_addNode(G); // L - 11
    graph_addNode(G); // M - 12

    graph_addEdge(G, false, 0, 1, 100);   // A-B
    graph_addEdge(G, false, 0, 4, 100);   // A-E
    graph_addEdge(G, false, 0, 8, 100);   // A-I

    graph_addEdge(G, false, 1, 4, 0);     // B-E
    graph_addEdge(G, false, 1, 5, 100);   // B-F
    graph_addEdge(G, false, 1, 8, 100);   // B-I

    graph_addEdge(G, false, 2, 5, 0);     // C-F
    graph_addEdge(G, false, 2, 12, 0);    // C-M
    graph_addEdge(G, false, 2, 9, 100);   // C-J
    graph_addEdge(G, false, 2, 6, 0);     // C-G

    graph_addEdge(G, false, 3, 11, 100);  // D-L
    graph_addEdge(G, false, 3, 9, 100);   // D-J
    graph_addEdge(G, false, 3, 6, 100);   // D-G

    graph_addEdge(G, false, 4, 7, 100);   // E-H

    graph_addEdge(G, false, 5, 8, 0);     // F-I
    graph_addEdge(G, false, 5, 9, 100);   // F-J
    graph_addEdge(G, false, 5, 12, 100);  // F-M
    
    graph_addEdge(G, false, 6, 10, 100);  // G-K

    graph_addEdge(G, false, 7, 8, 100);   // H-I

    graph_addEdge(G, false, 10, 11, 100); // K-L
    
    return G;
}
void graph_debugPrint(Graph G) {
    if (G != NULL) {
        for (int i = 0; i < G->nodeCount; i++) {
            if (G->adjList[i] != NULL) edge_debugPrintList(G->adjList[i]);
            else printf("Il nodo %d non ha nodi adiacenti.\n", i);
        }
    }
}