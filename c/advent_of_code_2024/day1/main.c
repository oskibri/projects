/* input:
 * 3   4
 * 4   3
 * 2   5
 * 1   3
 * 3   9
 * 3   3
 */

#include <stdio.h>
#include <stdlib.h>

int comp(const void *a, const void *b) {
	return (*(int*)a - *(int*)b);
}

int main(void) {
	FILE *input = fopen("input.txt", "r");
	char line[256];
	int left_int, right_int;
	int left[1000], right[1000];
	// int *left = malloc(sizeof(int));
	// int *right = malloc(sizeof(int));

	int nmemb = 0;
	while (fgets(line, sizeof(line), input)) {
		if (sscanf(line, "%d\t%d", &left_int, &right_int) != -1) {
			left[nmemb] = left_int;
			right[nmemb] = right_int;
			// left = realloc(left, (nmemb + 1) * sizeof(int));
			// right = realloc(right, (nmemb + 1) * sizeof(int));
			nmemb++;
		}
	}
	printf("%d\n", nmemb);

	qsort(left, nmemb, sizeof(int), comp);
	qsort(right, nmemb, sizeof(int), comp);

	int diff = 0;
	for (int i = 0; i < nmemb; i++) {
		int local_diff = left[i] - right[i];
		if (local_diff < 0) local_diff *= -1;
		diff += local_diff;
	}
	printf("Total diff: %d\n", diff);

	fclose(input);
	return 0;
}
