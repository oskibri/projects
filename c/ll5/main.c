#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct node {
	int val;
	struct node *next;
} node;

node *head = NULL;

void add(node **root, int val) {
	node *tmp = malloc(sizeof(node));
	if (*root == NULL) {
		tmp->val = val;
		tmp->next = NULL;
		*root = tmp;
	} else {
		tmp->val = val;
		tmp->next = *root;
		*root = tmp;
	}
}

void delete(node **root, int val) {
	if (*root == NULL) return;

	if ((*root)->val == val) {
		*root = (*root)->next;
		return;
	}

	while (*root != NULL) {
		node *prev = *root;
		node *tmp = (*root)->next;
		if (tmp->val == val && tmp->next != NULL) {
			prev->next = tmp->next;
			return;
		} else {
			free(tmp->next);
			prev->next = NULL;
			return;
		}
	}
}

void cleanup(node **root) {
	while (*root != NULL) {
		node *tmp = (*root)->next;
		free(*root);
		*root = tmp;
	}
}

void print(node *root) {
	while (root != NULL) {
		printf("%d->", root->val);
		root = root->next;
	}
	printf("NULL\n");
}

int main(void) {
	add(&head, 3);
	add(&head, 4);
	add(&head, 5);
	delete(&head, 4);
	delete(&head, 3);
	delete(&head, 5);
	add(&head, 32);
	print(head);

	cleanup(&head);
	return EXIT_SUCCESS;
}
