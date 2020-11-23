#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int filedesc = open("text.txt", O_WRONLY | O_APPEND);
    if (filedesc < 0) {
        return 1;
    }
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        //child
        printf("child filedesc: %d\n", filedesc);
        write(filedesc, "Hello i am the child!\n", 22);
    } else {
        //parent
        printf("parent filedesc: %d\n", filedesc);
        write(filedesc, "Hello i am the parent!\n", 23);
    }
    return 0;
}
