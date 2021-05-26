#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"
#include "edge.h"
#include "graph.h"
#include "const.h"

/* ----- FUNZIONI GRAFI ----- */
/* Alloca dinamicamente un grafo e lo restituisce in output */
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

/* Dealloca un grafo passato */
void graph_free(Graph G) {
    if (G != NULL) {
        for (int i = 0; i < G->nodeCount; i++) 
            edge_freeList(G->adjList[i]);
        
        G->nodeCount = 0;
        G->adjList = NULL;
        free(G);
    }
}

/* Aggiunge un nodo al grafo */
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

/* Aggiunge un arco al grafo, specificando indice di partenza, di arrivo, e peso dell'arco */
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

/* Restituisce, se esiste, il percorso minimo dall'indice di partenza a quello di arrivo all'interno del grafo */
/* Ponendo come vincolo, il fatto che il peso di ogni arco del percorso è maggiore a truckWeight */
Edge graph_findShortestPath(Graph G, int startIndex, int endIndex, int truckWeight) {
    /* Se il grafo è vuoto, non esiste nessun percorso */
    if (G == NULL) return NULL;

    /* Se indice di inizio e fine coincidono, allora è possibile già terminare l'algoritmo */
    if (startIndex == endIndex) return edge_newNode(startIndex, endIndex, 0);

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
            /* Scorriamo in avanti la lista di adiacenza */
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

/* Stampa in stdout un grafo */
void graph_debugPrint(Graph G) {
    if (G != NULL) {
        for (int i = 0; i < G->nodeCount; i++) {
            if (G->adjList[i] != NULL) edge_debugPrintList(G->adjList[i]);
            else printf("Il nodo %d non ha nodi adiacenti.\n", i);
        }
    }
}



/* ----- FUNZIONI CREAZIONE ARCIPELAGO ----- */

/* Scenario 1: Tutti gli archi hanno peso >= 2500, il grafo è connesso */
Graph graph_createSampleGraph1 () {
    Graph G = graph_new();

    for (int i = 0; i < ISLAND_NUMBER; i++) 
        graph_addNode(G);

    graph_addEdge(G, false, 0, 1, 3000); // A-B 
    graph_addEdge(G, false, 0, 4, 2500); // A-E 
    graph_addEdge(G, false, 0, 8, 3200); // A-I
    
    graph_addEdge(G, false, 1, 2, 2500); // B-C
    graph_addEdge(G, false, 1, 4, 2800); // B-E

    graph_addEdge(G, false, 2, 3, 3000); // C-D
    graph_addEdge(G, false, 2, 5, 2850); // C-F

    graph_addEdge(G, false, 3, 6, 2750); // D-G
    graph_addEdge(G, false, 3, 7, 2500); // D-H
    graph_addEdge(G, false, 3, 12, 3000); // D-M

    graph_addEdge(G, false, 4, 8, 3500); // E-I
    graph_addEdge(G, false, 4, 9, 3200); // E-J

    graph_addEdge(G, false, 5, 6, 3000); // F-G
    graph_addEdge(G, false, 5, 10, 2600); // F-K
    graph_addEdge(G, false, 5, 11, 3000); // F-L

    graph_addEdge(G, false, 6, 15, 2800); // G-P

    graph_addEdge(G, false, 7, 12, 2750); // H-M

    graph_addEdge(G, false, 8, 13, 2800); // I-N

    graph_addEdge(G, false, 9, 10, 3000); // J-K
    graph_addEdge(G, false, 9, 13, 3000); // J-N
    graph_addEdge(G, false, 9, 14, 2600); // J-O

    graph_addEdge(G, false, 11, 14, 3000); // L-O
    graph_addEdge(G, false, 11, 15, 2800); // L-P

    graph_addEdge(G, false, 12, 15, 3000); // M-P
    graph_addEdge(G, false, 12, 16, 2800); // M-Q

    graph_addEdge(G, false, 13, 14, 2750); // N-O

    graph_addEdge(G, false, 14, 15, 3000); // O-P

    graph_addEdge(G, false, 15, 16, 3000); // P-Q
    
    return G;
}

/* Scenario 2: come lo scenario 1, ma alcuni archi hanno un peso <= 300 */
Graph graph_createSampleGraph2 () {
    Graph G = graph_new();

    for (int i = 0; i < ISLAND_NUMBER; i++) 
        graph_addNode(G);

    graph_addEdge(G, false, 0, 1, 3000); // A-B 
    graph_addEdge(G, false, 0, 4, 200); // A-E 
    graph_addEdge(G, false, 0, 8, 100); // A-I
    
    graph_addEdge(G, false, 1, 2, 200); // B-C
    graph_addEdge(G, false, 1, 4, 2800); // B-E

    graph_addEdge(G, false, 2, 3, 100); // C-D
    graph_addEdge(G, false, 2, 5, 2850); // C-F

    graph_addEdge(G, false, 3, 6, 2750); // D-G
    graph_addEdge(G, false, 3, 7, 200); // D-H
    graph_addEdge(G, false, 3, 12, 3000); // D-M

    graph_addEdge(G, false, 4, 8, 300); // E-I
    graph_addEdge(G, false, 4, 9, 3200); // E-J

    graph_addEdge(G, false, 5, 6, 300); // F-G
    graph_addEdge(G, false, 5, 10, 200); // F-K
    graph_addEdge(G, false, 5, 11, 3000); // F-L

    graph_addEdge(G, false, 6, 15, 2800); // G-P

    graph_addEdge(G, false, 7, 12, 2750); // H-M

    graph_addEdge(G, false, 8, 13, 2800); // I-N

    graph_addEdge(G, false, 9, 10, 150); // J-K
    graph_addEdge(G, false, 9, 13, 200); // J-N
    graph_addEdge(G, false, 9, 14, 2600); // J-O

    graph_addEdge(G, false, 11, 14, 300); // L-O
    graph_addEdge(G, false, 11, 15, 200); // L-P

    graph_addEdge(G, false, 12, 15, 100); // M-P
    graph_addEdge(G, false, 12, 16, 200); // M-Q

    graph_addEdge(G, false, 13, 14, 2750); // N-O

    graph_addEdge(G, false, 14, 15, 3000); // O-P

    graph_addEdge(G, false, 15, 16, 3000); // P-Q
    
    return G;
}

/* Scenario 3: come lo scenario 2, ma il grafo è una foresta */
Graph graph_createSampleGraph3 () {
    Graph G = graph_new();

    for (int i = 0; i < ISLAND_NUMBER; i++) 
        graph_addNode(G);

    graph_addEdge(G, false, 0, 1, 3000); // A-B 
    graph_addEdge(G, false, 0, 8, 100); // A-I
    
    graph_addEdge(G, false, 1, 4, 2800); // B-E

    graph_addEdge(G, false, 2, 3, 100); // C-D
    graph_addEdge(G, false, 2, 5, 2850); // C-F

    graph_addEdge(G, false, 3, 6, 2750); // D-G

    graph_addEdge(G, false, 4, 8, 300); // E-I

    graph_addEdge(G, false, 5, 6, 300); // F-G

    graph_addEdge(G, false, 7, 12, 2750); // H-M

    graph_addEdge(G, false, 9, 13, 200); // J-N
    graph_addEdge(G, false, 9, 14, 2600); // J-O

    graph_addEdge(G, false, 11, 14, 300); // L-O

    graph_addEdge(G, false, 12, 15, 100); // M-P
    graph_addEdge(G, false, 12, 16, 200); // M-Q

    graph_addEdge(G, false, 13, 14, 2750); // N-O

    graph_addEdge(G, false, 15, 16, 3000); // P-Q
    
    return G;
}