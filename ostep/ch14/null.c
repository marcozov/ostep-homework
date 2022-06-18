#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	printf("Hello, world\n");
	//int *p = NULL;
	int *p = malloc(sizeof(int));
	*p = 3;
	printf("p: %p\n", p);
	printf("dereference p: %d\n", *p);
}
