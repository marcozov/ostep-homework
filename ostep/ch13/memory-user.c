#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	printf("Hello world (%d)\n", getpid());

	if (argc < 2) {
		printf("2 parameters required\n");
		exit(1);
	}
	int n = atoi(argv[1]);
	printf("number of MB: %d\n", n);

	printf("wat\n");
	int bytes = n*(1024*1024);
	printf("wat\n");
	//int bytes = 1024;
	printf("bytes: %d\n", bytes);
	
	char *p = (char*) malloc(bytes);
	int i = 0;
	while (1) {
		//p[i % bytes] = 0;
		p[i % bytes] = (char) rand();
		i++;
		i = (i+1) % 2147483647;
		// printf("i: %d\n", i);
	}



}
