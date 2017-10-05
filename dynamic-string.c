#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "dynamic-string.h"
#include "linked-list.h"
// string chunk size
#define CHUNK_SIZE 256

void destroyStringNode(void *v) {
    free(v);
}

DynamicString *DS_create() {
    DynamicString *dString;
    List *list = LL_create();
    
    if (!list) {
        return NULL;
    }
    
    dString = (DynamicString *) malloc(sizeof(DynamicString));
    
    if (!dString) {
        return NULL;
    }

    dString->length = 0;
    dString->list = list;

    return dString;
}
void DS_write(DynamicString *dString, char *value) {
    Node *lastNode = LL_lastNode(dString->list);
    Node *writeNode;
    size_t currAvailableSpace;
    char *nodeString;
    char *newString;
    size_t charsToWrite = strlen(value);
    size_t currentCharIndex = 0;
    size_t charsWrote = 0;
    size_t availableSpace;
    size_t nodesToCreate;
    size_t currLen;
    size_t writeLimit;
    
    // there is a last node
    if (!lastNode) {
        availableSpace = 0;
    } else {
        nodeString = (char *) lastNode->data;
        availableSpace = CHUNK_SIZE - strlen(nodeString) - 1; // \0
    }

    if (charsToWrite > availableSpace) {
        nodesToCreate = ceil((double)(charsToWrite - availableSpace) / (double)(CHUNK_SIZE - 1));
    } else {
        nodesToCreate = 0;
    }

    for (int i = 0; i < nodesToCreate; i++) {
        newString = (char *) malloc (sizeof(char) * CHUNK_SIZE);
        strcpy(newString, "\0");
        LL_insertNode(dString->list, newString);
    }

    if (!lastNode) {
        writeNode = LL_firstNode(dString->list);
    } else if (availableSpace) {
        writeNode = lastNode;
    } else {
        writeNode = lastNode->next;
    }

    while (charsWrote < charsToWrite) {
        int i;
        nodeString = (char *)writeNode->data;
        currLen = strlen(nodeString);
        if (charsToWrite - charsWrote < CHUNK_SIZE - currLen - 1) {
            writeLimit = charsToWrite - charsWrote + currLen;
        } else {
            writeLimit = CHUNK_SIZE - 1;
        }
        for (i = currLen; i < writeLimit; i++) {
            nodeString[i] = value[currentCharIndex++];
            charsWrote++;
            dString->length = dString->length + 1;
        }
        nodeString[i] = '\0';
        writeNode = writeNode->next;
    }
}
void DS_read(DynamicString *dString, size_t size, char *outBuf) {
    Node *currNode = LL_firstNode(dString->list);
    char *currNodeString;
    size_t bytesToRead = size;
    size_t byteReadIndex = 0;
    size_t currNodeReadIndex = 0;

    if (!currNode) {
        strcpy(outBuf, "\0");
        return;
    }

    currNodeString = (char *)currNode->data;

    while (byteReadIndex < bytesToRead) {
        if (currNodeReadIndex >= (CHUNK_SIZE - 1)) {
            currNode = currNode->next;
            if (currNode == NULL) {
                break;
            }
            currNodeString = (char *)currNode->data;
            currNodeReadIndex = 0;
        }
        outBuf[byteReadIndex++] = currNodeString[currNodeReadIndex++];
    }
    outBuf[byteReadIndex] = '\0';
}
char *DS_AsString(DynamicString *dString) {
    size_t len = dString->length;
    char *str = (char *) malloc (sizeof(char) * len + 1);
    DS_read(dString, len, str);
    return str;
}
int DS_length(DynamicString *dString) {
    return dString->length;
}
void DS_destroy(DynamicString *dString) {
    LL_destroy(dString->list, destroyStringNode);
    free(dString);
}
