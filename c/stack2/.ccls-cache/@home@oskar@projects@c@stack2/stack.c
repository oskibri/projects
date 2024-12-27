#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct stack {
	int *arr;
	int end;
	int MAX;
} stack;

void stackinit(stack *s, int max) {
	s->arr = malloc(sizeof(int) * max);
	s->end = -1;
	s->MAX = max;
}

void printstack(stack s) {
	for (int i = 0; i <= s.end; i++) {
		printf("%d\t%d\n", i, s.arr[i]);
	}
}

void stackinsert(stack *s, int val) {
	if (s->end == s->MAX - 1) return;
	s->end++;
	s->arr[s->end] = val;
}

void stackremove(stack *s) {
	if (s->end == -1) return;
	s->arr[s->end] = 0;
	s->end--;
}

int main(void) {
	stack s;
	stackinit(&s, 10);

	printstack(s);

	free(s.arr);
	return EXIT_SUCCESS;
}
