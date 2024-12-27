#include "../inc/file_utils.h"
#include "../inc/traversal.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "Usage: %s <path> [exclude]\n", argv[0]);
		return EXIT_FAILURE;
	}

	char *exclude = NULL;
	if (argv[2]) {
		exclude = argv[2];
	}

	remove_slash(argv[1]);
	remove_slash(argv[2]);

	if (traverse(argv[1], argv[2]) == false) {
		fprintf(stderr, "Error: Full traversal of path %s, failed\n", argv[1]);
		return EXIT_FAILURE;
	};

	return EXIT_SUCCESS;
}
