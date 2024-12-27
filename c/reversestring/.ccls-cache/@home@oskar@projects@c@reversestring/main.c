#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void reverse(char *str) {
	for (int i = 0; i < strlen(str)/2; i++) {
		char tmp = str[i];
		str[i] = str[strlen(str)-i-1];
		str[strlen(str)-i-1] = tmp;
	}
}

int main(void) {
	char str[] = "Hello, there my friend!";
	char str2[] = "!ereht ,olleH";
	reverse(str);
	reverse(str2);
	printf("%s\n%s\n", str, str2);

	return EXIT_SUCCESS;
}
