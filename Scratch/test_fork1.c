#define _XOPEN_SOURCE 700

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    pid_t pid_child;

    switch (pid_child = fork()) {
    case (pid_t) -1:
        perror("fork");
        exit(1);
    case (pid_t) 0:
        sleep(2);
        printf("CHILD> pid %d, parent pid %d \n", getpid(), getppid());
        return EXIT_SUCCESS;
    default:
        printf("PARENT> pid %d, child pid %d \n", getpid(), pid_child);
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}