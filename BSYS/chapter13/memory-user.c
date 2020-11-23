#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>

#define MEGABYTE 1024000

int main (int argc, char *argv[]) {
    printf("PID: %d\n", getpid());
    if (argc != 2) {
        fprintf(stderr, "Just one argument expected!\n");
        return -1;
    }
    int numberOfMB = atoi(argv[1]);
    long numberOfBytes = numberOfMB * MEGABYTE;
    char *array = (char*) malloc(sizeof(char) * numberOfBytes);
    if (array == NULL) {
        fprintf(stderr, "Allocation of %ld bytes failed\n", numberOfBytes);
        return -1;
    }
    while (1) {
        for (int i = 0;i<numberOfBytes;i++) {
            array[i] = 'x';
        }
    }
    free(array);
    return 0;
}