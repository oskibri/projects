#include "../inc/traversal.h"
#include "../inc/file_utils.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
		if (strcmp(path, "/") == 0) {
			snprintf(fullpath, PATH_MAX, "%s%s", path, entry->d_name);
		} else {
			snprintf(fullpath, PATH_MAX, "%s/%s", path, entry->d_name);
		}

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
