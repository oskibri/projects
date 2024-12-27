#include <netdb.h>
#include <stdio.h>

struct person {
	int age;
	char* name;
};

struct name {
	int age;
};

int main() {
	struct sockaddr_storage client_addr;
	struct sockaddr_in *addr_in = (struct sockaddr_in *)&client_addr;  // Correct
	struct person oskar;

	oskar.name = "Oskar";
	oskar.age = 30;

	struct name o = (struct name)oskar;

	printf("%d\n", o.age);

	return 0;
}
