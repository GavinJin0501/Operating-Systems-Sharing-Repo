#define _XOPEN_SOURCE 700
#define N_CHILDREN 5

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void generate_process(int i) {
    if (i >= N_CHILDREN) return;

    pid_t child;
    switch (child = fork()) {
        case (pid_t) -1:
            perror("fork");
            exit(2);
        case (pid_t) 0:
            printf("CHILD > My pid: %d, parent pid: %d\n", getpid(), getppid());
            exit(i);
        default:
            generate_process(++i);
            return;
    }

    
}

int main(int argc, char* argv[]) {
    printf("Parent> My pid: %d, parent pid: %d\n", getpid(), getppid());
    generate_process(0);
    wait(NULL);
    return EXIT_SUCCESS;
}