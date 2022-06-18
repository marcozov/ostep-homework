#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	printf("Hello, world\n");
	int *p = (int*) malloc(100*sizeof(int));
	p[0] = 10;
	//p[100] = 10;
	p[99] = 10;
	printf("p: %p\n", p);
	//printf("dereference p: %d\n", *p);
	//printf("p[100]: %d\n", p[100]);
	printf("p[100]: %d\n", p[99]);

	//free(p);
	free(p+4);

	p[0] = 30;
}
