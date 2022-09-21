#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define N 3

int main() {
    int i = 0;
    pid_t pid;
    printf("Parent> %d, pid: %d\n", i, getpid());

    while (i < N) {
        if ((pid = fork()) == -1) {
            perror("fork");
            exit(2);
        } else if (pid == 0) {
            i++;
        } else {
            break;
        }
        printf("Child> %d, pid: %d, parent pid: %d\n", i, getpid(), getppid());
    }

    return 0;
}