#ifndef edge_h
#define edge_h

typedef struct edge {
    int sourceIndex;
    int destIndex;
    int weight;
    struct edge* next;
} edge;
typedef edge* Edge;

void edge_freeNode(Edge node);
void edge_freeList(Edge list);
Edge edge_newNode(int source, int dest, int weight);
Edge edge_headInsert(Edge list, int source, int dest, int weight);
Edge edge_tailInsert(Edge list, int source, int dest, int weight);
void edge_printPath(Edge list);

#endif