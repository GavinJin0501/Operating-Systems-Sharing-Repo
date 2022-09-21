#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define N 3

int main() {
    int i = 0;
    int status;
    pid_t init_pid = getpid();
    pid_t pid; // for child process

    while (i < N) {
        if ((pid = fork()) == -1) {
            perror("fork");
            exit(2);
        } else if (pid == 0) {
            i++;
        } else {
            break;
        }
    }

    if (pid != 0) { // is parent
        wait(&status);
    }

    printf("%s> %d, pid: %d, parent pid: %d, exit: %d\n", (getpid() == init_pid) ? "Initial" : "Child", i, getpid(), getppid(), WEXITSTATUS(status));
    
    return i;
}