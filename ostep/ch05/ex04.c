#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	printf("Hello, world %d\n", (int) getpid());
	
	int rc = fork();
	if (rc < 0) {
		printf("Error while forking the process\n");
	} else if (rc > 0) {
		//int rc_wait = wait(NULL);
		int rc_wait = waitpid(rc, NULL, WUNTRACED | WCONTINUED);
		printf("parent, wait: %d\n", rc_wait);
	} else {
		close(STDOUT_FILENO);
		//open("test", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
		int rc_wait = wait(NULL);
		//int rc_wait = waitpid(NULL);
		printf("child, wait: %d, pid %d\n", rc_wait, (int) getpid());
		char *myargs[2];
		myargs[0] = "";
		myargs[1] = NULL;
		execvp("/bin/ls", myargs);
	}
}
