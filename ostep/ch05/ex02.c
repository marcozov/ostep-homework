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
	int fd = open("ex02_output", O_CREAT|O_WRONLY|O_TRUNC|O_APPEND, S_IRWXU);
	//printf("fd: %d\n", fd);
	//printf("errno: %s\n", strerror(errno));

	char *myargs[3];
	myargs[0] = strdup("wc");
	myargs[1] = strdup("ex01.c");
	myargs[2] = NULL;

	int rc = fork();
	if (rc < 0) {
		printf("Error while forking the process\n");
	} else if (rc > 0) {
		//int rc_wait = wait(NULL);
		printf("I am the parent, my child is %d.\n", rc);
	} else {
		
		//close(STDOUT_FILENO);
		//int fd = open("ex02_output", O_CREAT|O_WRONLY|O_TRUNC|O_APPEND, S_IRWXU);
		//close(STDOUT_FILENO);
		printf("I am the child!\n");
		execvp(myargs[0], myargs);
	}
}
