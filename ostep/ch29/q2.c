#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include "common_threads.h"

typedef struct __counter_t {
	int value;
	pthread_mutex_t lock;
} counter_t;

typedef struct __thread_arg {
	int cpu_id;
	pthread_t thread;
	counter_t *counter;
} thread_arg_t;

void init(counter_t *c) {
	c->value = 0;
	Mutex_init(&c->lock);
}

void increment(counter_t *c) {
	Pthread_mutex_lock(&c->lock);
	c->value++;
	Pthread_mutex_unlock(&c->lock);
}

void decrement(counter_t *c) {
	Pthread_mutex_lock(&c->lock);
	c->value--;
	Pthread_mutex_unlock(&c->lock);
}

int get(counter_t *c) {
	Pthread_mutex_lock(&c->lock);
	int rc = c->value;
	Pthread_mutex_unlock(&c->lock);
	return rc;
}

void *thread_function(void *arg) {
	printf("I am a thread\n");
	thread_arg_t *casted_arg = (thread_arg_t *) arg;
	printf("cpu id: %d\n", casted_arg->cpu_id);
	printf("thread: %ld\n", casted_arg->thread);
	//for (int i=0; i < 1000000; i++) {
	for (int i=0; i < 1000000; i++) {
		increment(casted_arg->counter);
		continue;
	}
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("not enough arguments\n");
		exit(1);
	}
	int num_of_threads = atoi(argv[1]);
	int num_of_cores = (int)sysconf(_SC_NPROCESSORS_ONLN);
	printf("number of cores: %d\n", num_of_cores);

	counter_t *counter;
	counter = malloc(sizeof(counter_t));
	init(counter);
	printf("get: %d\n", get(counter));

	thread_arg_t *args = malloc(num_of_threads * sizeof(thread_arg_t));

	struct timeval start, end;
	gettimeofday(&start, NULL);
	for (int i=0; i < num_of_threads; i++) {
		args[i].cpu_id = i;
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
