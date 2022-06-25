#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
	printf("asd\n");
	struct timeval start, end;

	gettimeofday(&start, NULL);
	gettimeofday(&end, NULL);

	printf("start: %ld\n", start.tv_usec);
	printf("end: %ld\n", end.tv_usec);
}
