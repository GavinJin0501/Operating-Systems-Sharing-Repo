#define _XOPEN_SOURCE 700
#define N_CHILDREN 5

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    pid_t child;
    int status;

    for (int i = 0; i < N_CHILDREN; i++) {
        child = fork();
        if (child == -1) {
            perror("fork");
            exit(-1);
        } else if (child == 0) {
            printf("CHILD > My pid: %d, parent pid: %d\n", getpid(), getppid());
            exit(i);
        }
    }

    wait(&status);
    printf("PARENT> My pid: %d, wait for: %d\n", getpid(), WEXITSTATUS(status));
    return EXIT_SUCCESS;
}