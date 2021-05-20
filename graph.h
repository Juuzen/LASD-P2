#ifndef graph_h
#define graph_h
#include <stdbool.h>
#define NODELIMIT 20

typedef struct list {
    int value;
    struct list* next;
} list;
typedef list* List;

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

/* FUNZIONI LISTE */
void list_freeNode(List node);
void list_freeList(List L);
List list_newNode(int value);
List enqueue(List queue, int value);
int dequeue(List* queue);
bool list_findValue(List L, int key);
void list_debugPrint(List L);

/* FUNZIONI ARCHI */
void edge_freeNode(Edge node);
void edge_freeList(Edge list);
Edge edge_newNode(int source, int dest, int weight);
Edge edge_removeNode(Edge list, int source, int dest);
Edge edge_findNode(Edge list, int source, int dest);
Edge edge_headInsert(Edge list, int source, int dest, int weight);
Edge edge_tailInsert(Edge list, int source, int dest, int weight);
void edge_debugPrintNode(Edge node);
void edge_debugPrintList(Edge list);

/* FUNZIONI GRAFI */
Graph graph_new();
void graph_free(Graph G);
void graph_addNode(Graph G);
void graph_addEdge(Graph G, bool ordered, int sourceIndex, int destIndex, int weight);
Edge graph_findShortestPath(Graph G, int startIndex, int endIndex, int truckWeight);
Graph graph_getSampleGraph();
void graph_debugPrint(Graph G);
#endif