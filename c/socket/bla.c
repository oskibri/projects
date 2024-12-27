#include <stdio.h>
#include <stdlib.h>

struct sni {
	int age;
	char* name;
};

int main() {
	struct sni *s, *p;

	s = malloc(sizeof(struct sni));
	if (s == NULL) {printf("malloc err s\n"); return 1;}
	p = malloc(sizeof(struct sni));
	if (p == NULL) {printf("malloc err p\n"); return 1;}

	s->age = 18;
	s->name = "oskar";

	*p = *s;
	s->name = "benedicte";
	printf("%d, %s\n", p->age, p->name);
	printf("%d, %s\n", s->age, s->name);

	free(s);
	free(p);
	return 0;
}
