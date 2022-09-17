#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int factorial(int n) {
	int i = 1, ret = 1;

	// while (i <= n) {
	// 	ret *= i;
	// 	i++;
	// }

	while (++i <= n) {
		ret *= i;
	}

	return ret;
}

double random_double() {
	/* generate radnom number in [0, 1) */
	double ret = (double) rand();
	return ret / RAND_MAX;
}

int sample_geometric_rv(double p) {
	// double q;
	// int n = 0;
	
	// do {
	// 	q = rand_double();
	// 	n++;
	// } while (q >= p);

	// return n;

	double q = random_double();
	int n = 0;

	while (q >= p) {
		printf("%f\n", q);
		n++;
		q = random_double();
	}

	return n;
}

int main() {
	printf("%d\n", factorial(1));
	printf("%d\n", factorial(2));
	printf("%d\n", factorial(3));
	puts("");
	time_t t;
	srand((unsigned) time(&t));
	printf("%d\n", sample_geometric_rv(0.5));
	return 0;
}