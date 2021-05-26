#ifndef list_h
#define list_h
#include <stdbool.h>

typedef struct list {
    int value;
    struct list* next;
} list;
typedef list* List;

void list_freeNode(List node);
void list_freeList(List L);
List list_newNode(int value);
List list_enqueue(List queue, int value);
int list_dequeue(List* queue);
bool list_findValue(List L, int key);
void list_debugPrint(List L);

#endif