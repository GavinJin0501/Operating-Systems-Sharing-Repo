#define _XOEPN_SOURCE 700

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    pid_t pid;
    printf("Begin\n");
    
    
    if ((pid = fork()) == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        printf("child execition 1 \n");
    } else {
        printf("parent execition 2 \n");
    }

    printf("End\n");
    return EXIT_SUCCESS;
}