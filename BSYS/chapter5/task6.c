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
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        //child
        printf("I am a child (%d)!\n", getpid());
        exit(0);
    } else {
        //parent
        printf("I am the parent (%d)!\n", getpid());
        int status;
        int childpid = waitpid(-1, &status, 0);
        printf("Exit status of child: %d.\n", WEXITSTATUS(status));
        printf("Pid of child: %d.\n", childpid);
    }
    return 0;
}