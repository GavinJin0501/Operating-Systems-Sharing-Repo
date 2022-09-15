#include <stdio.h>

void swap1(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}


int main() {
	int a = 0;
	int b = 1;
	printf("a: %d, b: %d\n", a, b);
	printf("a address: %p, b address: %p\n", &a, &b);

	swap1(&a, &b);
	printf("a: %d, b: %d\n", a, b);
	printf("a address: %p, b address: %p\n", &a, &b);



	return 0;
}
