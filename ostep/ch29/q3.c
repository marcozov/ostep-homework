#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include "common_threads.h"
#define NUMCPUS 4

typedef struct __counter_t {
	int global;
	pthread_mutex_t glock;
	int local[NUMCPUS];
	pthread_mutex_t llock[NUMCPUS];
	int threshold;
} counter_t;

typedef struct __thread_arg {
	int cpu_id;
	pthread_t thread;
	counter_t *counter;
} thread_arg_t;

void init(counter_t *c, int threshold) {
	c->global = 0;
	c->threshold = threshold;
	Mutex_init(&c->glock);
	for (int i=0; i < NUMCPUS; i++) {
		c->local[i] = 0;
		Mutex_init(&c->llock[i]);
	}
}

void update(counter_t *c, int threadID, int amount) {
	int cpu = threadID % NUMCPUS;
	Pthread_mutex_lock(&c->llock[cpu]);
	c->local[cpu] += amount;
	if (c->local[cpu] >= c->threshold) {
		Pthread_mutex_lock(&c->glock);
		c->global += c->local[cpu];
		Pthread_mutex_unlock(&c->glock);
		c->local[cpu] = 0;
	}
	Pthread_mutex_unlock(&c->llock[cpu]);
}

int get(counter_t *c) {
	Pthread_mutex_lock(&c->glock);
	int val = c->global;
	Pthread_mutex_unlock(&c->glock);
	return val;
}

void *thread_function(void *arg) {
	printf("I am a thread\n");
	thread_arg_t *casted_arg = (thread_arg_t *) arg;
	printf("cpu id: %d\n", casted_arg->cpu_id);
	printf("thread: %ld\n", casted_arg->thread);
	for (int i=0; i < 1000000; i++) {
		update(casted_arg->counter, casted_arg->cpu_id, 1);
	}
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("not enough arguments\n");
		exit(1);
	}
	int num_of_threads = atoi(argv[1]);
	int threshold = atoi(argv[2]);
	int num_of_cores = (int)sysconf(_SC_NPROCESSORS_ONLN);
	printf("number of cores: %d\n", num_of_cores);

	counter_t *counter;
	counter = malloc(sizeof(counter_t));
	init(counter, threshold);
	printf("get: %d\n", get(counter));

	thread_arg_t *args = malloc(num_of_threads * sizeof(thread_arg_t));

	struct timeval start, end;
	gettimeofday(&start, NULL);
	for (int i=0; i < num_of_threads; i++) {
		args[i].cpu_id = i % NUMCPUS;
		args[i].counter = counter;
		Pthread_create(&args[i].thread, NULL, &thread_function, &args[i]);
	}

	for (int i=0; i < num_of_threads; i++) {
		Pthread_join(args[i].thread, NULL);
	}
	gettimeofday(&end, NULL);

	printf("start: %ld, %ld\n", start.tv_sec, start.tv_usec);
	printf("end: %ld, %ld\n", end.tv_sec, end.tv_usec);
	printf("time elapsed: %f\n", (float)(end.tv_sec - start.tv_sec) + (float)(end.tv_usec - start.tv_usec) / 1000000);
	printf("counter value: %d\n", get(counter));
}
