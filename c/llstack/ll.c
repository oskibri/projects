#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct node {
	char *name;
	struct node *next;
} node;

node * ll_new() {
	return NULL;
}

node * __ll_create(char *name) {
	node *tmp = malloc(sizeof(node));
	if (!tmp) {
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	tmp->name = strdup(name);
	if (tmp->name == NULL) {
		perror("Failed to allocate memory for name");
		exit(EXIT_FAILURE);
	}
	tmp->next = NULL;
	return tmp;
}

void ll_add(node **root, char *name) {
	node *tmp = *root;
	if (tmp == NULL) {
		*root = __ll_create(name);
		return;
	}

	while (tmp->next != NULL) {
		tmp = tmp->next;
	}
	tmp->next = __ll_create(name);
}

void ll_print(node *root) {
	printf("BEGIN\n");
	for (int i = 0; root != NULL; i++) {
		printf("%d:\t%s\n", i, root->name);
		root = root->next;
	}
	printf("END\n\n");
}

void ll_remove(node **root, char *name) {
	node *tmp = *root;
	node *prev = NULL;

	while (tmp != NULL && strcmp(tmp->name, name) == 0) {
		*root = tmp->next;
		free(tmp->name);
		free(tmp);
		tmp = *root;
	}

	while (tmp != NULL) {
		if (strcmp(tmp->name, name) == 0) {
			prev->next = tmp->next;
			free(tmp->name);
			free(tmp);
			tmp = prev->next;
		} else {
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

void ll_remove_last(node **root) {
	node *tmp = *root;
	node *prev = NULL;

	if (*root == NULL) {
		return;
	}

	while (tmp->next != NULL) {
		prev = tmp;
		tmp = tmp->next;
	}

	if (prev == NULL && tmp != NULL) {
		free(tmp->name);
		free(tmp);
		*root = NULL;
		return;
	}

	prev->next = NULL;
	free(tmp->name);
	free(tmp);
}

void ll_free(node **root) {
	node *tmp = *root;
	while (tmp != NULL) {
		node *tmp_next = tmp->next;
		free(tmp->name);
		free(tmp);
		tmp = tmp_next;
	}
	*root = NULL;
}

int main(void) {
	node *head = ll_new();
	ll_add(&head, "Oskar");
	ll_add(&head, "Benedicte");
	ll_add(&head, "Simen");
	ll_add(&head, "Bob");
	ll_print(head);

	ll_remove_last(&head);
	ll_remove_last(&head);
	ll_remove_last(&head);
	ll_remove_last(&head);
	ll_remove_last(&head);
	ll_add(&head, "Oskar");
	ll_add(&head, "Bob");
	ll_print(head);

	ll_free(&head);
	return EXIT_SUCCESS;
}
