#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>

int map(const char *file) {
	unsigned int fd = open(file, O_RDONLY);
	if (fd == -1) {
		perror("open");
		return EXIT_FAILURE;
	}

	struct stat st;
	if (fstat(fd, &st)) {
		perror("fstat");
		close(fd);
		return EXIT_FAILURE;
	}
	printf("%lu\n", st.st_size);

	char *ptr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

	printf("%s", ptr);

	munmap(ptr, st.st_size);
	close(fd);
	return EXIT_SUCCESS;
}

int fop(const char *file) {
	FILE *f = fopen(file, "r");
	if (f == NULL) {
		perror("fopen");
		return EXIT_FAILURE;
	}

	struct stat st;
	if (stat(file, &st) == -1) {
		perror("fstat");
		fclose(f);
		return EXIT_FAILURE;
	}
	printf("%lu\n", st.st_size);

	char buf[st.st_size];
	int ret = fread(buf, sizeof(buf), sizeof(char), f);
	if (!ret) {
		fprintf(stderr, "fread failer");
		fclose(f);
		return EXIT_FAILURE;
	}

	printf("%s", buf);

	fclose(f);
	return EXIT_SUCCESS;
}

int main(int c, char **v) {
	if (c != 3) return EXIT_FAILURE;
	const char *path = v[2];

	if (strcmp(v[1], "fop") == 0) {
		if (fop(path) != 0) {
			fprintf(stderr, "fopen failed\n");
			return EXIT_FAILURE;
		}
	} else if (strcmp(v[1], "map") == 0) {
		if (map(path) != 0) {
			fprintf(stderr, "mmap failed\n");
			return EXIT_FAILURE;
		}
	} else {
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
