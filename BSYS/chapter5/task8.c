#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    int fd[2];

    pipe(fd);

    switch (fork()) {
        case -1:
            fprintf(stderr, "fork 1 failed!\n");
            exit(1);
        case 0:
            //child 1
            dup2(fd[1], 1);
            close(fd[0]);
            fprintf(stdout, "Hello i am the first child!\n");
            close(fd[1]);
            exit(0);
        default: 
            //parent
            wait(NULL);
            switch (fork()) {
                case -1:
                    fprintf(stderr, "fork 2 failed!\n");
                    exit(1);
                case 0:
                    //child 2
                    dup2(fd[0], 0);
                    close(fd[1]);
                    printf("Second childs echo: ");
                    char b;
                    while (read(0, &b, 1) > 0) {
                        printf("%c", b);
                        if (b == '\n') {
                            break;
                        }
                    }
                    close(fd[0]);
                    exit(0);
                default: 
                    wait(NULL);
                    break;
            }
    }
    close(fd[0]); 
    close(fd[1]);
    return 0;
}