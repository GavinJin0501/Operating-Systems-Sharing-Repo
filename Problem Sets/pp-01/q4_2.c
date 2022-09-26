#define _XOPEN_SOURCE 700

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) { 
    int rcode;
    char runid[] = {'0', '\0'};
    
    if (argc > 1) {
        runid[0] = argv[1][0];
    }

    if (runid[0] > '1') {
        exit(100);
    }
    
    printf("%s\n", argv[0]);
    switch (fork()) {
        case -1:
            perror("fork1()");
            exit(1);
        case 0:
            printf("B\n");
            switch (fork()) {
                case -1:
                    perror("fork2()");
                    exit(1);
                case 0:
                    runid[0]++;
                    if (execl("./prog", "prog", runid, NULL) == -1) {
                        perror("execl");
                        exit(1);
                    }
                default:
                    exit(0);
            }
        default:
            wait(&rcode);
    }
}