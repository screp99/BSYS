#define _GNU_SOURCE
#define _POSIX_C_SOURCE 199309L
#define BILLION 1000000000L
#define CYCLES 10
#include <time.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sched.h>

void showSchedAffinity();
int cmpfunc (const void * a, const void * b);
void setSchedAffinity();

int main(void) {
    struct timespec start, stop, startTimeFunction, stopTimeFunction;
    int pipeToChild[2], pipeToParent[2];
    if (pipe(pipeToChild) != 0 || pipe(pipeToParent) != 0) {
        fprintf(stderr, "Creating pipes failed!");
        return 1;
    }
    char y[2], x[2];
    long contextSwitchTime[CYCLES];
    long durationOfTimeFunction;
    switch (fork()) {
        case -1:
            fprintf(stderr, "fork failed!\n");
            exit(1);
        case 0:
            //CHILD
            printf("child: ");
            setSchedAffinity();
            showSchedAffinity();
            for (int i=0; i<CYCLES; i++) {
                read(pipeToChild[0], &x, sizeof(x));
                write(pipeToParent[1], "y", 2);
            }
            break;
        default: 
            //PARENT
            printf("parent: ");
            setSchedAffinity();
            showSchedAffinity();
            for (int i=0; i<CYCLES; i++) {
                write(pipeToChild[1], "x", 2);
                clock_gettime(CLOCK_MONOTONIC_RAW, &start);
                read(pipeToParent[0], &y, sizeof(y));
                clock_gettime(CLOCK_MONOTONIC_RAW, &stop);

                clock_gettime(CLOCK_MONOTONIC_RAW, &startTimeFunction);
                clock_gettime(CLOCK_MONOTONIC_RAW, &stopTimeFunction);
                durationOfTimeFunction = (((stopTimeFunction.tv_sec * BILLION) + stopTimeFunction.tv_nsec) - ((startTimeFunction.tv_sec * BILLION) + startTimeFunction.tv_nsec));
                printf("durationOfTimeFunction: %ld\n", durationOfTimeFunction);
                contextSwitchTime[i] = ((((stop.tv_sec * BILLION) + stop.tv_nsec) - ((start.tv_sec * BILLION) + start.tv_nsec)) - durationOfTimeFunction) / 2;
            }
            qsort(contextSwitchTime, CYCLES, sizeof(long), cmpfunc);
            //INTERQUARTILE DISTANCE
            long totalContextSwitchTime = 0;
            int n = 0;
            for (int j=(int)(CYCLES * 0.1);j<(int)(CYCLES * 0.9);j++) {
                totalContextSwitchTime += contextSwitchTime[j];
                n++;
                //printf("contextSwitchTime[%d] %ld\n", j, contextSwitchTime[j]);
            }
            printf("%d\n", n);
            printf("%d\n", (int) (CYCLES * 0.1));
            long averageContextSwitchTime = totalContextSwitchTime / n;
            printf("One context switch needs %ld nanoseconds.\n", averageContextSwitchTime);
            break;
    }
    close(x[0]);
    close(x[1]);
    close(y[0]);
    close(y[1]);
    return 0;
}

void showSchedAffinity() {
    cpu_set_t mask;
    int nproc = sysconf(_SC_NPROCESSORS_ONLN);
    sched_getaffinity(getpid(), sizeof(mask), &mask);
    printf("[%d] sched_getaffinity = ", getpid());
    for (int i = 0; i < nproc; i++) {
        printf("%d ", CPU_ISSET(i, &mask));
    }
    printf("\n");
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void setSchedAffinity() {
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(0, &set);
    if(sched_setaffinity(0, sizeof(set), &set)){
        fprintf(stderr, "Reducing to 1 CPU failed!");
        exit(1);
    }
}
