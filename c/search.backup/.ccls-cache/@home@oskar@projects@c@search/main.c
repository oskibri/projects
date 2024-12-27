#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>

const char *entry_type_name(unsigned char d_type) {
	switch (d_type) {
		case DT_DIR: return "\x1b[1;34mDIR\x1b[0m";
		case DT_REG: return "\x1b[32mREG\x1b[0m";
		case DT_LNK: return "\x1b[36mLNK\x1b[0m";
		case DT_CHR: return "CHR";
		case DT_BLK: return "BLK";
		case DT_WHT: return "WHT";
		case DT_SOCK: return "SOCK";
		case DT_FIFO: return "PIPE";
		case DT_UNKNOWN: return "UNKOWN";
		default: return "ERROR"; 
	}
}

bool traverse(const char *path, const char *exclude) {
	DIR *dir = opendir(path);
	if (dir == NULL) {
		char buf[PATH_MAX + 18];	
		snprintf(buf, sizeof(buf), "OPENDIR Failed (%s)", path);
		perror(buf);
		return false;
	}

	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL) {

		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
		if (exclude && strcmp(entry->d_name, exclude) == 0) continue;

		char fullpath[PATH_MAX];
		snprintf(fullpath, PATH_MAX, "%s/%s", path, entry->d_name);

		const char *type_name = entry_type_name(entry->d_type);
		if (strcmp(type_name, "ERROR") == 0) {
			fprintf(stderr, "Error: Russians, or aliens\n");
			closedir(dir);
			exit(51);
		}

		printf("(%s) --- %s\n", type_name, fullpath);

		if (entry->d_type == DT_DIR) {
			if (traverse(fullpath, exclude) == false) continue;
		}
	}

	closedir(dir);
	return true;
}

void remove_slash(char *path) {
	if (path == NULL) return;
	int length = strlen(path);
	while (path[length-1] == '/') {
		path[length-1] = '\0';
		length--;
	}
}

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
