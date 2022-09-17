#include <stdio.h>

// char* get_message() {
// 	char msg[] = "Aren't pointers fun?";
// 	return msg;
// }
#define array_length(arr) (sizeof(arr) == 0) ? 0 : sizeof(arr) / sizeof(arr[0])

int main() {
	// char* string = get_message();
	// puts(string);

	int arr[2];
	arr[0] = 0;
	arr[1] = 1;

	int* pa = arr;
	printf("%d\n", *pa);
	printf("%d\n", *(pa++));
	printf("size of arr is: %ld\n", array_length(pa));
	return 0;
}