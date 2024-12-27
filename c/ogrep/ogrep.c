#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>

void search_mm(const char *filename, const char *pattern) {
	int file = open(filename, O_RDONLY);
	if (file == -1) {
		perror("open");
		return;
	}

	struct stat st;
	if (fstat(file, &st) == -1) {
		perror("fstat");
		close(file);
		return;
	}

	if (st.st_size == 0) {
		fprintf(stderr, "%s: No size\n", filename);
		close(file);
		return;
	}

	char *data = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, file, 0);
	if (data == MAP_FAILED) {
		perror("mmap");
		close(file);
		exit(EXIT_FAILURE);
	}

	char *match = strstr(data, pattern);
    while (match != NULL) {
        // printf("Found match at position %ld in file %s on line %d\n", match - data, filename, count);
        match = strstr(match + 1, pattern);
    }

	munmap(data, st.st_size);
	close(file);
}

void search_line(const char *filename, const char *pattern) {
	FILE *file = fopen(filename, "r");
	char *buf;
	size_t t = 0;
	int line;
	while (getline(&buf, &t, file) != EOF) {
		if (strstr(buf, pattern)) {
			// printf("%s", buf);
		}
	}	
	fclose(file);
	free(buf);
}

void opend(char *path, char *pattern) {
	DIR *dir = opendir(path);
	if (dir == NULL) {
		perror(path);
		closedir(dir);
		return;
	}
	struct dirent *file;


	char buf[PATH_MAX], *fullp;
	while ((file = readdir(dir)) != NULL) {

		char *filename = file->d_name;
		if (strcmp(filename, ".") == 0 || strcmp(filename, "..") == 0) continue;
		
		snprintf(buf, PATH_MAX, "%s/%s", path, filename);
		fullp = realpath(buf, NULL);
		if (fullp == NULL) {
			perror("fullpath");
			continue;
		}

		if (file->d_type == DT_REG) {
			// printf("(%u):\t%s\n", file->d_type, fullp);
			search_mm(fullp, pattern);
		} else if (file->d_type == DT_DIR) {
			opend(fullp, pattern);
		}

		free(fullp);
	}
	closedir(dir);
}

int main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <path>\n", argv[0]);
		return EXIT_FAILURE;
	}

	struct stat path_stat;
	char *path = realpath(argv[1], NULL);
	if (path == NULL) {
		perror("fullpath main");
		return EXIT_FAILURE;;
	}
	char *pattern = argv[2];

	if (stat(path, &path_stat) != 0) {
		perror("stat");
		free(path);
		return EXIT_FAILURE;
	}

	if (S_ISREG(path_stat.st_mode)) {
		// printf("file\n");
		search_mm(path, pattern);
		// return EXIT_SUCCESS;
	} else if (S_ISDIR(path_stat.st_mode)) {
		opend(path, pattern);
	} else {
		fprintf(stderr, "neither\n");
		return EXIT_FAILURE;
	}

	free(path);
	return EXIT_SUCCESS;
}
// search_line("shake.txt", "are");

