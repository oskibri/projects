#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool has_php_extesion(const char *filename) {
	const char *dot = strchr(filename, '.');
	return (dot && strcmp(dot, ".php") == 0);
}


int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Usage: %s <path>\n", argv[0]);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
