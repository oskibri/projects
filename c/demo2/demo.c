#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void add2(int *i) {
	*i = *i + 2;
}

int main(void) {
	int *mynum = malloc(sizeof(int));
	add2(mynum);
	printf("%d\n", *mynum);

	free(mynum);
	return EXIT_SUCCESS;
}
