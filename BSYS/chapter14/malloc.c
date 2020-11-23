#include <stdio.h> 
#include <stdlib.h>

int main (void) {
    int *i = malloc(sizeof(int));
    printf("Pointer: %ls, Value: %d\n", i, *i);
    return 0;
}
