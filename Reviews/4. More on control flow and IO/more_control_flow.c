#include <stdio.h>

int main() {

	start: {
		if (1) {
			goto outside;
		}
		printf("This is inside!\n");
		goto start;
	}

	outside: 
	printf("This is outside\n");

	return 0;
}   