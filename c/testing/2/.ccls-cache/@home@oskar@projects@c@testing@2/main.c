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

	printf("%d\n", oskar.age);

	return EXIT_SUCCESS;
}
