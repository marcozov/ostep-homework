#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <malloc.h>
#include <time.h>

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("Not enough arguments provided. Please provide the number of pages to touch and the number of trials\n");
		exit(1);
	}
	cpu_set_t mask;
	CPU_ZERO(&mask);
	CPU_SET(0, &mask);
	sched_setaffinity(0, sizeof(mask), &mask);

	int NUMPAGES = atoi(argv[1]);
	int number_of_trials = atoi(argv[2]);
	//printf("NUMPAGES: %d\n", NUMPAGES);
	//printf("number of trials: %d\n", number_of_trials);
	int PAGESIZE = sysconf(_SC_PAGESIZE);
	//printf("PAGESIZE: %d\n", PAGESIZE);

	struct timeval time_before, time_after;
	struct timespec start, end;
	int jump = PAGESIZE / sizeof(int);
	// int *a = (int *) calloc(1, sizeof(int));
	//int *a = (int *) malloc(1 * sizeof(int));
	//int *a = (int *) malloc(NUMPAGES * sizeof(int) * jump);
	int *a = (int *) malloc(NUMPAGES * PAGESIZE);
	//int usable_size = malloc_usable_size(a);
	//printf("usable_size: %d\n", usable_size);
	//printf("jump: %d\n", jump);

	//gettimeofday(&time_before, NULL);
	if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start) == -1) {
		printf("error while measuring start time\n");
		exit(1);
	}
	for (int j=0; j < number_of_trials; j++) {
		//printf("looping %d times\n", (NUMPAGES * jump));
		for (int i=0; i < NUMPAGES * jump; i = i + jump) {
			// legge i dalla memoria
			// legge a[i] dalla memoria
			// scrive a[i] in memoria
			a[i] = a[i] + 1;
		}
	}

	if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end) == -1) {
		printf("error while measuring end time\n");
		exit(1);
	}
	//gettimeofday(&time_after, NULL);
	//printf("average (ns): %f\n", ((end.tv_sec - start.tv_sec) * 1E9 + end.tv_nsec - start.tv_nsec ) / (number_of_trials * NUMPAGES));
	printf("%f\n", ((end.tv_sec - start.tv_sec) * 1E9 + end.tv_nsec - start.tv_nsec ) / (number_of_trials * NUMPAGES));
}
