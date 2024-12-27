#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
	int data;
	struct Node* next;
} Node;

typedef struct LinkedList {
	Node* head;
} LinkedList;

Node* createNode(int data) {
	Node* newNode = malloc(sizeof(Node));
	if (!newNode) {
		perror("Error allocating memory for createNode");
		exit(EXIT_FAILURE);
	}
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

LinkedList* createLinkedList(void) {
	LinkedList* newList = malloc(sizeof(LinkedList));
	if (!newList) {
		perror("Error allocating memory for createLinkedList");
		exit(EXIT_FAILURE);
	}
	newList->head = NULL;
	return newList;
}

void appendDataToListDoublePtr(LinkedList* list, int data) {
	Node** current = &list->head;
	while (*current != NULL) {
		current = &(*current)->next;
	}
	*current = createNode(data);
}

void appendDataToList(LinkedList* list, int data) {
	if (list->head == NULL) {
		list->head = createNode(data);
		return;
	}

	Node* current = list->head;
	while (current->next != NULL) current = current->next;
	current->next = createNode(data);
}

void appendDataToListWrong(LinkedList* list, int data) {
	Node* current = list->head;
	if (current == NULL) {
		current = createNode(data);
		return;
	}

	while (current->next != NULL) current = current->next;
	current->next = createNode(data);
}

void printLinkedList(LinkedList* list) {
	Node* current = list->head;
	int index = 0;
	printf("Printing elements from list:\n");
	while (current != NULL) {
		printf("Element #%d: %d\n", index, current->data);
		current = current->next;
		index++;
	}
}

void freeLinkedList(LinkedList* list) {
	Node* current = list->head;
	Node* temp = list->head;
	while (current != NULL) {
		temp = current->next;
		free(current);
		current = temp;
	}
	free(list);
}

int main() {
	LinkedList* mylist = createLinkedList();
	appendDataToListDoublePtr(mylist, 1);
	appendDataToList(mylist, 2);
	appendDataToListDoublePtr(mylist, 3);
	printLinkedList(mylist);
	
	freeLinkedList(mylist);
	return 0;
}
