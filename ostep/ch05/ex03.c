#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	printf("Hello, world %s\n", "asd");
	
	close(STDOUT_FILENO);
	int fd = open("ex03_output", O_CREAT|O_WRONLY|O_TRUNC|O_APPEND, S_IRWXU);
	int rc = fork();
	if (rc < 0) {
		printf("Error while forking the process\n");
	} else if (rc > 0) {
		sleep(10);
		//int rc_wait = wait(NULL);
		printf("goodbye\n");
	} else {
		
		printf("hello\n");
	}
}
