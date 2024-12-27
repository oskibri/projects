#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>

#define NAME_MAX 255
#define TABLE_SIZE 10

typedef struct {
	char name[NAME_MAX];
	int age;
} person;

person *table[TABLE_SIZE];

int hash(char *name) {
	int len = strnlen(name, NAME_MAX);
	int hash = 0;
	for (int i = 0; i < len; i++) {
		hash += hash + name[i];
		hash = (hash * name[i]) % TABLE_SIZE;
	}
	return hash;
}

void init_hash(void) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		table[i] = NULL;	
	}
}

void print_hash(person **table) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (table[i] == NULL) {
			printf("\t%d\t----\n", i);
		} else {
			printf("\t%d\t%s\n", i, table[i]->name);
		}
	}
}

bool insert_hash(person *p) {
	if (p == NULL) return false;
	int index = hash(p->name);
	if (table[index] != NULL) {
		return false;
	}
	table[index] = p;
	return true;
}

int main(void) {
	init_hash();
	// print_hash(table);
	person oskar = {.name = "oskar", .age = 30};
	person Oskar = {.name = "snibri", .age = 30};
	insert_hash(&oskar);
	insert_hash(&Oskar);
	print_hash(table);

	//print_hash(table);


	// person bill = {"bill", 30};
	// person jane = {"jane", 30};
	// person stian = {"stian", 30};
	//
	// printf("%s: %d\n", bill.name, hash(&bill));
	// printf("%s: %d\n", jane.name, hash(&jane));
	// printf("%s: %d\n", stian.name, hash(&stian));

	return EXIT_SUCCESS;
}
