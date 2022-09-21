#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define N 3

int main() {
    int i = 0;
    int status;
    pid_t init_process = getpid(); // main(initial) process
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

    if (getpid() == init_process) { // only the main process waits for its child
        wait(&status);
        printf("Parent> %d, pid: %d\n", i, init_process);
    } else {
        printf("Child> %d, pid: %d, parent pid: %d, exit: %d\n", i, getpid(), getppid(), WEXITSTATUS(status));
    }
    
    return i;
}