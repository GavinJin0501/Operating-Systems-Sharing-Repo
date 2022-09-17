#include <stdio.h>
#include <string.h>

int main() {
	char str[] = "This is a string.";
	char* ps = str;

	*(ps + 10) = 'S';
	puts(ps);

	return 0;
}