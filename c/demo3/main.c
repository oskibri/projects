#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void) {
	char *s[] = {"Hello", "there"};

	int *d = malloc(sizeof(int));
	*d = 40;

	free(d);
	free(d);

	*s = NULL;
	return EXIT_SUCCESS;
}
