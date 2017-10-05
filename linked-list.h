#ifndef _LINKED_LIST
#define _LINKED_LIST

typedef struct List List;
typedef struct Node Node;

struct Node {
    Node *prev;
    Node *next;
    void *data;
};

struct List {
    Node *head;
    Node *tail;
    unsigned int length;
};

List *LL_create();
void LL_destroy(List *list, void (*cb)(void *nodeData));
Node *LL_findNode(List *list, void *searchData, int (*cmp)(void *searchData, void *nodeData));
Node *LL_insertNode(List *list, void *data);
void LL_deleteNode(List *list, Node *node);
Node *LL_firstNode(List *list);
Node *LL_lastNode(List *list);
void LL_forEachNode(List *list, void (*cb)(void *nodeData));

#endif