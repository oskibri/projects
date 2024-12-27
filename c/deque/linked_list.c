#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	void *data;
	struct Node *prev;
	struct Node *next;
} Node;

typedef struct DoublyLinkedList {
	Node *head;
	Node *tail;
} DoublyLinkedList;

DoublyLinkedList* createList() {
	DoublyLinkedList *list = malloc(sizeof(DoublyLinkedList));
	list->head = NULL;
	list->tail = NULL;
	return list;
}

Node* createNode(void *data) {
	Node *newNode = malloc(sizeof(Node));
	newNode->data = data;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}

void insertAtBeginning(DoublyLinkedList *list, void *data) {
	Node *newNode = createNode(data);

	if (list->head == NULL) {
		list->head = list->tail = newNode;
	} else {
		newNode->next = list->head;
		list->head->prev = newNode;
		list->head = newNode;
	}
}

void insertAtEnd(DoublyLinkedList *list, void *data) {
	Node *newNode = createNode(data);

	if (list->tail == NULL) {
		list->head = list->tail = newNode;
	} else {
		newNode->prev = list->tail;
		list->tail->next = newNode;
		list->tail = newNode;
	}
}

void traverseForward(DoublyLinkedList *list) {
	Node *current = list->head;
	printf("List (Forward): ");
	while (current != NULL) {
		
		printf("%d ", *(int*)current->data);
		current = current->next;
	}
	printf("\n");
}

void deleteFromEnd(DoublyLinkedList *list) {
	if (list->tail == NULL) {
		printf("List is empty\n");
		return;
	}

	Node *temp = list->tail;
	list->tail = list->tail->prev;

	if (list->tail != NULL) {
		list->tail->next = NULL;
	} else {
		list->head = NULL;
	}

	free(temp);
}

int main(void) {
	DoublyLinkedList *list = createList();
	int item1 = 30, item2 = 40, item3 = 10;
	char *item4 = "Hello there";
	insertAtEnd(list, &item1);
	insertAtEnd(list, &item2);
	insertAtBeginning(list, &item3);
	insertAtBeginning(list, item4);
	traverseForward(list);
	deleteFromEnd(list);
	traverseForward(list);

	free(list);
	return 0;
}
