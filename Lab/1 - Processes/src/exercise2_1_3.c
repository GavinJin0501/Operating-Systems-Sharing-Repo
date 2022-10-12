#define _XOPEN_SOURCE 700
#define N_CHILDREN 5

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int pid, i;
    int status;
    for (i = 0; (i < N_CHILDREN) && ((pid=fork()) > 0); i++);

    if (pid == 0) {
        printf("CHILD > My parent pid: %d\n", getppid());
        exit(i);
    } else {
        for (int j = 0; j < N_CHILDREN; j++) {
            wait(&status);
            printf("PARENT> My pid: %d, wait for: %d\n", getpid(), WEXITSTATUS(status));
        }
    }

    return EXIT_SUCCESS;
}