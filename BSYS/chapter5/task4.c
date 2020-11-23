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
        char *args[] = {"ls", NULL};
        char *env[] = {"SHELL=/bin/bash"};
        //child
        //execl("/bin/ls", "ls", NULL);
        //execve("/bin/ls", args, env);
        //execv("/bin/ls", args);
        //execle("/bin/ls", "ls", NULL, env);
        //execlp("ls", "ls", NULL);
        execvp("ls", args);
        printf("exec failed!\n");
    } else {
        //parent
        wait(NULL);
        printf("Done!\n");
    }
    return 0;
}