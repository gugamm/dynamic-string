#ifndef _DYNAMIC_STRING
#define _DYNAMIC_STRING

#include "linked-list.h"

typedef struct DynamicString DynamicString;

struct DynamicString {
    size_t length; //size of chars
    List *list;    
};

DynamicString *DS_create();
void DS_write(DynamicString *dString, char *value);
void DS_read(DynamicString *dString, size_t size, char *outBuf);
char *DS_AsString(DynamicString *dString);
int DS_length(DynamicString *dString);
void DS_destroy(DynamicString *dString);

#endif