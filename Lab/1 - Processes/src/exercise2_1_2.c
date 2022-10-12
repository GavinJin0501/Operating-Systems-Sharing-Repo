#define _XOPEN_SOURCE 700
#define N_CHILDREN 5

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int pid, i, status;
    for (i = 0; (i < N_CHILDREN) && ((pid=fork()) > 0); i++);

    if (pid == 0) {
        printf("CHILD > i: %d, My parent pid: %d, My pid: %d\n", i, getppid(), getpid());
        exit(i);
    } else {
        waitpid(pid, &status, 0);
        printf("PARENT> My pid: %d, wait for: %d\n", getpid(), WEXITSTATUS(status));
    }

    return EXIT_SUCCESS;
}