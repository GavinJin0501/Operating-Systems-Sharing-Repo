#include <stdio.h>

int nmax = 20;

int main(int args, char **argv) {
	int a = 0, b = 1, c, n;
	printf("%3d: %d\n", 1, a);
	printf("%3d: %d\n", 2, b);

	for (n = 3; n <= nmax; n++) {
		c = a + b; a = b; b = c;
		printf("%3d: %d\n", n, c);
	}

	return 0;
}


