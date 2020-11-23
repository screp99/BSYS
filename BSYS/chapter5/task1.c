#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int var = 100;
  int rc = fork();
  if (rc < 0) {
    // fork failed
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    // child
    printf("var (child): %d\n", var);
    var++;
    printf("new var (child): %d\n", var);
  } else {
    // parent goes down this path (main)
    printf("var (parent): %d\n", var);
    var++;
    printf("new var (parent): %d\n", var);
  }
  return 0;
}