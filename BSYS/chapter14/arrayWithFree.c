#include <stdio.h> 
#include <stdlib.h>

int main (void) {
    int *data = (int*) malloc(sizeof(int) * 100);
    data[100] = 0;

    //7.
    //free(&data[50]);

    //6.
    free(data);
    printf("Value: %d\n", data[100]);
    return 0;
}