#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int rc = fork();
    switch (rc) {
        case -1:
            fprintf(stderr, "fork failed!\n");
            exit(1);
        case 0:
            //child
            printf("Hello i am the child!\n");
            close(STDOUT_FILENO);
            printf("Hello i am the child! Can you still see me?\n");
            break;
        default: 
            //parent
            printf("Hello i am the parent!\n");
            wait(NULL);
            printf("Hello i am still the parent!\n");
    }
    return 0;
}