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
	for (int i = 0; root != NULL; i++) {
		printf("%d:\t%s\n", i, root->name);
		root = root->next;
	}
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
	char buf[100];
	for (int i = 0; i < 35000; i++) {
		sprintf(buf, "name_%d", i);
		ll_add(&head, buf);
	}
	for (int i = 20000; i < 25000; i++) {
		sprintf(buf, "name_%d", i);
		ll_remove(&head, buf);
	}

	ll_print(head);
	ll_free(&head);
	return EXIT_SUCCESS;
}
