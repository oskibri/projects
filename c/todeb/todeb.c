#include <stdio.h>
#include <string.h>

// ### Thu 05 Sep Oskar VH <oskar@servebolt.com> - `v1.3.0`
// -- Oskar Voldbakken Hesle <oskar@servebolt.com>  Thu, 05 Sep 2024 18:23:26 +0100
char* format_header_str(const char *str) {
	const char *ptr = str;
	char name[32];
	char email[32];

	//printf("%c", *b);
	char b, c, a;
	int i = 0;
	while (*ptr) {
		b = *(ptr-1), c = *ptr, a = *(ptr+1);
		//printf("%d: %c%c%c\n", i, b,c,a);
		
		if(b == '#' && c == '#' && a == '#') {
			char truple[1024];
			sprintf(truple, "%c%c%c", b,c,a);
			printf("%s\n", truple);
			printf("%d: %c%c%c\n", i, b,c,a);
		}
		
		ptr++;
		i++;
	}
	printf("\n");
}

int main() {
	FILE *ofile = fopen("1change", "r");
	FILE *nfile = fopen("2change", "w");

	if (ofile == NULL || nfile == NULL) {
		perror("Error opening file"); 
		return 1;
	}

	char final[1024] = {0};
	char line[1024] = {0};
	char dest[1024] = {0};
	while (fgets(line, sizeof(line), ofile) != NULL) {
		if (strncmp(line, "###", 3) == 0) {
			strncpy(dest, line, strlen(line)-1);
			continue;
		}

		for (int i = 0; line[i] != line[-1]; i++) {
			if (line[i-1] == ' ' && line[i] == '-' && line[i+1] == ' ') {
				line[i] = '*';
			}
		}
		strncat(final, line, strlen(line));
	}
	//printf("%s", final);
	//printf("%s\n", dest);
	format_header_str(dest);
	

	fclose(ofile);

	return 0;
}
