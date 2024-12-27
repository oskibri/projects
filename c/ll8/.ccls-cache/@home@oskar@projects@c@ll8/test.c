#include <stdio.h>
#include <stdlib.h>

struct test1 {
	int data;
};

struct test2 {
	struct test1* test2test1;
};

struct test3 {
	struct test2* test3test2;
};

int main() {
	struct test3* mytest = malloc(sizeof(struct test3));
	mytest->test3test2 = malloc(sizeof(struct test2));
	mytest->test3test2->test2test1 = malloc(sizeof(struct test1));
	mytest->test3test2->test2test1->data = 10;

	// struct test1* another = malloc(sizeof(struct test1));
	struct test1* another = mytest->test3test2->test2test1;

	printf("%d\n", mytest->test3test2->test2test1->data);	

	another->data = 12;

	printf("%d\n", mytest->test3test2->test2test1->data);	

	free(mytest->test3test2->test2test1);
	free(mytest->test3test2);
	free(mytest);
	return 0;
}
