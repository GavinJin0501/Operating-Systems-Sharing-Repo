#include <stdio.h>

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int main() {
	printf("Hello world!\n");
	printf("Hello world, again!\n");
	
	printf("Hello world!\n");

	int a = 0;
	int b = 1;
	swap(&a, &b);

	printf("a: %d, b: %d\n", a, b);
	return 0;

}