#define _XOPEN_SOURCE 700
#define N_CHILDREN 5

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void generate_process(int i) {
    if ((i < N_CHILDREN) && (fork() > 0)) {
        generate_process(++i);
    } else if (i < N_CHILDREN) {
        printf("Child > My pid: %d, parent pid: %d\n", getpid(), getppid());
    }
}

int main(int argc, char* argv[]) {
    printf("Parent> My pid: %d, parent pid: %d\n", getpid(), getppid());
    generate_process(0);
    wait(NULL);
    return EXIT_SUCCESS;
}