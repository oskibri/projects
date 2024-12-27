#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *next;
} Node;

typedef struct LinkedList {
	Node *head;
} LinkedList;

LinkedList* createList() {
	LinkedList *newList = malloc(sizeof(LinkedList));
	newList->head = NULL;
	return newList;
}

Node* createNode(int data) {
	Node *newNode = malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

void appendList(LinkedList *list, int data) {
	Node *newNode = createNode(data);
	
	if (list->head == NULL) {
		list->head = newNode;
	} else {
		Node *temp = list->head;
		while (temp->next != NULL) temp = temp->next;
		temp->next = newNode;
	}
}

void removeFromList(LinkedList *list, int data) {
	if (list->head == NULL) {
		printf("List is empty\n");
		return;
	} 

	Node *temp = list->head;

	if (temp->data == data) {
		list->head = temp->next;
		free(temp);
		return;
	}

	Node *prev = NULL;
	while (temp != NULL && temp->data != data) {
		prev = temp;
		temp = temp->next;
	}

        if (temp == ((void *)0)) {
          printf("Element %d not found in the list\n", data);
          return;
        }

        prev->next = temp->next;
	free(temp);
}

void traverseList(LinkedList *list) {
	if (list->head == NULL) {
		printf("List is empty\n");
		return;
	} else {
		Node *temp = list->head;
		while (temp != NULL) {
			printf("%d\t", temp->data);
			temp = temp->next;
		}
		printf("\n");
	}
}

void freeList(LinkedList *list) {
	Node *temp = list->head;
	while (temp != NULL) {
		Node *next = temp->next;
		free(temp);
		temp = next;
	}
	free(list);
}

int main() {
	LinkedList *mylist = createList();
	appendList(mylist, 10);
	appendList(mylist, 50);
	appendList(mylist, 20);
	removeFromList(mylist, 11);
	traverseList(mylist);
	freeList(mylist);
	return 0;
}
