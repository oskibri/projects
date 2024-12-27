#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct node {
	char *name;
	struct node *next;
} node;

node * create(char *name) {
	node *tmp = malloc(sizeof(node));
	tmp->name = name;
	tmp->next = NULL;
	return tmp;
}

void add(node **root, char *name) {
	if (*root == NULL) {
		*root = create(name);
		return;
	} else {
		node *current = *root;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = create(name);
	}
}
void llremove(node **root, char *name) {
	node *current = *root;

	if (current->name == name) {
		*root = current->next;
		return;
	}

	while (current != NULL) {
		if (current->next == NULL) {
			current = NULL; 
			return;
		} else if (current->next->name == name) {
			current->next = current->next->next;
			return;
		} else {
			current = current->next;
		}
	}
}

void print(node *root) {
	if (root == NULL) {
		fprintf(stderr, "Error: Not a list\n");
		exit(1);
	}
	printf("BEGIN\n");
	for (int i = 0; root != NULL; i++) {
		printf("%d:\t%s\n", i, root->name);
		root = root->next;
	}
	printf("END\n\n");
}

void free_list(node **root) {
	node *current = *root;
	printf("%p\t%p\n", current, *root);
	while (current != NULL) {
		node *next = current->next;
		free(current);
		current = next;
	}
	*root = NULL;
}

int main(void) {
	node **head;
	add(head, "Oskar");
	add(head, "Alice");
	add(head, "Snibri");
	print(*head);
	llremove(head, "Oskar");
	add(head, "Hello");
	llremove(head, "Snibri");
	add(head, "Hello");
	add(head, "Hello");
	add(head, "Hello");
	llremove(head, "Hello");
	print(*head);

	free_list(head);
	print(*head);
	return EXIT_SUCCESS;
}
