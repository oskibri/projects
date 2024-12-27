#include <stdlib.h>
#include <stdio.h>
  
typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
      Node* head;
} List;

void modify(Node* som) {
	struct Node** cur = malloc(sizeof(struct Node));
	cur = &som;
	(*cur)->data = 10;
	// free(*cur);
}

int main() {
    Node* mynode = malloc(sizeof(Node));
    // Node* current = malloc(sizeof(Node));
    Node* current = mynode;
	modify(current);
	printf("%d\n", current->data);

	free(mynode);
    return 0;
}
