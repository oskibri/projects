#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define STACK_MAX 10  // Define the max size of the stack as a macro

typedef struct stack {
    int *arr;
    int end;
    int MAX;
} stack;

// Stack initialization function
void stack_init(stack *s, int max) {
    s->arr = malloc(sizeof(int) * max);
    if (s->arr == NULL) {
        perror("Failed to allocate memory for stack");
        exit(EXIT_FAILURE);
    }
    s->end = -1;
    s->MAX = max;
}

// Stack cleanup function
void stack_cleanup(stack *s) {
    free(s->arr);
    s->arr = NULL;  // Set to NULL to avoid dangling pointer issues
}

// Print the stack elements
void print_stack(stack *s) {
    if (s->end == -1) {
        printf("Stack is empty.\n");
        return;
    }

    printf("Stack contents:\n");
    for (int i = 0; i <= s->end; i++) {
        printf("%d: %d\n", i, s->arr[i]);
    }
    printf("\n");
}

// Insert an element onto the stack
void stack_insert(stack *s, int val) {
    if (s->end == s->MAX - 1) {
        printf("Stack overflow: Unable to insert %d\n", val);
        return;
    }
    s->end++;
    s->arr[s->end] = val;
}

// Remove an element from the stack
void stack_remove(stack *s) {
    if (s->end == -1) {
        printf("Stack underflow: Unable to remove element\n");
        return;
    }
    s->end--;  // No need to set the value to 0, just decrement end
}

int main(void) {
    stack s;
    stack_init(&s, STACK_MAX);

    // Insert some elements onto the stack
    for (int i = 1; i <= 5; i++) {
        stack_insert(&s, i);
    }

    print_stack(&s);

    // Remove two elements from the stack
    stack_remove(&s);
    stack_remove(&s);

    print_stack(&s);

    // Insert more elements to test overflow
    for (int i = 6; i <= 13; i++) {
        stack_insert(&s, i);
    }

    print_stack(&s);

    stack_cleanup(&s);
    return EXIT_SUCCESS;
}

