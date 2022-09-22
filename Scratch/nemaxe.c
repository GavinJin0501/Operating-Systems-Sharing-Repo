#define _XOPEN_SOURCE 700

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int rcode;
    printf("%s\n", argv[0]);
    switch (fork()) {
        case -1:
            perror("fork1()");
            exit(1);
        case 0:
            switch (fork()) {
                case -1:
                    perror("fork()2");
                    exit(1);
                case 0:
                    if (execl("./prog","prog",NULL) == -1) { 
                        perror("execl");
                        printf("AHA");
                        exit(1); 
                    }
                default:
                    exit(0);
            }
        default:
            wait(&rcode);
    }
}