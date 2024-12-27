#include <stdio.h>

struct person {
	char* name;
	int age;
};

int main() {
	printf("Hello world!\n");
	printf("asdojifsdfasfdoa");
	printf("asdfafd");

	struct person Oskar;
	Oskar.name = "Oskar Voldbakken Hesle";
	Oskar.age = 30;

	printf("Hello my name is %s, and my age is: %d\n", Oskar.name, Oskar.age);
	return 0;
}
