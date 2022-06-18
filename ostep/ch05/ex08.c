#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	printf("Hello, world %d\n", (int) getpid());
	
	int rc1 = fork();
	int rc2 = fork();
	if (rc1 < 0) {
		printf("Error while forking the process (1)\n");
	} else if (rc1 > 0) {
		//int rc_wait = wait(NULL);
		int rc_wait = waitpid(rc1, NULL, WUNTRACED | WCONTINUED);
		printf("(1) parent, wait: %d\n", rc_wait);
	} else {
		printf("(1) child\n");
	}

	if (rc2 < 0) {
		printf("Error while forking the process (2)\n");
	} else if (rc2 > 0) {
		int rc_wait = waitpid(rc2, NULL, WUNTRACED | WCONTINUED);
		printf("(2) parent, wait: %d\n", rc_wait);
	} else {
		printf("(2) child\n");
	}
}
