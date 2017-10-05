#include <stdlib.h>
#include "linked-list.h"

List *LL_create() {
    List *list = (List *) malloc(sizeof(List));
    
    if (!list) {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->length = 0;

    return list;
}

void LL_destroy(List *list, void (*cb)(void *nodeData)) {
    Node *nextNode = list->head;
    Node *currNode;
    while (nextNode) {
        currNode = nextNode;
        nextNode = currNode->next;
        cb(currNode->data);
        free(currNode);
    }
    free(list);
}

Node *LL_findNode(List *list, void *searchData, int (*cmp)(void *searchData, void *nodeData)) {
    Node *currNode = list->head;
    while (currNode) {
        if (cmp) {
            if (cmp(searchData, currNode->data)) {
                return currNode;
            }
        } else {
            if (searchData == currNode->data) {
                return currNode;
            }
        }
        currNode = currNode->next;
    }
    return NULL;
}

Node *LL_insertNode(List *list, void *data) {
    Node *lastNode;
    Node *newNode = (Node *) malloc(sizeof(Node));

    if (!newNode) {
        return NULL;
    }
    
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = list->tail;

    if (list->tail) { 
        list->tail->next = newNode;
    }

    if (!list->head) {
        list->head = newNode;
    }
    list->tail = newNode;
    list->length = list->length + 1;

    return newNode;
}

void LL_deleteNode(List *list, Node *node) {
    if (node == list->head) {
        list->head = node->next;
    }

    if (node == list->tail) {
        list->tail = node->prev;
    }

    list->length = list->length - 1;

    free(node);
}

Node *LL_firstNode(List *list) {
    return list->head;
}

Node *LL_lastNode(List *list) {
    return list->tail;
}

void LL_forEachNode(List *list, void (*cb)(void *nodeData)) {
    Node *currNode = list->head;

    while(currNode) {
        cb(currNode->data);
        currNode = currNode->next;
    }
}
