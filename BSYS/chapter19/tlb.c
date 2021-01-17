#define _GNU_SOURCE
#define BILLION 1000000000L
#include <sched.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <fcntl.h>
#include <errno.h>

void setSchedAffinity();

int cmpfunc(const void *p, const void *q);


int main(int argc, char *argv[]) {

    if (argc != 3) {
        fprintf(stderr, "Number of pages and number of iterations are expected as arguments!\n");
        return -1;
    }

    long num_pages = atoi(argv[1]);
    long iterations = atoi(argv[2]);

    if (num_pages < 0 || iterations < 0) {
        fprintf(stderr, "No negative values!");
        return -1;
    }

    // limit execution to only 1 CPU
    setSchedAffinity();

    int pagesize = getpagesize();
    printf("Size of a page: %d Byte\n", pagesize);

    int jump = pagesize / sizeof(int);

    struct timespec start, stop;
    struct timespec clock_overhead_stop;

    // initialize array by using calloc -  counterbalance costs of initializing during measurement
    int* array = (int*) calloc(num_pages * jump, sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Allocating memory failed!");
        return -1;
    }

// ----------------------------------------------------------------------------------------------------------------------------------------------------
// Measurement
// ----------------------------------------------------------------------------------------------------------------------------------------------------

    unsigned long access_time[iterations];
    for(long i = 0; i < iterations; i++) {
        long pages_total_time = 0;
        for(int j = 0; j < num_pages*jump; j += jump) {
            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
            clock_gettime(CLOCK_MONOTONIC_RAW, &clock_overhead_stop);
            array[j] += 1;
            clock_gettime(CLOCK_MONOTONIC_RAW, &stop);

            //time calculation
            long pages_access_time_start_nano = ((start.tv_sec * BILLION) + start.tv_nsec);
            long pages_access_time_stop_nano = ((stop.tv_sec * BILLION) + stop.tv_nsec);
            long clock_overhead_stop_nano = ((clock_overhead_stop.tv_sec * BILLION) + clock_overhead_stop.tv_nsec);

            pages_total_time += (pages_access_time_stop_nano - pages_access_time_start_nano) - (clock_overhead_stop_nano - pages_access_time_start_nano);
        }

        //add average access time to array
        access_time[i] = pages_total_time / num_pages;
    }
// ------------------------------------------------------------------------------------------------------------------------------------------------------
// Evaluation
// ------------------------------------------------------------------------------------------------------------------------------------------------------

    // sort array of average access times
    qsort(access_time, iterations, sizeof(unsigned long), cmpfunc);

    // calculate interquantile distance to eliminate 'bad' measurements
    unsigned long total_access_time = 0;
    for (int i = iterations * 0.2; i < (iterations * 0.8); ++i) {
        total_access_time += access_time[i];
    }

    unsigned long average_access_time = total_access_time / iterations * 0.6;

    printf("Accessing %lu pages takes %lu ns in average.\n", num_pages, average_access_time);

// ----------------------------------------------------------------------------------------------------------------------------------------------------
// Write result to csv file
// ----------------------------------------------------------------------------------------------------------------------------------------------------

    FILE* fptr;
    fptr = fopen("tlb.csv", "a+");
    if (fptr == NULL) {
        fprintf(stderr, "Error with File Pointer");
        return -1;
    }

    fprintf(fptr, "%ld, %ld\n", num_pages, average_access_time);
    fflush(fptr);
    fclose(fptr);

// ----------------------------------------------------------------------------------------------------------------------------------------------------
    free(array);
    return 0;
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

int cmpfunc(const void *p, const void *q)
{
    return (*(int*) p - *(int*) q);
}
