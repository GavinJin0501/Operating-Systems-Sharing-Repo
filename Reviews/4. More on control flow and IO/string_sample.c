#include <stdio.h>
#include <string.h>

int main() {
	char name1[] = "Gavin Jin";
	char name2[] = "Bernice Feng";

	printf("name1 equal to name2: %d\n", strcmp(name1, name2));

	// char name[10];
	int n;

	while (scanf("%d", &n) != EOF) {
		printf("val: %d\n", n);
	}

	return 0;
}