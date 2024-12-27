#include "ll.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct node {
	int val;
	struct node *next;
} node_t;

node_t * llinit(int val) {
	node_t *head = malloc(sizeof(node_t));
	head->val = val;
	head->next = NULL;
	return head;
}

void llprint(node_t *head) {
	node_t *tmp = head;
	while (tmp != NULL) {
		printf("%d\n", head->val);
		tmp = tmp->next;
	}
}

void llappend(node_t *head, int val) {
	node_t *tmp = head;
	while (tmp->next != NULL) {
		tmp = tmp->next;
	}


}
