#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct node {
    char *name;
    struct node *next;
} node;

node *ll_new() {
    return NULL;
}

node *__ll_create(char *name) {
    node *tmp = malloc(sizeof(node));
    if (!tmp) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    tmp->name = name;
    tmp->next = NULL;
    return tmp;
}

void ll_add(node **root, char *name) {
    node *tmp = *root;
    if (tmp == NULL) {
        *root = __ll_create(name);
        return;
    }

    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = __ll_create(name);
}

void ll_print(node *root) {
    for (int i = 0; root != NULL; i++) {
        printf("%d:\t%s\n", i, root->name);
        root = root->next;
    }
}

void ll_remove(node **root, char *name) {
    node *tmp = *root;
    node *prev = NULL;

    while (tmp != NULL && strcmp(tmp->name, name) == 0) {
        *root = tmp->next;
        free(tmp);
        tmp = *root; // Update tmp to the new root
    }

    while (tmp != NULL) {
        if (strcmp(tmp->name, name) == 0) {
            prev->next = tmp->next;
            free(tmp);
            tmp = prev->next; // Move to the next node after removing current
        } else {
            prev = tmp;
            tmp = tmp->next;
        }
    }
}

void ll_free(node **root) {
    node *tmp = *root;
    while (tmp != NULL) {
        node *tmp_next = tmp->next;
        free(tmp);
        tmp = tmp_next;
    }
    *root = NULL;
}

int main(void) {
    node *head = ll_new();
    ll_add(&head, "Oskar");
    ll_add(&head, "Oskar");
    ll_add(&head, "Oskar");
    ll_add(&head, "Benedicte");
    ll_add(&head, "Simen");
    ll_add(&head, "Stian");
    ll_add(&head, "Bob");
	ll_add(&head, "Oskar");

    ll_remove(&head, "Oskar");
    ll_print(head);

    ll_free(&head);
    return EXIT_SUCCESS;
}

