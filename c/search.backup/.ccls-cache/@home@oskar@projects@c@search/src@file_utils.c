


void remove_slash(char *path) {
	if (path == NULL) return;
	int length = strlen(path);
	while (path[length-1] == '/') {
		path[length-1] = '\0';
		length--;
	}
}
