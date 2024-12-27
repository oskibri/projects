#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct data {
	char* name;
	int age;
};

union uni {
	char* name;
	int age;
};

int main(void) {
	union uni oskar;

	oskar.name = "Oskar";
	oskar.age = 30;

	printf("%s\n", oskar.name);

	return EXIT_SUCCESS;
}
