#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct Num {
	int number;
} Num;

void modifyPtr(int* ptr) {
	int* local = ptr;
	*local = 30;
} 

void modifyNum(Num* num) {
	int local = num->number;
	local = 30;

	// num->number = 30;	
}

int main(void) {
	Num* mynum = malloc(sizeof(Num));
	mynum->number = 10;
	modifyNum(mynum);

	printf("%d\n", mynum->number);

	free(mynum);
	return EXIT_SUCCESS;
}
