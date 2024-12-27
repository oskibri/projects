#include <stdio.h>
#include <string.h>

int main(void) {

	char *arr[] = {"hello", "there", "snibri"};
	printf("%lu\n", sizeof(arr) / sizeof(char*));

	return 0;
}
