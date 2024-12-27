#ifndef LL_H
#define LL_H

typedef struct node node_t;

node_t * llinit(int val);
void llprint(node_t *head);
void llappend(node_t *head, int val);

#endif
