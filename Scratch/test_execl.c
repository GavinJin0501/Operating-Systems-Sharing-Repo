#define _XOPEN_SOURCE 700

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int p;
    p = fork();
    if (p == 0) {
        execl("/bin/echo", "echo", "In", "the", "child", NULL); 
    }
    wait(NULL);
    printf ( "In the parent \n");
    return EXIT_SUCCESS;
}