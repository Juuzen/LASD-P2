#ifndef graph_h
#define graph_h
#include <stdbool.h>
#define NODELIMIT 20

typedef struct edge {
    int sourceIndex;
    int destIndex;
    int weight;
    struct edge* next;
} edge;
typedef edge* Edge;

typedef struct graph {
    int nodeCount;
    Edge *adjList;
} graph;
typedef graph* Graph;

/* FUNZIONI ARCHI */
void edge_freeNode(Edge node);
void edge_freeList(Edge list);
Edge edge_newNode(int source, int dest, int weight);
Edge edge_removeNode(Edge list, int source, int dest);
Edge edge_findNode(Edge list, int source, int dest);

void edge_debugPrintNode(Edge node);
void edge_debugPrintList(Edge list);

/* FUNZIONI GRAFI */
Graph graph_new();
void graph_free(Graph G);
void graph_addNode(Graph G);
void graph_addEdge(Graph G, bool ordered, int sourceIndex, int destIndex, int weight);

void graph_debugPrint(Graph G);
#endif