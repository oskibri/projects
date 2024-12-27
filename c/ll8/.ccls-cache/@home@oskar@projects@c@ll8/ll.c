#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct Node {
	int data;
	struct Node* next;
} Node;

typedef struct LinkedList {
	Node* head;
} LinkedList;

Node* create_node(int data) {
	Node* newNode = malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

LinkedList* create_ll() {
	LinkedList* newList = malloc(sizeof(LinkedList));
	newList->head = NULL;
	return newList;
}

void append_toll(LinkedList* list, int data) {
	Node** current = &list->head;
	while (*current != NULL) current = &(*current)->next;
	*current = create_node(data);
}

void prepend_toll(LinkedList* list, int data) {
	Node* newNode = create_node(data);
	newNode->next = list->head;
	list->head = newNode;
}

void rm_ll(LinkedList* list, int data, int nremoves) {
	Node** current = &list->head;
	Node* next = NULL;
	while ((nremoves > 0 || nremoves <= -1) && *current != NULL) {
		if ((*current)->data == data) {
			next = (*current)->next;
			free(*current);
			*current = next;
			nremoves--;
			continue;
		}
		current = &(*current)->next;
	}
}

void free_ll(LinkedList* list) {
	Node* current = list->head;
	free(list);

	Node* next = current->next;
	while (next != NULL) {
		free(current);
		current = next;
		next = current->next;
	}
	free(current);
}

void print_ll(LinkedList* list) {
	Node* current = list->head;
	int i = 0;
	while (current != NULL) {
		printf("Element #%d:\t%d\n", i, current->data);
		current = current->next;
		i++;
	}
}

void print_ll2(LinkedList* list) {
	Node* p;
	for (p = list->head; p != NULL; p = p->next) {
		printf("%p:\t%d\n", p, p->data);
	}
}

int main(void) {
	LinkedList* mylist = create_ll();
	append_toll(mylist, 10);
	append_toll(mylist, 20);
	append_toll(mylist, 10);
	prepend_toll(mylist, 5);
	append_toll(mylist, 10);

	print_ll(mylist);

	rm_ll(mylist, 10, -1);

	printf("\n");
	print_ll2(mylist);
	// print_ll(mylist);

	free_ll(mylist);
	return EXIT_SUCCESS;
}
