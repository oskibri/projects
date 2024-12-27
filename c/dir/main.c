#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void trav(char *d) {
	DIR *dir = opendir(d);

	if (dir == NULL) {
		printf("%s\n", d);
		perror("opendir");
		return;
	}

	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL) {

		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || entry->d_name[0] == '.')
			continue;

		char fullpath[PATH_MAX];
		snprintf(fullpath, sizeof(fullpath), "%s/%s", d, entry->d_name);

		switch(entry->d_type) {
			case DT_DIR:
				printf("(DIR)  \033[1;34m%s\033[0m/\n", fullpath);
				trav(fullpath);
				break;
			case DT_REG:
				printf("(FILE) %s\n", fullpath);
				break;
			default:
				printf("Unknown file trype...\n");
				break;
		}
	}
	closedir(dir);
}
void remove_slash(char **path) {
	char *arg = *path;
	while (arg[strlen(arg) - 1] == '/') {
		arg[strlen(arg) - 1] = '\0';
	}
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Not enough args\n");
		return EXIT_FAILURE;
	}

	remove_slash(&argv[1]);
	
	trav(argv[1]);
	return EXIT_SUCCESS;
}
