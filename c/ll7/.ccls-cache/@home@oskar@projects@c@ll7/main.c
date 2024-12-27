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

Node* createNode(int data) {
	Node* newNode = malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

LinkedList* createLinkedList() {
	LinkedList* newList = malloc(sizeof(LinkedList));
	newList->head = NULL;
	return newList;
}

void appendToList(LinkedList* listptr, int data) {
	Node** current = &listptr->head;
	while (*current != NULL) current = &(*current)->next;
	*current = createNode(data);
}

// void printLinkedList(LinkedList* list) {
// 	Node* current = list->head;
// 	int index = 0;
// 	while (current != NULL) {
// 		printf("%d: %d\n", index, current->data);
// 		current = current->next;
// 		index++;
// 	}
// }
//
// void freeLinkedList(LinkedList* list) {
// 	Node* current = list->head;
// 	Node* temp = NULL;
// 	while (current != NULL) {
// 		temp = current;
// 		free(current);
// 		current = temp->next;
// 	}
// 	free(list);
// }

int main(void) {
	LinkedList* mylist = createLinkedList();

	appendToList(mylist, 30);
	appendToList(mylist, 50);

	// printLinkedList(mylist);
	//
	// freeLinkedList(mylist);
	return EXIT_SUCCESS;
}
