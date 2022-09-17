#include <stdio.h>

#define array_length(arr) (sizeof(arr) == 0) ? 0 : sizeof(arr) / sizeof(arr[0])

int linear_search(int* arr, int val) {
	int n = array_length(arr);

	for (int i = 0; i < n; i++) {
		if (arr[i] == val) {
			return i;
		}
	}

	return -1;
}

int main() {
	int arr[] = {1, 2, 3, 4, 5};
	printf("Exists: %d\n", linear_search(arr, 1) != -1);
	return 0;
}