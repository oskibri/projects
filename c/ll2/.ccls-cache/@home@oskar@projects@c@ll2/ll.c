#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


typedef struct node {
	char *name;
	struct node *next;
} node;

int main(void) {
	struct node *head;
	struct node *oskar = (struct node *)malloc(sizeof(struct node));
	struct node *alice = malloc(sizeof(node));
	oskar->name = "oskar";
	alice->name = "alice";
	oskar->next = alice;

	head = oskar;
	head->name = "head";
	printf("%s %s\n", oskar->name, head->name);
	printf("%s %s\n", alice->name, head->name);

	free(oskar);
	return 0;
}
