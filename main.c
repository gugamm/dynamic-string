#include <stdio.h>
#include <stdlib.h>
#include "dynamic-string.h"

int main(void) {
    DynamicString *str = DS_create();
    char *finalString;
    for (int i = 0; i < 10000; i++) {
        DS_write(str, "abcdefghiJ");
    }
    printf("FINAL RESULT:\n");
    printf("FINAL LENGTH: %d\n", DS_length(str));
    printf("\n");
    finalString = DS_AsString(str);
    printf("%s\n", finalString);
    free(finalString);
    DS_destroy(str);
    return 0;
}
