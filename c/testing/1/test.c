#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

struct person {
	char *name;
	int age;
};

int pnew(char *name, int age, struct person **p) {
	*p = malloc(sizeof(struct person));
	if(!*p) {
		errno = ENOMEM;
		return -1;
	}
	
	(*p)->name = name;
	(*p)->age = age;
	return 0;
}

// === MAIN === //
int main(int argc, char **argv) {
	if (argc != 3) {
		printf("Usage: %s <name> <age>\nExample: %s \"Oskar\" 30\n", argv[0], argv[0]);
		return 1;
	}

	char *name = argv[1];
	int age = atoi(argv[2]);

	struct person *p;
	if (pnew(name, age, &p) != 0) {
		perror("pnew");
		return 1;
	}
	printf("name: %s\nage: %d\n", p->name, p->age);

	free(p);
	return 0;
}
