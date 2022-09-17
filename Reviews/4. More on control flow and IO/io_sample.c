#include <stdio.h>

int main() {
	puts("Convert uppercase to lowercase: ");
	char c;

	while ((c = getchar()) != EOF) {
		if (c >= 'A' && c <= 'Z') {
			c = c - 'A' + 'a';
		}
		putchar(c);
	}

	printf("\n\n");

	FILE *fp = NULL;
	const int size = 15;
	char line[size];

	fp = fopen("./names.txt", "r");
	while (fgets(line, size, fp) != NULL) {
		printf("%s", line);
	}
	puts("");
	fclose(fp);

	return 0;
}