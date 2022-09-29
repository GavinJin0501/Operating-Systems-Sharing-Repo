/**** decoder.c ****/

#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <decoder.h>


#define _XOPEN_SOURCE 700
#define NUM_OF_CHILDREN 10


int magicsq[3][3] = {{4, -1, 8}, {-1, -1, -1}, {2, -1, 6}};


int check() {
	int i, j, sums[8];
	for (i = 0; i < 8; i++) 
		sums[i] = 0;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			sums[i] += magicsq[i][j];
			sums[i+3] += magicsq[j][i];
			if (i == j) sums[6] += magicsq[i][j];
			if ((i+j) == 2) sums[7] += magicsq[i][j];
		}
	}
	int result = 1;
	i = 1;
	while ((i < 8) && (result == 1)) {
		if (sums[0] != sums[i])
			result = 0;
		i++;
	}
	return result;
}


void display() {
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++)
			printf("  %d", magicsq[i][j]);
		printf("\n");
	}
	printf("\n");
}


int solve(int a) {
	/* CODE THAT EVERY CHILD PROCESS EXECUTES */
	int sum, b, c, d, e;
	
	magicsq[0][1] = a;
	sum = magicsq[0][0] + magicsq[0][1] + magicsq[0][2];
	b = sum - magicsq[0][0] - magicsq[2][0];
	d = sum - magicsq[0][2] - magicsq[2][2];
	e = sum - magicsq[2][0] - magicsq[2][2];
	c = sum - a - e;

	magicsq[1][0] = b;
	magicsq[1][1] = c;
	magicsq[1][2] = d;
	magicsq[2][1] = e;

	if (check() == 1) {
		display();
		return 1;
	}
	return 0;
}

int main(int argc, char **argv)
{	
	/* PARENT PROCESS */
	int i, pid;

	for (i = 0; (i < NUM_OF_CHILDREN) && ((pid = fork()) > 0); i++);

	if (pid == -1) {
		perror("fork");
		exit(-1);
	} else if (pid == 0) {
		int val = solve(i);
		if (val == 1) {
			printf("Child %d> my pid is: %d\n", i, getpid());
		}
		exit(0);
	} else {
		for (int j = 0; i < NUM_OF_CHILDREN; j++) {
			wait(0);
		}
	}
}
