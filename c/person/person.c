#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct person {
	char *name;
	int age;
	void (*print)(struct person);
} person;

void print(person p) {
	printf("The person's name is: %s and their age is: %d\n", p.name, p.age);
};

person pinit(char *name, int age) {
	person p;
	p.name = name;
	p.age = age;
	p.print = &print;
	return p;
}

int main(void) {
	person oskar = pinit("Oskar", 30);
	oskar.print(oskar);

	return EXIT_SUCCESS;
}
