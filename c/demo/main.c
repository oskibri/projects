// main.c
#include <stdio.h>
#include <mymath.h>

int main() {
	int x = 10, y = 5;

	printf("Add: %d + %d = %d\n", x, y, add(x, y));
	printf("Add: %d + %d = %d\n", x, y, add(x, y));
	printf("Sub: %d + %d = %d\n", x, y, sub(x, y));
	printf("Sub: %d + %d = %d\n", x+10, y, sub(x, y));

	return 0;
}
