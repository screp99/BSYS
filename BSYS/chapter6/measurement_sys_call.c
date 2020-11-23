#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(void) {

    struct timespec start, stop, startLoop, stopLoop;
    int i;

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (i=0; i<100000; i++) {
        //write(STDOUT_FILENO, "", 0); // ca. 950ns
        getpid(); // ca. 495ns
    }
    clock_gettime(CLOCK_MONOTONIC, &stop);

    //get time of loop
    clock_gettime(CLOCK_MONOTONIC, &startLoop);
    for (i=0; i<100000; i++) {}
    clock_gettime(CLOCK_MONOTONIC, &stopLoop);
    
    long loopTime = (stopLoop.tv_sec * 1000000000 + stopLoop.tv_nsec) - (startLoop.tv_sec * 1000000000 + startLoop.tv_nsec);
    long totalTime = (stop.tv_sec * 1000000000 + stop.tv_nsec) - (start.tv_sec * 1000000000 + start.tv_nsec);
    long sysCallTime = (totalTime - loopTime) / 100000;

    printf("One sys call needs %ld nanoseconds.\n", sysCallTime);

    return 0;
}
