#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	printf("Hello, world %s\n", "asd");
	int x = 100;
	printf("x: %d\n", x);

	int rc = fork();
	if (rc < 0) {
		printf("Error while forking the process\n");
	} else if (rc > 0) {
		int rc_wait = wait(NULL);
		// x = 200;
		printf("I am the parent, my child is %d. x = %d\n", rc, x);
	} else {
		x = 300;
		printf("I am the child! x = %d\n", x);
	}
}
