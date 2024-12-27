#include <stdio.h>
#include <stdlib.h>
#include "ll.h"

int main() {
	node_t *my_linked_list = llinit(30);

	llappend(my_linked_list, 43);
	llprint(my_linked_list);
	llprint(my_linked_list);

	free(my_linked_list);
	return 0;
}
