#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define STACK_MAX 10

typedef struct stack {
	int MAX;
	int arr[MAX];
	int end;
} stack;

void initstack(int *stack, int *end) {
	for(int i = 0; i < sizeof(*stack) / sizeof(int); i++) {
		stack[i] = '\0';
	}
	*end = -1;
}

void printstack(int stack[], int end) {
	for(int i = 0; i <= end; i++) {
		printf("%d:\t%d\n", i, stack[i]);
	}
}

int insertstack(int *stack, int *end, int val) {
	if (*end == STACK_MAX - 1) {
		fprintf(stderr, "\033[1;31minsertstack error:\033[0m Over max stack size of: %d\n", STACK_MAX);
		return *end;
	}
	stack[++(*end)] = val;
	return *end;
}

void removestack(int stack[], int *end) {
	if (*end == -1) {
		fprintf(stderr, "\033[1;31mremovestack error:\033[0m No more elements to remove\n");
		return;
	}
	stack[*end] = '\0';
	* end = *end - 1;
}

int main(void) {
	int s[STACK_MAX], e;
	initstack(s, &e);

	insertstack(s, &e, 32);
	insertstack(s, &e, 32);
	removestack(s, &e);
	removestack(s, &e);
	insertstack(s, &e, 242);
	insertstack(s, &e, 123);
	printstack(s, e);

	return EXIT_SUCCESS;
}
