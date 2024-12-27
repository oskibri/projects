#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node {
	int data;
	char* string;
	char arr[23];
} Node;

void run(Node** node) {
	(*node)->data = 30;
	char* som = "Hello there how are you?";
	(*node)->string = som;
	strncpy((*node)->arr, "I'm doing good thanks!", 23);
}

int main() {
	Node* mynode = malloc(sizeof(Node));
	run(&mynode);
	free(mynode);
	return 0;
}
