#define _XOPEN_SOURCE 700

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int a;
    printf("process pid is: %d\n", getpid());
    printf("expression a = 1 --> %d\n", a = 1);
    return EXIT_SUCCESS;
}