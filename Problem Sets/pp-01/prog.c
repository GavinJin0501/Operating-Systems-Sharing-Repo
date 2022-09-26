#define _XOPEN_SOURCE 700

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) { 
    printf("argc: %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("%d: %s\n", i, argv[i]);
    }
}