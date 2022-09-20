#define _XOPEN_SOURCE 700

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int a, e;
    a = 10;
    if (fork() == 0) {
        a = a * 2;
        if (fork() == 0) {
            a = a + 1;
            // exit(2);
        }
        printf("%d \n", a);
        exit(a);
    }
    wait(&e);
    printf("a:%d; e:%d\n", a, WEXITSTATUS(e));

    return 0;
}