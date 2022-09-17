#include <stdio.h>

enum sz1{S1=0, L1=3, XL1};
enum sz2{S2=0, L2=-3, XL2};

int main() {
	// 1. Numeric (int, float, double)
	int a = 3;
	float b = 3.14;
	double c = 3.1415926;

	printf("%d, %f, %lf\n", a, b, c);

	// 2. Character (char)
	char ch1 = 'j';
	char ch2 = 'y';

	printf("%c%c%c\n", ch1, ch1, ch2);

	// 3. User defined (struct, union)
	char name[] = "Gavin Jin";
	puts(name);

	printf("size of char  : %lu\n", sizeof(char));
	printf("size of short : %lu\n", sizeof(short));
	printf("size of int   : %lu\n", sizeof(int));
	printf("size of long  : %lu\n", sizeof(long));
	printf("size of double: %lu\n", sizeof(double));

	int x = 017;
	int y = 12;
	printf("%d\n", x > y);
	// short int s = 0xFFFF12;
	char cc = -1;
	unsigned char uc = -1;
	printf("cc: %c, uc: %c\n", cc, uc);

	puts("Gavin" "Jin");
	printf("S1: %d, L1: %d, XL1: %d\n", S1, L1, XL1);
	printf("S2: %d, L2: %d, XL2: %d\n", S2, L2, XL2);

	return 0;
}