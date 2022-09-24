#define _XOPEN_SOURCE 700
#define N_CHILDREN 5

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int i = 0;
    pid_t child;

    while (i < N_CHILDREN) {
        switch (child = fork()) {
            case (pid_t) -1:
                perror("fork");
                exit(2);
            case (pid_t) 0:
                i = N_CHILDREN + 1;
                break;
            default:
                i++;
        }
    }

    wait(NULL);   
    printf("My pid: %d, parent pid: %d, child pid: %d\n", getpid(), getppid(), child);
    return EXIT_SUCCESS;
}