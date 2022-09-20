#define _XOPEN_SOURCE 700

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int a = 3;
    pid_t pid_child;

    a *= 2;
    if ((pid_child = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid_child == 0) {
        a = a + 3;
        printf("CHILD > child pid: %d, parent pid: %d, a = %d\n", getpid(), getppid(), a);
    } else {
        printf("PARENT> child pid: %d, parent pid: %d, a = %d\n", pid_child, getpid(), a);
    }

    return EXIT_SUCCESS;
}