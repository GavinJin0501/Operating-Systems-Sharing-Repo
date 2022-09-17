/* The first c program */

#include <stdio.h>

#define MSG "hello, 6.987 students"

int main() {
	// puts("hello, 6.087 students");
	const char msg[] = "hello, 6.987 students";
	puts(msg);
	puts(MSG);

	printf("Please enter your name: ");
	char name[50];
	gets(name);
	puts(name);
	return 0;
}