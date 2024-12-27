#include "../inc/file_utils.h"
#include "../inc/traversal.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "Usage: %s <path> [exclude]\n", argv[0]);
		return EXIT_FAILURE;
	}
	char *path = argv[1];

	char *exclude = NULL;
	if (argv[2]) {
		exclude = argv[2];
	}

	remove_slash(path);
	remove_slash(exclude);

	if (traverse(path, exclude) == false) {
		fprintf(stderr, "Error: Full traversal of path %s, failed\n", argv[1]);
		return EXIT_FAILURE;
	};

	return EXIT_SUCCESS;
}
