#ifndef graph_h
#define graph_h
#include "edge.h"

typedef struct graph {
    int nodeCount;
    Edge *adjList;
} graph;
typedef graph* Graph;

/* ----- FUNZIONI GRAFI ----- */
Graph graph_new();
void graph_free(Graph G);
void graph_addNode(Graph G);
void graph_addEdge(Graph G, bool ordered, int sourceIndex, int destIndex, int weight);
Edge graph_findShortestPath(Graph G, int startIndex, int endIndex, int truckWeight);
void graph_debugPrint(Graph G);

/* ----- FUNZIONI CREAZIONI ARCIPELAGO ----- */
Graph graph_createSampleGraph1();
Graph graph_createSampleGraph2();
Graph graph_createSampleGraph3();

#endif