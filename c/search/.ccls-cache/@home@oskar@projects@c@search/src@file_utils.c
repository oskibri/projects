#include "../inc/file_utils.h"
#include <dirent.h>
#include <string.h>

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

void remove_slash(char *path) {
	if (path == NULL || strcmp(path, "/") == 0) return;
	int length = strlen(path);
	while (path[length-1] == '/') {
		path[length-1] = '\0';
		length--;
	}
}
